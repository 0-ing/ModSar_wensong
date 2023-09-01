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

#ifndef ARA_PER_ERROR_H_
#define ARA_PER_ERROR_H_

#include "ara/core/error_domain.h"
#include "ara/core/error_code.h"
#include "ara/core/exception.h"

namespace ara
{
namespace per
{

/// @brief Defines the errors for Persistency.
///
/// The enumeration values 0 - 255 are reserved for AUTOSAR assigned errors, the stack provider is free to define
/// additional errors starting from 256.
///
/// @traceid{SWS_PER_00311}@tracestatus{valid}
/// @uptrace{RS_AP_00122}
/// @uptrace{RS_AP_00127}
enum class PerErrc : ara::core::ErrorDomain::CodeType
{
    /// The requested Key-Value Storage or File Storage is not configured in the AUTOSAR model.
    kStorageNotFound = 1,
    /// The provided key cannot be not found in the Key-Value Storage.
    kKeyNotFound = 2,
    /// Opening a file for writing or changing, or synchronizing a key-value pair failed, because the storage is
    /// configured read-only.
    kIllegalWriteAccess = 3,
    /// An error occurred when accessing the physical storage, e.g. because of a corrupted file system or corrupted
    /// hardware, or because of insufficient access rights.
    kPhysicalStorageFailure = 4,
    /// The structural integrity of the storage could not be established. This can happen when the internal structure of
    /// a Key-Value Storage or the meta data of a File Storage is corrupted.
    kIntegrityCorrupted = 5,
    /// The validation of redundancy measures failed for a single key-value pair, for the whole Key-Value Storage, for a
    /// single file, or for the whole File Storage.
    kValidationFailed = 6,
    /// The encryption or decryption failed for a single key-value pair, for the whole Key-Value Storage, for a single
    /// file, or for the whole File Storage.
    kEncryptionFailed = 7,
    /// The provided data type does not match the stored data type.
    kDataTypeMismatch = 8,
    /// The operation could not be performed because no initial value is available.
    kInitValueNotAvailable = 9,
    /// The operation could not be performed because the resource is currently busy.
    kResourceBusy = 10,
    /// The allocated storage quota was exceeded.
    kOutOfStorageSpace = 12,
    /// The requested file name cannot be not found in the File Storage.
    kFileNotFound = 13,
    /// A function of Persistency or a method of one of its classes was called before ara::core::Initialize() or after
    /// ara::core::Deinitialize().
    kNotInitialized = 14,
    /// SetPosition tried to move to a position that is not reachable (i.e. which is smaller than zero or greater than
    /// the current size of the file).
    kInvalidPosition = 15,
    /// The application tried to read from the end of the file or from an empty file.
    kIsEof = 16,
    /// Opening a file failed because the requested combination of OpenModes is invalid.
    kInvalidOpenMode = 17,
    /// SetFileSize tried to set a new size that is bigger than the current file size.
    kInvalidSize = 18
};

/// @brief Exception type thrown by Persistency.
///
/// @traceid{SWS_PER_00354}@tracestatus{valid}
/// @uptrace{RS_AP_00122}
/// @uptrace{RS_AP_00127}
class PerException : public ara::core::Exception
{
public:
    /// @brief Construct a new Persistency exception object containing an error code.
    ///
    /// @traceid{SWS_PER_00355}@tracestatus{valid}
    /// @uptrace{RS_AP_00120}
    /// @uptrace{RS_AP_00121}
    /// @uptrace{RS_AP_00132}
    /// @param[in] errorCode The error code.
    explicit PerException(ara::core::ErrorCode errorCode) noexcept : ara::core::Exception(std::move(errorCode)) {}
};

namespace internal
{
static constexpr char msgStorageNotFound[] = { "The requested Key-Value Storage or File Storage is not configured" };
static constexpr char msgKeyNotFound[] = { "The provided key cannot be not found in the Key-Value Storage" };
static constexpr char msgIllegalWriteAccess[] = {
    "Opening a file for writing or changing, or synchronizing a key failed, because the storage is configured read-only"
};
static constexpr char msgPhysicalStorageFailure[] = { "An error occurred when accessing the physical storage" };
static constexpr char msgIntegrityCorrupted[] = { "The structural integrity of the storage could not be established" };
static constexpr char msgValidationFailed[] = { "The validation of redundancy measures failed" };
static constexpr char msgEncryptionFailed[] = { "The encryption or decryption failed" };
static constexpr char msgDataTypeMismatch[] = { "The provided data type does not match the stored data type" };
static constexpr char msgInitValueNotAvailable[]
    = { "The operation could not be performed because no initial value is available" };
static constexpr char msgResourceBusy[]
    = { "The operation could not be performed because the resource is currently busy" };
static constexpr char msgOutOfStorageSpace[] = { "The allocated storage quota was exceeded" };
static constexpr char msgFileNotFound[] = { "The requested file cannot be not found in the File Storage" };
static constexpr char msgNotInitialized[]
    = { "A function of Persistency or a method of one of its classes was called before ara::core::Initialize() or "
        "after ara::core::Deinitialize()" };
static constexpr char msgInvalidPosition[] = { "SetPosition tried to move to a position that is not reachable" };
static constexpr char msgIsEof[] = { "The application tried to read from the end of the file or from an empty file" };
static constexpr char msgInvalidOpenMode[]
    = { "Opening a file failed because the requested combination of OpenModes is invalid" };
static constexpr char msgInvalidSize[]
    = { "SetFileSize tried to set a new size that is bigger than the current file size" };
static constexpr char msgUnknownError[] = { "Unknown error" };
}
/// @brief Defines the error domain for Persistency.
///
/// @domainid{0x8000'0000'0000'0101}
///
/// @traceid{SWS_PER_00312}@tracestatus{valid}
/// @uptrace{RS_AP_00122}
/// @uptrace{RS_AP_00127}
class PerErrorDomain final : public ara::core::ErrorDomain
{
    static const ErrorDomain::IdType kId { 0x8000000000000101ULL };

public:
    /// @brief Alias for the error code value enumeration.
    ///
    /// @traceid{SWS_PER_00411}@tracestatus{valid}
    /// @uptrace{RS_AP_00122}
    using Errc = PerErrc;

    /// @brief Alias for the exception base class.
    ///
    /// @traceid{SWS_PER_00412}@tracestatus{valid}
    /// @uptrace{RS_AP_00122}
    using Exception = PerException;

    /// @brief Creates a PerErrorDomain instance.
    ///
    /// @traceid{SWS_PER_00313}@tracestatus{valid}
    /// @uptrace{RS_AP_00119}
    /// @uptrace{RS_AP_00120}
    /// @uptrace{RS_AP_00132}
    /// @threadsafety{no}
    PerErrorDomain() noexcept : ErrorDomain(kId) {}

    /// @brief Returns the name of the error domain.
    ///
    /// @traceid{SWS_PER_00314}@tracestatus{valid}
    /// @uptrace{RS_AP_00119}
    /// @uptrace{RS_AP_00120}
    /// @uptrace{RS_AP_00132}
    /// @threadsafety{re-entrant}
    /// @returns The name of the error domain.
    const char* Name() const noexcept override { return "Per"; }

    /// @brief Returns the message associated with the error code.
    ///
    /// @traceid{SWS_PER_00315}@tracestatus{valid}
    /// @uptrace{RS_AP_00119}
    /// @uptrace{RS_AP_00120}
    /// @uptrace{RS_AP_00121}
    /// @uptrace{RS_AP_00132}
    /// @threadsafety{no}
    /// @param[in] errorCode The error code number.
    /// @returns The message associated with the error code.
    const char* Message(CodeType errorCode) const noexcept override
    {
#if defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic error "-Wswitch-enum"
#endif
        Errc const code = static_cast<Errc>(errorCode);
        const char* retVal(nullptr);
        switch (code)
        {
            case PerErrc::kStorageNotFound:
            {
                retVal = internal::msgStorageNotFound;
                break;
            }
            case PerErrc::kKeyNotFound:
            {
                retVal = internal::msgKeyNotFound;
                break;
            }
            case PerErrc::kIllegalWriteAccess:
            {
                retVal = internal::msgIllegalWriteAccess;
                break;
            }
            case PerErrc::kPhysicalStorageFailure:
            {
                retVal = internal::msgPhysicalStorageFailure;
                break;
            }
            case PerErrc::kIntegrityCorrupted:
            {
                retVal = internal::msgIntegrityCorrupted;
                break;
            }
            case PerErrc::kValidationFailed:
            {
                retVal = internal::msgValidationFailed;
                break;
            }
            case PerErrc::kEncryptionFailed:
            {
                retVal = internal::msgEncryptionFailed;
                break;
            }
            case PerErrc::kDataTypeMismatch:
            {
                retVal = internal::msgDataTypeMismatch;
                break;
            }
            case PerErrc::kInitValueNotAvailable:
            {
                retVal = internal::msgInitValueNotAvailable;
                break;
            }
            case PerErrc::kResourceBusy:
            {
                retVal = internal::msgResourceBusy;
                break;
            }
            case PerErrc::kOutOfStorageSpace:
            {
                retVal = internal::msgOutOfStorageSpace;
                break;
            }
            case PerErrc::kFileNotFound:
            {
                retVal = internal::msgFileNotFound;
                break;
            }
            case PerErrc::kNotInitialized:
            {
                retVal = internal::msgNotInitialized;
                break;
            }
            case PerErrc::kInvalidPosition:
            {
                retVal = internal::msgInvalidPosition;
                break;
            }
            case PerErrc::kIsEof:
            {
                retVal = internal::msgIsEof;
                break;
            }
            case PerErrc::kInvalidOpenMode:
            {
                retVal = internal::msgInvalidOpenMode;
                break;
            }
            case PerErrc::kInvalidSize:
            {
                retVal = internal::msgInvalidSize;
                break;
            }
            default:
            {
                retVal = internal::msgUnknownError;
                break;
            }
        }
        return retVal;

#if defined(__GNUC__)
#pragma GCC diagnostic pop
#endif
    }
    /// @brief Throws the exception associated with the error code.
    ///
    /// @traceid{SWS_PER_00350}@tracestatus{valid}
    /// @uptrace{RS_AP_00120}
    /// @uptrace{RS_AP_00121}
    /// @threadsafety{no}
    /// @param[in] errorCode The error to throw.
    void ThrowAsException(const ara::core::ErrorCode& errorCode) const override
    {
        ara::core::ThrowOrTerminate<Exception>(errorCode);
    }
};
namespace internal
{
static const PerErrorDomain g_perErrorDomain;
}

/// @brief Returns the global PerErrorDomain object.
///
/// @traceid{SWS_PER_00352}@tracestatus{valid}
/// @uptrace{RS_AP_00119}
/// @uptrace{RS_AP_00120}
/// @uptrace{RS_AP_00132}
/// @threadsafety{re-entrant}
/// @returns The global PerErrorDomain object.
constexpr const ara::core::ErrorDomain& GetPerDomain() noexcept { return internal::g_perErrorDomain; }

/// @brief Creates an error code.
///
/// @traceid{SWS_PER_00351}@tracestatus{valid}
/// @uptrace{RS_AP_00119}
/// @uptrace{RS_AP_00120}
/// @uptrace{RS_AP_00121}
/// @uptrace{RS_AP_00132}
/// @threadsafety{re-entrant}
/// @param[in] code Error code number.
/// @param[in] data Vendor defined data associated with the error.
/// @returns An ErrorCode object.
constexpr ara::core::ErrorCode MakeErrorCode(PerErrc code, ara::core::ErrorDomain::SupportDataType data) noexcept
{
    return ara::core::ErrorCode(static_cast<ara::core::ErrorDomain::CodeType>(code), GetPerDomain(), data);
}

} // namespace per
} // namespace ara

#endif // APD_ARA_CORE_ERROR_H_
