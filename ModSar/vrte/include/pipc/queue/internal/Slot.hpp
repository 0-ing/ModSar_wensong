#ifndef PIPC_SLOT_HPP
#define PIPC_SLOT_HPP

#include "pipc/utils/CacheLineSize.hpp"

#include <atomic>
#include <memory>
#include <new> // std::hardware_destructive_interference_size

namespace pipc
{
/**
 * @brief Slot without a sequence counter.
 *
 * TODO:
 * Rename & move somewhere else.
 */
template<typename T, bool CacheAligned = true>
struct Slot
{
    template<typename... Args>
    inline void construct(Args&&... args) noexcept
    {
        new (&storage) T(std::forward<Args>(args)...);
    }

    void destroy() noexcept
    {
        reinterpret_cast<T*>(&storage)->~T();
    }

    inline T&& move() noexcept
    {
        return reinterpret_cast<T&&>(storage);
    }

    alignas(utils::GetAlignment<T, CacheAligned>()) typename std::aligned_storage<sizeof(T), alignof(T)>::type storage;
};

} // namespace pipc

#endif // PIPC_SLOT_HPP
