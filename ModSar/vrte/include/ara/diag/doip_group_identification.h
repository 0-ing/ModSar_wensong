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
#ifndef ARA_DIAG_DOIP_GROUP_IDENTIFICATION_H_INCLUDED
#define ARA_DIAG_DOIP_GROUP_IDENTIFICATION_H_INCLUDED

#if 0 // Not yet supported in VRTE

#include <ara/core/instance_specifier.h>
#include <ara/core/array.h>
#include <ara/core/future.h>
#include <ara/core/result.h>
#include <ara/diag/reentrancy.h>

#include <cstdint>

namespace ara {

namespace diag {

/**
 * @brief DoIPGroupIdentificationInterface
 *
 * @traceid{SWS_DM_00720}@tracestatus{draft}
 * @uptrace{SRS_Eth_00026}
 */
class DoIPGroupIdentification
{
public:

   /**
    * @brief Response data of positive respone message
    *
    * @traceid{SWS_DM_00721}@tracestatus{draft}
    * @uptrace{SRS_Eth_00026}
    */
   struct GidStatus
   {
      ara::core::Array<std::uint8_t, 6> groupIdentification;
      std::uint8_t                      furtherActionRequired;
      std::uint8_t                      syncStatus;
   };

   /**
    * @brief Constructor of DoIPGroupIdentification
    *
    * @param specifier InstanceSpecifier to an PortPrototype of an DiagnosticDoIPGroupIdentificationInterface
    * @param reentrancyType specifies if interface is callable fully- or non-reentrant
    *
    * @traceid{SWS_DM_00722}@tracestatus{draft}
    * @uptrace{RS_AP_00137}
    * @uptrace{SRS_Eth_00026}
    */
   explicit DoIPGroupIdentification( const ara::core::InstanceSpecifier& specifier, ReentrancyType reentrancyType = ara::diag::ReentrancyType::kNot );

   /**
    * @brief Destructor of DoIPGroupIdentification
    *
    * @traceid{SWS_DM_00723}@tracestatus{draft}
    * @uptrace{RS_AP_00134}
    * @uptrace{SRS_Eth_00026}
    */
   virtual ~DoIPGroupIdentification() noexcept = default;

   /**
    * @brief Called to get the current GID state for the DoIP protocol.
    *
    * @return group identification and state
    *
    * @traceid{SWS_DM_00724}@tracestatus{draft}
    * @uptrace{RS_AP_00138}
    * @uptrace{SRS_Eth_00026}
    */
   virtual ara::core::Future<GidStatus> GetGidStatus() = 0;

   /**
    * @brief This Offer will enable the DM to forward request messages to this handler
    * @error DiagErrorDomain::DiagReportingErrc::kGenericError General error occurred.
    * @error DiagErrorDomain::DiagOfferErrc::kAlreadyOffered  This service was already offered.
    *
    * @traceid{SWS_DM_00725}@tracestatus{draft}
    * @uptrace{RS_AP_00119}
    * @uptrace{RS_AP_00139}
    * @uptrace{SRS_Eth_00026}
    */
   ara::core::Result<void> Offer();

   /**
    * @brief This StopOffer will disable the forwarding of request messages from DM
    *
    * @traceid{SWS_DM_00726}@tracestatus{draft}
    * @uptrace{SRS_Eth_00026}
    */
   void StopOffer();
};

}     //namespace diag

} //namespace ara

#endif // Not yet supported in VRTE

#endif //ARA_DIAG_DOIP_GROUP_IDENTIFICATION_H_INCLUDED
