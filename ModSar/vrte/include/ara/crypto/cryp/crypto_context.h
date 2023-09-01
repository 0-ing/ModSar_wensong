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
/// @brief Adaptive Autosar Crypto Stack. Cryptographic API. CryptoContext interface definition.

#ifndef ARA_CRYPTO_CRYP_CRYPTO_CONTEXT_H_
#define ARA_CRYPTO_CRYP_CRYPTO_CONTEXT_H_

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "ara/crypto/cryp/cryobj/crypto_primitive_id.h"

class CryptoProvider;

namespace ara
{
namespace crypto
{
namespace cryp
{

//- @interface CryptoContext
///
/// @traceid{SWS_CRYPT_20400}@tracestatus{draft}
/// @uptrace{RS_CRYPTO_02008}
/// @brief A common interface of a mutable cryptographic context, i.e. that is not binded to a single crypto object.
///
 
class CryptoContext
{
public:
    /// @traceid{SWS_CRYPT_20401}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02008}
    /// @brief Destructor.
    virtual ~CryptoContext() noexcept = default;

    /// @traceid{SWS_CRYPT_30214}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02004}
    /// @brief Copy-assign another CryptoContext to this instance.
    /// @param other  the other instance
    /// @returns *this, containing the contents of @a other
    CryptoContext& operator=(const CryptoContext& other) = default;

    /// @traceid{SWS_CRYPT_30215}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02004}
    /// @brief Move-assign another CryptoContext to this instance.
    /// @param other  the other instance
    /// @returns *this, containing the contents of @a other
    CryptoContext& operator=(CryptoContext&& other) = default;

    CryptoContext(const CryptoContext& other) = default;
    CryptoContext(CryptoContext&& other) = default;
    CryptoContext() = default;

    /// @traceid{SWS_CRYPT_20402}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02008}
    /// @brief Type definition of vendor specific binary Crypto Primitive ID.
    using AlgId = CryptoAlgId;

	/// @traceid{SWS_CRYPT_20411}@tracestatus{draft}
	/// @uptrace{RS_CRYPTO_02008}
	/// @brief Return CryptoPrimitivId instance containing instance identification.
	///
	virtual CryptoPrimitiveId::Uptr GetCryptoPrimitiveId() const noexcept = 0;

    /// @traceid{SWS_CRYPT_20412}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02309}
    /// @brief Check if the crypto context is already initialized and ready to use.
    ///           It checks all required values, including: key value, IV/seed, etc.
    /// @returns @c true if the crypto context is completely initialized and ready to use, and @c false otherwise
    ///
    /// @threadsafety{Thread-safe}
    virtual bool IsInitialized() const noexcept = 0;

    /// @traceid{SWS_CRYPT_20654}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02401}
    /// @brief Get a reference to Crypto Provider of this context.
    /// @returns a reference to Crypto Provider instance that provides this context
    /// @threadsafety{Thread-safe}
    virtual CryptoProvider& MyProvider() const noexcept = 0;
};

}  // namespace cryp
}  // namespace crypto
}  // namespace ara

#endif  // ARA_CRYPTO_CRYP_CRYPTO_CONTEXT_H_
