#ifndef COM_UTILS_PLACEHOLDER_HPP
#define COM_UTILS_PLACEHOLDER_HPP

namespace com
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
} // namespace com

#endif // COM_UTILS_PLACEHOLDER_HPP
