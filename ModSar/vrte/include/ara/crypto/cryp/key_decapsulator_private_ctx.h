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
/// @brief Adaptive Autosar Crypto Stack. Cryptographic API. KeyDecapsulatorPrivateCtx interface definition.

#ifndef ARA_CRYPTO_CRYP_KEY_DECAPSULATOR_PRIVATE_CTX_H_
#define ARA_CRYPTO_CRYP_KEY_DECAPSULATOR_PRIVATE_CTX_H_

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "ara/crypto/cryp/crypto_context.h"
#include "ara/crypto/cryp/cryobj/private_key.h"
#include "ara/crypto/cryp/cryobj/symmetric_key.h"
#include "ara/crypto/cryp/cryobj/secret_seed.h"
#include "ara/crypto/cryp/key_derivation_function_ctx.h"
#include "ara/crypto/cryp/extension_service.h"

#include "ara/core/result.h"
#include "ara/core/optional.h"

namespace ara
{
namespace crypto
{
namespace cryp
{

//- @interface KeyDecapsulatorPrivateCtx
///
/// @traceid{SWS_CRYPT_21400}@tracestatus{draft}
/// @uptrace{RS_CRYPTO_02104}
/// @uptrace{RS_CRYPTO_02209}
/// @brief Asymmetric %Key Encapsulation Mechanism (KEM) Private key Context interface.
///
/// 
class KeyDecapsulatorPrivateCtx : public CryptoContext
{
public:
    /// @traceid{SWS_CRYPT_21401}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02104}
    /// @brief Unique smart pointer of the interface.
    /// 
    using Uptr = std::unique_ptr<KeyDecapsulatorPrivateCtx>;

    /// @traceid{SWS_CRYPT_21402}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02006}
    /// @brief Get ExtensionService instance.
    /// 
    virtual ExtensionService::Uptr GetExtensionService() const noexcept = 0;

    /// @traceid{SWS_CRYPT_21411}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02007}
    /// @brief Decapsulate key material.
    ///       Produced @c SecretSeed object has following attributes: session, non-exportable, AlgID = this KEM AlgID.
    /// @param[in] input  a buffer with the encapsulated seed (its size should be equal @c GetEncapsulatedSize() bytes)
    /// @param[in] allowedUsage  the allowed usage scope of the target seed (default = kAllowKdfMaterialAnyUsage)
    /// @returns unique smart pointer to @c SecretSeed object, which keeps the key material decapsulated from the input buffer
    /// @error CryptoErrc::kUninitializedContext  if the context was not initialized by a private key value
    /// @error CryptoErrc::kInvalidInputSize  if this context does not support the size of @c input
    ///
    /// @threadsafety{Thread-safe}
    /// 
    virtual ara::core::Result<SecretSeed::Uptrc> DecapsulateSeed(ReadOnlyMemRegion input,
    		ara::core::Optional<AllowedUsageFlags> allowedUsage
    ) const noexcept = 0;

    /// @traceid{SWS_CRYPT_21412}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02102}
    /// @uptrace{RS_CRYPTO_02108}
    /// @uptrace{RS_CRYPTO_02115}
    /// @brief Decapsulate the keying data to be used for subsequent processing (e.g. secure communication).
	///       Produced @c SymmetricKey object has following attributes: session, non-exportable
    /// @param[in] input  an input buffer (its size should be equal @c GetEncapsulatedSize() bytes)
    /// @param[in] keyingDataAlgId  algorithm ID of the returned symmetric key
    /// @param[in] kdf  a context of a key derivation function, which should be used for KEK production
    /// @param[in] kekAlgId  an algorithm ID of the KEK
    /// @param[in] allowedUsage  the allowed usage scope of the returned symmetric key object (default = kAllowKdfMaterialAnyUsage)
    /// @returns unique smart pointer of the symmetric key object instantiated from the decapsulated keying data
    /// @error CryptoErrc::kUninitializedContext  if the context was not initialized by a private key value
    /// @error CryptoErrc::kInvalidArgument  if @c kekAlgId or @c kdf are incompatible with this context
    /// @error CryptoErrc::kInvalidInputSize  if this context does not support the size of @c input
    ///
    /// @threadsafety{Thread-safe}
    /// 
    virtual ara::core::Result<SymmetricKey::Uptrc> DecapsulateKey(ReadOnlyMemRegion input,
    	CryptoAlgId keyingDataAlgId,
        KeyDerivationFunctionCtx& kdf,
		CryptoAlgId kekAlgId,
		ara::core::Optional<AllowedUsageFlags> allowedUsage
    ) const noexcept = 0;

    /// @traceid{SWS_CRYPT_21413}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02001}
    /// @uptrace{RS_CRYPTO_02003}
    /// @brief Set (deploy) a key to the key decapsulator private algorithm context.
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

    /// @traceid{SWS_CRYPT_21414}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02108}
    /// @brief Clear the crypto context.
    ///
    /// @threadsafety{Thread-safe}
    /// 
    virtual ara::core::Result<void> Reset() noexcept = 0;

    /// @traceid{SWS_CRYPT_21415}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02309}
    /// @brief Get entropy (bit-length) of the key encryption key (KEK) material.
    ///       For RSA system the returned value corresponds to the length of module N (minus 1).
    ///       For DH-like system the returned value corresponds to the length of module q (minus 1).
    /// @returns entropy of the KEK material in bits
    ///
    /// @threadsafety{Thread-safe}
    /// 
    virtual std::size_t GetKekEntropy() const noexcept = 0;

    /// @traceid{SWS_CRYPT_21416}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02309}
    /// @brief Get fixed size of the encapsulated data block.
    /// @returns size of the encapsulated data block in bytes
    ///
    /// @threadsafety{Thread-safe}
    /// 
    virtual std::size_t GetEncapsulatedSize() const noexcept = 0;
};

}  // namespace cryp
}  // namespace crypto
}  // namespace ara

#endif  // ARA_CRYPTO_CRYP_KEY_DECAPSULATOR_PRIVATE_CTX_H_
