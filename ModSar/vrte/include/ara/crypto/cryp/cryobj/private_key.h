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
/// @brief Adaptive Autosar Crypto Stack. Cryptographic API. PrivateKey interface definition.

#ifndef ARA_CRYPTO_CRYP_PRIVATE_KEY_H_
#define ARA_CRYPTO_CRYP_PRIVATE_KEY_H_

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "ara/crypto/common/base_id_types.h"

#include "ara/crypto/cryp/cryobj/public_key.h"
#include "ara/crypto/cryp/cryobj/restricted_use_object.h"

#include "ara/core/result.h"

namespace ara
{
namespace crypto
{
namespace cryp
{
//- @interface PrivateKey
///
/// @traceid{SWS_CRYPT_22500}@tracestatus{draft}
/// @uptrace{RS_CRYPTO_02002}
/// @uptrace{RS_CRYPTO_02403}
/// @brief Generalized Asymmetric Private %Key interface.
///

class PrivateKey : public RestrictedUseObject
{
public:
    /// @traceid{SWS_CRYPT_22501}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02306}
    /// @brief Unique smart pointer of the interface.

    using Uptrc = std::unique_ptr<const PrivateKey>;

    /// @traceid{SWS_CRYPT_22503}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02306}
    /// @brief Static mapping of this interface to specific value of @c CryptoObjectType
    /// enumeration.

    static const CryptoObjectType kObjectType = CryptoObjectType::kPrivateKey;

    /// @traceid{SWS_CRYPT_22511}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02108}
    /// @uptrace{RS_CRYPTO_02115}
    /// @brief Get the public key correspondent to this private key.
    ///  Pre Conditions:
    ///  The Key pair (both public and private key) should be already laoded and available in the RAM.
    ///       (Public key for a particular Private key available in persistent key store but not loaded to RAM will not be fetched)
    ///  ara::crypto::cryp::CryptoProvider::GeneratePrivateKey() should generate both public and private key values with a common COUID.
    ///
    /// @returns unique smart pointer to the public key correspondent to this private key
    /// @threadsafety{Thread-safe}

    virtual ara::core::Result<PublicKey::Uptrc> GetPublicKey() const noexcept = 0;
};

} // namespace cryp
} // namespace crypto
} // namespace ara

#endif // ARA_CRYPTO_CRYP_PRIVATE_KEY_H_
