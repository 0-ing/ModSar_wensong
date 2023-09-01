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
#ifndef ARA_DIAG_INDICATOR_H_INCLUDED
#define ARA_DIAG_INDICATOR_H_INCLUDED

#if 0 // Not yet supported in VRTE

#include <ara/core/future.h>
#include <ara/core/instance_specifier.h>
#include <ara/core/result.h>
#include <functional>

namespace ara {

namespace diag {

/**
 * @brief Represents the state of an indicator.
 *
 * @traceid{SWS_DM_00740}@tracestatus{draft}
 * @uptrace{RS_Diag_04204}
 */
enum class IndicatorType
{
   kOff                  = 0x00, ///< Indicator off mode {default}
   kContinuous           = 0x01, ///< Indicator continuously on mode
   kBlinking             = 0x02, ///< Indicator blinking mode
   kBlinkingOrContinuous = 0x03, ///< Indicator blinking Or continuously on mode
   kSlowFlash            = 0x04, ///< Indicator slow flashing mode
   kFastFlash            = 0x05, ///< Indicator fast flashing mode
   kOnDemand             = 0x06, ///< Indicator on-demand mode
   kShort                = 0x07, ///< Indicator short mode
};

/**
 * @brief DiagnosticIndicatorInterface provides functionality for handling indicators.
 *
 * @traceid{SWS_DM_00741}@tracestatus{draft}
 * @uptrace{RS_Diag_04204}
 */
class Indicator
{
public:

   /**
    * @brief Constructor for DiagnosticIndicatorInterface
    * @param specifier InstanceSpecifier to an PortPrototype of an DiagnosticIndicatorInterface
    *
    * @traceid{SWS_DM_00742}@tracestatus{draft}
    * @uptrace{RS_AP_00137}
    * @uptrace{RS_Diag_04204}
    */
   explicit Indicator( const ara::core::InstanceSpecifier& specifier );

   /**
    * @brief Destructor of DiagnosticIndicatorInterface
    *
    * @traceid{SWS_DM_00743}@tracestatus{draft}
    * @uptrace{RS_AP_00134}
    * @uptrace{RS_Diag_04204}
    */
   ~Indicator() noexcept = default;

   /**
    * @brief Get current Indicator
    * @returns the current Indicator
    *
    * @traceid{SWS_DM_00744}@tracestatus{draft}
    * @uptrace{RS_AP_00139}
    * @uptrace{RS_Diag_04204}
    */
   ara::core::Result<IndicatorType> GetIndicator();

   /**
    * @brief Register a notifier function which is called if the indicator is updated.
    * @param notifier notifier function
    *
    * @traceid{SWS_DM_00745}@tracestatus{draft}
    * @uptrace{RS_AP_00139}
    * @uptrace{RS_Diag_04204}
    */
   ara::core::Result<void> SetNotifier( std::function<void (IndicatorType)> notifier );
};

}     //namespace diag

} //namespace ara

#endif // Not yet supported in VRTE

#endif //ARA_DIAG_INDICATOR_H_INCLUDED
