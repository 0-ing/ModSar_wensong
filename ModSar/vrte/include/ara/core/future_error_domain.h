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

/// @file future_error_domain.h
/// @brief Error domain for errors originating from classes Future and Promise.
//===============================================================================

#ifndef ARA_CORE_FUTURE_ERROR_DOMAIN_H_
#define ARA_CORE_FUTURE_ERROR_DOMAIN_H_

#include <cstdint>
#include <utility>

#include "ara/core/error_domain.h"
#include "ara/core/error_code.h"
#include "ara/core/exception.h"

namespace ara {
namespace core {

/// @brief Specifies the types of internal errors that can occur upon calling Future::get or Future::GetResult.
/// These definitions are equivalent to the ones from std::future_errc.
///
/// @traceid{SWS_CORE_00400}
/// @traceid{SWS_CORE_10900}
/// @traceid{SWS_CORE_10902}
/// @traceid{SWS_CORE_10903}
/// @traceid{SWS_CORE_10999}
enum class future_errc : ara::core::ErrorDomain::CodeType {
    broken_promise = 101,            ///< the asynchronous task abandoned its shared state
    future_already_retrieved = 102,  ///< the contents of the shared state were already accessed
    promise_already_satisfied = 103, ///< attempt to store a value into the shared state twice
    no_state = 104,                  ///< attempt to access Promise or Future without an associated state
};

/**
 * @brief Exception type thrown by Future/Promise classes
 *
 * @traceid{SWS_CORE_00411}
 * @traceid{SWS_CORE_10910}
 * @traceid{SWS_CORE_10911}
 * @traceid{SWS_CORE_10999}
 */
class FutureException : public Exception {
public:
    /**
     * @brief Construct a new future exception object containing an Error object.
     * @param err  the ErrorCode
     *
     * @traceid{SWS_CORE_00412}
     */
    explicit FutureException(ErrorCode err) noexcept : Exception(std::move(err)) {}
};

/**
 * @brief Error domain for errors originating from classes Future and Promise.
 * @domainid{0x8000'0000'0000'0013}
 *
 * @traceid{SWS_CORE_00011}
 * @traceid{SWS_CORE_00421}
 * @traceid{SWS_CORE_10400}
 * @traceid{SWS_CORE_10930}
 * @traceid{SWS_CORE_10931}
 * @traceid{SWS_CORE_10932}
 * @traceid{SWS_CORE_10950}
 * @traceid{SWS_CORE_10999}
 */
class FutureErrorDomain final : public ErrorDomain {
    /// @traceid{SWS_CORE_00010}
    constexpr static ErrorDomain::IdType kId = 0x8000000000000013;

public:
    /// @brief Alias for the error code value enumeration
    ///
    /// @traceid{SWS_CORE_00431}
    /// @traceid{SWS_CORE_10933}
    using Errc = future_errc;

    /// @brief Alias for the exception base class
    ///
    /// @traceid{SWS_CORE_00432}
    /// @traceid{SWS_CORE_10934}
    using Exception = FutureException;

    /// @brief Default constructor
    ///
    /// @traceid{SWS_CORE_00441}
    /// @traceid{SWS_CORE_00013}
    constexpr FutureErrorDomain() noexcept : ErrorDomain(kId) {}

    /// @brief Return the "shortname" ApApplicationErrorDomain.SN of this error domain.
    /// @returns "Future"
    ///
    /// @traceid{SWS_CORE_00442}
    /// @traceid{SWS_CORE_00013}
    /// @traceid{SWS_CORE_10951}
    char const* Name() const noexcept override { return "Future"; }

    /// @brief Translate an error code value into a text message.
    /// @param errorCode  the error code value
    /// @returns the text message, never nullptr
    ///
    /// @traceid{SWS_CORE_00443}
    char const* Message(ErrorDomain::CodeType errorCode) const noexcept override {
        Errc const code = static_cast<Errc>(errorCode);
        switch (code) {
            case Errc::broken_promise:
                return "broken promise";
            case Errc::future_already_retrieved:
                return "future already retrieved";
            case Errc::promise_already_satisfied:
                return "promise already satisfied";
            case Errc::no_state:
                return "no state associated with this future";
            default:
                return "unknown future error";
        }
    }

    /// @brief Throw the exception type corresponding to the given ErrorCode.
    /// @param errorCode  the ErrorCode instance
    ///
    /// @traceid{SWS_CORE_00444}
    void ThrowAsException(ErrorCode const& errorCode) const noexcept(false) override {
        /// @traceid{SWS_CORE_10953}
        ThrowOrTerminate<Exception>(errorCode);
    }
};

namespace internal {
constexpr FutureErrorDomain g_futureErrorDomain;
}  // namespace internal

/// @brief Obtain the reference to the single global FutureErrorDomain instance.
/// @returns reference to the FutureErrorDomain instance
///
/// @traceid{SWS_CORE_00480}
/// @traceid{SWS_CORE_10980}
/// @traceid{SWS_CORE_10981}
/// @traceid{SWS_CORE_10982}
/// @traceid{SWS_CORE_10999}
constexpr ErrorDomain const& GetFutureErrorDomain() noexcept { return internal::g_futureErrorDomain; }

/// @brief Create a new ErrorCode for FutureErrorDomain with the given support data type.
/// @param code  an enumeration value from future_errc
/// @param data  a vendor-defined supplementary value
/// @returns the new ErrorCode instance
///
/// @traceid{SWS_CORE_00490}
/// @traceid{SWS_CORE_10990}
/// @traceid{SWS_CORE_10991}
/// @traceid{SWS_CORE_10999}
constexpr ErrorCode MakeErrorCode(future_errc code, ErrorDomain::SupportDataType data) noexcept {
    return ErrorCode(static_cast<ErrorDomain::CodeType>(code), GetFutureErrorDomain(), data);
}
}  // namespace core
}  // namespace ara

#endif  // ARA_CORE_FUTURE_ERROR_DOMAIN_H_
