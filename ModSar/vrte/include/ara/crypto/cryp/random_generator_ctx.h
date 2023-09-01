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
/// @brief Adaptive Autosar Crypto Stack. Cryptographic API. RandomGeneratorCtx interface definition.

#ifndef ARA_CRYPTO_CRYP_RANDOM_GENERATOR_CTX_H_
#define ARA_CRYPTO_CRYP_RANDOM_GENERATOR_CTX_H_

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "ara/crypto/common/mem_region.h"

#include "ara/crypto/cryp/cryobj/symmetric_key.h"
#include "ara/crypto/cryp/cryobj/secret_seed.h"
#include "ara/crypto/cryp/crypto_context.h"
#include "ara/crypto/cryp/extension_service.h"

#include "ara/core/result.h"

namespace ara
{
namespace crypto
{
namespace cryp
{

//- @interface RandomGeneratorCtx
///
/// @traceid{SWS_CRYPT_22900}@tracestatus{draft}
/// @uptrace{RS_CRYPTO_02206}
/// @brief Interface of Random Number Generator Context.
///
 
class RandomGeneratorCtx
    : public CryptoContext
{
public:
    /// @traceid{SWS_CRYPT_22901}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02206}
    /// @brief Shared smart pointer of the interface.
     
    using Uptr = std::unique_ptr<RandomGeneratorCtx>;

    /// @traceid{SWS_CRYPT_22902}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02006}
    /// @brief Get ExtensionService instance.
     
    virtual ExtensionService::Uptr GetExtensionService() const noexcept = 0;

    /// @traceid{SWS_CRYPT_22911}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02206}
    /// @brief Set the internal state of the RNG using the provided seed
    /// @param[in] seed  a memory region with the seed value
    /// @returns @c true if the method is supported and the state has been set successfully
    /// @threadsafety{Thread-safe}
     
    virtual bool Seed(ReadOnlyMemRegion seed) noexcept = 0;

    /// @traceid{SWS_CRYPT_22912}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02206}
    /// @brief Set the internal state of the RNG using the provided seed
    /// @param[in] seed  a memory region with the seed value
    /// @returns @c true if the method is supported and the state has been set successfully
    /// @threadsafety{Thread-safe}
     
    virtual bool Seed(const SecretSeed& seed) noexcept = 0;

    /// @traceid{SWS_CRYPT_22913}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02001}
    /// @uptrace{RS_CRYPTO_02003}
    /// @brief Set the internal state of the RNG using the provided seed
    /// @param[in] key  a SymmetricKey with the key used as seed value
    /// @returns @c true if the method is supported and the key has been set successfully
    /// @threadsafety{Thread-safe}
     
    virtual bool SetKey(const SymmetricKey& key) noexcept = 0;

    /// @traceid{SWS_CRYPT_22914}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02206}
    /// @brief Update the internal state of the RNG by mixing it with the provided additional entropy.
	/// This method is optional for implementation.
    /// An implementation of this method may "accumulate" provided entropy for future use.
    /// @param[in] entropy  a memory region with the additional entropy value
    /// @returns @c true if the method is supported and the entropy has been updated successfully

    ///
    /// @threadsafety{Thread-safe}
     
    virtual bool AddEntropy(ReadOnlyMemRegion entropy) noexcept = 0;

    /// @traceid{SWS_CRYPT_22915}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02206}
    /// @brief Return an allocated buffer with a generated random sequence of the requested size.
	/// @param[in] count number of random bytes to generate
    /// @returns @c a buffer filled with the generated random sequence
    /// @error CryptoErrorDomain::kUninitializedContext  if this context implements a local RNG 
    ///                (i.e., the RNG state is controlled by the application), and has to be seeded by the 
    ///                application because it either has not already been seeded or ran out of entropy.
    /// @error CryptoErrorDomain::kBusyResource  if this context implements a global RNG (i.e., the RNG 
    ///                state is controlled by the stack and not the application) that is currently out-of-entropy
    ///                 and therefore cannot provide the requested number of random bytes
    ///
    /// @threadsafety{Thread-safe}
     
    virtual ara::core::Result<ara::core::Vector<ara::core::Byte>>  Generate(std::uint32_t count) noexcept  = 0;

};

}  // namespace cryp
}  // namespace crypto
}  // namespace ara

#endif  // ARA_CRYPTO_CRYP_RANDOM_GENERATOR_CTX_H_
