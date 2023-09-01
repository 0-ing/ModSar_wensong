#ifndef PIMP_BUFFER_HPP
#define PIMP_BUFFER_HPP

#include "SeqAndCnt.hpp"
#include "pipc/Config.hpp"
#include "pipc/e2e/IntegralWrapper.hpp"
#include "pipc/e2e/TypeWrapper.hpp"
#include "pipc/queue/internal/ReturnVal.hpp"
#include "pipc/utils/CacheLineSize.hpp"
#include "pipc/utils/Expect.hpp"

#include <atomic>
#include <cassert>
#include <cstddef> // offsetof
#include <limits>
#include <stdexcept>

namespace pipc
{
namespace pimp
{
namespace internal
{
/**
 * @brief A slot representing one item in the queue.
 *
 * Each slot has up to NBytes storage and a sequence counter.
 * The slot can be instantiated with or without E2E protection.
 *
 * @tparam NBytes The size of the slot's storage.
 * @tparam QueueStateProtection Sets whether to use an
 *         unprotected integral or one with inverse storage for the sequence counter.
 * @tparam PayloadProtection Sets whether to use unprotected
 * storage for the payload or protect it with inverse storage.
 *
 * @remark
 * The slot imposes the following requirements for data put into it:
 * - it must fit into the slot's storage
 * - it must be at least aligned to 8 Byte boundaries
 *   (because we pop unknown slot contents in 8 Byte chunks)
 * - it must be at most aligned to the slot's alignment
 *
 */
template<size_t NBytes, e2e::E2EProtection QueueStateProtection, e2e::E2EProtection PayloadProtection>
struct Slot
{
    /** @brief IntegralWrapper used for queue state protection. */
    using IntegralWrapper = typename e2e::IntegralWrapper<uint16_t, QueueStateProtection>::type;
    /** @brief TypeWrapper used for payload protection. */
    template<typename T>
    using TypeWrapper = typename e2e::TypeWrapper<T, PayloadProtection>::type;
    /**
     * @brief SlotStorage used as anonymuous storage object.
     *
     * The SlotStorage can be used as a buffer when popping from the
     * queue, when the type is unknown. It represents the net size of the actual data
     * without payload protection.
     */
    using SlotStorage = typename std::aligned_storage<NBytes, 8U>::type;

    Slot() noexcept
    {
        static_assert(alignof(Slot) == cacheLineSize,
                      "Slot must be aligned to cache line boundary to prevent false sharing");
        static_assert(sizeof(Slot) % cacheLineSize == 0,
                      "Slot size must be a multiple of cache line size to prevent "
                      "false sharing between adjacent slots");
    }

    /** @brief Construct a known type. */
    template<typename T, typename... Args>
    inline void construct(Args&&... args) noexcept
    {
        static_assert(std::is_nothrow_constructible<T, Args&&...>::value,
                      "T must be nothrow constructible with Args&&...");
        static_assert(sizeof(T) <= NBytes, "T must fit into the slot's storage.");
        static_assert(alignof(T) <= alignof(Slot), "T's alignment must be no more than the slot's alignment.");
        static_assert(alignof(T) >= 8, "T must be at least aligned to 8 Byte boundaries.");
        TypeWrapper<T>* tmp = reinterpret_cast<TypeWrapper<T>*>(&storage);
        tmp->construct(std::forward<Args>(args)...);
        // Round the size up to the next multiple of 8 Bytes
        payloadCnt.reset(((sizeof(T) + 7U) / 8U));
    }

    /** @brief Copy a known type into the object reference. */
    template<typename T>
    inline bool copy(T& obj)
    {
        static_assert(sizeof(T) <= NBytes, "T must fit into the slot's storage.");
        static_assert(alignof(T) <= alignof(Slot), "T's alignment must be no more than the slot's alignment.");
        static_assert(alignof(T) >= 8, "T must be at least aligned to 8 Byte boundaries.");
        TypeWrapper<T>* tmp = reinterpret_cast<TypeWrapper<T>*>(&storage);
        return tmp->copy(obj);
    }

    /** @brief Copy an unknown protected type into the object reference. */
    template<e2e::E2EProtection P = PayloadProtection>
    inline typename std::enable_if<P == e2e::E2EProtection::kInverse, bool>::type copy(SlotStorage& obj)
    {
        uint16_t cnt;
        bool success = payloadCnt.get(cnt);
        // Early exit in case cnt is corrupted, otherwise we could access OOB
        if (EXPECT_UNLIKELY(!success))
        {
            return success;
        }

        uint64_t* src = reinterpret_cast<uint64_t*>(&storage);
        uint64_t* inv = &src[cnt];
        uint64_t* dst = reinterpret_cast<uint64_t*>(&obj);
        for (size_t i = cnt; i > 0; i--)
        {
            auto tmp = *src++;
            *dst++   = tmp;
            success &= (tmp == ~(*inv++));
        }
        return success;
    }

    /** @brief Sequence counter. */
    alignas(cacheLineSize) std::atomic<IntegralWrapper> turn = {0};
    /**
     * @brief Count of 8-Byte chunks of the payload (without protection).
     *
     * The count is used when popping an unknown type from a queue
     * with payload protection for checking the payload.
     */
    IntegralWrapper payloadCnt;
    /** @brief Total storage required for the slot (with protection). */
    TypeWrapper<SlotStorage> storage;
};

} // namespace internal

/**
 * @brief Queue for sending & receiving messages.
 *
 * The queue is based on a MPSC queue and extends it to provide
 * type-agnostic access to queue slots as well as E2E protection.
 *
 * E2E protection:
 * Queue state and payload can either be unprotected or configured with a
 * specific protection mode.
 *
 * Push extension:
 * Provides a templated push operation to push different types with
 * different sizes into the queue (limited up to the max slot size).
 *
 * Pop extension:
 * Provides a peek operation (e.g. to get a port no.) to defer the pop operation
 * to the receive handler, which knows the underlying type of the payload.
 *
 * TODO:
 * try_emplace with in-place construction might not be valid, as the
 * slot is in untrusted space and reading values from it during construction
 * might be illegal!
 * How do we make sure this can never be done by the user?
 */
template<size_t NMaxPayload                      = PIPC_PIMP_APP_MAX_PAYLOAD_SIZE,
         size_t N                                = PIPC_PIMP_APP_QUEUE_SIZE,
         e2e::E2EProtection QueueStateProtection = e2e::E2EProtection::kInverse,
         e2e::E2EProtection PayloadProtection    = e2e::E2EProtection::kInverse>
class Queue
{
    /** @brief Type of a single slot. */
    using Slot = internal::Slot<NMaxPayload, QueueStateProtection, PayloadProtection>;

    template<typename T>
    using TypeWrapper = typename e2e::TypeWrapper<T, PayloadProtection>::type;
    static_assert(N >= 4, "N must be at least 4");
    static_assert(N < UINT16_MAX, "N must be less than UINT16_MAX");
    static_assert(N && !(N & (N - 1)), "N must be a power of 2");
    static_assert(ATOMIC_LLONG_LOCK_FREE == 2, "Hardware must support lock-free atomics on 64-bit variables");

public:
    /**
     * @brief Forward of SlotStorage, so the user gets the required buffer size.
     */
    using SlotStorage = typename Slot::SlotStorage;

    explicit Queue() noexcept : head_and_free_cnt_({0, N}), tail_and_read_cnt_({0, 0})
    {
        static_assert(sizeof(Queue) % cacheLineSize == 0,
                      "Queue size must be a multiple of cache line size to "
                      "prevent false sharing between adjacent queues");
        static_assert(offsetof(Queue, tail_and_read_cnt_) - offsetof(Queue, head_and_free_cnt_)
                          == static_cast<std::ptrdiff_t>(cacheLineSize),
                      "Head and tail must be a cache line apart to prevent false sharing");
        // First turn must be initialized with something different from 0,
        // otherwise it looks like it already provides a value.
        slots_[0].turn.store(1, std::memory_order_relaxed);
    }

    ~Queue() noexcept = default;

    /* @brief Copy and move is not allowed. */
    Queue(const Queue&) = delete;
    Queue& operator=(const Queue&) = delete;

    /** @brief Try to emplace an item. */
    template<typename T, typename... Args>
    ReturnVal try_emplace(Args&&... args) noexcept
    {
        static_assert(std::is_nothrow_constructible<T, Args&&...>::value,
                      "T must be nothrow constructible with Args&&...");
        // TODO: Tuple used not to be trivially copyable, seems to be fixed now?
        static_assert(std::is_trivially_copyable<T>::value, "T must be trivially copyable");
        static_assert(std::is_trivially_destructible<T>::value, "T must be trivially destructible");

        auto head_and_free_cnt = head_and_free_cnt_.load(std::memory_order_relaxed);
        do
        {
            if (EXPECT_UNLIKELY(!head_and_free_cnt.check()))
            {
                return ReturnVal::kQueueStateCorrupt;
            }
            if (EXPECT_UNLIKELY(head_and_free_cnt.cnt() == 0))
            {
                return ReturnVal::kQueueFull;
            }
        } while (!head_and_free_cnt_.compare_exchange_weak(head_and_free_cnt,
                                                           head_and_free_cnt.next_head(),
                                                           std::memory_order_acq_rel,
                                                           std::memory_order_relaxed));

        auto& slot = slots_[idx(head_and_free_cnt.seq())];
        slot.template construct<T>(std::forward<Args>(args)...);
        // We need release to make sure the slot is tagged written
        // only after it is fully constructed.
        slot.turn.store(head_and_free_cnt.seq(), std::memory_order_release);
        return ReturnVal::kOk;
    }

    template<typename T>
    inline ReturnVal try_push(const T& v) noexcept
    {
        return try_emplace<T>(v);
    }

    /** @brief Pop from the queue, return false if queue is empty. */
    template<typename T>
    inline ReturnVal try_pop(T& v) noexcept
    {
        auto tail_and_read_cnt = tail_and_read_cnt_.load(std::memory_order_relaxed);

        auto& slot = slots_[idx(tail_and_read_cnt.seq())];
        auto turn  = slot.turn.load(std::memory_order_acquire);
        if (EXPECT_UNLIKELY(!tail_and_read_cnt.check() || !turn.check()))
        {
            return ReturnVal::kQueueStateCorrupt;
        }

        ReturnVal ret = ReturnVal::kOk;
        if (EXPECT_LIKELY(turn.get() == tail_and_read_cnt.seq()))
        {
            if (EXPECT_UNLIKELY(!slot.copy(v)))
            {
                ret = ReturnVal::kQueuePayloadCorrupt;
            }

            auto next_tail = tail_and_read_cnt.next_tail();
            if (EXPECT_UNLIKELY(next_tail.cnt() == N / 4))
            {
                next_tail.dec_read_cnt(N / 4);
                auto head_and_free_cnt = head_and_free_cnt_.load(std::memory_order_relaxed);
                do
                {
                    if (EXPECT_UNLIKELY(!head_and_free_cnt.check()))
                    {
                        return ReturnVal::kQueueStateCorrupt;
                    }
                } while (!head_and_free_cnt_.compare_exchange_weak(head_and_free_cnt,
                                                                   head_and_free_cnt.inc_free_cnt(N / 4),
                                                                   std::memory_order_acq_rel,
                                                                   std::memory_order_relaxed));
            }
            tail_and_read_cnt_.store(next_tail, std::memory_order_relaxed);
            return ret;
        }
        else
        {
            return ReturnVal::kQueueEmpty;
        }
    }

    /**
     * @brief Peek into the queue's tail.
     *
     * Checks the tail and returns a pointer to its slot, if
     * there is something in the queue.
     *
     * Otherwise returns ReturnVal::kQueueEmpty.
     *
     * @remark
     * Can only be used if the queue's content can be trusted, since
     * this method does not apply E2E protection!
     */
    template<typename T>
    inline ReturnVal try_peek(T*& v) noexcept
    {
        auto tail_and_read_cnt = tail_and_read_cnt_.load(std::memory_order_relaxed);

        auto& slot = slots_[idx(tail_and_read_cnt.seq())];
        auto turn  = slot.turn.load(std::memory_order_acquire);
        if (EXPECT_UNLIKELY(!tail_and_read_cnt.check() || !turn.check()))
        {
            return ReturnVal::kQueueStateCorrupt;
        }

        if (EXPECT_LIKELY(turn.get() == tail_and_read_cnt.seq()))
        {
            v = reinterpret_cast<T*>(&slot.storage);
            return ReturnVal::kOk;
        }
        return ReturnVal::kQueueEmpty;
    }

    /**
     * @brief Pop a value without further looking at it.
     *
     * Designed to be used together with try_peek, in case the tail's slot has
     * already been processed.
     */
    inline ReturnVal try_pop()
    {
        ReturnVal ret          = ReturnVal::kOk;
        auto tail_and_read_cnt = tail_and_read_cnt_.load(std::memory_order_relaxed);

        auto next_tail = tail_and_read_cnt.next_tail();
        if (EXPECT_UNLIKELY(next_tail.cnt() == N / 4))
        {
            next_tail.dec_read_cnt(N / 4);
            auto head_and_free_cnt = head_and_free_cnt_.load(std::memory_order_relaxed);
            do
            {
                if (EXPECT_UNLIKELY(!head_and_free_cnt.check()))
                {
                    return ReturnVal::kQueueStateCorrupt;
                }
            } while (!head_and_free_cnt_.compare_exchange_weak(head_and_free_cnt,
                                                               head_and_free_cnt.inc_free_cnt(N / 4),
                                                               std::memory_order_acq_rel,
                                                               std::memory_order_relaxed));
        }
        tail_and_read_cnt_.store(next_tail, std::memory_order_relaxed);
        return ret;
    }

    /** @brief PayloadProtection forwarding for the listener. */
    static constexpr e2e::E2EProtection GetPayloadProtection()
    {
        return PayloadProtection;
    }

private:
    constexpr size_t idx(size_t i) const noexcept
    {
        return i % N;
    }

private:
    /** @brief The slots for the payloads. */
    internal::Slot<NMaxPayload, QueueStateProtection, PayloadProtection> slots_[N];
    /** @brief Head sequence and no. of free slots. */
    alignas(cacheLineSize) std::atomic<SeqAndCnt<QueueStateProtection>> head_and_free_cnt_;
    /** @brief Tail sequence and no. of (temporary) read slots. */
    alignas(cacheLineSize) std::atomic<SeqAndCnt<QueueStateProtection>> tail_and_read_cnt_;
};

} // namespace pimp
} // namespace pipc

#endif // PIMP_BUFFER_HPP
