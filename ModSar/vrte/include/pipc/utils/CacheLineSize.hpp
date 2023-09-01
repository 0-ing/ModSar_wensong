#ifndef CACHE_LINE_SIZE_HPP
#define CACHE_LINE_SIZE_HPP

#include <cstddef>

namespace pipc
{
/** @brief Definition of the required size if we want variables to be
 * cache-aligned. */
#ifdef __cpp_lib_hardware_interference_size
static constexpr size_t cacheLineSize = std::hardware_destructive_interference_size;
#else
static constexpr size_t cacheLineSize = 64;
#endif

namespace utils
{
/**
 * @brief Return the required alignment of a type.
 *
 * Returns either the natural alignment of a given type, or
 * an increased alignment in case cache line alignment is desired.
 */
template<typename T, bool CacheAligned>
constexpr static size_t GetAlignment()
{
    if (CacheAligned)
    {
        return ((alignof(T) < cacheLineSize) ? cacheLineSize : alignof(T));
    }
    else
    {
        return alignof(T);
    }
}

} // namespace utils
} // namespace pipc

#endif // CACHE_LINE_SIZE_HPP
