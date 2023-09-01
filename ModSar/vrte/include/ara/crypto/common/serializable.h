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

/// @file
/// @brief Adaptive Autosar Crypto Stack. Cryptographic API. Serializable interface definition.

#ifndef ARA_CRYPTO_COMMON_SERIALIZABLE_H_
#define ARA_CRYPTO_COMMON_SERIALIZABLE_H_

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "ara/core/result.h"
#include "ara/crypto/common/base_id_types.h"
#include "ara/crypto/common/mem_region.h"

namespace ara
{
namespace crypto
{
//- @interface Serializable
///
/// @traceid{SWS_CRYPT_10700}@tracestatus{draft}
/// @uptrace{RS_CRYPTO_02105}
/// @brief Serializable object interface.
///
///
class Serializable
{
public:
    /// @traceid{SWS_CRYPT_10710}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02004}
    /// @uptrace{RS_CRYPTO_02302}
    /// @brief Destructor.
    virtual ~Serializable() noexcept = default;

    /// @traceid{SWS_CRYPT_30204}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02004}
    /// @brief Copy-assign another Serializable to this instance.
    /// @param other  the other instance
    /// @returns *this, containing the contents of @a other
    Serializable& operator=(const Serializable& other) = default;

    /// @traceid{SWS_CRYPT_30205}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02004}
    /// @brief Move-assign another Serializable to this instance.
    /// @param other  the other instance
    /// @returns *this, containing the contents of @a other
    Serializable& operator=(Serializable&& other) = default;

    Serializable(const Serializable& other) = default;
    Serializable(Serializable&& other) = default;
    Serializable() = default;

    /// @traceid{SWS_CRYPT_10701}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02004}
    /// @uptrace{RS_CRYPTO_02302}
    /// @brief A container type for the encoding format identifiers.
    ///
    using FormatId = std::uint32_t;

    /// @traceid{SWS_CRYPT_10750}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02004}
    /// @uptrace{RS_CRYPTO_02302}
    /// @brief Default serialization format.
    ///
    static const FormatId kFormatDefault = 0;

    /// @traceid{SWS_CRYPT_10751}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02004}
    /// @uptrace{RS_CRYPTO_02302}
    /// @brief Export only raw value of an object.
    ///
    static const FormatId kFormatRawValueOnly = 1;

    /// @traceid{SWS_CRYPT_10752}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02004}
    /// @uptrace{RS_CRYPTO_02302}
    /// @brief Export DER-encoded value of an object.
    ///
    static const FormatId kFormatDerEncoded = 2;

    /// @traceid{SWS_CRYPT_10753}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02004}
    /// @uptrace{RS_CRYPTO_02302}
    /// @brief Export PEM-encoded value of an object.
    ///
    static const FormatId kFormatPemEncoded = 3;

    /// @}  // Predefined encoding format identifiers

    /// @traceid{SWS_CRYPT_10711}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02112}
    /// @brief Serialize itself publicly.
    /// @param[in] formatId  the Crypto Provider specific identifier of the output format
    /// @returns a buffer with the serialized object
    /// @error SecurityErrorDomain::kInsufficientCapacity
    ///         if <tt>(output.empty() == false)</tt>, but it's capacity is less than required
    /// @error SecurityErrorDomain::kUnknownIdentifier  if an unknown format ID was specified
    /// @error SecurityErrorDomain::kUnsupportedFormat
    ///         if the specified format ID is not supported for this object type
    /// @threadsafety{Thread-safe}
    ///
    virtual ara::core::Result<ara::core::Vector<ara::core::Byte>>
    ExportPublicly(FormatId formatId = kFormatDefault) const noexcept = 0;

    /// @traceid{SWS_CRYPT_10712}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02112}
    /// @brief Serialize itself publicly.
    ///     This method sets the size of the output container according to actually saved value!
    /// @tparam Alloc custom allocator type of the output container
    /// @returns  pre-reserved managed container for the serialization output
    /// @param[in] formatId  the Crypto Provider specific identifier of the output format
    /// @error SecurityErrorDomain::kInsufficientCapacity
    ///         if capacity of the output buffer is less than required
    /// @error SecurityErrorDomain::kUnknownIdentifier  if an unknown format ID was specified
    /// @error SecurityErrorDomain::kUnsupportedFormat
    ///         if the specified format ID is not supported for this object type
    /// @threadsafety{Thread-safe}
    ///
//    template<typename Alloc = VENDOR_IMPLEMENTATION_DEFINED>
//    ara::core::Result<ByteVector<Alloc>>
//    ExportPublicly(FormatId formatId = kFormatDefault) const noexcept
//    {
        //    	auto result = ExportPublicly(formatId);
        //        if (result)
        //        {
        //            ByteVector<Alloc> output;
        //            output.resize(result.Value().size());
        //            memcpy(core::data(output), result.Value().data(), result.Value().size());
        //            return ara::core::Result<ByteVector<Alloc>>::FromValue(output);
        //        }
        //        else
        //        {
        //            return ara::core::Result<ByteVector<Alloc>>::FromError(result.Error());
        //        }
//    }
};

} // namespace crypto
} // namespace ara

#endif // ARA_CRYPTO_COMMON_SERIALIZABLE_H_
