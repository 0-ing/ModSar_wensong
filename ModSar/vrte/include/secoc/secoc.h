/// @file secoc.h
/// @copyright 2021 Robert Bosch GmbH. All rights reserved.

#ifndef SECOC_H
#define SECOC_H

#include <cstdint>

namespace ara
{
namespace com
{
namespace secoc
{
/// @brief The enumeration class defines the status of a verification
///
/// @ID{[SWS_CM_11284]}
enum class VerificationStatusResult : std::uint8_t
{
    kSecOcVerificationSuccess        = 0x00, ///< Verification successful
    kSecOcVerificationFailure        = 0x01, ///< Verification not successful
    kSecOcFreshnessFailure           = 0x02, ///< Verification not successful because of wrong freshness value.
    kSecOcAuthenticationBuildFailure = 0x03, ///< Verification not successful because of wrong build authentication codes
    kSecOcNoVerification
    = 0x04, ///< Verification has been skipped and the data has been provided to the application as is.
    kSecOcVerificationFailureOverwritten = 0x05, ///< Verification failed, but the message was passed on to the
                                                 ///< application due to the override status for this message.
};

/// @brief Data structure to bundle the status of a verification attempt for a specific Freshness Value and Data ID
///
/// @ID{[[SWS_CM_11283]]}

struct VerificationStatusContainer
{
    std::uint16_t freshnessValueID;              ///< Freshness Value ID
    VerificationStatusResult verificationStatus; ///< status of a verification
    std::uint16_t secOCDataId;                   ///< Data ID
};

} // namespace secoc
} // namespace com
} // namespace ara

#endif // SECOC_H
