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
#ifndef ARA_DIAG_CONDITION_H_INCLUDED
#define ARA_DIAG_CONDITION_H_INCLUDED

#if 0 // Not yet supported in VRTE
#include <ara/core/future.h>
#include <ara/core/instance_specifier.h>
#include <ara/core/result.h>

namespace ara {

namespace diag {

/**
 * @brief Type for Condition status
 *
 * @traceid{SWS_DM_00710}@tracestatus{draft}
 * @uptrace{RS_AP_00125}
 * @uptrace{RS_Diag_04192}
 */
enum class ConditionType
{
   kConditionFalse = 0x00,  ///< condition is set to false
   kConditionTrue  = 0x01,  ///< condition is set to true
};

/**
 * @brief DiagnosticConditionInterface
 *
 * @traceid{SWS_DM_00711}@tracestatus{draft}
 * @uptrace{RS_Diag_04192}
 */
class Condition
{
public:

   /**
    * @brief Constructor of Condition Class
    * @param specifier InstanceSpecifier to an PortPrototype of an DiagnosticConditionInterface
    *
    * @traceid{SWS_DM_00712}@tracestatus{draft}
    * @uptrace{RS_AP_00137}
    * @uptrace{RS_Diag_04192}
    */
   explicit Condition( const ara::core::InstanceSpecifier& specifier );

   /**
    * @brief Destructor of class Condition
    *
    * @traceid{SWS_DM_00713}@tracestatus{draft}
    * @uptrace{RS_AP_00134}
    * @uptrace{RS_Diag_04192}
    */
   ~Condition() noexcept = default;

   /**
    * @brief Get current condition
    * @returns the current condition
    *
    * @traceid{SWS_DM_00714}@tracestatus{draft}
    * @uptrace{RS_AP_00139}
    * @uptrace{RS_Diag_04192}
    */
   ara::core::Result<ConditionType> GetCondition();

   /**
    * @brief Set condition
    * @param condition current condition
    *
    * @traceid{SWS_DM_00715}@tracestatus{draft}
    * @uptrace{RS_AP_00139}
    * @uptrace{RS_Diag_04192}
    */
   ara::core::Result<void> SetCondition( ConditionType condition );
};

}  // namespace diag

}  // namespace ara
#endif // Not yet supported in VRTE
#endif //ARA_DIAG_CONDITION_H_INCLUDED
