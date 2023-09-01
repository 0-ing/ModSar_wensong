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
/// @brief Adaptive Autosar Crypto Stack. Cryptographic API. KeyAgreementPrivateCtx interface definition.

#ifndef ARA_CRYPTO_CRYP_KEY_AGREEMENT_PRIVATE_CTX_H_
#define ARA_CRYPTO_CRYP_KEY_AGREEMENT_PRIVATE_CTX_H_

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "ara/crypto/common/mem_region.h"

#include "ara/crypto/cryp/crypto_context.h"
#include "ara/crypto/cryp/key_derivation_function_ctx.h"
#include "ara/crypto/cryp/cryobj/public_key.h"
#include "ara/crypto/cryp/cryobj/secret_seed.h"
#include "ara/crypto/cryp/cryobj/symmetric_key.h"
#include "ara/crypto/cryp/extension_service.h"
#include "ara/crypto/cryp/cryobj/private_key.h"

#include "ara/core/result.h"
#include "ara/core/optional.h"

namespace ara
{
namespace crypto
{
namespace cryp
{

//- @interface KeyAgreementPrivateCtx
///
/// @traceid{SWS_CRYPT_21300}@tracestatus{draft}
/// @uptrace{RS_CRYPTO_02104}
/// @brief %Key Agreement Private key Context interface (Diffie Hellman or conceptually similar).
///
/// 
class KeyAgreementPrivateCtx : public CryptoContext
{

public:
    /// @traceid{SWS_CRYPT_21301}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02104}
    /// @brief Unique smart pointer of this interface.
    /// 
    using Uptr = std::unique_ptr<KeyAgreementPrivateCtx>;

    /// @traceid{SWS_CRYPT_21302}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02006}
    /// @brief Get ExtensionService instance.
    /// 
    virtual ExtensionService::Uptr GetExtensionService() const noexcept = 0;

    /// @traceid{SWS_CRYPT_21311}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02007}
    /// @brief Produce a common secret seed via execution of the key-agreement algorithm between this private key
    ///           and a public key of another side.
	///       Produced @c SecretSeed object has following attributes: session, non-exportable, AlgID (this Key-Agreement
    ///       Algorithm ID).
    /// @param[in] otherSideKey  the public key of the other side of the Key-Agreement
    /// @param[in] allowedUsage  the allowed usage scope of the target seed
    /// @returns unique pointer to @c SecretSeed object, which contains the key material produced by the Key-Agreement
    ///          algorithm
    /// @error CryptoErrc::kUninitializedContext  if the context was not initialized by a key value
    /// @error CryptoErrc::kIncompatibleObject  if the public and private keys correspond to different algorithms
    ///
    /// @threadsafety{Thread-safe}
    /// 
    virtual ara::core::Result<SecretSeed::Uptrc> AgreeSeed(const PublicKey& otherSideKey,
    		ara::core::Optional<AllowedUsageFlags> allowedUsage
    ) const noexcept = 0;

    /// @traceid{SWS_CRYPT_21312}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02115}
    /// @brief Produce a common symmetric key via execution of the key-agreement algorithm between this private key
    ///           and a public key of another side.
	///       Produced @c SymmetricKey object has following attributes: session, non-exportable.
    ///       This method can be used for direct production of the target key, without creation of the intermediate
    ///       @c SecretSeed object.
    /// @param[in] otherSideKey  the public key of the other side of the Key-Agreement
    /// @param[in] targetAlgId  identifier of the target symmetric algorithm (also defines a target key-length)
    /// @param[in] allowedUsage  the allowed usage scope of the target key
    /// @param[in] kdf  the optional context of a Key Derivation Function, which can be used for the target key production
    /// @param[in] salt  an optional salt value (if used, it should be unique for each instance of the target key)
    /// @param[in] ctxLabel  an optional application specific "context label" (it can identify purpose of the target
    ///            key and/or communication parties)
    /// @returns a unique pointer to @c SymmetricKey object, which contains the computed shared secret or key material
    /// produced by the Key-Agreement algorithm
    /// @error CryptoErrc::kUninitializedContext  if the context was not initialized by a key value
    /// @error CryptoErrc::kIncompatibleObject  if the public and private keys correspond to different algorithms
    ///
    /// @threadsafety{Thread-safe}
    ///
    virtual ara::core::Result<SymmetricKey::Uptrc>
    AgreeKey(const PublicKey& otherSideKey,
             KeyDerivationFunctionCtx& kdf,
             CryptoAlgId targetAlgId,
             AllowedUsageFlags allowedUsage,
             ara::core::Optional<ReadOnlyMemRegion> salt,
             ara::core::Optional<ReadOnlyMemRegion> ctxLabel) const noexcept = 0;

    /// @traceid{SWS_CRYPT_21313}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02001}
    /// @uptrace{RS_CRYPTO_02003}
    /// @brief Set (deploy) a key to the key agreement private algorithm context.
    /// @param[in] key  the source key object
    /// @error CryptoErrc::kIncompatibleObject  if the provided key object is
    ///                incompatible with this private key context
    /// @error CryptoErrc::kUsageViolation  if the transformation type associated with this context
    ///                is prohibited by
    ///                the "allowed usage" restrictions of provided key object
    ///
    /// @threadsafety{Thread-safe}
    /// 
    virtual ara::core::Result<void> SetKey(const PrivateKey& key) noexcept = 0;

    /// @traceid{SWS_CRYPT_21314}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02108}
    /// @brief Clear the crypto context.
    ///
    /// @threadsafety{Thread-safe}
    /// 
    virtual ara::core::Result<void> Reset() noexcept = 0;

};

}  // namespace cryp
}  // namespace crypto
}  // namespace ara

#endif  // ARA_CRYPTO_CRYP_KEY_AGREEMENT_PRIVATE_CTX_H_
