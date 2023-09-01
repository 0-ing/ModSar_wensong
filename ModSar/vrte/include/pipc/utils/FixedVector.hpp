#ifndef UTILS_FIXED_VECTOR_HPP
#define UTILS_FIXED_VECTOR_HPP

#include <vector>

namespace pipc
{
namespace utils
{
/**
 * @brief Vector with fixed size capacity.
 *
 * @remark
 * We cannot use the VFC fixed vector implementation as of now, because it
 * supports neither emplacing nor move semantics.
 *
 * For example:
 * If we try to erase an element from a vector with elements, which are not
 * copy-assignable, the code will fail!
 *
 */
template<typename T, size_t N>
using FixedVector = std::vector<T>;

} // namespace utils
} // namespace pipc

#endif // UTILS_FIXED_VECTOR_HPP
