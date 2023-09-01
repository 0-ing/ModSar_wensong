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
 * @file execution_error_event.h
 */

#ifndef ARA_EXEC_EXECUTION_ERROR_EVENT_H_
#define ARA_EXEC_EXECUTION_ERROR_EVENT_H_

#include "ara/exec/IStateClient.hpp"

namespace ara
{
namespace exec
{

/**
 * @brief Represents the execution error.
 *
 * @traceid{SWS_EM_02541} @tracestatus{draft}
 * @uptrace{RS_EM_00101}
 * @uptrace{RS_AP_00122}
 */
using ExecutionError = std::uint32_t;

/**
 * @brief Represents an execution error event which happens in a Function Group.
 *
 * @traceid{SWS_EM_02544} @tracestatus{draft}
 * @uptrace{RS_EM_00101}
 * @uptrace{RS_AP_00116}
 * @uptrace{RS_AP_00122}
 * @uptrace{RS_AP_00124}
 * @uptrace{RS_AP_00140}
 */
struct ExecutionErrorEvent
{
public:
    /// @brief Constructor 
    ExecutionErrorEvent(ExecutionError processExecutionError, FunctionGroup functionGroup_) noexcept
                                    : executionError(processExecutionError),
                                      functionGroup(std::move(functionGroup_)) {}

    /// @brief Move constructor                                  
    ExecutionErrorEvent(ExecutionErrorEvent&& other)
      : executionError(other.executionError),
        functionGroup(std::move(other.functionGroup)){}

    /// @brief Copy constructor                                  
    ExecutionErrorEvent(ExecutionErrorEvent& other)
      : executionError(other.executionError), 
        functionGroup(other.functionGroup.short_name){}

    /**
     * @brief The execution error of the Process which unexpectedly terminated
     * @traceid{SWS_EM_02545} @tracestatus{draft}
     * @uptrace{RS_EM_00101}
     * @uptrace{RS_AP_00124}
     */
    ExecutionError executionError;

    /**
     * @brief The function group in which the error occurred
     * @traceid{SWS_EM_02546} @tracestatus{draft}
     * @uptrace{RS_EM_00101}
     * @uptrace{RS_AP_00124}
     */
    FunctionGroup functionGroup;
};

} /* namespace exec */
} /* namespace ara */

#endif /* ARA_EXEC_EXECUTION_ERROR_EVENT_H_ */
