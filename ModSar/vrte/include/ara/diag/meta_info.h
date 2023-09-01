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
#ifndef ARA_DIAG_META_INFO_H_INCLUDED
#define ARA_DIAG_META_INFO_H_INCLUDED

#include <ara/core/optional.h>
#include <ara/core/string_view.h>
#include <cstdint>

namespace ara {

namespace diag {

/**
 * @brief Metainfo interface
 *
 * @traceid{SWS_DM_00971}@tracestatus{draft}
 * @uptrace{RS_Diag_04170}
 */
class MetaInfo final
{
public:

   /**
    * @brief Constructor of MetaInfo cannot be used
    *
    * @traceid{SWS_DM_00972}@tracestatus{draft}
    * @uptrace{RS_Diag_04170}
    */
   MetaInfo() noexcept = delete;

   /**
    * @brief Copy Constructor of MetaInfo cannot be used
    *
    * @traceid{SWS_DM_00973}@tracestatus{draft}
    * @uptrace{RS_Diag_04170}
    */
   MetaInfo( const MetaInfo& ) = delete;

   /**
    * @brief Move Constructor of MetaInfo
    *
    * @traceid{SWS_DM_00974}@tracestatus{draft}
    * @param obj object to be moved
    * @uptrace{RS_Diag_04170}
    */
   MetaInfo( MetaInfo&& obj ) noexcept = default;

   /**
    * @brief Copy Assignment Operator of MetaInfo cannot be used
    *
    * @traceid{SWS_DM_00975}@tracestatus{draft}
    * @uptrace{RS_Diag_04170}
    */
   MetaInfo& operator=( const MetaInfo& ) = delete;

   /**
    * @brief Move Assignment Operator of MetaInfo
    *
    * @traceid{SWS_DM_00976}@tracestatus{draft}
    * @param other MetaInfo instance
    * @return Reference to the current object
    * @uptrace{RS_Diag_04170}
    */
   MetaInfo& operator=( MetaInfo&& other )& noexcept = default;

   /**
    * @brief Definition of possible call context
    *
    * @traceid{SWS_DM_00977}@tracestatus{draft}
    * @uptrace{RS_Diag_04170}
    */
   enum class Context : std::uint32_t
   {
      kDiagnosticCommunication, ///< service request in DCM context
      kFaultMemory,             ///< for DIDs in Snapshots
      kDoIP                     ///< for reading VIN
   };

            #if 0 // Not yet supported in VRTE
   /**
    * @brief Get the metainfo value for a given key
    *
    * @param key identification of value to be returned
    * @returns Returns value for the given key.
    *
    * @traceid{SWS_DM_00978}@tracestatus{draft}
    * @uptrace{RS_Diag_04170}
    */
   ara::core::Optional<ara::core::StringView> GetValue( ara::core::StringView key ) const noexcept;
            #endif // Not yet supported in VRTE

            #if 0 // Not yet supported in VRTE
   /**
    * @brief Get the context of the invocation
    * @returns Returns the context.
    *
    * @traceid{SWS_DM_00979}@tracestatus{draft}
    * @uptrace{RS_Diag_04170}
    */
   Context GetContext() const noexcept;
            #endif // Not yet supported in VRTE

   /**
    * @brief Default destructor
    *
    * @traceid{SWS_DM_00980}@tracestatus{draft}
    * @uptrace{RS_Diag_04170}
    */
   ~MetaInfo() noexcept = default;
};

}     //namespace diag

} //namespace ara

#endif //ARA_DIAG_META_INFO_H_INCLUDED
