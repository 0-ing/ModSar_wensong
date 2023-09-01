#ifndef TRUSTED_HPP
#define TRUSTED_HPP

namespace pipc
{
namespace e2e
{
/**
 * @brief Enum which selects the type of E2E protection.
 *
 * This enum is used in combination with storage wrappers for
 * enabling mechanisms like inverse redundant storage.
 */
enum class E2EProtection
{
    kNone = 0,
    kInverse
};

} // namespace e2e
} // namespace pipc

#endif // TRUSTED_HPP
