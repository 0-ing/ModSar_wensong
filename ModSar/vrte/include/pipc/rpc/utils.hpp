#ifndef PIPC_RPC_UTILS_HPP
#define PIPC_RPC_UTILS_HPP

#include <tuple>

namespace pipc
{
namespace rpc
{
template<class F, size_t... Is>
constexpr auto index_apply_impl(F f, std::index_sequence<Is...>)
{
    return f(std::integral_constant<size_t, Is>{}...);
}

template<size_t N, class F>
constexpr auto index_apply(F f)
{
    return index_apply_impl(f, std::make_index_sequence<N>{});
}

template<class Tuple, class F>
constexpr auto apply(F f, Tuple t)
{
    return index_apply<std::tuple_size<Tuple>{}>([&](auto... Is) { return f(std::get<Is>(t)...); });
}

} // namespace rpc
} // namespace pipc

#endif // PIPC_RPC_UTILS_HPP
