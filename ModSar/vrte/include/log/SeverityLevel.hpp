//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file      SeverityLevel.hpp
/// @brief     Type Definition: Severity
/// @copyright Robert Bosch GmbH  2018
/// @author    Jyothi Kuntegowda

#ifndef LOG_SEVERITYLEVEL_HPP_INCLUDED
#define LOG_SEVERITYLEVEL_HPP_INCLUDED

#include <stdint.h>

namespace exm
{
/// @brief    Representation of error severity
enum class Severity : uint8_t
{
    DEBUG = 0,     ///<  Debug information
    INFO,          ///<  Generic information
    WARN,          ///<  Debug warning
    ERROR          ///<  Error information
};
} // namespace exm

#endif
