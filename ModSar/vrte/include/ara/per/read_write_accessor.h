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

#ifndef ARA_PER_READ_WRITE_ACCESSOR_H_
#define ARA_PER_READ_WRITE_ACCESSOR_H_

#include "ara/core/utility.h"
#include "ara/core/result.h"
#include "ara/core/span.h"
#include "ara/core/string.h"
#include "ara/core/vector.h"

#include "ara/per/per_error_domain.h"
#include "ara/per/read_accessor.h"

namespace ara
{
namespace per
{

/// @brief ReadWriteAccessor is used to read and write file data.
///
/// It provides the WriteBinary and WriteText methods featuring a Result for controlled, unformatted writing, and the
/// operator<< method for simple formatted writing. It also provides SyncToFile() to flush the buffer of the operating
/// system to the storage.
///
/// @traceid{SWS_PER_00343}@tracestatus{valid}
/// @uptrace{RS_PER_00004}
/// @uptrace{RS_AP_00122}
/// @uptrace{RS_AP_00146}
class ReadWriteAccessor : public ReadAccessor
{
public:
    /// @brief The default constructor for ReadWriteAccessor shall not be used.
    ///
    /// @traceid{SWS_PER_00462}@tracestatus{draft}
    /// @uptrace{RS_PER_00004}
    /// @uptrace{RS_AP_00120}
    /// @uptrace{RS_AP_00129}
    /// @uptrace{RS_AP_00146}
    // ReadWriteAccessor() = delete;

    /// @brief Triggers flushing of the current file content to the physical storage.
    ///
    /// @traceid{SWS_PER_00122}@tracestatus{valid}
    /// @uptrace{RS_PER_00001}
    /// @uptrace{RS_PER_00004}
    /// @uptrace{RS_AP_00119}
    /// @uptrace{RS_AP_00120}
    /// @uptrace{RS_AP_00128}
    /// @uptrace{RS_AP_00127}
    /// @uptrace{RS_AP_00129}
    /// @uptrace{RS_AP_00132}
    /// @threadsafety{no}
    /// @returns A Result of void. In case of an error, it contains any of the errors defined below, or a vendor
    ///          specific error.
    /// @error PerErrc::kPhysicalStorageFailure Returned if access to the storage fails.
    /// @error PerErrc::kEncryptionFailed Returned if the encryption of stored data fails.
    /// @error PerErrc::kOutOfStorageSpace Returned if the available storage space is insufficient for the updated file
    ///                                    size.
    virtual ara::core::Result<void> SyncToFile() noexcept = 0;

    /// @brief Reduces the size of the file to 'size', effectively removing the current content of the file beyond this
    ///        size.
    ///
    /// The current file position is unchanged if it is lower than 'size', or set to the last valid position in the file
    /// otherwise. If 'size' is 0, the current file position will also be set to 0.
    ///
    /// @traceid{SWS_PER_00428}@tracestatus{valid}
    /// @uptrace{RS_PER_00001}
    /// @uptrace{RS_PER_00004}
    /// @uptrace{RS_AP_00119}
    /// @uptrace{RS_AP_00120}
    /// @uptrace{RS_AP_00128}
    /// @uptrace{RS_AP_00127}
    /// @uptrace{RS_AP_00129}
    /// @uptrace{RS_AP_00132}
    /// @threadsafety{no}
    /// @param[in] size New size of the file.
    /// @returns A Result of void. In case of an error, it contains any of the errors defined below, or a vendor
    ///          specific error.
    /// @error PerErrc::kPhysicalStorageFailure Returned if access to the storage fails.
    /// @error PerErrc::kEncryptionFailed Returned if the encryption or decryption of stored data fails.
    /// @error PerErrc::kInvalidSize Returned if the new size is larger than the current size.
    virtual ara::core::Result<void> SetFileSize(std::uint64_t size) noexcept = 0;

    /// @brief Writes the content of a StringView to the file.
    ///
    /// The time when the content is persisted depends on the implementation of Persistency. SyncToFile can be used to
    /// force Persistency to persist the file content.
    ///
    /// In case of an error, the file content might be corrupted, and the current position might or might not have
    /// changed.
    ///
    /// The expected state of the file for each supported error can be expected to be as follows:
    ///  - kPhysicalStorageFailure: The state of the file is unknown. It could have been entirely destroyed.
    ///  - kEncryptionFailed: The content of the file and the current position will have been updated, but could not be
    ///                       persisted. The persisted file will reflect an older version of the file.
    ///  - kOutOfStorageSpace: The content of the file will have been updated, but the part of the operation that
    ///                        exceeded the quota will have been discarded. The current position will be at the end of
    ///                        the file.
    ///
    /// @traceid{SWS_PER_00166}@tracestatus{valid}
    /// @uptrace{RS_PER_00001}
    /// @uptrace{RS_PER_00004}
    /// @uptrace{RS_AP_00119}
    /// @uptrace{RS_AP_00120}
    /// @uptrace{RS_AP_00121}
    /// @uptrace{RS_AP_00127}
    /// @uptrace{RS_AP_00132}
    /// @threadsafety{no}
    /// @param[in] s A StringView containing the characters to be written.
    /// @returns A Result of void. In case of an error, it contains any of the errors defined below, or a vendor
    ///          specific error.
    /// @error PerErrc::kPhysicalStorageFailure Returned if access to the storage fails.
    /// @error PerErrc::kEncryptionFailed Returned if the encryption or decryption of stored data fails.
    /// @error PerErrc::kOutOfStorageSpace Returned if the available storage space is insufficient for the updated file
    ///        size.
    virtual ara::core::Result<void> WriteText(ara::core::StringView s) noexcept = 0;

    /// @brief Writes the content of a Span of Byte to the file.
    ///
    /// The time when the content is persisted depends on the implementation of Persistency. SyncToFile can be used to
    /// force Persistency to persist the file content.
    ///
    /// In case of an error, the file content might be corrupted, and the current position might or might not have
    /// changed.
    ///
    /// The expected state of the file for each supported error can be expected to be as follows:
    ///  - kPhysicalStorageFailure: The state of the file is unknown. It could have been entirely destroyed.
    ///  - kEncryptionFailed: The content of the file and the current position will have been updated, but could not be
    ///                       persisted. The persisted file will reflect an older version of the file.
    ///  - kOutOfStorageSpace: The content of the file will have been updated, but the part of the operation that
    ///                        exceeded the quota will have been discarded. The current position will be at the end of
    ///                        the file.
    ///
    /// @traceid{SWS_PER_00423}@tracestatus{valid}
    /// @uptrace{RS_PER_00001}
    /// @uptrace{RS_PER_00004}
    /// @uptrace{RS_AP_00119}
    /// @uptrace{RS_AP_00120}
    /// @uptrace{RS_AP_00121}
    /// @uptrace{RS_AP_00127}
    /// @uptrace{RS_AP_00132}
    /// @threadsafety{no}
    /// @param[in] b A Span of Byte containing the bytes to be written.
    /// @returns A Result of void. In case of an error, it contains any of the errors defined below, or a vendor
    ///          specific error.
    /// @error PerErrc::kPhysicalStorageFailure Returned if access to the storage fails.
    /// @error PerErrc::kEncryptionFailed Returned if the encryption or decryption of stored data fails.
    /// @error PerErrc::kOutOfStorageSpace Returned if the available storage space is insufficient for the updated file
    ///                                    size.
    virtual ara::core::Result<void> WriteBinary(ara::core::Span<const ara::core::Byte> b) noexcept = 0;

    /// @brief Writes the content of a StringView to the file.
    ///
    /// This operator is just a comfort feature for non-safety critical applications. If an error occurs during this
    /// operation, it is silently ignored.
    ///
    /// @traceid{SWS_PER_00125}@tracestatus{valid}
    /// @uptrace{RS_PER_00001}
    /// @uptrace{RS_PER_00004}
    /// @uptrace{RS_AP_00119}
    /// @uptrace{RS_AP_00120}
    /// @uptrace{RS_AP_00121}
    /// @uptrace{RS_AP_00127}
    /// @uptrace{RS_AP_00132}
    /// @threadsafety{no}
    /// @param[in] s The StringView containing the characters to be written.
    /// @returns The ReadWriteAccessor object.
    virtual ReadWriteAccessor& operator<<(ara::core::StringView s) noexcept = 0;
};

} // namespace per
} // namespace ara

#endif // ARA_PER_READ_WRITE_ACCESSOR_H_
