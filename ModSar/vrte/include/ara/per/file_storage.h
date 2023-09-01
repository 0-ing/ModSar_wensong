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

#ifndef ARA_PER_FILE_STORAGE_H_
#define ARA_PER_FILE_STORAGE_H_

#include "ara/core/instance_specifier.h"
#include "ara/core/result.h"
#include "ara/core/string.h"
#include "ara/core/vector.h"

#include "ara/per/per_error_domain.h"
#include "ara/per/read_accessor.h"
#include "ara/per/read_write_accessor.h"
#include "ara/per/shared_handle.h"
#include "ara/per/unique_handle.h"

namespace ara
{
namespace per
{

/// @brief This enumeration describes how and when a file was created.
///
/// @traceid{SWS_PER_00435}@tracestatus{valid}
/// @uptrace{RS_PER_00004}
/// @uptrace{RS_AP_00122}
enum class FileCreationState : std::uint32_t
{
    /// The file was created by Persistency after installation of the application or after ResetPersistency.
    kCreatedDuringInstallion = 1,
    /// The file was created by Persistency during an update.
    kCreatedDuringUpdate = 2,
    /// The file was re-created due to a call to ResetFile or ResetAllFiles.
    kCreatedDuringReset = 3,
    /// The file was re-created by Persistency after a corruption was detected.
    kCreatedDuringRecovery = 4,
    /// The file was created by the application.
    kCreatedByApplication = 5
};

/// @brief This enumeration describes how and when a file was last modified.
///
/// @traceid{SWS_PER_00436}@tracestatus{valid}
/// @uptrace{RS_PER_00004}
/// @uptrace{RS_AP_00122}
enum class FileModificationState : std::uint32_t
{
    /// The file was last modified by Persistency during an update.
    kModifiedDuringUpdate = 2,
    /// The file was last modified by Persistency due to a call to ResetFile or ResetAllFiles.
    kModifiedDuringReset = 3,
    /// The file was last modified by Persistency after a corruption was detected.
    kModifiedDuringRecovery = 4,
    /// The file was last modified by the application.
    kModifiedByApplication = 5
};

/// @brief This structure contains additional information on a file returned by GetFileInfo.
///
/// @traceid{SWS_PER_00437}@tracestatus{valid}
/// @uptrace{RS_PER_00004}
/// @uptrace{RS_AP_00122}
struct FileInfo
{
    /// @brief Time in nanoseconds since midnight 1970-01-01 UTC at which the file was created.
    ///
    /// @traceid{SWS_PER_00441}@tracestatus{valid}
    /// @uptrace{RS_PER_00004}
    std::uint64_t creationTime;

    /// @brief Time in nanoseconds since midnight 1970-01-01 UTC at which the file was last modified.
    ///
    /// @traceid{SWS_PER_00442}@tracestatus{valid}
    /// @uptrace{RS_PER_00004}
    std::uint64_t modificationTime;

    /// @brief Time in nanoseconds since midnight 1970-01-01 UTC at which the file was last accessed.
    ///
    /// @traceid{SWS_PER_00443}@tracestatus{valid}
    /// @uptrace{RS_PER_00004}
    std::uint64_t accessTime;

    /// @brief Information on how and by whom the file was created.
    ///
    /// @traceid{SWS_PER_00444}@tracestatus{valid}
    /// @uptrace{RS_PER_00004}
    FileCreationState fileCreationState;

    /// @brief Information on how and by whom the file was last modified.
    ///
    /// @traceid{SWS_PER_00445}@tracestatus{valid}
    /// @uptrace{RS_PER_00004}
    FileModificationState fileModificationState;
};

/// @brief This enumeration defines how a file shall be opened.
///
/// The values can be combined (using | and |=) as long as they do not contradict each other.
///
/// @traceid{SWS_PER_00147}@tracestatus{valid}
/// @uptrace{RS_PER_00003}
/// @uptrace{RS_AP_00122}
enum class OpenMode : std::uint32_t {
    /// Sets the seek position to the beginning of the file when the file is opened. This mode cannot be combined
    /// with kAtTheEnd.
    kAtTheBeginning = 1 << 0, 
    /// Sets the seek position to the end of the file when the file is opened. This mode cannot be combined with
    /// kAtTheBeginning or kTruncate.
    kAtTheEnd = 1 << 1,
    /// Removes existing content when the file is opened. This mode cannot be combined with kAtTheEnd.
    kTruncate = 1 << 2,
    /// Append to the end. Always seeks to the end of the file before writing.
    kAppend = 1 << 3
};

/// @brief Merges two OpenMode modifiers into one.
///
/// @traceid{SWS_PER_00144}@tracestatus{valid}
/// @uptrace{RS_PER_00001}
/// @uptrace{RS_PER_00004}
/// @uptrace{RS_AP_00119}
/// @uptrace{RS_AP_00120}
/// @uptrace{RS_AP_00121}
/// @threadsafety{re-entrant}
/// @param[in] left First OpenMode modifiers.
/// @param[in] right Second OpenMode modifiers.
/// @returns returns Merged OpenMode modifiers.
constexpr OpenMode operator|(OpenMode left, OpenMode right);

/// @brief Merges an OpenMode modifier into this OpenMode.
///
/// @traceid{SWS_PER_00434}@tracestatus{valid}
/// @uptrace{RS_PER_00001}
/// @uptrace{RS_PER_00004}
/// @uptrace{RS_AP_00119}
/// @uptrace{RS_AP_00120}
/// @uptrace{RS_AP_00121}
/// @threadsafety{re-entrant}
/// @param[in] left Left OpenMode modifiers.
/// @param[in] right Right OpenMode modifiers.
/// @returns returns The modified OpenMode.
OpenMode& operator|=(OpenMode& left, const OpenMode& right);

/// @brief The File Storage contains a set of files identified by their file names.
///
/// @traceid{SWS_PER_00340}@tracestatus{valid}
/// @uptrace{RS_PER_00004}
/// @uptrace{RS_AP_00122}
/// @uptrace{RS_AP_00146}
/// @warning "final" Keyword was removed because current implementation inherits from the FileStorage class
class FileStorage // final
{
public:
    /// @brief The default constructor for FileStorage shall not be used.
    ///
    /// @traceid{SWS_PER_00460}@tracestatus{draft}
    /// @uptrace{RS_PER_00004}
    /// @uptrace{RS_AP_00120}
    /// @uptrace{RS_AP_00129}
    /// @uptrace{RS_AP_00146}
    FileStorage() = default;

    /// @brief The move constructor for FileStorage shall not be used.
    ///
    /// @traceid{SWS_PER_00326}@tracestatus{valid}
    /// @uptrace{RS_PER_00004}
    /// @uptrace{RS_AP_00120}
    /// @uptrace{RS_AP_00121}
    /// @uptrace{RS_AP_00129}
    /// @uptrace{RS_AP_00132}
    FileStorage(FileStorage&& fs) = delete;

    /// @brief The move assignment operator for FileStorage shall not be used.
    ///
    /// @traceid{SWS_PER_00327}@tracestatus{valid}
    /// @uptrace{RS_PER_00004}
    /// @uptrace{RS_AP_00119}
    /// @uptrace{RS_AP_00120}
    /// @uptrace{RS_AP_00121}
    /// @uptrace{RS_AP_00132}
    FileStorage& operator=(FileStorage&& fs) & = delete;

    /// @brief The copy constructor for FileStorage shall not be used.
    ///
    /// @traceid{SWS_PER_00328}@tracestatus{valid}
    /// @uptrace{RS_PER_00004}
    /// @uptrace{RS_AP_00120}
    FileStorage(const FileStorage&) = delete;

    /// @brief The copy assignment operator for FileStorage shall not be used.
    ///
    /// @traceid{SWS_PER_00329}@tracestatus{valid}
    /// @uptrace{RS_PER_00004}
    /// @uptrace{RS_AP_00119}
    /// @uptrace{RS_AP_00120}
    FileStorage& operator=(const FileStorage&) = delete;

    /// @brief Destructor for FileStorage.
    ///
    /// @traceid{SWS_PER_00330}@tracestatus{valid}
    /// @uptrace{RS_PER_00004}
    /// @uptrace{RS_AP_00120}
    /// @uptrace{RS_AP_00129}
    /// @uptrace{RS_AP_00132}
    /// @uptrace{RS_AP_00134}
    /// @threadsafety{no}
    virtual ~FileStorage() noexcept = default;

    /// @brief Returns a list of all currently available file names of this File Storage.
    ///
    /// The list of file names is only accurate if no file is added or deleted at the same time.
    ///
    /// @traceid{SWS_PER_00110}@tracestatus{valid}
    /// @uptrace{RS_PER_00001}
    /// @uptrace{RS_PER_00004}
    /// @uptrace{RS_AP_00119}
    /// @uptrace{RS_AP_00120}
    /// @uptrace{RS_AP_00127}
    /// @uptrace{RS_AP_00129}
    /// @uptrace{RS_AP_00132}
    /// @threadsafety{re-entrant}
    /// @returns A Result containing a list of available file names. In case of an error, it contains any of the errors
    ///          defined below, or a vendor specific error.
    /// @error PerErrc::kPhysicalStorageFailure Returned if access to the storage fails.
    /// @error PerErrc::kIntegrityCorrupted Returned if stored data cannot be read because the structural integrity is
    ///                                     corrupted.
    /// @error PerErrc::kValidationFailed Returned if the validity of stored data cannot be ensured.
    /// @error PerErrc::kEncryptionFailed Returned if the decryption of stored data fails.
    virtual ara::core::Result<ara::core::Vector<ara::core::String>> GetAllFileNames() const noexcept = 0;

    /// @brief Checks if a file exists in this File Storage.
    ///
    /// The result is only accurate if no file is added or deleted at the same time. E.g. when a file is removed in
    /// another thread directly after this function returned "true", the result is not valid anymore.
    ///
    /// @traceid{SWS_PER_00112}@tracestatus{valid}
    /// @uptrace{RS_PER_00001}
    /// @uptrace{RS_PER_00004}
    /// @uptrace{RS_AP_00119}
    /// @uptrace{RS_AP_00120}
    /// @uptrace{RS_AP_00121}
    /// @uptrace{RS_AP_00127}
    /// @uptrace{RS_AP_00132}
    /// @threadsafety{re-entrant}
    /// @param[in] fileName File name of the file. May correspond to the PersistencyFile.fileName of a configured file.
    /// @returns A Result containing true if the file could be located or false if it couldn't. In case of an error, it
    ///          contains any of the errors defined below, or a vendor specific error.
    /// @error PerErrc::kPhysicalStorageFailure Returned if access to the storage fails.
    /// @error PerErrc::kIntegrityCorrupted Returned if stored data cannot be read because the structural integrity is
    ///                                     corrupted.
    /// @error PerErrc::kValidationFailed Returned if the validity of stored data cannot be ensured.
    /// @error PerErrc::kEncryptionFailed Returned if the decryption of stored data fails.
    virtual ara::core::Result<bool> FileExists(ara::core::StringView fileName) const noexcept = 0;

    /// @brief Opens a file of this File Storage for reading and writing.
    ///
    /// The file is opened with the seek position set to the beginning (corresponding to kAtTheBeginning).
    ///
    /// If the file does not exist, it is created.
    ///
    /// The file will be closed when the returned UniqueHandle goes out of scope.
    ///
    /// @traceid{SWS_PER_00375}@tracestatus{valid}
    /// @uptrace{RS_PER_00001}
    /// @uptrace{RS_PER_00004}
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
    /// @param[in] fileName File name of the file. May correspond to the PersistencyFile.fileName of a configured file.
    /// @returns A Result containing a UniqueHandle for the file. In case of an error, it contains any of the errors
    ///          defined below, or a vendor specific error.
    /// @error PerErrc::kIllegalWriteAccess Returned if the File Storage is configured as read-only.
    /// @error PerErrc::kPhysicalStorageFailure Returned if access to the storage fails.
    /// @error PerErrc::kIntegrityCorrupted Returned if stored data cannot be read because the structural integrity is
    ///                                     corrupted.
    /// @error PerErrc::kValidationFailed Returned if the validity of stored data cannot be ensured.
    /// @error PerErrc::kEncryptionFailed Returned if the decryption of stored data fails.
    /// @error PerErrc::kResourceBusy Returned if the file is already open, or if DeleteFile, RecoverFile, or ResetFile
    ///                               with the same file name is currently being executed.
    /// @error PerErrc::kOutOfStorageSpace Returned if the available storage space is insufficient or the number of
    ///                                    files would get larger than the configured maxNumberOfFiles when the file is
    ///                                    created.
    virtual ara::core::Result<UniqueHandle<ReadWriteAccessor>> OpenFileReadWrite(ara::core::StringView fileName) noexcept = 0;

    /// @brief Opens a file of this File Storage for reading and writing with a defined mode.
    ///
    /// If not otherwise specified by the provided mode, the file is opened with the seek position set to the beginning
    /// (corresponding to kAtTheBeginning).
    ///
    /// If the file does not exist, it is created.
    ///
    /// The file will be closed when the returned UniqueHandle goes out of scope.
    ///
    /// @traceid{SWS_PER_00113}@tracestatus{valid}
    /// @uptrace{RS_PER_00001}
    /// @uptrace{RS_PER_00004}
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
    /// @param[in] fileName File name of the file. May correspond to the PersistencyFile.fileName of a configured file.
    /// @param[in] mode Mode with which the file shall be opened.
    /// @returns A Result containing a UniqueHandle for the file. In case of an error, it contains any of the errors
    ///          defined below, or a vendor specific error.
    /// @error PerErrc::kIllegalWriteAccess Returned if the File Storage is configured as read-only.
    /// @error PerErrc::kPhysicalStorageFailure Returned if access to the storage fails.
    /// @error PerErrc::kIntegrityCorrupted Returned if stored data cannot be read because the structural integrity is
    ///                                     corrupted.
    /// @error PerErrc::kValidationFailed Returned if the validity of stored data cannot be ensured.
    /// @error PerErrc::kEncryptionFailed Returned if the decryption of stored data fails.
    /// @error PerErrc::kResourceBusy Returned if the file is already open, or if DeleteFile, RecoverFile, or ResetFile
    ///                               with the same file name is currently being executed.
    /// @error PerErrc::kOutOfStorageSpace Returned if the available storage space is insufficient or the number of
    ///                                    files would get larger than the configured maxNumberOfFiles when the file is
    ///                                    created.
    /// @error PerErrc::kInvalidOpenMode Returned if the passed mode contains an invalid combination of modes.
    virtual ara::core::Result<UniqueHandle<ReadWriteAccessor>> OpenFileReadWrite(ara::core::StringView fileName,
        OpenMode mode) noexcept = 0;

    /// @brief Opens a file of this File Storage for reading and writing with a user provided buffer.
    ///
    /// If not otherwise specified by the provided mode, the file is opened with the seek position set to the beginning
    /// (corresponding to kAtTheBeginning).
    ///
    /// The provided buffer will be used by the ReadWriteAccessor to implement block-wise reading and writing to speed
    /// up multiple small accesses to the file.
    ///
    /// If the file does not exist, it is created.
    ///
    /// The file will be closed when the returned UniqueHandle goes out of scope.
    ///
    /// @traceid{SWS_PER_00429}@tracestatus{valid}
    /// @uptrace{RS_PER_00001}
    /// @uptrace{RS_PER_00004}
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
    /// @param[in] fileName File name of the file. May correspond to the PersistencyFile.fileName of a configured file.
    /// @param[in] mode Mode with which the file shall be opened.
    /// @param[in] buffer Memory to be used for block-wise reading/writing.
    /// @returns A Result containing a UniqueHandle for the file. In case of an error, it contains any of the errors
    ///          defined below, or a vendor specific error.
    /// @error PerErrc::kIllegalWriteAccess Returned if the File Storage is configured as read-only.
    /// @error PerErrc::kPhysicalStorageFailure Returned if access to the storage fails.
    /// @error PerErrc::kIntegrityCorrupted Returned if stored data cannot be read because the structural integrity is
    ///                                     corrupted.
    /// @error PerErrc::kValidationFailed Returned if the validity of stored data cannot be ensured.
    /// @error PerErrc::kEncryptionFailed Returned if the decryption of stored data fails.
    /// @error PerErrc::kResourceBusy Returned if the file is already open, or if DeleteFile, RecoverFile, or ResetFile
    ///                               with the same file name is currently being executed.
    /// @error PerErrc::kOutOfStorageSpace Returned if the available storage space is insufficient or the number of
    ///                                    files would get larger than the configured maxNumberOfFiles when the file is
    ///                                    created.
    /// @error PerErrc::kInvalidOpenMode Returned if the passed mode contains an invalid combination of modes.
    virtual ara::core::Result<UniqueHandle<ReadWriteAccessor>> OpenFileReadWrite(ara::core::StringView fileName,
        OpenMode mode, ara::core::Span<ara::core::Byte> buffer) noexcept = 0;

    /// @brief Opens a file of this File Storage for reading.
    ///
    /// The file is opened with the seek position set to the beginning (corresponding to kAtTheBeginning).
    ///
    /// The file will be closed when the returned UniqueHandle goes out of scope.
    ///
    /// @traceid{SWS_PER_00376}@tracestatus{valid}
    /// @uptrace{RS_PER_00001}
    /// @uptrace{RS_PER_00004}
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
    /// @param[in] fileName File name of the file. May correspond to the PersistencyFile.fileName of a configured file.
    /// @returns A Result containing a UniqueHandle for the file. In case of an error, it contains any of the errors
    ///          defined below, or a vendor specific error.
    /// @error PerErrc::kPhysicalStorageFailure Returned if access to the storage fails.
    /// @error PerErrc::kIntegrityCorrupted Returned if stored data cannot be read because the structural integrity is
    ///                                     corrupted.
    /// @error PerErrc::kValidationFailed Returned if the validity of stored data cannot be ensured.
    /// @error PerErrc::kEncryptionFailed Returned if the decryption of stored data fails.
    /// @error PerErrc::kResourceBusy Returned if the file is already open, or if DeleteFile, RecoverFile, or ResetFile
    ///                               with the same file name is currently being executed.
    /// @error PerErrc::kFileNotFound Returned if the provided file does not exist in the File Storage.
    virtual ara::core::Result<UniqueHandle<ReadAccessor>> OpenFileReadOnly(ara::core::StringView fileName) noexcept = 0;

    /// @brief Opens a file of this File Storage for reading with a defined mode.
    ///
    /// If not otherwise specified by the provided mode, the file is opened with the seek position set to the beginning
    /// (corresponding to kAtTheBeginning).
    ///
    /// The file will be closed when the returned UniqueHandle goes out of scope.
    ///
    /// @traceid{SWS_PER_00114}@tracestatus{valid}
    /// @uptrace{RS_PER_00001}
    /// @uptrace{RS_PER_00004}
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
    /// @param[in] fileName File name of the file. May correspond to the PersistencyFile.fileName of a configured file.
    /// @param[in] mode Mode with which the file shall be opened.
    /// @returns A Result containing a UniqueHandle for the file. In case of an error, it contains any of the errors
    ///          defined below, or a vendor specific error.
    /// @error PerErrc::kPhysicalStorageFailure Returned if access to the storage fails.
    /// @error PerErrc::kIntegrityCorrupted Returned if stored data cannot be read because the structural integrity is
    ///                                     corrupted.
    /// @error PerErrc::kValidationFailed Returned if the validity of stored data cannot be ensured.
    /// @error PerErrc::kEncryptionFailed Returned if the decryption of stored data fails.
    /// @error PerErrc::kResourceBusy Returned if the file is already open, or if DeleteFile, RecoverFile, or ResetFile
    ///                               with the same file name is currently being executed.
    /// @error PerErrc::kFileNotFound Returned if the provided file does not exist in the File Storage.
    /// @error PerErrc::kInvalidOpenMode Returned if the passed mode contains an invalid combination of modes.
    virtual ara::core::Result<UniqueHandle<ReadAccessor>> OpenFileReadOnly(ara::core::StringView fileName,
        OpenMode mode) noexcept = 0;

    /// @brief Opens a file of this File Storage for reading with a user provided buffer.
    ///
    /// If not otherwise specified by the provided mode, the file is opened with the seek position set to the beginning
    /// (corresponding to kAtTheBeginning).
    ///
    /// The provided buffer will be used by the ReadAccessor to implement block-wise reading to speed up multiple small
    /// accesses to the file.
    ///
    /// The file will be closed when the returned UniqueHandle goes out of scope.
    ///
    /// @traceid{SWS_PER_00430}@tracestatus{valid}
    /// @uptrace{RS_PER_00001}
    /// @uptrace{RS_PER_00004}
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
    /// @param[in] fileName File name of the file. May correspond to the PersistencyFile.fileName of a configured file.
    /// @param[in] mode Mode with which the file shall be opened.
    /// @param[in] buffer Memory to be used for block-wise reading.
    /// @returns A Result containing a UniqueHandle for the file. In case of an error, it contains any of the errors
    ///          defined below, or a vendor specific error.
    /// @error PerErrc::kPhysicalStorageFailure Returned if access to the storage fails.
    /// @error PerErrc::kIntegrityCorrupted Returned if stored data cannot be read because the structural integrity is
    ///                                     corrupted.
    /// @error PerErrc::kValidationFailed Returned if the validity of stored data cannot be ensured.
    /// @error PerErrc::kEncryptionFailed Returned if the decryption of stored data fails.
    /// @error PerErrc::kResourceBusy Returned if the file is already open, or if DeleteFile, RecoverFile, or ResetFile
    ///                               with the same file name is currently being executed.
    /// @error PerErrc::kFileNotFound Returned if the provided file does not exist in the File Storage.
    /// @error PerErrc::kInvalidOpenMode Returned if the passed mode contains an invalid combination of modes.
    virtual ara::core::Result<UniqueHandle<ReadAccessor>> OpenFileReadOnly(ara::core::StringView fileName,
        OpenMode mode, ara::core::Span<ara::core::Byte> buffer) noexcept = 0;

    /// @brief Opens a file of this File Storage for writing.
    ///
    /// The file is truncated (corresponding to kTruncate).
    ///
    /// If the file does not exist, it is created.
    ///
    /// The file will be closed when the returned UniqueHandle goes out of scope.
    ///
    /// @traceid{SWS_PER_00377}@tracestatus{valid}
    /// @uptrace{RS_PER_00001}
    /// @uptrace{RS_PER_00004}
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
    /// @param[in] fileName File name of the file. May correspond to the PersistencyFile.fileName of a configured file.
    /// @returns A Result containing a UniqueHandle for the file. In case of an error, it contains any of the errors
    ///          defined below, or a vendor specific error.
    /// @error PerErrc::kIllegalWriteAccess Returned if the File Storage is configured as read-only.
    /// @error PerErrc::kPhysicalStorageFailure Returned if access to the storage fails.
    /// @error PerErrc::kIntegrityCorrupted Returned if stored data cannot be read because the structural integrity is
    ///                                     corrupted.
    /// @error PerErrc::kValidationFailed Returned if the validity of stored data cannot be ensured.
    /// @error PerErrc::kEncryptionFailed Returned if the decryption of stored data fails.
    /// @error PerErrc::kResourceBusy Returned if the file is already open, or if DeleteFile, RecoverFile, or ResetFile
    ///                               with the same file name is currently being executed.
    /// @error PerErrc::kOutOfStorageSpace Returned if the available storage space is insufficient or the number of
    ///                                    files would get larger than the configured maxNumberOfFiles when the file is
    ///                                    created.
    virtual ara::core::Result<UniqueHandle<ReadWriteAccessor>> OpenFileWriteOnly(ara::core::StringView fileName) noexcept = 0;

    /// @brief Opens a file of this File Storage for writing with a defined mode.
    ///
    /// If not otherwise specified by the provided mode, the file is truncated (corresponding to kTruncate).
    ///
    /// If the file does not exist, it is created.
    ///
    /// The file will be closed when the returned UniqueHandle goes out of scope.
    ///
    /// @traceid{SWS_PER_00115}@tracestatus{valid}
    /// @uptrace{RS_PER_00001}
    /// @uptrace{RS_PER_00004}
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
    /// @param[in] fileName File name of the file. May correspond to the PersistencyFile.fileName of a configured file.
    /// @param[in] mode Mode with which the file shall be opened.
    /// @returns A Result containing a UniqueHandle for the file. In case of an error, it contains any of the errors
    ///          defined below, or a vendor specific error.
    /// @error PerErrc::kIllegalWriteAccess Returned if the File Storage is configured as read-only.
    /// @error PerErrc::kPhysicalStorageFailure Returned if access to the storage fails.
    /// @error PerErrc::kIntegrityCorrupted Returned if stored data cannot be read because the structural integrity is
    ///                                     corrupted.
    /// @error PerErrc::kValidationFailed Returned if the validity of stored data cannot be ensured.
    /// @error PerErrc::kEncryptionFailed Returned if the decryption of stored data fails.
    /// @error PerErrc::kResourceBusy Returned if the file is already open, or if DeleteFile, RecoverFile, or ResetFile
    ///                               with the same file name is currently being executed.
    /// @error PerErrc::kOutOfStorageSpace Returned if the available storage space is insufficient or the number of
    ///                                    files would get larger than the configured maxNumberOfFiles when the file is
    ///                                    created.
    /// @error PerErrc::kInvalidOpenMode Returned if the passed mode contains an invalid combination of modes.
    virtual ara::core::Result<UniqueHandle<ReadWriteAccessor>> OpenFileWriteOnly(ara::core::StringView fileName,
        OpenMode mode) noexcept = 0;

    /// @brief Opens a file of this File Storage for writing with a user provided buffer.
    ///
    /// If not otherwise specified by the provided mode, the file is truncated (corresponding to kTruncate).
    ///
    /// The provided buffer will be used by the ReadWriteAccessor to implement block-wise writing to speed up multiple
    /// small accesses to the file.
    ///
    /// If the file does not exist, it is created.
    ///
    /// The file will be closed when the returned UniqueHandle goes out of scope.
    ///
    /// @traceid{SWS_PER_00431}@tracestatus{valid}
    /// @uptrace{RS_PER_00001}
    /// @uptrace{RS_PER_00004}
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
    /// @param[in] fileName File name of the file. May correspond to the PersistencyFile.fileName of a configured file.
    /// @param[in] mode Mode with which the file shall be opened.
    /// @param[in] buffer Memory to be used for block-wise writing.
    /// @returns A Result containing a UniqueHandle for the file. In case of an error, it contains any of the errors
    ///          defined below, or a vendor specific error.
    /// @error PerErrc::kIllegalWriteAccess Returned if the File Storage is configured as read-only.
    /// @error PerErrc::kPhysicalStorageFailure Returned if access to the storage fails.
    /// @error PerErrc::kIntegrityCorrupted Returned if stored data cannot be read because the structural integrity is
    ///                                     corrupted.
    /// @error PerErrc::kValidationFailed Returned if the validity of stored data cannot be ensured.
    /// @error PerErrc::kEncryptionFailed Returned if the decryption of stored data fails.
    /// @error PerErrc::kResourceBusy Returned if the file is already open, or if DeleteFile, RecoverFile, or ResetFile
    ///                               with the same file name is currently being executed.
    /// @error PerErrc::kOutOfStorageSpace Returned if the available storage space is insufficient or the number of
    ///                                    files would get larger than the configured maxNumberOfFiles when the file is
    ///                                    created.
    /// @error PerErrc::kInvalidOpenMode Returned if the passed mode contains an invalid combination of modes.
    virtual ara::core::Result<UniqueHandle<ReadWriteAccessor>> OpenFileWriteOnly(ara::core::StringView fileName,
        OpenMode mode, ara::core::Span<ara::core::Byte> buffer) noexcept = 0;

    /// @brief Deletes a file from this File Storage.
    ///
    /// This operation will fail with kResourceBusy when the file is currently open.
    ///
    /// @traceid{SWS_PER_00111}@tracestatus{valid}
    /// @uptrace{RS_PER_00001}
    /// @uptrace{RS_PER_00004}
    /// @uptrace{RS_AP_00119}
    /// @uptrace{RS_AP_00120}
    /// @uptrace{RS_AP_00121}
    /// @uptrace{RS_AP_00127}
    /// @uptrace{RS_AP_00128}
    /// @uptrace{RS_AP_00129}
    /// @uptrace{RS_AP_00132}
    /// @threadsafety{re-entrant}
    /// @param[in] fileName File name of the file. May correspond to the PersistencyFile.fileName of a configured file.
    /// @returns A Result of void. In case of an error, it contains any of the errors defined below, or a vendor
    ///          specific error.
    /// @error PerErrc::kIllegalWriteAccess Returned if the File Storage is configured as read-only.
    /// @error PerErrc::kPhysicalStorageFailure Returned if access to the storage fails.
    /// @error PerErrc::kIntegrityCorrupted Returned if stored data cannot be written because the structural integrity
    ///                                     is corrupted.
    /// @error PerErrc::kEncryptionFailed Returned if the encryption or decryption of stored data fails.
    /// @error PerErrc::kResourceBusy Returned if the file is open, or if RecoverFile or ResetFile with the same file
    ///                               name is currently being executed.
    /// @error PerErrc::kFileNotFound Returned if the provided file does not exist in the File Storage.
    virtual ara::core::Result<void> DeleteFile(ara::core::StringView fileName) noexcept = 0;

    /// @brief Recovers a file of this File Storage.
    ///
    /// This method allows to recover a single file when the redundancy checks fail.
    ///
    /// It will fail with kResourceBusy when the file is currently open.
    ///
    /// This method does a best-effort recovery of the file. After recovery, the file might show outdated or initial
    /// content, or might be lost.
    ///
    /// @traceid{SWS_PER_00337}@tracestatus{valid}
    /// @uptrace{RS_PER_00001}
    /// @uptrace{RS_PER_00004}
    /// @uptrace{RS_PER_00009}
    /// @uptrace{RS_AP_00119}
    /// @uptrace{RS_AP_00120}
    /// @uptrace{RS_AP_00121}
    /// @uptrace{RS_AP_00127}
    /// @uptrace{RS_AP_00128}
    /// @uptrace{RS_AP_00129}
    /// @uptrace{RS_AP_00132}
    /// @threadsafety{re-entrant}
    /// @param[in] fileName File name of the file. May correspond to the PersistencyFile.fileName of a configured file.
    /// @returns A Result of void. In case of an error, it contains any of the errors defined below, or a vendor
    ///          specific error.
    /// @error PerErrc::kPhysicalStorageFailure Returned if access to the storage fails.
    /// @error PerErrc::kEncryptionFailed Returned if the encryption or decryption of stored data fails.
    /// @error PerErrc::kResourceBusy Returned if the file is open, or if DeleteFile or ResetFile with the same file
    ///                               name is currently being executed.
    /// @error PerErrc::kOutOfStorageSpace Returned if the available storage space is insufficient for the restored
    ///                                    file.
    /// @error PerErrc::kFileNotFound Returned if the provided file does not exist in the File Storage.
    virtual ara::core::Result<void> RecoverFile(ara::core::StringView fileName) noexcept = 0;

    /// @brief Resets a file of this File Storage to its initial content.
    ///
    /// ResetFile allows to reset a single file to its initial content. If the file is currently not available in the
    /// File Storage, it is re-created. Afterwards, the file will appear in both cases as if it was newly installed from
    /// the current manifest.
    ///
    /// It will fail with kResourceBusy when the file is currently open, and with kInitValueNotAvailable when neither
    /// design nor deployment define an initial content for the file.
    ///
    /// @traceid{SWS_PER_00338}@tracestatus{valid}
    /// @uptrace{RS_PER_00001}
    /// @uptrace{RS_PER_00004}
    /// @uptrace{RS_PER_00009}
    /// @uptrace{RS_AP_00119}
    /// @uptrace{RS_AP_00120}
    /// @uptrace{RS_AP_00121}
    /// @uptrace{RS_AP_00127}
    /// @uptrace{RS_AP_00128}
    /// @uptrace{RS_AP_00129}
    /// @uptrace{RS_AP_00132}
    /// @threadsafety{re-entrant}
    /// @param[in] fileName File name of the file. May correspond to the PersistencyFile.fileName of a configured file.
    /// @returns A Result of void. In case of an error, it contains any of the errors defined below, or a vendor
    ///          specific error.
    /// @error PerErrc::kPhysicalStorageFailure Returned if access to the storage fails.
    /// @error PerErrc::kEncryptionFailed Returned if the encryption or decryption of stored data fails.
    /// @error PerErrc::kInitValueNotAvailable Returned if no intitial value was configured for this file.
    /// @error PerErrc::kResourceBusy Returned if the file is open, or if DeleteFile or RecoverFile with the same file
    ///                               name is currently being executed.
    /// @error PerErrc::kOutOfStorageSpace Returned if the available storage space is insufficient or the number of
    ///                                    files would get larger than the configured maxNumberOfFiles when the file is
    ///                                    restored.
    virtual ara::core::Result<void> ResetFile(ara::core::StringView fileName) noexcept = 0;

    /// @brief Returns the space in bytes currently occupied by the content of a file of this File Storage.
    ///
    /// The returned size is only accurate if no other operation on the file takes place at the same time.
    ///
    /// @traceid{SWS_PER_00407}@tracestatus{valid}
    /// @uptrace{RS_PER_00017}
    /// @uptrace{RS_AP_00119}
    /// @uptrace{RS_AP_00120}
    /// @uptrace{RS_AP_00121}
    /// @uptrace{RS_AP_00127}
    /// @uptrace{RS_AP_00128}
    /// @uptrace{RS_AP_00129}
    /// @uptrace{RS_AP_00132}
    /// @threadsafety{re-entrant}
    /// @param[in] fileName File name of the file. May correspond to the PersistencyFile.fileName of a configured file.
    /// @returns A Result containing the occupied space in bytes. In case of an error, it contains any of the errors
    ///          defined below, or a vendor specific error.
    /// @error PerErrc::kPhysicalStorageFailure Returned if access to the storage fails.
    /// @error PerErrc::kIntegrityCorrupted Returned if stored data cannot be read because the structural integrity
    ///                                     is corrupted.
    /// @error PerErrc::kFileNotFound Returned if the provided file does not exist in the File Storage.
    virtual ara::core::Result<std::uint64_t> GetCurrentFileSize(ara::core::StringView fileName) const noexcept = 0;

    /// @brief Returns additional information on a file of this File Storage.
    ///
    /// The returned FileInfo struct contains information about the times when the file was created, last modified, and last accessed,
    /// and about how and by whom the file was created and last modified.
    /// The modificationTime, accessTime, and fileModificationState returned in the FileInfo are only accurate if the file is currently not open.
    ///
    /// @traceid{SWS_PER_00438}@tracestatus{valid}
    /// @uptrace{RS_PER_00004}
    /// @uptrace{RS_AP_00119}
    /// @uptrace{RS_AP_00120}
    /// @uptrace{RS_AP_00121}
    /// @uptrace{RS_AP_00127}
    /// @uptrace{RS_AP_00128}
    /// @uptrace{RS_AP_00129}
    /// @uptrace{RS_AP_00132}
    /// @threadsafety{re-entrant}
    /// @param[in] fileName File name of the file. May correspond to the PersistencyFile.fileName of a configured file.
    /// @returns A Result containing a FileInfo struct. In case of an error, it contains any of the errors defined
    ///          below, or a vendor specific error.
    /// @error PerErrc::kPhysicalStorageFailure Returned if access to the storage fails.
    /// @error PerErrc::kIntegrityCorrupted Returned if stored data cannot be read because the structural integrity is
    ///                                     corrupted.
    /// @error PerErrc::kFileNotFound Returned if the provided file does not exist in the File Storage.
    virtual ara::core::Result<FileInfo> GetFileInfo(ara::core::StringView fileName) const noexcept = 0;
};

/// @brief Opens a File Storage.
///
/// OpenFileStorage will fail with kResourceBusy when the File Storage is currently being modified by a call from
/// another thread to UpdatePersistency, ResetPersistency, RecoverAllFiles, or ResetAllFiles.
///
/// Because multiple threads can access the same File Storage concurrently, the File Storage might not be closed when
/// the SharedHandle returned by this function goes out of scope. It will only be closed when all SharedHandles that
/// refer to the same File Storage went out of scope.
///
/// @traceid{SWS_PER_00116}@tracestatus{valid}
/// @uptrace{RS_PER_00001}
/// @uptrace{RS_PER_00004}
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
/// @param[in] fs The shortName path of a PortPrototype typed by a PersistencyFileStorageInterface.
/// @returns A Result containing a SharedHandle for the File Storage. In case of an error, it contains any of the errors
///          defined below, or a vendor specific error.
/// @error PerErrc::kStorageNotFound Returned if the passed InstanceSpecifier does not match any
///                                  PersistencyFileStorageInterface configured for this Executable.
/// @error PerErrc::kPhysicalStorageFailure Returned if access to the storage fails.
/// @error PerErrc::kIntegrityCorrupted Returned if stored data cannot be read because the structural integrity is
///                                     corrupted.
/// @error PerErrc::kValidationFailed Returned if the validity of stored data cannot be ensured.
/// @error PerErrc::kEncryptionFailed Returned if the decryption of stored data fails.
/// @error PerErrc::kResourceBusy Returned if UpdatePersistency or ResetPersistency is currently being executed, or if
///                               RecoverAllFiles or ResetAllFiles is currently being executed for the same File
///                               Storage.
/// @error PerErrc::kOutOfStorageSpace Returned if the available storage space is insufficient for the added/updated
///                                    files.
/// @verbatim embed:rst:leading-slashes
/// .. uml:: ../../../../source/ara/per/docs/AraPer_OpenFileStorage_AD.puml
/// @endverbatim
ara::core::Result<SharedHandle<FileStorage>> OpenFileStorage(const ara::core::InstanceSpecifier& fs) noexcept;

/// @brief Recovers a File Storage, including all files.
///
/// RecoverAllFiles recovers a File Storage when the redundancy checks fail.
///
/// It will fail with kResourceBusy when the File Storage is currently open, or when it is modified by a call from
/// another thread to UpdatePersistency, ResetPersistency, RecoverAllFiles, or ResetAllFiles.
///
/// This method does a best-effort recovery of all files. After recovery, files might show outdated or initial content,
/// or might be lost.
///
/// @traceid{SWS_PER_00335}@tracestatus{valid}
/// @uptrace{RS_PER_00001}
/// @uptrace{RS_PER_00004}
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
/// @param[in] fs The shortName path of a PortPrototype typed by a PersistencyFileStorageInterface.
/// @returns A Result of void. In case of an error, it contains any of the errors defined below, or a vendor specific
///          error.
/// @error PerErrc::kStorageNotFound Returned if the passed InstanceSpecifier does not match any
///                                  PersistencyFileStorageInterface configured for this Executable.
/// @error PerErrc::kPhysicalStorageFailure Returned if access to the storage fails.
/// @error PerErrc::kEncryptionFailed Returned if the encryption of stored data fails.
/// @error PerErrc::kResourceBusy Returned if UpdatePersistency or ResetPersistency is currently being executed, or if
///                               ResetAllFiles is currently being executed for the same File Storage, or a SharedHandle
///                               of the same File Storage is currently in use.
/// @error PerErrc::kOutOfStorageSpace Returned if the available storage space is insufficient for the restored files.
/// @verbatim embed:rst:leading-slashes
/// .. uml:: ../../../../source/ara/per/docs/AraPer_RecoverAllFiles_AD.puml
/// @endverbatim
ara::core::Result<void> RecoverAllFiles(const ara::core::InstanceSpecifier& fs) noexcept;

/// @brief Resets a File Storage, including all files.
///
/// ResetAllFiles resets a File Storage to the initial state, containing only the files which were deployed from the
/// manifest, with their initial content. Afterwards, the File Storage will appear as if it was newly installed from the
/// current manifest.
///
/// It will fail with kResourceBusy when the File Storage is currently open, or when it is modified by a call from
/// another thread to UpdatePersistency, ResetPersistency, RecoverAllFiles, or ResetAllFiles.
///
/// @traceid{SWS_PER_00336}@tracestatus{valid}
/// @uptrace{RS_PER_00001}
/// @uptrace{RS_PER_00004}
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
/// @param[in] fs The shortName path of a PortPrototype typed by a PersistencyFileStorageInterface.
/// @returns A Result of void. In case of an error, it contains any of the errors defined below, or a vendor specific
///          error.
/// @error PerErrc::kStorageNotFound Returned if the passed InstanceSpecifier does not match any
///                                  PersistencyFileStorageInterface configured for this Executable.
/// @error PerErrc::kPhysicalStorageFailure Returned if access to the storage fails.
/// @error PerErrc::kEncryptionFailed Returned if the encryption of stored data fails.
/// @error PerErrc::kResourceBusy Returned if UpdatePersistency or ResetPersistency is currently being executed, or if
///                               RecoverAllFiles is currently being executed for the same File Storage, or a
///                               SharedHandle of the same File Storage is currently in use.
/// @error PerErrc::kOutOfStorageSpace Returned if the available storage space is insufficient for the restored files.
/// @verbatim embed:rst:leading-slashes
/// .. uml:: ../../../../source/ara/per/docs/AraPer_ResetAllFiles_AD.puml
/// @endverbatim
ara::core::Result<void> ResetAllFiles(const ara::core::InstanceSpecifier& fs) noexcept;

/// @brief Returns the space in bytes currently occupied by a File Storage.
///
/// The returned size includes all meta data and the space used for redundancy and backups.
///
/// The returned size is only accurate if no other operation on the File Storage takes place at the same time.
///
/// @traceid{SWS_PER_00406}@tracestatus{valid}
/// @uptrace{RS_PER_00017}
/// @uptrace{RS_AP_00119}
/// @uptrace{RS_AP_00120}
/// @uptrace{RS_AP_00121}
/// @uptrace{RS_AP_00127}
/// @uptrace{RS_AP_00128}
/// @uptrace{RS_AP_00129}
/// @uptrace{RS_AP_00132}
/// @threadsafety{re-entrant}
/// @param[in] fs The shortName path of a PortPrototype typed by a PersistencyFileStorageInterface.
/// @returns A Result containing the occupied space in bytes. In case of an error, it contains any of the errors defined
///          below, or a vendor specific error.
/// @error PerErrc::kStorageNotFound Returned if the passed InstanceSpecifier does not match any
///                                  PersistencyFileStorageInterface configured for this Executable.
/// @error PerErrc::kPhysicalStorageFailure Returned if access to the storage fails.
ara::core::Result<std::uint64_t> GetCurrentFileStorageSize(const ara::core::InstanceSpecifier& fs) noexcept;

}  // namespace per
}  // namespace ara

#endif  // ARA_PER_FILE_STORAGE_H_
