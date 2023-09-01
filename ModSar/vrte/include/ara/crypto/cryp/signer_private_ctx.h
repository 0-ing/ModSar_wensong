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
/// @brief Adaptive Autosar Crypto Stack. Cryptographic API. SignerPrivateCtx interface definition.

#ifndef ARA_CRYPTO_CRYP_SIGNER_PRIVATE_CTX_H_
#define ARA_CRYPTO_CRYP_SIGNER_PRIVATE_CTX_H_

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "ara/crypto/common/mem_region.h"

#include "ara/crypto/cryp/crypto_context.h"
#include "ara/crypto/cryp/cryobj/private_key.h"
#include "ara/crypto/cryp/cryobj/signature.h"
#include "ara/crypto/cryp/signature_service.h"

#include "ara/core/result.h"

namespace ara
{
namespace crypto
{
namespace cryp
{

//- @interface SignerPrivateCtx
///
/// @traceid{SWS_CRYPT_23500}@tracestatus{draft}
/// @uptrace{RS_CRYPTO_02204}
/// @brief Signature Private key Context interface.
///

class SignerPrivateCtx : public CryptoContext
{
public:
    /// @traceid{SWS_CRYPT_23501}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02204}
    /// @brief Unique smart pointer of the interface.
    
    using Uptr = std::unique_ptr<SignerPrivateCtx>;

    /// @traceid{SWS_CRYPT_23510}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02006}
    /// @brief Get SignatureService instance.
    
    virtual SignatureService::Uptr GetSignatureService() const noexcept = 0;

    /// @traceid{SWS_CRYPT_23511}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02204}
    /// @brief Sign a provided digest value stored in the hash-function context.
    ///       This method must put the hash-function algorithm ID and a @a COUID of the used key-pair to the resulting
    ///       signature object!
    ///       The user supplied @c context may be used for such algorithms as: Ed25519ctx, Ed25519ph, Ed448ph.
	///       If the target algorithm doesn't support the @c context argument then the empty (default) value must be
    ///       supplied!
    /// @param[in] hashFn  a finalized hash-function context that contains a digest value ready for sign
    /// @param[in] context  an optional user supplied "context" (its support depends from concrete algorithm)
    /// @returns unique smart pointer to serialized signature
    /// @error CryptoErrorDomain::kInvalidArgument  if hash-function algorithm does not comply with
    ///                the signature algorithm specification of this context
    /// @error CryptoErrorDomain::kInvalidInputSize  if the user supplied @c context has incorrect
    ///                (or unsupported) size
    /// @error CryptoErrorDomain::kProcessingNotFinished  if the method @c hash.Finish() was not called
    ///                before the call of this method
    /// @error CryptoErrorDomain::kUninitializedContext  this context was not initialized by a key value
    ///
    /// @threadsafety{Thread-safe}
    
    virtual ara::core::Result<Signature::Uptrc> SignPreHashed(const HashFunctionCtx& hashFn
        , ReadOnlyMemRegion context = ReadOnlyMemRegion()
    ) const noexcept = 0;

    /// @traceid{SWS_CRYPT_23512}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02204}
    /// @brief Sign a directly provided hash or message value.
    ///       This method can be used for implementation of the "multiple passes" signature algorithms that process
    ///       a message directly, i.e. without "pre-hashing" (like Ed25519ctx). But also this method is suitable for
    ///       implementation of the traditional signature schemes with pre-hashing (like Ed25519ph, Ed448ph, ECDSA).
	///       If the target algorithm doesn't support the @c context argument then the empty (default) value must be
    ///       supplied!
    /// @param[in] value  the (pre-)hashed or direct message value that should be signed
    /// @param[in] context  an optional user supplied "context" (its support depends from concrete algorithm)
    /// @returns actual size of the signature value stored to the output buffer
    /// @error CryptoErrorDomain::kInvalidInputSize  if size of the input @c value or @c context arguments
    ///                are incorrect / unsupported
    /// @error CryptoErrorDomain::kUninitializedContext  if the context was not initialized by a key value
    ///
    /// @threadsafety{Thread-safe}
    
    virtual ara::core::Result<ara::core::Vector<ara::core::Byte>> Sign(ReadOnlyMemRegion value
        , ReadOnlyMemRegion context = ReadOnlyMemRegion()
    ) const noexcept = 0;

    /// @traceid{SWS_CRYPT_23513}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02204}
    /// @brief Sign a directly provided digest value and create the @c Signature object.
    ///       This method must put the hash-function algorithm ID and a @a COUID of the used key-pair to the resulting
    ///       signature object!
    ///       The user supplied @c context may be used for such algorithms as: Ed25519ctx, Ed25519ph, Ed448ph.
    ///       If the target algorithm doesn't support the @c context argument then the empty (default) value must be
    ///       supplied!
    /// @param[in] hashAlgId  hash function algorithm ID
    /// @param[in] hashValue  hash function value (resulting digest without any truncations)
    /// @param[in] context  an optional user supplied "context" (its support depends from concrete algorithm)
    /// @returns unique smart pointer to serialized signature
    /// @error CryptoErrorDomain::kInvalidArgument  if hash-function algorithm does not comply with
    ///                the signature algorithm specification of this context
    /// @error CryptoErrorDomain::kInvalidInputSize  if the user supplied @c context has incorrect
    ///                (or unsupported) size
    /// @error CryptoErrorDomain::kUninitializedContext  this context was not initialized by a key value
    /// @threadsafety{Thread-safe}
    
    virtual ara::core::Result<Signature::Uptrc> SignPreHashed(AlgId hashAlgId
        , ReadOnlyMemRegion hashValue
        , ReadOnlyMemRegion context = ReadOnlyMemRegion()
    ) const noexcept = 0;

    /// @traceid{SWS_CRYPT_23514}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02204}
    /// @brief Sign a directly provided hash or message value.
    ///       This method can be used for implementation of the "multiple passes" signature algorithms that process
    ///       a message directly, i.e. without "pre-hashing" (like Ed25519ctx). But also this method is suitable for
    ///       implementation of the traditional signature schemes with pre-hashing (like Ed25519ph, Ed448ph, ECDSA).
    ///       This method sets the size of the output container according to actually saved value!
	///       If the target algorithm doesn't support the @c context argument then the empty (default) value must be
    ///       supplied!
    /// @tparam Alloc  a custom allocator type of the output container
    /// @param[out] signature  pre-reserved managed container for resulting signature
    /// @param[in] value  the (pre-)hashed or direct message value that should be signed
    /// @param[in] context  an optional user supplied "context" (its support depends from concrete algorithm)
    /// @error CryptoErrorDomain::kInvalidInputSize  if size of the input @c value or @c context arguments
    ///                are incorrect / unsupported
    /// @error CryptoErrorDomain::kInsufficientCapacity  if capacity of the output @c signature container
    ///                is not enough
    /// @error CryptoErrorDomain::kUninitializedContext  if the context was not initialized by a key value
    ///
    /// @threadsafety{Thread-safe}
    
//    template <typename Alloc = VENDOR_IMPLEMENTATION_DEFINED>
//    ara::core::Result<ByteVector<Alloc>> Sign(ReadOnlyMemRegion value
//        , ReadOnlyMemRegion context = ReadOnlyMemRegion()
//    ) const noexcept
//    {
//        ara::core::Result<ara::core::Vector<ara::core::Byte>> result = Sign(value, context);
//        if(result)
//        {
//            ByteVector<Alloc> signature;
//            signature.resize(result.Value()->size());
//            memcpy(core::data(signature), result.Value()->data(), result.Value()->size());
//            return ara::core::Result<ByteVector<Alloc>>::FromValue(signature);
//        }
//        else
//        {
//            return ara::core::Result<ByteVector<Alloc>>::FromError(result.Error());
//        }
//    }

    /// @traceid{SWS_CRYPT_23515}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02001}
    /// @uptrace{RS_CRYPTO_02003}
    /// @brief Set (deploy) a key to the signer private algorithm context.
    /// @param[in] key  the source key object
    /// @error CryptoErrorDomain::kIncompatibleObject  if the provided key object is
    ///                incompatible with this symmetric key context
    /// @error CryptoErrorDomain::kUsageViolation  if the transformation type associated with this context
    ///                is prohibited by     ///                the "allowed usage" restrictions of provided key object
    ///
    /// @threadsafety{Thread-safe}
    
    virtual ara::core::Result<void> SetKey(const PrivateKey& key) noexcept = 0;

    /// @traceid{SWS_CRYPT_23516}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02108}
    /// @brief Clear the crypto context.
    ///
    /// @threadsafety{Thread-safe}
    
    virtual ara::core::Result<void> Reset() noexcept = 0;

};

}  // namespace cryp
}  // namespace crypto
}  // namespace ara

#endif  // ARA_CRYPTO_CRYP_SIGNER_PRIVATE_CTX_H_
