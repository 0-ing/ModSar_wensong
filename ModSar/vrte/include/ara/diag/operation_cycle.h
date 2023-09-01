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
#ifndef ARA_DIAG_OPERATION_CYCLE_H_INCLUDED
#define ARA_DIAG_OPERATION_CYCLE_H_INCLUDED

#include <ara/core/future.h>
#include <ara/core/instance_specifier.h>
#include <ara/core/result.h>

#include <functional>
#include <memory>

namespace ara {

namespace diag {

namespace internal {

class OperationCycleImpl;

} // namespace internal

/**
 * @brief DiagnosticOperationCycleInterface provides functionality for handling of operation cycles.
 *
 * @traceid{SWS_DM_00751}@tracestatus{draft}
 * @uptrace{RS_Diag_04178}
 */
class OperationCycle
{
public:

   /**
    * @brief Constructor for DiagnosticOperationCycleInterface
    * @param specifier InstanceSpecifier to an PortPrototype of an DiagnosticOperationCycleInterface
    *
    * @traceid{SWS_DM_00752}@tracestatus{draft}
    * @uptrace{RS_AP_00137}
    * @uptrace{RS_Diag_04178}
    */
   explicit OperationCycle( const ara::core::InstanceSpecifier& specifier );

   /**
    * @brief Destructor of DiagnosticOperationCycleInterface
    *
    * @traceid{SWS_DM_00753}@tracestatus{draft}
    * @uptrace{RS_AP_00134}
    * @uptrace{RS_Diag_04178}
    */
   ~OperationCycle() noexcept;

   /**
    * @brief Registering a notifier function which is called if the operation cycle is changed.
    *
    * @traceid{SWS_DM_00755}@tracestatus{draft}
    * @uptrace{RS_AP_00139}
    * @uptrace{RS_Diag_04178}
    * @uptrace{RS_Diag_04186}
    */
   ara::core::Result<void> SetNotifier( std::function<void (void)> notifier );

   /**
    * @brief Trigger to restart the OperationCycle
    *
    * @traceid{SWS_DM_01102}@tracestatus{draft}
    * @uptrace{RS_AP_00139}
    * @uptrace{RS_Diag_04178}
    * @uptrace{RS_Diag_04182}
    */
   ara::core::Result<void> RestartOperationCycle();

private:
   OperationCycle() = delete;

   OperationCycle( const OperationCycle& ) = delete;            // non construction-copyable

   OperationCycle& operator=( const OperationCycle& ) = delete; // non copyable


   OperationCycle( const OperationCycle&& ) = delete;

   OperationCycle& operator=( const OperationCycle&& ) = delete;

   std::unique_ptr<ara::diag::internal::OperationCycleImpl> impl;
};

}     //namespace diag

} //namespace ara

#endif //ARA_DIAG_OPERATION_CYCLE_H_INCLUDED
