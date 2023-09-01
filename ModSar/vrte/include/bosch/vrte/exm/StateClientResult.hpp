//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================
//
/// @file      StateClientResult.hpp
/// @brief     Collection of results of a "Get State" or "Set State" request for the caller
/// @copyright Robert Bosch GmbH  2018
/// @author    Bastian Baetz
//=============================================================================

#ifndef _STATECLIENTRESULT_HPP_INCLUDED
#define _STATECLIENTRESULT_HPP_INCLUDED

#include <stdint.h>

namespace bosch
{
namespace vrte
{
namespace exm
{
    /// @brief Collection of results of a "Get State" or "Set State" request for the caller.
    enum StateClientResult
        : uint32_t
        {
            OK = 0,             ///< Request successfully dispatched or completed.
        CANCELLED,              ///< The SetState request was cancelled by a newer request.
        FAILED,                 ///< SetState transition failed, e.g. due to an application failing to start.
        TIMEOUT,                ///< A request could not be performed in the internally or externally defined time interval.
        INVALID_ARGUMENTS,      ///< One or more arguments are invalid or do not exist.
        INVALID_MESSAGE,        ///< Something failed during reception of a request message.
        INSUFFICIENT_RESOURCES, ///< Not enough resources to execute the call.
        IN_TRANSITION,          ///< The GetState request cannot be performed as the Function Group is in transition.
        CHANNEL_ERROR,          ///< Sending the IPC message failed.
        IN_ERROR_STATE,         ///< The Function Group is in an error state, i.e. a previous transition failed.
        INVALID_TRANSITION,     ///< The requested transition is invalid(MachineFG to Off)
        STARTING_PROCESS_FAILED ///< The requested transition failed because one or more processes that should've start, ended in error
    };
}  //namespace exm
}  //namespace vrte
}  //namespace bosch

#endif // _STATECLIENTRESULT_HPP_INCLUDED
