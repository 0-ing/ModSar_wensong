//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2019 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file        IMutex.hpp
/// @brief       Interface for Mutex
/// @copyright   Robert Bosch GmbH 2019
/// @author      Yohan Pistor

#ifndef UTILS_IMUTEX_HPP_
#define UTILS_IMUTEX_HPP_

#include "utils/StdReturnType.hpp"

namespace exm
{
namespace utils
{
///@brief Interface for Mutex
class IMutex
{
public:
    /// Lock the Mutex
    ///
    /// @return StdReturnType
    /// @retval  OK = success
    /// @retval  GENERAL_ERROR = failed
    virtual StdReturnType Lock() = 0;

    /// Try to lock the Mutex
    /// Returns an error if mutex is already locked.
    ///
    /// @return StdReturnType
    /// @retval  OK = success
    /// @retval  GENERAL_ERROR = failed
    /// @retval  INVALID_STATE = mutex is already locked
    virtual StdReturnType TryLock() = 0;

    /// Unlock the Mutex
    ///
    /// @return StdReturnType
    /// @retval  OK = success
    /// @retval  GENERAL_ERROR = failed
    virtual StdReturnType Unlock() = 0;

    /// @brief      destructor
    virtual ~IMutex() {
    } // Not covered: Deleting destructors of pure virtual base classes can not be called.
};
}
}

#endif // _IMUTEX_HPP_
