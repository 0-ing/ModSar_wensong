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
/// @brief Adaptive Autosar Crypto Stack. Cryptographic API. PublicKey interface definition.

#ifndef ARA_CRYPTO_CRYP_PUBLIC_KEY_H_
#define ARA_CRYPTO_CRYP_PUBLIC_KEY_H_

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "ara/crypto/common/base_id_types.h"
#include "ara/crypto/common/mem_region.h"
#include "ara/crypto/common/serializable.h"

#include "ara/crypto/cryp/cryobj/restricted_use_object.h"
#include "ara/crypto/cryp/hash_function_ctx.h"

namespace ara
{
namespace crypto
{
namespace cryp
{
//- @interface PublicKey
///
/// @traceid{SWS_CRYPT_22700}@tracestatus{draft}
/// @uptrace{RS_CRYPTO_02202}
/// @brief General Asymmetric Public %Key interface.
///

class PublicKey : public RestrictedUseObject, public Serializable
{
public:
    /// @traceid{SWS_CRYPT_22701}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02202}
    /// @brief Unique smart pointer of the interface.

    using Uptrc = std::unique_ptr<const PublicKey>;

    /// @traceid{SWS_CRYPT_22702}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02202}
    /// @brief const object type

    static const CryptoObjectType kObjectType = CryptoObjectType::kPublicKey;

    /// @traceid{SWS_CRYPT_22711}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02202}
    /// @brief Check the key for its correctness.
    /// @param[in] strongCheck  the severeness flag that indicates type of the required check:
    ///            strong (if @c true) or fast (if @c false)
    /// @returns @c true if the key is correct
    /// @threadsafety{Thread-safe}

    virtual bool CheckKey(bool strongCheck = true) const noexcept = 0;

    /// @traceid{SWS_CRYPT_22712}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02202}
    /// @brief Calculate hash of the Public Key value.
    ///        The original public key value BLOB is available via the @c Serializable interface.
    /// @param[in] hashFunc  a hash-function instance that should be used the hashing
    /// @returns a buffer preallocated for the resulting hash value

    /// @error SecurityErrorDomain::kInsufficientCapacity  if size of the hash buffer is not enough
    /// for
    ///                storing of the result
    /// @error SecurityErrorDomain::kIncompleteArgState  if the @c hashFunc context is not
    /// initialized
    /// @threadsafety{Thread-safe}
    virtual ara::core::Result<ara::core::Vector<ara::core::Byte>>
    HashPublicKey(HashFunctionCtx& hashFunc) const noexcept = 0;

    /// @traceid{SWS_CRYPT_22713}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02202}
    /// @brief Calculate hash of the Public Key value.
    ///    This method sets the size of the output container according to actually saved value!
    ///    The original public key value BLOB is available via the Serializable interface.
    /// @tparam Alloc  a custom allocator type of the output container
    /// @returns  pre-reserved managed container for the resulting hash value
    /// @param[in] hashFunc  a hash-function instance that should be used the hashing

    /// @error SecurityErrorDomain::kInsufficientCapacity  if capacity of the hash buffer is not
    /// enough for storing of the result
    /// @error SecurityErrorDomain::kIncompleteArgState  if the @c hashFunc context is not
    /// initialized
    /// @threadsafety{Thread-safe}

//    template<typename Alloc = VENDOR_IMPLEMENTATION_DEFINED>
//    ara::core::Result<ByteVector<Alloc>> HashPublicKey(HashFunctionCtx& hashFunc) const noexcept
//    {
        //        ara::core::Result<ara::core::Vector<ara::core::Byte>> result = HashPublicKey(
        //        hashFunc); if(result)
        //        {
        //            ByteVector<Alloc> hash;
        //            hash.resize(result.Value()->size());
        //            memcpy(core::data(hash), result.Value()->data(), result.Value()->size());
        //            return ara::core::Result<ByteVector<Alloc>>::FromValue(hash);
        //        }
        //        else
        //        {
        //            return ara::core::Result<ByteVector<Alloc>>::FromError(result.Error());
        //        }
//    }
};

} // namespace cryp
} // namespace crypto
} // namespace ara

#endif // ARA_CRYPTO_CRYP_PUBLIC_KEY_H_
