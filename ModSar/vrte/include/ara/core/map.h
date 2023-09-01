//==============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
/// @copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// The reproduction, distribution and utilization of this file as
// well as the communication of its contents to others without express
// authorization is prohibited. Offenders will be held liable for the
// payment of damages. All rights reserved in the event of the grant
// of a patent, utility model or design.
//==============================================================================

/// @file map.h
/// @brief A container which contains key-value pairs with unique keys.
//==============================================================================

#ifndef ARA_CORE_MAP_H_
#define ARA_CORE_MAP_H_

#include <functional>
#include <map>
#include <memory>
#include <type_traits>
#include <utility>

namespace ara {
namespace core {

/**
 * @brief A container that contains key-value pairs with unique keys
 *
 * @tparam Key  the type of keys in this Map
 * @tparam T  the type of values in this Map
 * @tparam Compare  the type of comparison Callable
 * @tparam Allocator  the type of Allocator to use for this container
 *
 * @traceid{SWS_CORE_01400}
 */
template <typename Key,
          typename T,
          typename Compare = std::less<Key>,
          typename Allocator = std::allocator<std::pair<const Key, T>>>
using Map = std::map<Key, T, Compare, Allocator>;

/// @brief Add overload of std::swap for Map.
///
/// @note We actually don't need this overload at all, because our implementation is just
/// a type alias and thus can simply use the overload for the std:: type.
/// However, we need this symbol in order to provide uptracing.
///
/// @tparam Key  the type of keys in the Maps
/// @tparam T  the type of values in the Maps
/// @tparam Compare  the type of comparison Callables in the Maps
/// @tparam Allocator  the type of Allocators in the Maps
/// @param lhs  the first argument of the swap invocation
/// @param rhs  the second argument of the swap invocation
///
/// @traceid{SWS_CORE_01496}
template <typename Key, typename T, typename Compare, typename Allocator>
void swap(Map<Key, T, Compare, Allocator>& lhs, Map<Key, T, Compare, Allocator>& rhs) {
    lhs.swap(rhs);
}

}  // namespace core
}  // namespace ara

#endif  // ARA_CORE_MAP_H_
