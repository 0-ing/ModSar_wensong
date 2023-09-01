#ifndef COM_UTILS_HASH_FNV_1A_HPP
#define COM_UTILS_HASH_FNV_1A_HPP

#include <cstdint>

namespace com
{
namespace utils
{
/**
 * @brief Function to hash a C string using FNV algorithm variant 1A.
 *
 * @param str Null terminated C string
 * @return uint32_t Hashed value
 */
static inline uint32_t HashFnv1a32(const char* str)
{
    const uint32_t prime = 0x01000193;
    uint32_t hash        = 0x811c9dc5;

    while (*str != 0)
    {
        hash ^= *str++;
        hash *= prime;
    }
    return hash;
}

/**
 * @brief Function to hash a C string using FNV algorithm variant 1A.
 *
 * @param str Null terminated C string
 * @return uint64_t Hashed value
 */
static inline uint64_t HashFnv1a64(const char* str)
{
    const uint64_t prime = 0x00000100000001B3;
    uint64_t hash        = 0xcbf29ce484222325;

    while (*str != 0)
    {
        hash ^= *str++;
        hash *= prime;
    }
    return hash;
}

} // namespace utils
} // namespace com

#endif // COM_UTILS_HASH_FNV_1A_HPP
