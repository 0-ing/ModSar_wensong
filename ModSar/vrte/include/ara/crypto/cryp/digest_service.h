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
/// @brief Adaptive Autosar Crypto Stack. Cryptographic API. DigestService interface definition.

#ifndef ARA_CRYPTO_CRYP_DIGEST_SERVICE_H_
#define ARA_CRYPTO_CRYP_DIGEST_SERVICE_H_

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "ara/crypto/common/mem_region.h"
#include "ara/crypto/cryp/block_service.h"
#include "ara/core/result.h"

namespace ara
{
namespace crypto
{
namespace cryp
{
	
//- @interface DigestService
///
/// @traceid{SWS_CRYPT_29010}@tracestatus{draft}
/// @uptrace{RS_CRYPTO_02309}
/// @brief Extension meta-information service for digest producing contexts.
///
 
class DigestService: public BlockService
{
public:

    /// @traceid{SWS_CRYPT_29011}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02309}
    /// @brief Unique smart pointer of the interface.
     
    using Uptr = std::unique_ptr<DigestService>;

    /// @traceid{SWS_CRYPT_29012}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02309}
    /// @brief Get the output digest size.
    /// @returns size of the full output from this digest-function in bytes
    ///
    /// @threadsafety{Thread-safe}
     
    virtual std::size_t GetDigestSize() const noexcept = 0;

    /// @traceid{SWS_CRYPT_29013}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02309}
    /// @brief Compare the calculated digest against an expected value.
	///       Entire digest value is kept in the context up to next call @c Start(), therefore any its part can be
    ///       verified again or extracted.
    ///       If <tt>(full_digest_size <= offset) || (expected.size() == 0)</tt> then return @c false;
    ///       else <tt>comparison_size = min(expected.size(), (full_digest_size - offset))</tt> bytes.
    ///       This method can be implemented as "inline" after standartization of function @c ara::core::memcmp().
    /// @param[in] expected  the memory region containing an expected digest value
    /// @param[in] offset  position of the first byte in calculated digest for the comparison starting
    /// @returns @c true if the expected bytes sequence is identical to first bytes of calculated digest
    /// @error CryptoErrorDomain::kProcessingNotFinished  if the digest calculation was not finished
    ///                by a call of the @c Finish() method
    /// @error CryptoErrorDomain::kBruteForceRisk  if the buffered digest belongs to a MAC/HMAC/AE/AEAD
    ///                context, which was initialized by a key without @c kAllowSignature permission, but actual
    ///                size of requested digest is less than 8 bytes (it is a protection from the brute-force attack)
    /// @threadsafety{Thread-safe}
     
    virtual ara::core::Result<bool> Compare(ReadOnlyMemRegion expected
        , std::size_t offset = 0
    ) const noexcept  = 0;

	
	/// @traceid{SWS_CRYPT_29014}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02309}
    /// @brief Check current status of the stream processing: started or no.
    /// @returns @c true if the processing was start by a call of the @c Start() methods and was not finished yet
    /// @threadsafety{Thread-safe}
     
    virtual bool IsStarted() const noexcept = 0;

	
    /// @traceid{SWS_CRYPT_29015}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02309}
    /// @brief Check current status of the stream processing: finished or no.
    /// @returns @c true if a previously started stream processing was finished by a call of the @c Finish()
    ///          or @c FinishBytes() methods
    /// @threadsafety{Thread-safe}
     
    virtual bool IsFinished() const noexcept = 0;
	
};



}  // namespace cryp
}  // namespace crypto
}  // namespace ara

#endif /* ARA_CRYPTO_CRYP_DIGEST_SERVICE_H_ */
