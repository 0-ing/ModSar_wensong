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

#ifndef ARA_EXEC_EXEC_ERROR_DOMAIN_H_
#define ARA_EXEC_EXEC_ERROR_DOMAIN_H_

#include <cstdint>
#include <iostream>
#include <ostream>
#include <utility>

#include "ara/core/error_code.h"
#include "ara/core/error_domain.h"
#include "ara/core/exception.h"
#include "ara/core/string.h"

namespace ara
{
namespace exec
{

/**
 * @brief Defines an enumeration class for the Execution Management error codes.
 *
 * @traceid{SWS_EM_02281}@tracestatus{draft}
 * @uptrace{RS_AP_00130}
 * @uptrace{RS_AP_00122}
 * @uptrace{RS_AP_00127}
 */
enum class ExecErrc : ara::core::ErrorDomain::CodeType
{
    kGeneralError = 1,                       /**< Some unspecified error occurred */
    kInvalidArguments = 2,                   /**< Invalid argument was passed */
    kCommunicationError = 3,                 /**< Communication error occurred */
    kMetaModelError = 4,                     /**< Wrong meta model identifier passed to a function */
    kCancelled = 5,                          /**< Transition to the requested Function Group state was cancelled by a newer request */
    kFailed = 6,                             /**< Requested operation could not be performed */
    kFailedUnexpectedTerminationOnExit = 7,  /**< Unexpected Termination during transition in Process of previous Function Group State happened */
    kFailedUnexpectedTerminationOnEnter = 8, /**< Unexpected Termination during transition in Process of target Function Group State happened */
    kInvalidTransition = 9,                  /**< Transition invalid (e.g. report kRunning when already in Running Process State) */
    kAlreadyInState = 10,                    /**< Transition to the requested Function Group state failed because it is already in requested state */
    kInTransitionToSameState = 11,           /**< Transition to the requested Function Group state failed because transition to requested state is already in progress*/
    kNoTimeStamp = 12,                       /**< DeterministicClient time stamp information is not available */
    kCycleOverrun = 13,                      /**< Deterministic activation cycle time exceeded */
};                                              

#if defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wnon-virtual-dtor"
#endif

/**
 * @brief Defines a class for exceptions to be thrown by the Execution Management.
 *
 * @traceid{SWS_EM_02282}@tracestatus{draft}
 * @uptrace{RS_AP_00130}
 * @uptrace{RS_AP_00122}
 * @uptrace{RS_AP_00127}
 */
class ExecException : public ara::core::Exception
{
public:
    /**
     * @brief Constructs a new ExecException object containing an error code
     * @param[in] errorCode The error code.
     *
     * @traceid{SWS_EM_02283}@tracestatus{draft}
     * @uptrace{RS_AP_00120}
     * @uptrace{RS_AP_00121}
     * @uptrace{RS_AP_00130}
     * @uptrace{RS_AP_00132}
     */
    explicit ExecException (ara::core::ErrorCode errorCode) noexcept
    : ara::core::Exception(std::move(errorCode)) {}
};

/**
 * @brief Defines a class representing the Execution Management error domain.
 *
 * @traceid{SWS_EM_02284}@tracestatus{draft}
 * @uptrace{RS_AP_00130}
 * @uptrace{RS_AP_00122}
 * @uptrace{RS_AP_00127}
 * @domainid{0x8000'0000'0000'0202}
 */
class ExecErrorDomain final : public ara::core::ErrorDomain
{
    /**
     * @brief Key ID for Execution Management error domain.
     */
    static const ErrorDomain::IdType kId{0x8000000000000202ULL};

public:
    using Errc = ExecErrc;
    using Exception = ExecException;

    /**
     * @brief Constructs a new ExecErrorDomain object
     *
     * @traceid{SWS_EM_02286}@tracestatus{draft}
     * @uptrace{RS_AP_00120}
     * @uptrace{RS_AP_00130}
     * @uptrace{RS_AP_00132}
     */
    ExecErrorDomain() noexcept
    : ErrorDomain(kId) {}

    /**
     * @brief Returns a string constant associated with ExecErrorDomain
     * @return "Exec".
     *
     * @traceid{SWS_EM_02287}@tracestatus{draft}
     * @uptrace{RS_AP_00120}
     * @uptrace{RS_AP_00130}
     * @uptrace{RS_AP_00132}
     */
    const char* Name() const noexcept override;

    /**
     * @brief Returns the message associated with errorCode.
     * @param[in] errorCode The error code number.
     * @return The message associated with the error code.
     *
     * @traceid{SWS_EM_02288}@tracestatus{draft}
     * @uptrace{RS_AP_00120}
     * @uptrace{RS_AP_00121}
     * @uptrace{RS_AP_00130}
     * @uptrace{RS_AP_00132}
     */
    const char* Message(CodeType errorCode) const noexcept override;

    /**
     * @brief Creates a new instance of ExecException from errorCode and throws it as a C++ exception.
     * @param[in] errorCode The error to throw.
     *
     * @traceid{SWS_EM_02289}@tracestatus{draft}
     * @uptrace{RS_AP_00120}
     * @uptrace{RS_AP_00121}
     * @uptrace{RS_AP_00130}
     */
    void ThrowAsException (const ara::core::ErrorCode &errorCode) const noexcept(false) override;
};

/**
 * @brief Returns a string constant associated with ExecErrorDomain
 * @return "Exec".
 *
 * @traceid{SWS_EM_02292}@tracestatus{draft}
 * @uptrace{RS_AP_00128}
 */
inline const char* ExecErrorDomain::Name() const noexcept
{
    return "Exec";
}

/// @brief Returns the message associated with errorCode.
/// @param[in] errorCode The error code number.
/// @return The message associated with the error code.

inline char const* ExecErrorDomain::Message(const CodeType errorCode) const noexcept
{
#if defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic error "-Wswitch-enum"
#endif
    ara::exec::ExecErrc const code = static_cast<ara::exec::ExecErrc>(errorCode); // PRQA S 3013 #The function argument is of type uint32_t so it has to be cast to an enum for further evaluation
    switch (code)
    {
        case ara::exec::ExecErrc::kGeneralError:
        {
            return "Some unspecified error occurred";
        }
        case ara::exec::ExecErrc::kInvalidArguments:
        {
            return "Invalid argument was passed";
        }
        case ara::exec::ExecErrc::kCommunicationError:
        {
            return "Communication error occurred";
        }
        case ara::exec::ExecErrc::kMetaModelError:
        {
            return "Wrong meta model identifier passed to a function";
        }
        case ara::exec::ExecErrc::kCancelled:
        {
            return "Transition to the requested Function Group state was cancelled by a newer request"; // SWS_EM_02298
        }
        case ara::exec::ExecErrc::kFailed:
        {
            return "Transition to the requested Function Group state failed";
        }
        case ara::exec::ExecErrc::kFailedUnexpectedTerminationOnExit:
        {
            return "Unexpected Termination during transition in Process of previous Function Group State happened";
        }
        case ara::exec::ExecErrc::kFailedUnexpectedTerminationOnEnter:
        {
            return "Unexpected Termination during transition in Process of target Function Group State happened";
        }
        case ara::exec::ExecErrc::kInvalidTransition:
        {
            return "Transition invalid (e.g. report kRunning when already in Running Process State)";
        }
        case ara::exec::ExecErrc::kAlreadyInState:
        {
            return "Transition to the requested Function Group state failed because it is already in requested state";
        }
        case ara::exec::ExecErrc::kInTransitionToSameState:
        {
            return "Transition to the requested Function Group state failed because transition to requested state is already in progress";
        }
        case ara::exec::ExecErrc::kNoTimeStamp:
        {
            return "DeterministicClient time stamp information is not available";
        }
        case ara::exec::ExecErrc::kCycleOverrun:
        {
            return "Deterministic activation cycle time exceeded";
        }
        default:
            return "Unknown error";
    }

#if defined(__GNUC__)
#pragma GCC diagnostic pop
#endif
}

/// @brief Creates a new instance of ExecException from errorCode and throws it as a C++ exception.
/// @param[in] errorCode The error to throw.

inline void ExecErrorDomain::ThrowAsException(ara::core::ErrorCode const& errorCode) const noexcept(false)
{
    throw ExecException(errorCode);
}

#if defined(__GNUC__)
#pragma GCC diagnostic pop
#endif

namespace internal
{
static const ExecErrorDomain g_ExecErrorDomain;
}

/**
 * @brief Returns a reference to the global ExecErrorDomain object.
 *
 * @traceid{SWS_EM_02290}@tracestatus{draft}
 * @uptrace{RS_AP_00120}
 * @uptrace{RS_AP_00130}
 * @uptrace{RS_AP_00132}
 * @return Return a reference to the global ExecErrorDomain object.
 */

inline const ara::core::ErrorDomain& GetExecErrorDomain () noexcept
{
    return internal::g_ExecErrorDomain;
}

/**
 * @brief Creates an instance of ErrorCode.
 *
 * @traceid{SWS_EM_02291}@tracestatus{draft}
 * @uptrace{RS_AP_00120}
 * @uptrace{RS_AP_00121}
 * @uptrace{RS_AP_00130}
 * @uptrace{RS_AP_00132}
 * @param[in] code Error code number.
 * @param[in] data Vendor defined data associated with the error.
 * @return An ErrorCode object.
 */
inline ara::core::ErrorCode MakeErrorCode(ara::exec::ExecErrc code, ara::core::ErrorDomain::SupportDataType data) noexcept
{
    return ara::core::ErrorCode(static_cast<ara::core::ErrorDomain::CodeType>(code), GetExecErrorDomain(), data);
}

} // namespace exec
} // namespace ara

#endif // ARA_EXEC_EXEC_ERROR_DOMAIN_H_
