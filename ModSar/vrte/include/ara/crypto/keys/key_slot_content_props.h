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
/// @brief Adaptive Autosar Crypto Stack. Key Storage API. Key Slot Content Properties structure
/// definition.

#ifndef ARA_CRYPTO_KEYS_KEY_SLOT_CONTENT_PROPS_H_
#define ARA_CRYPTO_KEYS_KEY_SLOT_CONTENT_PROPS_H_

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "ara/crypto/common/base_id_types.h"
#include "ara/crypto/common/crypto_object_uid.h"

namespace ara
{
namespace crypto
{
namespace keys
{
/// @traceid{SWS_CRYPT_30500}@tracestatus{draft}
/// @uptrace{RS_CRYPTO_02005}
/// @uptrace{RS_CRYPTO_02111}
///
/// @brief Properties of current Key Slot Content, i.e. of a current instance stored to the Key
/// Slot. A value of the @c mAllowedUsage field is bitwise AND of the common usage flags defined at
/// run-time and
///       the usage flags defined by the @c UserPermissions prototype for current "Actor".
///
struct KeySlotContentProps
{
    /// @traceid{SWS_CRYPT_30510}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02111}
    /// @brief set content properties
    KeySlotContentProps() = default;

    /// @traceid{SWS_CRYPT_30511}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02111}
    /// @brief shared pointer of interface
    using Uptr = std::unique_ptr<KeySlotContentProps>;

    /// @traceid{SWS_CRYPT_30501}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02111}
    /// @brief UID of a Crypto Object stored to the slot.
    ///
    CryptoObjectUid mObjectUid;

    /// @traceid{SWS_CRYPT_30503}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02111}
    /// @brief Cryptoalgorithm of actual object stored to the slot.
    ///
    CryptoAlgId mAlgId;

    /// @traceid{SWS_CRYPT_30505}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02111}
    /// @brief Actual size of an object currently stored to the slot.
    ///
    std::size_t mObjectSize;

    /// @traceid{SWS_CRYPT_30506}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02111}
    /// @brief Actual usage restriction flags of an object stored to the slot for the current
    /// "Actor".
    ///
    AllowedUsageFlags mContentAllowedUsage;

    /// @traceid{SWS_CRYPT_30508}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02111}
    /// @brief Actual type of an object stored to the slot.
    ///
    CryptoObjectType mObjectType;
};

/// @traceid{SWS_CRYPT_30550}@tracestatus{draft}
/// @uptrace{RS_CRYPTO_02111}
///
/// @brief Comparison operator "equal" for @c KeySlotContentProps operands.
/// @param[in] lhs  left-hand side operand
/// @param[in] rhs  right-hand side operand
/// @returns @c true if all members' values of @c lhs is equal to @c rhs, and @c false otherwise
/// @threadsafety{Thread-safe}
///
inline constexpr bool operator==(const KeySlotContentProps& lhs,
                                 const KeySlotContentProps& rhs) noexcept
{
    return (lhs.mObjectUid == rhs.mObjectUid) &&
           (lhs.mContentAllowedUsage == rhs.mContentAllowedUsage) && (lhs.mAlgId == rhs.mAlgId) &&
           (lhs.mObjectSize == rhs.mObjectSize) && (lhs.mObjectType == rhs.mObjectType);
}

/// @traceid{SWS_CRYPT_30551}@tracestatus{draft}
/// @uptrace{RS_CRYPTO_02111}
///
/// @brief Comparison operator "not equal" for @c KeySlotContentProps operands.
/// @param[in] lhs  left-hand side operand
/// @param[in] rhs  right-hand side operand
/// @returns @c true if at least one member of @c lhs has a value not equal to correspondent member
/// of @c rhs,
///          and @c false otherwise
/// @threadsafety{Thread-safe}
///
inline constexpr bool operator!=(const KeySlotContentProps& lhs,
                                 const KeySlotContentProps& rhs) noexcept
{
    return !(lhs == rhs);
}

} // namespace keys
} // namespace crypto
} // namespace ara

#endif // ARA_CRYPTO_KEYS_KEY_SLOT_CONTENT_PROPS_H_
