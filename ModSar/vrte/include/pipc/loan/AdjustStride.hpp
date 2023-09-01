/// @copyright : 2022 Robert Bosch GmbH. All rights reserved.
#ifndef PIPC_LOAN_ADJUST_STRIDE_HPP
#define PIPC_LOAN_ADJUST_STRIDE_HPP

#include "pipc/Logger.hpp"
#include "pipc/utils/String.hpp"

namespace pipc
{
namespace loan
{
/**
 * @brief Return the required stride of a type with sizeof(T)=size and alignof(T)=align.
 *
 * Returns a stride that is aligned to the alignment requirement of a given type T
 * If stride needs to be altered, a log message is printed with context string to indicate that stride
 * was changed by the respective class depicted by the context string
 */
template<typename T>
inline static size_t adjustStride(size_t stride, const utils::String& context)
{
    if (stride < sizeof(T))
    {
        stride = sizeof(T);
        PIPC_LOG_DEBUG() << context
                         << ": stride is smaller than size of T. It was set to at least sizeof(T)=" << sizeof(T)
                         << std::endl;
    }
    if (stride % alignof(T) != 0)
    {
        stride = ((stride + alignof(T) - 1) / alignof(T)) * alignof(T);
        PIPC_LOG_DEBUG() << context
                         << ": stride is not multiple of alignment requirement of T. It was set to the next "
                            "higher multipe of alignof(T)="
                         << stride << std::endl;
    }
    return stride;
}

/**
 * @brief Return the required stride of a type with sizeof(T)=size and alignof(T)=align.
 *
 * Returns a stride that is aligned to the alignment requirement of a given type T
 */
template<typename T>
inline static size_t calcStride()
{
    return ((sizeof(T) + alignof(T) - 1) / alignof(T)) * alignof(T);
}

} // namespace loan
} // namespace pipc

#endif // PIPC_LOAN_ADJUST_STRIDE_HPP
