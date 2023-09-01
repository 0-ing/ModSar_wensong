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
#ifndef ARA_DIAG_DYNAMIC_ACCESS_LIST_DIAG_SERVICE_BUILDER_H_INCLUDED
#define ARA_DIAG_DYNAMIC_ACCESS_LIST_DIAG_SERVICE_BUILDER_H_INCLUDED
#if 0 // Not yet supported in VRTE
#include <cstdint>
#include "ara/core/span.h"
#include "ara/core/vector.h"

namespace ara {

namespace diag {

/**
 * @brief Definition of the DynamicAccessListDiagServiceBuilder class, which is used by the application to
 * build a DynamicAccessList
 *
 * @traceid{SWS_DM_01166}@tracestatus{draft}
 * @uptrace{RS_Diag_04251}
 */
class DynamicAccessListDiagServiceBuilder final
{
public:

   /**
    * @brief Type alias of a single diagnostic service pattern element in the DynamicAccessList
    *
    * @traceid{SWS_DM_01167}@tracestatus{draft}
    * @uptrace{RS_Diag_04251}
    */
   using Byte = std::uint8_t;

   /**
    * @brief Type alias of a sequence of diagnostic service pattern elements in the DynamicAccessList
    *
    * @traceid{SWS_DM_01168}@tracestatus{draft}
    * @uptrace{RS_Diag_04251}
    */
   using ByteString = ara::core::Span<Byte>;

   /*!
    * \brief           Represents a single byte value closed range
    */

   /**
    * @brief Type alias of a single diagnostic service pattern element in the DynamicAccessList
    *
    * @traceid{SWS_DM_01182}@tracestatus{draft}
    * @uptrace{RS_Diag_04251}
    */
   class ByteRange final
   {
public:

      /**
       * @brief Constructs a value range
       *
       * @param min The minimum value to match
       * @param The maximum value to match
       *
       * @traceid{SWS_DM_01183}@tracestatus{draft}
       * @uptrace{RS_Diag_04251}
       */
      ByteRange( Byte min, Byte max ) noexcept;

      /**
       * @brief Copy constructor of ByteRange
       *
       * @traceid{SWS_DM_01184}@tracestatus{draft}
       * @uptrace{RS_Diag_04251}
       */
      ByteRange( ByteRange const& other ) noexcept;

      /**
       * @brief Move constructor of ByteRange
       *
       * @traceid{SWS_DM_01185}@tracestatus{draft}
       * @uptrace{RS_Diag_04251}
       */
      ByteRange( ByteRange&& other ) noexcept;

      /**
       * @brief Copy assignment operator of ByteRange
       *
       * @traceid{SWS_DM_01186}@tracestatus{draft}
       * @uptrace{RS_Diag_04251}
       */
      auto operator=( ByteRange const& other ) &->ByteRange &;

      /**
       * @brief Move assignment operator of ByteRange
       *
       * @traceid{SWS_DM_01187}@tracestatus{draft}
       * @uptrace{RS_Diag_04251}
       */
      auto operator=( ByteRange&& other ) &->ByteRange &;

      /**
       * @brief Destructor of ByteRange
       *
       * @returns The the lowest value
       *
       * @traceid{SWS_DM_01188}@tracestatus{draft}
       * @uptrace{RS_Diag_04251}
       */
      ~ByteRange() noexcept;

      /**
       * @brief Reports the lowest value to match
       *
       * @returns The the lowest value
       *
       * @traceid{SWS_DM_01189}@tracestatus{draft}
       * @uptrace{RS_Diag_04251}
       */
      auto GetMin() const noexcept->Byte;

      /**
       * @brief Reports the highest value to match
       *
       * @returns The the highest value
       *
       * @traceid{SWS_DM_01190}@tracestatus{draft}
       * @uptrace{RS_Diag_04251}
       */
      auto GetMax() const noexcept->Byte;
   };

   /**
    * @brief Constructor for DynamicAccessListDiagServiceBuilder
    *
    * @returns The instance of the same object to allow fluent API usage
    *
    * @param value value(s) to be added to the DynamicAccessList
    * @param content Stack holder for serialized DynamicAccessList
    *
    * @traceid{SWS_DM_01169}@tracestatus{draft}
    * @uptrace{RS_Diag_04251}
    */
   template<typename V> DynamicAccessListDiagServiceBuilder( V                                value,
                                                             ara::core::Vector<std::uint8_t>& content ) noexcept;

   /**
    * @brief Move constructor of DynamicAccessListDiagServiceBuilder
    *
    * @param other Object to move-construct from
    *
    * @traceid{SWS_DM_01170}@tracestatus{draft}
    * @uptrace{RS_Diag_04251}
    */
   DynamicAccessListDiagServiceBuilder( DynamicAccessListDiagServiceBuilder&& other ) noexcept;

   /**
    * @brief Copy constructor of DynamicAccessListDiagServiceBuilder cannot be used
    *
    * @param other Object to copy-construct from
    *
    * @traceid{SWS_DM_01171}@tracestatus{draft}
    * @uptrace{RS_Diag_04251}
    */
   DynamicAccessListDiagServiceBuilder( DynamicAccessListDiagServiceBuilder const& other ) = delete;

   /**
    * @brief Copy assignment operator of DynamicAccessListDiagServiceBuilder cannot be used
    *
    * @param other Object to copy-assign from.
    *
    * @traceid{SWS_DM_01172}@tracestatus{draft}
    * @uptrace{RS_Diag_04251}
    */
   auto operator=( DynamicAccessListDiagServiceBuilder const& other )->DynamicAccessListDiagServiceBuilder& = delete;

   /**
    * @brief Move assignment operator of DynamicAccessListDiagServiceBuilder
    *
    * @param other Object to move-assign from.
    *
    * @traceid{SWS_DM_01173}@tracestatus{draft}
    * @uptrace{RS_Diag_04251}
    */
   auto operator=( DynamicAccessListDiagServiceBuilder&& other )->DynamicAccessListDiagServiceBuilder& = delete;

   /**
    * @brief Destructor of DynamicAccessListDiagServiceBuilder
    *
    * @traceid{SWS_DM_01174}@tracestatus{draft}
    * @uptrace{RS_Diag_04251}
    */
   ~DynamicAccessListDiagServiceBuilder() noexcept;

   /**
    * @brief This function is used by the application to add a single byte to a
    * DynamicAccessListPattern
    *
    * @returns The instance of the same object to allow fluent API usage
    *
    * @param value The byte value to add to the DynamicAccessList. The value will be used to check
    * for an exact match during evaluation of the diagnostic service access rights
    *
    * @traceid{SWS_DM_01175}@tracestatus{draft}
    * @uptrace{RS_Diag_04251}
    */
   auto Add( Byte value ) noexcept->DynamicAccessListDiagServiceBuilder &;

   /**
    * @brief This function is used by the application to add a string of bytes to a
    * DynamicAccessListPattern
    *
    * @returns The instance of the same object to allow fluent API usage
    *
    * @param values The byte sequence to add to the DynamicAccessList. The values will be used to check
    * for an exact match during evaluation of the diagnostic service access rights
    *
    * @traceid{SWS_DM_01176}@tracestatus{draft}
    * @uptrace{RS_Diag_04251}
    */
   auto Add( ByteString values ) noexcept->DynamicAccessListDiagServiceBuilder &;

   /**
    * @brief This function is used by the application to add a range of bytes to a
    * DynamicAccessListPattern
    *
    * @returns The instance of the same object to allow fluent API usage
    *
    * @param range The range of byte values to add to the DynamicAccessList. The range will be used to check
    * for a match during evaluation of the diagnostic service access rights
    *
    * @traceid{SWS_DM_01177}@tracestatus{draft}
    * @uptrace{RS_Diag_04251}
    */
   auto Add( ByteRange range ) noexcept->DynamicAccessListDiagServiceBuilder &;

   /**
    * @brief This function is used by the application to define a wildcard, i.e, to define a set
    * of bytes that will be ignored in the DynamicAccessList pattern being created
    *
    * @returns The instance of the same object to allow fluent API usage
    *
    * @param numberOfBytesToIgnore The number of bytes to ignore
    *
    * @traceid{SWS_DM_01178}@tracestatus{draft}
    * @uptrace{RS_Diag_04251}
    */
   auto Any( std::size_t numberOfBytesToIgnore ) noexcept->DynamicAccessListDiagServiceBuilder &;

   /**
    * @brief This function is used by the application to specify a single byte value at the end
    * of the DynamicAccessList pattern
    *
    * @returns void
    *
    * @param value The byte value to end the DynamicAccessList. The value will be used to check
    * for an exact match during evaluation of the diagnostic service access rights
    *
    * @traceid{SWS_DM_01179}@tracestatus{draft}
    * @uptrace{RS_Diag_04251}
    */
   void EndsWith( Byte value ) noexcept;

   /**
    * @brief This function is used by the application to specify a closed range of bytes at the end
    * of the DynamicAccessList pattern
    *
    * @returns void
    *
    * @param range The range of byte values to end the DynamicAccessList. The range will be used to check
    * for a match during evaluation of the diagnostic service access rights
    *
    * @traceid{SWS_DM_01180}@tracestatus{draft}
    * @uptrace{RS_Diag_04251}
    */
   void EndsWith( ByteRange range ) noexcept;

   /**
    * @brief Finalizes building the DynamicAccessList. Must be called before destroying the ServiceBuilder object
    *
    * @returns void
    *
    * @traceid{SWS_DM_01181}@tracestatus{draft}
    * @uptrace{RS_Diag_04251}
    */
   void Build() noexcept;
};

}  // namespace diag

}  // namespace ara

#endif // Not yet supported in VRTE
#endif /* ARA_DIAG_DYNAMIC_ACCESS_LIST_DIAG_SERVICE_BUILDER_H_INCLUDED */
