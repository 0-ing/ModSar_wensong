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
/// @brief Adaptive Autosar Crypto Stack. Cryptographic API. KeyEncapsulatorPublicCtx interface definition.

#ifndef ARA_CRYPTO_CRYP_KEY_ENCAPSULATOR_PUBLIC_CTX_H_
#define ARA_CRYPTO_CRYP_KEY_ENCAPSULATOR_PUBLIC_CTX_H_

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "ara/crypto/cryp/cryobj/public_key.h"
#include "ara/crypto/cryp/cryobj/symmetric_key.h"
#include "ara/crypto/cryp/cryobj/secret_seed.h"
#include "ara/crypto/cryp/key_derivation_function_ctx.h"
#include "ara/crypto/cryp/extension_service.h"

#include "ara/core/result.h"

namespace ara
{
namespace crypto
{
namespace cryp
{
//- @interface KeyEncapsulatorPublicCtx
///
/// @traceid{SWS_CRYPT_21800}@tracestatus{draft}
/// @uptrace{RS_CRYPTO_02104}
/// @uptrace{RS_CRYPTO_02209}
/// @brief Asymmetric %Key Encapsulation Mechanism (KEM) Public key Context interface.
///

class KeyEncapsulatorPublicCtx : public CryptoContext
{
public:
    /// @traceid{SWS_CRYPT_21801}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02209}
    /// @brief Unique smart pointer of the interface.
   
    using Uptr = std::unique_ptr<KeyEncapsulatorPublicCtx>;

	/// @traceid{SWS_CRYPT_21802}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02006}
    /// @brief Get ExtensionService instance.

    virtual ExtensionService::Uptr GetExtensionService() const noexcept = 0;

    /// @traceid{SWS_CRYPT_21810}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02007}
    /// @brief Add the content to be encapsulated (payload) according to RFC 5990 ("keying data").
    ///           At the moment only SymmetricKey and SecretSeed objects are supported.
    /// @param[in] keyingData  the payload to be protected
    /// @error CryptoErrc::kUsageViolation  if the @c keyingData cannot be exported due to CryptoObject::IsExportable() returning FALSE
    /// @error CryptoErrc::kIncompatibleObject  if the @c keyingData belongs to a different CryptoProvider
    /// @error CryptoErrc::kInvalidInputSize if this context does not support the size of the @c keyingData
    /// @threadsafety{Thread-safe}
    virtual ara::core::Result<void> AddKeyingData(const RestrictedUseObject& keyingData) noexcept  = 0;

    /// @traceid{SWS_CRYPT_21813}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02102}
    /// @uptrace{RS_CRYPTO_02108}
    /// @uptrace{RS_CRYPTO_02115}
    /// @brief Encapsulate the last set keying-data.
    /// @param[in] kdf  a context of a key derivation function, which should be used for the target KEK production
    /// @param[in] kekAlgId  an algorithm ID of the target KEK
    /// @returns the encapsulated data as a byte-vector
    /// @error CryptoErrc::kUninitializedContext  if the context was not initialized by a public key value
    /// @error CryptoErrc::kInvalidArgument  if @c kekAlgId or @c kdf are incompatible with this context
    ///
    /// @threadsafety{Thread-safe}
    virtual ara::core::Result<ara::core::Vector<ara::core::Byte>> Encapsulate(
        KeyDerivationFunctionCtx& kdf,
		CryptoAlgId kekAlgId
    ) const noexcept  = 0;

    /// @traceid{SWS_CRYPT_21815}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02001}
    /// @uptrace{RS_CRYPTO_02003}
    /// @brief Set (deploy) a key to the key encapsulator public algorithm context.
    /// @param[in] key  the source key object
    /// @error CryptoErrc::kIncompatibleObject  if the provided key object is
    ///                incompatible with this symmetric key context
    /// @error CryptoErrc::kUsageViolation  if the transformation type associated with this context
    ///                is prohibited by
    ///                the "allowed usage" restrictions of provided key object
    ///
    /// @threadsafety{Thread-safe}

    virtual ara::core::Result<void> SetKey(const PublicKey& key) noexcept = 0;

    /// @traceid{SWS_CRYPT_21816}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02108}
    /// @brief Clear the crypto context.
    ///
    /// @threadsafety{Thread-safe}
    virtual ara::core::Result<void> Reset() noexcept  = 0;

    /// @traceid{SWS_CRYPT_21817}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02309}
    /// @brief Get entropy (bit-length) of the key encryption key (KEK) material.
    ///       For RSA system the returned value corresponds to the length of module N (minus 1).
    ///       For DH-like system the returned value corresponds to the length of module q (minus 1).
    /// @returns entropy of the KEK material in bits
    ///
    /// @threadsafety{Thread-safe}

    virtual std::size_t GetKekEntropy() const noexcept = 0;

    /// @traceid{SWS_CRYPT_21818}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02309}
    /// @brief Get fixed size of the encapsulated data block.
    /// @returns size of the encapsulated data block in bytes
    ///
    /// @threadsafety{Thread-safe}

    virtual std::size_t GetEncapsulatedSize() const noexcept = 0;
};

}  // namespace cryp
}  // namespace crypto
}  // namespace ara

#endif  // ARA_CRYPTO_CRYP_KEY_ENCAPSULATOR_PUBLIC_CTX_H_
