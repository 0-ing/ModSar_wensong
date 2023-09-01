#ifndef UTILS_FUNCTION_HPP
#define UTILS_FUNCTION_HPP

#include <functional>

namespace pipc
{
namespace utils
{
/**
 * @brief Function with similar behavior to std::function
 *
 * TODO:
 * Not sure if there is already something fitting available.
 * If there is, we can change this wrapper accordingly.
 * In most cases we can get around std::function by using a struct
 * similar to transport::DispatchEntry.
 */
template<typename T>
using Function = std::function<T>;

} // namespace utils
} // namespace pipc

#endif // UTILS_FUNCTION_HPP
