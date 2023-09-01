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

#ifndef ARA_DIAG_EXTERNAL_AUTHENTICATION_H_INCLUDED
#define ARA_DIAG_EXTERNAL_AUTHENTICATION_H_INCLUDED
#if 0 // Not yet supported in VRTE
#include "ara/core/instance_specifier.h"
#include "ara/core/result.h"
#include "ara/core/vector.h"
#include "ara/diag/client_authentication.h"
#include "ara/diag/meta_info.h"

namespace ara {

namespace diag {

/**
 * @brief Definition of the ExternalAuthentication class, which is used by the application to receive
 * an instance of the ClientAuthentication Class relevant to the specific client
 *
 * @traceid{SWS_DM_01191}@tracestatus{draft}
 * @uptrace{RS_Diag_04251}
 */
class ExternalAuthentication final
{
public:

   /**
    * @brief Alias for tester address
    *
    * @traceid{SWS_DM_01192}@tracestatus{draft}
    * @uptrace{RS_Diag_04251}
    */
   using Address = std::uint16_t;

   /**
    * @brief Constructs the port for authentication of diagnostic clients
    *
    * @param instanceSpecifier InstanceSpecifier to a PortPrototype of a DiagnosticAuthentication service instance in the manifest
    * @param reentrancyType specifies if interface is callable fully- or non-reentrant
    *
    * @traceid{SWS_DM_01193}@tracestatus{draft}
    * @uptrace{RS_Diag_04251}
    */
   explicit ExternalAuthentication( ara::core::InstanceSpecifier instanceSpecifier, ReentrancyType reentrancyType ) noexcept;

   /**
    * @brief Move constructor of ExternalAuthentication
    *
    * @param other Object to move-construct from
    *
    * @traceid{SWS_DM_01194}@tracestatus{draft}
    * @uptrace{RS_Diag_04251}
    */
   ExternalAuthentication( ExternalAuthentication&& other ) noexcept = default;

   /**
    * @brief Move assignment operator of ExternalAuthentication
    *
    * @param other Object to move-assign from.
    *
    * @traceid{SWS_DM_01195}@tracestatus{draft}
    * @uptrace{RS_Diag_04251}
    */
   auto operator=( ExternalAuthentication&& other )& noexcept->ExternalAuthentication& = default;

   /**
    * @brief Copy constructor of ExternalAuthentication
    *
    * @param other Object to copy-construct from
    *
    * @traceid{SWS_DM_01196}@tracestatus{draft}
    * @uptrace{RS_Diag_04251}
    */
   ExternalAuthentication( ExternalAuthentication const& other ) = delete;

   /**
    * @brief Copy assignment operator of ExternalAuthentication
    *
    * @param other Object to copy-assign from.
    *
    * @traceid{SWS_DM_01197}@tracestatus{draft}
    * @uptrace{RS_Diag_04251}
    */
   auto operator=( ExternalAuthentication const& other )->ExternalAuthentication& = delete;

   /**
    * @brief Destructor of DiagnosticServiceDynamicAccessList
    *
    * @traceid{SWS_DM_01198}@tracestatus{draft}
    * @uptrace{RS_Diag_04251}
    */
   ~ExternalAuthentication() noexcept;

   /**
    * @brief This function is used by the application to get the ClientAuthentication Instance
    * that is handling the Authentication State of the Client corresponding to the MetaInfo
    *
    * @returns The diagnostic client associated authentication object or error
    *
    * @param metaInfo The meta information of a diagnostic service port
    *
    * @traceid{SWS_DM_01199}@tracestatus{draft}
    * @uptrace{RS_Diag_04251}
    */
   ara::core::Result<ClientAuthentication> Get( ara::diag::MetaInfo& metaInfo ) noexcept;

   /**
    * @brief This function is used by the application to get the ClientAuthentication
    * Instance that is handling the Authentication State of the Client corresponding to the Address
    *
    * @returns The associated diagnostic client authentication object or error
    *
    * @param sourceAddress The source address of the client
    *
    * @traceid{SWS_DM_01200}@tracestatus{draft}
    * @uptrace{RS_Diag_04251}
    */
   ara::core::Result<ClientAuthentication> Get( Address sourceAddress ) noexcept;

   /**
    * @brief This function is used by the application to get all the ClientAuthentication
    * Instances that are currently handled by the DM
    *
    * @returns The list of all diagnostic client associated authentication objects or
    * empty list if none available.
    *
    * @traceid{SWS_DM_01201}@tracestatus{draft}
    * @uptrace{RS_Diag_04251}
    */
   ara::core::Vector<ClientAuthentication> GetAll() noexcept;
};

}  // namespace diag

}  // namespace ara

#endif // Not yet supported in VRTE
#endif /* ARA_DIAG_EXTERNAL_AUTHENTICATION_H_INCLUDED */
