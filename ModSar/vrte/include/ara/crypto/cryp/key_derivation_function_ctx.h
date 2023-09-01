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
/// @brief Adaptive Autosar Crypto Stack. Cryptographic API. KeyDerivationFunctionCtx interface definition.

#ifndef ARA_CRYPTO_CRYP_KEY_DERIVATION_FUNCTION_CTX_H_
#define ARA_CRYPTO_CRYP_KEY_DERIVATION_FUNCTION_CTX_H_

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "ara/crypto/common/mem_region.h"

#include "ara/crypto/cryp/crypto_context.h"
#include "ara/crypto/cryp/cryobj/symmetric_key.h"
#include "ara/crypto/cryp/cryobj/secret_seed.h"
#include "ara/crypto/cryp/extension_service.h"

#include "ara/core/result.h"

namespace ara
{
namespace crypto
{
namespace cryp
{

//- @interface KeyDerivationFunctionCtx
///
/// @traceid{SWS_CRYPT_21500}@tracestatus{draft}
/// @uptrace{RS_CRYPTO_02103}
/// @brief %Key Derivation Function interface.
///

class KeyDerivationFunctionCtx :  public CryptoContext
{
public:
	/// @traceid{SWS_CRYPT_21501}@tracestatus{draft}
	/// @uptrace{RS_CRYPTO_02103}
	/// @brief Unique smart pointer of the interface.
	
	using Uptr = std::unique_ptr<KeyDerivationFunctionCtx>;

///// @traceid{SWS_CRYPT_21510}@tracestatus{draft}
///// @uptrace{RS_CRYPTO_02102}
///// @uptrace{RS_CRYPTO_02107}
///// @uptrace{RS_CRYPTO_02108}
///// @uptrace{RS_CRYPTO_02111}
///// @brief Add an application filler value stored in a (non-secret) ReadOnlyMemRegion.
/////       If <tt>(GetFillerSize() == 0)</tt>, then this method call will be ignored.
/////
///// @param[in] appFiller  the application specific "filler" value
/////
///// @error CryptoErrorDomain::kInvalidInputSize  if size of the @c appFiller is incorrect,
/////                i.e. if <tt>(appFiller.size() < GetFillerSize())</tt>;
/////
///// @threadsafety{Thread-safe}
	
//	virtual ara::core::Result<void> AddAppFiller(const ReadOnlyMemRegion appFiller) noexcept = 0;

///// @traceid{SWS_CRYPT_21511}@tracestatus{draft}
///// @uptrace{RS_CRYPTO_02102}
///// @uptrace{RS_CRYPTO_02107}
///// @uptrace{RS_CRYPTO_02108}
///// @uptrace{RS_CRYPTO_02111}
///// @brief Add a secret application filler value stored in a SecretSeed object.
/////       If <tt>(GetFillerSize() == 0)</tt>, then this method call will be ignored.
/////
///// @param[in] appFiller  the application specific "filler" value
/////
///// @error CryptoErrorDomain::kInvalidInputSize  if size of the @c appFiller is incorrect,
/////                i.e. if <tt>(appFiller.size() < GetFillerSize())</tt>;
/////
///// @threadsafety{Thread-safe}
	
//	virtual ara::core::Result<void> AddSecretAppFiller(const SecretSeed& appFiller) noexcept = 0;

	/// @traceid{SWS_CRYPT_21512}@tracestatus{draft}
	/// @uptrace{RS_CRYPTO_02102}
	/// @uptrace{RS_CRYPTO_02107}
	/// @uptrace{RS_CRYPTO_02108}
	/// @uptrace{RS_CRYPTO_02111}
	/// @brief Add a salt value stored in a (non-secret) ReadOnlyMemRegion.
	///
	/// @param[in] salt  a salt value (if used, it should be unique for each instance of the target key)
	///
	/// @threadsafety{Thread-safe}
	
	virtual ara::core::Result<void> AddSalt(ReadOnlyMemRegion salt) noexcept = 0;

	/// @traceid{SWS_CRYPT_21513}@tracestatus{draft}
	/// @uptrace{RS_CRYPTO_02102}
	/// @uptrace{RS_CRYPTO_02107}
	/// @uptrace{RS_CRYPTO_02108}
	/// @uptrace{RS_CRYPTO_02111}
	/// @brief Add a secret salt value stored in a SecretSeed object.
	///
	/// @param[in] salt  a salt value (if used, it should be unique for each instance of the target key)
	///
	/// @threadsafety{Thread-safe}
	
	virtual ara::core::Result<void> AddSecretSalt(const SecretSeed& salt) noexcept = 0;

	/// @traceid{SWS_CRYPT_21514}@tracestatus{draft}
	/// @uptrace{RS_CRYPTO_02309}
	/// @brief Configure the number of iterations that will be applied by default.
	///       Implementation can restrict minimal and/or maximal value of the iterations number.
	///
	/// @param[in] iterations  the required number of iterations of the base function (0 means implementation default
	///            number)
	/// @returns actual number of the iterations configured in the context now (after this method call)
	///
	///
	/// @threadsafety{Thread-safe}
	
	virtual std::uint32_t ConfigIterations(std::uint32_t iterations = 0) noexcept = 0;

	/// @traceid{SWS_CRYPT_21515}@tracestatus{draft}
	/// @uptrace{RS_CRYPTO_02102}
	/// @uptrace{RS_CRYPTO_02107}
	/// @uptrace{RS_CRYPTO_02108}
	/// @uptrace{RS_CRYPTO_02111}
	/// @uptrace{RS_CRYPTO_02115}
	/// @brief Derive a symmetric key from the provided key material and provided context configuration.
	///
	/// @param[in] isSession  the "session" (or "temporary") attribute for the target key (if @c true)
	/// @param[in] isExportable  the exportability attribute for the target key (if @c true)
	///
	/// @returns unique smart pointer to the created instance of derived symmetric key
	///
	/// @error CryptoErrorDomain::kUninitializedContext  if the context was not sufficiently initialized
	///
	/// @threadsafety{Thread-safe}
	
	virtual ara::core::Result<SymmetricKey::Uptrc> DeriveKey(
			bool isSession = true,
			bool isExportable = false
	) const noexcept = 0;

	/// @traceid{SWS_CRYPT_21516}@tracestatus{draft}
	/// @uptrace{RS_CRYPTO_02007}
	/// @brief Derive a "slave" key material (secret seed) from the provided "master" key material and
	///           provided context configuration.
	///
	/// @param[in] isSession  the "session" (or "temporary") attribute for the target key (if @c true)
	/// @param[in] isExportable  the exportability attribute for the target key (if @c true)
	///
	/// @returns unique smart pointer to the created @c SecretSeed object
	///
	/// @error CryptoErrorDomain::kUninitializedContext  if the context was not sufficiently initialized
	///
	/// @threadsafety{Thread-safe}
	
	virtual ara::core::Result<SecretSeed::Uptrc> DeriveSeed(
			bool isSession = true,
			bool isExportable = false
			) const noexcept = 0;

	/// @traceid{SWS_CRYPT_21517}@tracestatus{draft}
	/// @uptrace{RS_CRYPTO_02006}
	/// @brief Get ExtensionService instance.
	///
	
	virtual ExtensionService::Uptr GetExtensionService() const noexcept = 0;

///// @traceid{SWS_CRYPT_21518}@tracestatus{draft}
///// @uptrace{RS_CRYPTO_02103}
///// @brief Get the fixed size of an application specific "filler" required by this context instance.
/////       If this instance of the key derivation context does not support filler values, 0 shall be returned.
///// @returns size of the application specific filler in bytes
/////
/////       Returned value is constant for this instance of the key derivation context, i.e. independent from configuration by
/////       the @c Init() call.
/////
///// @threadsafety{Thread-safe}
	
//	virtual std::size_t GetFillerSize() const noexcept = 0;


	/// @traceid{SWS_CRYPT_21519}@tracestatus{draft}
	/// @uptrace{RS_CRYPTO_02103}
	/// @brief Get the fixed size of the target key ID required by diversification algorithm.
	///       Returned value is constant for each instance of the interface, i.e. independent from configuration by
	///
	/// @returns size of the key ID in bytes
	///
	///       the @c Init() call.
	///
	/// @threadsafety{Thread-safe}
	
	virtual std::size_t GetKeyIdSize() const noexcept = 0;

	/// @traceid{SWS_CRYPT_21520}@tracestatus{draft}
	/// @uptrace{RS_CRYPTO_02103}
	/// @brief Get the symmetric algorithm ID of target (slave) key.
	///       If the context was not configured yet by a call of the @c Init() method then @c kAlgIdUndefined should be
	///
	/// @returns the symmetric algorithm ID of the target key, configured by the last call of the @c Init() method
	///
	///       returned.
	///
	/// @threadsafety{Thread-safe}
	
	virtual AlgId GetTargetAlgId() const noexcept = 0;

	/// @traceid{SWS_CRYPT_21521}@tracestatus{draft}
	/// @uptrace{RS_CRYPTO_02008}
	/// @brief Get allowed key usage of target (slave) key.
	///       The returned value depends on the source key-material allowed usage flags and the argument @c allowedUsage
	///       of last call of the @c Init() method.
	///       If the context has not yet been configured by a call of the @c Init() method, the allowed usage flags
	///       of the source key-material shall be returned.
	///       If the context has not yet been configured by a call of the @c Init() method and no source key-material
	///       has been set either, kAllowKdfMaterialAnyUsage shall be returned.
	///
	/// @returns allowed key usage bit-flags of target keys
	///
	///
	/// @threadsafety{Thread-safe}
	
	virtual AllowedUsageFlags GetTargetAllowedUsage() const noexcept = 0;

	/// @traceid{SWS_CRYPT_21522}@tracestatus{draft}
	/// @uptrace{RS_CRYPTO_02103}
	/// @brief Get the bit-length of target (diversified) keys.
	///       Returned value is configured by the context factory method, i.e. independent from configuration by
	///
	/// @returns the length of target (diversified) key in bits
	///
	///       the @c Init() calls.
	///
	/// @threadsafety{Thread-safe}
	
	virtual std::size_t GetTargetKeyBitLength() const noexcept = 0;

	/// @traceid{SWS_CRYPT_21523}@tracestatus{draft}
	/// @uptrace{RS_CRYPTO_02102}
	/// @uptrace{RS_CRYPTO_02107}
	/// @uptrace{RS_CRYPTO_02108}
	/// @uptrace{RS_CRYPTO_02111}
	/// @uptrace{RS_CRYPTO_02115}
	/// @brief Initialize this context by setting at least the target key ID.
	///       The byte sequence provided via argument @c ctxLabel can include a few fields with different meaning
	///       separated by single @c 0x00 byte.
	///       If <tt>(targetAlgId == kAlgIdAny)</tt> then a diversified key can be loaded to any symmetric context that
	///       supports the same key length (if the "allowed usage" flags are also satisfied)!
	///
	/// @param[in] targetKeyId  ID of the target key
	/// @param[in] targetAlgId  the identifier of the target symmetric crypto algorithm
	/// @param[in] allowedUsage  bit-flags that define a list of allowed transformations' types in which the target key
	///            may be used
	/// @param[in] ctxLabel  an optional application specific "context label" (this can identify the purpose of the
	///            target key and/or communication parties)
	///
	///
	/// @error CryptoErrorDomain::kIncompatibleArguments  if @c targetAlgId specifies a cryptographic
	///                algorithm different from a symmetric one with key length equal to @c GetTargetKeyBitLength();
	/// @error CryptoErrorDomain::kUsageViolation  if @c allowedUsage specifies more usages of the derived
	///                key-material than the source key-material, i.e. usage of the derived key-material may not be
	///                expanded beyond what the source key-material allows
	///
	/// @threadsafety{Thread-safe}
	
	virtual ara::core::Result<void> Init(
			ReadOnlyMemRegion targetKeyId,
			AlgId targetAlgId = kAlgIdAny,
			AllowedUsageFlags allowedUsage = kAllowKdfMaterialAnyUsage,
			ReadOnlyMemRegion ctxLabel = ReadOnlyMemRegion()
	) noexcept = 0;

    /// @traceid{SWS_CRYPT_21524}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02108}
    /// @brief Clear the crypto context.
    ///
    /// @threadsafety{Thread-safe}
   
    virtual ara::core::Result<void> Reset() noexcept = 0;

	/// @traceid{SWS_CRYPT_21525}@tracestatus{draft}
	/// @uptrace{RS_CRYPTO_02001}
	/// @uptrace{RS_CRYPTO_02003}
	/// @brief Set (deploy) key-material to the key derivation algorithm context.
	/// @param[in] sourceKM  the source key-material
	///
	/// @error CryptoErrorDomain::kIncompatibleObject  if the provided key object is
	///                incompatible with this symmetric key context
	/// @error CryptoErrorDomain::kUsageViolation  if deriving a key is prohibited by
	///                the "allowed usage" restrictions of the provided source key-material
	/// @error CryptoErrorDomain::kBruteForceRisk  if key length of the @c sourceKm is below of
	///                an internally defined limitation
	///
	/// @threadsafety{Thread-safe}
	
	virtual ara::core::Result<void> SetSourceKeyMaterial(const RestrictedUseObject& sourceKM) noexcept = 0;
};

}  // namespace cryp
}  // namespace crypto
}  // namespace ara

#endif  // ARA_CRYPTO_CRYP_KEY_DERIVATION_FUNCTION_CTX_H_
