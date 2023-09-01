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
#ifndef ARA_DIAG_SERVICE_VALIDATION_H_INCLUDED
#define ARA_DIAG_SERVICE_VALIDATION_H_INCLUDED

#include <ara/core/future.h>
#include <ara/core/instance_specifier.h>
#include <ara/core/result.h>
#include <ara/core/span.h>
#include <ara/diag/meta_info.h>
#include <memory>
#include <cstdint>

namespace ara {

namespace diag {

// Hide implementation details by forward declaration
namespace internal {

class ServiceValidationImpl;

}

/**
 * @brief Represents the status of the service processing
 *
 * @traceid{SWS_DM_00770}@tracestatus{draft}
 * @uptrace{RS_Diag_04199}
 */
enum class ConfirmationStatusType : std::uint8_t
{
   kResPosOk               = 0x00, ///< Positive response has been sent out successfully
   kResPosNotOk            = 0x01, ///< Positive response has not been sent out successfully
   kResNegOk               = 0x02, ///< Negative response has been sent out successfull
   kResNegNotOk            = 0x03, ///< Negative response has not been sent out successfully
   kResPosSuppressed       = 0x04, ///< Positive answer suppressed
   kResNegSuppressed       = 0x05, ///< Negative answer suppressed
   kCanceled               = 0x06, ///< Processing is canceled
   kNoProcessingNoResponse = 0x07, ///< Processing rejected in Validation
};

/**
 * @brief DiagnosticServiceValidationInterface
 *
 * @traceid{SWS_DM_00771}@tracestatus{draft}
 * @uptrace{RS_Diag_04199}
 */
class ServiceValidation
{
public:

   /**
    * @brief Constructor of ServiceValidation
    *
    * @param specifier InstanceSpecifier to an PortPrototype of an DiagnosticServiceValidationInterface
    *
    * @traceid{SWS_DM_00772}@tracestatus{draft}
    * @uptrace{RS_AP_00137}
    * @uptrace{RS_Diag_04199}
    */
   explicit ServiceValidation( const ara::core::InstanceSpecifier& specifier );

   /**
    * @brief Destructor of ServiceValidation
    *
    * @traceid{SWS_DM_00773}@tracestatus{draft}
    * @uptrace{RS_AP_00134}
    * @uptrace{RS_Diag_04199}
    */
   virtual ~ServiceValidation() noexcept;

   /**
    * @brief Called for any request messsage.
    *
    * @param requestData Diagnostic request data (including SID).
    * @param metaInfo MetaInfo of the request.
    * @returns Returns nothing or an error
    * @error DiagUdsNrcErrorDomain::DiagUdsNrcErrc::kGeneralReject 0x10, Negative return code according to ISO 14229.
    * @error DiagUdsNrcErrorDomain::DiagUdsNrcErrc::kServiceNotSupported 0x11, Negative return code according to ISO 14229.
    * @error DiagUdsNrcErrorDomain::DiagUdsNrcErrc::kSubfunctionNotSupported 0x12, Negative return code according to ISO 14229.
    * @error DiagUdsNrcErrorDomain::DiagUdsNrcErrc::kIncorrectMessageLengthOrInvalidFormat 0x13, Negative return code according to ISO 14229.
    * @error DiagUdsNrcErrorDomain::DiagUdsNrcErrc::kResponseTooLong 0x14, Negative return code according to ISO 14229.
    * @error DiagUdsNrcErrorDomain::DiagUdsNrcErrc::kBusyRepeatRequest 0x21, Negative return code according to ISO 14229.
    * @error DiagUdsNrcErrorDomain::DiagUdsNrcErrc::kConditionsNotCorrect 0x22, Negative return code according to ISO 14229.
    * @error DiagUdsNrcErrorDomain::DiagUdsNrcErrc::kRequestSequenceError 0x24, Negative return code according to ISO 14229.
    * @error DiagUdsNrcErrorDomain::DiagUdsNrcErrc::kNoResponseFromSubnetComponent 0x25, Negative return code according to ISO 14229.
    * @error DiagUdsNrcErrorDomain::DiagUdsNrcErrc::kFailurePreventsExecutionOfRequestedAction 0x26, Negative return code according to ISO 14229.
    * @error DiagUdsNrcErrorDomain::DiagUdsNrcErrc::kRequestOutOfRange 0x31, Negative return code according to ISO 14229.
    * @error DiagUdsNrcErrorDomain::DiagUdsNrcErrc::kSecurityAccessDenied 0x33, Negative return code according to ISO 14229.
    * @error DiagUdsNrcErrorDomain::DiagUdsNrcErrc::kInvalidKey 0x35, Negative return code according to ISO 14229.
    * @error DiagUdsNrcErrorDomain::DiagUdsNrcErrc::kExceedNumberOfAttempts 0x36, Negative return code according to ISO 14229.
    * @error DiagUdsNrcErrorDomain::DiagUdsNrcErrc::kRequiredTimeDelayNotExpired 0x37, Negative return code according to ISO 14229.
    * @error DiagUdsNrcErrorDomain::DiagUdsNrcErrc::kUploadDownloadNotAccepted 0x70, Negative return code according to ISO 14229.
    * @error DiagUdsNrcErrorDomain::DiagUdsNrcErrc::kTransferDataSuspended 0x71, Negative return code according to ISO 14229.
    * @error DiagUdsNrcErrorDomain::DiagUdsNrcErrc::kGeneralProgrammingFailure 0x72, Negative return code according to ISO 14229.
    * @error DiagUdsNrcErrorDomain::DiagUdsNrcErrc::kWrongBlockSequenceCounter 0x73, Negative return code according to ISO 14229.
    * @error DiagUdsNrcErrorDomain::DiagUdsNrcErrc::kSubFunctionNotSupportedInActiveSession 0x7E, Negative return code according to ISO 14229.
    * @error DiagUdsNrcErrorDomain::DiagUdsNrcErrc::kServiceNotSupportedInActiveSession 0x7F, Negative return code according to ISO 14229.
    * @error DiagUdsNrcErrorDomain::DiagUdsNrcErrc::kRpmTooHigh 0x81, Negative return code according to ISO 14229.
    * @error DiagUdsNrcErrorDomain::DiagUdsNrcErrc::kRpmTooLow 0x82, Negative return code according to ISO 14229.
    * @error DiagUdsNrcErrorDomain::DiagUdsNrcErrc::kEngineIsRunning 0x83, Negative return code according to ISO 14229.
    * @error DiagUdsNrcErrorDomain::DiagUdsNrcErrc::kEngineIsNotRunning 0x84, Negative return code according to ISO 14229.
    * @error DiagUdsNrcErrorDomain::DiagUdsNrcErrc::kEngineRunTimeTooLow 0x85, Negative return code according to ISO 14229.
    * @error DiagUdsNrcErrorDomain::DiagUdsNrcErrc::kTemperatureTooHigh 0x86, Negative return code according to ISO 14229.
    * @error DiagUdsNrcErrorDomain::DiagUdsNrcErrc::kTemperatureTooLow 0x87, Negative return code according to ISO 14229.
    * @error DiagUdsNrcErrorDomain::DiagUdsNrcErrc::kVehicleSpeedTooHigh 0x88, Negative return code according to ISO 14229.
    * @error DiagUdsNrcErrorDomain::DiagUdsNrcErrc::kVehicleSpeedTooLow 0x89, Negative return code according to ISO 14229.
    * @error DiagUdsNrcErrorDomain::DiagUdsNrcErrc::kThrottlePedalTooHigh 0x8A, Negative return code according to ISO 14229.
    * @error DiagUdsNrcErrorDomain::DiagUdsNrcErrc::kThrottlePedalTooLow 0x8B, Negative return code according to ISO 14229.
    * @error DiagUdsNrcErrorDomain::DiagUdsNrcErrc::kTransmissionRangeNotInNeutral 0x8C, Negative return code according to ISO 14229.
    * @error DiagUdsNrcErrorDomain::DiagUdsNrcErrc::kTransmissionRangeNotInGear 0x8D, Negative return code according to ISO 14229.
    * @error DiagUdsNrcErrorDomain::DiagUdsNrcErrc::kBrakeSwitchNotClosed 0x8F, Negative return code according to ISO 14229.
    * @error DiagUdsNrcErrorDomain::DiagUdsNrcErrc::kShifterLeverNotInPark 0x90, Negative return code according to ISO 14229.
    * @error DiagUdsNrcErrorDomain::DiagUdsNrcErrc::kTorqueConverterClutchLocked 0x91, Negative return code according to ISO 14229.
    * @error DiagUdsNrcErrorDomain::DiagUdsNrcErrc::kVoltageTooHigh 0x92, Negative return code according to ISO 14229.
    * @error DiagUdsNrcErrorDomain::DiagUdsNrcErrc::kVoltageTooLow 0x93, Negative return code according to ISO 14229.
    * @error DiagUdsNrcErrorDomain::DiagUdsNrcErrc::kNoProcessingNoResponse 0xFF, ///< Deviating from ISO - no further service processing and no response (silently ignore request message).
    *
    * @traceid{SWS_DM_00774}@tracestatus{draft}
    * @uptrace{RS_AP_00138}
    * @uptrace{RS_Diag_04170}
    * @uptrace{RS_Diag_04199}
    * @uptrace{RS_AP_00119}
    */
   virtual ara::core::Future<void> Validate( ara::core::Span<std::uint8_t> requestData, MetaInfo& metaInfo );

   /**
    * @brief This method is called, when a diagnostic request has been finished, to notify about the outcome.
    *
    * @param status status/outcome of the service processing.
    * @param metaInfo MetaInfo of the request.
    * @returns Returns nothing or an error
    *
    * @traceid{SWS_DM_00775}@tracestatus{draft}
    * @uptrace{RS_AP_00138}
    * @uptrace{RS_Diag_04170}
    * @uptrace{RS_Diag_04199}
    */
   virtual ara::core::Future<void> Confirmation( ConfirmationStatusType status, MetaInfo& metaInfo );

   /**
    * @brief This Offer will enable the DM to forward request messages to this handler
    * @returns Returns nothing or an error
    * @error DiagErrorDomain::DiagReportingErrc::kGenericError General error occurred.
    * @error DiagErrorDomain::DiagOfferErrc::kAlreadyOffered  This service was already offered.
    *
    * @traceid{SWS_DM_00776}@tracestatus{draft}
    * @uptrace{RS_AP_00119}
    * @uptrace{RS_AP_00139}
    * @uptrace{RS_Diag_04199}
    */
   ara::core::Result<void> Offer();

   /**
    * @brief This StopOffer will disable the forwaring of request messages from DM
    *
    * @traceid{SWS_DM_00777}@tracestatus{draft}
    * @uptrace{RS_Diag_04199}
    */
   void StopOffer();

private:
   ServiceValidation() = delete;

   ServiceValidation( const ServiceValidation& ) = delete;            // non construction-copyable

   ServiceValidation& operator=( const ServiceValidation& ) = delete; // non copyable

   std::shared_ptr<ara::diag::internal::ServiceValidationImpl> impl;
};    //class ServiceValidation

}     //namespace diag

} //namespace ara

#endif //ARA_DIAG_SERVICE_VALIDATION_H_INCLUDED
