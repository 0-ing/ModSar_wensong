//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2020 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file      array.hpp
/// @brief     Utility functions & classes related to array handling
/// @copyright Robert Bosch GmbH 2020
/// @author    crg2fe

#ifndef QNX_EXM_DELIVERABLES_SRC_UTILS_INC_UTILS_ARRAY_HPP_
#define QNX_EXM_DELIVERABLES_SRC_UTILS_INC_UTILS_ARRAY_HPP_

#include <stddef.h>

namespace exm
{
namespace utils
{

/// @brief Return the distance (as in no. of elements) between two pointers of the same type
/// The value returned is unsigned, so it must be clear to the user which one is the 'left-hand'
/// pointer and which is the 'right-hand' pointer
template<typename T>
static inline size_t GetPtrDiffUnsigned(const T* ptrRight, const T* ptrLeft)
{
    return ((reinterpret_cast<size_t>(ptrRight) - reinterpret_cast<size_t>(ptrLeft)) / sizeof(T)); // PRQA S 3044 # Cast from pointer required to get the difference
}

/// @brief Generic array reference
template<typename T>
using array_ref = T(&)[];

/// @brief Transform a pointer into an array reference
/// Useful for handling MISRA warnings about indexing pointers, e.g. when working with older C style APIs
template <typename T>
static inline array_ref<T> PtrToArrayRef(T ptr[])
{
    return reinterpret_cast<array_ref<T>>(*ptr);
}


} // namespace exm
} // namespace utils

#endif // QNX_EXM_DELIVERABLES_SRC_UTILS_INC_UTILS_ARRAY_HPP_