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
/// @brief Adaptive Autosar Crypto Stack. Common API. ProvidersFactory interface definition.

#ifndef ARA_CRYPTO_ENTRY_POINT_H_
#define ARA_CRYPTO_ENTRY_POINT_H_

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "ara/crypto/common/base_id_types.h"
#include "ara/crypto/cryp/crypto_provider.h"
#include "ara/crypto/keys/key_storage_provider.h"
#include "ara/crypto/x509/x509_provider.h"

#include "ara/core/instance_specifier.h"
#include "ara/core/result.h"

namespace ara
{
namespace crypto
{
/// @traceid{SWS_CRYPT_30001}@tracestatus{draft}
/// @uptrace{RS_CRYPTO_02401}
/// @brief 128 bit secure counter made up of most significant and least significant
///           quad-word of the hardware counter.
struct SecureCounter
{
    /// @traceid{SWS_CRYPT_30002}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02401}
    /// @brief least significant 64 bits
    std::uint64_t mLSQW;

    /// @traceid{SWS_CRYPT_30003}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02401}
    /// @brief most significant 64 bits
    std::uint64_t mMSQW;
};

/// @traceid{SWS_CRYPT_20099}@tracestatus{draft}
/// @uptrace{RS_CRYPTO_02401}
/// @brief Factory that creates or return existing single instance of specific Crypto Provider.
///  If <tt>(providerUid == nullptr)</tt> then platform default provider should be loaded.
/// @param[in] iSpecify  the globally unique identifier of required Crypto Provider
/// @returns unique smart pointer to loaded Crypto Provider
///
/// @threadsafety{Thread-safe}
ara::crypto::cryp::CryptoProvider::Uptr
LoadCryptoProvider(const ara::core::InstanceSpecifier& iSpecify) noexcept;

/// @traceid{SWS_CRYPT_20098}@tracestatus{draft}
/// @uptrace{RS_CRYPTO_02401}
/// @brief Get current value of 128 bit Secure Counter supported by the Crypto Stack.
///       Secure Counter is a non-rollover monotonic counter that ensures incrementation of its
///       value for each following call. The Secure Counter is presented by two 64 bit components:
///       Most Significant Quadword (MSQW) and Least Significant Quadword (LSQW). During normal
///       operation of the Crypto Stack, the MSQW value is fixed (unchangeable) and only LSQW should
///       be incremented. The LSQW counter can be implemented in the "low-power" (always-powered-up)
///       domain of the main CPU, but the MSQW in the Flash/EEPROM storage. But the MSQW must be
///       incremented if the LSQW reaches the maximum value of all ones. Also the MSQW must be
///       incremented during reinitialisation of the whole Crypto Stack (e.g. if the "low-power"
///       supply was interrupted by some reason). Permission to execute this routine is subject of
///       Identity and Access Management control and may be restricted by application manifest!
/// @returns a SecureCounter struct made up of the two unsigned 64 bit values (LSQW and MSQW)

/// @error SecurityErrorDomain::kUnsupported  if the Secure Counter is unsupported by the Crypto
/// Stack
///                implementation on this Platform
/// @error SecurityErrorDomain::kAccessViolation  if current Actor has no permission to call this
/// routine
/// @threadsafety{Thread-safe}
ara::core::Result<SecureCounter> GetSecureCounter() noexcept;

/// @traceid{SWS_CRYPT_30098}@tracestatus{draft}
/// @uptrace{RS_CRYPTO_02206}
/// @brief Return an allocated buffer with a generated random sequence of the requested size.
/// @param[in] count number of random bytes to generate
/// @returns @c a buffer filled with the generated random sequence
/// @error SecurityErrorDomain::kBusyResource  if the used RNG is currently out-of-entropy
///                 and therefore cannot provide the requested number of random bytes
/// @threadsafety{Thread-safe}
ara::core::Result<ara::core::Vector<ara::core::Byte>>
GenerateRandomData(std::uint32_t count) noexcept;

/// @traceid{SWS_CRYPT_30099}@tracestatus{draft}
/// @uptrace{RS_CRYPTO_02109}
/// @uptrace{RS_CRYPTO_02401}
/// @brief Factory that creates or return existing single instance of the Key Storage Provider.
/// @returns unique smart pointer to loaded Key Storage Provider
/// @error SecurityErrorDomain::kRuntimeFault  if the Key Storage Provider instance cannot be
/// created
/// @threadsafety{Thread-safe}
ara::crypto::keys::KeyStorageProvider::Uptr LoadKeyStorageProvider() noexcept;

/// @traceid{SWS_CRYPT_40099}@tracestatus{draft}
/// @uptrace{RS_CRYPTO_02306}
/// @brief Factory that creates or return existing single instance of the X.509 Provider.
///     X.509 Provider should use the default Crypto Provider for hashing and signature
///     verification!
///       Therefore when you load the X.509 Provider, in background it loads the default Crypto
///       Provider too.
/// @returns unique smart pointer to loaded X.509 Provider

/// @error SecurityErrorDomain::kRuntimeFault  if the X.509 Provider cannot be loaded
/// @threadsafety{Thread-safe}
ara::crypto::x509::X509Provider::Uptr LoadX509Provider() noexcept;

} // namespace crypto
} // namespace ara

#endif // ARA_CRYPTO_ENTRY_POINT_H_
