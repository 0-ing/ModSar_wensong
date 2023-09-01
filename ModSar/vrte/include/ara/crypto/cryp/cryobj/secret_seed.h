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
/// @brief Adaptive Autosar Crypto Stack. Cryptographic API. SecretSeed interface definition.

#ifndef ARA_CRYPTO_CRYP_SECRET_SEED_H_
#define ARA_CRYPTO_CRYP_SECRET_SEED_H_

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "ara/crypto/common/base_id_types.h"
#include "ara/crypto/common/mem_region.h"

#include "ara/crypto/cryp/cryobj/crypto_object.h"
#include "ara/crypto/cryp/cryobj/restricted_use_object.h"

#include "ara/core/result.h"

namespace ara
{
namespace crypto
{
namespace cryp
{
//- @interface SecretSeed
///
/// @traceid{SWS_CRYPT_23000}@tracestatus{draft}
/// @uptrace{RS_CRYPTO_02007}
/// @brief Secret Seed object interface.
///       This object contains a raw bit sequence of specific length (without any filtering of
///       allowed/disallowed values)! The secret seed value can be loaded only to a non-key input of
///       a cryptographic transformation context (like IV/salt/nonce)! Bit length of the secret seed
///       is specific to concret crypto algorithm and corresponds to maximum of its
///       input/output/salt block-length.
///

class SecretSeed : public RestrictedUseObject
{
public:
    /// @traceid{SWS_CRYPT_23003}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02007}
    /// @brief Static mapping of this interface to specific value of @c CryptoObjectType
    /// enumeration.

    static const CryptoObjectType kObjectType = CryptoObjectType::kSecretSeed;

    /// @traceid{SWS_CRYPT_23001}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02007}
    /// @brief Unique smart pointer of a constant interface instance.

    using Uptrc = std::unique_ptr<const SecretSeed>;

    /// @traceid{SWS_CRYPT_23002}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02007}
    /// @brief Unique smart pointer of a volatile interface instance.

    using Uptr = std::unique_ptr<SecretSeed>;

    /// @traceid{SWS_CRYPT_23011}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02007}
    /// @brief Clone this Secret Seed object to new session object.
    ///       Created object instance is session and non-exportable, @c AllowedUsageFlags attribute
    ///       of the "cloned" object is identical to this attribute of the source object! If size of
    ///       the @c xorDelta argument is less than the value size of this seed then only
    ///       correspondent number of leading bytes of the original seed should be XOR-ed, but the
    ///       rest should be copied without change. If size of the @c xorDelta argument is larger
    ///       than the value size of this seed then extra bytes of the @c xorDelta should be
    ///       ignored.
    /// @param[in] xorDelta  optional "delta" value that must be XOR-ed with the "cloned" copy of
    /// the original seed
    /// @returns unique smart pointer to "cloned" session @c SecretSeed object

    /// @threadsafety{Thread-safe}

    virtual ara::core::Result<SecretSeed::Uptr>
    Clone(ReadOnlyMemRegion xorDelta = ReadOnlyMemRegion()) const noexcept = 0;

    /// @traceid{SWS_CRYPT_23012}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02007}
    /// @brief Set value of this seed object as a "jump" from an initial state to specified number
    /// of steps,
    ///           according to "counting" expression defined by a cryptographic algorithm associated
    ///           with this object.
    ///       @c steps may have positive and negative values that correspond to forward and backward
    ///       direction of the "jump" respectively, but 0 value means only copy @c from value to
    ///       this seed object. Seed size of the @c from argument always must be greater or equal of
    ///       this seed size.
    /// @param[in] from  source object that keeps the initial value for jumping from
    /// @param[in] steps  number of steps for the "jump"
    /// @returns reference to this updated object

    /// @error SecurityErrorDomain::kIncompatibleObject  if this object and the @c from argument are
    /// associated
    ///                with incompatible cryptographic algorithms
    /// @error SecurityErrorDomain::kInvalidInputSize  if value size of the @c from seed is less
    /// then
    ///                value size of this one
    /// @threadsafety{Thread-safe}

    virtual ara::core::Result<void> JumpFrom(const SecretSeed& from,
                                             std::int64_t steps) noexcept = 0;

    /// @traceid{SWS_CRYPT_23013}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02007}
    /// @brief Set next value of the secret seed according to "counting" expression defined by a
    /// cryptographic
    ///           algorithm associated with this object.
    ///       If the associated cryptographic algorithm doesn't specify a "counting" expression then
    ///       generic increment operation must be implemented as default (little-endian notation,
    ///       i.e. first byte is least significant).
    /// @threadsafety{Thread-safe}

    virtual SecretSeed& Next() noexcept = 0;

    /// @traceid{SWS_CRYPT_23014}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02007}
    /// @brief Set value of this seed object as a "jump" from it's current state to specified number
    /// of steps,
    ///           according to "counting" expression defined by a cryptographic algorithm associated
    ///           with this object.
    ///       @c steps may have positive and negative values that correspond to forward and backward
    ///       direction of the "jump" respectively, but 0 value means no changes of the current seed
    ///       value.
    /// @param[in] steps  number of "steps" for jumping (forward or backward) from the current state
    /// @returns reference to this updated object

    /// @threadsafety{Thread-safe}

    virtual SecretSeed& Jump(std::int64_t steps) noexcept = 0;

    /// @traceid{SWS_CRYPT_23015}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02007}
    /// @brief XOR value of this seed object with another one and save result to this object.
    ///       If seed sizes in this object and in the @c source argument are different then only
    ///       correspondent number of leading bytes in this seed object should be updated.
    /// @param[in] source  right argument for the XOR operation
    /// @returns reference to this updated object
    /// @threadsafety{Thread-safe}

    virtual SecretSeed& operator^=(const SecretSeed& source) noexcept = 0;

    /// @traceid{SWS_CRYPT_23016}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02007}
    /// @brief XOR value of this seed object with provided memory region and save result to this
    /// object.
    ///       If seed sizes in this object and in the @c source argument are different then only
    ///       correspondent number of leading bytes of this seed object should be updated.
    /// @param[in] source  right argument for the XOR operation
    /// @returns reference to this updated object

    /// @threadsafety{Thread-safe}

    virtual SecretSeed& operator^=(ReadOnlyMemRegion source) noexcept = 0;
};

} // namespace cryp
} // namespace crypto
} // namespace ara

#endif // ARA_CRYPTO_CRYP_SECRET_SEED_H_
