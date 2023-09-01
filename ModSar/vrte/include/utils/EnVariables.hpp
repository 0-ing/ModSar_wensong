//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file      EnVariables.hpp
/// @brief     Environment Variables Interface
/// @copyright Robert Bosch GmbH  2018
/// @author

#ifndef ENVARIABLES_HPP_INCLUDED
#define ENVARIABLES_HPP_INCLUDED

namespace exm
{
namespace utils
{
/* Environment Variable */

/// @brief Definition of the environment variable name of execution client
static constexpr const char* EXE_CLIENT_ENV_VAR = "EXE_CLIENT";

/// @brief Definition of the environment variable name of execution client
static constexpr const char* EXE_CLIENT_R_ENV_VAR = "EXE_CLIENT_R";

/// @brief Definition of the environment variable name of the executable version
static constexpr const char* EXECUTABLE_VERSION_ENV_VAR = "EXECUTABLE_VERSION";

/// @brief Definition of the environment variable name of the ProcessIdentifier
static constexpr const char* PROCESS_IDENTIFIER_ENV_VAR = "PROCESSIDENTIFIER";

/// @brief Definition of the environment variable name of the LogTraceDefaultLogLevel
static constexpr const char* LOGTRACE_DEFAULTLOGLEVEL_ENV_VAR = "LOGTRACEDEFAULTLOGLEVEL";

/// @brief Definition of the environment variable name of the LogTraceFilePath
static constexpr const char* LOGTRACE_FILEPATH_ENV_VAR = "LOGTRACEFILEPATH";

/// @brief Definition of the environment variable name of the LogTraceFilePath
static constexpr const char* LOGTRACE_FILESIZE_ENV_VAR = "LOGTRACEFILESIZE";

/// @brief Definition of the environment variable name of the LogTraceLogMode
static constexpr const char* LOGTRACE_LOGMODE_ENV_VAR = "LOGTRACELOGMODE";

/// @brief Definition of the environment variable name of the LogTraceProcessId
static constexpr const char* LOGTRACE_PROCESSID_ENV_VAR = "LOGTRACEPROCESSID";

/// @brief Definition of the environment variable name of the LogTraceProcessDesc
static constexpr const char* LOGTRACE_PROCESSDESC_ENV_VAR = "LOGTRACEPROCESSDESC";

/// @brief Definition of the environment variable name to exchange file descriptors.
static constexpr const char* CLIENT_RECEIVE_PIPE_ENV_VAR = "FGC_RX";
/// @brief Definition of the environment variable name to exchange file descriptors.
static constexpr const char* CLIENT_SEND_PIPE_ENV_VAR = "FGC_TX";
} // namespace utils
} // namespace exm
#endif
