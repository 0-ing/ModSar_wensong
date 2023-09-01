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
#ifndef ARA_DIAG_DOIP_ACTIVATIONLINE_H_INCLUDED
#define ARA_DIAG_DOIP_ACTIVATIONLINE_H_INCLUDED

#if 0 // Not yet supported in VRTE

#include <ara/core/instance_specifier.h>
#include <ara/core/future.h>
#include <ara/core/result.h>
#include <cstdint>

namespace ara {

namespace diag {

/**
 * @brief DiagnosticDoIPActivationLineInterface
 *
 * @traceid{SWS_DM_00830}@tracestatus{draft}
 * @uptrace{RS_Diag_04242}
 */
class DoIPActivationLine
{
public:

   /**
    * @brief Constructor of DoIPActivationLine
    *
    * @param specifier InstanceSpecifier to an PortPrototype of an DiagnosticDoIPActivationLineInterface
    *
    * @traceid{SWS_DM_00831}@tracestatus{draft}
    * @uptrace{RS_Diag_04242}
    */
   explicit DoIPActivationLine( const ara::core::InstanceSpecifier& specifier );

   /**
    * @brief Destructor of DoIPActivationLine
    *
    * @traceid{SWS_DM_00832}@tracestatus{draft}
    * @uptrace{RS_Diag_04242}
    * @uptrace{RS_AP_00134}
    */
   virtual ~DoIPActivationLine() noexcept = default;

   /**
    * @brief Called to get the network interface Id (see DoIpNetworkConfiguration.networkInterfaceId)
    * for which this DoIPActivationLine instance is responsible.
    * @note If the reported DoIpNetworkConfiguration.networkInterfaceId belongs to a DoIpNetworkConfiguration
    * with property isActivationLineDependent = 'FALSE', this is an error!
    *
    * @return network interface id for which this activation line is responsible.
    *
    * @traceid{SWS_DM_00833}@tracestatus{draft}
    * @uptrace{RS_Diag_04242}
    */
   virtual ara::core::Future<std::uint8_t> GetNetworkInterfaceId() = 0;

   /**
    * @brief Called to update current activation line state.
    *
    * @traceid{SWS_DM_00834}@tracestatus{draft}
    * @uptrace{RS_Diag_04242}
    */
   virtual void UpdateActivationLineState( bool ) = 0;

   /**
    * @brief Called to get the current activation line state.
    *
    * @return TRUE in case the activation line is active, else FALSE.
    *
    * @traceid{SWS_DM_00835}@tracestatus{draft}
    * @uptrace{RS_Diag_04242}
    */
   virtual ara::core::Future<bool> GetActivationLineState() = 0;

   /**
    * @brief This Offer will enable the DM to listen to activation line state changes for the
    * given interface.
    * @error DiagErrorDomain::DiagReportingErrc::kGenericError General error occurred.
    * @error DiagErrorDomain::DiagOfferErrc::kAlreadyOffered  This service was already offered.
    *
    * @traceid{SWS_DM_00836}@tracestatus{draft}
    * @uptrace{RS_Diag_04242}
    * @uptrace{RS_AP_00119}
    */
   ara::core::Result<void> Offer();

   /**
    * @brief This StopOffer will disable the provision of activation line state to DM.
    *
    * @traceid{SWS_DM_00837}@tracestatus{draft}
    * @uptrace{RS_Diag_04242}
    */
   void StopOffer();
};

}   //namespace diag

} //namespace ara

#endif // Not yet supported in VRTE

#endif //ARA_DIAG_DOIP_ACTIVATIONLINE_H_INCLUDED
