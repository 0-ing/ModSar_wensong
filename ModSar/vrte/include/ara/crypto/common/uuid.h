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
/// @brief Adaptive Autosar Crypto Stack. Common API. UUID type definition.

#ifndef ARA_CRYPTO_COMMON_UUID_H_
#define ARA_CRYPTO_COMMON_UUID_H_

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include <cstdint>

namespace ara
{
namespace crypto
{
//- @struct Uuid
///
/// @traceid{SWS_CRYPT_10400}@tracestatus{draft}
/// @uptrace{RS_CRYPTO_02005}
/// @brief Definition of Universally Unique Identifier (@b UUID) type.
///    Independently from internal definition details of this structure, it's size @b must be 16
///    bytes and
///       entropy of this ID should be close to 128 bit!
struct Uuid
{
    /// @traceid{SWS_CRYPT_10413}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02005}
    /// Most significant QWORD.
    std::uint64_t mQwordMs = 0u;
    /// @traceid{SWS_CRYPT_10412}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02005}

    /// Less significant QWORD.
    std::uint64_t mQwordLs = 0u;

    /// @traceid{SWS_CRYPT_10411}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02005}
    /// @brief Check whether this identifier is the "Nil UUID" (according to RFC4122).
    /// @returns @c true if this identifier is "Nil" and @c false otherwise
    /// @threadsafety{Thread-safe}
    bool IsNil() const noexcept;
};

inline bool Uuid::IsNil() const noexcept
{
    return (0u == mQwordMs) && (0u == mQwordLs);
}

/// @traceid{SWS_CRYPT_10451}@tracestatus{draft}
/// @uptrace{RS_CRYPTO_02112}
/// @brief Comparison operator "equal" for @c Uuid operands.
/// @param[in] lhs  left-hand side operand
/// @param[in] rhs  right-hand side operand
/// @returns @c true if a binary representation of @c lhs is equal to @c rhs, and @c false otherwise
/// @threadsafety{Thread-safe}

inline constexpr bool operator==(const Uuid& lhs, const Uuid& rhs) noexcept
{
    return (lhs.mQwordMs == rhs.mQwordMs) && (lhs.mQwordLs == rhs.mQwordLs);
}

/// @traceid{SWS_CRYPT_10452}@tracestatus{draft}
/// @uptrace{RS_CRYPTO_02112}
/// @brief Comparison operator "less than" for @c Uuid operands.
/// @param[in] lhs  left-hand side operand
/// @param[in] rhs  right-hand side operand
/// @returns @c true if a binary representation of @c lhs is less than @c rhs, and @c false
/// otherwise
/// @threadsafety{Thread-safe}

inline constexpr bool operator<(const Uuid& lhs, const Uuid& rhs) noexcept
{
    return (lhs.mQwordMs < rhs.mQwordMs) ||
           ((lhs.mQwordMs == rhs.mQwordMs) && (lhs.mQwordLs < rhs.mQwordLs));
}

/// @traceid{SWS_CRYPT_10453}@tracestatus{draft}
/// @uptrace{RS_CRYPTO_02112}
/// @brief Comparison operator "greater than" for @c Uuid operands.
/// @param[in] lhs  left-hand side operand
/// @param[in] rhs  right-hand side operand
/// @returns @c true if a binary representation of @c lhs is greater than @c rhs, and @c false
/// otherwise
/// @threadsafety{Thread-safe}

inline constexpr bool operator>(const Uuid& lhs, const Uuid& rhs) noexcept
{
    return (lhs.mQwordMs > rhs.mQwordMs) ||
           ((lhs.mQwordMs == rhs.mQwordMs) && (lhs.mQwordLs > rhs.mQwordLs));
}

/// @traceid{SWS_CRYPT_10454}@tracestatus{draft}
/// @uptrace{RS_CRYPTO_02112}
/// @brief Comparison operator "not equal" for @c Uuid operands.
/// @param[in] lhs  left-hand side operand
/// @param[in] rhs  right-hand side operand
/// @returns @c true if a binary representation of @c lhs is not equal to @c rhs, and @c false
/// otherwise
/// @threadsafety{Thread-safe}

inline constexpr bool operator!=(const Uuid& lhs, const Uuid& rhs) noexcept
{
    return !(lhs == rhs);
}

/// @traceid{SWS_CRYPT_10455}@tracestatus{draft}
/// @uptrace{RS_CRYPTO_02112}
/// @brief Comparison operator "less than or equal" for @c Uuid operands.
/// @param[in] lhs  left-hand side operand
/// @param[in] rhs  right-hand side operand
/// @returns @c true if a binary representation of @c lhs is less than or equal to @c rhs, and @c
/// false otherwise
/// @threadsafety{Thread-safe}

inline constexpr bool operator<=(const Uuid& lhs, const Uuid& rhs) noexcept
{
    return !(lhs > rhs);
}

/// @traceid{SWS_CRYPT_10456}@tracestatus{draft}
/// @uptrace{RS_CRYPTO_02112}
/// @brief Comparison operator "greater than or equal" for @c Uuid operands.
/// @param[in] lhs  left-hand side operand
/// @param[in] rhs  right-hand side operand
/// @returns @c true if a binary representation of @c lhs is greater than or equal to @c rhs, and @c
/// false otherwise
/// @threadsafety{Thread-safe}

inline constexpr bool operator>=(const Uuid& lhs, const Uuid& rhs) noexcept
{
    return !(lhs < rhs);
}

} // namespace crypto
} // namespace ara

#endif // ARA_CRYPTO_COMMON_UUID_H_
