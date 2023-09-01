//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/error_code.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY__UCM__ERROR_CODE_H_
#define UCM_AAP_LIBRARY__UCM__ERROR_CODE_H_

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/error_types.h"
#include "ucm/error_domain.h"

namespace bosch {
namespace vrte  {
namespace ucm   {

/// @brief Encapsulation of an error code
///
/// An ErrorCode contains a raw error code value and an error domain.
/// The raw error code value is specific to this error domain.
class ErrorCode
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test__ucm__ErrorCode, CTor);
#endif

public:
    /// @brief Constructs a new ErrorCode instance with parameters.
    ///
    /// This constructor does not participate in overload resolution unless
    /// @a _Value is an enum type.
    ///
    /// @tparam _Value  an enum type that contains error code values
    /// @param  errc  a domain-specific error code value
    template<typename _Value,
        std::enable_if_t<std::is_enum<_Value>::value, bool> = true>
    constexpr ErrorCode(_Value errc) noexcept
        : ErrorCode(make_error_code(errc))
    {
    }

    /// @brief Constructs a new ErrorCode instance with parameters.
    ///
    /// @param value  a domain-specific error code value
    /// @param domain  the ErrorDomain associated with @a value
    constexpr ErrorCode(err::value_type value,
                        const ErrorDomain& domain) noexcept
        : value_{value}
        , domain_{&domain}
    {
    }

    /// @brief Returns the raw error code value.
    /// @returns the raw error code value
    constexpr const auto& value() const noexcept
    {
        return value_;
    }

    /// @brief Returns the domain with which this ErrorCode is associated.
    /// @returns the ErrorDomain
    constexpr const auto& domain() const noexcept
    {
        return *domain_;
    }

    /// @brief Returns a textual representation of this ErrorCode.
    /// @returns the error message text
    const char* message() const noexcept
    {
        return domain().message(value());
    }

private:
    const err::value_type  value_;
    const ErrorDomain*     domain_;
};

inline bool operator==(const ErrorCode& lhs, const ErrorCode& rhs)
{
    return lhs.value() == rhs.value() && lhs.domain() == rhs.domain();
}

inline bool operator!=(const ErrorCode& lhs, const ErrorCode& rhs)
{
    return !(lhs == rhs);
}

}    // namespace ucm
}    // namespace vrte
}    // namespace bosch


#endif    // UCM_AAP_LIBRARY__UCM__ERROR_CODE_H_
