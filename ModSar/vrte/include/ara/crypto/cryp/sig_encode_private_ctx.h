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
/// @brief Adaptive Autosar Crypto Stack. Cryptographic API. SigEncodePrivateCtx interface definition.

#ifndef ARA_CRYPTO_CRYP_SIG_ENCODE_PRIVATE_CTX_H_
#define ARA_CRYPTO_CRYP_SIG_ENCODE_PRIVATE_CTX_H_

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "ara/crypto/cryp/crypto_context.h"
#include "ara/crypto/cryp/cryobj/private_key.h"
#include "ara/crypto/cryp/extension_service.h"
#include "ara/core/result.h"

namespace ara
{
namespace crypto
{
namespace cryp
{

//- @interface SigEncodePrivateCtx
///
/// @traceid{SWS_CRYPT_23200}@tracestatus{draft}
/// @uptrace{RS_CRYPTO_02202}
/// @uptrace{RS_CRYPTO_02204}
/// @brief A private key context for asymmetric signature calculation and short message encoding (RSA-like).
///       Restricted groups of trusted subscribers can use this primitive for simultaneous provisioning of
///       confidentiality, authenticity and non-repudiation of short messages, if the public key is generated
///       appropriately and kept in secret.
///

class SigEncodePrivateCtx : public CryptoContext
{
public:
    /// @traceid{SWS_CRYPT_23201}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02204}
    /// @uptrace{RS_CRYPTO_02202}
    /// @brief Unique smart pointer of the interface.
    
    using Uptr = std::unique_ptr<SigEncodePrivateCtx>;

    /// @traceid{SWS_CRYPT_23210}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02006}
    /// @brief Extension service member class
    
    virtual ExtensionService::Uptr GetExtensionService() const noexcept = 0;

    /// @traceid{SWS_CRYPT_23211}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02001}
    /// @uptrace{RS_CRYPTO_02003}
    /// @brief Set (deploy) a key to the sig encode private algorithm context.
    /// @param[in] key  the source key object
    /// @error CryptoErrorDomain::kIncompatibleObject  if the provided key object is
    ///                incompatible with this symmetric key context
    /// @error CryptoErrorDomain::kUsageViolation  if the transformation type associated with this context
    ///                is prohibited by
    ///                the "allowed usage" restrictions of provided key object
    ///
    /// @threadsafety{Thread-safe}
    
    virtual ara::core::Result<void> SetKey(const PrivateKey& key) noexcept = 0;

    /// @traceid{SWS_CRYPT_23212}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02108}
    /// @brief Clear the crypto context.
    ///
    /// @threadsafety{Thread-safe}
    
    virtual ara::core::Result<void> Reset() noexcept = 0;

    /// @traceid{SWS_CRYPT_23213}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02309}
    /// @brief Get maximum expected size of the input data block.
    ///       If <tt>(IsEncryption() == false)</tt> then a value returned by this method is independent from
    ///       the @c suppressPadding argument and it will be equal to the block size.
    /// @param[in] suppressPadding  if @c true then the method calculates the size for the case when the whole space of
    ///            the plain data block is used for the payload only
    /// @returns maximum size of the input data block in bytes
    ///
    /// @threadsafety{Thread-safe}
    
    virtual std::size_t GetMaxInputSize(bool suppressPadding = false) const noexcept = 0;

    /// @traceid{SWS_CRYPT_23214}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02309}
    /// @brief Get maximum possible size of the output data block.
    ///       If <tt>(IsEncryption() == true)</tt> then a value returned by this method is independent from the
    ///       @c suppressPadding argument and will be equal to the block size.
    /// @param[in] suppressPadding  if @c true then the method calculates the size for the case when the whole space of
    ///            the plain data block is used for the payload only
    /// @returns maximum size of the output data block in bytes
    ///
    /// @threadsafety{Thread-safe}
    
    virtual std::size_t GetMaxOutputSize(bool suppressPadding = false) const noexcept = 0;

    /// @traceid{SWS_CRYPT_23215}@tracestatus{draft}
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
    /// @returns  the output buffer
    /// @param[in] in  the input data block
    /// @param[in] suppressPadding  if @c true then the method doesn't apply the padding, but the payload should fill
    ///            the whole block of the plain data
    /// @returns actual size of output data (it always <tt><= out.size()</tt>) or 0 if the input data block has
    ///          incorrect content
    /// @error  CryptoErrorDomain::kIncorrectInputSize  if the mentioned above rules about the input size is
    ///         violated
    /// @error  CryptoErrorDomain::kUninitializedContext  if the context was not initialized by a key value
    ///
    /// @threadsafety{Thread-safe}
    
    virtual ara::core::Result<ara::core::Vector<ara::core::Byte>> SignAndEncode(ReadOnlyMemRegion in
    ) const noexcept = 0;

    /// @traceid{SWS_CRYPT_23216}@tracestatus{draft}
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
    /// @error  CryptoErrorDomain::kIncorrectInputSize  if the mentioned above rules about the input size is
    ///         violated
    /// @error  CryptoErrorDomain::kUninitializedContext  if the context was not initialized by a key value
    ///
    /// @threadsafety{Thread-safe}
    
//    template <typename Alloc = VENDOR_IMPLEMENTATION_DEFINED>
//    ara::core::Result<ByteVector<Alloc>> SignAndEncode(ReadOnlyMemRegion in
//    ) const noexcept
//    {
//        ara::core::Result<ara::core::Vector<ara::core::Byte>> result = SignAndEncode(in);
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

#endif  // ARA_CRYPTO_CRYP_SIG_ENCODE_PRIVATE_CTX_H_
