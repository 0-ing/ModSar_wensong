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
#ifndef ARA_DIAG_CLIENT_AUTHENTICATION_HANDLE_H_INCLUDED
#define ARA_DIAG_CLIENT_AUTHENTICATION_HANDLE_H_INCLUDED
#if 0 // Not yet supported in VRTE
#include "ara/diag/diagnostic_service_dynamic_access_list.h"
#include "ara/core/result.h"

namespace ara {

namespace diag {

/**
 * @brief Definition of the ClientAuthenticationHandle which is returned to the application when
 * an AuthenticationState is set by the application
 *
 * @traceid{SWS_DM_01145}@tracestatus{draft}
 * @uptrace{RS_Diag_04251}
 */
class ClientAuthenticationHandle final
{
public:

   /**
    * @brief Constructor of ClientAuthenticationHandle
    *
    * @traceid{SWS_DM_01146}@tracestatus{draft}
    * @uptrace{RS_Diag_04251}
    */
   ClientAuthenticationHandle();

   /**
    * @brief Destructor of ClientAuthenticationHandle
    *
    * @traceid{SWS_DM_01147}@tracestatus{draft}
    * @uptrace{RS_Diag_04251}
    */
   virtual ~ClientAuthenticationHandle() noexcept = default;

   /**
    * @brief Move constructor of ClientAuthenticationHandle
    *
    * @param other Object to move-construct from
    *
    * @traceid{SWS_DM_01148}@tracestatus{draft}
    * @uptrace{RS_Diag_04251}
    */
   ClientAuthenticationHandle( ClientAuthenticationHandle&& other ) noexcept = default;

   /**
    * @brief Move assignment operator of ClientAuthenticationHandle
    *
    * @param other Object to move-assign from.
    *
    * @traceid{SWS_DM_01149}@tracestatus{draft}
    * @uptrace{RS_Diag_04251}
    */
   auto operator=( ClientAuthenticationHandle&& other )& noexcept->ClientAuthenticationHandle& = default;

   /**
    * @brief Copy constructor of ClientAuthenticationHandle cannot be used
    *
    * @param other Object to copy-construct from
    *
    * @traceid{SWS_DM_01150}@tracestatus{draft}
    * @uptrace{RS_Diag_04251}
    */
   ClientAuthenticationHandle( ClientAuthenticationHandle const& other ) = delete;

   /**
    * @brief Copy assignment operator of CancellationHandler cannot be used
    *
    * @param other Object to copy-assign from.
    *
    * @traceid{SWS_DM_01151}@tracestatus{draft}
    * @uptrace{RS_Diag_04251}
    */
   auto operator=( ClientAuthenticationHandle const& other )->ClientAuthenticationHandle& = delete;

   /**
    * @brief This function is used by the application to append a DynamicAccessList to the already
    * existing DynamicAccessList of a Diagnostic Conversation
    *
    * @returns void
    *
    * @param DynamicAccessList The DynamicAccessList to be appended in the client
    *
    * @traceid{SWS_DM_01152}@tracestatus{draft}
    * @uptrace{RS_Diag_04251}
    */
   ara::core::Result<void> Append( DiagnosticServiceDynamicAccessList DynamicAccessList ) noexcept;

   /**
    * @brief This function is used by the application to set/replace a DynamicAccessList  of  a
    * diagnostic conversation
    *
    * @returns void
    *
    * @param DynamicAccessList The new DynamicAccessList to be set in the client
    *
    * @traceid{SWS_DM_01153}@tracestatus{draft}
    * @uptrace{RS_Diag_04251}
    */
   ara::core::Result<void> Set( DiagnosticServiceDynamicAccessList DynamicAccessList ) noexcept;

   /**
    * @brief This function is used by the application to de-authenticate a client, and also to clear
    * the DynamicAccessList and any overridden defaults
    *
    * @returns void
    *
    * @traceid{SWS_DM_01154}@tracestatus{draft}
    * @uptrace{RS_Diag_04251}
    */
   ara::core::Result<void> Revoke() noexcept;

   /**
    * @brief This function is used by the application to refresh the timer that was started by Authenticate or
    * OverrideDefaultRoles. If both Methods were previously called, both timers are refreshed
    *
    * @returns void
    *
    * @traceid{SWS_DM_01155}@tracestatus{draft}
    * @uptrace{RS_Diag_04251}
    */
   ara::core::Result<void> Refresh() noexcept;
};

}  // namespace diag

}  // namespace ara

#endif // Not yet supported in VRTE
#endif /* ARA_DIAG_CLIENT_AUTHENTICATION_HANDLE_H_INCLUDED */
