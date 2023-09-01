//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/error_domain.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks


// Error domains assigned numbers
//
// UCM_ErrorDomainSystem       - 0x8830300000000001 * SYS
// UCM_ErrorDomainGeneric      - 0x8830300000000002 * ucm
// UCM_LIB_BUF_ErrorDomain     - 0x8830300000000022 * ucm::lib::buf
// UCM_LIB_PKG_BIN_ErrorDomain - 0x8830300000000083 * ucm::lib::pkg::bin
//

#ifndef UCM_AAP_LIBRARY__UCM__ERROR_DOMAIN_H_
#define UCM_AAP_LIBRARY__UCM__ERROR_DOMAIN_H_

#include <cstdint>
#include <exception>

#include "ucm/error_types.h"

namespace bosch {
namespace vrte  {
namespace ucm   {


#if defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wnon-virtual-dtor"
#endif

/// @brief Encapsulation of an error domain.
///
/// An error domain is the controlling entity for ErrorCode's error code values,
/// and defines the mapping of such error code values to textual representations.
///
/// This class is a literal type, and subclasses are strongly advised
/// to be literal types as well.
class ErrorDomain
{
public:

    ErrorDomain(      ErrorDomain&&) = delete;
    ErrorDomain(const ErrorDomain &) = delete;

    ErrorDomain& operator=(      ErrorDomain&&) = delete;
    ErrorDomain& operator=(const ErrorDomain &) = delete;

    /// @brief Returns the unique domain identifier.
    /// @returns the identifier
    constexpr err::id_type id() const noexcept
    {
        return id_;
    }

    /// @brief Returns the name of this error domain.
    ///
    /// The returned pointer remains owned by class ErrorDomain and
    /// shall not be freed by clients.
    ///
    /// @returns the name as a null-terminated string, never nullptr
    virtual char const* name() const noexcept = 0;

    /// @brief Returns a textual representation of the given error code.
    ///
    /// It is a Violation if the errorCode did not originate from this error
    /// domain.
    /// The returned pointer remains owned by the ErrorDomain subclass and
    /// shall not be freed by clients.
    ///
    /// @param value  the domain-specific error code value
    /// @returns the text as a null-terminated string, never nullptr
    virtual char const* message(err::value_type value) const noexcept = 0;

    /// @brief Compares for equality with another ErrorDomain instance.
    ///
    /// Two ErrorDomain instances compare equal when their identifiers
    /// (returned by id()) are equal.
    ///
    /// @param other  the other instance
    /// @returns true if @a other is equal to *this, false otherwise
    constexpr bool operator==(const ErrorDomain& other) const noexcept
    {
        return id() == other.id();
    }

    /// @brief Compares for non-equality with another ErrorDomain instance.
    /// @param other  the other instance
    /// @returns true if @a other is not equal to *this, false otherwise
    constexpr bool operator!=(const ErrorDomain& other) const noexcept
    {
        return id() != other.id();
    }

protected:
    /// @brief Constructs a new instance with the given identifier.
    ///
    /// Identifiers are expected to be system-wide unique.
    ///
    /// @param id  the unique identifier
    constexpr explicit ErrorDomain(err::id_type id) noexcept
        : id_{id}
    {}

    /// @brief Destructor
    ///
    /// This dtor is non-virtual (and trivial) so that this class is a literal type.
    /// While we do have virtual functions, we never need polymorphic destruction.
    ~ErrorDomain() = default;

private:
    const err::id_type id_;
};

#if defined(__GNUC__)
#pragma GCC diagnostic pop
#endif

}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif    // UCM_AAP_LIBRARY__UCM__ERROR_DOMAIN_H_
