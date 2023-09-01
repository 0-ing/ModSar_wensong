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
/// @brief Adaptive Autosar Crypto Stack. Cryptographic API. BlockService interface definition.

#ifndef ARA_CRYPTO_CRYP_BLOCK_SERVICE_H_
#define ARA_CRYPTO_CRYP_BLOCK_SERVICE_H_

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "ara/crypto/cryp/extension_service.h"
#include "ara/core/optional.h"

namespace ara
{
namespace crypto
{
namespace cryp
{
	
//- @interface BlockService
///
/// @traceid{SWS_CRYPT_29030}@tracestatus{draft}
/// @uptrace{RS_CRYPTO_02309}
/// @brief Extension meta-information service for block cipher contexts.
///
 
class BlockService: public ExtensionService
{
public:

    /// @traceid{SWS_CRYPT_29031}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02309}
    /// @brief Unique smart pointer of the interface.
     
    using Uptr = std::unique_ptr<BlockService>;

    /// @traceid{SWS_CRYPT_29032}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02309}
    /// @brief Get default expected size of the Initialization Vector (IV) or nonce.
    /// @returns default expected size of IV in bytes
    ///
    /// @threadsafety{Thread-safe}
     
    virtual std::size_t GetIvSize() const noexcept = 0;

    /// @traceid{SWS_CRYPT_29033}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02309}
    /// @brief Get block (or internal buffer) size of the base algorithm.
    /// @returns size of the block in bytes
    ///
    /// @threadsafety{Thread-safe}
     
    virtual std::size_t GetBlockSize() const noexcept = 0;

    /// @traceid{SWS_CRYPT_29034}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02309}
    /// @brief Verify validity of specific Initialization Vector (IV) length.
    /// @param[in] ivSize  the length of the IV in bytes
    /// @returns @c true if provided IV length is supported by the algorithm and @c false otherwise
    ///
    /// @threadsafety{Thread-safe}
     
    virtual bool IsValidIvSize(std::size_t ivSize) const noexcept = 0;

    /// @traceid{SWS_CRYPT_29035}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02309}
    /// @brief Get actual bit-length of an IV loaded to the context.
    /// @param[in] ivUid  optional pointer to a buffer for saving an @a COUID of a IV object now loaded to the context.
	/// If the context was initialized by a @c SecretSeed object then the output buffer @c *ivUid must be filled
    ///       by @a COUID of this loaded IV object, in other cases @c *ivUid must be filled by all zeros.
    /// @returns actual length of the IV (now set to the algorithm context) in bits
    ///
    /// @threadsafety{Thread-safe}
     
    virtual std::size_t GetActualIvBitLength(ara::core::Optional<CryptoObjectUid> ivUid) const noexcept = 0;

};


}  // namespace cryp
}  // namespace crypto
}  // namespace ara

#endif /* ARA_CRYPTO_CRYP_BLOCK_SERVICE_H_ */
