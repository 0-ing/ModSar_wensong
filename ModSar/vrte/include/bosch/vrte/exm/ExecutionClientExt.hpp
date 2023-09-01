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
/// @file      ExecutionClientExt.hpp
/// @brief     ExecutionClientExt Class
/// @copyright Robert Bosch GmbH  2019
/// @author
//=============================================================================

#ifndef _EXECUTIONCLIENTEXT_H_INCLUDED
#define _EXECUTIONCLIENTEXT_H_INCLUDED

#include "bosch/vrte/exm/IExecutionClientExt.hpp"

namespace bosch
{
namespace vrte
{
namespace exm
{

/// @brief ExecutionClientExt class
class ExecutionClientExt : public IExecutionClientExt
{
public:
    /// @brief Destructor
    ~ExecutionClientExt() override;

    /// @brief Constructor
    ExecutionClientExt();

    /// @brief copy construction
    ExecutionClientExt(const ExecutionClientExt&) noexcept = default;

    /// @brief copy assignment operator
    ExecutionClientExt& operator=(const ExecutionClientExt&) noexcept;

    /// @brief Function to retrieve the logTraceDefaultLogLevel
    /// @return  const char*        logTraceDefaultLogLevel. On error, an empty string is returned
    const char* GetExecutableVersion() const noexcept override;

    /// @brief Function to retrieve the logTraceDefaultLogLevel
    /// @return  const char*        logTraceDefaultLogLevel. On error, an empty string is returned
    const char* GetlogTraceDefaultLogLevel() const noexcept override;

    /// @brief Function to retrieve the logTraceFilePath
    /// @return  const char*        logTraceFilePath. On error, an empty string is returned
    const char* GetLogTraceFilePath() const noexcept override;

    /// @brief Function to retrieve the logTraceFileSize
    /// @return  const char*        logTraceFileSize. On error, an empty string is returned
    const char* GetLogTraceFileSize() const noexcept override;

    /// @brief Function to retrieve the logTraceLogMode
    /// @return  const char*        logTraceLogMode as comma-separated values. On error, an empty string is returned
    const char* GetLogTraceLogMode() const noexcept override;

    /// @brief Function to retrieve the logTraceProcessDesc
    /// @return  const char*        logTraceProcessDesc. On error, an empty string is returned
    const char* GetLogTraceProcessDesc() const noexcept override;

    /// @brief Function to retrieve the logTraceProcessId
    /// @return  const char*        logTraceProcessId. On error, an empty string is returned
    const char* GetlogTraceProcessId() const noexcept override;

    /// @brief Function to retrieve the Process Identifier
    /// Each Process has a unique Identifier which is defined by the Execution Manager. This Identifier can
    /// be retrieved by the Process using this function
    /// @return  const char*        Process Identifer. On error, an empty string is returned
    const char* GetProcessIdentifier() const noexcept override;

}; // class ExecutionClientExt
} // namespace exm
} // namespace vrte
} // namespace bosch

#endif
