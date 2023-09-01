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
/// @brief Adaptive Autosar Crypto Stack. Cryptographic API. EncryptorPublicCtx interface definition.

#ifndef ARA_CRYPTO_CRYP_ENCRYPTOR_PUBLIC_CTX_H_
#define ARA_CRYPTO_CRYP_ENCRYPTOR_PUBLIC_CTX_H_

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "ara/crypto/cryp/crypto_context.h"
#include "ara/crypto/cryp/cryobj/public_key.h"
#include "ara/crypto/cryp/crypto_service.h"
#include "ara/core/result.h"

namespace ara
{
namespace crypto
{
namespace cryp
{

//- @interface EncryptorPublicCtx
///
/// @traceid{SWS_CRYPT_21000}@tracestatus{draft}
/// @uptrace{RS_CRYPTO_02202}
/// @brief Asymmetric Encryption Public key Context interface.
///
class EncryptorPublicCtx : public CryptoContext
{

public:
    /// @traceid{SWS_CRYPT_21001}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02202}
    /// @brief Unique smart pointer of the interface.
        
    using Uptr = std::unique_ptr<EncryptorPublicCtx>;

    /// @traceid{SWS_CRYPT_21002}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02006}
    /// @brief Get CryptoService instance.
        
    virtual CryptoService::Uptr GetCryptoService() const noexcept = 0;

    /// @traceid{SWS_CRYPT_21010}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02001}
    /// @uptrace{RS_CRYPTO_02003}
    /// @brief Set (deploy) a key to the encryptor public algorithm context.
    /// @param[in] key  the source key object

    /// @error CryptoErrorDomain::kIncompatibleObject  if the provided key object is
    ///                incompatible with this symmetric key context
    /// @error CryptoErrorDomain::kUsageViolation  if the transformation type associated with this context
    ///                is prohibited by
    ///                the "allowed usage" restrictions of provided key object
    ///
    /// @threadsafety{Thread-safe}
        
    virtual ara::core::Result<void> SetKey(const PublicKey& key) noexcept  = 0;

    /// @traceid{SWS_CRYPT_21011}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02202}
    /// @brief Clear the crypto context.
    ///
    /// @threadsafety{Thread-safe}
        
    virtual ara::core::Result<void> Reset() noexcept  = 0;

    /// @traceid{SWS_CRYPT_21012}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02202}
    /// @brief Process (encrypt / decrypt) an input block according to the cryptor configuration.
	///       Encryption with <tt>(suppressPadding == true)</tt> expects that:
    ///       <tt>in.size() == GetMaxInputSize(true) && out.size() >= GetMaxOutputSize(true)</tt>.
    ///       Encryption with <tt>(suppressPadding == false)</tt> expects that:
    ///       <tt>in.size() <= GetMaxInputSize(false) && in.size() > 0 && out.size() >= GetMaxOutputSize(false)</tt>.
    ///       Decryption expects that:
    ///       <tt>in.size() == GetMaxInputSize() && out.size() >= GetMaxOutputSize(suppressPadding)</tt>.
    ///       The case <tt>(out.size() < GetMaxOutputSize())</tt> should be used with caution, only if you are strictly
    ///       certain about the size of the output data!
    ///       In case of <tt>(suppressPadding == true)</tt> the actual size of plain text should be equal to full size
    ///       of the plain data block (defined by the algorithm)!
    /// @param[in] in  the input data block
    /// @param[in] suppressPadding  if @c true then the method doesn't apply the padding, but the payload should fill
    ///            the whole block of the plain data
    /// @returns actual size of output data (it always <tt><= out.size()</tt>) or 0 if the input data block has
    ///          incorrect content

    /// @error CryptoErrorDomain::kIncorrectInputSize  if the mentioned above rules about the input size is
    ///         violated
    /// @error CryptoErrorDomain::kUninitializedContext  if the context was not initialized by a key value
    ///
    /// @threadsafety{Thread-safe}
        
    virtual ara::core::Result<ara::core::Vector<ara::core::Byte>> ProcessBlock(ReadOnlyMemRegion in
        , bool suppressPadding = false
    ) const noexcept  = 0;

    /// @traceid{SWS_CRYPT_21013}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02202}
    /// @brief Process (encrypt / decrypt) an input block according to the cryptor configuration.
	///       This method sets the size of the output container according to actually saved value!
    ///       Encryption with <tt>(suppressPadding == true)</tt> expects what:
    ///       <tt>in.size() == GetMaxInputSize(true) && out.capacity() >= GetMaxOutputSize(true)</tt>.
    ///       Encryption with <tt>(suppressPadding == false)</tt> expects what:
    ///     <tt>in.size() <= GetMaxInputSize(false) && in.size() > 0 && out.capacity() >= GetMaxOutputSize(false)</tt>.
    ///       Decryption expects what:
    ///       <tt>in.size() == GetMaxInputSize() && out.capacity() >= GetMaxOutputSize(suppressPadding)</tt>.
    ///       The case <tt>(out.capacity() < GetMaxOutputSize())</tt> should be used with caution, only if you are
    ///       strictly certain about the size of the output data!
    ///       In case of <tt>(suppressPadding == true)</tt> the actual size of plain text should be equal to full size
    ///       of the plain data block (defined by the algorithm)!
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

#endif  // ARA_CRYPTO_CRYP_ENCRYPTOR_PUBLIC_CTX_H_
