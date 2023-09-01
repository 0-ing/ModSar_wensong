#ifndef UTILS_VECTOR_HPP
#define UTILS_VECTOR_HPP

#include <vector>

namespace pipc
{
namespace utils
{
/**
 * @brief Vector with variable size capacity.
 *
 * @remark
 * We cannot use the VFC vector implementation as of now, because it
 * supports neither emplacing nor move semantics.
 *
 * For example:
 * If we try to erase an element from a vector with elements, which are not
 * copy-assignable, the code will fail!
 *
 */
template<typename T>
using Vector = std::vector<T>;

} // namespace utils
} // namespace pipc

#endif // UTILS_VECTOR_HPP
