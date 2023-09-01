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

#ifndef ARA_DIAG_CANCELLATION_HANDLER_H_
#define ARA_DIAG_CANCELLATION_HANDLER_H_

#include <functional>
#include <memory>

namespace ara {

namespace diag {

// Hide implementation details by forward declaration
namespace internal {

class CancellationHandlerImpl;

}

/**
 * @brief CancellationHandler contains a shared state if the processing should be canceled
 * @traceid{SWS_DM_00608}@tracestatus{draft}
 * @uptrace{RS_Diag_04169}
 */
class CancellationHandler final
{
public:

   /**
    * @brief Constructor of CancellationHandler cannot be used
    *
    * @traceid{SWS_DM_00609}@tracestatus{draft}
    * @uptrace{RS_Diag_04169}
    */
   CancellationHandler() = delete;

   /**
    * @brief Move constructor of CancellationHandler
    *
    * @traceid{SWS_DM_00610}@tracestatus{draft}
    * @uptrace{RS_AP_00133}
    * @uptrace{RS_Diag_04169}
    */
   CancellationHandler( CancellationHandler&& ) noexcept = default;

   /**
    * @brief Copy constructor of CancellationHandler cannot be used
    *
    * @traceid{SWS_DM_00611}@tracestatus{draft}
    * @uptrace{RS_Diag_04169}
    */
   CancellationHandler( CancellationHandler& ) = delete;

   /**
    * @brief Move assignment operator of CancellationHandler
    *
    * @traceid{SWS_DM_00612}@tracestatus{draft}
    * @uptrace{RS_AP_00133}
    * @uptrace{RS_Diag_04169}
    */
   CancellationHandler& operator=( CancellationHandler&& ) noexcept = default;

   /**
    * @brief Copy assignment operator of CancellationHandler cannot be used
    *
    * @traceid{SWS_DM_00613}@tracestatus{draft}
    * @uptrace{RS_Diag_04169}
    */
   CancellationHandler& operator=( CancellationHandler& ) = delete;

   /**
    * @brief Returns true in if the diagnostic service execution is cancelled in DM.
    *
    * @traceid{SWS_DM_00614}@tracestatus{draft}
    * @uptrace{RS_Diag_04169}
    */
   bool IsCanceled() const;

   /**
    * @brief Regisering a notifier function which is called if the diagnostic service execution is canceled in DM.
    *
    * @traceid{SWS_DM_00615}@tracestatus{draft}
    * @uptrace{RS_Diag_04169}
    */
   void SetNotifier( std::function<void (void)> notifier );

// Do not access except for the implementation class.
// private:
//    friend class                                  ara::diag::internal::CancellationHandlerImpl;
   std::shared_ptr<ara::diag::internal::CancellationHandlerImpl> m_impl { nullptr };
};

}  // namespace diag

}  // namespace ara

#endif
