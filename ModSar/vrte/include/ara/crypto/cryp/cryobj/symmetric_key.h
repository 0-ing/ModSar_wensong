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
/// @brief Adaptive Autosar Crypto Stack. Cryptographic API. SymmetricKey interface definition.

#ifndef ARA_CRYPTO_CRYP_SYMMETRIC_KEY_H_
#define ARA_CRYPTO_CRYP_SYMMETRIC_KEY_H_

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "ara/crypto/common/base_id_types.h"

#include "ara/crypto/cryp/cryobj/restricted_use_object.h"

namespace ara
{
namespace crypto
{
namespace cryp
{
//- @interface SymmetricKey
///
/// @traceid{SWS_CRYPT_23800}@tracestatus{draft}
/// @uptrace{RS_CRYPTO_02001}
/// @uptrace{RS_CRYPTO_02403}
/// @brief Symmetric Key interface.
///

class SymmetricKey : public RestrictedUseObject
{
public:
    /// @traceid{SWS_CRYPT_23801}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02201}
    /// @brief Unique smart pointer of the interface.

    using Uptrc = std::unique_ptr<const SymmetricKey>;

    /// @traceid{SWS_CRYPT_23802}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02201}
    /// @brief const object type

    static const CryptoObjectType kObjectType = CryptoObjectType::kSymmetricKey;
};

} // namespace cryp
} // namespace crypto
} // namespace ara

#endif // ARA_CRYPTO_CRYP_SYMMETRIC_KEY_H_
