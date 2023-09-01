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
/// @brief Adaptive Autosar Crypto Stack. Cryptographic API. SymmetricBlockCipherCtx interface definition.

#ifndef ARA_CRYPTO_CRYP_SYMMETRIC_BLOCK_CIPHER_CTX_H_
#define ARA_CRYPTO_CRYP_SYMMETRIC_BLOCK_CIPHER_CTX_H_

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "ara/crypto/common/base_id_types.h"
#include "ara/crypto/common/mem_region.h"

#include "ara/crypto/cryp/crypto_context.h"
#include "ara/crypto/cryp/cryobj/symmetric_key.h"
#include "ara/crypto/cryp/crypto_service.h"

#include "ara/core/result.h"

namespace ara
{
namespace crypto
{
namespace cryp
{

//- @interface SymmetricBlockCipherCtx
///
/// @traceid{SWS_CRYPT_23700}@tracestatus{draft}
/// @uptrace{RS_CRYPTO_02201}
/// @brief Interface of a Symmetric Block Cipher Context with padding.
///
class SymmetricBlockCipherCtx : public CryptoContext
{
public:
    /// @traceid{SWS_CRYPT_23701}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02201}
    /// @brief Unique smart pointer of the interface.
    using Uptr = std::unique_ptr<SymmetricBlockCipherCtx>;

    /// @traceid{SWS_CRYPT_23702}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02006}
    /// @brief Get CryptoService instance.
    virtual CryptoService::Uptr GetCryptoService() const noexcept = 0;

    /// @traceid{SWS_CRYPT_23710}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02001}
    /// @uptrace{RS_CRYPTO_02003}
    /// @brief Set (deploy) a key to the symmetric algorithm context.
    /// @param[in] key  the source key object
    /// @param[in] transform  the "direction" indicator: deploy the key for direct transformation (if @c true)
    ///            or for reverse one (if @c false)
    /// @error CryptoErrorDomain::kIncompatibleObject  if the provided key object belongs to a different CryptoProvider instance
    /// @error CryptoErrorDomain::kUsageViolation  if the transformation type associated with this context
    ///                (taking into account the direction specified by @c transform) is prohibited by
    ///                the "allowed usage" restrictions of provided key object
    ///
    /// @threadsafety{Thread-safe}
    virtual ara::core::Result<void> SetKey(const SymmetricKey& key
        , CryptoTransform transform = CryptoTransform::kEncrypt
    ) noexcept = 0;

    /// @traceid{SWS_CRYPT_23711}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02309}
    /// @brief Get the kind of transformation configured for this context: kEncrypt or kDecrypt
    /// @returns @c CryptoTransform
    /// @error CryptoErrorDomain::kUninitializedContext, if SetKey() has not been called yet.
    /// @threadsafety{Thread-safe}
    virtual ara::core::Result<CryptoTransform> GetTransformation() const noexcept = 0;


    /// @traceid{SWS_CRYPT_23712}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02309}
    /// @brief Indicate that the currently configured transformation accepts only complete blocks of input data.
    /// @returns @c true if the transformation requires the maximum size of input data and @c false otherwise
    /// @error CryptoErrorDomain::kUninitializedContext  if the transformation direction of this context
    ///                is configurable during an initialization, but the context was not initialized yet
    /// @threadsafety{Thread-safe}
//    ara::core::Result<bool> IsMaxInputOnly() const noexcept
//    {
//        //return !IsEncryption();
//        auto result = GetTransformation();
//        if(!result)
//        {
//        	return ara::core::Result<bool>::FromError(result.Error());
//        }
//        if(CryptoTransform::kDecrypt == result.Value())
//        {
//            return ara::core::Result<bool>::FromValue(true);
//        }
//        else
//        {
//            return ara::core::Result<bool>::FromValue(false);
//        }
//    }
//
//    /// @traceid{SWS_CRYPT_23713}@tracestatus{draft}
//    /// @uptrace{RS_CRYPTO_02309}
//    /// @brief Indicate that the currently configured transformation can produce only complete blocks of output data.
//    /// @returns @c true if the transformation can produce only the maximum size of output data and @c false otherwise
//    /// @error CryptoErrorDomain::kUninitializedContext  if the transformation direction of this context
//    ///                is configurable during an initialization, but the context was not initialized yet
//    /// @threadsafety{Thread-safe}
//    ara::core::Result<bool> IsMaxOutputOnly() const noexcept
//    {
//    	auto result = GetTransformation();
//
//    	if(!result)
//    	{
//    		 return ara::core::Result<bool>::FromError(result.Error());
//    	}
//        return ara::core::Result<bool>::FromValue((GetTransformation().Value()==CryptoTransform::kEncrypt));
//    }

    /// @traceid{SWS_CRYPT_23714}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02108}
    /// @brief Clear the crypto context.
    ///
    /// @threadsafety{Thread-safe}
    virtual ara::core::Result<void> Reset() noexcept = 0;

    /// @traceid{SWS_CRYPT_23715}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02302}
    /// @brief Process (encrypt / decrypt) an input block according to the configuration.
    ///       The @c in must have a size that is divisible by the block size (see @c GetBlockSize()).
    ///       <b>The pointer to the input buffer must be aligned to the block-size boundary!</b>
    /// @returns  an output data buffer
    /// @param[in] in  an input data buffer
    /// @error CryptoErrorDomain::kUninitializedContext  if the context was not initialized by a key value
    /// @error CryptoErrorDomain::kInvalidInputSize  if size of the input buffer is not divisible by
    ///                the block size (see @c GetBlockSize())
    ///
    /// @threadsafety{Thread-safe}
    virtual ara::core::Result<ara::core::Vector<ara::core::Byte>> ProcessBlocks(ReadOnlyMemRegion in
    ) const noexcept = 0;

    /// @traceid{SWS_CRYPT_23716}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02201}
    /// @brief Process (encrypt / decrypt) an input block according to the configuration.
    /// @param[in] in  the input data block
    /// @param[in] suppressPadding  if @c true then this method doesn't apply padding, hence the input buffer be of the
    ///            same size as the block-size, i.e. either the data to be processed exactly fits the block-size or the
    ///            user must apply padding to the same effect.
    /// @returns the output buffer containing the transformation result
    /// @error:  CryptoErrorDomain::kInvalidInputSize  if the boolean parameter \ARApiRef{suppressPadding} was set to
    ///          TRUE and the provided input buffer does not match the block-size.
    /// @error CryptoErrorDomain::kUninitializedContext  if the context was not initialized by calling SetKey()
    ///
    /// @threadsafety{Thread-safe}
    virtual ara::core::Result<ara::core::Vector<ara::core::Byte>> ProcessBlock(ReadOnlyMemRegion in
        , bool suppressPadding = false
    ) const noexcept = 0;

    /// @traceid{SWS_CRYPT_23717}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02201}
    /// @brief Process (encrypt / decrypt) an input block according to the configuration.
    /// @tparam Alloc  a custom allocator type of the output container
    /// @returns  the managed container for output block
    /// @param[in] in  the input data block
    /// @param[in] suppressPadding  if @c true then the method doesn't apply the padding, but the payload should fill
    ///            the whole block of the plain data
    /// @error CryptoErrorDomain::kIncorrectInputSize  if the mentioned above rules about the input size is
    ///         violated
    /// @error CryptoErrorDomain::kInsufficientCapacity  if the @c out.size() is not enough to store the
    ///         transformation result
    /// @error CryptoErrorDomain::kUninitializedContext  if the context was not initialized by a key value
    ///
    /// @threadsafety{Thread-safe}
//    template <typename Alloc = VENDOR_IMPLEMENTATION_DEFINED>
//    ara::core::Result<ByteVector<Alloc>> ProcessBlock(ReadOnlyMemRegion in
//        , bool suppressPadding = false
//    ) const noexcept
//    {
//        ara::core::Result<ara::core::Vector<ara::core::Byte>> result = ProcessBlock(in, suppressPadding);
//
//        if (result)
//        {
//            ByteVector<Alloc> out;
//            out.resize(result.Value()->size());
//            memcpy(core::data(out), result.Value()->data(), result.Value()->size());
//            return ara::core::Result<ByteVector<Alloc>>::FromValue(out);
//        }
//        else
//        {
//            return ara::core::Result<ByteVector<Alloc>>::FromError(result.Error());
//        }
//    }
};

}  // namespace cryp
}  // namespace crypto
}  // namespace ara

#endif  // ARA_CRYPTO_CRYP_SYMMETRIC_BLOCK_CIPHER_CTX_H_
