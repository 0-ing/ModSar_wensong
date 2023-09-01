//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file      ITimeoutServer.hpp
/// @brief     Timeout server Interface
/// @copyright Robert Bosch GmbH  2018
/// @author

#ifndef UTILS_ITIMEOUTSERVER_HPP_INCLUDED
#define UTILS_ITIMEOUTSERVER_HPP_INCLUDED

#include "utils/ITimeout.hpp"

namespace exm
{
namespace utils
{

/// @class   ITimeoutServer
/// @brief   Interface to Time monitoring Sever

class ITimeoutServer
{
public:
    /// @brief Destructor
    virtual ~ITimeoutServer(){}; // Not covered: Deleting destructors of pure virtual base classes
                                 // can not be called.

    /// @brief Get a new ITimeout object.
    /// @param[out] timeOut ITimeout object. This object is recycable.
    /// @return  StdReturnType
    /// @retval  OK              OK
    /// @retval  GENERAL_ERROR   Error occurred
    virtual StdReturnType GetNew(ITimeout** timeOut) = 0;

    virtual StdReturnType Start() = 0;
    virtual StdReturnType Join() = 0;
    virtual StdReturnType cancel() = 0;

}; /* class ITimeoutServer */
} /* namespace utils */
} /* namespace exm */
#endif
