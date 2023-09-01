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
/// @brief Adaptive Autosar Crypto Stack. Key Storage API. Key Slot Prototype Properties structure
/// definition.

#ifndef ARA_CRYPTO_KEYS_KEY_SLOT_PROTOTYPE_PROPS_H_
#define ARA_CRYPTO_KEYS_KEY_SLOT_PROTOTYPE_PROPS_H_

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
/// @traceid{SWS_CRYPT_30300}@tracestatus{draft}
/// @uptrace{RS_CRYPTO_02009}
/// @uptrace{RS_CRYPTO_02110}
/// @uptrace{RS_CRYPTO_02116}
///
/// @brief Prototyped Properties of a Key Slot.
///
struct KeySlotPrototypeProps
{
    /// @traceid{SWS_CRYPT_30301}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02110}
    KeySlotPrototypeProps() = default;

    /// @traceid{SWS_CRYPT_30302}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02110}
    using Uptr = std::unique_ptr<KeySlotPrototypeProps>;

    /// @traceid{SWS_CRYPT_30305}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02110}
    /// @brief Key-slot type configuration: all key-slots used by the adaptive machine to provide
    /// serives such as
    ///		   secure communication, diagnostics, updates, secure storage etc. shall use the type
    ///kMachine.
    ///        All key-slots that will be used by the adaptive user application must use
    ///        kApplication.
    ///		   A key-manager user application may define kMachine key-slots as well; in this case the
    ///integrator
    ///        must match a corresponding machine key-slot to be managed.
    ///
    KeySlotType mSlotType;

    /// @traceid{SWS_CRYPT_30306}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02110}
    /// @brief Cryptoalgorithm restriction (@c kAlgIdAny means without restriction).
    ///           The algorithm can be specified partially: family & length, mode, padding.
    ///
    CryptoAlgId mAlgId;

    /// @traceid{SWS_CRYPT_30307}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02110}
    /// @brief Capacity of the slot in bytes.
    ///
    std::size_t mSlotCapacity;

    /// @traceid{SWS_CRYPT_30308}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02110}
    /// @brief Restriction of an object type that can be stored the slot.
    ///           If this field contains @c CryptoObjectType::kUnknown then without restriction of
    ///           the type.
    ///
    CryptoObjectType mObjectType;

    /// @traceid{SWS_CRYPT_30309}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02110}
    /// @brief Indicates whether FC Crypto shall allocate sufficient storage space for a shadow copy
    /// of this KeySlot.
    ///
    bool mAllocateSpareSlot;

    /// @traceid{SWS_CRYPT_30310}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02110}
    /// @brief Indicates whether the content of this key-slot may be changed, e.g. from storing a
    /// symmetric key to storing an RSA key
    ///        If this is set to false, then the mObjectType of this KeySlotPrototypeProps must be
    ///        a) valid and b) cannot be changed ( i.e. only objects of mObjectType may be stored in
    ///        this key-slot).
    ///
    bool mAllowContentTypeChange;

    /// @traceid{SWS_CRYPT_30311}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02110}
    /// @brief Specifies how many times this key-slot may be updated, e.g.:
    ///        - a value of 0 means the key-slot content will be pre-set during production
    ///        - a value of 1 means the key-slot content can be updated only once ("OTP")
    ///        - a negative value means the key-slot content can be updated inifinitely
    ///
    std::int32_t mMaxUpdateAllowed;

    /// @traceid{SWS_CRYPT_30312}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02110}
    /// @brief Indicates whether the key-slot content may be exported.
    ///
    bool mExportAllowed;

    /// @traceid{SWS_CRYPT_30313}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02110}
    /// @brief Indicates how the content may be used. The following use cases of this attribute are
    /// considered:
    ///        - the object to be stored in this key-slot has it's AllowedUsageFlags set to
    ///        kAllowPrototypedOnly.
    ///          In this case this attribute must be observed when loading the content into a
    ///          runtime instance (e.g. the AllowedUsageFlags of a SymmetricKey object should be set
    ///          according to this attribute)
    ///        - mMaxUpdatesAllowed==0, in this case the content is provided during production while
    ///        the AllowedUsageFlags
    ///          is modeled using this attribute
    ///        - when this key-slot is flexibly updated the runtime object's AllowedUsageFlags
    ///        override this attribute
    ///          upon a later loading from this key-slot
    ///
    AllowedUsageFlags mContentAllowedUsage;
};

/// @traceid{SWS_CRYPT_30350}@tracestatus{draft}
/// @uptrace{RS_CRYPTO_02110}
///
/// @brief Comparison operator "equal" for @c KeySlotPrototypeProps operands.
/// @param[in] lhs  left-hand side operand
/// @param[in] rhs  right-hand side operand
/// @returns @c true if all members' values of @c lhs is equal to @c rhs, and @c false otherwise
/// @threadsafety{Thread-safe}
///
inline constexpr bool operator==(const KeySlotPrototypeProps& lhs,
                                 const KeySlotPrototypeProps& rhs) noexcept
{
    return (lhs.mContentAllowedUsage == rhs.mContentAllowedUsage) &&
           (lhs.mExportAllowed == rhs.mExportAllowed) &&
           (lhs.mMaxUpdateAllowed == rhs.mMaxUpdateAllowed) &&
           (lhs.mAllowContentTypeChange == rhs.mAllowContentTypeChange) &&
           (lhs.mAllocateSpareSlot == rhs.mAllocateSpareSlot) && (lhs.mAlgId == rhs.mAlgId) &&
           (lhs.mSlotCapacity == rhs.mSlotCapacity) && (lhs.mObjectType == rhs.mObjectType) &&
           (lhs.mSlotType == rhs.mSlotType);
}

/// @traceid{SWS_CRYPT_30351}@tracestatus{draft}
/// @uptrace{RS_CRYPTO_02110}
///
/// @brief Comparison operator "not equal" for @c KeySlotPrototypeProps operands.
/// @param[in] lhs  left-hand side operand
/// @param[in] rhs  right-hand side operand
/// @returns @c true if at least one member of @c lhs has a value not equal to correspondent member
/// of @c rhs,
///          and @c false otherwise
/// @threadsafety{Thread-safe}
///
inline constexpr bool operator!=(const KeySlotPrototypeProps& lhs,
                                 const KeySlotPrototypeProps& rhs) noexcept
{
    return !(lhs == rhs);
}

} // namespace keys
} // namespace crypto
} // namespace ara

#endif // ARA_CRYPTO_KEYS_KEY_SLOT_PROTOTYPE_PROPS_H_
