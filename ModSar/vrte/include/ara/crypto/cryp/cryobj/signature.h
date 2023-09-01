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
/// @brief Adaptive Autosar Crypto Stack. Cryptographic API. Signature interface definition.

#ifndef ARA_CRYPTO_CRYP_SIGNATURE_H_
#define ARA_CRYPTO_CRYP_SIGNATURE_H_

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "ara/crypto/common/base_id_types.h"
#include "ara/crypto/common/serializable.h"
#include "ara/crypto/cryp/cryobj/crypto_object.h"
#include "ara/crypto/cryp/cryobj/crypto_primitive_id.h"

namespace ara
{
namespace crypto
{
namespace cryp
{
//- @interface Signature
///
/// @traceid{SWS_CRYPT_23300}@tracestatus{draft}
/// @uptrace{RS_CRYPTO_02203}
/// @uptrace{RS_CRYPTO_02204}
/// @uptrace{RS_CRYPTO_02205}
/// @brief Signature container interface
///       This interface is applicable for keeping the Digital Signature, Hash Digest, (Hash-based)
///       Message Authentication Code (MAC/HMAC). In case of a keyed signature (Digital Signature or
///       MAC/HMAC) a @a COUID of the signature verification key can be obtained by a call of @c
///       CryptoObject::HasDependence()!
class Signature : public CryptoObject, public Serializable
{
public:
    /// @traceid{SWS_CRYPT_23302}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02204}
    /// @uptrace{RS_CRYPTO_02203}
    /// @uptrace{RS_CRYPTO_02205}
    /// @brief Signature object initialized
    static const CryptoObjectType kObjectType = CryptoObjectType::kSignature;

    /// @traceid{SWS_CRYPT_23301}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02204}
    /// @uptrace{RS_CRYPTO_02203}
    /// @uptrace{RS_CRYPTO_02205}
    /// @brief Unique smart pointer of the interface
    using Uptrc = std::unique_ptr<const Signature>;

    /// @traceid{SWS_CRYPT_23311}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02204}
    /// @uptrace{RS_CRYPTO_02203}
    /// @uptrace{RS_CRYPTO_02205}
    /// @brief Get an ID of hash algorithm used for this signature object production.
    /// @returns ID of used hash algorithm only (without signature algorithm specification)
    /// @threadsafety{Thread-safe}
    virtual CryptoPrimitiveId::AlgId GetHashAlgId() const noexcept = 0;

    /// @traceid{SWS_CRYPT_23312}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02309}
    /// @brief Get the hash size required by current signature algorithm.
    /// @returns required hash size in bytes
    virtual std::size_t GetRequiredHashSize() const noexcept = 0;
};

} // namespace cryp
} // namespace crypto
} // namespace ara

#endif // ARA_CRYPTO_CRYP_SIGNATURE_H_
