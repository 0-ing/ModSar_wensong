#ifndef INTEGRAL_WRAPPER_T
#define INTEGRAL_WRAPPER_T

#include "Trusted.hpp"
#include "internal/IntegralInverseProtected.hpp"
#include "internal/IntegralUnprotected.hpp"

namespace pipc
{
namespace e2e
{
/**
 * @brief Wrapper to select a trusted or untrusted Integral type.
 *
 * Trusted means the integral is used as-is, while untrusted
 * protects it via inverse redundant storage.
 */
template<typename T, E2EProtection T2, typename T3 = void>
struct IntegralWrapper;

template<typename T>
struct IntegralWrapper<T, E2EProtection::kNone>
{
    using type = IntegralUnprotected<T>;
};

template<typename T>
struct IntegralWrapper<T, E2EProtection::kInverse>
{
    using type = IntegralInverseProtected<T>;
};

} // namespace e2e
} // namespace pipc

#endif // INTEGRAL_WRAPPER_T
