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
/// @file      IStateClient.hpp
/// @brief     Abstract interface for AR 1911 State Client
/// @copyright Robert Bosch GmbH  2020
/// @author    Avnish Kasbi
//=============================================================================


#ifndef _ISTATE_CLIENT_HPP_INCLUDED
#define _ISTATE_CLIENT_HPP_INCLUDED

#include "ara/core/future.h"
#include "ara/core/result.h"
#include "ara/core/string.h"
#include "ara/core/string_view.h"
#include "ara/exec/exec_error_domain.h"
#include "ara/exec/function_group.h"
#include "ara/exec/function_group_state.h"
#include "ara/exec/execution_error_event.h"

namespace ara
{
namespace exec
{

struct ExecutionErrorEvent;

/// @brief Class representing connection to Execution Management that is used to request Function Group state transitions (or other operations).
/// @note StateClient opens communication channel to Execution Management (e.g. POSIX FIFO). Each Process that intends to perform state management, shall create an instance of this class and it shall have rights to use it.
class IStateClient
{

public:

    /// @brief Destructor of the State Client instance.
    /// @param None none.
    virtual ~IStateClient() noexcept {}

    /// @brief Method to request state transition for a single Function Group.
    /// This method will request Execution Management to perform state transition and return immediately.
    /// Returned ara::core::Future can be used to determine result of requested transition.
    /// @param[in] state representing meta-model definition of a state inside a specific Function Group. Execution Management will perform state transition from the current state to the state identified by this parameter.
    /// @returns void if requested transition is successful, otherwise it returns ExecErrorDomain error.
    /// @error ara::exec::ExecErrc::kCancelled if transition to the requested Function Group state was cancelled by a newer request
    /// @error ara::exec::ExecErrc::kFailed if transition to the requested Function Group state failed
    /// @error ara::exec::ExecErrc::kInvalidArguments if arguments passed doesn't appear to be valid (e.g. after a software update, given functionGroup doesn't exist anymore)
    /// @error ara::exec::ExecErrc::kCommunicationError if StateClient can't communicate with Execution Management (e.g. IPC link is down)
    /// @error ara::exec::ExecErrc::kGeneralError if any other error occurs.
    /// @threadsafety{Thread-safe}
    virtual ara::core::Future<void> SetState(FunctionGroupState const& state) const = 0;

    /// @brief Method to retrieve result of Machine State initial transition to Startup state.

    // This method allows State Management to retrieve result of a transition specified by SWS_EM_01023 and SWS_EM_02241.
    // Please note that this transition happens once per machine life cycle, thus result delivered by this method shall not change (unless machine is started again).
    /// @traceid{SWS_EM_02241}@tracestatus{implemented}
    /// @uptrace{RS_EM_00101}
    /// @param  None.
    /// @returns void if requested transition is successful, otherwise it returns ExecErrorDomain error.
    /// @error ara::exec::ExecErrc::kCancelled if transition to the requested Function Group state was cancelled by a newer request
    /// @error ara::exec::ExecErrc::kFailed if transition to the requested Function Group state failed
    /// @error ara::exec::ExecErrc::kCommunicationError if StateClient can't communicate with Execution Management (e.g. IPC link is down)
    /// @error ara::exec::ExecErrc::kGeneralError if any other error occurs.
    /// @threadsafety{Thread-safe}

    virtual ara::core::Future<void> GetInitialMachineStateTransitionResult() const = 0;
    
    /// @brief Returns the execution error which changed the given Function Group to an Undefined Function Group State.
    ///
    /// This function will return with error and will not return an ExecutionErrorEvent object, if the given
    /// Function Group is in a defined Function Group state again.
    ///
    /// @param[in] functionGroup   Function Group of interest.
    ///
    /// @returns The execution error which changed the given Function Group to an Undefined Function Group State.
    /// @error ara::exec::ExecErrc::kFailed    Given Function Group is not in an Undefined Function Group State.
    /// 
    /// @threadsafety{thread-safe}
    ///
    /// @traceid{SWS_EM_02542}@tracestatus{draft}
    /// @uptrace{RS_EM_00101}
    /// @uptrace{RS_AP_00120}
    /// @uptrace{RS_AP_00121}
    /// @uptrace{RS_AP_00132}
    /// @uptrace{RS_AP_00128}
     
    virtual ara::core::Result<::ara::exec::ExecutionErrorEvent> GetExecutionError(const ara::exec::FunctionGroup &functionGroup) noexcept = 0;
};

} // namespace exec
} // namespace ara

#endif // _ISTATE_CLIENT_HPP_INCLUDED
