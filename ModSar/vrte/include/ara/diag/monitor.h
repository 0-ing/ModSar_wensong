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
#ifndef ARA_DIAG_MONITOR_H_INCLUDED
#define ARA_DIAG_MONITOR_H_INCLUDED

#include <ara/core/future.h>
#include <ara/core/instance_specifier.h>
#include <ara/core/result.h>
#include <functional>
#include <cstdint>

// Hide implementation details by forward declaration
namespace bosch {

namespace vrte {

namespace dia {

namespace rb_diag_eventmanagement {

class CMonitor;

} // namespace rb_diag_eventmanagement

} // namespace dia

} // namespace vrte

} // namespace bosch

namespace ara {

namespace diag {

using sint8_t  = int8_t;
using sint16_t = int16_t;

/**
 * @brief Represents the status information reported to AAs why the monitor may be re-initalized
 *
 * @traceid{SWS_DM_00540}@tracestatus{draft}
 * @uptrace{RS_Diag_04179}
 */
enum class InitMonitorReason : std::uint32_t
{
   kClear     = 0x00, ///<  Event was cleared and all internal values and states are reset.
   kRestart   = 0x01, ///<  Operation cycle of the event was (re-)started
   kReenabled = 0x02, ///<  Enable conditions are fulfilled and control DTC setting is set to on
   kDisabled  = 0x03  ///<  Enable conditions no longer fulfilled, or Control DTC setting is set to off
};

/**
 * @brief Represents the status information reported by AAs being relevant for error monitoring
 *
 * @traceid{SWS_DM_00541}@tracestatus{draft}
 * @uptrace{RS_Diag_04179}
 */
enum class MonitorAction : std::uint32_t
{
   kPassed              = 0x00, ///<  Monitor reports qualified test result passed.
   kFailed              = 0x01, ///<  Monitor reports qualified test result failed
   kPrepassed           = 0x02, ///<  Monitor reports unqualified test result pre-passed.
   kPrefailed           = 0x03, ///<  Monitor reports unqualified test result pre-failed.
   kFdcThresholdReached = 0x04, ///<  Monitor triggers the storage of ExtendedDataRecords and Freeze Frames (if the
   kResetTestFailed     = 0x05, ///<  Reset TestFailed Bit without any other side effects like readiness
   kFreezeDebouncing    = 0x06, ///<  Freeze the internal debounce counter/timer.
   kResetDebouncing     = 0x07  ///<  Reset the internal debounce counter/timer.
};

/**
 * @brief Class to implement operations on diagnostic Monitor interface.
 *
 * @traceid{SWS_DM_00542}@tracestatus{draft}
 * @uptrace{RS_Diag_04179}
 */
class Monitor final
{
public:

   /**
    * @brief Represents the parameters for counter-based debouncing
    *
    * @traceid{SWS_DM_00538}@tracestatus{draft}
    * @uptrace{RS_Diag_04068}
    */
   struct CounterBased
   {
      /**
       * @brief Threshold until qualified failed
       *
       * @traceid{SWS_DM_00621}@tracestatus{draft}
       * @uptrace{RS_Diag_04068}
       */
      sint16_t      failedThreshold;

      /**
       * @brief Threshold until qualified passed
       *
       * @traceid{SWS_DM_00622}@tracestatus{draft}
       * @uptrace{RS_Diag_04068}
       */
      sint16_t      passedThreshold;

      /**
       * @brief Stepsize per pre-failed report
       *
       * @traceid{SWS_DM_00623}@tracestatus{draft}
       * @uptrace{RS_Diag_04068}
       */
      std::uint16_t failedStepsize;

      /**
       * @brief Stepsize per pre-passed report
       *
       * @traceid{SWS_DM_00624}@tracestatus{draft}
       * @uptrace{RS_Diag_04068}
       */
      std::uint16_t passedStepsize;

      /**
       * @brief failed to jump value
       *
       * @traceid{SWS_DM_00625}@tracestatus{draft}
       * @uptrace{RS_Diag_04068}
       */
      sint16_t      failedJumpValue;

      /**
       * @brief passed to jump value
       *
       * @traceid{SWS_DM_00626}@tracestatus{draft}
       * @uptrace{RS_Diag_04068}
       */
      sint16_t      passedJumpValue;

      /**
       * @brief is jump supported
       *
       * @traceid{SWS_DM_00627}@tracestatus{draft}
       * @uptrace{RS_Diag_04068}
       */
      bool          useJumpToFailed;

      /**
       * @brief is jump supported
       *
       * @traceid{SWS_DM_00628}@tracestatus{draft}
       * @uptrace{RS_Diag_04068}
       */
      bool          useJumpToPassed;
   };

   /**
    * @brief Represents the parameters for time-based debouncing
    *
    * @traceid{SWS_DM_00539}@tracestatus{draft}
    * @uptrace{RS_Diag_04225}
    */
   struct TimeBased
   {
      /**
       * @brief time until failed in (ms)
       *
       * @traceid{SWS_DM_00629}@tracestatus{draft}
       * @uptrace{RS_Diag_04225}
       */
      std::uint32_t failedMs;

      /**
       * @brief time until passed in (ms)
       *
       * @traceid{SWS_DM_00630}@tracestatus{draft}
       * @uptrace{RS_Diag_04225}
       */
      std::uint32_t passedMs;
   };

   /**
    * @brief Monitor constructor for Monitors with Monitor-internal debouncing
    * @param specifier InstanceSpecifier to an PortPrototype of an DiagnosticMonitorInterface
    * @param[in] initMonitor Possibility to register an InitMonitor callback
    * @param[in] getFaultDetectionCounter Possibility to register a function to get the current FDC for this event.
    *
    * @traceid{SWS_DM_00548}@tracestatus{draft}
    * @uptrace{RS_AP_00137}@uptrace{RS_Diag_04179}
    */
   Monitor( const ara::core::InstanceSpecifier& specifier, std::function<void (InitMonitorReason)> initMonitor, std::function<int8_t( void )> getFaultDetectionCounter );

            #if 0 // Not yet supported in VRTE

   /**
    * @brief Monitor constructor for Monitors with counter-based debouncing
    * @param specifier InstanceSpecifier to an PortPrototype of an DiagnosticMonitorInterface
    * @param[in] initMonitor Possibility to register an InitMonitor callback
    * @param[in] debouncing CounterBased debouncing option is added to the monitor
    *
    * @traceid{SWS_DM_00549}@tracestatus{draft}
    * @uptrace{RS_AP_00137}@uptrace{RS_Diag_04179}@uptrace{RS_Diag_04068}
    */
   Monitor( const ara::core::InstanceSpecifier& specifier, std::function<void (InitMonitorReason)> initMonitor, CounterBased debouncing );
            #endif // Not yet supported in VRTE

            #if 0 // Not yet supported in VRTE

   /**
    * @brief Monitor constructor for Monitors with time-based debouncing
    * @param specifier InstanceSpecifier to an PortPrototype of an DiagnosticMonitorInterface
    * @param[in] initMonitor Possibility to register an InitMonitor callback
    * @param[in] debouncing TimeBased debouncing option is added to the monitor
    *
    * @traceid{SWS_DM_00550}@tracestatus{draft}
    * @uptrace{RS_AP_00137}@uptrace{RS_Diag_04179}@uptrace{RS_Diag_04225}
    */
   Monitor( const ara::core::InstanceSpecifier& specifier, std::function<void (InitMonitorReason)> initMonitor, TimeBased debouncing );
            #endif // Not yet supported in VRTE

   /**
    * @brief Function to report the status information being relevant for error monitoring paths.
    * @param[in] action Contains either the last (un-)qualified test result of the diagnostic monitor or commands to
    * control the debouncing or to force a prestorage.
    *
    * @traceid{SWS_DM_00543}@tracestatus{draft}
    * @uptrace{RS_Diag_04179}
    * @uptrace{RS_AP_00139}
    * @uptrace{RS_AP_00119}
    */
   void ReportMonitorAction( MonitorAction action );

   /**
    * @brief This Offer will enable the DM to forward request messages to this handler
    * @error DiagErrorDomain::DiagOfferErrc::kAlreadyOffered  This service was already offered.
    *
    * @traceid{SWS_DM_01088}@tracestatus{draft}
    * @uptrace{RS_AP_00119}
    * @uptrace{RS_AP_00139}
    * @uptrace{RS_Diag_04169}
    */
   ara::core::Result<void> Offer();

   /**
    * @brief This StopOffer will disable the forwarding of request messages from DM
    *
    * @traceid{SWS_DM_01089}@tracestatus{draft}
    * @uptrace{RS_Diag_04169}
    */
   void StopOffer();

private:
   std::shared_ptr<bosch::vrte::dia::rb_diag_eventmanagement::CMonitor> impl;
};

}     //namespace diag

} //namespace ara

#endif //ARA_DIAG_MONITOR_H_INCLUDED
