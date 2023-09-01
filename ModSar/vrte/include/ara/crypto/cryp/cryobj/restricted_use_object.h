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
/// @brief Adaptive Autosar Crypto Stack. Cryptographic API. Restricted Use Object interface
/// definition.

#ifndef ARA_CRYPTO_CRYP_RESTRICTED_USE_OBJECT_H_
#define ARA_CRYPTO_CRYP_RESTRICTED_USE_OBJECT_H_

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "ara/crypto/common/base_id_types.h"

#include "ara/crypto/cryp/cryobj/crypto_object.h"

namespace ara
{
namespace crypto
{
namespace cryp
{
//- @interface RestrictedUseObject
///
/// @traceid{SWS_CRYPT_24800}@tracestatus{draft}
/// @uptrace{RS_CRYPTO_02008}
/// @brief A common interface for all objects supporting the usage restriction.
class RestrictedUseObject : public CryptoObject
{
public:
    /// @traceid{SWS_CRYPT_24802}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02403}
    /// @brief Unique smart pointer of the interface.
    using Uptrc = std::unique_ptr<RestrictedUseObject>;

    /// @traceid{SWS_CRYPT_24801}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02008}
    /// @brief Alias to the container type for bit-flags of allowed usages of the object.
    using Usage = AllowedUsageFlags;

    /// @traceid{SWS_CRYPT_24811}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02008}
    /// @brief Get allowed usages of this object.
    /// @returns a combination of bit-flags that specifies allowed applications of the object
    /// @threadsafety{Thread-safe}
    virtual Usage GetAllowedUsage() const noexcept = 0;
};

} // namespace cryp
} // namespace crypto
} // namespace ara

#endif // ARA_CRYPTO_CRYP_RESTRICTED_USE_OBJECT_H_
