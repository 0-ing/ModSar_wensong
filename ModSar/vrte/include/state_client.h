// --------------------------------------------------------------------------
// |              _    _ _______     .----.      _____         _____        |
// |         /\  | |  | |__   __|  .  ____ .    / ____|  /\   |  __ \       |
// |        /  \ | |  | |  | |    .  / __ \ .  | (___   /  \  | |__) |      |
// |       / /\ \| |  | |  | |   .  / / / / v   \___ \ / /\ \ |  _  /       |
// |      / /__\ \ |__| |  | |   . / /_/ /  .   ____) / /__\ \| | \ \       |
// |     /________\____/   |_|   ^ \____/  .   |_____/________\_|  \_\      |
// |                              . _ _  .                                  |
// --------------------------------------------------------------------------
//
// All Rights Reserved.
// Any use of this source code is subject to a license agreement with the
// AUTOSAR development cooperation.
// More information is available at www.autosar.org.
//
// Disclaimer
//
// This work (specification and/or software implementation) and the material
// contained in it, as released by AUTOSAR, is for the purpose of information
// only. AUTOSAR and the companies that have contributed to it shall not be
// liable for any use of the work.
//
// The material contained in this work is protected by copyright and other
// types of intellectual property rights. The commercial exploitation of the
// material contained in this work requires a license to such intellectual
// property rights.
//
// This work may be utilized or reproduced without any modification, in any
// form or by any means, for informational purposes only. For any other
// purpose, no part of the work may be utilized or reproduced, in any form
// or by any means, without permission in writing from the publisher.
//
// The work has been developed for automotive applications only. It has
// neither been developed, nor tested for non-automotive applications.
//
// The word AUTOSAR and the AUTOSAR logo are registered trademarks.
// --------------------------------------------------------------------------

/**
 * @file
 */

#ifndef ARA_EXEC_STATE_CLIENT_H_INCLUDED
#define ARA_EXEC_STATE_CLIENT_H_INCLUDED

#include "ara/core/result.h"
#include "ara/core/future.h"
#include "ara/core/string_view.h"
#include "ara/exec/IStateClient.hpp"
#include "ara/exec/execution_error_event.h"

namespace ara
{
namespace exec
{

/**
 * @brief Class representing connection to Execution Management that is used to request Function Group state transitions (or other operations).
 * @note StateClient opens communication channel to Execution Management (e.g. POSIX FIFO). Each Process that intends to perform state management, shall create an instance of this class and it shall have rights to use it.
 *
 * @traceid{SWS_EM_02275}@tracestatus{draft}
 * @uptrace{RS_EM_00101}
 */
class StateClient final : public ara::exec::IStateClient
{
public:
    /**
     * @brief Constructor that creates State Client instance.
     *
     * Registers given callback which is called in case a Function Group changes its state unexpectedly to an Undefined
     * Function Group State.
     *
     * @param[in] undefinedStateCallback    callback to be invoked by StateClient library if a
     *                                          FunctionGroup changes its state unexpectedly to an
     *                                          Undefined Function Group State, i.e. without
     *                                          previous request by SetState(). The affected
     *                                          FunctionGroup and ExecutionError is provided as an
     *                                          argument to the callback in form of ExecutionError
     *                                          Event.
     * 
     * @traceid{SWS_EM_02276}@tracestatus{draft}
     * @uptrace{RS_EM_00101}
     * @uptrace{RS_AP_00120}
     * @uptrace{RS_AP_00121}
     * @uptrace{RS_AP_00132}
     */
    explicit StateClient (std::function< void(const ara::exec::ExecutionErrorEvent &)> undefinedStateCallback) noexcept;

    /**
     * @brief Destructor of the State Client instance.
     * @param  None.
     *
     * @traceid{SWS_EM_02277}@tracestatus{draft}
     * @uptrace{RS_EM_00101}
     */
    ~StateClient () noexcept;

    /// @brief Copy constructor
    StateClient(const StateClient&);

    /// @brief copy assignment
    StateClient& operator=(StateClient&);

    /**
     * @brief Method to request state transition for a single Function Group.
     *
     * This method will request Execution Management to perform state transition and return immediately.
     * Returned ara::core::Future can be used to determine result of requested transition.
     *
     * @param[in] state representing meta-model definition of a state inside a specific Function Group. Execution Management will perform state transition from the current state to the state identified by this parameter.
     * @returns void if requested transition is successful, otherwise it returns ExecErrorDomain error.
     * @error ara::exec::ExecErrc::kCancelled if transition to the requested Function Group state was cancelled by a newer request
     * @error ara::exec::ExecErrc::kFailed if transition to the requested Function Group state failed
     * @error ara::exec::ExecErrc::kFailedUnexpectedTerminationOnExit if Unexpected Termination in Process of previous Function Group State happened.
     * @error ara::exec::ExecErrc::kFailedUnexpectedTerminationOnEnter if Unexpected Termination in Process of target Function Group State happened.
     * @error ara::exec::ExecErrc::kInvalidArguments if arguments passed doesn't appear to be valid (e.g. after a software update, given functionGroup doesn't exist anymore)
     * @error ara::exec::ExecErrc::kCommunicationError if StateClient can't communicate with Execution Management (e.g. IPC link is down)
     * @error ara::exec::ExecErrc::kAlreadyInState if the FunctionGroup is already in the requested state
     * @error ara::exec::ExecErrc::kInTransitionToSameState if a transition to the requested state is already ongoing
     * @error ara::exec::ExecErrc::kInvalidTransition if transition to the requested state is prohibited (e.g. Off state for MachineFG)
     * @error ara::exec::ExecErrc::kGeneralError if any other error occurs.
     * 
     * @threadsafety{thread-safe}
     *
     * @traceid{SWS_EM_01309}@tracestatus{draft}
     * @uptrace{RS_EM_00103}
     * @traceid{SWS_EM_02278}@tracestatus{draft}
     * @uptrace{RS_EM_00101}
     */
    ara::core::Future<void> SetState (const FunctionGroupState &state) const noexcept;

    /**
     * @brief Method to retrieve result of Machine State initial transition to Startup state.
     *
     * This method allows State Management to retrieve result of a transition specified by SWS_EM_01023 and SWS_EM_02241.
     * Please note that this transition happens once per machine life cycle, thus result delivered by this method shall not change (unless machine is started again).
     *
     * @param  None.
     * @returns void if requested transition is successful, otherwise it returns ExecErrorDomain error.
     * @error ara::exec::ExecErrc::kCancelled if transition to the requested Function Group state was cancelled by a newer request
     * @error ara::exec::ExecErrc::kFailed if transition to the requested Function Group state failed
     * @error ara::exec::ExecErrc::kCommunicationError if StateClient can't communicate with Execution Management (e.g. IPC link is down)
     * @error ara::exec::ExecErrc::kGeneralError if any other error occurs.
     * 
     * @threadsafety{thread-safe}
     *
     * @traceid{SWS_EM_02279}@tracestatus{draft}
     * @uptrace{RS_EM_00101}
     */
    ara::core::Future<void> GetInitialMachineStateTransitionResult() const noexcept;

    /**
     * @brief Returns the execution error which changed the given Function Group to an Undefined Function Group State.
     *
     * This function will return with error and will not return an ExecutionErrorEvent object, if the given
     * Function Group is in a defined Function Group state again.
     *
     * @param[in] functionGroup   Function Group of interest.
     *
     * @returns The execution error which changed the given Function Group to an Undefined Function Group State.
     * @error ara::exec::ExecErrc::kFailed    Given Function Group is not in an Undefined Function Group State.
     * @error ara::exec::ExecErrc::kCommunicationError     if StateClient can’t communicate with Execution Management (e.g. IPC link is down)
     * 
     * @threadsafety{thread-safe}
     *
     * @traceid{SWS_EM_02542}@tracestatus{draft}
     * @uptrace{RS_EM_00101}
     * @uptrace{RS_AP_00120}
     * @uptrace{RS_AP_00121}
     * @uptrace{RS_AP_00132}
     * @uptrace{RS_AP_00128}
     */
    ara::core::Result<ara::exec::ExecutionErrorEvent> GetExecutionError (const ara::exec::FunctionGroup &functionGroup) noexcept;

private:
    /// @brief Function object to store the address of callback.
    std::function<void(const ara::exec::ExecutionErrorEvent &)> _undefinedStateCallback;

    /**
    * @brief Method to invoke the callback by providing the ExecutionErrorEvent.
    * @param[in] error  The affected FunctionGroup and ExecutionError is provided as 
    *                   an argument to the callback in form of ExecutionErrorEvent.
    */
    void callBackCapture(const ara::exec::ExecutionErrorEvent& error) const noexcept;
};


} /* namespace exec */
} /* namespace ara */

#endif /* ARA_EXEC_State_CLIENT_H_ */
