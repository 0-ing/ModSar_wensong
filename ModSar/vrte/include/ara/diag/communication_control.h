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
#ifndef ARA_DIAG_COMMUNICATION_CONTROL_H_INCLUDED
#define ARA_DIAG_COMMUNICATION_CONTROL_H_INCLUDED

#if 0 // Not yet supported in VRTE

#include <ara/diag/cancellation_handler.h>
#include <ara/diag/reentrancy.h>
#include <ara/diag/meta_info.h>

#include <ara/core/instance_specifier.h>
#include <ara/core/future.h>
#include <ara/core/result.h>

#include <cstdint>

namespace ara {

namespace diag {

/**
 * @brief CommunicationControl interface
 *
 * @traceid{SWS_DM_00804}@tracestatus{draft}
 * @uptrace{RS_Diag_04196}
 */
class CommunicationControl
{
public:

   /**
    * @brief ComCtrlRequestParamsType is a structure, which holds all parameters of an UDS 0x28 communicationControl
    * request.
    *
    * @traceid{SWS_DM_00805}@tracestatus{draft}
    * @uptrace{RS_Diag_04196}
    */
   struct ComCtrlRequestParamsType
   {
      /**
       * @brief Threshold until qualified failed
       *
       * @traceid{SWS_DM_xxxxx}@tracestatus{draft}
       * @uptrace{RS_Diag_xxxxx}
       */
      std::uint8_t  controlType;

      /**
       * @brief Threshold until qualified failed
       *
       * @traceid{SWS_DM_xxxxx}@tracestatus{draft}
       * @uptrace{RS_Diag_xxxxx}
       */
      std::uint8_t  communicationType;

      /**
       * @brief Node identifier to which the request is addressed to
       *
       * @traceid{SWS_DM_xxxxx}@tracestatus{draft}
       * @uptrace{RS_Diag_xxxxx}
       */
      std::uint16_t nodeIdentificationNumber;
   };

   /**
    * @brief Class for an CommunicationControl
    * @param specifier InstanceSpecifier to an PortPrototype of an DiagnosticCommunicationControlInterface
    * @param reentrancyType specifies if interface is callable fully- or non-reentrant
    *
    * @traceid{SWS_DM_00806}@tracestatus{draft}
    * @uptrace{RS_AP_00137}
    * @uptrace{RS_Diag_04196}
    */
   explicit CommunicationControl( const ara::core::InstanceSpecifier& specifier, ReentrancyType reentrancyType = ara::diag::ReentrancyType::kNot );

   /**
    * @brief Destructor of class CommunicationControl
    *
    * @traceid{SWS_DM_00807}@tracestatus{draft}
    * @uptrace{RS_AP_00134}
    * @uptrace{RS_Diag_04196}
    */
   virtual ~CommunicationControl() noexcept = default;

   /**
    * @brief Called for CommunicationControl (x028) with any subfunction as subfunction value is part of argument list.
    * Typically provider of this interface is considered as part of the state management.
    *
    * @param controlType  All UDS request parameters packed into a structure since it holds optional elements
    * @param metaInfo contains additional meta information
    * @param cancellationHandler informs if the current conversation is canceled
    * @error DiagUdsNrcErrorDomain::DiagUdsNrcErrc::kSubfunctionNotSupported 0x12, Negative return code according to
    * ISO 14229.
    * @error DiagUdsNrcErrorDomain::DiagUdsNrcErrc::kIncorrectMessageLengthOrInvalidFormat 0x13, Negative return code
    * according to ISO 14229.
    * @error DiagUdsNrcErrorDomain::DiagUdsNrcErrc::kConditionsNotCorrect 0x22, Negative return code according to ISO
    * 14229.
    * @error DiagUdsNrcErrorDomain::DiagUdsNrcErrc::kRequestOutOfRange 0x31, Negative return code according to ISO
    * 14229.
    *
    * @traceid{SWS_DM_00808}@tracestatus{draft}
    * @uptrace{RS_AP_00119}
    * @uptrace{RS_AP_00138}
    * @uptrace{RS_Diag_04170}
    * @uptrace{RS_Diag_04196}
    */
   virtual ara::core::Future<void> CommCtrlRequest( ComCtrlRequestParamsType controlType,
                                                    MetaInfo&                metaInfo,
                                                    CancellationHandler      cancellationHandler )
   = 0;

   /**
    * @brief This Offer will enable the DM to forward request messages to this handler
    *
    * @error DiagErrorDomain::DiagReportingErrc::kGenericError General error occurred.
    * @error DiagErrorDomain::DiagOfferErrc::kAlreadyOffered  This service was already offered.
    *
    * @traceid{SWS_DM_00809}@tracestatus{draft}
    * @uptrace{RS_AP_00119}
    * @uptrace{RS_AP_00139}
    * @uptrace{RS_Diag_04196}
    */
   ara::core::Result<void> Offer();

   /**
    * @brief This StopOffer will disable the forwarding of request messages from DM
    *
    * @traceid{SWS_DM_00810}@tracestatus{draft}
    * @uptrace{RS_Diag_04196}
    */
   void StopOffer();
};

}  // namespace diag

}  // namespace ara
#endif // Not yet supported in VRTE
#endif //ARA_DIAG_COMMUNICATION_CONTROL_H_INCLUDED
