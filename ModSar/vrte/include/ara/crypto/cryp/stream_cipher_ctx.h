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
/// @brief Adaptive Autosar Crypto Stack. Cryptographic API. StreamCipherCtx interface definition.

#ifndef ARA_CRYPTO_CRYP_STREAM_CIPHER_CTX_H_
#define ARA_CRYPTO_CRYP_STREAM_CIPHER_CTX_H_

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "ara/crypto/common/mem_region.h"
#include "ara/crypto/common/base_id_types.h"

#include "ara/crypto/cryp/crypto_context.h"
#include "ara/crypto/cryp/cryobj/symmetric_key.h"
#include "ara/crypto/cryp/cryobj/secret_seed.h"
#include "ara/crypto/cryp/block_service.h"

#include "ara/core/result.h"

namespace ara
{
namespace crypto
{
namespace cryp
{

//- @interface StreamCipherCtx
///
/// @traceid{SWS_CRYPT_23600}@tracestatus{draft}
/// @uptrace{RS_CRYPTO_02201}
/// @brief Generalized Stream Cipher Context interface (it covers all modes of operation).
///

class StreamCipherCtx : public CryptoContext
{
public:
    /// @traceid{SWS_CRYPT_23601}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02201}
    /// @brief Unique smart pointer of the interface.
    
    using Uptr = std::unique_ptr<StreamCipherCtx>;

    /// @traceid{SWS_CRYPT_23602}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02006}
    /// @brief Get BlockService instance.
    
    virtual BlockService::Uptr GetBlockService() const noexcept = 0;

    /// @traceid{SWS_CRYPT_23611}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02309}
    /// @brief Check the operation mode for the bytewise property.
    /// @returns @c true if the mode can process messages the byte-by-byte (without padding up to the block boundary)
    ///          and @c false if only the block-by-block (only full blocks can be processed, the padding is mandatory)
    ///
    /// @threadsafety{Thread-safe}
    
    virtual bool IsBytewiseMode() const noexcept = 0;

    /// @traceid{SWS_CRYPT_23612}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02309}
    /// @brief Check if the seek operation is supported in the current mode.
    /// @returns @c true the seek operation is supported in the current mode and @c false otherwise
    ///
    /// @threadsafety{Thread-safe}
    
    virtual bool IsSeekableMode() const noexcept = 0;

    /// @traceid{SWS_CRYPT_23613}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02304}
    /// @brief Set the position of the next byte within the stream of the encryption/decryption gamma.
    /// @param[in] offset  the offset value in bytes, relative to begin or current position in the gamma stream
    /// @param[in] fromBegin  the starting point for positioning within the stream: from begin (if @c true) or from
    ///            current position (if @c false)
    /// @error CryptoErrorDomain::kUnsupported  if the seek operation is not supported by the current mode
    /// @error CryptoErrorDomain::kProcessingNotStarted  if the data processing was not started by a call of
    ///                the @c Start() method
    /// @error CryptoErrorDomain::kBelowBoundary  if the @c offset value is incorrect (in context of the
    ///                the @c fromBegin argument), i.e. it points before begin of the stream (note: it is an optional
    ///                error condition)
    /// @error CryptoErrorDomain::kInvalidArgument  if the offset is not aligned to the required boundary
    ///                (see @c IsBytewiseMode())
    ///
    /// @threadsafety{Thread-safe}
    
    virtual ara::core::Result<void> Seek(std::int64_t offset, bool fromBegin = true) noexcept = 0;

    /// @traceid{SWS_CRYPT_23614}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02302}
    /// @brief Processe initial parts of message aligned to the block-size boundary.
    ///       It is a copy-optimized method that doesn't use the internal cache buffer! It can be used only before
    ///       processing of any non-aligned to the block-size boundary data.
    ///       <b>Pointers to the input and output buffers must be aligned to the block-size boundary!</b>
    ///       The input and output buffers may completely coincide, but they must not partially intersect!
    /// @returns  an output data buffer
    /// @param[in] in  an input data buffer
    /// @error CryptoErrorDomain::kIncompatibleArguments  if sizes of the input and output buffers
    ///                are not equal
    /// @error CryptoErrorDomain::kInvalidInputSize  if size of the input buffer is not divisible by
    ///                the block size (see @c GetBlockSize())
    /// @error CryptoErrorDomain::kInOutBuffersIntersect  if the input and output buffers partially intersect
    /// @error CryptoErrorDomain::kInvalidUsageOrder  if this method is called after processing of
    ///                non-aligned data (to the block-size boundary)
    /// @error CryptoErrorDomain::kProcessingNotStarted  if the data processing was not started by a call of
    ///                the @c Start() method
    ///
    /// @threadsafety{Thread-safe}
    
    virtual ara::core::Result<ara::core::Vector<ara::core::Byte>> ProcessBlocks(ReadOnlyMemRegion in
    ) noexcept = 0;

    /// @traceid{SWS_CRYPT_23615}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02302}
    /// @brief Processe initial parts of message aligned to the block-size boundary.
    ///       It is a copy-optimized method that doesn't use internal cache buffer! It can be used up to first non-block
    ///       aligned data processing.
    ///       <b>Pointer to the input-output buffer must be aligned to the block-size boundary!</b>
    /// @param[in,out] inOut  an input and output data buffer, i.e. the whole buffer should be updated
    /// @error CryptoErrorDomain::kInvalidInputSize  if size of the @c inOut buffer is not divisible by
    ///                the block size (see @c GetBlockSize())
    /// @error CryptoErrorDomain::kInvalidUsageOrder  if this method is called after processing of
    ///                non-aligned data (to the block-size boundary)
    /// @error CryptoErrorDomain::kProcessingNotStarted  if the data processing was not started by a call of
    ///                the @c Start() method
    ///
    /// @threadsafety{Thread-safe}
    
    virtual ara::core::Result<void> ProcessBlocks(ReadWriteMemRegion inOut) noexcept = 0;

    /// @traceid{SWS_CRYPT_23616}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02302}
    /// @brief Processe a non-final part of message (that is not aligned to the block-size boundary).
    ///       If <tt>(IsBytewiseMode() == false)</tt> then it @b must be:
    ///       <tt>bs = GetBlockSize(), out.size() >= (((in.size() + bs - 1) / bs) * bs)</tt>
    ///       If <tt>(IsBytewiseMode() == true)</tt>  then it @b must be:  <tt>out.size() >= in.size()</tt>
    ///       The input and output buffers must not intersect!
    ///       This method is "copy inefficient", therefore it should be used only in conditions when an application
    ///       cannot control the chunking of the original message!
    /// @param[in] in  an input data buffer
    /// @returns an output data buffer
    /// @error CryptoErrorDomain::kInsufficientCapacity  if the output buffer has capacity
    ///                insufficient for placing of the transformation result
    /// @error CryptoErrorDomain::kInOutBuffersIntersect  if the input and output buffers intersect
    /// @error CryptoErrorDomain::kProcessingNotStarted  if data processing was not started by a call of
    ///                the @c Start() method
    ///
    /// @threadsafety{Thread-safe}
    
    virtual ara::core::Result<ara::core::Vector<ara::core::Byte>>ProcessBytes(ReadOnlyMemRegion in
    ) noexcept = 0;

    /// @traceid{SWS_CRYPT_23617}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02302}
    /// @brief Processes a non-final part of message (that is not aligned to the block-size boundary).
    ///       This method sets size of the output container according to actually saved value.
    ///       If <tt>(IsBytewiseMode() == false)</tt> then it @b must be:
    ///       <tt>bs = GetBlockSize(), out.capacity() >= (((in.size() + bs - 1) / bs) * bs)</tt>
    ///       If <tt>(IsBytewiseMode() == true)</tt>  then it @b must be:  <tt>out.capacity() >= in.size()</tt>
    ///       This method is "copy inefficient", therefore it should be used only in conditions when an application
    ///       cannot control the chunking of the original message!
    ///       The input buffer must not point inside the output container!
    /// @tparam Alloc  a custom allocator type of the output container
    /// @returns  a managed container for the output data
    /// @param[in] in  an input data buffer
    /// @error CryptoErrorDomain::kInsufficientCapacity  if capacity of the output container is not enough
    /// @error CryptoErrorDomain::kInOutBuffersIntersect  if the input buffer points inside of
    ///                the preallocated output container
    /// @error:  CryptoErrorDomain::kProcessingNotStarted  if data processing was not started by a call of
    ///                the @c Start() method
    ///
    /// @threadsafety{Thread-safe}
    
//    template <typename Alloc = VENDOR_IMPLEMENTATION_DEFINED>
//    ara::core::Result<ByteVector<Alloc>> ProcessBytes( ReadOnlyMemRegion in
//    ) noexcept
//    {
//        ara::core::Result<ara::core::Vector<ara::core::Byte>> result = ProcessBytes( in);
//        if(result)
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

    /// @traceid{SWS_CRYPT_23618}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02302}
    /// @brief Processe the final part of message (that may be not aligned to the block-size boundary).
    ///       If <tt>(IsBytewiseMode() == false)</tt> then it @b must be:
    ///       <tt>bs = GetBlockSize(), </tt>
    ///       <tt>out.size() >= (((in.size() + bs * ((CryptoTransform::kEncrypt == GetTransformation().Value()) ? 2 : 1) - 1) / bs) * bs)</tt>
    ///       If <tt>(IsBytewiseMode() == true)</tt>  then it @b must be:  <tt>out.size() >= in.size()</tt>
    ///       The input and output buffers must not intersect!
    ///       Usage of this method is mandatory for processing of the last data chunk in block-wise modes!
    ///       This method may be used for processing of a whole message in a single call (in any mode)!
    /// @param[in] in  an input data buffer
    /// @returns an output data buffer
    /// @error CryptoErrorDomain::kInsufficientCapacity  if capacity of the output buffer is not enough
    /// @error CryptoErrorDomain::kInOutBuffersIntersect  if the input and output buffers intersect
    /// @error CryptoErrorDomain::kProcessingNotStarted  if data processing was not started by a call of
    ///                the @c Start() method
    ///
    /// @threadsafety{Thread-safe}
    
    virtual ara::core::Result<ara::core::Vector<ara::core::Byte>> FinishBytes(ReadOnlyMemRegion in
    ) noexcept = 0;

    /// @traceid{SWS_CRYPT_23619}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02302}
    /// @brief Processe the final part of message (that may be not aligned to the block-size boundary).
    ///       This method sets the size of the output container according to actually saved value.
    ///       If <tt>(IsBytewiseMode() == false)</tt> then it @b must be:
    ///       <tt>bs = GetBlockSize(), </tt>
    ///       <tt>out.capacity() >= (((in.size() + bs * ((CryptoTransform::kEncrypt == GetTransformation.Value()) ? 2 : 1) - 1) / bs) * bs)</tt>
    ///       If <tt>(IsBytewiseMode() == true)</tt>  then it @b must be:  <tt>out.capacity() >= in.size()</tt>
    ///       Usage of this method is mandatory for processing of the last data chunk in block-wise modes!
    ///       This method may be used for processing of a whole message in a single call (in any mode)!
    /// @tparam Alloc  a custom allocator type of the output container
    /// @returns a managed container for output data
    /// @param[in] in  an input data buffer
    ///       The input buffer @b must @b not point inside the output container!
    /// @error CryptoErrorDomain::kInsufficientCapacity  if capacity of the output container is not enough
    /// @error CryptoErrorDomain::kInOutBuffersIntersect  if the input and output buffers intersect
    /// @error CryptoErrorDomain::kProcessingNotStarted  if data processing was not started by a call of
    ///                the @c Start() method
    ///
    /// @threadsafety{Thread-safe}
    
//    template <typename Alloc = VENDOR_IMPLEMENTATION_DEFINED>
//    ara::core::Result<ByteVector<Alloc>> FinishBytes(ReadOnlyMemRegion in
//    ) noexcept
//    {
//        ara::core::Result<ara::core::Vector<ara::core::Byte>> result = FinishBytes(in);
//        if(result)
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

    /// @traceid{SWS_CRYPT_23620}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02302}
    /// @brief Count number of bytes now kept in the context cache.
    ///       In block-wise modes if an application has supplied input data chunks with incomplete last block
    ///       then the context saves the rest part of the last (incomplete) block to internal "cache" memory
    ///       and wait a next call for additional input to complete this block.
    /// @returns number of bytes now kept in the context cache
    ///
    /// @threadsafety{Thread-safe}
    
    virtual std::size_t CountBytesInCache() const noexcept = 0;

    /// @traceid{SWS_CRYPT_23621}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02302}
    /// @brief Estimate maximal number of input bytes that may be processed for filling of an output buffer
    ///           without overflow.
    /// @param[in] outputCapacity  capacity of the output buffer
    /// @returns maximum number of input bytes
    ///
    /// @threadsafety{Thread-safe}
    
    std::size_t EstimateMaxInputSize(std::size_t outputCapacity) const noexcept
    {
        const std::size_t kGranularity = IsBytewiseMode() ? 1 : GetBlockService()->GetBlockSize();
        const std::size_t kUsableCapacity = outputCapacity / kGranularity * kGranularity;
        return !kUsableCapacity ? 0 : kUsableCapacity - CountBytesInCache();
    }

    /// @traceid{SWS_CRYPT_23622}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02302}
    /// @brief Estimate minimal required capacity of the output buffer, which is enough for saving a result of
    ///           input data processing.
    /// @param[in] inputSize  size of input data
    /// @param[in] isFinal  flag that indicates processing of the last data chunk (if @c true)
    /// @returns required capacity of the output buffer (in bytes)
    ///
    /// @threadsafety{Thread-safe}
    
    std::size_t EstimateRequiredCapacity(std::size_t inputSize, bool isFinal = false) const noexcept
    {
        const std::size_t kGranularity = IsBytewiseMode() ? 1 : GetBlockService()->GetBlockSize();
        std::size_t maxPaddingSize = isFinal && !IsBytewiseMode() && GetTransformation() ? kGranularity : 0;
        return (inputSize + CountBytesInCache() + maxPaddingSize) / kGranularity * kGranularity;
    }

    /// @traceid{SWS_CRYPT_23623}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02001}
    /// @uptrace{RS_CRYPTO_02003}
    /// @brief Set (deploy) a key to the stream chiper algorithm context.
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
        , CryptoTransform transform = CryptoTransform::kEncrypt
    ) noexcept = 0;

    /// @traceid{SWS_CRYPT_23624}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02309}
    /// @brief Get the kind of transformation configured for this context: kEncrypt or kDecrypt
    /// @returns @c CryptoTransform
    /// @error CryptoErrorDomain::kUninitializedContext  if the transformation direction of this context
    ///                is configurable during an initialization, but the context was not initialized yet
    /// @threadsafety{Thread-safe}
    virtual ara::core::Result<CryptoTransform> GetTransformation() const noexcept = 0;

    /// @traceid{SWS_CRYPT_23625}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02302}
    /// @brief Initialize the context for a new data stream processing or generation (depending from the primitive).
    ///       If IV size is greater than maximally supported by the algorithm then an implementation may use the
    ///       leading bytes only from the sequence.
    /// @param[in] iv  an optional Initialization Vector (IV) or "nonce" value
    /// @error CryptoErrorDomain::kUninitializedContext  if the context was not initialized by deploying a key
    /// @error CryptoErrorDomain::kInvalidInputSize  if the size of provided IV is not supported
    ///                (i.e. if it is not enough for the initialization)
    /// @error CryptoErrorDomain::kUnsupported  if the base algorithm (or its current implementation)
    ///                principally doesn't support the IV variation, but provided IV value is not empty,
    ///                i.e. if <tt>(iv.empty() == false)</tt>
    ///
    /// @threadsafety{Thread-safe}
    
    virtual ara::core::Result<void> Start(ReadOnlyMemRegion iv = ReadOnlyMemRegion()) noexcept = 0;

    /// @traceid{SWS_CRYPT_23626}@tracestatus{draft}
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

    /// @traceid{SWS_CRYPT_23627}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02108}
    /// @brief Clear the crypto context.
    ///
    /// @threadsafety{Thread-safe}
    
    virtual ara::core::Result<void> Reset() noexcept = 0;

};

}  // namespace cryp
}  // namespace crypto
}  // namespace ara

#endif  // ARA_CRYPTO_CRYP_STREAM_CIPHER_CTX_H_
