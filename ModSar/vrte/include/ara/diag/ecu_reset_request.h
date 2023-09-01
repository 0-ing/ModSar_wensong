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
#ifndef ARA_DIAG_ECU_RESET_REQUEST_H_INCLUDED
#define ARA_DIAG_ECU_RESET_REQUEST_H_INCLUDED

#include <ara/core/future.h>
#include <ara/core/instance_specifier.h>
#include <ara/core/result.h>
#include <ara/core/vector.h>
#include <ara/core/optional.h>
#include <ara/core/span.h>
#include <ara/diag/meta_info.h>
#include <ara/diag/cancellation_handler.h>
#include <ara/diag/reentrancy.h>
#include <memory>
#include <cstdint>

namespace ara {

namespace diag {

namespace internal {

class EcuResetRequestImpl;

}

/**
 * @brief The type of the requested reset.
 *
 * @traceid{SWS_DM_01007}@tracestatus{draft}
 * @uptrace{RS_Diag_04169}
 * @uptrace{RS_Diag_04196}
 * @uptrace{}
 */
enum class ResetRequestType : std::uint32_t
{
   kSoftReset     = 0,      ///<  softReset.
   kHardReset     = 1,      ///<  hardReset
   kKeyOffOnReset = 2,      ///<  keyOffOnReset
   kCustomReset   = 3       ///< kCustomReset
};

/**
 * @brief The type of the requested reset.
 *
 * @traceid{SWS_DM_01008}@tracestatus{draft}
 * @uptrace{}
 */
enum class LastResetType : std::uint32_t
{
   kRegular       = 0,    ///<  regular shutdown.
   kUnexpected    = 1,    ///<  unexpected reset.
   kSoftReset     = 2,    ///<  Diagnostic softReset.
   kHardReset     = 3,    ///<  Diagnostic hardReset
   kKeyOffOnReset = 4,    ///< Diagnostic keyOffOnReset
   kCustomReset   = 5     ///< Diagnostic kCustomReset
};

/**
 * @brief Service EcuReset Request interface
 *
 * @traceid{SWS_DM_01009}@tracestatus{draft}
 * @uptrace{RS_Diag_04169}
 * @uptrace{RS_Diag_04196}
 */
class EcuResetRequest
{
public:

   /**
    * @brief Constructor of EcuResetRequest
    *
    * @param specifier An InstanceSpecifier linking this instance with the PortPrototype in the manifest
    *
    * @traceid{SWS_DM_01010}@tracestatus{draft}
    * @uptrace{RS_Diag_04169}
    * @uptrace{RS_Diag_04196}
    * @uptrace{}
    */
   explicit EcuResetRequest( const ara::core::InstanceSpecifier& specifier );

   /**
    * @brief Destructor of EcuResetRequest
    *
    * @traceid{SWS_DM_01011}@tracestatus{draft}
    * @uptrace{RS_Diag_04169}
    * @uptrace{RS_Diag_04196}
    * @uptrace{}
    */
   virtual ~EcuResetRequest() noexcept;

            #if 0 // Not yet supported in VRTE
   /**
    * @brief interface for subFunction En-/DisableRapidShutdown
    *
    * @param enable when enable is set to true the rapid shutdown will be enabled, setting enable to false will disable rapid shutdown
    * @param metaInfo MetaInfo of the request.
    * @param cancellationHandler Set if the current conversation is canceled.
    * @error DiagErrorDomain::DiagErrc::kRejected Requested operation was rejected due to StateManagements/machines internal state.
    * @error DiagErrorDomain::DiagErrc::kResetTypeNotSupported The requested Diagnostic reset type is not supported by the Diagnostic Address instance.
    *
    * @traceid{SWS_DM_01012}@tracestatus{draft}
    * @uptrace{RS_Diag_04169}
    * @uptrace{RS_Diag_04196}
    */
   virtual ara::core::Future<void> EnableRapidShutdown(
      bool                enable,
      const MetaInfo&     metaInfo,
      CancellationHandler cancellationHandler ) = 0;
            #endif // Not yet supported in VRTE

   /**
    * @brief Called for any EcuRest subFunction, except En-/DisableRapidShutdown.
    *
    * StateManagement needs to evalute carefully if the request to restart parts or the whole machine.
    * Once the request to reset is accepted, the StateManagement has to rely on this decision for the
    * ExecuteReset() trigger.
    *
    * @param resetType Type of the requested reset.
    * @param id id of the custom reset type. Will only be evaluated when resetType is "custom"
    * @param metaInfo MetaInfo of the request.
    * @param cancellationHandler Set if the current conversation is canceled.
    * @error DiagErrorDomain::DiagErrc::kRejected Requested operation was rejected due to StateManagements/machines internal state.
    * @error DiagErrorDomain::DiagErrc::kRequestFailed Diagnostic request could not be performed successfully.
    * @error DiagErrorDomain::DiagErrc::kCustomResetTypeNotSupported The requested Diagnostic custom reset type is not supported by the Diagnostic Address instance.
    * @error DiagErrorDomain::DiagErrc::kResetTypeNotSupported The requested Diagnostic reset type is not supported by the Diagnostic Address instance.
    *
    * @traceid{SWS_DM_01013}@tracestatus{draft}
    */
   virtual ara::core::Future<void> RequestReset(
      ResetRequestType                  resetType,
      ara::core::Optional<std::uint8_t> id,
      const MetaInfo&                   metaInfo,
      CancellationHandler               cancellationHandler ) = 0;

   /**
    * @brief StateManagement has to execute the requested reset.
    *
    * Called after DM sent the response message to tester.
    *
    * @traceid{SWS_DM_01014}@tracestatus{draft}
    * @uptrace{RS_Diag_04169}
    * @uptrace{RS_Diag_04196}
    */
   virtual void ExecuteReset(
      MetaInfo& metaInfo
      ) = 0;

   /**
    * @brief This Offer will enable the DM to forward request messages to this handler
    * @error DiagErrorDomain::DiagReportingErrc::kNotOffered There was no Offer called before.
    * @error DiagErrorDomain::DiagReportingErrc::kGenericError General error occurred.
    * @error DiagErrorDomain::DiagOfferErrc::kAlreadyOffered  This service was already offered.
    *
    * @traceid{SWS_DM_01016}@tracestatus{draft}
    * @uptrace{RS_AP_00139}
    * @uptrace{RS_AP_00119}
    */
   ara::core::Result<void> Offer();

   /**
    * @brief This StopOffer will disable the forwarding of request messages from DM
    *
    * @traceid{SWS_DM_01017}@tracestatus{draft}
    * @uptrace{RS_Diag_04169}
    * @uptrace{RS_Diag_04196}
    */
   void StopOffer();

private:
   EcuResetRequest() = delete;

   EcuResetRequest( const EcuResetRequest& ) = delete;            // non construction-copyable

   EcuResetRequest& operator=( const EcuResetRequest& ) = delete; // non copyable

   std::shared_ptr<ara::diag::internal::EcuResetRequestImpl> impl;
};

}     //namespace diag

} //namespace ara

#endif //ARA_DIAG_ECU_RESET_REQUEST_H_INCLUDED
