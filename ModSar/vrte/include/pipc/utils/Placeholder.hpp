#ifndef PIPC_UTILS_PLACEHOLER_HPP
#define PIPC_UTILS_PLACEHOLER_HPP

namespace pipc
{
namespace utils
{
/** @brief Empty placeholder. */
struct Placeholder
{
    /** @brief Equal operator (used mainly for testing). */
    constexpr bool operator==(const Placeholder&) const
    {
        return true;
    }
};

} // namespace utils
} // namespace pipc

#endif // PIPC_UTILS_PLACEHOLER_HPP
