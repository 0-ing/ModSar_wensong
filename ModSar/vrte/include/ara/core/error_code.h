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

/// @file error_code.h
/// @brief Encapsulation of an error code.
//==============================================================================

#ifndef ARA_CORE_ERROR_CODE_H_
#define ARA_CORE_ERROR_CODE_H_

#include <ostream>
#include <cstdint>
#include <utility>
#include <exception>
#include <type_traits>

#include "ara/core/error_domain.h"
#include "ara/core/string_view.h"

namespace ara {
namespace core {

/// @brief Encapsulation of an error code
///
/// An ErrorCode contains a raw error code value and an error domain.
/// The raw error code value is specific to this error domain.
///
/// @traceid{SWS_CORE_00501}
/// @traceid{SWS_CORE_10300}
class ErrorCode final {
    friend std::ostream& operator<<(std::ostream& out, ErrorCode const& e) {
        return (out << e.mDomain->Name() << ":" << e.mValue << ":" << e.mSupportData);
    }

    using CodeType = ErrorDomain::CodeType;
    using SupportDataType = ErrorDomain::SupportDataType;

public:
    /// @brief Constructs a new ErrorCode instance with parameters.
    ///
    /// This constructor does not participate in overload resolution unless @a EnumT
    /// is an enum type.
    ///
    /// @tparam EnumT  an enum type that contains error code values
    /// @param e  a domain-specific error code value
    /// @param data  optional vendor-specific supplementary error context data
    ///
    /// @traceid{SWS_CORE_00512}
    template <typename EnumT, typename = typename std::enable_if<std::is_enum<EnumT>::value>::type>
    constexpr ErrorCode(EnumT e, SupportDataType data = 0) noexcept
        // Call MakeErrorCode() unqualified, so the correct overload is found via ADL.
        : ErrorCode(MakeErrorCode(e, data)) {}

    /// @brief Constructs a new ErrorCode instance with parameters.
    ///
    /// @param value  a domain-specific error code value
    /// @param domain  the ErrorDomain associated with @a value
    /// @param data  optional vendor-specific supplementary error context data
    ///
    /// @traceid{SWS_CORE_00513}
    constexpr ErrorCode(CodeType value, ErrorDomain const& domain, SupportDataType data = 0) noexcept
        : mValue(value), mSupportData(data), mDomain(&domain) {}

    /// @brief Returns the raw error code value.
    /// @returns the raw error code value
    ///
    /// @traceid{SWS_CORE_00514}
    constexpr CodeType Value() const noexcept { return mValue; }

    /// @brief Returns the supplementary error context data.
    ///
    /// The underlying type and the meaning of the returned value are implementation-defined.
    ///
    /// @returns the supplementary error context data
    ///
    /// @traceid{SWS_CORE_00516}
    constexpr SupportDataType SupportData() const noexcept { return mSupportData; }

    /// @brief Returns the domain with which this ErrorCode is associated.
    /// @returns the ErrorDomain
    ///
    /// @traceid{SWS_CORE_00515}
    constexpr ErrorDomain const& Domain() const noexcept { return *mDomain; }

    /// @brief Returns a textual representation of this ErrorCode.
    /// @returns the error message text
    ///
    /// @traceid{SWS_CORE_00518}
    StringView Message() const noexcept { return Domain().Message(Value()); }

    /// @brief Throws this error as exception.
    ///
    /// This function will determine the appropriate exception type for
    /// this ErrorCode and throw it. The thrown exception will contain this
    /// ErrorCode.
    ///
    /// @traceid{SWS_CORE_00519}
    [[noreturn]] void ThrowAsException() const noexcept(false) {
        Domain().ThrowAsException(*this);

        // Never reached, but apparently needed to avoid warnings from certain compilers (such as 5.4.0).
        std::terminate();
    }

private : CodeType mValue;
    SupportDataType mSupportData;
    ErrorDomain const* mDomain;  // non-owning pointer to the associated ErrorDomain
};

/// @brief Global operator== for ErrorCode
///
/// Two ErrorCode instances compare equal if the results of their Value() and
/// Domain() functions are equal. The result of SupportData()
/// is not considered for equality.
///
/// @param lhs  the left hand side of the comparison
/// @param rhs  the right hand side of the comparison
/// @returns true if the two instances compare equal, false otherwise
///
/// @traceid{SWS_CORE_00571}
constexpr bool operator==(ErrorCode const& lhs, ErrorCode const& rhs) noexcept {
    return lhs.Domain() == rhs.Domain() && lhs.Value() == rhs.Value();
}

/// @brief Global operator!= for ErrorCode
///
/// Two ErrorCode instances compare equal if the results of their Value() and
/// Domain() functions are equal. The result of SupportData()
/// is not considered for equality.
///
/// @param lhs  the left hand side of the comparison
/// @param rhs  the right hand side of the comparison
/// @returns true if the two instances compare not equal, false otherwise
///
/// @traceid{SWS_CORE_00572}
constexpr bool operator!=(ErrorCode const& lhs, ErrorCode const& rhs) noexcept {
    return lhs.Domain() != rhs.Domain() || lhs.Value() != rhs.Value();
}

template <typename ExceptionType>
[[noreturn]] void ThrowOrTerminate(ErrorCode errorCode) {
#ifndef ARA_NO_EXCEPTIONS
    throw ExceptionType(std::move(errorCode));
#else
    (void) errorCode;
    std::terminate();
#endif
}

}  // namespace core
}  // namespace ara

#endif  // ARA_CORE_ERROR_CODE_H_
