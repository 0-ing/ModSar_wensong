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
/// @brief Adaptive Autosar Crypto Stack. VolatileTrustedContainer interface definition.

#ifndef ARA_CRYPTO_COMMON_VOLATILE_TRUSTED_CONTAINER_H_
#define ARA_CRYPTO_COMMON_VOLATILE_TRUSTED_CONTAINER_H_

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "ara/crypto/common/base_id_types.h"
#include "ara/crypto/common/io_interface.h"

namespace ara
{
namespace crypto
{
//- @interface VolatileTrustedContainer
///
/// @traceid{SWS_CRYPT_10850}@tracestatus{draft}
/// @uptrace{RS_CRYPTO_02004}
/// @brief This explicit interface of a volatile Trusted Container is used for buffering CryptoAPI
/// objects in RAM.
///       This class represents a "smart buffer" in that it provides access to the IOInterface,
///       which can be used for querying meta-data of the buffer content.
class VolatileTrustedContainer
{
public:
    /// @traceid{SWS_CRYPT_10851}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02004}
    /// @brief Destructor.
    virtual ~VolatileTrustedContainer() noexcept = default;

    /// @traceid{SWS_CRYPT_30206}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02004}
    /// @brief Copy-assign another VolatileTrustedContainer to this instance.
    /// @param other  the other instance
    /// @returns *this, containing the contents of @a other
    VolatileTrustedContainer& operator=(const VolatileTrustedContainer& other) = default;

    /// @traceid{SWS_CRYPT_30207}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02004}
    /// @brief Move-assign another VolatileTrustedContainer to this instance.
    /// @param other  the other instance
    /// @returns *this, containing the contents of @a other
    VolatileTrustedContainer& operator=(VolatileTrustedContainer&& other) = default;

    VolatileTrustedContainer(const VolatileTrustedContainer& other) = default;
    VolatileTrustedContainer(VolatileTrustedContainer&& other) = default;
    VolatileTrustedContainer() = default;

    /// @traceid{SWS_CRYPT_10852}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02004}
    /// @brief Unique smart pointer of the interface.
    using Uptr = std::unique_ptr<VolatileTrustedContainer>;

    /// @traceid{SWS_CRYPT_10853}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02004}
    /// @brief Retrieve the IOInterface used for importing/exporting objects into this container
    /// @returns a reference to the IOInterface of this container
    virtual IOInterface& GetIOInterface() const noexcept = 0;
};

} // namespace crypto
} // namespace ara

#endif /* ARA_CRYPTO_COMMON_VOLATILE_TRUSTED_CONTAINER_H_ */
