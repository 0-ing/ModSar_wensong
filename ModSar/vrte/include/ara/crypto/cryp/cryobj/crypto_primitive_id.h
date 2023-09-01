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
/// @brief Adaptive Autosar Crypto Stack. Cryptographic API. CryptoPrimitiveId interface definition.

#ifndef ARA_CRYPTO_CRYP_CRYPTO_PRIMITIVE_ID_H_
#define ARA_CRYPTO_CRYP_CRYPTO_PRIMITIVE_ID_H_

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "ara/core/string_view.h"
#include "ara/crypto/common/base_id_types.h"
#include <memory>

namespace ara
{
namespace crypto
{
namespace cryp
{
// Forward declaration of the Crypto Provider interface.
class CryptoProvider;

//- @interface CryptoPrimitiveId
///
/// @traceid{SWS_CRYPT_20600}@tracestatus{draft}
/// @uptrace{RS_CRYPTO_02005}
/// @brief Common interface for identification of all Crypto Primitives and their keys & parameters.
///

class CryptoPrimitiveId
{
public:
    /// @traceid{SWS_CRYPT_10808}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02005}
    /// @brief Destructor.
    virtual ~CryptoPrimitiveId() noexcept = default;

    /// @traceid{SWS_CRYPT_30212}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02004}
    /// @brief Copy-assign another CryptoPrimitiveId to this instance.
    /// @param other  the other instance
    /// @returns *this, containing the contents of @a other
    CryptoPrimitiveId& operator=(const CryptoPrimitiveId& other) = default;

    /// @traceid{SWS_CRYPT_30213}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02004}
    /// @brief Move-assign another CryptoPrimitiveId to this instance.
    /// @param other  the other instance
    /// @returns *this, containing the contents of @a other
    CryptoPrimitiveId& operator=(CryptoPrimitiveId&& other) = default;

    CryptoPrimitiveId(const CryptoPrimitiveId& other) = default;
    CryptoPrimitiveId(CryptoPrimitiveId&& other) = default;
    CryptoPrimitiveId() = default;

    /// @traceid{SWS_CRYPT_20641}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02005}
    /// @brief Type definition of vendor specific binary Crypto Primitive ID.
    using AlgId = CryptoAlgId;

    /// @traceid{SWS_CRYPT_20643}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02005}
    /// @brief type definition pointer to const

    using Uptr = std::unique_ptr<CryptoPrimitiveId>;

    /// @traceid{SWS_CRYPT_20644}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02005}
    /// @brief type definition pointer
    using Uptrc = std::unique_ptr<const CryptoPrimitiveId>;

    /// @traceid{SWS_CRYPT_20651}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02308}
    /// @brief Get a unified name of the primitive.
    ///     The crypto primitive name can be fully or partially specified (see "Crypto Primitives
    ///     Naming Convention"
    ///       for more details).
    ///     The life-time of the returned @c StringView instance should not exceed the life-time of
    ///     this
    ///       @c CryptoPrimitiveId instance!
    /// @returns the unified name of the crypto primitive

    /// @threadsafety{Thread-safe}

    virtual const ara::core::StringView GetPrimitiveName() const noexcept = 0;

    /// @traceid{SWS_CRYPT_20652}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02309}
    /// @brief Get vendor specific ID of the primitive.
    /// @returns the binary Crypto Primitive ID
    /// @threadsafety{Thread-safe}

    virtual AlgId GetPrimitiveId() const noexcept = 0;
};

} // namespace cryp
} // namespace crypto
} // namespace ara

#endif // ARA_CRYPTO_CRYP_CRYPTO_PRIMITIVE_ID_H_
