//==============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
/// @copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// The reproduction, distribution and utilization of this file as
// well as the communication of its contents to others without express
// authorization is prohibited. Offenders will be held liable for the
// payment of damages. All rights reserved in the event of the grant
// of a patent, utility model or design.
//==============================================================================

/// @file error_domain.h
/// @brief Encapsulation of an error domain.
//==============================================================================

#ifndef ARA_CORE_ERROR_DOMAIN_H_
#define ARA_CORE_ERROR_DOMAIN_H_

#include <cstdint>
#include <exception>

namespace ara {
namespace core {

#if defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wnon-virtual-dtor"
#endif

// forward declaration
class ErrorCode;

/// @brief Encapsulation of an error domain.
///
/// An error domain is the controlling entity for ErrorCode's error code values,
/// and defines the mapping of such error code values to textual representations.
///
/// This class is a literal type, and subclasses are strongly advised
/// to be literal types as well.
///
/// @traceid{SWS_CORE_00110}
/// @traceid{SWS_CORE_10400}
class ErrorDomain {
public:
    /// @brief Alias type for a unique ErrorDomain identifier type
    ///
    /// @traceid{SWS_CORE_00121}
    using IdType = std::uint64_t;

    /// @brief Alias type for a domain-specific error code value
    ///
    /// @traceid{SWS_CORE_00122}
    using CodeType = std::int32_t;

    /// @brief Alias type for vendor-specific supplementary data
    ///
    /// @traceid{SWS_CORE_00123}
    using SupportDataType = std::int32_t;

    /// @brief Copy construction is disabled.
    ///
    /// @traceid{SWS_CORE_00131}
    ErrorDomain(ErrorDomain const&) = delete;

    /// @brief Move construction is disabled.
    ///
    /// @traceid{SWS_CORE_00132}
    ErrorDomain(ErrorDomain&&) = delete;

    /// @brief Copy assignment is disabled.
    ///
    /// @traceid{SWS_CORE_00133}
    ErrorDomain& operator=(ErrorDomain const&) = delete;

    /// @brief Move assignment is disabled.
    ///
    /// @traceid{SWS_CORE_00134}
    ErrorDomain& operator=(ErrorDomain&&) = delete;

    /// @brief Returns the name of this error domain.
    ///
    /// The returned pointer remains owned by class ErrorDomain and
    /// shall not be freed by clients.
    ///
    /// @returns the name as a null-terminated string, never nullptr
    ///
    /// @traceid{SWS_CORE_00152}
    virtual char const* Name() const noexcept = 0;

    /// @brief Returns a textual representation of the given error code.
    ///
    /// It is a Violation if the errorCode did not originate from this error domain,
    /// and thus be subject to SWS_CORE_00003.
    ///
    /// The returned pointer remains owned by the ErrorDomain subclass and
    /// shall not be freed by clients.
    ///
    /// @param errorCode  the domain-specific error code
    /// @returns the text as a null-terminated string, never nullptr
    ///
    /// @traceid{SWS_CORE_00153}
    virtual char const* Message(CodeType errorCode) const noexcept = 0;

    /// @brief Throws the given errorCode as Exception
    /// @param errorCode error code to be thrown
    /// @remark if ARA_NO_EXCEPTIONS is defined, this function call will terminate.
    ///
    /// @traceid{SWS_CORE_00154}
    [[noreturn]] virtual void ThrowAsException(ErrorCode const& errorCode) const noexcept(false) = 0;

    /// @brief Returns the unique domain identifier.
    /// @returns the identifier
    ///
    /// @traceid{SWS_CORE_00151}
    /// @traceid{SWS_CORE_10952}
    constexpr IdType Id() const noexcept { return mId; }

    /// @brief Compares for equality with another ErrorDomain instance.
    ///
    /// Two ErrorDomain instances compare equal when their identifiers
    /// (returned by Id()) are equal.
    ///
    /// @param other  the other instance
    /// @returns true if @a other is equal to *this, false otherwise
    ///
    /// @traceid{SWS_CORE_00137}
    constexpr bool operator==(ErrorDomain const& other) const noexcept { return mId == other.mId; }

    /// @brief Compares for non-equality with another ErrorDomain instance.
    /// @param other  the other instance
    /// @returns true if @a other is not equal to *this, false otherwise
    ///
    /// @traceid{SWS_CORE_00138}
    constexpr bool operator!=(ErrorDomain const& other) const noexcept { return mId != other.mId; }

protected:
    /// @brief Constructs a new instance with the given identifier.
    ///
    /// Identifiers are expected to be system-wide unique.
    ///
    /// @param id  the unique identifier
    ///
    /// @traceid{SWS_CORE_00135}
    constexpr explicit ErrorDomain(IdType id) noexcept : mId(id) {}

    /// @brief Destructor
    ///
    /// This dtor is non-virtual (and trivial) so that this class is a literal type.
    /// While we do have virtual functions, we never need polymorphic destruction.
    ///
    /// @traceid{SWS_CORE_00136}
    ~ErrorDomain() = default;

private:
    IdType const mId;
};

#if defined(__GNUC__)
#pragma GCC diagnostic pop
#endif

}  // namespace core
}  // namespace ara

#endif  // ARA_CORE_ERROR_DOMAIN_H_
