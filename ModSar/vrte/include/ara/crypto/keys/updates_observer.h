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
/// @brief Adaptive Autosar Crypto Stack. Key Storage API. Updates Observer interface definition.

#ifndef ARA_CRYPTO_KEYS_KEY_UPDATES_OBSERVER_H_
#define ARA_CRYPTO_KEYS_KEY_UPDATES_OBSERVER_H_

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "ara/crypto/keys/elementary_types.h"

namespace ara
{
namespace crypto
{
namespace keys
{
//- @interface UpdatesObserver
///
/// @traceid{SWS_CRYPT_30200}@tracestatus{draft}
/// @uptrace{RS_CRYPTO_02004}
/// @brief Definition of an "updates observer" interface.
///
///  The "updates observer" interface should be implemented by a consumer application, if a software
///          developer would like to get notifications about the slots' content update events.
class UpdatesObserver
{
public:
    /// @traceid{SWS_CRYPT_30201}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02004}
    /// @brief Shared smart pointer of the interface.
    using Uptr = std::unique_ptr<UpdatesObserver>;

    UpdatesObserver() = default;

    /// @traceid{SWS_CRYPT_30224}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02004}
    /// @brief Copy-assign another UpdatesObserver to this instance.
    /// @param other  the other instance
    /// @returns *this, containing the contents of @a other
    UpdatesObserver& operator=(const UpdatesObserver& other) = default;

    /// @traceid{SWS_CRYPT_30225}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02004}
    /// @brief Move-assign another UpdatesObserver to this instance.
    /// @param other  the other instance
    /// @returns *this, containing the contents of @a other
    UpdatesObserver& operator=(UpdatesObserver&& other) = default;

    UpdatesObserver(const UpdatesObserver& other) = default;
    UpdatesObserver(UpdatesObserver&& other) = default;

    /// @traceid{SWS_CRYPT_30210}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02004}
    /// @brief Destructor.
    virtual ~UpdatesObserver() noexcept = default;

    /// @traceid{SWS_CRYPT_30211}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02004}
    /// @brief Notification method that should be called if content of specified slots was changed.
    /// Key Storage engine should call this method in a dedicated thread.
    /// The provided list may include only slots subscribed for observing (during openning with the
    /// "User"
    ///       permissions, i.e. for "reading" via a call of the method @c OpenAsUser()).
    /// Each slot number may present in the provided list only one time!
    /// @param[in] updatedSlots  List of monitored slots that were updated after opening (for
    /// reading)
    /// @threadsafety{Thread-safe}
    virtual void OnUpdate(const TransactionScope& updatedSlots) noexcept = 0;
};

} // namespace keys
} // namespace crypto
} // namespace ara

#endif // ARA_CRYPTO_KEYS_UPDATES_OBSERVER_H_
