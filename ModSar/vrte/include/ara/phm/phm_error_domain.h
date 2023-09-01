//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
/// \copyright (c) 2022 by Robert Bosch GmbH. All rights reserved.
//
// The reproduction, distribution and utilization of this file as
// well as the communication of its contents to others without express
// authorization is prohibited. Offenders will be held liable for the
// payment of damages. All rights reserved in the event of the grant
// of a patent, utility model or design.
//=============================================================================

#ifndef ARA_PHM_PHM_ERROR_DOMAIN_H_
#define ARA_PHM_PHM_ERROR_DOMAIN_H_

#include <ara/core/error_code.h>
#include <ara/core/error_domain.h>
#include <ara/core/core_error_domain.h>

namespace ara
{
namespace phm
{

/// @brief Enumeration class for the Platform Health Management error codes
/// @par **Uptrace** [SWS_PHM_01240]
enum class PhmErrc : ara::core::ErrorDomain::CodeType
{
    /// @brief Service not available. This could be due to communication error (e.g, communication with Phm daemon is 
    /// broken)
    kServiceNotAvailable = 1,
    /// @brief Service could not be offered due to failure of communication with Phm daemon.
    kOfferFailed = 2
};

/// @brief Create a new ErrorCode within PHM error domain.
///
/// This function is used internally by constructors of ErrorCode.
///
/// @param code  PHM domain error code value
/// @param data  optional vendor-specific error data
/// @returns a new ErrorCode instance
constexpr ara::core::ErrorCode MakeErrorCode(PhmErrc code, ara::core::ErrorDomain::SupportDataType data) noexcept 
{
    return ara::core::ErrorCode(static_cast<ara::core::ErrorDomain::CodeType>(code), 
                                ara::core::GetCoreErrorDomain(), data);
}

}
}

#endif
