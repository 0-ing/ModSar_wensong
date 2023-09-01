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
/// @brief Adaptive Autosar Crypto Stack. Cryptographic API. SymmetricKeyWrapperCtx interface definition.

#ifndef ARA_CRYPTO_CRYP_SYMMETRIC_KEY_WRAPPER_CTX_H_
#define ARA_CRYPTO_CRYP_SYMMETRIC_KEY_WRAPPER_CTX_H_

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

//- @interface SymmetricKeyWrapperCtx
///
/// @traceid{SWS_CRYPT_24000}@tracestatus{draft}
/// @uptrace{RS_CRYPTO_02104}
/// @uptrace{RS_CRYPTO_02208}
/// @brief Context of a symmetric key wrap algorithm (for AES it should be compatible with RFC3394 or RFC5649).
///       The public interface of this context is dedicated for raw key material wrapping/unwrapping, i.e. without
///       any meta-information assigned to the key material in source crypto object. But additionally this context
///       type should support some "hidden" low-level methods suitable for whole crypto object exporting/importing.
///       %Key Wrapping of a whole crypto object (including associated meta-information) can be done by methods:
///       @c ExportSecuredObject() and @c ImportSecuredObject(), but without compliance to RFC3394 or RFC5649.
///

class SymmetricKeyWrapperCtx : public CryptoContext
{
public:
    /// @traceid{SWS_CRYPT_24001}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02201}
    /// @brief Unique smart pointer of the interface.
    
    using Uptr = std::unique_ptr<SymmetricKeyWrapperCtx>;

    /// @traceid{SWS_CRYPT_24002}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02006}
    /// @brief Get ExtensionService instance.
    
    virtual ExtensionService::Uptr GetExtensionService() const noexcept = 0;

    /// @traceid{SWS_CRYPT_24011}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02201}
    /// @brief Get expected granularity of the target key (block size).
    ///       If the class implements RFC3394 (KW without padding) then this method should return 8
    ///       (i.e. 8 octets = 64 bits).
    ///       If the class implements RFC5649 (KW with padding) then this method should return 1 (i.e. 1 octet = 8 bits).
    ///
    /// @returns size of the block in bytes
    /// @threadsafety{Thread-safe}
    
    virtual std::size_t GetTargetKeyGranularity() const noexcept = 0;

    /// @traceid{SWS_CRYPT_24012}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02201}
    /// @brief Get maximum length of the target key supported by the implementation.
    ///       This method can be useful for some implementations different from RFC3394 / RFC5649.
    /// @returns maximum length of the target key in bits
    ///
    /// @threadsafety{Thread-safe}
    
    virtual std::size_t GetMaxTargetKeyLength() const noexcept = 0;

    /// @traceid{SWS_CRYPT_24013}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02201}
    /// @brief Calculate size of the wrapped key in bytes from original key length in bits.
    ///       This method can be useful for some implementations different from RFC3394 / RFC5649.
    /// @param[in] keyLength  original key length in bits
    /// @returns size of the wrapped key in bytes
    ///
    /// @threadsafety{Thread-safe}
    
    virtual std::size_t CalculateWrappedKeySize(std::size_t keyLength) const noexcept = 0;

    /// @traceid{SWS_CRYPT_24014}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02201}
    /// @brief Execute the "key wrap" operation for the provided key material.
    ///       This method should be compliant to RFC3394 or RFC5649, if an implementation is based on the AES block
    ///       cipher and applied to an AES key.
    ///       Method @c CalculateWrappedKeySize() can be used for size calculation of the required output buffer.
    /// @param[out] wrapped  an output buffer for the wrapped key
    /// @param[in] key  a key that should be wrapped
    /// @error CryptoErrorDomain::kInsufficientCapacity  if the size of the @c wrapped buffer is not enough
    ///                for storing the result
    /// @error CryptoErrorDomain::kInvalidInputSize  if the @c key object has an unsupported length
    /// @error CryptoErrorDomain::kUninitializedContext  if the context was not initialized by a key value
    ///
    /// @threadsafety{Thread-safe}
    
    virtual ara::core::Result<ara::core::Vector<ara::core::Byte>> WrapKeyMaterial(const RestrictedUseObject& key
    ) const noexcept  = 0;

    /// @traceid{SWS_CRYPT_24015}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02007}
    /// @brief Execute the "key unwrap" operation for provided BLOB and produce @c SecretSeed object.
    ///       This method should be compliant to RFC3394 or RFC5649, if implementation is based on the AES block cipher
    ///       and applied to an AES key material.
    ///       The created @c SecretSeed object has following attributes: session and non-exportable (because it was
    ///       imported without meta-information).
    /// @param[in] wrappedSeed  a memory region that contains wrapped seed
    /// @param[in] targetAlgId  the target symmetric algorithm identifier (also defines a target seed-length)
    /// @param[in] allowedUsage  allowed usage scope of the target seed
    /// @returns unique smart pointer to @c SecretSeed object, which keeps unwrapped key material
    /// @error CryptoErrorDomain::kInvalidInputSize  if the size of provided wrapped seed is unsupported
    /// @error CryptoErrorDomain::kUninitializedContext  if the context was not initialized by a key value
    ///
    /// @threadsafety{Thread-safe}
    
    virtual ara::core::Result<SecretSeed::Uptrc> UnwrapSeed(ReadOnlyMemRegion wrappedSeed,
        AlgId targetAlgId,
        SecretSeed::Usage allowedUsage
    ) const noexcept  = 0;

    /// @traceid{SWS_CRYPT_24016}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02115}
    /// @brief Execute the "key unwrap" operation for provided BLOB and produce @c Key object.
    ///       This method should be compliant to RFC3394 or RFC5649, if implementation is based on the AES block cipher
    ///       and applied to an AES key.
    ///       The created @c Key object has following attributes: session and non-exportable (because it was imported
    ///       without meta-information)!
    ///       @c SymmetricKey may be unwrapped in following way:
    ///          <tt>SymmetricKey::Uptrc key = SymmetricKey::Cast(UnwrapKey(wrappedKey, ...));</tt> @n
    ///       @c PrivateKey may be unwrapped in following way:
    ///          <tt>PrivateKey::Uptrc key = PrivateKey::Cast(UnwrapKey(wrappedKey, ...));</tt> @n
    ///       In both examples the @c Cast() method may additionally @b throw the @c BadObjectTypeException if an
    ///       actual type of the unwrapped key differs from the target one!
    /// @param[in] wrappedKey  a memory region that contains wrapped key
    /// @param[in] algId  an identifier of the target symmetric crypto algorithm
    /// @param[in] allowedUsage  bit-flags that define a list of allowed transformations' types in which the target key
    ///            can be used
    /// @returns unique smart pointer to @c Key object, which keeps unwrapped key material
    /// @error CryptoErrorDomain::kInvalidInputSize  if the size of provided wrapped key is unsupported
    /// @error CryptoErrorDomain::kUninitializedContext  if the context was not initialized by a key value
    ///
    /// @threadsafety{Thread-safe}
    
    virtual ara::core::Result<RestrictedUseObject::Uptrc> UnwrapKey(ReadOnlyMemRegion wrappedKey,
        AlgId algId,
        AllowedUsageFlags allowedUsage
    ) const noexcept = 0;

    /// @traceid{SWS_CRYPT_24017}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02115}
    /// @brief Execute the "key unwrap" operation for provided BLOB and produce a %Key object of expected type.
    ///       For additional details see @c UnwrapKey()
    /// @tparam ExpectedKey  the expected type of concrete key
    /// @param[in] wrappedKey  a memory region that contains wrapped key
    /// @param[in] algId  an identifier of the target symmetric crypto algorithm
    /// @param[in] allowedUsage  bit-flags that define a list of allowed transformations' types in which the target key
    ///            can be used
    /// @returns unique smart pointer to @c ExpectedKey object, which keeps unwrapped key material
    /// @error CryptoErrorDomain::kInvalidInputSize  if the size of provided wrapped key is unsupported
    /// @error CryptoErrorDomain::kUninitializedContext  if the context was not initialized by a key value
    
    template<typename ExpectedKey>
    ara::core::Result<typename ExpectedKey::Uptrc> UnwrapConcreteKey(ReadOnlyMemRegion wrappedKey,
        AlgId algId,
        AllowedUsageFlags allowedUsage
    ) noexcept; 
    // {
    //     ara::core::Result<Key::Uptrc> result = UnwrapKey(wrappedKey, algId, allowedUsage);
    //     if(result)
    //     {
    //         return ExpectedKey::Cast(std::move(result).Value());
    //     }
    //     else
    //     {
    //         return ara::core::Result<typename ExpectedKey::Uptrc>::FromError(result.Error());
    //     }
    // }
	
    /// @traceid{SWS_CRYPT_24018}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02001}
    /// @uptrace{RS_CRYPTO_02003}
    /// @brief Set (deploy) a key to the symmetric key wrapper algorithm context.
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
    
    virtual ara::core::Result<void> SetKey(const SymmetricKey& key, CryptoTransform transform) noexcept  = 0;

    /// @traceid{SWS_CRYPT_24019}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02108}
    /// @brief Clear the crypto context.
    ///
    /// @threadsafety{Thread-safe}
    
    virtual ara::core::Result<void> Reset() noexcept  = 0;

};

}  // namespace cryp
}  // namespace crypto
}  // namespace ara

#endif  // ARA_CRYPTO_CRYP_SYMMETRIC_KEY_WRAPPER_CTX_H_
