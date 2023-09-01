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
#ifndef ARA_DIAG_UPLOAD_H_INCLUDED
#define ARA_DIAG_UPLOAD_H_INCLUDED

#if 0 // Not yet supported in VRTE

#include <ara/core/future.h>
#include <ara/core/instance_specifier.h>
#include <ara/core/result.h>
#include <ara/core/span.h>
#include <ara/core/vector.h>
#include <ara/diag/meta_info.h>
#include <ara/diag/cancellation_handler.h>

#include <ara/diag/reentrancy.h>
#include <cstdint>

namespace ara {

namespace diag {

/**
 * @brief Upload service interface
 *
 * @traceid{SWS_DM_00794}@tracestatus{draft}
 * @uptrace{RS_Diag_04033}
 * @uptrace{RS_Diag_04196}
 */
class UploadService
{
public:

   /**
    * @brief Response data of positive respone message
    *
    * @traceid{SWS_DM_00795}@tracestatus{draft}
    * @uptrace{RS_Diag_04033}
    * @uptrace{RS_Diag_04196}
    */
   struct OperationOutput
   {
      /**
       * @brief Content of positive respone message (without SID)
       *
       * Depending on the operation (e.g.: UploadData, RequestUploadExit) the expectation, what
       * responseData shall contain (where it starts in the positive response) might differ. See
       * doc of corresponding operation.
       *
       * @traceid{SWS_DM_00796}@tracestatus{draft}
       * @uptrace{RS_Diag_04033}
       * @uptrace{RS_Diag_04196}
       */
      ara::core::Vector<std::uint8_t> responseData;
   };

public:

   /**
    * @brief Class for an UploadService
    * @param specifier InstanceSpecifier to an PortPrototype of an DownloadServiceInterface
    * @param reentrancyType specifies if interface is callable fully- or non-reentrant
    *
    * @traceid{SWS_DM_00797}@tracestatus{draft}
    * @uptrace{RS_AP_00137}
    * @uptrace{RS_Diag_04033}
    * @uptrace{RS_Diag_04196}
    */
   explicit UploadService( const ara::core::InstanceSpecifier& specifier, ReentrancyType reentrancyType = ara::diag::ReentrancyType::kNot );

   /**
    * @brief Destructor of class UploadService
    *
    * @traceid{SWS_DM_00798}@tracestatus{draft}
    * @uptrace{RS_AP_00134}
    * @uptrace{RS_Diag_04033}
    * @uptrace{RS_Diag_04196}
    */
   virtual ~UploadService() noexcept = default;

   /**
    * @brief Called for RequestDownload.
    *
    * @param dataFormatIdentifier  UDS dataFormat Identifier
    * @param addressAndLengthFormatIdentifier UDS addressAndLengthFormatIdentifier
    * @param memoryAddressAndSize memoryAddress and memorySize part of the request
    * @param metaInfo contains additional meta information
    * @param cancellationHandler informs if the current conversation is canceled
    * @returns a Result with either void (for a positive response message) or an UDS NRC value (for an negative response message)
    * @error DiagUdsNrcErrorDomain::DiagUdsNrcErrc::kIncorrectMessageLengthOrInvalidFormat 0x13, Negative return code according to ISO 14229.
    * @error DiagUdsNrcErrorDomain::DiagUdsNrcErrc::kConditionsNotCorrect 0x22, Negative return code according to ISO 14229.
    * @error DiagUdsNrcErrorDomain::DiagUdsNrcErrc::kRequestOutOfRange 0x31, Negative return code according to ISO 14229.
    * @error DiagUdsNrcErrorDomain::DiagUdsNrcErrc::kSecurityAccessDenied 0x33, Negative return code according to ISO 14229.
    * @error DiagUdsNrcErrorDomain::DiagUdsNrcErrc::kUploadDownloadNotAccepted 0x70, Negative return code according to ISO 14229.
    *
    * @traceid{SWS_DM_00799}@tracestatus{draft}
    * @uptrace{RS_AP_00119}
    * @uptrace{RS_AP_00138}
    * @uptrace{RS_Diag_04033}
    * @uptrace{RS_Diag_04170}
    * @uptrace{RS_Diag_04196}
    */
   virtual ara::core::Future<void> RequestUpload( std::uint8_t                  dataFormatIdentifier,
                                                  std::uint8_t                  addressAndLengthFormatIdentifier,
                                                  ara::core::Span<std::uint8_t> memoryAddressAndSize,
                                                  MetaInfo&                     metaInfo,
                                                  CancellationHandler           cancellationHandler ) = 0;

   /**
    * @brief Called for TransferData following a previous RequestUpload.
    *
    * @param numBytesToReturn number of bytes DM accepts (due to its internal buffer) for this chunk.
    * @param metaInfo contains additional meta information
    * @param cancellationHandler informs if the current conversation is canceled
    * @returns a Future, which either gets readied to OperationOutput (transferResponseParameterRecord for a positive response message) or readied with ErrorCode from DiagUdsNrcErrc (for an negative response message).
    *          Data in OperationOutput.responseData will be placed after blockSequenceCounter as transferResponseParameterRecord in the positive response.
    * @error DiagUdsNrcErrorDomain::DiagUdsNrcErrc::kIncorrectMessageLengthOrInvalidFormat 0x13, Negative return code according to ISO 14229.
    * @error DiagUdsNrcErrorDomain::DiagUdsNrcErrc::kRequestSequenceError 0x24, Negative return code according to ISO 14229.
    * @error DiagUdsNrcErrorDomain::DiagUdsNrcErrc::kRequestOutOfRange 0x31, Negative return code according to ISO 14229.
    * @error DiagUdsNrcErrorDomain::DiagUdsNrcErrc::kTransferDataSuspended 0x71, Negative return code according to ISO 14229.
    * @error DiagUdsNrcErrorDomain::DiagUdsNrcErrc::kGeneralProgrammingFailure 0x72, Negative return code according to ISO 14229.
    * @error DiagUdsNrcErrorDomain::DiagUdsNrcErrc::kWrongBlockSequenceCounter 0x73, Negative return code according to ISO 14229.
    * @error DiagUdsNrcErrorDomain::DiagUdsNrcErrc::kVoltageTooHigh 0x92, Negative return code according to ISO 14229.
    * @error DiagUdsNrcErrorDomain::DiagUdsNrcErrc::kVoltageTooLow 0x93, Negative return code according to ISO 14229.
    *
    * @traceid{SWS_DM_00800}@tracestatus{draft}
    * @uptrace{RS_AP_00119}
    * @uptrace{RS_AP_00138}
    * @uptrace{RS_Diag_04033}
    * @uptrace{RS_Diag_04170}
    * @uptrace{RS_Diag_04196}
    */
   virtual ara::core::Future<OperationOutput> UploadData(
      std_size_t          numBytesToReturn,
      MetaInfo&           metaInfo,
      CancellationHandler cancellationHandler ) = 0;

   /**
    * @brief Called for RequestTransferExit.
    *
    * @param transferRequestParameterRecord  This parameter record contains parameter(s), which are required by the server to support the transfer of data.
    *        Format and length of this parameter(s) are vehicle manufacturer specific.
    * @param metaInfo contains additional meta information
    * @param cancellationHandler informs if the current conversation is canceled
    * @returns a Future, which either gets readied to OperationOutput (transferResponseParameterRecord for a positive response message)
    *                    or readied with ErrorCode from DiagUdsNrcErrc (for an negative response message)
    *          Data in OperationOutput.responseData will be placed after SID as transferResponseParameterRecord in the positive response.
    * @error DiagUdsNrcErrorDomain::DiagUdsNrcErrc::kIncorrectMessageLengthOrInvalidFormat 0x13, Negative return code according to ISO 14229.
    * @error DiagUdsNrcErrorDomain::DiagUdsNrcErrc::kRequestSequenceError 0x24, Negative return code according to ISO 14229.
    * @error DiagUdsNrcErrorDomain::DiagUdsNrcErrc::kRequestOutOfRange 0x31, Negative return code according to ISO 14229.
    * @error DiagUdsNrcErrorDomain::DiagUdsNrcErrc::kGeneralProgrammingFailure 0x72, Negative return code according to ISO 14229.
    *
    * @traceid{SWS_DM_00801}@tracestatus{draft}
    * @uptrace{RS_AP_00119}
    * @uptrace{RS_AP_00138}
    * @uptrace{RS_Diag_04033}
    * @uptrace{RS_Diag_04170}
    * @uptrace{RS_Diag_04196}
    */
   virtual ara::core::Future<OperationOutput> RequestUploadExit( ara::core::Span<std::uint8_t> transferRequestParameterRecord,
                                                                 MetaInfo&                     metaInfo,
                                                                 CancellationHandler           cancellationHandler ) = 0;

   /**
    * @brief This Offer will enable the DM to forward request messages to this handler
    *
    * @error DiagErrorDomain::DiagReportingErrc::kGenericError General error occurred.
    * @error DiagErrorDomain::DiagOfferErrc::kAlreadyOffered  This service was already offered.
    *
    * @traceid{SWS_DM_00802}@tracestatus{draft}
    * @uptrace{RS_AP_00119}
    * @uptrace{RS_AP_00139}
    * @uptrace{RS_Diag_04033}
    * @uptrace{RS_Diag_04196}
    */
   ara::core::Result<void> Offer();

   /**
    * @brief This StopOffer will disable the forwaring of request messages from DM
    *
    * @traceid{SWS_DM_00803}@tracestatus{draft}
    * @uptrace{RS_Diag_04033}
    * @uptrace{RS_Diag_04196}
    */
   void StopOffer();
};

}     //namespace diag

} //namespace ara

#endif // Not yet supported in VRTE

#endif //ARA_DIAG_UPLOAD_H_INCLUDED
