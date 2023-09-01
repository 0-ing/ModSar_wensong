/// @copyright : 2022 Robert Bosch GmbH. All rights reserved.

#ifndef PIPC_UTILS_PERMISSION_HPP
#define PIPC_UTILS_PERMISSION_HPP

#include <cstddef>
#include <cstdint>

namespace pipc
{
namespace utils
{
/**
 * @brief Permission.
 *
 * Used whenever access permissions need to be defined.
 */
enum class Permission : uint8_t
{
    kNone      = 0,
    kRead      = 1, /**< Read permission */
    kWrite     = 2, /**< Write permission */
    kReadWrite = 3  /**< Read & Write permission */
};

/**
 * @brief Or operator.
 */
inline Permission operator|(Permission a, Permission b)
{
    return static_cast<Permission>(static_cast<size_t>(a) | static_cast<size_t>(b));
}

/** @brief And operator. */
inline Permission operator&(Permission a, Permission b)
{
    return static_cast<Permission>(static_cast<size_t>(a) & static_cast<size_t>(b));
}

/** @brief Or-assign operator. */
inline Permission& operator|=(Permission& a, Permission b)
{
    return a = a | b;
}

} // namespace utils
} // namespace pipc

#endif // PIPC_UTILS_PERMISSION_HPP
