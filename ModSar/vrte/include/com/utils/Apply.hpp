/// @copyright : 2022 Robert Bosch GmbH. All rights reserved.

#ifndef COM_UTILS_APPLY_HPP
#define COM_UTILS_APPLY_HPP

#include <cstddef>
#include <tuple>
#include <type_traits>
#include <utility>

namespace com
{
namespace utils
{
/**
 * @brief Expand an index_sequence and apply the integers to a callable.
 */
template<class F, size_t... Is>
constexpr auto IdxApplyImpl(F&& f, std::index_sequence<Is...>)
{
    return f(std::integral_constant<size_t, Is>{}...);
}

/**
 * @brief Take an arbitrary number and invoke a callable with an index sequence of it.
 *
 * @tparam N
 * @tparam F
 * @param f
 * @return constexpr auto
 */
template<size_t N, class F>
constexpr auto IdxApply(F&& f)
{
    return IdxApplyImpl(f, std::make_index_sequence<N>{});
}

/**
 * @brief Expand the tuple as arguments and invoke a callable with them.
 *
 * @tparam Tuple
 * @tparam F
 * @param f
 * @param t
 * @return constexpr auto
 */
template<class Tuple, class F>
constexpr auto Apply(F&& f, Tuple& t)
{
    return IdxApply<std::tuple_size<Tuple>{}>([&](auto... Is) { return f(std::get<Is>(t)...); });
}

} // namespace utils
} // namespace com

#endif // COM_UTILS_APPLY_HPP
