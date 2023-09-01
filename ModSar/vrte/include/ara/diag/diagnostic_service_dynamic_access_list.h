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
#ifndef ARA_DIAG_DIAGNOSTIC_SERVICE_DYNAMIC_ACCESS_LIST_H_INCLUDED
#define ARA_DIAG_DIAGNOSTIC_SERVICE_DYNAMIC_ACCESS_LIST_H_INCLUDED
#if 0 // Not yet supported in VRTE
#include <memory>
#include "ara/core/vector.h"
#include "ara/diag/dynamic_access_list_diag_service_builder.h"

namespace ara {

namespace diag {

/**
 * @brief Definition of the DiagnosticServiceDynamicAccessList class, which is used by the
 * application to build a DynamicAccessList
 *
 * @traceid{SWS_DM_01156}@tracestatus{draft}
 * @uptrace{RS_Diag_04251}
 */
class DiagnosticServiceDynamicAccessList final
{
public:

   /**
    * @brief Constructor of DiagnosticServiceDynamicAccessList
    *
    * @traceid{SWS_DM_01157}@tracestatus{draft}
    * @uptrace{RS_Diag_04251}
    */
   DiagnosticServiceDynamicAccessList();

   /**
    * @brief Destructor of DiagnosticServiceDynamicAccessList
    *
    * @traceid{SWS_DM_01158}@tracestatus{draft}
    * @uptrace{RS_Diag_04251}
    */
   virtual ~DiagnosticServiceDynamicAccessList() noexcept = default;

   /**
    * @brief Copy constructor of DiagnosticServiceDynamicAccessList
    *
    * @param other Object to copy-construct from
    *
    * @traceid{SWS_DM_01159}@tracestatus{draft}
    * @uptrace{RS_Diag_04251}
    */
   DiagnosticServiceDynamicAccessList( DiagnosticServiceDynamicAccessList const& other ) noexcept;

   /**
    * @brief Move constructor of DiagnosticServiceDynamicAccessList
    *
    * @param other Object to move-construct from
    *
    * @traceid{SWS_DM_01160}@tracestatus{draft}
    * @uptrace{RS_Diag_04251}
    */
   DiagnosticServiceDynamicAccessList( DiagnosticServiceDynamicAccessList&& other ) noexcept;

   /**
    * @brief Copy assignment operator of DiagnosticServiceDynamicAccessList
    *
    * @param other Object to copy-assign from.
    *
    * @traceid{SWS_DM_01161}@tracestatus{draft}
    * @uptrace{RS_Diag_04251}
    */
   auto operator=( DiagnosticServiceDynamicAccessList const& other ) &->DiagnosticServiceDynamicAccessList &;

   /**
    * @brief Move assignment operator of DiagnosticServiceDynamicAccessList
    *
    * @param other Object to move-assign from.
    *
    * @traceid{SWS_DM_01162}@tracestatus{draft}
    * @uptrace{RS_Diag_04251}
    */
   auto operator=( DiagnosticServiceDynamicAccessList&& other ) &->DiagnosticServiceDynamicAccessList &;

   /**
    * @brief Preallocates memory for all service heads to fit into the DynamicAccessList.
    * The preallocation can be just estimated and may calculate just the worst case of memory needed,
    * not exact memory size needed for data numberOfServiceHeads
    *
    * @returns void
    *
    * @param numberOfServiceHeads The number of diagnostic service patterns
    * @param maxServiceHeadSize The expected maximum number of diagnostic service bytes in a single pattern
    *
    * @traceid{SWS_DM_01163}@tracestatus{draft}
    * @uptrace{RS_Diag_04251}
    */
   void Reserve( std::size_t numberOfServiceHeads,
                 std::size_t maxServiceHeadSize ) noexcept;

   /**
    * @brief This function is used by the Application to construct a pattern for the DynamicAccessList using
    * only the SID
    *
    * @returns An instance of a diagnostic service pattern builder
    *
    * @param sid The diagnostic service identifier
    *
    * @traceid{SWS_DM_01164}@tracestatus{draft}
    * @uptrace{RS_Diag_04251}
    */
   auto MakeServiceBuilder( DynamicAccessListDiagServiceBuilder::Byte sid ) noexcept->DynamicAccessListDiagServiceBuilder;

   /**
    * @brief This function is used by the Application to construct a pattern for the DynamicAccessList using a string of
    * bytes
    *
    * @returns An instance of a diagnostic service pattern builder
    *
    * @param serviceHead A string of bytes to start the DynamicAccess pattern-match
    *
    * @traceid{SWS_DM_01165}@tracestatus{draft}
    * @uptrace{RS_Diag_04251}
    */
   auto MakeServiceBuilder( DynamicAccessListDiagServiceBuilder::ByteString serviceHead ) noexcept->DynamicAccessListDiagServiceBuilder;
};

}  // namespace diag

}  // namespace ara

#endif // Not yet supported in VRTE
#endif /* ARA_DIAG_DIAGNOSTIC_SERVICE_DYNAMIC_ACCESS_LIST_H_INCLUDED */
