//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
/// @copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================
/// @file      Log.hpp
/// @brief     Main Log header
/// @author    Arnaud Riess
//=============================================================================
#ifndef LOG_LOG_HPP_INCLUDED
#define LOG_LOG_HPP_INCLUDED

#include "utils/c/stdio.hpp"       //wrapper to prevent direct inclusion of libc headers
#include "utils/c/string.hpp"      //wrapper to prevent direct inclusion of libc headers
#include "utils/StdReturnType.hpp"
#include "utils/AppInstId.hpp"
#include "utils/FuncGroupId.hpp"
#include "utils/FuncGroupStateId.hpp"

#include "log/SeverityLevel.hpp"

namespace exm
{
namespace log
{

/// @brief App Logger wrapper function.
/// @param[in] severity          Severity level of  error.
/// @param[in] AppInsId          Instance ID of the application.
/// @param[in] format            Format string for the variable number of argument passed.
/// @param[in] ...               Variable number of arguments.
void AppLog(const Severity severity, const AppInstId appId, const char* const format, ... ); // PRQA S 2012 #... used for additional/variable number of arguments for sending out debug info

/// @brief Function Group Logger wrapper function.
/// @param[in] severity          Severity level of  error.
/// @param[in] funcGroupId       Function group ID the application.
/// @param[in] funcGroupState    Function group state ID the application.
/// @param[in] format            Format string for the variable number of argument passed.
/// @param[in] ...               Variable number of arguments.
void FunGroupLog(const Severity severity, const FuncGroupId funcGroupId, const FuncGroupStateId funcGroupStateId, const char* const format, ... ); // PRQA S 2012 #... used for additional/variable number of arguments for sending out debug info

/// @brief Generic Logger wrapper function.
/// @param[in] severity          Severity level of  error.
/// @param[in] format            Format string for the variable number of argument passed.
/// @param[in] ...               Variable number of arguments.
void Log(const Severity severity, const char* const format, ... ); // PRQA S 2012 #... used for additional/variable number of arguments for sending out debug info

/// @brief Locks the logging internal mutex
StdReturnType LockLogger();

/// @brief Unlocks the logging internal mutex
StdReturnType UnlockLogger();

}  // namespace log
}  // namespace exm

#endif

