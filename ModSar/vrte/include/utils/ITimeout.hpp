//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file      ITimeout.hpp
/// @brief     Timeout Interface
/// @copyright Robert Bosch GmbH  2018
/// @author

#ifndef UTILS_ITIMEOUT_HPP_INCLUDED
#define UTILS_ITIMEOUT_HPP_INCLUDED

#include "utils/ITimeoutNotificator.hpp"
#include "utils/StdReturnType.hpp"
#include <stdint.h>

namespace exm
{
namespace utils
{

/// @class   ITimeout
/// @brief   Interface to Timeout functionality
class ITimeout
{
public:
    /// @brief Destructor
    virtual ~ITimeout() {
    } // Not covered: Deleting destructors of pure virtual base classes can not be called.
      /// @brief Constructor
    ITimeout() {}

    /// @brief Start a timeout
    /// @param[in]  timeoutMs              Timeout in ms
    /// @param[in]  notification           Timout notificator
    /// @param[in]  userData               Pointer to userdata that will be passed to the
    /// notificator if the timeout fires.
    /// @return  StdReturnType
    /// @retval  OK              OK
    /// @retval  FATAL_ERROR     An unexpected error occurred.
    /// @retval  GENERAL_ERROR   Not possible to start this timeout object, because it is already
    /// started.
    virtual StdReturnType
    Start(uint32_t timeoutMs, ITimeoutNotificator& notification, void* userData)
        = 0;

    /// @brief Cancel a timeout
    /// @return  StdReturnType
    /// @retval  OK              OK
    /// @retval  FATAL_ERROR     An unexpected error occurred.
    /// @retval  GENERAL_ERROR   Not possible to cancel this timeout object, because it is already
    /// cancelled.
    virtual StdReturnType Cancel() = 0;

}; /* class ITimeout */
} /* namespace utils */
} /* namespace exm */
#endif
