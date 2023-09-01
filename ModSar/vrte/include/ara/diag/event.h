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
#ifndef ARA_DIAG_EVENT_H_INCLUDED
#define ARA_DIAG_EVENT_H_INCLUDED

#include <ara/core/future.h>
#include <ara/core/instance_specifier.h>
#include <ara/core/result.h>
#include <functional>
#include <cstdint>
#include <initializer_list>

namespace ara {

namespace diag {

namespace internal {

class EventImpl;

}
using sint8_t = int8_t;

/**
 * @brief Represents the type of the DTC format according to ISO 14229-1.
 *
 * @traceid{SWS_DM_00642}@tracestatus{draft}
 * @uptrace{RS_Diag_04201}
 * @uptrace{RS_AP_00125}
 */
enum class DTCFormatType : std::uint8_t
{
   kDTCFormatOBD   = 0,          ///< SAE_J2012-DA_DTCFormat_00 as defined in ISO 15031-6 specification.
   kDTCFormatUDS   = 1,          ///< ISO_14229-1_DTCFormat     as defined in ISO 14229-1 specification.
   kDTCFormatJ1939 = 2           ///< SAE_J1939-73_DTCFormat    as defined in SAE J1939-73.
};

/**
 * @brief Single event status bits
 *
 * @traceid{SWS_DM_00643}@tracestatus{draft}
 * @uptrace{RS_Diag_04151}
 * @uptrace{RS_AP_00125}
 */
enum class EventStatusBit : std::uint8_t
{
   kTestFailed                         = 0x01, ///< bit 0: TestFailed
   kTestFailedThisOperationCycle       = 0x02, ///< bit 1: TestFailedThisOperationCycle
   kTestNotCompletedThisOperationCycle = 0x40  ///< bit 6: TestNotCompletedThisOperationCycle
};


/**
 * @brief Class to implement operations on diagnostic Events.
 *
 * @traceid{SWS_DM_00646}@tracestatus{draft}
 * @uptrace{RS_Diag_04151}
 */
class Event
{
public:

   /**
    * @brief Current event status byte, bit-encoded
    *
    * @traceid{SWS_DM_00644}@tracestatus{draft}
    * @uptrace{RS_Diag_04151}
    */

   struct EventStatusByte
   {
      uint8_t eventStatus;

      #if 0 // Not yet supported in VRTE
      constexpr bool IsFailedAndTested() const noexcept;
      constexpr bool IsPassedAndTested() const noexcept;
      #endif // Not yet supported in VRTE

      /// Check if EventStatusBit(s) in EventStatusByte are set.
      template<typename ... Args>
      constexpr bool IsSet( Args... bits ) const noexcept
      {
         uint8_t data = 0;

         using swallow = std::initializer_list<int>;
         (void) swallow { ( void ( ( data |= static_cast<uint8_t>( bits ) ) ), 0 )... };

         return( ( eventStatus & data ) == data );
      }

      /// Check if EventStatusBit(s) in EventStatusByte are not set.
      template<typename ... Args>
      constexpr bool IsNotSet( Args... bits ) const noexcept
      {
         uint8_t data = 0;

         using swallow = std::initializer_list<int>;
         (void) swallow { ( void ( ( data |= static_cast<uint8_t>( bits ) ) ), 0 )... };

         return( ( static_cast<uint8_t>( ~eventStatus ) & data ) == data );
      }

      /// EventStatusByte ctor
      template<typename ... Args>
      explicit constexpr EventStatusByte( Args ... bits ) noexcept
      {
         uint8_t data = 0;

         using swallow = std::initializer_list<int>;
         (void) swallow { ( void ( data |= static_cast<uint8_t>( bits ) ), 0 )... };
         eventStatus = data;
      };

      constexpr EventStatusByte( const EventStatusByte& ) noexcept = default;

      constexpr EventStatusByte( EventStatusByte&& ) noexcept = default;

      constexpr EventStatusByte& operator=( const EventStatusByte& ) noexcept = default;
      constexpr EventStatusByte& operator=( EventStatusByte&& ) noexcept      = default;
   };

   /**
    * @brief Debounce status of event .
    *
    * @traceid{SWS_DM_00645}@tracestatus{draft}
    * @uptrace{RS_Diag_04068}
    * @uptrace{RS_Diag_04225}
    * @uptrace{RS_AP_00125}
    */
   enum class DebouncingState : std::uint8_t
   {
      kNeutral              = 0x00, ///< Neutral (corresponds to FDC = 0)
      kTemporarilyDefective = 0x01, ///< Temporarily Defective (corresponds to 0 < FDC < 127)
      kFinallyDefective     = 0x02, ///< finally Defective (corresponds to FDC = 127)
      kTemporarilyHealed    = 0x04, ///< temporarily healed (corresponds to -128 < FDC < 0)
      kFinallyHealed        = 0x08  ///< finally healed (corresponds to FDC = -128)
   };

   /**
    * @brief Constructor fct. for objects of class Event.
    * @param specifier InstanceSpecifier to an PortPrototype of an DiagnosticEventInterface
    *
    * @traceid{SWS_DM_00647}@tracestatus{draft}
    * @uptrace{RS_Diag_04151}
    * @uptrace{RS_AP_00137}
    */
   explicit Event( const ara::core::InstanceSpecifier& specifier );

   /**
    * @brief Destructor of class Event
    *
    * @traceid{SWS_DM_00648}@tracestatus{draft}
    * @uptrace{RS_Diag_04151}
    * @uptrace{RS_AP_00134}
    */
   ~Event() noexcept;

   /**
    * @brief Returns the current diagnostic event status
    * @returns the current diagnostic event status
    *
    * @traceid{SWS_DM_00649}@tracestatus{draft}
    * @uptrace{RS_Diag_04151}
    * @uptrace{RS_AP_00139}
    */
   ara::core::Result<EventStatusByte> GetEventStatus();

   /**
    * @brief Register a notifier function which is called if a diagnostic event is changed.
    * @param[in] notifier The function to be called if a diagnostic event is changed.
    * @error DiagErrorDomain::DiagErrc::kInvalidArgument given argument is invalid (pointer).
    *
    * @traceid{SWS_DM_00650}@tracestatus{draft}
    * @uptrace{RS_Diag_04183}
    * @uptrace{RS_AP_00139}
    */
   ara::core::Result<void> SetEventStatusChangedNotifier( std::function<void (EventStatusByte)> notifier );

   // ToDo : Following methods depend on rb-dm functions which are not implemented.
   // So currently these methods are commented out.
   #if 0 // Not yet supported in VRTE
   /**
    * @brief Returns the current warning indicator status
    * @returns the current warning indicator status
    *
    * @traceid{SWS_DM_00651}@tracestatus{draft}
    * @uptrace{RS_Diag_04204}
    * @uptrace{RS_AP_00139}
    */
   ara::core::Result<bool> GetLatchedWIRStatus();

   /**
    * @brief Set the warning indicator status
    *
    * @param[in] status  Limp-home status as determined by the AA. '0' means limp-home not active; '1' means limp-home active;
    * @traceid{SWS_DM_00652}@tracestatus{draft}
    * @uptrace{RS_Diag_04151}
    * @uptrace{RS_AP_00139}
    */
   ara::core::Result<void> SetLatchedWIRStatus( bool status );
   #endif // Not yet supported in VRTE

   /**
    * @brief Returns the DTC-ID related to this event instance.
    *
    * @param[in] dtcFormat  Define DTC format for the return value.
    * @return DTC number in respective DTCFormatType
    *
    * @error DiagErrorDomain::DiagErrc::kNoSuchDTC No DTC available.
    *
    * @traceid{SWS_DM_00653}@tracestatus{draft}
    * @uptrace{RS_Diag_04201}
    * @uptrace{RS_AP_00139}
    * @uptrace{RS_AP_00119}
    */
   ara::core::Result<std::uint32_t> GetDTCNumber( DTCFormatType dtcFormat );

   /**
    * @brief Get the current debouncing status .
    *
    * @return Return the current debouncing state of this event.
    *
    * @traceid{SWS_DM_00654}@tracestatus{draft}
    * @uptrace{RS_Diag_04068}
    * @uptrace{RS_Diag_04225}
    * @uptrace{RS_AP_00139}
    */
   ara::core::Result<DebouncingState> GetDebouncingStatus();

   /**
    * @brief Get the status if the event has matured to test completed (corresponds to FDC = -128 or FDC = 127).
    *
    * @return Return the current test_completed-state of this event. "true", if FDC = -128 or FDC = 127; "false" in all other cases.
    *
    * @traceid{SWS_DM_00655}@tracestatus{draft}
    * @uptrace{RS_Diag_04151}
    * @uptrace{RS_AP_00139}
    */
   ara::core::Result<bool> GetTestComplete();

   /**
    * @brief Returns the current value of Fault Detection Counter of this event.
    * @returns current FaultDetectionCounter value.
    *
    * @traceid{SWS_DM_00656}@tracestatus{draft}
    * @uptrace{RS_Diag_04068}
    * @uptrace{RS_AP_00139}
    */
   ara::core::Result<sint8_t> GetFaultDetectionCounter();

private:
   std::unique_ptr<ara::diag::internal::EventImpl> impl; ///< All the implementation details are delegated to this impl object.
};

} //namespace diag

} //namespace ara

#endif //ARA_DIAG_EVENT_H_INCLUDED
