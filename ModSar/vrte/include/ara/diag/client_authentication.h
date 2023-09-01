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
#ifndef ARA_DIAG_CLIENT_AUTHENTICATION_H_INCLUDED
#define ARA_DIAG_CLIENT_AUTHENTICATION_H_INCLUDED
#if 0 // Not yet supported in VRTE
#include <chrono>
#include "ara/core/result.h"
#include "ara/core/string.h"
#include "ara/diag/client_authentication_handle.h"

namespace ara {

namespace diag {

/**
 * @brief Interface for the application to inform the Diagnostic Server instance about the authentication
 * states and the user roles that are currently authenticated
 *
 * @traceid{SWS_DM_01132}@tracestatus{draft}
 * @uptrace{RS_Diag_04251}
 */
class ClientAuthentication final
{
public:

   /**
    * @brief Possible values of the Authentication State of the client
    *
    * @traceid{SWS_DM_01133}@tracestatus{draft}
    * @uptrace{RS_Diag_04251}
    */
   enum class DiagnosticAuthState : std::uint8_t
   {
      kDeAuthenticated = 0x00,      ///< No Diagnostic Clients are currently authenticated
      kAuthenticated   = 0x01       ///< A Diagnostic Client is currently authen ticated
   };

   /**
    * @brief The Supported values for the Diagnostic Authentication roles are specified in the Diagnostic Extract
    *
    * @traceid{SWS_DM_01134}@tracestatus{draft}
    * @uptrace{RS_Diag_04251}
    */
   using DiagnosticAuthRole = ara::core::String;

   /**
    * @brief Destructor of ClientAuthentication
    *
    * @traceid{SWS_DM_01136}@tracestatus{draft}
    * @uptrace{RS_Diag_04251}
    */
   virtual ~ClientAuthentication() noexcept = default;

   /**
    * @brief Move constructor of ClientAuthentication
    *
    * @param other Object to move-construct from
    *
    * @traceid{SWS_DM_01137}@tracestatus{draft}
    * @uptrace{RS_Diag_04251}
    */
   ClientAuthentication( ClientAuthentication&& other ) noexcept = default;

   /**
    * @brief Move assignment operator of ClientAuthentication
    *
    * @param other Object to move-assign from.
    *
    * @traceid{SWS_DM_01138}@tracestatus{draft}
    * @uptrace{RS_Diag_04251}
    */
   auto operator=( ClientAuthentication&& other )& noexcept->ClientAuthentication& = default;

   /**
    * @brief Copy constructor of ClientAuthentication cannot be used
    *
    * @param other Object to copy-construct from
    *
    * @traceid{SWS_DM_01139}@tracestatus{draft}
    * @uptrace{RS_Diag_04251}
    */
   ClientAuthentication( ClientAuthentication const& other ) = delete;

   /**
    * @brief Copy assignment operator of ClientAuthentication cannot be used
    *
    * @param other Object to copy-assign from.
    *
    * @traceid{SWS_DM_01140}@tracestatus{draft}
    * @uptrace{RS_Diag_04251}
    */
   auto operator=( ClientAuthentication const& other )->ClientAuthentication& = delete;

   /**
    * @brief This method is used by the application to temporarily change the default AuthenticationRole for a
    * Diagnostic Server Instance. The diagnostic services allowed in the passed defaultRoles are now accessible
    * to the tester for a time period defined in the parameter timeout
    *
    * @returns Operation result
    *
    * @param defaultRoles The default roles requested by the application, to be set on the diagnostic client
    * @param timeout The timeout until which the override request is active
    *
    * @traceid{SWS_DM_01141}@tracestatus{draft}
    * @uptrace{RS_Diag_04251}
    */
   ara::core::Result<ClientAuthenticationHandle> OverrideDefaultRoles( ara::core::Vector<DiagnosticAuthRole> defaultRoles,
                                                                       std::chrono::milliseconds             timeout );

   /**
    * @brief This function is used by the application to report the authenticated state to the Diagnostic Server instance.
    * The authentication could be either done using the Authentication interfaces of the Diagnostic Server instance,
    * or through other means in the application
    *
    * @returns A handler of the Authentication State, which can be used by the application to set or extend the DynamicAccessList
    *
    * @param userRoles The user roles to set on the diagnostic client
    *
    * @traceid{SWS_DM_01142}@tracestatus{draft}
    * @uptrace{RS_Diag_04251}
    */
   ara::core::Result<ClientAuthenticationHandle> Authenticate( ara::core::Vector<DiagnosticAuthRole> userRoles );

   /**
    * @brief This function is used by the application to query the current authentication state of the diagnostic client
    *
    * @returns The Authentication State of the Diagnostic Client or error
    *
    * @traceid{SWS_DM_01143}@tracestatus{draft}
    * @uptrace{RS_Diag_04251}
    */
   ara::core::Result<DiagnosticAuthState> GetState() const noexcept;

   /**
    * @brief This function is used by the application to set a Notifier Function that shall be called by the
    * Diagnostic Server instance when an Authentication Status Change Occurs. This may be used, for. E.g, to notify
    * the application when a transition to kDeAuthenticated  State occurred due to an S3 timeout
    *
    * @returns void
    *
    * @param notifier The notifier to call on state transition
    *
    * @traceid{SWS_DM_01144}@tracestatus{draft}
    * @uptrace{RS_Diag_04251}
    */
   ara::core::Result<void> SetNotifier( std::function<void (DiagnosticAuthState)> notifier ) noexcept;
};

}  // namespace diag

}  // namespace ara

#endif // Not yet supported in VRTE
#endif /* ARA_DIAG_CLIENT_AUTHENTICATION_H_INCLUDED */
