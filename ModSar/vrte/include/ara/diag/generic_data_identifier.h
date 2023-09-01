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
#ifndef ARA_DIAG_GENERIC_DATA_IDENTIFIER_H_INCLUDED
#define ARA_DIAG_GENERIC_DATA_IDENTIFIER_H_INCLUDED

#include <ara/core/future.h>
#include <ara/core/instance_specifier.h>
#include <ara/core/result.h>
#include <ara/core/vector.h>
#include <ara/core/span.h>
#include <ara/diag/meta_info.h>
#include <ara/diag/cancellation_handler.h>
#include <ara/diag/reentrancy.h>
#include <memory>
#include <cstdint>

namespace ara {

namespace diag {

// Hide implementation details by forward declaration
namespace internal {

class GenericDataIdentifierImpl;

}

/**
 * @brief Generic DataIdentifier interface
 *
 * @traceid{SWS_DM_00607}@tracestatus{draft}
 * @uptrace{RS_Diag_04169}
 */
class GenericDataIdentifier
{
public:

   /**
    * @brief Response data of positive respone message
    *
    * @traceid{SWS_DM_00641}@tracestatus{draft}
    * @uptrace{RS_Diag_04169}
    * @uptrace{RS_Diag_04172}
    */
   struct OperationOutput
   {
      /**
       * @brief Content of positive respone message (without DataIdentifier)
       *
       * @traceid{SWS_DM_00631}@tracestatus{draft}
       * @uptrace{RS_AP_00137}
       * @uptrace{RS_Diag_04169}
       */
      ara::core::Vector<std::uint8_t> responseData;
   };

   /**
    * @brief Class for an GenericDataIdentifier
    * @param specifier InstanceSpecifier to an PortPrototype of an DiagnosticDataIdentifierGenericInterface
    * @param reentrancyType specifies if interface is callable fully- or non-reentrant for reads, writes or both
    *
    * @traceid{SWS_DM_00634}@tracestatus{draft}
    * @uptrace{RS_AP_00137}
    * @uptrace{RS_Diag_04169}
    */
   explicit GenericDataIdentifier( const ara::core::InstanceSpecifier& specifier, DataIdentifierReentrancyType reentrancyType = { ara::diag::ReentrancyType::kNot, ara::diag::ReentrancyType::kNot, ara::diag::ReentrancyType::kNot } );

   /**
    * @brief Destructor of class GenericDataIdentifier
    *
    * @traceid{SWS_DM_00635}@tracestatus{draft}
    * @uptrace{RS_AP_00134}
    * @uptrace{RS_Diag_04169}
    */
   virtual ~GenericDataIdentifier() noexcept;

   /**
    * @brief Called for ReadDataByIdentifier request for this DiagnosticDataIdentifier.
    * @param dataIdentifier the corresponding DataIdentifier
    * @param metaInfo contains additional meta information
    * @param cancellationHandler informs if the current conversation is canceled
    * @returns a Result with either OperationOutput (for a positive response message) or an UDS NRC value (for an negative response message)
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
    * @error DiagUdsNrcErrorDomain::DiagUdsNrcErrc::kResourceTemporarilyNotAvailable 0x94, Negative return code according to ISO 14229-1.
    *
    * @traceid{SWS_DM_00636}@tracestatus{draft}
    * @uptrace{RS_AP_00138}
    * @uptrace{RS_AP_00119}
    * @uptrace{RS_Diag_04169}
    * @uptrace{RS_Diag_04170}
    * @uptrace{RS_Diag_04172}
    */
   virtual ara::core::Future<OperationOutput> Read( std::uint16_t       dataIdentifier,
                                                    MetaInfo&           metaInfo,
                                                    CancellationHandler cancellationHandler ) = 0;

   /**
    * @brief Called for WriteDataByIdentifier request for this DiagnosticDataIdentifier.
    * @param dataIdentifier the corresponding DataIdentifier
    * @param requestData Content of request message (without DataIdentifier)
    * @param metaInfo contains additional meta information
    * @param cancellationHandler informs if the current conversation is canceled
    * @returns a Result with either void (for a positive response message) or an UDS NRC value (for an negative response message)
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
    *
    * @traceid{SWS_DM_00637}@tracestatus{draft}
    * @uptrace{RS_AP_00138}
    * @uptrace{RS_AP_00119}
    * @uptrace{RS_Diag_04169}
    * @uptrace{RS_Diag_04170}
    */
   virtual ara::core::Future<void> Write( std::uint16_t                 dataIdentifier,
                                          ara::core::Span<std::uint8_t> requestData,
                                          MetaInfo&                     metaInfo,
                                          CancellationHandler           cancellationHandler );

   /**
    * @brief This Offer will enable the DM to forward request messages to this handler
    * @error DiagErrorDomain::DiagReportingErrc::kGenericError General error occurred.
    * @error DiagErrorDomain::DiagOfferErrc::kAlreadyOffered  This service was already offered.
    *
    * @traceid{SWS_DM_00638}@tracestatus{draft}
    * @uptrace{RS_AP_00139}
    * @uptrace{RS_AP_00119}
    * @uptrace{RS_Diag_04169}
    */
   ara::core::Result<void> Offer();

   /**
    * @brief This StopOffer will disable the forwaring of request messages from DM
    *
    * @traceid{SWS_DM_00639}@tracestatus{draft}
    * @uptrace{RS_Diag_04169}
    */
   void StopOffer();

private:
   GenericDataIdentifier() = delete;

   GenericDataIdentifier( const GenericDataIdentifier& ) = delete;            // non construction-copyable

   GenericDataIdentifier& operator=( const GenericDataIdentifier& ) = delete; // non copyable

   std::shared_ptr<ara::diag::internal::GenericDataIdentifierImpl> impl;
};

}     //namespace diag

} //namespace ara

#endif //ARA_DIAG_GENERIC_DATA_IDENTIFIER_H_INCLUDED
