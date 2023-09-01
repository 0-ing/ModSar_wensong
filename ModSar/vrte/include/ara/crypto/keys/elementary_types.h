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
/// @brief Adaptive Autosar Crypto Stack. Key Storage API. Elementary types definition.

#ifndef ARA_CRYPTO_KEYS_ELEMENTARY_TYPES_H_
#define ARA_CRYPTO_KEYS_ELEMENTARY_TYPES_H_

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "ara/core/vector.h"
#include "ara/crypto/keys/keyslot.h"

namespace ara
{
namespace crypto
{
namespace keys
{
/// @traceid{SWS_CRYPT_30010}@tracestatus{draft}
/// @uptrace{RS_CRYPTO_02004}
/// @brief Definition of a transaction identifier type.
///     The zero value should be reserved for especial cases.
///
using TransactionId = std::uint64_t;

/// @traceid{SWS_CRYPT_30011}@tracestatus{draft}
/// @uptrace{RS_CRYPTO_02004}
/// @brief Definition of a "transaction scope" type.
///      The "transaction scope" defines a list of key slots that are target for update in a
///      transaction.
///
using TransactionScope = ara::core::Vector<KeySlot>;

} // namespace keys
} // namespace crypto
} // namespace ara

#endif // ARA_CRYPTO_KEYS_ELEMENTARY_TYPES_H_
