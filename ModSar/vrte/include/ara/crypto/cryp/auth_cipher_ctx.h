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
/// @brief Adaptive Autosar Crypto Stack. Cryptographic API. AuthCipherCtx interface definition.

#ifndef ARA_CRYPTO_CRYP_AUTH_CIPHER_CTX_H_
#define ARA_CRYPTO_CRYP_AUTH_CIPHER_CTX_H_

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "ara/crypto/cryp/digest_service.h"
#include "ara/crypto/cryp/crypto_context.h"
#include "ara/crypto/cryp/cryobj/symmetric_key.h"
#include "ara/crypto/cryp/cryobj/secret_seed.h"
#include "ara/crypto/cryp/cryobj/signature.h"
#include "ara/crypto/cryp/block_service.h"

#include "ara/core/result.h"

namespace ara
{
namespace crypto
{
namespace cryp
{

//- @interface AuthCipherCtx
///
/// @traceid{SWS_CRYPT_20100}@tracestatus{draft}
/// @uptrace{RS_CRYPTO_02207}
/// @brief Generalized Authenticated Cipher Context interface.
///       Methods of the derived interface @c BufferedDigest are used for authentication of associated public data.
///       Methods of the derived interface @c StreamCipherCtx are used for encryption/decryption and authentication of
///       confidential part of message.
///       The data processing must be executed in following order:
///       1. Call one of the @c Start() methods.
///       2. Process all associated public data via calls of @c Update() methods.
///       3. Process the confidential part of the message via calls of @c ProcessBlocks(), @c ProcessBytes() (and
///          optionally @c FinishBytes()) methods.
///       4. Call the @c Finish() method due to finalize the authentication code calculation (and get it optionally).
///       5. Copy of the calculated MAC may be extracted (by @c GetDigest()) or compared internally (by @c Compare()).
///       Receiver side should not use decrypted data before finishing of the whole decryption and authentication
///       process! I.e. decrypted data can be used only after successful MAC verification!
///

class AuthCipherCtx : public CryptoContext
{
public:
    /// @traceid{SWS_CRYPT_20101}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02207}
    /// @brief Unique smart pointer of the interface.
    
    using Uptr = std::unique_ptr<AuthCipherCtx>;

	/// @traceid{SWS_CRYPT_20102}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02006}
    /// @brief Get DigestService instance.
    
    virtual DigestService::Uptr GetDigestService() const noexcept = 0;

    /// @traceid{SWS_CRYPT_20103}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02309}
    /// @brief Get maximal supported size of associated public data.
    /// @returns maximal supported size of associated public data in bytes
    /// @threadsafety{Thread-safe}
    
    virtual std::uint64_t GetMaxAssociatedDataSize() const noexcept = 0;

    /// @traceid{SWS_CRYPT_21715}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02309}
    /// @brief Get the kind of transformation configured for this context: kEncrypt or kDecrypt
    /// @returns @c CryptoTransform
    /// @error CryptoErrorDomain::kUninitializedContext  if the transformation direction of this context
    ///                is configurable during an initialization, but the context was not initialized yet
    /// @threadsafety{Thread-safe}
    virtual ara::core::Result<CryptoTransform> GetTransformation() const noexcept = 0;

    /// @traceid{SWS_CRYPT_23911}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02001}
    /// @uptrace{RS_CRYPTO_02003}
    /// @brief Set (deploy) a key to the authenticated cipher symmetric algorithm context.
    /// @param[in] key  the source key object
    /// @param[in] transform  the "direction" indicator: deploy the key for encryption (if @c true)
    ///            or for decryption (if @c false)
    /// @error CryptoErrorDomain::kIncompatibleObject  if the provided key object is
    ///                incompatible with this symmetric key context
    /// @error CryptoErrorDomain::kUsageViolation  if the transformation type associated with this context
    ///                (taking into account the direction specified by @c transform) is prohibited by
    ///                the "allowed usage" restrictions of provided key object
    ///
    /// @threadsafety{Thread-safe}
    
    virtual ara::core::Result<void> SetKey(const SymmetricKey& key
        , CryptoTransform transform = CryptoTransform::kEncrypt
    ) noexcept = 0;

    /// @traceid{SWS_CRYPT_24714}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02302}
    /// @brief Initialize the context for a new data processing or generation (depending from the primitive).
	///      If IV size is greater than maximally supported by the algorithm then an implementation may use the
    ///       leading bytes only from the sequence.
    /// @param[in] iv  an optional Initialization Vector (IV) or "nonce" value
    /// @error CryptoErrorDomain::kUninitializedContext  if the context was not initialized
    /// @error CryptoErrorDomain::kInvalidInputSize  if the size of provided IV is not supported
    ///                (i.e. if it is not enough for the initialization)
    /// @error CryptoErrorDomain::kUnsupported  if the base algorithm (or its current implementation)
    ///                principally doesn't support the IV variation, but provided IV value is not empty,
    ///                i.e. if <tt>(iv.empty() == false)</tt>

    ///
    /// @threadsafety{Thread-safe}
    
    virtual ara::core::Result<void> Start(ReadOnlyMemRegion iv = ReadOnlyMemRegion()) noexcept = 0;

    /// @traceid{SWS_CRYPT_24715}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02302}
    /// @brief Initialize the context for a new data processing or generation (depending from the primitive).
	/// If IV size is greater than maximally supported by the algorithm then an implementation may use the
    ///       leading bytes only from the sequence.
    /// @param[in] iv  the Initialization Vector (IV) or "nonce" object
    /// @error CryptoErrorDomain::kUninitializedContext  if the context was not initialized
    /// @error CryptoErrorDomain::kInvalidInputSize  if the size of provided IV is not supported
    ///                (i.e. if it is not enough for the initialization)
    /// @error CryptoErrorDomain::kUnsupported  if the base algorithm (or its current implementation)
    ///                principally doesn't support the IV variation
    /// @error CryptoErrorDomain::kUsageViolation  if this transformation type is prohibited by
    ///                the "allowed usage" restrictions of the provided @c SecretSeed object
    ///
    /// @threadsafety{Thread-safe}
    
    virtual ara::core::Result<void> Start(const SecretSeed& iv) noexcept = 0;

    /// @traceid{SWS_CRYPT_20312}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02302}
    /// @brief Update the digest calculation by the specified RestrictedUseObject.
	///    This method is dedicated for cases then the @c RestrictedUseObject is a part of the "message".
    /// @param[in] in  a part of input message that should be processed

    /// @error CryptoErrorDomain::kProcessingNotStarted  if the digest calculation was not initiated
    ///         by a call of the @c Start() method
    /// @error CryptoErrorDomain::kInvalidUsageOrder if ProcessConfidentialData has already been called
    ///
    ///
    /// @threadsafety{Thread-safe}
    
    virtual ara::core::Result<void> UpdateAssociatedData(const RestrictedUseObject& in) noexcept = 0;

    /// @traceid{SWS_CRYPT_20313}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02302}
    /// @brief Update the digest calculation by a new chunk of associated data.
    /// @param[in] in  a part of the input message that should be processed
    /// @error CryptoErrorDomain::kProcessingNotStarted  if the digest calculation was not initiated
    ///         by a call of the @c Start() method
    /// @error CryptoErrorDomain::kInvalidUsageOrder if ProcessConfidentialData has already been called
    ///
    /// @threadsafety{Thread-safe}
    
    virtual ara::core::Result<void> UpdateAssociatedData(ReadOnlyMemRegion in) noexcept = 0;

    /// @traceid{SWS_CRYPT_20314}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02302}
    /// @brief Update the digest calculation by the specified Byte.
	///        This method is convenient for processing of constant tags.
    /// @param[in] in  a byte value that is a part of input message
    /// @error CryptoErrorDomain::kProcessingNotStarted  if the digest calculation was not initiated
    ///         by a call of the @c Start() method
    /// @error CryptoErrorDomain::kInvalidUsageOrder if ProcessConfidentialData has already been called
    ///
    ///
    /// @threadsafety{Thread-safe}
    
    virtual ara::core::Result<void> UpdateAssociatedData(std::uint8_t in) noexcept = 0;


    /// @traceid{SWS_CRYPT_23634}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02302}
    /// @brief Process confidential data and return result.
	///     The input buffer will be overwritten by the processed message.
	///     This function is the final call, i.e. all associated data must have been already provided.
    ///       Hence, the function will check the authentication tag and only return the processed data, if the tag is valid.
	/// @param[in] in the input buffer containing the full message
	/// @param[in] expectedTag optional pointer to read only mem region containing the auth-tag for verification.
	/// @returns the processed data
	///
	/// @error CryptoErrorDomain::kInvalidInputSize  if size of the input buffer is not divisible by
	///                the block size (see @c GetBlockSize())
	/// @error CryptoErrorDomain::kProcessingNotStarted  if the data processing was not started by a call of
	///                the @c Start() method
    /// @error CryptoErrorDomain::kAuthTagNotValid  if the processed data cannot be authenticated
	///
	/// @threadsafety{Thread-safe}
	
    virtual ara::core::Result<ara::core::Vector<ara::core::Byte>> ProcessConfidentialData(ReadOnlyMemRegion in, ara::core::Optional<ReadOnlyMemRegion> expectedTag ) noexcept = 0;

    /// @traceid{SWS_CRYPT_23635}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02302}
    /// @brief Process confidential data and update the input buffer with the processed message.
	///     The input buffer will be overwritten by the processed message
    ///     After this method is called no additional associated data may be updated.
    /// @param[in] inOut  the input buffer containing the full message
    /// @param[in] expectedTag optional pointer to read only mem region containing the auth-tag for verification.
    ///

    ///
	/// @error CryptoErrorDomain::kInvalidInputSize  if size of the input buffer is not divisible by
	///                the block size (see @c GetBlockSize())
	/// @error CryptoErrorDomain::kProcessingNotStarted  if the data processing was not started by a call of
	///                the @c Start() method
    /// @error CryptoErrorDomain::kAuthTagNotValid  if the processed data cannot be authenticated
	///
	/// @threadsafety{Thread-safe}
	
			
	virtual ara::core::Result<void> ProcessConfidentialData(ReadWriteMemRegion inOut, ara::core::Optional<ReadOnlyMemRegion> expectedTag ) noexcept = 0;

    /// @traceid{SWS_CRYPT_20316}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02207}
    /// @brief Retrieve the calculated digest.
    ///       The entire digest value is kept in the context until the next call of @c Start().
    ///       Therefore, the digest can be re-checked or extracted at any time.
    ///       If the offset is larger than the digest, an empty buffer shall be returned.
    ///       This method can be implemented as "inline" after standardization of function @c ara::core::memcpy().
    /// @param[in] offset  position of the first byte of digest that should be placed to the output buffer
    /// @returns an output buffer storing the requested digest fragment or the full digest

    ///
    /// @error CryptoErrorDomain::kProcessingNotFinished  if the digest calculation was not finished
    ///                by a call of the @c Finish() method
    /// @error CryptoErrorDomain::kUsageViolation  if the buffered digest belongs to a MAC/HMAC/AE/AEAD
    ///                context initialized by a key without @c kAllowSignature permission
    /// @threadsafety{Thread-safe}
    
    virtual ara::core::Result<ara::core::Vector<ara::core::Byte>> GetDigest(std::size_t offset = 0
    ) const noexcept = 0;

    /// @traceid{SWS_CRYPT_20316}@tracestatus{draft}
        /// @uptrace{RS_CRYPTO_02207}
        /// @brief Retrieve the calculated digest.
		///     The entire digest value is kept in the context until the next call of @c Start().
        ///       Therefore, the digest can be re-checked or extracted at any time.
        ///      If the offset is larger than the digest, an empty buffer shall be returned.
        ///      This method can be implemented as "inline" after standardization of function @c ara::core::memcpy().
        /// @param[in] offset  position of the first byte of digest that should be placed to the output buffer
        /// @returns an output buffer storing the requested digest fragment or the full digest
        ///

        ///
        /// @error CryptoErrorDomain::kProcessingNotFinished  if the digest calculation was not finished
        ///                by a call of the @c Finish() method
        /// @error CryptoErrorDomain::kUsageViolation  if the buffered digest belongs to a MAC/HMAC/AE/AEAD
        ///                context initialized by a key without @c kAllowSignature permission
        /// @threadsafety{Thread-safe}
        
//    template <typename Alloc = VENDOR_IMPLEMENTATION_DEFINED>
//    ara::core::Result<ByteVector<Alloc>> GetDigest(std::size_t offset = 0
//    ) const noexcept
//    {
//        ara::core::Result<ara::core::Vector<ara::core::Byte>> result = GetDigest(offset);
//        if (result)
//        {
//            ByteVector<Alloc> output;
//            output.resize(result.Value()->size());
//            memcpy(core::data(output), result.Value()->data(), result.Value()->size());
//            return ara::core::Result<ByteVector<Alloc>>::FromValue(output);
//        }
//        else
//        {
//            return ara::core::Result<ByteVector<Alloc>>::FromError(result.Error());
//        }
//    }

    /// @traceid{SWS_CRYPT_20414}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02108}
    /// @brief Clear the crypto context.
    /// @threadsafety{Thread-safe}
    
    virtual ara::core::Result<void> Reset() noexcept = 0;

    /// @traceid{SWS_CRYPT_20319}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02203}
    /// @uptrace{RS_CRYPTO_02204}
    /// @brief Check the calculated digest against an expected "signature" object.
	///       Entire digest value is kept in the context up to next call @c Start(), therefore it can be
    ///       verified again or extracted.
    ///       This method can be implemented as "inline" after standartization of function @c ara::core::memcmp().
    /// @param[in] expected  the signature object containing an expected digest value
    /// @returns @c true if value and meta-information of the provided "signature" object is identical to calculated
    ///          digest and current configuration of the context respectively; but @c false otherwise

    /// @error CryptoErrorDomain::kProcessingNotFinished  if the digest calculation was not finished by
    ///                a call of the @c Finish() method
    /// @error CryptoErrorDomain::kIncompatibleObject  if the provided "signature" object was produced by
    ///                another crypto primitive type
    /// @threadsafety{Thread-safe}
    
    virtual ara::core::Result<bool> Check(const Signature & expected) const noexcept = 0;

};

}  // namespace cryp
}  // namespace crypto
}  // namespace ara

#endif  // ARA_CRYPTO_CRYP_AUTH_CIPHER_CTX_H_
