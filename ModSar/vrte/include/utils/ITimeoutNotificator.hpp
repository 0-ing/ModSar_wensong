//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file      ITimeoutNotificator.hpp
/// @brief     Timeout Notification Interface
/// @copyright Robert Bosch GmbH  2018
/// @author

#ifndef UTILS_ITIMEOUTNOTIFICATOR_HPP_INCLUDED
#define UTILS_ITIMEOUTNOTIFICATOR_HPP_INCLUDED

namespace exm
{
namespace utils
{

/// @class   ITimeoutNotificator
/// @brief   Interface to Timeout Notificator
class ITimeoutNotificator
{
public:
    /// @brief Destructor
    virtual ~ITimeoutNotificator(){}; // Not covered: Deleting destructors of pure virtual base
                                      // classes can not be called.
    /// @brief Constructor
    ITimeoutNotificator(){};

    /// @brief TimeoutNotification
    /// @param[in]  userData      Pointer to user data
    /// @return  void
    virtual void TimeoutNotification(void* userData) = 0;

}; /* class ITimeoutNotificator */
} /* namespace utils */
} /* namespace exm */
#endif
