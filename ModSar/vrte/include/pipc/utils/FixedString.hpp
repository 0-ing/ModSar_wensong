#ifndef PIPC_UTILS_FIXED_STRING_HPP
#define PIPC_UTILS_FIXED_STRING_HPP

#include <string>

namespace pipc
{
namespace utils
{
/**
 * @brief String with fixed size capacity.
 *
 * Just a wrapper to std::string for now, can be adjusted later.
 *
 */
template<size_t N>
using FixedString = std::string;

} // namespace utils
} // namespace pipc

#endif // PIPC_UTILS_FIXED_STRING_HPP
