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

#ifndef ARA_PER_READ_ACCESSOR_H_
#define ARA_PER_READ_ACCESSOR_H_

#include "ara/core/utility.h"
#include "ara/core/result.h"
#include "ara/core/string.h"
#include "ara/core/vector.h"

#include "ara/per/per_error_domain.h"

namespace ara
{
namespace per
{

/// @brief Specification of origin used in MovePosition.
///
/// @traceid{SWS_PER_00146}@tracestatus{valid}
/// @uptrace{RS_PER_00003}
/// @uptrace{RS_AP_00122}
enum class Origin : std::uint32_t
{
    /// Seek from the beginning of the file.
    kBeginning = 0,
    /// Seek from the current position.
    kCurrent = 1,
    /// Seek from the end of the file.
    kEnd = 2
};

/// @brief ReadAccessor is used to read file data.
///
/// It provides binary and text mode methods for checking or getting the current byte/character (PeekByte/PeekChar,
/// GetByte/GetChar) methods for reading a section of a binary/text file (ReadBinary/ReadText), a method to read a line
/// of text (ReadLine), and methods for checking and setting the current position in the file (GetPosition, SetPosition,
/// MovePosition, IsEof) and for checking the current size of the file (GetSize).
///
/// @traceid{SWS_PER_00342}@tracestatus{valid}
/// @uptrace{RS_PER_00004}
/// @uptrace{RS_AP_00122}
/// @uptrace{RS_AP_00146}
class ReadAccessor
{
public:
    /// @brief The default constructor for ReadAccessor shall not be used.
    ///
    /// @traceid{SWS_PER_00461}@tracestatus{draft}
    /// @uptrace{RS_PER_00004}
    /// @uptrace{RS_AP_00120}
    /// @uptrace{RS_AP_00129}
    /// @uptrace{RS_AP_00146}
    ReadAccessor() = default;

    /// @brief The move constructor for ReadAccessor shall not be used.
    ///
    /// @traceid{SWS_PER_00413}@tracestatus{valid}
    /// @uptrace{RS_PER_00004}
    /// @uptrace{RS_AP_00120}
    /// @uptrace{RS_AP_00121}
    /// @uptrace{RS_AP_00129}
    /// @uptrace{RS_AP_00132}
    ReadAccessor(ReadAccessor&& ra) = delete;

    /// @brief The move assignment operator for ReadAccessor shall not be used.
    ///
    /// @traceid{SWS_PER_00414}@tracestatus{valid}
    /// @uptrace{RS_PER_00004}
    /// @uptrace{RS_AP_00119}
    /// @uptrace{RS_AP_00120}
    /// @uptrace{RS_AP_00121}
    /// @uptrace{RS_AP_00132}
    ReadAccessor& operator=(ReadAccessor&& ra) & = delete;

    /// @brief The copy constructor for ReadAccessor shall not be used.
    ///
    /// @traceid{SWS_PER_00415}@tracestatus{valid}
    /// @uptrace{RS_PER_00004}
    /// @uptrace{RS_AP_00120}
    ReadAccessor(const ReadAccessor&) = delete;

    /// @brief The copy assignment operator for ReadAccessor shall not be used.
    ///
    /// @traceid{SWS_PER_00416}@tracestatus{valid}
    /// @uptrace{RS_PER_00004}
    /// @uptrace{RS_AP_00119}
    /// @uptrace{RS_AP_00120}
    ReadAccessor& operator=(const ReadAccessor&) = delete;

    /// @brief Destructor for ReadAccessor.
    ///
    /// @traceid{SWS_PER_00417}@tracestatus{valid}
    /// @uptrace{RS_PER_00004}
    /// @uptrace{RS_AP_00120}
    /// @uptrace{RS_AP_00129}
    /// @uptrace{RS_AP_00132}
    /// @uptrace{RS_AP_00134}
    /// @threadsafety{no}
    virtual ~ReadAccessor() noexcept = default;

    /// @brief Returns the character at the current position of the file.
    ///
    /// The current position is not changed.
    ///
    /// @traceid{SWS_PER_00167}@tracestatus{valid}
    /// @uptrace{RS_PER_00001}
    /// @uptrace{RS_PER_00004}
    /// @uptrace{RS_AP_00119}
    /// @uptrace{RS_AP_00120}
    /// @uptrace{RS_AP_00132}
    /// @threadsafety{no}
    /// @returns A Result containing a character. In case of an error, it contains any of the errors defined below, or a
    ///          vendor specific error.
    /// @error PerErrc::kPhysicalStorageFailure Returned if access to the storage fails.
    /// @error PerErrc::kValidationFailed Returned if the validity of stored data cannot be ensured.
    /// @error PerErrc::kEncryptionFailed Returned if the decryption of stored data fails.
    /// @error PerErrc::kIsEof Returned if the current position is at the end of the file or if the file is empty.
    virtual ara::core::Result<char> PeekChar() const noexcept = 0;

    /// @brief Returns the byte at the current position of the file.
    ///
    /// The current position is not changed.
    ///
    /// @traceid{SWS_PER_00418}@tracestatus{valid}
    /// @uptrace{RS_PER_00001}
    /// @uptrace{RS_PER_00004}
    /// @uptrace{RS_AP_00119}
    /// @uptrace{RS_AP_00120}
    /// @uptrace{RS_AP_00132}
    /// @threadsafety{no}
    /// @returns A Result containing a byte. In case of an error, it contains any of the errors defined below, or a
    ///          vendor specific error.
    /// @error PerErrc::kPhysicalStorageFailure Returned if access to the storage fails.
    /// @error PerErrc::kValidationFailed Returned if the validity of stored data cannot be ensured.
    /// @error PerErrc::kEncryptionFailed Returned if the decryption of stored data fails.
    /// @error PerErrc::kIsEof Returned if the current position is at the end of the file or if the file is empty.
    virtual ara::core::Result<ara::core::Byte> PeekByte() const noexcept = 0;

    /// @brief Returns the character at the current position of the file, advancing the current position.
    ///
    /// In case of an error, the current position is not changed.
    ///
    /// @traceid{SWS_PER_00168}@tracestatus{valid}
    /// @uptrace{RS_PER_00001}
    /// @uptrace{RS_PER_00004}
    /// @uptrace{RS_AP_00119}
    /// @uptrace{RS_AP_00120}
    /// @uptrace{RS_AP_00132}
    /// @threadsafety{no}
    /// @returns A Result containing a character. In case of an error, it contains any of the errors defined below, or a
    ///          vendor specific error.
    /// @error PerErrc::kPhysicalStorageFailure Returned if access to the storage fails.
    /// @error PerErrc::kValidationFailed Returned if the validity of stored data cannot be ensured.
    /// @error PerErrc::kEncryptionFailed Returned if the decryption of stored data fails.
    /// @error PerErrc::kIsEof Returned if the current position is at the end of the file or if the file is empty.
    virtual ara::core::Result<char> GetChar() noexcept = 0;

    /// @brief Returns the byte at the current position of the file, advancing the current position.
    ///
    /// In case of an error, the current position is not changed.
    ///
    /// @traceid{SWS_PER_00419}@tracestatus{valid}
    /// @uptrace{RS_PER_00001}
    /// @uptrace{RS_PER_00004}
    /// @uptrace{RS_AP_00119}
    /// @uptrace{RS_AP_00120}
    /// @uptrace{RS_AP_00132}
    /// @threadsafety{no}
    /// @returns A Result containing a byte. In case of an error, it contains any of the errors defined below, or a
    ///          vendor specific error.
    /// @error PerErrc::kPhysicalStorageFailure Returned if access to the storage fails.
    /// @error PerErrc::kValidationFailed Returned if the validity of stored data cannot be ensured.
    /// @error PerErrc::kEncryptionFailed Returned if the decryption of stored data fails.
    /// @error PerErrc::kIsEof Returned if the current position is at the end of the file or if the file is empty.
    virtual ara::core::Result<ara::core::Byte> GetByte() noexcept = 0;

    /// @brief Reads all remaining characters into a String, starting from the current position.
    ///
    /// The current position is set to the end of the file.
    ///
    /// In case of an error, the current position is not changed.
    ///
    /// @traceid{SWS_PER_00420}@tracestatus{valid}
    /// @uptrace{RS_PER_00001}
    /// @uptrace{RS_PER_00004}
    /// @uptrace{RS_AP_00119}
    /// @uptrace{RS_AP_00120}
    /// @uptrace{RS_AP_00121}
    /// @uptrace{RS_AP_00127}
    /// @uptrace{RS_AP_00132}
    /// @threadsafety{no}
    /// @returns A Result containing a String. In case of an error, it contains any of the errors defined below, or a
    ///          vendor specific error.
    /// @error PerErrc::kPhysicalStorageFailure Returned if access to the storage fails.
    /// @error PerErrc::kValidationFailed Returned if the validity of stored data cannot be ensured.
    /// @error PerErrc::kEncryptionFailed Returned if the decryption of stored data fails.
    /// @error PerErrc::kIsEof Returned if the current position is at the end of the file or if the file is empty.
    virtual ara::core::Result<ara::core::String> ReadText() noexcept = 0;

    /// @brief Reads a number of characters into a String, starting from the current position.
    ///
    /// The current position is advanced accordingly.
    ///
    /// If the end of the file is reached, the number of returned characters can be less than the requested number, and
    /// the current position is set to the end of the file.
    ///
    /// In case of an error, the current position is not changed.
    ///
    /// @traceid{SWS_PER_00165}@tracestatus{valid}
    /// @uptrace{RS_PER_00001}
    /// @uptrace{RS_PER_00004}
    /// @uptrace{RS_AP_00119}
    /// @uptrace{RS_AP_00120}
    /// @uptrace{RS_AP_00121}
    /// @uptrace{RS_AP_00127}
    /// @uptrace{RS_AP_00132}
    /// @threadsafety{no}
    /// @param[in] n Number of characters to read.
    /// @returns A Result containing a String. In case of an error, it contains any of the errors defined below, or a
    ///          vendor specific error.
    /// @error PerErrc::kPhysicalStorageFailure Returned if access to the storage fails.
    /// @error PerErrc::kValidationFailed Returned if the validity of stored data cannot be ensured.
    /// @error PerErrc::kEncryptionFailed Returned if the decryption of stored data fails.
    /// @error PerErrc::kIsEof Returned if the current position is at the end of the file or if the file is empty.
    virtual ara::core::Result<ara::core::String> ReadText(std::uint64_t n) noexcept = 0;

    /// @brief Reads all remaining bytes into a Vector of Byte, starting from the current position.
    ///
    /// The current position is set to the end of the file.
    ///
    /// In case of an error, the current position is not changed.
    ///
    /// @traceid{SWS_PER_00421}@tracestatus{valid}
    /// @uptrace{RS_PER_00001}
    /// @uptrace{RS_PER_00004}
    /// @uptrace{RS_AP_00119}
    /// @uptrace{RS_AP_00120}
    /// @uptrace{RS_AP_00121}
    /// @uptrace{RS_AP_00127}
    /// @uptrace{RS_AP_00132}
    /// @threadsafety{no}
    /// @returns A Result containing a Vector of Byte. In case of an error, it contains any of the errors defined below,
    ///          or a vendor specific error.
    /// @error PerErrc::kPhysicalStorageFailure Returned if access to the storage fails.
    /// @error PerErrc::kValidationFailed Returned if the validity of stored data cannot be ensured.
    /// @error PerErrc::kEncryptionFailed Returned if the decryption of stored data fails.
    /// @error PerErrc::kIsEof Returned if the current position is at the end of the file or if the file is empty.
    virtual ara::core::Result<ara::core::Vector<ara::core::Byte>> ReadBinary() noexcept = 0;

    /// @brief Reads a number of bytes into a Vector of Byte, starting from the current position.
    ///
    /// The current position is advanced accordingly.
    ///
    /// If the end of the file is reached, the number of returned bytes can be less than the requested number, and the
    /// current position is set to the end of the file.
    ///
    /// In case of an error, the current position is not changed.
    ///
    /// @traceid{SWS_PER_00422}@tracestatus{valid}
    /// @uptrace{RS_PER_00001}
    /// @uptrace{RS_PER_00004}
    /// @uptrace{RS_AP_00119}
    /// @uptrace{RS_AP_00120}
    /// @uptrace{RS_AP_00121}
    /// @uptrace{RS_AP_00127}
    /// @uptrace{RS_AP_00132}
    /// @threadsafety{no}
    /// @param[in] n Number of bytes to read.
    /// @returns A Result containing a Vector of Byte. In case of an error, it contains any of the errors defined below,
    ///          or a vendor specific error.
    /// @error PerErrc::kPhysicalStorageFailure Returned if access to the storage fails.
    /// @error PerErrc::kValidationFailed Returned if the validity of stored data cannot be ensured.
    /// @error PerErrc::kEncryptionFailed Returned if the decryption of stored data fails.
    /// @error PerErrc::kIsEof Returned if the current position is at the end of the file or if the file is empty.
    virtual ara::core::Result<ara::core::Vector<ara::core::Byte>> ReadBinary(std::uint64_t n) noexcept = 0;

    /// @brief Reads a complete line of characters into a String, advancing the current position accordingly.
    ///
    /// The end of the line is demarcated by the delimiter, or by "\\n" (ASCII 0x0a) if that parameter is omitted. The
    /// delimiter itself is not included in the returned String.
    ///
    /// If the end of the file is reached, the remaining characters are returned and the current position is set to the
    /// end of the file.
    ///
    /// In case of an error, the current position is not changed.
    ///
    /// @traceid{SWS_PER_00119}@tracestatus{valid}
    /// @uptrace{RS_PER_00001}
    /// @uptrace{RS_PER_00004}
    /// @uptrace{RS_AP_00119}
    /// @uptrace{RS_AP_00120}
    /// @uptrace{RS_AP_00121}
    /// @uptrace{RS_AP_00127}
    /// @uptrace{RS_AP_00129}
    /// @uptrace{RS_AP_00132}
    /// @threadsafety{no}
    /// @param[in] delimiter The character that is used as delimiter.
    /// @returns A Result containing a String. In case of an error, it contains any of the errors defined below, or a
    ///          vendor specific error.
    /// @error PerErrc::kPhysicalStorageFailure Returned if access to the storage fails.
    /// @error PerErrc::kValidationFailed Returned if the validity of stored data cannot be ensured.
    /// @error PerErrc::kEncryptionFailed Returned if the decryption of stored data fails.
    /// @error PerErrc::kIsEof Returned if the current position is at the end of the file or if the file is empty.
    virtual ara::core::Result<ara::core::String> ReadLine(char delimiter = '\n') noexcept = 0;

    /// @brief Returns the current size of a file in bytes.
    ///
    /// @traceid{SWS_PER_00424}@tracestatus{valid}
    /// @uptrace{RS_PER_00017}
    /// @uptrace{RS_AP_00119}
    /// @uptrace{RS_AP_00120}
    /// @uptrace{RS_AP_00121}
    /// @uptrace{RS_AP_00127}
    /// @uptrace{RS_AP_00128}
    /// @uptrace{RS_AP_00129}
    /// @uptrace{RS_AP_00132}
    /// @threadsafety{no}
    /// @returns The current size of the file in bytes.
    virtual std::uint64_t GetSize() const noexcept = 0;

    /// @brief Returns the current position relative to the beginning of the file.
    ///
    /// The returned position may be at the end of the file.
    ///
    /// @traceid{SWS_PER_00162}@tracestatus{valid}
    /// @uptrace{RS_PER_00001}
    /// @uptrace{RS_PER_00004}
    /// @uptrace{RS_AP_00119}
    /// @uptrace{RS_AP_00120}
    /// @uptrace{RS_AP_00132}
    /// @threadsafety{no}
    /// @returns The current position in the file in bytes from the beginning of the file.
    virtual std::uint64_t GetPosition() const noexcept = 0;

    /// @brief Sets the current position relative to the beginning of the file.
    ///
    /// In case of an error, the current position is not changed.
    ///
    /// @traceid{SWS_PER_00163}@tracestatus{valid}
    /// @uptrace{RS_PER_00001}
    /// @uptrace{RS_PER_00004}
    /// @uptrace{RS_AP_00119}
    /// @uptrace{RS_AP_00120}
    /// @uptrace{RS_AP_00121}
    /// @uptrace{RS_AP_00132}
    /// @threadsafety{no}
    /// @param[in] position Current position in the file in bytes from the beginning of the file.
    /// @returns A Result of void. In case of an error, it contains any of the errors defined below, or a vendor
    ///          specific error.
    /// @error PerErrc::kInvalidPosition Returned if the given position is beyond the end of the file.
    virtual ara::core::Result<void> SetPosition(std::uint64_t position) noexcept = 0;

    /// @brief Moves the current position in the file relative to the Origin.
    ///
    /// In case of an error, the current position is not changed.
    ///
    /// @traceid{SWS_PER_00164}@tracestatus{valid}
    /// @uptrace{RS_PER_00001}
    /// @uptrace{RS_PER_00004}
    /// @uptrace{RS_AP_00119}
    /// @uptrace{RS_AP_00120}
    /// @uptrace{RS_AP_00121}
    /// @uptrace{RS_AP_00132}
    /// @threadsafety{no}
    /// @param[in] origin Starting point from which to move 'offset' bytes.
    /// @param[in] offset Offset in bytes relative to 'origin'. Can be positive in case of kBeginning and kCurrent and
    ///                   negative in case of kCurrent and kEnd. In case of kCurrent, an offset of zero will not change
    ///                   the current position. In case of kEnd, an offset of zero will set the position to the end of
    ///                   the file.
    /// @returns A Result containing the new position in bytes from the beginning of the file. In case of an error, it
    ///          contains any of the errors defined below, or a vendor specific error.
    /// @error PerErrc::kInvalidPosition Returned if the resulting position is lower than zero or beyond the end of the
    ///                                  file.
    virtual ara::core::Result<std::uint64_t> MovePosition(Origin origin, std::int64_t offset) noexcept = 0;

    /// @brief Checks if the current position is at end of file.
    ///
    /// @traceid{SWS_PER_00107}@tracestatus{valid}
    /// @uptrace{RS_PER_00001}
    /// @uptrace{RS_PER_00004}
    /// @uptrace{RS_AP_00119}
    /// @uptrace{RS_AP_00120}
    /// @uptrace{RS_AP_00132}
    /// @threadsafety{no}
    /// @returns True if the current position is at the end of the file, false otherwise.
    virtual bool IsEof() const noexcept = 0;
};

} // namespace per
} // namespace ara

#endif // ARA_PER_READ_ACCESSOR_H_
