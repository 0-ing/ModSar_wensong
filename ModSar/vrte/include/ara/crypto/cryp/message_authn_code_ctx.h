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
/// @brief Adaptive Autosar Crypto Stack. Cryptographic API. MessageAuthnCodeCtx interface definition.

#ifndef ARA_CRYPTO_CRYP_MESSAGE_AUTHN_CODE_CTX_H_
#define ARA_CRYPTO_CRYP_MESSAGE_AUTHN_CODE_CTX_H_

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "ara/crypto/cryp/crypto_context.h"

#include "ara/crypto/cryp/cryobj/symmetric_key.h"
#include "ara/crypto/cryp/cryobj/secret_seed.h"
#include "ara/crypto/cryp/cryobj/signature.h"
#include "ara/crypto/cryp/digest_service.h"

#include "ara/core/result.h"

namespace ara
{
namespace crypto
{
namespace cryp
{

//- @interface MessageAuthnCodeCtx
///
/// @traceid{SWS_CRYPT_22100}@tracestatus{draft}
/// @uptrace{RS_CRYPTO_02203}
/// @brief Keyed Message Authentication Code Context interface definition (MAC/HMAC).
///

class MessageAuthnCodeCtx : public CryptoContext
{
public:
    /// @traceid{SWS_CRYPT_22101}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02203}
    /// @brief Unique smart pointer of the interface.
    
    using Uptr = std::unique_ptr<MessageAuthnCodeCtx>;

    /// @traceid{SWS_CRYPT_22102}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02006}
    /// @brief Get DigestService instance.
    
    virtual DigestService::Uptr GetDigestService() const noexcept = 0;

    /// @traceid{SWS_CRYPT_22110}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02302}
    /// @brief Initialize the context for a new data stream processing or generation (depending from the primitive).
    ///       If IV size is greater than maximally supported by the algorithm then an implementation may use the
    ///       leading bytes only from the sequence.
    ///
    /// @param[in] iv  an optional Initialization Vector (IV) or "nonce" value
    /// @error CryptoErrorDomain::kUninitializedContext  if the context was not initialized by deploying a key
    /// @error CryptoErrorDomain::kInvalidInputSize  if the size of provided IV is not supported
    ///                (i.e. if it is not enough for the initialization)
    /// @error CryptoErrorDomain::kUnsupported  if the base algorithm (or its current implementation)
    ///                principally doesn't support the IV variation, but provided IV value is not empty,
    ///                i.e. if <tt>(iv.empty() == false)</tt>
    /// @threadsafety{Thread-safe}
    
    virtual ara::core::Result<void> Start(ReadOnlyMemRegion iv = ReadOnlyMemRegion()) noexcept = 0;

    /// @traceid{SWS_CRYPT_22111}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02302}
    /// @brief Initialize the context for a new data stream processing or generation (depending from the primitive).
    ///       If IV size is greater than maximally supported by the algorithm then an implementation may use the
    ///       leading bytes only from the sequence.
    /// @param[in] iv  the Initialization Vector (IV) or "nonce" object
    /// @error CryptoErrorDomain::kUninitializedContext  if the context was not initialized by deploying a key
    /// @error CryptoErrorDomain::kInvalidInputSize  if the size of provided IV is not supported
    ///                (i.e. if it is not enough for the initialization)
    /// @error CryptoErrorDomain::kUnsupported  if the base algorithm (or its current implementation)
    ///                principally doesn't support the IV variation
    /// @error CryptoErrorDomain::kUsageViolation  if this transformation type is prohibited by
    ///                the "allowed usage" restrictions of the provided @c SecretSeed object
    ///
    /// @threadsafety{Thread-safe}
    
    virtual ara::core::Result<void> Start(const SecretSeed& iv) noexcept = 0;

    /// @traceid{SWS_CRYPT_22112}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02302}
    /// @brief Update the digest calculation context by a new part of the message.
    ///       This method is dedicated for cases then the @c RestrictedUseObject is a part of the "message".
    /// @param[in] in  a part of input message that should be processed
    /// @error CryptoErrorDomain::kProcessingNotStarted  if the digest calculation was not initiated
    ///         by a call of the @c Start() method
    ///
    /// @threadsafety{Thread-safe}
    
    virtual ara::core::Result<void> Update(const RestrictedUseObject& in) noexcept = 0;

    /// @traceid{SWS_CRYPT_22113}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02302}
    /// @brief Update the digest calculation context by a new part of the message.
    /// @param[in] in  a part of the input message that should be processed
    /// @error CryptoErrorDomain::kProcessingNotStarted  if the digest calculation was not initiated
    ///         by a call of the @c Start() method
    ///
    /// @threadsafety{Thread-safe}
    
    virtual ara::core::Result<void> Update(ReadOnlyMemRegion in) noexcept = 0;

    /// @traceid{SWS_CRYPT_22114}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02302}
    /// @brief Update the digest calculation context by a new part of the message.
    ///       This method is convenient for processing of constant tags.
    /// @param[in] in  a byte value that is a part of input message
    /// @error CryptoErrorDomain::kProcessingNotStarted  if the digest calculation was not initiated
    ///         by a call of the @c Start() method
    ///
    /// @threadsafety{Thread-safe}
    
    virtual ara::core::Result<void> Update(std::uint8_t in) noexcept = 0;

    /// @traceid{SWS_CRYPT_22115}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02302}
    /// @uptrace{RS_CRYPTO_02203}
    /// @brief Finish the digest calculation and optionally produce the "signature" object.
    ///       Only after call of this method the digest can be signed, verified, extracted or compared!
    ///       If the signature object produced by a keyed MAC/HMAC/AE/AEAD algorithm then the dependence COUID of the
    ///       "signature" should be set to COUID of used symmetric key.
    /// @param[in] makeSignatureObject  if this argument is @c true then the method will also produce the signature
    ///            object
    /// @returns unique smart pointer to created signature object, if <tt>(makeSignatureObject == true)</tt> or
    ///          @c nullptr if <tt>(makeSignatureObject == false)</tt>
    /// @error CryptoErrorDomain::kProcessingNotStarted  if the digest calculation was not initiated
    ///         by a call of the @c Start() method
    /// @error CryptoErrorDomain::kUsageViolation  if the buffered digest belongs to a MAC/HMAC/AE/AEAD
    ///                context initialized by a key without @c kAllowSignature permission,
    ///                but <tt>(makeSignatureObject == true)</tt>
    ///
    /// @threadsafety{Thread-safe}
    
    virtual ara::core::Result<Signature::Uptrc> Finish(bool makeSignatureObject = false) noexcept = 0;

    /// @traceid{SWS_CRYPT_22116}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02203}
    /// @brief Get requested part of calculated digest to existing memory buffer.
    ///       Entire digest value is kept in the context up to next call @c Start(), therefore any its part can be
    ///       extracted again or verified.
    ///       If <tt>(full_digest_size <= offset)</tt> then <tt>return_size = 0</tt> bytes;
    ///       else <tt>return_size = min(output.size(), (full_digest_size - offset))</tt> bytes.
    ///       This method can be implemented as "inline" after standartization of function @c ara::core::memcpy().
    /// @param[out] output  an output buffer for storing the requested digest fragment (or fully)
    /// @param[in] offset  position of the first byte of digest that should be placed to the output buffer
    /// @returns number of digest bytes really stored to the output buffer (they are always <= @c output.size() and
    ///          denoted below as @a return_size)
    /// @error CryptoErrorDomain::kProcessingNotFinished  if the digest calculation was not finished
    ///                by a call of the @c Finish() method
    /// @error CryptoErrorDomain::kUsageViolation  if the buffered digest belongs to a MAC/HMAC/AE/AEAD
    ///                context initialized by a key without @c kAllowSignature permission
    /// @threadsafety{Thread-safe}
    
    virtual ara::core::Result<ara::core::Vector<ara::core::Byte>> GetDigest(std::size_t offset = 0
    ) const noexcept = 0;

    /// @traceid{SWS_CRYPT_22117}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02203}
    /// @brief Get requested part of calculated digest to pre-reserved managed container.
    ///       This method sets the size of the output container according to actually saved value.
    ///       Entire digest value is kept in the context up to next call @c Start(), therefore any its part can be
    ///       extracted again or verified.
    ///       If <tt>(full_digest_size <= offset)</tt> then <tt>return_size = 0</tt> bytes;
    ///       else <tt>return_size = min(output.capacity(), (full_digest_size - offset))</tt> bytes.
    /// @tparam Alloc  a custom allocator type of the output container
    /// @param[out] output  a managed container for storing the requested digest fragment (or fully)
    /// @param[in] offset  position of first byte of digest that should be placed to the output buffer
    /// @error CryptoErrorDomain::kProcessingNotFinished  if the digest calculation was not finished
    ///                by a call of the @c Finish() method
    /// @error CryptoErrorDomain::kUsageViolation  if the buffered digest belongs to a MAC/HMAC/AE/AEAD
    ///                context initialized by a key without @c kAllowSignature permission
    ///
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

    /// @traceid{SWS_CRYPT_22118}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02001}
    /// @uptrace{RS_CRYPTO_02003}
    /// @brief Set (deploy) a key to the message authn code algorithm context.
    /// @param[in] key  the source key object
    /// @param[in] transform  the "direction" indicator: deploy the key for direct transformation (if @c true)
    ///            or for reverse one (if @c false)
    /// @error CryptoErrorDomain::kIncompatibleObject  if the provided key object is
    ///                incompatible with this symmetric key context
    /// @error CryptoErrorDomain::kUsageViolation  if the transformation type associated with this context
    ///                (taking into account the direction specified by @c transform) is prohibited by
    ///                the "allowed usage" restrictions of provided key object
    ///
    /// @threadsafety{Thread-safe}
    
    virtual ara::core::Result<void> SetKey(const SymmetricKey& key
        , CryptoTransform transform = CryptoTransform::kMacGenerate
    ) noexcept = 0;

    /// @traceid{SWS_CRYPT_22119}@tracestatus{draft}
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

    /// @traceid{SWS_CRYPT_22120}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02108}
    /// @brief Clear the crypto context.
    ///
    /// @threadsafety{Thread-safe}
    
    virtual ara::core::Result<void> Reset() noexcept = 0;

};

}  // namespace cryp
}  // namespace crypto
}  // namespace ara

#endif  // ARA_CRYPTO_CRYP_MESSAGE_AUTHN_CODE_CTX_H_
