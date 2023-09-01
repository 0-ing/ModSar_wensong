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
/// @brief Adaptive Autosar Crypto Stack. Cryptographic API. Extension Service interface definition.

#ifndef ARA_CRYPTO_CRYP_EXTENSION_SERVICE_H_
#define ARA_CRYPTO_CRYP_EXTENSION_SERVICE_H_

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "ara/crypto/common/crypto_object_uid.h"
#include "ara/crypto/common/base_id_types.h"

namespace ara
{
namespace crypto
{
namespace cryp
{
//- @interface ExtensionService
///
/// @traceid{SWS_CRYPT_29040}@tracestatus{draft}
/// @uptrace{RS_CRYPTO_02309}
/// @brief Basic meta-information service for all contexts.
///
 
class ExtensionService
{
public:

    /// @traceid{SWS_CRYPT_29041}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02309}
    /// @brief Destructor
    virtual ~ExtensionService() noexcept = default;

    /// @traceid{SWS_CRYPT_30218}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02004}
    /// @brief Copy-assign another ExtensionService to this instance.
    /// @param other  the other instance
    /// @returns *this, containing the contents of @a other
    ExtensionService& operator=(const ExtensionService& other) = default;

    /// @traceid{SWS_CRYPT_30219}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02004}
    /// @brief Move-assign another ExtensionService to this instance.
    /// @param other  the other instance
    /// @returns *this, containing the contents of @a other
    ExtensionService& operator=(ExtensionService&& other) = default;

    ExtensionService(const ExtensionService& other) = default;
    ExtensionService(ExtensionService&& other) = default;
    ExtensionService() = default;

    /// @traceid{SWS_CRYPT_29042}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02309}
    /// @brief Unique smart pointer of the interface.
    using Uptr = std::unique_ptr<ExtensionService>;

    /// @traceid{SWS_CRYPT_29048}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02309}
    /// @brief Verify supportness of specific key length by the context.
    /// @param[in] keyBitLength  length of the key in bits
    /// @returns @c true if provided value of the key length is supported by the context
    ///
    /// @threadsafety{Thread-safe}
    virtual bool IsKeyBitLengthSupported(std::size_t keyBitLength) const noexcept = 0;

    /// @traceid{SWS_CRYPT_29043}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02309}
    /// @brief Get minimal supported key length in bits.
    /// @returns minimal supported length of the key in bits
    ///
    /// @threadsafety{Thread-safe}
     
    virtual std::size_t GetMinKeyBitLength() const noexcept = 0;

    /// @traceid{SWS_CRYPT_29044}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02309}
    /// @brief Get maximal supported key length in bits.
    /// @returns maximal supported length of the key in bits
    ///
    /// @threadsafety{Thread-safe}
     
    virtual std::size_t GetMaxKeyBitLength() const noexcept = 0;

    /// @traceid{SWS_CRYPT_29045}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02309}
    /// @brief Get actual bit-length of a key loaded to the context. If no key was set to the context yet then 0 is returned.
    /// @returns actual length of a key (now set to the algorithm context) in bits
    /// 
    /// @threadsafety{Thread-safe}
     
    virtual std::size_t GetActualKeyBitLength() const noexcept = 0;
	
    /// @traceid{SWS_CRYPT_29046}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02008}
    /// @brief Get allowed usages of this context (according to the key object attributes loaded to this context).
	/// If the context is not initialized by a key object yet then zero (all flags are reset) must be returned.
    /// @returns a combination of bit-flags that specifies allowed usages of the context
    /// @threadsafety{Thread-safe}
     
    virtual AllowedUsageFlags GetAllowedUsage() const noexcept = 0;

    /// @traceid{SWS_CRYPT_29047}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02309}
    /// @brief Get the COUID of the key deployed to the context this extension service is attached to. 
	/// If no key was set to the context yet then an empty COUID (Nil) is returned.
    /// @returns the COUID of the CryptoObject
    ///
    /// @threadsafety{Thread-safe}
     
    virtual CryptoObjectUid GetActualKeyCOUID() const noexcept = 0;
	
    /// @traceid{SWS_CRYPT_29049}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02309}
    /// @brief Check if a key has been set to this context.
    /// @returns FALSE if no key has been set
    ///
    /// @threadsafety{Thread-safe}
    virtual bool IsKeyAvailable() const noexcept = 0;

};

}  // namespace cryp
}  // namespace crypto
}  // namespace ara

#endif /* ARA_CRYPTO_CRYP_EXTENSION_SERVICE_H_ */
