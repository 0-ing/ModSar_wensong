/// @copyright 2022 Robert Bosch GmbH. All rights reserved.

#ifndef FLATCFG_ERROR_H
#define FLATCFG_ERROR_H

#include "ara/core/error_code.h"
#include "ara/core/error_domain.h"
#include "ara/core/string.h"

namespace flatcfg
{

/// Error codes for FlatCfg
enum class FlatCfgErrorCode : ara::core::ErrorDomain::CodeType
{
    kNotInitialized = 256,
    kGeneric = 257,
    kParameter = 258,
    kInvalidConfigPath = 259,
    kInvalidFileName = 260,
    kConfigFiles = 261,
    kMultipleProcessesInPath = 262,
    kMemoryAllocationFailed = 263,
    kMemoryAlreadyAllocated = 264,
    kInvalidSWCLName = 265,
    kFileNotFound = 266,
    kFileEmpty = 267,
    kFileAccessError = 268,
    kUnknown = 511,
};

class FlatCfgErrorDomain final : public ara::core::ErrorDomain
{
    /// @brief Key ID for persistency error domain.
    static const ara::core::ErrorDomain::IdType kId { 0x0001 };

public:
    FlatCfgErrorDomain() noexcept : ara::core::ErrorDomain(kId) {}

    /// Returns the name of the component
    char const* Name() const noexcept override { return "FlatCfg"; }

    /// Returns a message for the error code
    /// @param[in] errorCode Error for which the message shall be returned
    /// @return    Message for the given errorCode
    char const* Message(ara::core::ErrorDomain::CodeType errorCode) const noexcept override
    {
        const FlatCfgErrorCode code = static_cast<FlatCfgErrorCode>(errorCode);
        char const* retVal;
        switch (code)
        {
            case FlatCfgErrorCode::kNotInitialized:
            {
                retVal = "FlatCfg was not initialized before another function was called";
                break;
            }
            case FlatCfgErrorCode::kGeneric:
            {
                retVal = "Generic internal error";
                break;
            }
            case FlatCfgErrorCode::kParameter:
            {
                retVal = "Parameter error";
                break;
            }
            case FlatCfgErrorCode::kInvalidConfigPath:
            {
                retVal = "Root path to the configuration files is invalid";
                break;
            }
            case FlatCfgErrorCode::kInvalidFileName:
            {
                retVal = "Found filename that is not conform to the rules";
                break;
            }
            case FlatCfgErrorCode::kConfigFiles:
            {
                retVal = "Handling the config files resulted in an error";
                break;
            }
            case FlatCfgErrorCode::kMultipleProcessesInPath:
            {
                retVal = "Configuration folder contains configurations for more than one process";
                break;
            }
            case FlatCfgErrorCode::kMemoryAllocationFailed:
            {
                retVal = "Failed to allocate memory";
                break;
            }
            case FlatCfgErrorCode::kMemoryAlreadyAllocated:
            {
                retVal = "Memory is already allocated";
                break;
            }
            case FlatCfgErrorCode::kInvalidSWCLName:
            {
                retVal = "Invalid SWCluster name";
                break;
            }
            case FlatCfgErrorCode::kFileNotFound:
            {
                retVal = "File not found";
                break;
            }
            case FlatCfgErrorCode::kFileEmpty:
            {
                retVal = "File is empty";
                break;
            }
            case FlatCfgErrorCode::kFileAccessError:
            {
                retVal = "File access error";
                break;
            }            
            case FlatCfgErrorCode::kUnknown:
            default:
            {
                retVal = "An unknown error occurred";
                break;
            }
        }
        return retVal;
    }
    void ThrowAsException(ara::core::ErrorCode const& errorCode) const noexcept(false) override { (void)errorCode; }
};

namespace global
{
static const FlatCfgErrorDomain g_flatcfgErrorDomain;
}

inline constexpr ara::core::ErrorDomain const& GetFlatCfgDomain() noexcept { return global::g_flatcfgErrorDomain; }

inline constexpr ara::core::ErrorCode MakeErrorCode(FlatCfgErrorCode code,
                                                    ara::core::ErrorDomain::SupportDataType data) noexcept
{
    return ara::core::ErrorCode(static_cast<ara::core::ErrorDomain::CodeType>(code), GetFlatCfgDomain(), data);
}

} // flatcfg
#endif /* FLATCFG_ERROR_H */
