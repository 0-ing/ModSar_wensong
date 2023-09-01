#ifndef PIPC_QUEUE_MPMC_QUEUE_HPP
#define PIPC_QUEUE_MPMC_QUEUE_HPP

#include "internal/ReturnVal.hpp"
#include "internal/SlotWithSeqCnt.hpp"
#include "pipc/utils/Expect.hpp"

#include <atomic>
#include <cassert>
#include <cstddef> // offsetof
#include <limits>
#include <stdexcept>

namespace pipc
{
/**
 * @brief Bounded Multiple Producer Multiple Consumer Queue.
 *
 * The queue is statically allocated and uses a sequence counter for ABA
 * detection. The slot's turn variable consists of a 31-bit sequence counter and
 * the LSB indicates 0 for empty slot and 1 for a slot with data to be read.
 *
 * @todo
 * Make N max-size parameter and make the queue resizable for 'maxSamples'
 * support later.
 */
template<typename T, size_t N, bool CacheAligned = true>
class MpMcQueue
{
private:
    static_assert(std::is_nothrow_copy_assignable<T>::value || std::is_nothrow_move_assignable<T>::value,
                  "T must be nothrow copy or move assignable");
    static_assert(std::is_nothrow_destructible<T>::value, "T must be nothrow destructible");
    static_assert(N >= 1, "N must be at least 1");

public:
    /**
     * @brief Constructor with basic initialization.
     *
     * TODO:
     * Change so that the turns don't need special initialization at startup.
     * Try to use a bit toggle per wrap-around or counter in high bits, should be
     * sufficient for ABA.
     */
    explicit MpMcQueue() noexcept : head_(0), tail_(0)
    {
        for (size_t i = 0; i < N; i++)
        {
            slots_[i].turn.store((i << 1U), std::memory_order_relaxed);
        }
    }

    ~MpMcQueue() noexcept = default;

    /** @brief Copy and move is not allowed. */
    MpMcQueue(const MpMcQueue&) = delete;
    MpMcQueue& operator=(const MpMcQueue&) = delete;

    /** @brief Wrapper for calling a push on an object. */
    static ReturnVal Try_push(MpMcQueue* obj, T v)
    {
        return obj->try_push(v);
    }

    /** @brief Check if the queue is empty. */
    inline bool empty()
    {
        auto head = head_.load(std::memory_order_relaxed);
        auto tail = tail_.load(std::memory_order_relaxed);
        return (head == tail);
    }

    /** @brief Check if the queue is full. */
    inline bool full()
    {
        auto head = head_.load(std::memory_order_relaxed);
        auto tail = tail_.load(std::memory_order_relaxed);
        return (head == (tail + N));
    }

    /**
     * @brief Report the current size of the queue.
     *
     * @todo Check atomicity and usefulness, currently only used
     * in a benchmark.
     */
    inline size_t size() const
    {
        auto tail = tail_.load(std::memory_order_acquire);
        auto head = head_.load(std::memory_order_relaxed);
        return (head - tail);
    }

    /** @brief Emplace an item, return false if queue is full. */
    template<typename... Args>
    ReturnVal try_emplace(Args&&... args) noexcept
    {
        static_assert(std::is_nothrow_constructible<T, Args&&...>::value,
                      "T must be nothrow constructible with Args&&...");

        auto head = head_.load(std::memory_order_acquire);
        do
        {
            auto& slot = slots_[idx(head)];
            if (slot.turn.load(std::memory_order_acquire) == (head << 1U))
            {
                if (head_.compare_exchange_strong(head, head + 1))
                {
                    slot.construct(std::forward<Args>(args)...);
                    slot.turn.store((head << 1U) + 1U, std::memory_order_release);
                    return ReturnVal::kOk;
                }
            }
            else
            {
                auto lastHead = head;
                head          = head_.load(std::memory_order_acquire);
                if (lastHead == head)
                {
                    return ReturnVal::kQueueFull;
                }
            }
        } while (true);
    }

    /** @brief Copy-push into the queue. */
    inline ReturnVal try_push(const T& v) noexcept
    {
        static_assert(std::is_nothrow_copy_constructible<T>::value, "T must be nothrow copy constructible");
        return try_emplace(v);
    }

    /** @brief Move-push into the queue. */
    template<typename P, typename = typename std::enable_if<std::is_nothrow_constructible<T, P&&>::value>::type>
    ReturnVal try_push(P&& v) noexcept
    {
        return try_emplace(std::forward<P>(v));
    }

    /** @brief Pop from the queue, return false if queue is empty. */
    inline ReturnVal try_pop(T& v) noexcept
    {
        auto tail = tail_.load(std::memory_order_acquire);
        do
        {
            auto& slot = slots_[idx(tail)];
            if (slot.turn.load(std::memory_order_acquire) == (tail << 1U) + 1U)
            {
                if (tail_.compare_exchange_strong(tail, tail + 1))
                {
                    v = slot.move();
                    slot.turn.store(((tail + N) << 1U), std::memory_order_release);
                    return ReturnVal::kOk;
                }
            }
            else
            {
                auto lastTail = tail;
                tail          = tail_.load(std::memory_order_acquire);
                if (lastTail == tail)
                {
                    return ReturnVal::kQueueEmpty;
                }
            }
        } while (true);
    }

private:
    constexpr size_t idx(size_t i) const noexcept
    {
        return i % N;
    }

private:
    SlotWithSeqCnt<T, CacheAligned> slots_[N];
    /** @brief Head index. */
    alignas(utils::GetAlignment<size_t, CacheAligned>()) std::atomic<size_t> head_;
    /** @brief Tail index. */
    alignas(utils::GetAlignment<size_t, CacheAligned>()) std::atomic<size_t> tail_;
};

} // namespace pipc

#endif // PIPC_QUEUE_MPMC_QUEUE_HPP
