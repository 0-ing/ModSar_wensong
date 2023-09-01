#ifndef SPSC_OV_QUEUE_HPP
#define SPSC_OV_QUEUE_HPP

#include "internal/ReturnVal.hpp"
#include "internal/Slot.hpp"
#include "pipc/utils/Expect.hpp"

namespace pipc
{
/**
 * @brief SPSC queue with overflow support.
 *
 * This is FIFO which pops the oldest value when pushing to a full queue.
 * This means that calling try_push will always succeed.
 * Don't use this type of queue if you don't have to, the SPSC queue without
 * overflow support performs better.
 *
 * @todo
 * Only supports powers of 2 at the moment (see full queue check at
 * try_emplace). Might make sense to enhance this one to support any size.
 */
template<typename T, size_t N, bool CacheAligned = true>
class SpScOvQueue
{
private:
    static_assert(std::is_nothrow_copy_assignable<T>::value || std::is_nothrow_move_assignable<T>::value,
                  "T must be nothrow copy or move assignable");
    static_assert(std::is_nothrow_destructible<T>::value, "T must be nothrow destructible");
    static_assert(N >= 1, "N must be at least 1");

public:
    explicit constexpr SpScOvQueue() noexcept : head_(0), tail_(0)
    {
        // static_assert(sizeof(SpScOvQueue) % cacheLineSize == 0,
        //               "Queue size must be a multiple of cache line size to "
        //               "prevent false sharing between adjacent queues");
    }

    ~SpScOvQueue() noexcept = default;

    /* @brief Copy and move is not allowed. */
    SpScOvQueue(const SpScOvQueue&) = delete;
    SpScOvQueue& operator=(const SpScOvQueue&) = delete;

    /** @brief Check if the queue is empty. */
    inline bool empty()
    {
        auto head = head_.load(std::memory_order_relaxed);
        auto tail = tail_.load(std::memory_order_relaxed);
        return (head == tail);
    }

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
        // TODO: We need to check if and why exactly we need this
        // static_assert(std::is_nothrow_constructible<T, Args &&...>::value,
        //               "T must be nothrow constructible with Args&&...");

        auto head = head_.load(std::memory_order_relaxed);
        auto tail = tail_.load(std::memory_order_relaxed);
        // If the queue is full, we need to try to increment
        // the tail before proceeding
        if (EXPECT_UNLIKELY(head == tail + N))
        {
            // No need to check for failure: If the CAS did not succeed,
            // the consumer has fetched the slot in the meantime
            tail_.compare_exchange_strong(tail, tail + 1);
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
        do
        {
            // Try to fetch the slot and update the tail, until we succeed
            auto& slot = slots_[idx(tail)];
            v          = slot.move();
        } while (!tail_.compare_exchange_weak(tail, tail + 1));

        return ReturnVal::kOk;
    }

private:
    constexpr static size_t idx(size_t i)
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
     * Cache alignment can be enabled, but will not work well since
     * producer and consumer both access head & tail.
     */
    alignas(size_t_align()) std::atomic<size_t> head_;
    alignas(size_t_align()) std::atomic<size_t> tail_;
};

} // namespace pipc

#endif // SPSC_OV_QUEUE_HPP
