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
#ifndef ARA_DIAG_DTC_INFORMATION_H_INCLUDED
#define ARA_DIAG_DTC_INFORMATION_H_INCLUDED

#include <ara/core/instance_specifier.h>
#include <ara/core/future.h>
#include <ara/core/result.h>
#include <ara/core/vector.h>
#include <functional>
#include <cstdint>

#include <initializer_list>

namespace ara {

namespace diag {

namespace internal {

class DTCInformationImpl;

}

/**
 * @brief UDS DTC status bits according to ISO 14229-1
 *
 * @traceid{SWS_DM_00658}@tracestatus{draft}
 * @uptrace{RS_Diag_04067}
 * @uptrace{RS_Diag_04151}
 */
enum class UdsDtcStatusBitType : std::uint8_t
{
   kTestFailed                         = 0x01, ///< bit 0: TestFailed
   kTestFailedThisOperationCycle       = 0x02, ///< bit 1: TestFailedThisOperationCycle
   kPendingDTC                         = 0x04, ///< bit 2: PendingDTC
   kConfirmedDTC                       = 0x08, ///< bit 3: ConfirmedDTC
   kTestNotCompletedSinceLastClear     = 0x10, ///< bit 4: TestNotCompletedSinceLastClear
   kTestFailedSinceLastClear           = 0x20, ///< bit 5: TestFailedSinceLastClear
   kTestNotCompletedThisOperationCycle = 0x40, ///< bit 6: TestNotCompletedThisOperationCycle
   kWarningIndicatorRequested          = 0x80  ///< bit 7: WarningIndicatorRequested
};

/**
 * @brief Type for ControlDTCStatus status as requested by UDS service 0x85 ControlDTCSetting.
 *
 * @traceid{SWS_DM_00663}@tracestatus{draft}
 * @uptrace{RS_Diag_04159}
 */
enum class ControlDtcStatusType : uint8_t
{
   kDTCSettingOn  = 0x00,         ///<  Updating of diagnostic trouble code status bits is under normal operating conditions
   kDTCSettingOff = 0x01          ///<  Updating of diagnostic trouble code status bits is stopped
};

/**
 * @brief Class to implement operations on DTC informations per configured DiagnosticMemoryDestination.
 *
 * @traceid{SWS_DM_00657}@tracestatus{draft}
 * @uptrace{RS_Diag_04150}
 * @uptrace{RS_Diag_04105}
 */
class DTCInformation
{
public:

   /**
    * @brief Type for UDS DTC status byte.
    *
    * @traceid{SWS_DM_00659}@tracestatus{draft}
    * @uptrace{RS_Diag_04067}
    * @uptrace{RS_Diag_04151}
    */
   struct UdsDtcStatusByteType
   {
      uint8_t udsDtcStatus;

      #if 0 // Not yet supported in VRTE
      constexpr bool IsFailedAndTested() const noexcept;
      constexpr bool IsPassedAndTested() const noexcept;
      #endif // Not yet supported in VRTE

      /**
       * @brief Check if given DTC status is set.
       * @param[in] bits DTC status expected to set
       * @return bool true if all the given status bits are set
       * @details It provides the functionality to check if all the given status are set for user
       */
      template<typename ... Args>
      constexpr bool IsSet( Args... bits ) const noexcept
      {
         uint8_t data = 0;

         using swallow = std::initializer_list<int>;
         (void) swallow { ( void ( ( data |= static_cast<uint8_t>( bits ) ) ), 0 )... };

         return( ( udsDtcStatus & data ) == data );
      };

      /**
       * @brief Check if given DTC status is not set.
       * @param[in] bits DTC status expected to not set
       * @return bool true if all the given status bits are not set
       * @details It provides the functionality to check if all the given status are not set for user
       */
      template<typename ... Args>
      constexpr bool IsNotSet( Args... bits ) const noexcept
      {
         uint8_t data = 0;

         using swallow = std::initializer_list<int>;
         (void) swallow { ( void ( ( data |= static_cast<uint8_t>( bits ) ) ), 0 )... };

         return( ( static_cast<uint8_t>( ~udsDtcStatus ) & data ) == data );
      };

      /**
       * @brief Constructor of UdsDtcStatusByteType
       * @param[in] bits DTC status to be set
       * @details It initializes udsDtcStatus with given DTC status
       */
      template<typename ... Args>
      explicit constexpr UdsDtcStatusByteType( Args... bits ) noexcept
      {
         uint8_t data = 0;

         using swallow = std::initializer_list<int>;
         (void) swallow { ( void ( data |= static_cast<uint8_t>( bits ) ), 0 )... };
         udsDtcStatus = data;
      };

      constexpr UdsDtcStatusByteType( const UdsDtcStatusByteType& ) noexcept = default;

      constexpr UdsDtcStatusByteType( UdsDtcStatusByteType&& ) noexcept = default;

      constexpr UdsDtcStatusByteType &operator=( const UdsDtcStatusByteType& ) noexcept = default;
      constexpr UdsDtcStatusByteType &operator=( UdsDtcStatusByteType&& ) noexcept      = default;
   };

   /**
    * @brief Type for SnapshotDataIdentifierType status
    *
    * @traceid{SWS_DM_00660}@tracestatus{draft}
    * @uptrace{RS_Diag_04205}
    */
   struct SnapshotDataIdentifierType
   {
      std::uint16_t                   dataIdentifier;
      ara::core::Vector<std::uint8_t> data;
   };

   /**
    * @brief Type for SnapshotDataRecordType status
    *
    * @traceid{SWS_DM_00661}@tracestatus{draft}
    * @uptrace{RS_Diag_04205}
    */
   struct SnapshotDataRecordType
   {
      std::uint8_t                                  snapshotRecordNumber;
      ara::core::Vector<SnapshotDataIdentifierType> snapshotDataIdentifiers;
   };

   /**
    * @brief Type for SnapshotRecordUpdatedType status
    *
    * @traceid{SWS_DM_00662}@tracestatus{draft}
    * @uptrace{RS_Diag_04205}
    */
   struct SnapshotRecordUpdatedType
   {
      uint32_t                                  DTC; ///<  DTC which is changed
      ara::core::Vector<SnapshotDataRecordType> snapshotDataRecords;
   };

   /**
    * @brief Constructor for a DTCInformation instance which allows for DTC related operation per DiagnosticMemoryDestination.
    * @param specifier InstanceSpecifier to an PortPrototype of an DiagnosticDTCInformationInterface
    * @traceid{SWS_DM_00664}@tracestatus{draft}
    * @uptrace{RS_AP_00137}
    * @uptrace{RS_Diag_04150}
    * @uptrace{RS_Diag_04105}
    */
   explicit DTCInformation( const ara::core::InstanceSpecifier& specifier );

   /**
    * @brief Destructor of class DTCInformation
    *
    * @traceid{SWS_DM_00665}@tracestatus{draft}
    * @uptrace{RS_AP_00134}
    */
   ~DTCInformation() noexcept;

   /**
    * @brief Retrieves the current UDS DTC status byte of the given DTC identifier.
    * @param[in] dtc  DTC indentifier for which the status should be retrieved.
    * @returns the current UDS DTC status byte of the given DTC identifier.
    * @error DiagErrorDomain::DiagErrc::kNoSuchDtc given DTC identifier not available.
    *
    * @traceid{SWS_DM_00666}@tracestatus{draft}
    * @uptrace{RS_AP_00139}
    */
   ara::core::Result<UdsDtcStatusByteType> GetCurrentStatus( std::uint32_t dtc );

   /**
    * @brief Register a notifier function which is called if a UDS DTC status is changed.
    * @param[in] notifier  The function to be called if a DTC status has changed.
    * @error DiagErrorDomain::DiagErrc::kNoSuchDtc given DTC identifier not available.
    * @error DiagErrorDomain::DiagErrc::kInvalidArgument given arguments are invalid (pointer, status old/new not plausible).
    *
    * @traceid{SWS_DM_00667}@tracestatus{draft}
    * @uptrace{RS_AP_00139}
    * @uptrace{RS_Diag_04148}
    */
   ara::core::Result<void> SetDTCStatusChangedNotifier( std::function<void (std::uint32_t dtc, UdsDtcStatusByteType udsStatusByteOld, UdsDtcStatusByteType udsStatusByteNew)> notifier );

   // ToDo : Following methods depend on rb-dm functions which are not implemented.
   // So currently these methods are commented out.
            #if 0 // Not yet supported in VRTE
   /**
    * @brief Register a notifier function which is called if the SnapshotRecord is changed.
    * @param[in] notifier  The function to be called if the SnapshotRecord is changed.
    * @error DiagErrorDomain::DiagErrc::kInvalidArgument given argument is invalid (pointer).
    *
    * @traceid{SWS_DM_00668}@tracestatus{draft}
    * @uptrace{RS_AP_00139}
    * @uptrace{RS_Diag_04205}
    */
   ara::core::Result<void> SetSnapshotRecordUpdatedNotifier( std::function<void (SnapshotRecordUpdatedType)> notifier );

   /**
    * @brief Contains the number of currently stored fault memory entries.
    * @returns Number of currently stored fault memory entries.
    *
    * @traceid{SWS_DM_00669}@tracestatus{draft}
    * @uptrace{RS_AP_00139}
    * @uptrace{RS_Diag_04109}
    */
   ara::core::Result<std::uint32_t> GetNumberOfStoredEntries();

   /**
    * @brief Register a notifier function which is called if the number of currently stored fault memory entries changed.
    * @param[in] notifier  The function to be called if the number of entries for this diagnostic event memory instance has changed.
    * @error DiagErrorDomain::DiagErrc::kInvalidArgument given argument is invalid (pointer).
    *
    * @traceid{SWS_DM_00670}@tracestatus{draft}
    * @uptrace{RS_AP_00139}
    * @uptrace{RS_Diag_04109}
    */
   ara::core::Result<void> SetNumberOfStoredEntriesNotifier( std::function<void (std::uint32_t)> notifier );

   /**
    * @brief Contains the current event memory overflow status.
    * @returns Current status of event memory overflow.
    *
    * @traceid{SWS_DM_00919}@tracestatus{draft}
    * @uptrace{RS_AP_00139}
    * @uptrace{RS_Diag_04093}
    */
   ara::core::Result<bool> GetEventMemoryOverflow();

   /**
    * @brief Register a notifier function which is called if the current event memory overflow status changed.
    * @param[in] notifier  The function to be called if the overflow status for this diagnostic event memory instance has changed.
    * @error DiagErrorDomain::DiagErrc::kInvalidArgument given argument is invalid (pointer).
    * @traceid{SWS_DM_00918}@tracestatus{draft}
    * @uptrace{RS_AP_00139}
    * @uptrace{RS_Diag_04093}
    */
   ara::core::Result<void> SetEventMemoryOverflowNotifier( std::function<void (bool)> notifier );

   /**
    * @brief Method for Clearing a DTC or a group of DTCs.
    * @param[in] DTCGroup  DTC group to be cleared.
    * @returns void or errors
    * @error DiagErrorDomain::DiagErrc::kBusy Busy processing.
    * @error DiagErrorDomain::DiagErrc::kFailed Clear failed.
    * @error DiagErrorDomain::DiagErrc::kMemoryError Memory error reported.
    * @error DiagErrorDomain::DiagErrc::kWrongDtc Wrong DTC group passed.
    *
    * @traceid{SWS_DM_00671}@tracestatus{draft}
    * @uptrace{RS_AP_00119}
    * @uptrace{RS_AP_00139}
    * @uptrace{RS_Diag_04194}
    */
   ara::core::Result<void> Clear( std::uint32_t DTCGroup );

   /**
    * @brief Contains the current status of the ControlDTCStatus
    * @returns The current status of ControlDtcStatus (related to UDS service 0x85)
    *
    * @traceid{SWS_DM_00672}@tracestatus{draft}
    * @uptrace{RS_AP_00139}
    * @uptrace{RS_Diag_04159}
    */
   ara::core::Result<ControlDtcStatusType> GetControlDTCStatus();

   /**
    * @brief Registers a notifier function which is called if the control DTC setting is changed.
    * @param[in] notifier  The function to be called if the ControlDTCStatus (related to UDS service 0x85) for this diagnostic memory instance has changed.
    * @error DiagErrorDomain::DiagErrc::kInvalidArgument given argument is invalid (pointer).
    *
    * @traceid{SWS_DM_00673}@tracestatus{draft}
    * @uptrace{RS_AP_00139}
    * @uptrace{RS_Diag_04159}
    */
   ara::core::Result<void> SetControlDtcStatusNotifier( std::function<void (ControlDtcStatusType)> notifier );

   /**
    * @brief Enforce restoring ControlDTCStatus setting to enabled in case the monitor has some conditions or states demands to do so.
    *
    * @traceid{SWS_DM_00674}@tracestatus{draft}
    * @uptrace{RS_AP_00139}
    * @uptrace{RS_Diag_04159}
    */
   ara::core::Result<void> EnableControlDtc();
            #endif // Not yet supported in VRTE

private:
   DTCInformation() = delete;

   DTCInformation( const DTCInformation& ) = delete;              // non construction-copyable

   DTCInformation& operator=( const DTCInformation& ) = delete;   // non copyable

   std::shared_ptr<ara::diag::internal::DTCInformationImpl> impl; ///< All the implementation details are delegated to this impl object
};

}     //namespace diag

} //namespace ara
#endif //ARA_DIAG_DTC_INFORMATION_H_INCLUDED
