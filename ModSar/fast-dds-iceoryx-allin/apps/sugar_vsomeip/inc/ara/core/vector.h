//==============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
/// @copyright (c) 2021-2022 by Robert Bosch GmbH. All rights reserved.
//
// The reproduction, distribution and utilization of this file as
// well as the communication of its contents to others without express
// authorization is prohibited. Offenders will be held liable for the
// payment of damages. All rights reserved in the event of the grant
// of a patent, utility model or design.
//==============================================================================

/// @file vector.h
/// @brief Interface to class ara::core::Vector
//==============================================================================

#ifndef ARA_CORE_VECTOR_H_
#define ARA_CORE_VECTOR_H_

#include <vector>
#include <memory>
#include <type_traits>
#include <utility>

namespace ara {
namespace core {

/// @defgroup araCoreVector
/// @{
/// @brief A sequence container that encapsulates dynamically sized arrays
///
/// @tparam T  the type of contained values
/// @tparam Allocator  the type of Allocator to use for this container
///
/// @traceid{SWS_CORE_01301}
///
template <typename T, typename Allocator = std::allocator<T>>
using Vector = std::vector<T, Allocator>;

/// @brief Global operator== for Vector instances
///
/// @traceid{SWS_CORE_01390}
///
template <typename T,
          typename Allocator,
          typename
          = typename std::enable_if<!std::is_same<Vector<T, Allocator>, std::vector<T, Allocator>>::value>::type>
inline bool operator==(Vector<T, Allocator> const& lhs, Vector<T, Allocator> const& rhs) {
    return std::operator==(lhs, rhs);
}

/// @brief Global operator!= for Vector instances
///
/// @traceid{SWS_CORE_01391}
///
template <typename T,
          typename Allocator,
          typename
          = typename std::enable_if<!std::is_same<Vector<T, Allocator>, std::vector<T, Allocator>>::value>::type>
inline bool operator!=(Vector<T, Allocator> const& lhs, Vector<T, Allocator> const& rhs) {
    return std::operator!=(lhs, rhs);
}

/// @brief Global operator< for Vector instances
///
/// @traceid{SWS_CORE_01392}
///
template <typename T,
          typename Allocator,
          typename
          = typename std::enable_if<!std::is_same<Vector<T, Allocator>, std::vector<T, Allocator>>::value>::type>
inline bool operator<(Vector<T, Allocator> const& lhs, Vector<T, Allocator> const& rhs) {
    return std::operator<(lhs, rhs);
}

/// @brief Global operator<= for Vector instances
///
/// @traceid{SWS_CORE_01393}
///
template <typename T,
          typename Allocator,
          typename
          = typename std::enable_if<!std::is_same<Vector<T, Allocator>, std::vector<T, Allocator>>::value>::type>
inline bool operator<=(Vector<T, Allocator> const& lhs, Vector<T, Allocator> const& rhs) {
    return std::operator<=(lhs, rhs);
}

/// @brief Global operator> for Vector instances
///
/// @traceid{SWS_CORE_01394}
///
template <typename T,
          typename Allocator,
          typename
          = typename std::enable_if<!std::is_same<Vector<T, Allocator>, std::vector<T, Allocator>>::value>::type>
inline bool operator>(Vector<T, Allocator> const& lhs, Vector<T, Allocator> const& rhs) {
    return std::operator>(lhs, rhs);
}

/// @brief Global operator>= for Vector instances
///
/// @traceid{SWS_CORE_01395}
///
template <typename T,
          typename Allocator,
          typename
          = typename std::enable_if<!std::is_same<Vector<T, Allocator>, std::vector<T, Allocator>>::value>::type>
inline bool operator>=(Vector<T, Allocator> const& lhs, Vector<T, Allocator> const& rhs) {
    return std::operator>=(lhs, rhs);
}

/// @brief Add overload of swap for ara::core::Vector
///
/// @note We actually don't need this overload at all, because current implementation is just
/// a type alias and thus can simply use the overload for the std:: type.
/// However, we need this symbol in order to provide uptracing.
///
/// @tparam T  the type of values in the Vectors
/// @tparam Allocator  the Allocator used by the Vectors
/// @param lhs  the first argument of the swap invocation
/// @param rhs  the second argument of the swap invocation
///
/// @traceid{SWS_CORE_01396}
///
template <typename T, typename Allocator>
void swap(Vector<T, Allocator>& lhs, Vector<T, Allocator>& rhs) {
    lhs.swap(rhs);
}

/// }@
} // namespace core
} // namespace ara
#endif // ARA_CORE_VECTOR_H_
