#ifndef PIPC_SLOT_WITH_SEQ_CNT_HPP
#define PIPC_SLOT_WITH_SEQ_CNT_HPP

#include "pipc/utils/CacheLineSize.hpp"

#include <atomic>
#include <memory>
#include <new> // std::hardware_destructive_interference_size

namespace pipc
{
/**
 * @brief Slot with a sequence counter.
 *
 * TODO:
 * Rename & move somewhere else.
 */
template<typename T, bool CacheAligned = true>
struct SlotWithSeqCnt
{
    SlotWithSeqCnt() noexcept : turn(0)
    {
    }

    ~SlotWithSeqCnt() noexcept
    {
        // Destroy if an element is still present
        if (turn & 1)
        {
            destroy();
        }
    }

    template<typename... Args>
    void construct(Args&&... args) noexcept
    {
        static_assert(std::is_nothrow_constructible<T, Args&&...>::value,
                      "T must be nothrow constructible with Args&&...");
        new (&storage) T(std::forward<Args>(args)...);
    }

    void destroy() noexcept
    {
        static_assert(std::is_nothrow_destructible<T>::value, "T must be nothrow destructible");
        reinterpret_cast<T*>(&storage)->~T();
    }

    T&& move() noexcept
    {
        return reinterpret_cast<T&&>(storage);
    }

    alignas(utils::GetAlignment<size_t, CacheAligned>()) std::atomic<size_t> turn;
    typename std::aligned_storage<sizeof(T), alignof(T)>::type storage;
};

} // namespace pipc

#endif // PIPC_SLOT_WITH_SEQ_CNT_HPP
