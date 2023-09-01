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

/// @file optional_error.h
/// @brief Error handling for Optional class.
//==============================================================================

#ifndef ARA_CORE_OPTIONAL_ERROR_H_
#define ARA_CORE_OPTIONAL_ERROR_H_

#include <utility>

#include "ara/core/error_domain.h"
#include "ara/core/error_code.h"
#include "ara/core/exception.h"

namespace ara {
namespace core {

class ErrorCode;

enum class optional_errc : ErrorDomain::CodeType { bad_access = 1 };

/**
 * @brief Exception type thrown by Optional class
 */
class OptionalException : public Exception {
public:
    /**
     * @brief Construct a new optional exception object containing an Error object.
     */
    explicit OptionalException(ErrorCode&& err) noexcept : Exception(std::move(err)) {}
};

#if defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wnon-virtual-dtor"
#endif

class OptionalErrorDomain : public ErrorDomain {
    constexpr static ErrorDomain::IdType kId = 0x6F7074696F6E616C;

public:
    using Errc = optional_errc;
    using Exception = OptionalException;

    constexpr OptionalErrorDomain() noexcept : ErrorDomain(kId) {}

    char const* Name() const noexcept override { return "Optional"; }

    char const* Message(ErrorDomain::CodeType errorCode) const noexcept override {
        optional_errc const code = static_cast<optional_errc>(errorCode);
        switch (code) {
            case optional_errc::bad_access:
                return "Accessing an optional object that does not contain a value";
            default:
                return "Unknown error";
        }
    }

    void ThrowAsException(ErrorCode const& errorCode) const noexcept(false) override {
        ThrowOrTerminate<Exception>(errorCode);
    }
};

namespace internal {
constexpr OptionalErrorDomain g_optionalErrorDomain;
}  // namespace internal

inline constexpr ErrorDomain const& GetOptionalDomain() { return internal::g_optionalErrorDomain; }

inline constexpr ErrorCode MakeErrorCode(optional_errc code, ErrorDomain::SupportDataType data, char const* = "") {
    return ErrorCode(static_cast<ErrorDomain::CodeType>(code), GetOptionalDomain(), data);
}

}  // namespace core
}  // namespace ara

#endif  // ARA_CORE_OPTIONAL_ERROR_H_
