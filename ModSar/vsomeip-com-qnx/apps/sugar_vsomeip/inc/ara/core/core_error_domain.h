//==============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
/// @copyright (c) 2021-2022 by Robert Bosch GmbH. All rights reserved.
//
// The reproduction, distribution and utilization of this file as
// well as the communication of its contents to others without express
// authorization is prohibited. Offenders will be held liable for the
// payment of damages. All rights reserved in the event of the grant
// of a patent, utility model or design.
//==============================================================================

/// @file core_error_domain.h
/// @brief An error domain for errors originating from the CORE Functional Cluster.
//==================================================================================

#ifndef ARA_CORE_CORE_ERROR_DOMAIN_H_
#define ARA_CORE_CORE_ERROR_DOMAIN_H_

#include <cerrno>

#include "ara/core/error_code.h"
#include "ara/core/error_domain.h"
#include "ara/core/exception.h"

namespace ara {
namespace core {

/// @brief An enumeration with errors that can occur within this Functional Cluster
///
/// @traceid{SWS_CORE_05200}
/// @traceid{SWS_CORE_10900}
/// @traceid{SWS_CORE_10901}
/// @traceid{SWS_CORE_10902}
/// @traceid{SWS_CORE_10903}
/// @traceid{SWS_CORE_10999}
enum class CoreErrc : ErrorDomain::CodeType {
    kInvalidArgument = 22,            ///< invalid argument
    kInvalidMetaModelShortname = 137, ///< given string is not a valid model element shortname
    kInvalidMetaModelPath = 138,      ///< missing or invalid path to model element
};

/// @brief Exception type thrown for CORE errors.
///
/// @traceid{SWS_CORE_05211}
/// @traceid{SWS_CORE_10910}
/// @traceid{SWS_CORE_10911}
/// @traceid{SWS_CORE_10999}
class CoreException : public Exception {
public:
    /// @brief Construct a new CoreException from an ErrorCode.
    /// @param err  the ErrorCode
    ///
    /// @traceid{SWS_CORE_05212}
    explicit CoreException(ErrorCode err) noexcept : Exception(err) {}
};

/// @brief An error domain for ara::core errors.
/// @domainid{0x8000'0000'0000'0014}
///
/// @traceid{SWS_CORE_00011}
/// @traceid{SWS_CORE_05221}
/// @traceid{SWS_CORE_10400}
/// @traceid{SWS_CORE_10930}
/// @traceid{SWS_CORE_10931}
/// @traceid{SWS_CORE_10932}
/// @traceid{SWS_CORE_10950}
/// @traceid{SWS_CORE_10999}
class CoreErrorDomain final : public ErrorDomain {
    /// @traceid{SWS_CORE_00010}
    constexpr static ErrorDomain::IdType kId = 0x8000000000000014;

public:
    /// @brief Alias for the error code value enumeration
    ///
    /// @traceid{SWS_CORE_05231}
    /// @traceid{SWS_CORE_10933}
    using Errc = CoreErrc;

    /// @brief Alias for the exception base class
    ///
    /// @traceid{SWS_CORE_05232}
    /// @traceid{SWS_CORE_10934}
    using Exception = CoreException;

    /// @brief Default constructor
    ///
    /// @traceid{SWS_CORE_05241}
    /// @traceid{SWS_CORE_00014}
    constexpr CoreErrorDomain() noexcept : ErrorDomain(kId) {}

    /// @brief Return the "shortname" ApApplicationErrorDomain.SN of this error domain.
    /// @returns "Core"
    ///
    /// @traceid{SWS_CORE_05242}
    /// @traceid{SWS_CORE_00014}
    /// @traceid{SWS_CORE_10951}
    char const* Name() const noexcept override { return "Core"; }

    /// @brief Translate an error code value into a text message.
    /// @param errorCode  the error code value
    /// @returns the text message, never nullptr
    ///
    /// @traceid{SWS_CORE_05243}
    char const* Message(ErrorDomain::CodeType errorCode) const noexcept override {
        Errc const code = static_cast<Errc>(errorCode);
        switch (code) {
            case Errc::kInvalidArgument:
                return "Invalid argument";
            case Errc::kInvalidMetaModelShortname:
                return "Invalid meta model shortname";
            case Errc::kInvalidMetaModelPath:
                return "Invalid meta model path";
            default:
                return "Unknown error";
        }
    }

    /// @brief Throws the exception type corresponding to the given ErrorCode.
    /// @param errorCode  the ErrorCode instance
    ///
    /// @traceid{SWS_CORE_05244}
    void ThrowAsException(ErrorCode const& errorCode) const noexcept(false) override {
        /// @traceid{SWS_CORE_10953}
        ThrowOrTerminate<Exception>(errorCode);
    }
};

namespace internal {
constexpr CoreErrorDomain g_coreErrorDomain;
}  // namespace internal

/// @brief Return a reference to the global CoreErrorDomain.
/// @returns the CoreErrorDomain
///
/// @traceid{SWS_CORE_05280}
/// @traceid{SWS_CORE_10980}
/// @traceid{SWS_CORE_10981}
/// @traceid{SWS_CORE_10982}
/// @traceid{SWS_CORE_10999}
constexpr ErrorDomain const& GetCoreErrorDomain() noexcept { return internal::g_coreErrorDomain; }

/// @brief Create a new ErrorCode within CoreErrorDomain.
///
/// This function is used internally by constructors of ErrorCode.
///
/// @param code  the CoreErrorDomain-specific error code value
/// @param data  optional vendor-specific error data
/// @returns a new ErrorCode instance
///
/// @traceid{SWS_CORE_05290}
/// @traceid{SWS_CORE_10990}
/// @traceid{SWS_CORE_10991}
/// @traceid{SWS_CORE_10999}
constexpr ErrorCode MakeErrorCode(CoreErrc code, ErrorDomain::SupportDataType data) noexcept {
    return ErrorCode(static_cast<ErrorDomain::CodeType>(code), GetCoreErrorDomain(), data);
}

}  // namespace core
}  // namespace ara

#endif  // ARA_CORE_CORE_ERROR_DOMAIN_H_
