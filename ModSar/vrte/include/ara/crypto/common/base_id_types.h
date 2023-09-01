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
/// @brief Adaptive Autosar Crypto Stack. Common API. Base ID types definition.

#ifndef ARA_CRYPTO_COMMON_BASE_ID_TYPES_H_
#define ARA_CRYPTO_COMMON_BASE_ID_TYPES_H_

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "ara/core/vector.h"
#include <cstdint>
#include <memory>

namespace ara
{
namespace crypto
{
/// @traceid{SWS_CRYPT_10014}@tracestatus{draft}
/// @uptrace{RS_CRYPTO_02102}
/// @uptrace{RS_CRYPTO_02107}
/// @brief Container type of the Crypto Algorithm Identifier.
///
using CryptoAlgId = std::uint64_t;

/// @traceid{SWS_CRYPT_10015}@tracestatus{draft}
/// @uptrace{RS_CRYPTO_02111}
/// @brief A container type and constant bit-flags of allowed usages of a key or a secret seed
/// object.
///   Only directly specified usages of a key are allowed, all other are prohibited!
///   Similar set of flags are defined for the usage restrictions of original key/seed and for a
///   symmetric key or
///       seed that potentially can be derived from the original one.
///   A symmetric key or secret seed can be derived from the original one, only if it supports @c
///   kAllowKeyAgreement
///       or @c kAllowKeyDiversify or @c kAllowKeyDerivation!
///
using AllowedUsageFlags = std::uint32_t;

/// @traceid{SWS_CRYPT_10016}@tracestatus{draft}
/// @uptrace{RS_CRYPTO_02004}
/// @brief Enumeration of all types of crypto objects, i.e. types of content that can be stored to a
/// key slot.
///
enum class CryptoObjectType : std::uint32_t
{

    /// Object type is currently not defined (empty container)
    kUndefined = 0,
    /// @c cryp::SymmetricKey object
    kSymmetricKey = 1,
    /// @c cryp::PrivateKey object
    kPrivateKey = 2,
    /// @c cryp::PublicKey object
    kPublicKey = 3,
    /// @c cryp::Signature object (asymmetric digital signature or symmetric MAC/HMAC or hash
    /// digest)
    kSignature = 4,
    /// @c cryp::SecretSeed object. @b Note: the seed cannot have an associated crypto algorithm!
    kSecretSeed = 5

};

///
/// @traceid{SWS_CRYPT_10017}@tracestatus{draft}
/// @uptrace{RS_CRYPTO_02401}
/// @uptrace{RS_CRYPTO_02109}
/// @brief Enumeration of all known Provider types.
///
enum class ProviderType : std::uint32_t
{

    /// Undefined/Unknown Provider type (or applicable for the whole Crypto Stack)
    kUndefinedProvider = 0,
    /// Cryptography Provider
    kCryptoProvider = 1,
    /// Key Storage Provider
    kKeyStorageProvider = 2,
    /// X.509 Provider
    kX509Provider = 3

};

/// @traceid{SWS_CRYPT_10018}@tracestatus{draft}
/// @uptrace{RS_CRYPTO_02004}
/// @brief Enumeration of key-slot types; currently only machine and applicaiton key-slots are
/// defined.
///
enum class KeySlotType : std::uint32_t
{

    /// machine type key-slot - can be managed by application
    kMachine = 1,
    /// application exclusive type key-slot
    kApplication = 2

};

/// @traceid{SWS_CRYPT_10019}@tracestatus{draft}
/// @uptrace{RS_CRYPTO_02004}
/// @brief Enumeration of cryptographic transformations.
///
enum class CryptoTransform : std::uint32_t
{

    /// encryption
    kEncrypt = 1,
    /// decryption
    kDecrypt = 2,
    /// MAC verification
    kMacVerify = 3,
    /// MAC generation
    kMacGenerate = 4,
    /// key wrapping
    kWrap = 5,
    /// key unwrapping
    kUnwrap = 6,
    /// signature verification
    kSigVerify = 7,
    /// signature generation
    kSigGenerate = 8

};

// Common grouped constants should be numbered in the way similar to interfaces:
// SWS_CRYPT_1YYXX:
//   - ZZ - constants group ID (30-59)
//   - XX - constant definition ID (00-99)

///          Effective values of Crypto Algorithm IDs are specific for concrete Crypto Stack
///          implementation. But the zero value is reserved for especial purposes, that can differ
///          depending from a usage context. This group defines a few constant names of the single
///          zero value, but semantically they have different meaning specific for concrete
///          application of the constant.

/// @traceid{SWS_CRYPT_13000}@tracestatus{draft}
/// @uptrace{RS_CRYPTO_02107}
/// @brief Algorithm ID is undefined.
///    Also this value may be used in meanings: Any or Default algorithm, None of algorithms.
///
const CryptoAlgId kAlgIdUndefined = 0u;

/// @traceid{SWS_CRYPT_13001}@tracestatus{draft}
/// @uptrace{RS_CRYPTO_02107}
/// @brief Any Algorithm ID is allowed.
///
const CryptoAlgId kAlgIdAny = kAlgIdUndefined;

/// @traceid{SWS_CRYPT_13002}@tracestatus{draft}
/// @uptrace{RS_CRYPTO_02107}
/// @brief Default Algorithm ID (in current context/primitive).
///
const CryptoAlgId kAlgIdDefault = kAlgIdUndefined;

/// @traceid{SWS_CRYPT_13003}@tracestatus{draft}
/// @uptrace{RS_CRYPTO_02107}
/// @brief None of Algorithm ID (i.e. an algorithm definition is not applicable).
///
const CryptoAlgId kAlgIdNone = kAlgIdUndefined;

///  This group contains list of constant 1-bit values predefined for Allowed Usage flags.

/// @traceid{SWS_CRYPT_13100}@tracestatus{draft}
/// @uptrace{RS_CRYPTO_02111}
/// @brief The key/seed usage will be fully specified by a key slot prototype (the object can be
/// used only after
///           reloading from the slot).
///
const AllowedUsageFlags kAllowPrototypedOnly = 0;

/// @traceid{SWS_CRYPT_13101}@tracestatus{draft}
/// @uptrace{RS_CRYPTO_02111}
/// @brief The key/seed can be used for data encryption initialization (applicable to symmetric and
/// asymmetric
///           algorithms).
///
const AllowedUsageFlags kAllowDataEncryption = 0x0001;

/// @traceid{SWS_CRYPT_13102}@tracestatus{draft}
/// @uptrace{RS_CRYPTO_02111}
/// @brief The key/seed can be used for data decryption initialization (applicable to symmetric and
/// asymmetric
///           algorithms).
///
const AllowedUsageFlags kAllowDataDecryption = 0x0002;

/// @traceid{SWS_CRYPT_13103}@tracestatus{draft}
/// @uptrace{RS_CRYPTO_02111}
/// @brief The key/seed can be used for digital signature or MAC/HMAC production (applicable to
/// symmetric and
///           asymmetric algorithms).
///
const AllowedUsageFlags kAllowSignature = 0x0004;

/// @traceid{SWS_CRYPT_13104}@tracestatus{draft}
/// @uptrace{RS_CRYPTO_02111}
/// @brief The key/seed can be used for digital signature or MAC/HMAC verification (applicable to
/// symmetric and
///           asymmetric algorithms).
///
const AllowedUsageFlags kAllowVerification = 0x0008;

/// @traceid{SWS_CRYPT_13105}@tracestatus{draft}
/// @uptrace{RS_CRYPTO_02111}
/// @brief The seed or asymmetric key can be used for key-agreement protocol execution.
///
const AllowedUsageFlags kAllowKeyAgreement = 0x0010;

/// @traceid{SWS_CRYPT_13106}@tracestatus{draft}
/// @uptrace{RS_CRYPTO_02111}
/// @brief The seed or symmetric key can be used for slave-keys diversification.
///
const AllowedUsageFlags kAllowKeyDiversify = 0x0020;

/// @traceid{SWS_CRYPT_13107}@tracestatus{draft}
/// @uptrace{RS_CRYPTO_02111}
/// @brief The seed or symmetric key can be used for seeding of a RandomGeneratorCtx
///
const AllowedUsageFlags kAllowRngInit = 0x0040;

/// @traceid{SWS_CRYPT_13108}@tracestatus{draft}
/// @uptrace{RS_CRYPTO_02111}
/// @brief The object can be used as an input key material to KDF.
///           The seed or symmetric key can be used as a @c RestrictedUseObject for slave-keys
///           derivation via a Key Derivation Function (KDF).
///
const AllowedUsageFlags kAllowKdfMaterial = 0x0080;

/// @traceid{SWS_CRYPT_13109}@tracestatus{draft}
/// @uptrace{RS_CRYPTO_02111}
/// @brief The key can be used as "transport" one for Key-Wrap or Encapsulate transformations
/// (applicable to
///           symmetric and asymmetric keys).
///
const AllowedUsageFlags kAllowKeyExporting = 0x0100;

/// @traceid{SWS_CRYPT_13110}@tracestatus{draft}
/// @uptrace{RS_CRYPTO_02111}
/// @brief The key can be used as "transport" one for Key-Unwrap or Decapsulate transformations
/// (applicable to
///           symmetric and asymmetric keys).
///
const AllowedUsageFlags kAllowKeyImporting = 0x0200;

/// @traceid{SWS_CRYPT_13111}@tracestatus{draft}
/// @uptrace{RS_CRYPTO_02111}
/// @brief The key can be used only for the mode directly specified by @c Key::AlgId.
///
const AllowedUsageFlags kAllowExactModeOnly = 0x8000;

/// @traceid{SWS_CRYPT_13112}@tracestatus{draft}
/// @uptrace{RS_CRYPTO_02111}
/// @brief A derived seed or symmetric key can be used for data encryption.
///
const AllowedUsageFlags kAllowDerivedDataEncryption = kAllowDataEncryption << 16;

/// @traceid{SWS_CRYPT_13113}@tracestatus{draft}
/// @uptrace{RS_CRYPTO_02111}
/// @brief A derived seed or symmetric key can be used for data decryption.
///
const AllowedUsageFlags kAllowDerivedDataDecryption = kAllowDataDecryption << 16;

/// @traceid{SWS_CRYPT_13114}@tracestatus{draft}
/// @uptrace{RS_CRYPTO_02111}
/// @brief A derived seed or symmetric key can be used for MAC/HMAC production.
///
const AllowedUsageFlags kAllowDerivedSignature = kAllowSignature << 16;

/// @traceid{SWS_CRYPT_13115}@tracestatus{draft}
/// @uptrace{RS_CRYPTO_02111}
/// @brief A derived seed or symmetric key can be used for MAC/HMAC verification.
///
const AllowedUsageFlags kAllowDerivedVerification = kAllowVerification << 16;

/// @traceid{SWS_CRYPT_13116}@tracestatus{draft}
/// @uptrace{RS_CRYPTO_02111}
/// @brief A derived seed or symmetric key can be used for slave-keys diversification.
///
const AllowedUsageFlags kAllowDerivedKeyDiversify = kAllowKeyDiversify << 16;

/// @traceid{SWS_CRYPT_13117}@tracestatus{draft}
/// @uptrace{RS_CRYPTO_02111}
/// @brief A derived seed or symmetric key can be used for seeding of a RandomGeneratorContext
///
const AllowedUsageFlags kAllowDerivedRngInit = kAllowRngInit << 16;

/// @traceid{SWS_CRYPT_13118}@tracestatus{draft}
/// @uptrace{RS_CRYPTO_02111}
/// @brief A derived seed or symmetric key can be used as a @c RestrictedUseObject for slave-keys
/// derivation via a Key
///           Derivation Function (KDF).
///
const AllowedUsageFlags kAllowDerivedKdfMaterial = kAllowKdfMaterial << 16;

/// @traceid{SWS_CRYPT_13119}@tracestatus{draft}
/// @uptrace{RS_CRYPTO_02111}
/// @brief A derived seed or symmetric key can be used as a "transport" one for Key-Wrap
/// transformation.
///
const AllowedUsageFlags kAllowDerivedKeyExporting = kAllowKeyExporting << 16;

/// @traceid{SWS_CRYPT_13120}@tracestatus{draft}
/// @uptrace{RS_CRYPTO_02111}
/// @brief A derived seed or symmetric key can be used as a "transport" one for Key-Unwrap
/// transformation.
///
const AllowedUsageFlags kAllowDerivedKeyImporting = kAllowKeyImporting << 16;

/// @traceid{SWS_CRYPT_13121}@tracestatus{draft}
/// @uptrace{RS_CRYPTO_02111}
/// @brief Restrict usage of derived objects to specified operation mode only.
///           A derived seed or symmetric key can be used only for the mode directly specified by @c
///           Key::AlgId.
///
const AllowedUsageFlags kAllowDerivedExactModeOnly = kAllowExactModeOnly << 16;

/// @traceid{SWS_CRYPT_13122}@tracestatus{draft}
/// @uptrace{RS_CRYPTO_02111}
/// @brief Allow usage of the object as a key material for KDF and any usage of derived objects.
///           The seed or symmetric key can be used as a @c RestrictedUseObject for a Key Derivation
///           Function (KDF) and the derived "slave" keys can be used without limitations.
///
const AllowedUsageFlags kAllowKdfMaterialAnyUsage =
    kAllowKdfMaterial | kAllowDerivedDataEncryption | kAllowDerivedDataDecryption |
    kAllowDerivedSignature | kAllowDerivedVerification | kAllowDerivedKeyDiversify |
    kAllowDerivedRngInit | kAllowDerivedKdfMaterial | kAllowDerivedKeyExporting |
    kAllowDerivedKeyImporting;

// just make it compile
// DO NOT MAKE A SWS_ID!!
#define VENDOR_IMPLEMENTATION_DEFINED std::allocator<std::uint8_t>

/// @traceid{SWS_CRYPT_10042}@tracestatus{draft}
/// @uptrace{RS_CRYPTO_02201}
/// @uptrace{RS_CRYPTO_02202}
/// @uptrace{RS_CRYPTO_02203}
/// @uptrace{RS_CRYPTO_02204}
/// @uptrace{RS_CRYPTO_02205}
/// @uptrace{RS_CRYPTO_02206}
/// @uptrace{RS_CRYPTO_02207}
/// @uptrace{RS_CRYPTO_02208}
/// @uptrace{RS_CRYPTO_02209}
/// @brief Alias of a bytes' vector template with customizable allocator
/// @tparam Alloc  custom allocator of bytes sequences
template<class Alloc = VENDOR_IMPLEMENTATION_DEFINED>
using ByteVector = ara::core::Vector<std::uint8_t, Alloc>;

} // namespace crypto
} // namespace ara

#endif // ARA_CRYPTO_COMMON_BASE_ID_TYPES_H_
