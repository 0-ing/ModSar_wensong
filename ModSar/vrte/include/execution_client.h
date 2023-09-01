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

///
/// @file
///

#ifndef _EXECUTION_CLIENT_R2011_H_INCLUDED
#define _EXECUTION_CLIENT_R2011_H_INCLUDED

#ifdef __cplusplus
#include "ara/exec/IExecutionClient.hpp"

namespace exm
{
namespace exclt
{
class ExecutionClientImpl;
}
}

namespace ara
{
namespace exec
{

/// @brief Class to implement operations on Execution Client.
/// @traceid{SWS_EM_02001}
/// @uptrace{RS_EM_00103}
class ExecutionClient final : public IExecutionClient
{

public:
    /// @brief Constructor that creates the Execution Client.
    /// @note Constructor for ExecutionClient which opens the Execution Management communication channel (e.g. POSIX FIFO) for reporting the Execution State. Each Process shall create an instance of this class to report its state
    /// @traceid{SWS_EM_02030}
    /// @uptrace{RS_EM_00103}
    ExecutionClient() noexcept;

    /// @brief Destructor of the Execution Client instance.
    /// @traceid{SWS_EM_02002}
    /// @uptrace{RS_EM_00103}
    ~ExecutionClient() noexcept;

    /// @brief Copy constructor
    ExecutionClient(const ExecutionClient& other);

    /// @brief Copy assignment operator
    ExecutionClient& operator=(const ExecutionClient& other);

    /// @brief Interface for a Process to report its internal state to Execution Management.
    /// @param state Value of the Execution State
    /// @returns An instance of ara::core::Result. The instance holds an ErrorCode containing either one of the specified errors or a void-value.
    /// @error ara::exec::ExecErrc::kGeneralError if some unspecified error occurred
    /// @error ara::exec::ExecErrc::kCommunicationError Communication error between Application and Execution Management, e.g. unable to report state for Non-reporting Process.
    /// @error ara::exec::ExecErrc::kInvalidTransition Invalid transition request (e.g. to Running when already in Running state)
    /// @traceid{SWS_EM_02003}
    /// @uptrace{RS_EM_00103}
    ara::core::Result<void> ReportExecutionState (ExecutionState state) const noexcept;
private:
    exm::exclt::ExecutionClientImpl& client;
};

} // namespace exec
} // namespace ara

extern "C"
{
#else
#include <stdint.h>
#endif

    /// @brief ara_exec_ReportExecutionStateRunning
    ///
    /// Report to EM the application state running - C style
    ///
    /// @return  int8_t
    /// @retval  0              Success
    /// @retval  -1             General Error
    int8_t ara_exec_ReportExecutionStateRunning(void);

#ifdef __cplusplus
}
#endif
#endif // _EXECUTION_CLIENT_R2011_H_INCLUDED