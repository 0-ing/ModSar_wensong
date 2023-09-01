#ifndef SPSC_QUEUE_HPP
#define SPSC_QUEUE_HPP

#include "internal/ReturnVal.hpp"
#include "internal/Slot.hpp"
#include "pipc/utils/Expect.hpp"

#include <cstddef>

namespace pipc
{
/**
 * @brief SPSC queue.
 *
 * @todo
 * Only supports powers of 2 at the moment (see full queue check at
 * try_emplace). Might make sense to enhance this one to support any size.
 */
template<typename T, size_t N, bool CacheAligned = true>
class SpScQueue
{
private:
    static_assert(std::is_nothrow_copy_assignable<T>::value || std::is_nothrow_move_assignable<T>::value,
                  "T must be nothrow copy or move assignable");
    static_assert(std::is_nothrow_destructible<T>::value, "T must be nothrow destructible");
    static_assert(N >= 1, "N must be at least 1");

public:
    explicit constexpr SpScQueue() noexcept : head_(0), tail_(0)
    {
        static_assert(sizeof(SpScQueue) % cacheLineSize == 0,
                      "Queue size must be a multiple of cache line size to "
                      "prevent false sharing between adjacent queues");
    }

    ~SpScQueue() noexcept = default;

    /* @brief Copy and move is not allowed. */
    SpScQueue(const SpScQueue&) = delete;
    SpScQueue& operator=(const SpScQueue&) = delete;

    /**
     * @brief Emplace an item, return false if queue is full.
     *
     * @remark
     * In case the queue is not full, we increment only head.
     * In case we have a full queue, increment head as well as tail.
     */
    template<typename... Args>
    inline ReturnVal try_emplace(Args&&... args) noexcept
    {
        static_assert(std::is_nothrow_constructible<T, Args&&...>::value,
                      "T must be nothrow constructible with Args&&...");

        auto head = head_.load(std::memory_order_relaxed);
        auto tail = tail_.load(std::memory_order_relaxed);
        // Early exit if queue is full
        if (EXPECT_UNLIKELY(head == tail + N))
        {
            return ReturnVal::kQueueFull;
        }
        auto& slot = slots_[idx(head)];
        slot.construct(std::forward<Args>(args)...);
        head_.store(head + 1, std::memory_order_release);
        return ReturnVal::kOk;
    }

    inline ReturnVal try_push(const T& v) noexcept
    {
        static_assert(std::is_nothrow_copy_constructible<T>::value, "T must be nothrow copy constructible");
        return try_emplace(v);
    }

    template<typename P, typename = typename std::enable_if<std::is_nothrow_constructible<T, P&&>::value>::type>
    inline ReturnVal try_push(P&& v) noexcept
    {
        return try_emplace(std::forward<P>(v));
    }

    /**
     * @brief Pop from the queue, return false if queue is empty.
     *
     * @remark
     * If the queue is not empty, we need to first buffer the slot and then try to
     * increment tail. If the increment is not successful, the slot could have
     * been overridden while we tried to get it.
     */
    ReturnVal try_pop(T& v) noexcept
    {
        auto tail = tail_.load(std::memory_order_relaxed);
        auto head = head_.load(std::memory_order_relaxed);
        // If the queue is empty, we need to exit early
        if (EXPECT_UNLIKELY(tail == head))
        {
            return ReturnVal::kQueueEmpty;
        }
        auto& slot = slots_[idx(tail)];
        v          = slot.move();
        tail_.store(tail + 1, std::memory_order_release);
        return ReturnVal::kOk;
    }

    /** @brief Check if the queue is empty. */
    inline bool empty()
    {
        auto head = head_.load(std::memory_order_relaxed);
        auto tail = tail_.load(std::memory_order_relaxed);
        return (head == tail);
    }

    /** @brief return size of the queue. */
    inline size_t capacity() const
    {
        return N;
    }

private:
    constexpr size_t idx(size_t i) const noexcept
    {
        return i % N;
    }
    constexpr static size_t size_t_align()
    {
        return ((CacheAligned) ? (cacheLineSize) : alignof(size_t));
    }

private:
    Slot<T, CacheAligned> slots_[N];
    /**
     * @brief Head and tail.
     *
     * @remark
     * Cache alignment is there, but will not work well since
     * producer and consumer both access head & tail.
     */
    alignas(size_t_align()) std::atomic<size_t> head_;
    alignas(size_t_align()) std::atomic<size_t> tail_;
};

} // namespace pipc

#endif // SPSC_QUEUE_HPP
