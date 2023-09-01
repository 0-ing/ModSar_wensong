//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2017 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file      InstanceState.hpp
/// @brief     Definitions of Instance States
/// @copyright Robert Bosch GmbH  2017
/// @author


#ifndef _INSTANCE_STATE_HPP_INCLUDED
#define _INSTANCE_STATE_HPP_INCLUDED

#include <stdint.h>

namespace exm
{
namespace ldr
{
    /// @brief Instance state
    enum class InstanceState : uint8_t
    {
        EMPTY=0,                                                        ///< @brief default state of an instance
        INSTALLING,                                                     ///< @brief instance is getting registered with ExM
        INSTALLED,                                                      ///< @brief instance is registered and ready to be started
        PREVIOUSLY_REMOVED,                                             ///< @brief instance was previously uninstalled
        ERROR                                                           ///< @brief An error has occurred
    };

    /// @brief Possible errors causing an application ERROR state
    enum class ErrorCodeInstance : uint8_t
    {
        ERROR_NONE = 0,
        ERROR_APP_NOT_AVAILABLE,    ///< @brief The application is not available
        ERROR_INSTALLED,        ///< @brief Error when installing
        ERROR_EXIT_FAILURE,    ///< @brief The application was exited with a value different than 0 or by another signal than SIGTERM. The 'data' member of the ErrorContext class points to the 'status' returned by waitpid().
        ERROR_REPORTING_EXIT_SET_USER,                                   ///< @brief Error while setting user
        ERROR_NO_DB_ALLOC,      ///< @brief Instance not allocated inside Database array
    };                         
} /* namespace mfe */
} /* namespace exm */

#endif
