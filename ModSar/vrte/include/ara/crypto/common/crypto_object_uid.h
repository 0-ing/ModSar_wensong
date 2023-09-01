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
/// @brief Adaptive Autosar Crypto Stack. Common API. Crypto Object Unique Identifier type
/// definition.

#ifndef ARA_CRYPTO_COMMON_CRYPTO_OBJECT_UID_H_
#define ARA_CRYPTO_COMMON_CRYPTO_OBJECT_UID_H_

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "ara/crypto/common/uuid.h"
#include <cstdint>

namespace ara
{
namespace crypto
{
/// @traceid{SWS_CRYPT_10100}@tracestatus{draft}
/// @uptrace{RS_CRYPTO_02005}
/// @uptrace{RS_CRYPTO_02006}
/// @brief Definition of Crypto Object Unique Identifier (@b COUID) type.
///

struct CryptoObjectUid
{
    /// @traceid{SWS_CRYPT_10101}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02006}
    /// @brief UUID of a generator that has produced this COUID. This UUID can be associated with
    /// HSM,
    ///           physical host/ECU or VM.
    Uuid mGeneratorUid;

    /// @traceid{SWS_CRYPT_10102}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02006}
    /// @brief Sequential value of a steady timer or simple counter, representing version of
    /// correspondent
    ///           Crypto Object.
    std::uint64_t mVersionStamp = 0u;

    /// @traceid{SWS_CRYPT_10111}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02006}
    /// @brief Check whether this identifier has a common source with the one provided by the
    /// argument.
    /// @param[in] anotherId  another identifier for the comparison
    /// @returns @c true if both identifiers has common source (identical value of the @c
    /// mGeneratorUid field)
    /// @threadsafety{Reentrant}
    constexpr bool HasSameSourceAs(const CryptoObjectUid& anotherId) const noexcept;

    /// @traceid{SWS_CRYPT_10112}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02006}
    /// @brief Check whether this identifier was generated earlier than the one provided by the
    /// argument.
    /// @param[in] anotherId  another identifier for the comparison
    /// @returns @c true if this identifier was generated earlier than the @c anotherId
    /// @threadsafety{Reentrant}
    constexpr bool HasEarlierVersionThan(const CryptoObjectUid& anotherId) const noexcept;

    /// @traceid{SWS_CRYPT_10113}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02006}
    /// @brief Check whether this identifier was generated later than the one provided by the
    /// argument.
    /// @param[in] anotherId  another identifier for the comparison
    /// @returns @c true if this identifier was generated later than the @c anotherId
    /// @threadsafety{Reentrant}

    constexpr bool HasLaterVersionThan(const CryptoObjectUid& anotherId) const noexcept;

    /// @traceid{SWS_CRYPT_10114}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02006}
    /// @brief Check whether this identifier is "Nil".
    /// @returns @c true if this identifier is "Nil" and @c false otherwise
    /// @threadsafety{Reentrant}

    bool IsNil() const noexcept;

    /// @traceid{SWS_CRYPT_10115}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02006}
    /// @brief Check whether this object's generator identifier is "Nil".
    /// @returns @c true if this identifier is "Nil" and @c false otherwise
    /// @threadsafety{Reentrant}

    bool SourceIsNil() const noexcept;
};

inline constexpr bool
CryptoObjectUid::HasSameSourceAs(const CryptoObjectUid& anotherId) const noexcept
{
    return mGeneratorUid == anotherId.mGeneratorUid;
}

inline constexpr bool
CryptoObjectUid::HasEarlierVersionThan(const CryptoObjectUid& anotherId) const noexcept
{
    return HasSameSourceAs(anotherId) && (mVersionStamp < anotherId.mVersionStamp);
}

inline constexpr bool
CryptoObjectUid::HasLaterVersionThan(const CryptoObjectUid& anotherId) const noexcept
{
    return HasSameSourceAs(anotherId) && (mVersionStamp > anotherId.mVersionStamp);
}

inline bool CryptoObjectUid::IsNil() const noexcept
{
    return mGeneratorUid.IsNil() && (0u == mVersionStamp);
}

inline bool CryptoObjectUid::SourceIsNil() const noexcept
{
    return mGeneratorUid.IsNil();
}

/// @traceid{SWS_CRYPT_10150}@tracestatus{draft}
/// @uptrace{RS_CRYPTO_02005}
/// @brief Comparison operator "equal" for @c CryptoObjectUid operands.
/// @param[in] lhs  left-hand side operand
/// @param[in] rhs  right-hand side operand
/// @returns @c true if all members' values of @c lhs is equal to @c rhs, and @c false otherwise
/// @threadsafety{Thread-safe}
inline constexpr bool operator==(const CryptoObjectUid& lhs, const CryptoObjectUid& rhs) noexcept
{
    return lhs.HasSameSourceAs(rhs) && (lhs.mVersionStamp == rhs.mVersionStamp);
}

/// @traceid{SWS_CRYPT_10151}@tracestatus{draft}
/// @uptrace{RS_CRYPTO_02005}
/// @brief Comparison operator "less than" for @c CryptoObjectUid operands.
/// @param[in] lhs  left-hand side operand
/// @param[in] rhs  right-hand side operand
/// @returns @c true if a binary representation of @c lhs is less than @c rhs, and @c false
/// otherwise
/// @threadsafety{Thread-safe}

inline constexpr bool operator<(const CryptoObjectUid& lhs, const CryptoObjectUid& rhs) noexcept
{
    return lhs.HasEarlierVersionThan(rhs);
}

/// @traceid{SWS_CRYPT_10152}@tracestatus{draft}
/// @uptrace{RS_CRYPTO_02005}
/// @brief Comparison operator "greater than" for @c CryptoObjectUid operands.
/// @param[in] lhs  left-hand side operand
/// @param[in] rhs  right-hand side operand
/// @returns @c true if a binary representation of @c lhs is greater than @c rhs, and @c false
/// otherwise
/// @threadsafety{Thread-safe}

inline constexpr bool operator>(const CryptoObjectUid& lhs, const CryptoObjectUid& rhs) noexcept
{
    return lhs.HasLaterVersionThan(rhs);
}

/// @traceid{SWS_CRYPT_10153}@tracestatus{draft}
/// @uptrace{RS_CRYPTO_02005}
/// @brief Comparison operator "not equal" for @c CryptoObjectUid operands.
/// @param[in] lhs  left-hand side operand
/// @param[in] rhs  right-hand side operand
/// @returns @c true if at least one member of @c lhs has a value not equal to correspondent member
/// of @c rhs,
///          and @c false otherwise
/// @threadsafety{Thread-safe}

inline constexpr bool operator!=(const CryptoObjectUid& lhs, const CryptoObjectUid& rhs) noexcept
{
    return !(lhs == rhs);
}

/// @traceid{SWS_CRYPT_10154}@tracestatus{draft}
/// @uptrace{RS_CRYPTO_02005}
/// @brief Comparison operator "less than or equal" for @c CryptoObjectUid operands.
/// @param[in] lhs  left-hand side operand
/// @param[in] rhs  right-hand side operand
/// @returns @c true if a binary representation of @c lhs is less than or equal to @c rhs, and @c
/// false otherwise
/// @threadsafety{Thread-safe}

inline constexpr bool operator<=(const CryptoObjectUid& lhs, const CryptoObjectUid& rhs) noexcept
{
    return lhs.HasSameSourceAs(rhs) && (lhs.mVersionStamp <= rhs.mVersionStamp);
}

/// @traceid{SWS_CRYPT_10155}@tracestatus{draft}
/// @uptrace{RS_CRYPTO_02005}
/// @brief Comparison operator "greater than or equal" for @c CryptoObjectUid operands.
/// @param[in] lhs  left-hand side operand
/// @param[in] rhs  right-hand side operand
/// @returns @c true if a binary representation of @c lhs is greater than or equal to @c rhs, and @c
/// false otherwise
/// @threadsafety{Thread-safe}

inline constexpr bool operator>=(const CryptoObjectUid& lhs, const CryptoObjectUid& rhs) noexcept
{
    return lhs.HasSameSourceAs(rhs) && (lhs.mVersionStamp >= rhs.mVersionStamp);
}

} // namespace crypto
} // namespace ara

#endif // ARA_CRYPTO_COMMON_CRYPTO_OBJECT_UID_H_
