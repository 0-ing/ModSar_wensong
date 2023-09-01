#ifndef TYPE_WRAPPER_HPP
#define TYPE_WRAPPER_HPP

#include "Trusted.hpp"
#include "internal/TypeInverseProtected.hpp"
#include "internal/TypeUnprotected.hpp"

namespace pipc
{
namespace e2e
{
/**
 * @brief Wrapper to select a trusted or untrusted general type.
 *
 * Trusted means the type is used as-is, while untrusted
 * protects it via inverse redundant storage.
 */
template<typename T, E2EProtection T2, typename T3 = void>
struct TypeWrapper;

template<typename T>
struct TypeWrapper<T, E2EProtection::kNone>
{
    using type = TypeUnprotected<T>;
};

template<typename T>
struct TypeWrapper<T, E2EProtection::kInverse>
{
    using type = TypeInverseProtected<T>;
};

} // namespace e2e
} // namespace pipc

#endif // TYPE_WRAPPER_HPP
