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
/// @brief Adaptive Autosar Crypto Stack. Key Storage API. KeyStorageProvider interface definition.

#ifndef ARA_CRYPTO_KEYS_KEY_STORAGE_PROVIDER_H_
#define ARA_CRYPTO_KEYS_KEY_STORAGE_PROVIDER_H_

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "ara/crypto/common/io_interface.h"

#include "ara/crypto/keys/elementary_types.h"
#include "ara/crypto/keys/key_slot_content_props.h"
#include "ara/crypto/keys/key_slot_prototype_props.h"
#include "ara/crypto/keys/keyslot.h"
#include "ara/crypto/keys/updates_observer.h"

#include "ara/crypto/cryp/signer_private_ctx.h"

#include "ara/core/instance_specifier.h"
#include "ara/core/result.h"

namespace ara
{
namespace crypto
{
namespace keys
{
//- @interface KeyStorageProvider
///
/// @traceid{SWS_CRYPT_30100}@tracestatus{draft}
/// @uptrace{RS_CRYPTO_02109}
/// @uptrace{RS_CRYPTO_02305}
/// @uptrace{RS_CRYPTO_02401}
/// @brief Key Storage Provider interface.
///        Any object is uniquely identified by the combination of its UUID and type.
///        HSMs/TPMs implementing the concept of "non-extractable keys" should use own copies of
///        externally supplied crypto objects. A few software Crypto Providers can share single key
///        slot if they support same format.
///
///
class KeyStorageProvider
{
public:
    /// @traceid{SWS_CRYPT_30101}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02004}
    ///
    using Uptr = std::unique_ptr<KeyStorageProvider>;

    /// @traceid{SWS_CRYPT_30110}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02004}
    /// @brief Destructor.
    virtual ~KeyStorageProvider() noexcept = default;

    /// @traceid{SWS_CRYPT_30222}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02004}
    /// @brief Copy-assign another KeyStorageProvider to this instance.
    /// @param other  the other instance
    /// @returns *this, containing the contents of @a other
    KeyStorageProvider& operator=(const KeyStorageProvider& other) = default;

    /// @traceid{SWS_CRYPT_30223}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02004}
    /// @brief Move-assign another KeyStorageProvider to this instance.
    /// @param other  the other instance
    /// @returns *this, containing the contents of @a other
    KeyStorageProvider& operator=(KeyStorageProvider&& other) = default;

    KeyStorageProvider(const KeyStorageProvider& other) = default;
    KeyStorageProvider(KeyStorageProvider&& other) = default;
    KeyStorageProvider() = default;

    /// @traceid{SWS_CRYPT_30115}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02004}
    /// @brief Load a key slot.
    ///       The functions loads the information associated with a KeySlot into a KeySlot object.
    /// @param[in] iSpecify  the target key-slot instance specifier
    /// @returns an unique smart pointer to allocated key slot
    /// @error SecurityErrorDomain::kUnreservedResource  if the InstanceSpecifier is incorrect (the
    /// slot is not
    ///                allocated)
    /// @threadsafety{Thread-safe}
    ///
    virtual ara::core::Result<KeySlot::Uptr>
    LoadKeySlot(ara::core::InstanceSpecifier& iSpecify) noexcept = 0;

    /// @traceid{SWS_CRYPT_30123}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02004}
    /// @brief Begin new transaction for key slots update.
    ///  In order for a keyslot to be part of a transaction scope, the reserveSpareSlot model
    ///  parameter of the keyslot
    ///          has to be set to true.
    ///         A transaction is dedicated for updating related key slots simultaneously (in an
    ///         atomic, all-or-nothing, way).
    ///     All key slots that should be updated by the transaction have to be opened and provided
    ///     to this function. Any changes to the slots in scope are executed by calling commit().
    /// @param[in] targetSlots  a list of KeySlots that should be updated during this transaction.
    /// @returns a unique ID assigned to this transaction
    /// @error SecurityErrorDomain::kUnreservedResource if @c targetSlots list has a slot that has
    /// not been configured
    ///                 with the reserveSpareSlot parameter in the manifest
    /// @error SecurityErrorDomain::kBusyResource  if @c targetSlots list has key slots that are
    /// already
    ///                involved to another pending transaction or opened in writing mode
    /// @threadsafety{Thread-safe}
    ///
    virtual ara::core::Result<TransactionId>
    BeginTransaction(const TransactionScope& targetSlots) noexcept = 0;

    /// @traceid{SWS_CRYPT_30124}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02004}
    /// @brief Commit changes of the transaction to Key Storage.
    ///        Any changes of key slots made during a transaction are invisible up to the commit
    ///        execution.
    ///       The commit command permanently saves all changes made during the transaction in Key
    ///       Storage
    /// @param[in] id  an ID of a transaction that should be commited
    /// @error SecurityErrorDomain::kInvalidArgument  if provided @c id is invalid, i.e. this ID is
    /// unknown
    ///                or correspondent transaction already was finished (commited or rolled back)
    /// @threadsafety{Thread-safe}
    ///
    virtual ara::core::Result<void> CommitTransaction(TransactionId id) noexcept = 0;

    /// @traceid{SWS_CRYPT_30125}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02004}
    /// @brief Rollback all changes executed during the transaction in Key Storage.
    ///          The rollback command permanently cancels all changes made during the transaction in
    ///          Key Storage. A rolled back transaction is completely invisible for all
    ///          applications.
    /// @param[in] id  an ID of a transaction that should be rolled back
    /// @error SecurityErrorDomain::kInvalidArgument  if provided @c id is invalid, i.e. this ID is
    /// unknown
    ///                or correspondent transaction already was finished (commited or rolled back)
    /// @threadsafety{Thread-safe}
    ///
    virtual ara::core::Result<void> RollbackTransaction(TransactionId id) noexcept = 0;

    /// @traceid{SWS_CRYPT_30126}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02004}
    /// @brief Unsubscribe the Update Observer from changes monitoring of the specified slot.
    /// @param[in] slot  number of a slot that should be unsubscribed from the updates observing
    /// @error SecurityErrorDomain::kInvalidArgument  if the specified slot is not monitored now
    /// (i.e. if it
    ///        was not successfully opened via @c OpenAsUser() or it was already unsubscribed by
    ///        this method)
    /// @threadsafety{Thread-safe}
    ///
    virtual ara::core::Result<void> UnsubscribeObserver(KeySlot& slot) noexcept = 0;

    /// @traceid{SWS_CRYPT_30130}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02401}
    /// @brief Register consumer Updates Observer.
    ///  Only one instance of the @c UpdatesObserver may be registered by an application process,
    ///  therefore this
    ///       method always unregister previous observer and return its unique pointer.
    ///  If <tt>(nullptr == observer)</tt> then the method only unregister the previous observer!
    ///  The method returns @c nullptr if no observers have been registered yet!
    /// @param[in] observer  optional pointer to a client-supplied @c UpdatesObserver instance that
    /// should be registered
    ///            inside %Key Storage implementation and called every time, when an opened for
    ///            usage/loading key slot is updated externally (by its "Owner" application)
    /// @returns unique pointer to previously registered Updates Observer interface (the pointer
    /// ownership is "moved out"
    ///          to the caller code)
    /// @threadsafety{Thread-safe}
    ///
    virtual UpdatesObserver::Uptr
    RegisterObserver(UpdatesObserver::Uptr observer = nullptr) noexcept = 0;

    /// @traceid{SWS_CRYPT_30131}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02401}
    /// @brief Get pointer of registered Updates Observer.
    ///  The method returns @c nullptr if no observers have been registered yet!
    /// @returns unique pointer to the registered Updates Observer interface (copy of an internal
    /// unique pointer
    ///          is returned, i.e. the %Key Storage provider continues to keep the ownership)
    /// @threadsafety{Thread-safe}
    ///
    virtual UpdatesObserver::Uptr GetRegisteredObserver() const noexcept = 0;
};

} // namespace keys
} // namespace crypto
} // namespace ara

#endif // ARA_CRYPTO_KEYS_KEY_STORAGE_PROVIDER_H_
