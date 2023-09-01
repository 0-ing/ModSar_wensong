#ifndef PIPC_UTILS_ERROR_TYPE_HPP
#define PIPC_UTILS_ERROR_TYPE_HPP

#include <stdint.h>

namespace pipc
{
namespace utils
{
/** @brief Types of errors. */
enum class ErrorType : uint8_t
{
    kGeneral = 0,
    kPosix
};

} // namespace utils
} // namespace pipc

#endif // PIPC_UTILS_ERROR_TYPE_HPP
