//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file      AppInstStatus.hpp
/// @brief     Type Definition: AppInstStatus
/// @copyright Robert Bosch GmbH  2018
/// @author    Christopher Schwager

#ifndef UTILS_IAPPINSTSTATUS_HPP_INCLUDED
#define UTILS_IAPPINSTSTATUS_HPP_INCLUDED

#include <stdint.h>

namespace exm
{
/// @brief   Representation of an Application Instance Status

enum class AppInstStatus : int8_t
{
    CANCELLED = -2, ///< Request cancelled
    ERROR = -1,     ///< Error encountered
    RUNNING = 0,    ///< Application Instance is running
    TERMINATED = 1  ///< Application Instance was terminated
};
} /* namespace exm */

#endif
