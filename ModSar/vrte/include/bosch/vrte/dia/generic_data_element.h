/**
 * @file
 * @copyright 2021 Robert Bosch GmbH. All rights reserved.
 */
#ifndef ARA_DIAG_GENERIC_DATA_ELEMENT_H_INCLUDED
#define ARA_DIAG_GENERIC_DATA_ELEMENT_H_INCLUDED

#include <ara/core/future.h>
#include <ara/core/instance_specifier.h>
#include <ara/core/result.h>
#include <ara/core/vector.h>
#include <ara/diag/meta_info.h>
#include <ara/diag/cancellation_handler.h>
#include <ara/diag/reentrancy.h>
#include <memory>

namespace bosch {

namespace vrte {

namespace dia {

// Hide implementation details by forward declaration
namespace rb_diag_udsservices {

namespace internal {

class GenericDataElementImpl;

}

}         // namespace rb_diag_udsservices

/**
 * @brief Generic DataElement interface
 *
 */
class GenericDataElement
{
public:

   /**
    * @brief Response data of positive respone message
    *
    */
   struct OperationOutput
   {
      /**
       * @brief Content of positive respone message
       *
       */
      ara::core::Vector<std::uint8_t> responseData;
   };

   /**
    * @brief Constructor for a GenericDataElement
    * @param specifier An InstanceSpecifier linking this instance with the PortPrototype in the manifest
    * @param reentrancyType specifies if interface is callable fully- or non-reentrant
    */
   explicit GenericDataElement( const ara::core::InstanceSpecifier& specifier, ara::diag::ReentrancyType reentrancyType = ara::diag::ReentrancyType::kNot );

   /**
    * @brief Destructor of class GenericDataElement
    *
    */
   virtual ~GenericDataElement() noexcept = default;

   /**
    * @brief Called for reading a DataElement.
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
    */
   virtual ara::core::Future<OperationOutput> ReadGenericDataElement( ara::diag::MetaInfo&           metaInfo,
                                                                      ara::diag::CancellationHandler cancellationHandler ) = 0;

   /**
    * @brief This Offer will enable the DM to forward request messages to this handler
    * @error DiagErrorDomain::DiagReportingErrc::kNotOffered There was no Offer called before.
    * @error DiagErrorDomain::DiagReportingErrc::kGenericError General error occurred.
    * @error DiagErrorDomain::DiagOfferErrc::kAlreadyOffered  This service was already offered.
    *
    */
   ara::core::Result<void> Offer();

   /**
    * @brief This StopOffer will disable the forwaring of request messages from DM
    *
    */
   void StopOffer();

private:
   GenericDataElement() = delete;

   GenericDataElement( const GenericDataElement& ) = delete;            // non construction-copyable

   GenericDataElement& operator=( const GenericDataElement& ) = delete; // non copyable

   std::shared_ptr<bosch::vrte::dia::rb_diag_udsservices::internal::GenericDataElementImpl> impl;
};

}     //namespace dia

}     //namespace vrte

} //namespace bosch

#endif //ARA_DIAG_GENERIC_DATA_ELEMENT_H_INCLUDED
