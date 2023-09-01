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
#ifndef ARA_DIAG_SECURITY_ACCESS_H_INCLUDED
#define ARA_DIAG_SECURITY_ACCESS_H_INCLUDED

#include <ara/core/future.h>
#include <ara/core/instance_specifier.h>
#include <ara/core/result.h>
#include <ara/core/span.h>
#include <ara/diag/meta_info.h>
#include <ara/diag/cancellation_handler.h>
#include <ara/diag/reentrancy.h>

namespace ara {

namespace diag {

// Hide implementation details by forward declaration
namespace internal {

class SecurityAccessImpl;

}        //namespace internal


/**
 * @brief Represents the status of the key compare
 *
 * @traceid{SWS_DM_00760}@tracestatus{draft}
 * @uptrace{RS_Diag_04005}
 */
enum class KeyCompareResultType
{
   kKeyValid   = 0x00,        ///< Key is valid
   kKeyInvalid = 0x01,        ///< Key is invalid
};

/**
 * @brief DiagnosticSecurityAccessInterface
 *
 * @traceid{SWS_DM_00761}@tracestatus{draft}
 * @uptrace{RS_Diag_04005}
 */
class SecurityAccess
{
public:

   /**
    * @brief Constructor of SecurityAccess
    *
    * @param specifier InstanceSpecifier to an PortPrototype of an DiagnosticSecurityAccessInterface
    * @param reentrancyType specifies if interface is callable fully- or non-reentrant
    *
    * @traceid{SWS_DM_00762}@tracestatus{draft}
    * @uptrace{RS_AP_00137}
    * @uptrace{RS_Diag_04005}
    */
   explicit SecurityAccess( const ara::core::InstanceSpecifier& specifier, ReentrancyType reentrancyType = ara::diag::ReentrancyType::kNot );

   /**
    * @brief Destructor of SecurityAccess
    *
    * @traceid{SWS_DM_00763}@tracestatus{draft}
    * @uptrace{RS_AP_00134}
    * @uptrace{RS_Diag_04005}
    */
   virtual ~SecurityAccess() noexcept;

   /**
    * @brief Called for any request messsage.
    *
    * @param securityAccessDataRecord Security Access payload
    * @param metaInfo MetaInfo of the request.
    * @param cancellationHandler Set if the current conversation is canceled.
    * @return provided seed
    * @error DiagUdsNrcErrorDomain::DiagUdsNrcErrc::kSubfunctionNotSupported 0x12, Negative return code according to ISO 14229.
    * @error DiagUdsNrcErrorDomain::DiagUdsNrcErrc::kIncorrectMessageLengthOrInvalidFormat 0x13, Negative return code according to ISO 14229.
    * @error DiagUdsNrcErrorDomain::DiagUdsNrcErrc::kConditionsNotCorrect 0x22, Negative return code according to ISO 14229.
    * @error DiagUdsNrcErrorDomain::DiagUdsNrcErrc::kRequestSequenceError 0x24, Negative return code according to ISO 14229.
    * @error DiagUdsNrcErrorDomain::DiagUdsNrcErrc::kRequestOutOfRange 0x31, Negative return code according to ISO 14229.
    * @error DiagUdsNrcErrorDomain::DiagUdsNrcErrc::kInvalidKey 0x35, Negative return code according to ISO 14229.
    * @error DiagUdsNrcErrorDomain::DiagUdsNrcErrc::kExceedNumberOfAttempts 0x36, Negative return code according to ISO 14229.
    * @error DiagUdsNrcErrorDomain::DiagUdsNrcErrc::kRequiredTimeDelayNotExpired 0x37, Negative return code according to ISO 14229.
    *
    * @traceid{SWS_DM_00764}@tracestatus{draft}
    * @uptrace{RS_AP_00138}
    * @uptrace{RS_Diag_04005}
    * @uptrace{RS_Diag_04170}
    * @uptrace{RS_AP_00119}
    */
   virtual ara::core::Future<ara::core::Span<std::uint8_t>> GetSeed(
      ara::core::Span<std::uint8_t> securityAccessDataRecord,
      MetaInfo&                     metaInfo,
      CancellationHandler           cancellationHandler ) = 0;

   /**
    * @brief This method is called, when a diagnostic request has been finished, to notify about the outcome.
    *
    * @param key The key to be validated
    * @param metaInfo MetaInfo of the request.
    * @param cancellationHandler Set if the current conversation is canceled.
    * @return Result of the key validation.
    * @error DiagUdsNrcErrorDomain::DiagUdsNrcErrc::kSubfunctionNotSupported 0x12, Negative return code according to ISO 14229.
    * @error DiagUdsNrcErrorDomain::DiagUdsNrcErrc::kIncorrectMessageLengthOrInvalidFormat 0x13, Negative return code according to ISO 14229.
    * @error DiagUdsNrcErrorDomain::DiagUdsNrcErrc::kConditionsNotCorrect 0x22, Negative return code according to ISO 14229.
    * @error DiagUdsNrcErrorDomain::DiagUdsNrcErrc::kRequestSequenceError 0x24, Negative return code according to ISO 14229.
    * @error DiagUdsNrcErrorDomain::DiagUdsNrcErrc::kRequestOutOfRange 0x31, Negative return code according to ISO 14229.
    * @error DiagUdsNrcErrorDomain::DiagUdsNrcErrc::kInvalidKey 0x35, Negative return code according to ISO 14229.
    * @error DiagUdsNrcErrorDomain::DiagUdsNrcErrc::kExceedNumberOfAttempts 0x36, Negative return code according to ISO 14229.
    * @error DiagUdsNrcErrorDomain::DiagUdsNrcErrc::kRequiredTimeDelayNotExpired 0x37, Negative return code according to ISO 14229.
    *
    * @traceid{SWS_DM_00765}@tracestatus{draft}
    * @uptrace{RS_AP_00138}
    * @uptrace{RS_Diag_04005}
    * @uptrace{RS_Diag_04170}
    * @uptrace{RS_AP_00119}
    */
   virtual ara::core::Future<KeyCompareResultType> CompareKey(
      ara::core::Span<std::uint8_t> key,
      MetaInfo&                     metaInfo,
      CancellationHandler           cancellationHandler ) = 0;

   /**
    * @brief This Offer will enable the DM to forward request messages to this handler
    * @error DiagErrorDomain::DiagReportingErrc::kGenericError General error occurred.
    * @error DiagErrorDomain::DiagOfferErrc::kAlreadyOffered  This service was already offered.
    *
    * @traceid{SWS_DM_00766}@tracestatus{draft}
    * @uptrace{RS_AP_00139}
    * @uptrace{RS_Diag_04005}
    * @uptrace{RS_AP_00119}
    */
   ara::core::Result<void> Offer();

   /**
    * @brief This StopOffer will disable the forwaring of request messages from DM
    *
    * @traceid{SWS_DM_00767}@tracestatus{draft}
    * @uptrace{RS_Diag_04005}
    */
   void StopOffer();

private:
   SecurityAccess() = delete;                                   // non default construction

   SecurityAccess( const SecurityAccess& ) = delete;            // non construction-copyable

   SecurityAccess& operator=( const SecurityAccess& ) = delete; // non copyable

   std::shared_ptr<ara::diag::internal::SecurityAccessImpl> impl;
};

}     //namespace diag

} //namespace ara

#endif //ARA_DIAG_SECURITY_ACCESS_H_INCLUDED
