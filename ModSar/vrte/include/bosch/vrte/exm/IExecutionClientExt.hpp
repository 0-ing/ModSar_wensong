//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2019 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================
//
/// @file      IExecutionClientExt.hpp
/// @brief     ExecutionClientExt Interface to ExecutionClientExt
/// @copyright Robert Bosch GmbH  2019
/// @author
//=============================================================================

#ifndef _IEXECUTIONCLIENTEXT_HPP_INCLUDED
#define _IEXECUTIONCLIENTEXT_HPP_INCLUDED

namespace bosch
{
namespace vrte
{
namespace exm
{

/// @brief Interface to ExecutionClientExt class
class IExecutionClientExt
{
public:
    /// @brief Destructor
    virtual ~IExecutionClientExt()
    {
    }

    /// @brief Function to retrieve the executableVersion
    /// @return  const char*        executableVersion. On error, an empty string is returned
    virtual const char* GetExecutableVersion() const = 0;

    /// @brief Function to retrieve the logTraceDefaultLogLevel
    /// @return  const char*        logTraceDefaultLogLevel. On error, an empty string is returned
    virtual const char* GetlogTraceDefaultLogLevel() const = 0;

    /// @brief Function to retrieve the logTraceFilePath
    /// @return  const char*        logTraceFilePath. On error, an empty string is returned
    virtual const char* GetLogTraceFilePath() const = 0;

    /// @brief Function to retrieve the logTraceFileSize
    /// @return  const char*        logTraceFileSize. On error, an empty string is returned
    virtual const char* GetLogTraceFileSize() const = 0;

    /// @brief Function to retrieve the logTraceLogMode
    /// @return  const char*        logTraceLogMode as comma-separated values. On error, an empty string is returned
    virtual const char* GetLogTraceLogMode() const = 0;

    /// @brief Function to retrieve the logTraceProcessDesc
    /// @return  const char*        logTraceProcessDesc. On error, an empty string is returned
    virtual const char* GetLogTraceProcessDesc() const = 0;

    /// @brief Function to retrieve the logTraceProcessId
    /// @return  const char*        logTraceProcessId. On error, an empty string is returned
    virtual const char* GetlogTraceProcessId() const = 0;

    /// @brief Function to retrieve the Process Identifier
    /// Each Process has a unique Identifier which is defined by the Execution Manager. This Identifier can
    /// be retrieved by the Process using this function
    /// @return  const char*        Process Identifer. On error, an empty string is returned
    virtual const char *GetProcessIdentifier() const = 0;

}; // class IExecutionClientExt
} // namespace exm
} // namespace vrte
} // namespace bosch
#endif
