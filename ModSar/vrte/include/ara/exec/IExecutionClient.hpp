//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2020 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================
//
/// @file      IExecutionClient.hpp
/// @brief     Abstract interface for AR 2011 Execution Client
/// @copyright Robert Bosch GmbH  2021
/// @author    uku2kor
//=============================================================================

#ifndef _IEXECUTION_CLIENT_HPP_INCLUDED
#define _IEXECUTION_CLIENT_HPP_INCLUDED

#include "ara/core/error_code.h"
#include "ara/core/error_domain.h"
#include "ara/core/result.h"
#include "ara/exec/exec_error_domain.h"

namespace ara
{
namespace exec
{

/// @brief Defines the internal states of a Process (see 7.3.1). Scoped Enumeration of uint8_t
/// @traceid{SWS_EM_02000}
/// @uptrace{RS_EM_00103}
enum class ExecutionState : uint8_t
{

    /// @brief After a Process has been started by Execution Management, it reports ExecutionState kRunning
    kRunning = 0,
};

/// @brief Interface for the AR 2011 Execution Client class
class IExecutionClient
{

public:
    /// @brief Destructor of the Execution Client instance.
    virtual ~IExecutionClient() {}

    /// @brief Interface for a Process to report its internal state to Execution Management.
    /// @param state Value of the Execution State
    /// @returns An instance of ara::core::Result. The instance holds an ErrorCode containing either one of the specified errors or a void-value.
    /// @error ara::exec::ExecErrc::kGeneralError if some unspecified error occurred
    virtual ara::core::Result<void> ReportExecutionState(ara::exec::ExecutionState state) const = 0;
};

} // namespace exec
} // namespace ara


#endif // _IEXECUTION_CLIENT_HPP_INCLUDED