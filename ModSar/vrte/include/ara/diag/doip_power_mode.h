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
#ifndef ARA_DIAG_DOIP_POWER_MODE_H_INCLUDED
#define ARA_DIAG_DOIP_POWER_MODE_H_INCLUDED

#if 0 // Not yet supported in VRTE

#include <ara/diag/reentrancy.h>
#include <ara/core/instance_specifier.h>
#include <ara/core/future.h>
#include <ara/core/result.h>
#include <ara/diag/reentrancy.h>

namespace ara {

namespace diag {

/**
 * @brief PowerMode as defined in ISO13400-2.
 *
 * @traceid{SWS_DM_00730}@tracestatus{draft}
 * @uptrace{SRS_Eth_00080}
 */
enum class PowerModeType
{
   kNotReady     = 0x00,   ///< not all ECUs accessible via DoIP can communicate
   kReady        = 0x01,   ///< all ECUs accessible via DoIP can communicate
   kNotSupported = 0x02    ///< the Diagnostic Information Power Mode Information Request message is not supported
};

/**
 * @brief DiagnosticDoIPPowerModeInterface
 *
 * @traceid{SWS_DM_00731}@tracestatus{draft}
 * @uptrace{SRS_Eth_00080}
 */
class DoIPPowerMode
{
public:

   /**
    * @brief Constructor of DoIPPowerMode
    *
    * @param specifier InstanceSpecifier to an PortPrototype of an DiagnosticDoIPPowerModeInterface
    * @param reentrancyType specifies if interface is callable fully- or non-reentrant
    *
    * @traceid{SWS_DM_00732}@tracestatus{draft}
    * @uptrace{RS_AP_00137}
    * @uptrace{SRS_Eth_00080}
    */
   explicit DoIPPowerMode( const ara::core::InstanceSpecifier& specifier, ReentrancyType reentrancyType = ara::diag::ReentrancyType::kNot );

   /**
    * @brief Destructor of DoIPPowerMode
    *
    * @traceid{SWS_DM_00733}@tracestatus{draft}
    * @uptrace{RS_AP_00134}
    * @uptrace{SRS_Eth_00080}
    */
   virtual ~DoIPPowerMode() noexcept = default;

   /**
    * @brief Called to get the current Power Mode for the DoIP protocol.
    *
    * @return current diagnostic power mode
    *
    * @traceid{SWS_DM_00734}@tracestatus{draft}
    * @uptrace{RS_AP_00138}
    * @uptrace{SRS_Eth_00080}
    */
   virtual ara::core::Future<PowerModeType> GetDoIPPowerMode() = 0;

   /**
    * @brief This Offer will enable the DM to forward request messages to this handler
    * @error DiagErrorDomain::DiagReportingErrc::kGenericError General error occurred.
    * @error DiagErrorDomain::DiagOfferErrc::kAlreadyOffered  This service was already offered.
    *
    * @traceid{SWS_DM_00735}@tracestatus{draft}
    * @uptrace{RS_AP_00119}
    * @uptrace{RS_AP_00139}
    * @uptrace{SRS_Eth_00080}
    */
   ara::core::Result<void> Offer();

   /**
    * @brief This StopOffer will disable the forwarding of request messages from DM
    *
    * @traceid{SWS_DM_00736}@tracestatus{draft}
    * @uptrace{SRS_Eth_00080}
    */
   void StopOffer();
};

}     //namespace diag

} //namespace ara

#endif // Not yet supported in VRTE

#endif //ARA_DIAG_DOIP_POWER_MODE_H_INCLUDED
