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

#ifndef ARA_PER_KEY_VALUE_STORAGE_H_
#define ARA_PER_KEY_VALUE_STORAGE_H_

#include "ara/core/instance_specifier.h"
#include "ara/core/result.h"
#include "ara/core/string.h"
#include "ara/core/vector.h"

#include "ara/per/per_error_domain.h"
#include "ara/per/shared_handle.h"

namespace ara
{
namespace per
{

/// @brief The Key-Value Storage contains a set of keys with associated values.
///
/// @traceid{SWS_PER_00339}@tracestatus{valid}
/// @uptrace{RS_PER_00002}
/// @uptrace{RS_AP_00122}
/// @uptrace{RS_AP_00146}
/// @warning "final" Keyword was removed because current implementation inherits from the KeyValueStorage class
class KeyValueStorage // final
{
public:
    /// @brief The default constructor for KeyValueStorage shall not be used.
    ///
    /// @traceid{SWS_PER_00459}@tracestatus{draft}
    /// @uptrace{RS_PER_00002}
    /// @uptrace{RS_AP_00120}
    /// @uptrace{RS_AP_00129}
    /// @uptrace{RS_AP_00146}
    KeyValueStorage() = default;

    /// @brief The move constructor for KeyValueStorage shall not be used.
    ///
    /// @traceid{SWS_PER_00322}@tracestatus{valid}
    /// @uptrace{RS_PER_00002}
    /// @uptrace{RS_AP_00120}
    /// @uptrace{RS_AP_00121}
    /// @uptrace{RS_AP_00129}
    /// @uptrace{RS_AP_00132}
    KeyValueStorage(KeyValueStorage&& kvs) = delete;

    /// @brief The move assignment operator for KeyValueStorage shall not be used.
    ///
    /// @traceid{SWS_PER_00323}@tracestatus{valid}
    /// @uptrace{RS_PER_00002}
    /// @uptrace{RS_AP_00119}
    /// @uptrace{RS_AP_00120}
    /// @uptrace{RS_AP_00121}
    /// @uptrace{RS_AP_00132}
    KeyValueStorage& operator=(KeyValueStorage&& kvs) & = delete;

    /// @brief The copy constructor for KeyValueStorage shall not be used.
    ///
    /// @traceid{SWS_PER_00324}@tracestatus{valid}
    /// @uptrace{RS_PER_00002}
    /// @uptrace{RS_AP_00120}
    KeyValueStorage(const KeyValueStorage&) = delete;

    /// @brief The copy assignment operator for KeyValueStorage shall not be used.
    ///
    /// @traceid{SWS_PER_00325}@tracestatus{valid}
    /// @uptrace{RS_PER_00002}
    /// @uptrace{RS_AP_00119}
    /// @uptrace{RS_AP_00120}
    KeyValueStorage& operator=(const KeyValueStorage&) = delete;

    /// @brief Destructor for KeyValueStorage.
    ///
    /// @traceid{SWS_PER_00050}@tracestatus{valid}
    /// @uptrace{RS_PER_00002}
    /// @uptrace{RS_AP_00120}
    /// @uptrace{RS_AP_00129}
    /// @uptrace{RS_AP_00132}
    /// @uptrace{RS_AP_00134}
    /// @threadsafety{no}
    virtual ~KeyValueStorage() noexcept = default;

    /// @brief Returns a list of all currently available keys of this Key-Value Storage.
    ///
    /// The list of keys is only accurate if no key-value pair is added or deleted at the same
    /// time.
    ///
    /// @traceid{SWS_PER_00042}@tracestatus{valid}
    /// @uptrace{RS_PER_00003}
    /// @uptrace{RS_AP_00119}
    /// @uptrace{RS_AP_00120}
    /// @uptrace{RS_AP_00127}
    /// @uptrace{RS_AP_00129}
    /// @uptrace{RS_AP_00132}
    /// @threadsafety{re-entrant}
    /// @returns A Result containing a list of available keys. In case of an error, it contains any of the errors
    ///          defined below, or a vendor specific error.
    /// @error PerErrc::kPhysicalStorageFailure Returned if access to the storage fails.
    /// @error PerErrc::kIntegrityCorrupted Returned if stored data cannot be read because the structural integrity is
    ///                                     corrupted.
    /// @error PerErrc::kValidationFailed Returned if the validity of stored data cannot be ensured.
    /// @error PerErrc::kEncryptionFailed Returned if the decryption of stored data fails.
    virtual ara::core::Result<ara::core::Vector<ara::core::String>> GetAllKeys() const noexcept = 0;

    /// @brief Checks if a key-value pair exists in this Key-Value Storage.
    ///
    /// The result is only accurate if no key-value pair is added or deleted at the same time. E.g. when a key-value
    /// pair is removed in another thread directly after this function returned "true", the result is not valid anymore.
    ///
    /// @traceid{SWS_PER_00043}@tracestatus{valid}
    /// @uptrace{RS_PER_00003}
    /// @uptrace{RS_AP_00119}
    /// @uptrace{RS_AP_00120}
    /// @uptrace{RS_AP_00121}
    /// @uptrace{RS_AP_00127}
    /// @uptrace{RS_AP_00132}
    /// @threadsafety{re-entrant}
    /// @param[in] key The key that shall be checked.
    /// @returns A Result containing true if the key could be located or false if it couldn't. In case of an error, it
    ///          contains any of the errors defined below, or a vendor specific error.
    /// @error PerErrc::kPhysicalStorageFailure Returned if access to the storage fails.
    /// @error PerErrc::kIntegrityCorrupted Returned if stored data cannot be read because the structural integrity is
    ///                                     corrupted.
    /// @error PerErrc::kValidationFailed Returned if the validity of stored data cannot be ensured.
    /// @error PerErrc::kEncryptionFailed Returned if the decryption of stored data fails.
    virtual ara::core::Result<bool> KeyExists(ara::core::StringView key) const noexcept = 0;

    /// @brief Returns the value assigned to a key of this Key-Value Storage.
    ///
    /// GetValue may be delayed by an ongoing call from another thread to RemoveAllKeys or DiscardPendingChanges, or to
    /// SetValue, RemoveKey, RecoverKey, or ResetKey for the same key-value pair.
    ///
    /// @traceid{SWS_PER_00332}@tracestatus{valid}
    /// @uptrace{RS_PER_00003}
    /// @uptrace{RS_PER_00010}
    /// @uptrace{RS_AP_00119}
    /// @uptrace{RS_AP_00120}
    /// @uptrace{RS_AP_00121}
    /// @uptrace{RS_AP_00127}
    /// @uptrace{RS_AP_00128}
    /// @uptrace{RS_AP_00129}
    /// @uptrace{RS_AP_00132}
    /// @threadsafety{re-entrant}
    /// @tparam T The type of the value that shall be retrieved.
    /// @param[in] key The key to look up.
    /// @returns A Result containing the retrieved value. In case of an error, it contains any of the errors defined
    ///          below, or a vendor specific error.
    /// @error PerErrc::kKeyNotFound Returned if the provided key does not exist in the Key-Value Storage.
    /// @error PerErrc::kPhysicalStorageFailure Returned if access to the storage fails.
    /// @error PerErrc::kIntegrityCorrupted Returned if stored data cannot be read because the structural integrity is
    ///                                     corrupted.
    /// @error PerErrc::kValidationFailed Returned if the validity of stored data cannot be ensured.
    /// @error PerErrc::kEncryptionFailed Returned if the decryption of stored data fails.
    /// @error PerErrc::kDataTypeMismatch Returned if the data type of stored value does not match the templated type.
    template <class T>
    ara::core::Result<T> GetValue(ara::core::StringView key) const noexcept;

    /// @brief Stores a key-value pair in this Key-Value Storage.
    ///
    /// If a value already exists and has the same data type as the new value, it is overwritten. If the new value has a
    /// different data type than the stored value, kDataTypeMismatch is returned.
    ///
    /// SetValue may be delayed by an ongoing call from another thread to RemoveAllKeys, SyncToStorage, or
    /// DiscardPendingChanges, or to SetValue, GetValue, RemoveKey, RecoverKey, or ResetKey for the same key-value pair.
    ///
    /// @traceid{SWS_PER_00046}@tracestatus{valid}
    /// @uptrace{RS_PER_00003}
    /// @uptrace{RS_PER_00010}
    /// @uptrace{RS_AP_00119}
    /// @uptrace{RS_AP_00120}
    /// @uptrace{RS_AP_00121}
    /// @uptrace{RS_AP_00127}
    /// @uptrace{RS_AP_00128}
    /// @uptrace{RS_AP_00129}
    /// @uptrace{RS_AP_00132}
    /// @threadsafety{re-entrant}
    /// @tparam T The type of the value that shall be set.
    /// @param[in] key The key to assign the value to.
    /// @param[in] value The value to store.
    /// @returns A Result of void. In case of an error, it contains any of the errors defined below, or a vendor
    ///          specific error.
    /// @error PerErrc::kIllegalWriteAccess Returned if the Key-Value Storage is configured as read-only.
    /// @error PerErrc::kPhysicalStorageFailure Returned if access to the storage fails.
    /// @error PerErrc::kIntegrityCorrupted Returned if stored data cannot be written because the structural integrity
    ///                                     is corrupted.
    /// @error PerErrc::kEncryptionFailed Returned if the encryption or decryption of stored data fails.
    /// @error PerErrc::kDataTypeMismatch Returned if the data type of an already stored value does not match the
    ///                                   templated type.
    /// @error PerErrc::kOutOfStorageSpace Returned if the available storage space is insufficient for the added/updated
    ///                                    value.
    template <class T>
    ara::core::Result<void> SetValue(ara::core::StringView key, const T& value) noexcept;

    /// @brief Removes a key and the associated value from this Key-Value Storage.
    ///
    /// RemoveKey may be delayed by an ongoing call from another thread to RemoveAllKeys, SyncToStorage, or
    /// DiscardPendingChanges, or to SetValue, GetValue, RemoveKey, RecoverKey, or ResetKey for the same key-value pair.
    ///
    /// @traceid{SWS_PER_00047}@tracestatus{valid}
    /// @uptrace{RS_PER_00003}
    /// @uptrace{RS_PER_00010}
    /// @uptrace{RS_AP_00119}
    /// @uptrace{RS_AP_00120}
    /// @uptrace{RS_AP_00121}
    /// @uptrace{RS_AP_00127}
    /// @uptrace{RS_AP_00128}
    /// @uptrace{RS_AP_00129}
    /// @uptrace{RS_AP_00132}
    /// @threadsafety{re-entrant}
    /// @param[in] key The key to be removed.
    /// @returns A Result of void. In case of an error, it contains any of the errors defined below, or a vendor
    ///          specific error.
    /// @error PerErrc::kKeyNotFound Returned if the provided key does not exist in the Key-Value Storage.
    /// @error PerErrc::kIllegalWriteAccess Returned if the Key-Value Storage is configured as read-only.
    /// @error PerErrc::kPhysicalStorageFailure Returned if access to the storage fails.
    /// @error PerErrc::kIntegrityCorrupted Returned if stored data cannot be written because the structural integrity
    ///                                     is corrupted.
    /// @error PerErrc::kEncryptionFailed Returned if the encryption or decryption of stored data fails.
    virtual ara::core::Result<void> RemoveKey(ara::core::StringView key) noexcept = 0;

    /// @brief Recovers a single key-value pair of this Key Value Storage.
    ///
    /// This method allows to recover a single key-value pair when the redundancy checks fail.
    ///
    /// This method does a best-effort recovery of the key-value pair. After recovery, the key-value pair might contain
    /// outdated or initial content, or might be lost.
    ///
    /// RecoverKey may be delayed by an ongoing call from another thread to RemoveAllKeys, SyncToStorage, or
    /// DiscardPendingChanges, or to SetValue, GetValue, RemoveKey, RecoverKey, or ResetKey for the same key-value pair.
    ///
    /// @traceid{SWS_PER_00427}@tracestatus{valid}
    /// @uptrace{RS_PER_00003}
    /// @uptrace{RS_PER_00009}
    /// @uptrace{RS_PER_00010}
    /// @uptrace{RS_AP_00119}
    /// @uptrace{RS_AP_00120}
    /// @uptrace{RS_AP_00121}
    /// @uptrace{RS_AP_00127}
    /// @uptrace{RS_AP_00128}
    /// @uptrace{RS_AP_00129}
    /// @uptrace{RS_AP_00132}
    /// @threadsafety{re-entrant}
    /// @param[in] key The key to be recovered.
    /// @returns A Result of void. In case of an error, it contains any of the errors defined below, or a vendor
    ///          specific error.
    /// @error PerErrc::kKeyNotFound Returned if the provided key does not exist in the Key-Value Storage.
    /// @error PerErrc::kPhysicalStorageFailure Returned if access to the storage fails.
    /// @error PerErrc::kIntegrityCorrupted Returned if stored data cannot be written because the structural integrity
    ///                                     is corrupted.
    /// @error PerErrc::kEncryptionFailed Returned if the encryption or decryption of stored data fails.
    /// @error PerErrc::kOutOfStorageSpace Returned if the available storage space is insufficient for the restored
    ///                                    value.
    virtual ara::core::Result<void> RecoverKey(ara::core::StringView key) noexcept = 0;

    /// @brief Resets a key of this Key-Value Storage to its initial value.
    ///
    /// ResetKey allows to reset a single key to its initial value. If the key is currently not available in the
    /// Key-Value Storage, it is re-created. Afterwards, the key-value pair will appear in both cases as if it was newly
    /// installed from the current manifest.
    ///
    /// ResetKey will fail with kInitValueNotAvailable when neither design nor deployment define an initial value for
    /// the key.
    ///
    /// ResetKey may be delayed by an ongoing call from another thread to RemoveAllKeys, SyncToStorage, or
    /// DiscardPendingChanges, or to SetValue, GetValue, RemoveKey, RecoverKey, or ResetKey for the same key-value pair.
    ///
    /// @traceid{SWS_PER_00426}@tracestatus{valid}
    /// @uptrace{RS_PER_00003}
    /// @uptrace{RS_PER_00009}
    /// @uptrace{RS_PER_00010}
    /// @uptrace{RS_AP_00119}
    /// @uptrace{RS_AP_00120}
    /// @uptrace{RS_AP_00121}
    /// @uptrace{RS_AP_00127}
    /// @uptrace{RS_AP_00128}
    /// @uptrace{RS_AP_00129}
    /// @uptrace{RS_AP_00132}
    /// @threadsafety{re-entrant}
    /// @param[in] key The key to be reset.
    /// @returns A Result of void. In case of an error, it contains any of the errors defined below, or a vendor
    ///          specific error.
    /// @error PerErrc::kIllegalWriteAccess Returned if the Key-Value Storage is configured as read-only.
    /// @error PerErrc::kPhysicalStorageFailure Returned if access to the storage fails.
    /// @error PerErrc::kIntegrityCorrupted Returned if stored data cannot be written because the structural integrity
    ///                                     is corrupted.
    /// @error PerErrc::kEncryptionFailed Returned if the encryption or decryption of stored data fails.
    /// @error PerErrc::kInitValueNotAvailable Returned if no intitial value was configured for this key.
    /// @error PerErrc::kOutOfStorageSpace Returned if the available storage space is insufficient for the restored
    ///                                    value.
    virtual ara::core::Result<void> ResetKey(ara::core::StringView key) noexcept = 0;

    /// @brief Removes all key-value pairs and associated values from this Key-Value Storage.
    ///
    /// RemoveAllKeys may be delayed by an ongoing call from another thread to RemoveAllKeys, SyncToStorage,
    /// DiscardPendingChanges, SetValue, GetValue, RemoveKey, RecoverKey, or ResetKey.
    ///
    /// @traceid{SWS_PER_00048}@tracestatus{valid}
    /// @uptrace{RS_PER_00003}
    /// @uptrace{RS_PER_00010}
    /// @uptrace{RS_AP_00119}
    /// @uptrace{RS_AP_00120}
    /// @uptrace{RS_AP_00127}
    /// @uptrace{RS_AP_00128}
    /// @uptrace{RS_AP_00129}
    /// @uptrace{RS_AP_00132}
    /// @threadsafety{re-entrant}
    /// @returns A Result of void. In case of an error, it contains any of the errors defined below, or a vendor
    ///          specific error.
    /// @error PerErrc::kIllegalWriteAccess Returned if the Key-Value Storage is configured as read-only.
    /// @error PerErrc::kPhysicalStorageFailure Returned if access to the storage fails.
    /// @error PerErrc::kIntegrityCorrupted Returned if stored data cannot be written because the structural integrity
    ///                                     is corrupted.
    /// @error PerErrc::kEncryptionFailed Returned if the encryption or decryption of stored data fails.
    virtual ara::core::Result<void> RemoveAllKeys() noexcept = 0;

    /// @brief Triggers flushing of changed key-value pairs of the Key-Value Storage to the physical storage.
    ///
    /// SyncToStorage may be delayed by an ongoing call from another thread to RemoveAllKeys, DiscardPendingChanges,
    /// SetValue, RemoveKey, RecoverKey, or ResetKey.
    ///
    /// @traceid{SWS_PER_00049}@tracestatus{valid}
    /// @uptrace{RS_PER_00002}
    /// @uptrace{RS_AP_00119}
    /// @uptrace{RS_AP_00120}
    /// @uptrace{RS_AP_00127}
    /// @uptrace{RS_AP_00128}
    /// @uptrace{RS_AP_00129}
    /// @uptrace{RS_AP_00132}
    /// @threadsafety{re-entrant}
    /// @returns A Result of void. In case of an error, it contains any of the errors defined below, or a vendor
    ///          specific error.
    /// @error PerErrc::kIllegalWriteAccess Returned if the Key-Value Storage is configured as read-only.
    /// @error PerErrc::kPhysicalStorageFailure Returned if access to the storage fails.
    /// @error PerErrc::kIntegrityCorrupted Returned if stored data cannot be written because the structural integrity
    ///                                     is corrupted.
    /// @error PerErrc::kEncryptionFailed Returned if the encryption of stored data fails.
    /// @error PerErrc::kOutOfStorageSpace Returned if the available storage space is insufficient for the added/updated
    /// values.
    virtual ara::core::Result<void> SyncToStorage() noexcept = 0;

    /// @brief Removes all pending changes to this Key-Value Storage since the last call to SyncToStorage() or since
    /// this Key-Value Storage was opened using OpenKeyValueStorage().
    ///
    /// DiscardPendingChanges may be delayed by an ongoing call from another thread to RemoveAllKeys, SyncToStorage,
    /// DiscardPendingChanges, SetValue, GetValue, RemoveKey, RecoverKey, or ResetKey.
    ///
    /// @traceid{SWS_PER_00365}@tracestatus{valid}
    /// @uptrace{RS_PER_00002}
    /// @uptrace{RS_AP_00119}
    /// @uptrace{RS_AP_00120}
    /// @uptrace{RS_AP_00127}
    /// @uptrace{RS_AP_00128}
    /// @uptrace{RS_AP_00129}
    /// @uptrace{RS_AP_00132}
    /// @threadsafety{re-entrant}
    /// @returns A Result of void. In case of an error, it contains any of the errors defined below, or a vendor
    ///          specific error.
    /// @error PerErrc::kPhysicalStorageFailure Returned if access to the storage fails.
    /// @error PerErrc::kIntegrityCorrupted Returned if stored data cannot be read because the structural integrity is
    ///                                     corrupted.
    /// @error PerErrc::kValidationFailed Returned if the validity of stored data cannot be ensured.
    /// @error PerErrc::kEncryptionFailed Returned if the decryption of stored data fails.
    virtual ara::core::Result<void> DiscardPendingChanges() noexcept = 0;
   /// @brief FetchValueFromRamtable
    ///
    /// @param key key position where the value should be located
    /// @param kvs_type bits that defines the type
    /// @return correct value corresponding to key or error
    ///
    virtual ara::core::Result<ara::core::Vector<uint8_t>> FetchValueFromRamtable(ara::core::StringView,
                                                                                 uint16_t&) const noexcept = 0;

    /// @brief SetValueToRamtable
    ///
    /// @param key key position where the value should be located
    /// @param value value to set
    /// @param kvs_type bits that defines the type
    /// @return result of operation
    ///
    virtual void SetValueToRamtable(ara::core::StringView, const ara::core::Vector<uint8_t>&, uint16_t&) noexcept = 0;
};

/// @brief Opens a Key-Value Storage.
///
/// OpenKeyValueStorage will fail with kResourceBusy when the Key-Value Storage is currently being modified by a call
/// from another thread to UpdatePersistency, ResetPersistency, RecoverKeyValueStorage, or ResetKeyValueStorage.
///
/// Because multiple threads can access the same Key-Value Storage concurrently, the Key-Value Storage might not be
/// closed when the SharedHandle returned by this function goes out of scope. It will only be closed when all
/// SharedHandles that refer to the same Key-Value Storage went out of scope.
///
/// @traceid{SWS_PER_00052}@tracestatus{valid}
/// @uptrace{RS_PER_00003}
/// @uptrace{RS_PER_00010}
/// @uptrace{RS_AP_00119}
/// @uptrace{RS_AP_00120}
/// @uptrace{RS_AP_00121}
/// @uptrace{RS_AP_00127}
/// @uptrace{RS_AP_00128}
/// @uptrace{RS_AP_00129}
/// @uptrace{RS_AP_00132}
/// @uptrace{RS_AP_00144}
/// @threadsafety{re-entrant}
/// @param[in] kvs The shortName path of a PortPrototype typed by a PersistencyKeyValueStorageInterface.
/// @returns A Result containing a SharedHandle for the KeyValueStorage. In case of an error, it contains any of the
///          errors defined below, or a vendor specific error.
/// @error PerErrc::kStorageNotFound Returned if the passed InstanceSpecifier does not match any
///                                  PersistencyKeyValueStorageInterface configured for this Executable.
/// @error PerErrc::kPhysicalStorageFailure Returned if access to the storage fails.
/// @error PerErrc::kIntegrityCorrupted Returned if stored data cannot be read because the structural integrity is
///                                     corrupted.
/// @error PerErrc::kValidationFailed Returned if the validity of stored data cannot be ensured.
/// @error PerErrc::kEncryptionFailed Returned if the decryption of stored data fails.
/// @error PerErrc::kResourceBusy Returned if UpdatePersistency or ResetPersistency is currently being executed, or if
///                               RecoverKeyValueStorage or ResetKeyValueStorage is currently being executed for the
///                               same Key-Value Storage.
/// @error PerErrc::kOutOfStorageSpace Returned if the available storage space is insufficient for the added/updated values.
/// @verbatim embed:rst:leading-slashes
/// .. uml:: ../../../../source/ara/per/docs/AraPer_OpenKeyValueStorage_AD.puml
/// @endverbatim
ara::core::Result<SharedHandle<KeyValueStorage>> OpenKeyValueStorage(const ara::core::InstanceSpecifier& kvs) noexcept;

/// @brief Recovers a Key-ValueStorage.
///
/// RecoverKeyValueStorage allows to recover a Key-Value Storage when the redundancy checks fail.
///
/// It will fail with kResourceBusy when the Key-Value Storage is currently open, or when it is modified by a call from
/// another thread to UpdatePersistency, ResetPersistency, RecoverKeyValueStorage, or ResetKeyValueStorage.
///
/// This method does a best-effort recovery of all key-value pairs. After recovery, keys might show outdated or initial
/// value, or might be lost.
///
/// @traceid{SWS_PER_00333}@tracestatus{valid}
/// @uptrace{RS_PER_00003}
/// @uptrace{RS_PER_00009}
/// @uptrace{RS_PER_00010}
/// @uptrace{RS_AP_00119}
/// @uptrace{RS_AP_00120}
/// @uptrace{RS_AP_00121}
/// @uptrace{RS_AP_00127}
/// @uptrace{RS_AP_00128}
/// @uptrace{RS_AP_00129}
/// @uptrace{RS_AP_00132}
/// @threadsafety{re-entrant}
/// @param[in] kvs The shortName path of a PortPrototype typed by a PersistencyKeyValueStorageInterface.
/// @returns A Result of void. In case of an error, it contains any of the errors defined below, or a vendor specific
///          error.
/// @error PerErrc::kStorageNotFound Returned if the passed InstanceSpecifier does not match any
///                                  PersistencyKeyValueStorageInterface configured for this Executable.
/// @error PerErrc::kPhysicalStorageFailure Returned if access to the storage fails.
/// @error PerErrc::kEncryptionFailed Returned if the encryption of stored data fails.
/// @error PerErrc::kResourceBusy Returned if UpdatePersistency or ResetPersistency is currently being executed, or if
///                               ResetKeyValueStorage is currently being executed for the same Key-Value Storage, or a
///                               SharedHandle of the same Key-Value Storage is currently in use.
/// @error PerErrc::kOutOfStorageSpace Returned if the available storage space is insufficient for the added/updated
///                                    values.
ara::core::Result<void> RecoverKeyValueStorage(const ara::core::InstanceSpecifier& kvs) noexcept;

/// @brief Resets a Key-Value Storage to the initial state.
///
/// ResetKeyValueStorage allows to reset a Key-Value Storage to the initial state, containing only key-value pairs which
/// were deployed from the manifest, with their initial values. Afterwards, the Key-Value Storage will appear as if it
/// was newly installed from the current manifest.
///
/// It will fail with kResourceBusy when the Key-Value Storage is currently open, or when it is modified by a call from
/// another thread to UpdatePersistency, ResetPersistency, RecoverKeyValueStorage, or ResetKeyValueStorage.
///
/// @traceid{SWS_PER_00334}@tracestatus{valid}
/// @uptrace{RS_PER_00003}
/// @uptrace{RS_PER_00009}
/// @uptrace{RS_PER_00010}
/// @uptrace{RS_AP_00119}
/// @uptrace{RS_AP_00120}
/// @uptrace{RS_AP_00121}
/// @uptrace{RS_AP_00127}
/// @uptrace{RS_AP_00128}
/// @uptrace{RS_AP_00129}
/// @uptrace{RS_AP_00132}
/// @threadsafety{re-entrant}
/// @param[in] kvs The shortName path of a PortPrototype typed by a PersistencyKeyValueStorageInterface.
/// @returns A Result of void. In case of an error, it contains any of the errors defined below, or a vendor specific
///          error.
/// @error PerErrc::kStorageNotFound Returned if the passed InstanceSpecifier does not match any
///                                  PersistencyKeyValueStorageInterface configured for this Executable.
/// @error PerErrc::kPhysicalStorageFailure Returned if access to the storage fails.
/// @error PerErrc::kEncryptionFailed Returned if the encryption of stored data fails.
/// @error PerErrc::kResourceBusy Returned if UpdatePersistency or ResetPersistency is currently being executed, or if
///                               RecoverKeyValueStorage is currently being executed for the same Key-Value Storage, or
///                               a SharedHandle of the same Key-Value Storage is currently in use.
/// @error PerErrc::kOutOfStorageSpace Returned if the available storage space is insufficient for the added/updated
///                                    values.
/// @verbatim embed:rst:leading-slashes
/// .. uml:: ../../../../source/ara/per/docs/AraPer_ResetKeyValueStorage_AD.puml
/// @endverbatim
ara::core::Result<void> ResetKeyValueStorage(const ara::core::InstanceSpecifier& kvs) noexcept;

/// @brief Returns the space in bytes currently occupied by a Key-Value Storage.
///
/// The returned size includes all meta data and the space used for redundancy and backups.
///
/// The returned size is only accurate if no other operation on the Key-Value Storage takes place at the same time.
///
/// @traceid{SWS_PER_00405}@tracestatus{valid}
/// @uptrace{RS_PER_00017}
/// @uptrace{RS_AP_00119}
/// @uptrace{RS_AP_00120}
/// @uptrace{RS_AP_00121}
/// @uptrace{RS_AP_00127}
/// @uptrace{RS_AP_00128}
/// @uptrace{RS_AP_00129}
/// @uptrace{RS_AP_00132}
/// @threadsafety{re-entrant}
/// @param[in] kvs The shortName path of a PortPrototype typed by a PersistencyKeyValueStorageInterface.
/// @returns A Result containing the occupied space in bytes. In case of an error, it contains any of the errors defined
///          below, or a vendor specific error.
/// @error PerErrc::kStorageNotFound Returned if the passed InstanceSpecifier does not match any
///                                  PersistencyKeyValueStorageInterface configured for this Executable.
/// @error PerErrc::kPhysicalStorageFailure Returned if access to the storage fails.
ara::core::Result<std::uint64_t> GetCurrentKeyValueStorageSize(const ara::core::InstanceSpecifier& kvs) noexcept;

}  // namespace per
}  // namespace ara

#endif  // ARA_PER_KEY_VALUE_STORAGE_H_
