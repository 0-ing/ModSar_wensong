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
#ifndef ARA_DIAG_DOIP_TRIGGER_ANNOUNCEMENT_H_INCLUDED
#define ARA_DIAG_DOIP_TRIGGER_ANNOUNCEMENT_H_INCLUDED

#if 0 // Not yet supported in VRTE

#include <ara/core/result.h>

#include <cstdint>

namespace ara {

namespace diag {

/**
 * @brief DiagnosticDoIPTriggerVehicleAnnouncement
 *
 * @traceid{SWS_DM_00820}@tracestatus{draft}
 * @uptrace{RS_Diag_04242}
 */
class DoIPTriggerVehicleAnnouncement
{
public:

   /**
    * @brief Get DoIPTriggerVehicleAnnouncement interface from DM.
    * @returns DoIPTriggerVehicleAnnouncement object
    *
    * @traceid{SWS_DM_00821}@tracestatus{draft}
    * @uptrace{RS_Diag_04242}
    */
   static ara::core::Result<DoIPTriggerVehicleAnnouncement&> GetDoIPTriggerVehicleAnnouncement();

   /**
    * @brief Called by application to trigger DM sending out vehicle announcements on the given network interface Id.
    *
    * @note If the reported DoIpNetworkConfiguration.networkInterfaceId belongs to a DoIpNetworkConfiguration
    * with property isActivationLineDependent = 'TRUE', this is an error as on those interfaces sending of
    * announcements happens automatically after activation line going up/ip address assignment.
    *
    * @traceid{SWS_DM_00822}@tracestatus{draft}
    * @uptrace{RS_Diag_04242}
    */
   virtual ara::core::Result<void> TriggerVehicleAnnouncement( std::uint8_t networkInterfaceId ) = 0;

private:

   /**
    * @brief Ctor is vendor-specific
    *
    * @traceid{SWS_DM_00823}@tracestatus{draft}
    * @uptrace{RS_Diag_04242}
    */
   DoIPTriggerVehicleAnnouncement();

   /**
    * @brief Dtor is vendor-specific
    *
    * @traceid{SWS_DM_00824}@tracestatus{draft}
    * @uptrace{RS_Diag_04242}
    * @uptrace{RS_AP_00134}
    */
   ~DoIPTriggerVehicleAnnouncement() noexcept;
};

}   //namespace diag

} //namespace ara

#endif // Not yet supported in VRTE

#endif //ARA_DIAG_DOIP_TRIGGER_ANNOUNCEMENT_H_INCLUDED
