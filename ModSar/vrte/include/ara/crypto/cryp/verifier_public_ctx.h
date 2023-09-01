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
/// @brief Adaptive Autosar Crypto Stack. Cryptographic API. VerifierPublicCtx interface definition.

#ifndef ARA_CRYPTO_CRYP_VERIFIER_PUBLIC_CTX_H_
#define ARA_CRYPTO_CRYP_VERIFIER_PUBLIC_CTX_H_

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "ara/crypto/common/mem_region.h"

#include "ara/crypto/cryp/crypto_context.h"
#include "ara/crypto/cryp/cryobj/public_key.h"
#include "ara/crypto/cryp/cryobj/signature.h"
#include "ara/crypto/cryp/signature_service.h"

#include "ara/core/result.h"

namespace ara
{
namespace crypto
{
namespace cryp
{

//- @interface VerifierPublicCtx
///
/// @traceid{SWS_CRYPT_24100}@tracestatus{draft}
/// @uptrace{RS_CRYPTO_02204}
/// @brief Signature Verification Public key Context interface.
///

class VerifierPublicCtx : public CryptoContext
{
public:
    /// @traceid{SWS_CRYPT_24101}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02204}
    /// @brief Unique smart pointer of the interface.
    
    using Uptr = std::unique_ptr<VerifierPublicCtx>;

    /// @traceid{SWS_CRYPT_24102}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02006}
    /// @brief Extension service member class
    
    virtual SignatureService::Uptr GetSignatureService() const noexcept = 0;

    /// @traceid{SWS_CRYPT_24111}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02204}
    ///
    /// @brief Verify signature by a digest value stored in the hash-function context. This is a pass-through
    ///        interface to SWS_CRYPT_24113 for developer convenience, i.e. it adds additional input checks
    ///        amd then calls the verify() interface from SWS_CRYPT_24113.
    ///
	/// @param[in] hashAlgId  hash function algorithm ID
    /// @param[in] hashValue  hash function value (resulting digest without any truncations)
    /// @param[in] signature  the signature object for verification
    /// @param[in] context  an optional user supplied "context" (its support depends from concrete algorithm)
    ///
    /// @returns @c true if the signature was verified successfully and @c false otherwise
    ///
    /// @error  CryptoErrc::kProcessingNotFinished  if the method @c hashFn.Finish() was not called
    ///                before this method call <br>
    /// @error  CryptoErrc::kInvalidArgument  if the CryptoAlgId of @c hashFn differs from the CryptoAlgId of this context <br>
	/// @error CryptoErrc::kInvalidInputSize if the size of the supplied @c context is incompatible with the configured signature algorithm.
    /// @threadsafety{Thread-safe}
    ///

    virtual ara::core::Result<bool> VerifyPrehashed(CryptoAlgId hashAlgId
            , ReadOnlyMemRegion hashValue
            , const Signature& signature
            , ReadOnlyMemRegion context = ReadOnlyMemRegion()
    ) const noexcept =0;


    /// @traceid{SWS_CRYPT_24112}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02204}
    /// @brief Verify signature BLOB by a directly provided hash or message value.
    ///  This method can be used for implementation of the "multiple passes" signature algorithms that process
    ///       a message directly, i.e. without "pre-hashing" (like Ed25519ctx). But also this method is suitable for
    ///       implementation of the traditional signature schemes with pre-hashing (like Ed25519ph, Ed448ph, ECDSA).
    ///  If the target algorithm doesn't support the @c context argument then the empty (default) value must be
    ///       supplied! The user supplied @c context may be used for such algorithms as: Ed25519ctx, Ed25519ph, Ed448ph.
    ///
    /// @param[in] value  the (pre-)hashed or direct message value that should be verified
    /// @param[in] signature  the signature BLOB for the verification (the BLOB contains a plain sequence of the digital
    ///            signature components located in fixed/maximum length fields defined by the algorithm specification,
    ///            and each component is presented by a raw bytes sequence padded by zeroes to full length of the field;
    ///            e.g. in case of (EC)DSA-256 (i.e. length of the q module is 256 bits) the signature BLOB must have two
    ///            fixed-size fields: 32 + 32 bytes, for R and S components respectively, i.e. total BLOB size is 64 bytes)	
    /// @param[in] context  an optional user supplied "context" (its support depends from concrete algorithm)
    ///
    /// @returns @c true if the signature was verified successfully and @c false otherwise
    ///
    ///
    /// @error  CryptoErrc::kUninitializedContext  if the context was not initialized by a key value <br>
    /// @error  CryptoErrc::kInvalidInputSize  if the @c context argument has unsupported size <br>
    ///
    /// @threadsafety{Thread-safe}
    
    virtual ara::core::Result<bool> Verify(ReadOnlyMemRegion value
        , ReadOnlyMemRegion signature
        , ReadOnlyMemRegion context = ReadOnlyMemRegion()
    ) const noexcept = 0;

    /// @traceid{SWS_CRYPT_24113}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02204}
    /// @brief Verify signature by a digest value stored in the hash-function context. This is a pass-through
    ///        interface to SWS_CRYPT_24112 for developer convenience, i.e. it adds additional input checks
    ///        amd then calls the default verify() interface.
    ///
    /// @param[in] hashFn  hash function to be used for hashing
    /// @param[in] signature  the signature object for the verification
    /// @param[in] context    an optional user supplied "context" (its support depends from concrete algorithm)
    ///
    /// @returns @c true if the signature was verified successfully and @c false otherwise
    ///
    /// @error  CryptoErrc::kIncompatibleObject if the CryptoAlgId of this context does not match the
    ///                CryptoAlgId of @c signature; or the required CryptoAlgId of the hash is not kAlgIdDefault
    ///                and the required hash CryptoAlgId of this context does not match @c hashAlgId or the hash
    ///                CryptoAlgId of @c signature <br>
    /// @error  CryptoErrc::kIncompatibleArguments if the provided hashAlgId is not kAlgIdDefault and the CryptoAlgId of the provided signature object does not match the provided hashAlgId
    /// @error  CryptoErrc::kBadObjectReference  if the provided signature object does not reference the public key loaded to the context,
    ///                                                   i.e. if the COUID of the public key in the context is not equal to the COUID referenced from the signature object.
    ///
	/// @error CryptoErrc::kInvalidInputSize if the size of the supplied @c context or @c hashValue is incompatible with the configured signature algorithm.
    /// @threadsafety{Thread-safe}
    
    virtual ara::core::Result<bool> VerifyPrehashed(const HashFunctionCtx& hashFn    
        , const Signature& signature 
        , ReadOnlyMemRegion context = ReadOnlyMemRegion()    
    ) const noexcept =0;

	/// @traceid{SWS_CRYPT_24114}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02204}
    /// 
    /// @brief Verify signature by a digest value stored in the hash-function context. This is a pass-through
    ///        interface to SWS_CRYPT_24112 for developer convenience, i.e. it adds additional input checks
    ///        amd then calls the default verify() interface.
    ///
    /// @param[in] hashFn  hash function to be used for hashing
	/// @param[in] signature  the data BLOB to be verified
    /// @param[in] context  an optional user supplied "context" (its support depends from concrete algorithm)
    ///
    /// @returns @c true if the signature was verified successfully and @c false otherwise
    ///
    /// @error  CryptoErrc::kProcessingNotFinished  if the method @c hashFn.Finish() was not called
    ///                before this method call <br>
    /// @error  CryptoErrc::kInvalidArgument  if the CryptoAlgId of @c hashFn differs from the CryptoAlgId of this context <br>
    /// @threadsafety{Thread-safe}
    /// @error CryptoErrc::kInvalidInputSize if the size of the supplied @c context or @c signature is incompatible with the configured signature algorithm.
	
    virtual ara::core::Result<bool> VerifyPrehashed(const HashFunctionCtx& hashFn  
        , ReadOnlyMemRegion signature
        , ReadOnlyMemRegion context = ReadOnlyMemRegion()    
	) const noexcept =0;

    /// @traceid{SWS_CRYPT_24115}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02001}
    /// @uptrace{RS_CRYPTO_02003}
    /// @brief Set (deploy) a key to the verifier public algorithm context.
    /// @param[in] key  the source key object
    /// @error  CryptoErrc::kIncompatibleObject  if the provided key object is
    ///                incompatible with this symmetric key context <br>
    /// @error  CryptoErrc::kUsageViolation  if the transformation type associated with this context
    ///                is prohibited by the "allowed usage" restrictions of provided key object <br>
    ///
    /// @threadsafety{Thread-safe}
    
    virtual ara::core::Result<void> SetKey(const PublicKey& key) noexcept = 0;

    /// @traceid{SWS_CRYPT_24116}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02108}
    /// @brief Clear the crypto context.
    ///
    /// @threadsafety{Thread-safe}
    
    virtual ara::core::Result<void> Reset() noexcept = 0;

};

//inline ara::core::Result<bool> VerifierPublicCtx::VerifyPrehashed(CryptoAlgId hashAlgId
//    , ReadOnlyMemRegion hashValue
//    , const Signature& signature
//    , ReadOnlyMemRegion context
//) const noexcept
//{
//
//    using Res = ara::core::Result<bool>;
//    if(this->GetCryptoPrimitiveId()->GetPrimitiveId() != signature.GetCryptoPrimitiveId()->GetPrimitiveId())
//    {
//        return Res::FromError(ara::crypto::MakeErrorCode(CryptoErrc::kIncompatibleObject, 1));
//    }
//    if(this->GetSignatureService()->GetRequiredHashAlgId() != kAlgIdDefault)
//    {
//        if(signature.GetHashAlgId() != this->GetSignatureService()->GetRequiredHashAlgId())
//        {
//            return Res::FromError(ara::crypto::MakeErrorCode(CryptoErrc::kIncompatibleObject, 1));
//        }
//        if(hashAlgId != this->GetSignatureService()->GetRequiredHashAlgId())
//        {
//            return Res::FromError(ara::crypto::MakeErrorCode(CryptoErrc::kIncompatibleObject, 2));
//        }
//    }
//    else
//    {
//        if(hashAlgId != signature.GetHashAlgId())
//        {
//            //return Res::FromError(ara::crypto::MakeErrorCode(CryptoErrc::kIncompatibleArguments, (2 << 8) | 1));
//        }
//    }
//    /* The supplied Signature object must depend on the same PublicKey used to verify it. */
//    CryptoObject::COIdentifier appliedID = signature.HasDependence();
//    if(CryptoObjectType::kPublicKey != appliedID.mCOType ||
//       this->GetSignatureService()->GetActualKeyCOUID() != appliedID.mCouid)
//    {
//        return Res::FromError(ara::crypto::MakeErrorCode(CryptoErrc::kBadObjectReference, 1));
//    }
//
//    return Verify(hashValue, signature.GetValue(), context);
//}
//
//
//inline ara::core::Result<bool> VerifierPublicCtx::VerifyPrehashed(const HashFunctionCtx& hashFn
//    , const Signature& signature
//    , ReadOnlyMemRegion context
//) const noexcept
//{
//    if(!hashFn.GetDigestService()->IsFinished())
//    {
//        return ara::core::Result<bool>::FromError(ara::crypto::MakeErrorCode(CryptoErrc::kProcessingNotFinished, 1));
//    }
//    if( this->GetSignatureService()->GetRequiredHashAlgId() != kAlgIdDefault &&
//    		this->GetSignatureService()->GetRequiredHashAlgId() != hashFn.GetCryptoPrimitiveId()->GetPrimitiveId())
//    {
//    	return ara::core::Result<bool>::FromError(ara::crypto::MakeErrorCode(CryptoErrc::kInvalidArgument, 1));
//    }
//    return Verify(hashFn.GetCryptoPrimitiveId()->GetPrimitiveId(), hashFn.GetValue(), signature, context);
//}
//
//inline ara::core::Result<bool> VerifierPublicCtx::VerifyPrehashed(const HashFunctionCtx& hashFn
//    , ReadOnlyMemRegion signature
//    , ReadOnlyMemRegion context
//) const noexcept
//{
//    using Res = ara::core::Result<bool>;
//    if(!hashFn.GetDigestService()->IsFinished())
//    {
//        return Res::FromError(ara::crypto::MakeErrorCode(CryptoErrc::kProcessingNotFinished, 1));
//    }
//    if( this->GetSignatureService()->GetRequiredHashAlgId() != kAlgIdDefault &&
//        this->GetSignatureService()->GetRequiredHashAlgId() != hashFn.GetCryptoPrimitiveId()->GetPrimitiveId())
//    {
//        return Res::FromError(ara::crypto::MakeErrorCode(CryptoErrc::kInvalidArgument, 1));
//    }
//    return Verify(hashFn.GetValue(), signature, context);
//}


}  // namespace cryp
}  // namespace crypto
}  // namespace ara

#endif  // ARA_CRYPTO_CRYP_VERIFIER_PUBLIC_CTX_H_
