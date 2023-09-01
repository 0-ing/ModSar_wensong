//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/error.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY__UCM__ERROR_H_
#define UCM_AAP_LIBRARY__UCM__ERROR_H_

#include <type_traits>
#include <system_error>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ara/core/result.h"
#include "ara/core/string_view.h"

#include "ucm/error_code.h"
#include "ucm/system_error.h"
#include "ucm/generic_error.h"
#include "ucm/lib/utl/source_location.h"

namespace bosch {
namespace vrte  {
namespace ucm   {

/// @brief UCM error class.
class Error
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test__ucm__Error, CTor);
#endif

public:
    using Code     = ErrorCode;
    using Value    = err::value_type;
    using Domain   = ErrorDomain;
    using Context  = std::uint64_t;
    using Message  = ::ara::core::StringView;
    using Location = lib::utl::source_location;

    template<typename _Value,
        std::enable_if_t<std::is_enum<_Value>::value, bool> = true>
    constexpr explicit
    Error(const _Value& evalue,
          const Message& message = Message{""},
          const Context& context = 0,
          const Location& location = Location::current()) noexcept
        : code_{evalue}
        , message_{message}
        , context_{context}
        , location_{location}
    {}

    constexpr explicit
    Error(int syserr,
          const Domain& domain = sys::UCM_ErrorDomainSystem(),
          const Message& message = Message{""},
          const Context& context = 0,
          const Location& location = Location::current()) noexcept
        : code_{syserr, domain}
        , message_{message}
        , context_{context}
        , location_{location}
    {}

    constexpr explicit
    Error(const Value& evalue,
          const Domain& domain,
          const Message& message = Message{""},
          const Context& context = 0,
          const Location& location = Location::current()) noexcept
        : code_{evalue, domain}
        , message_{message}
        , context_{context}
        , location_{location}
    {}

    constexpr explicit
    Error(const Code&     code,
          const Message&  message = Message{""},
          const Context&  context = 0,
          const Location& location = Location::current()) noexcept
        : code_{code}
        , message_{message}
        , context_{context}
        , location_{location}
    {}

    constexpr Error(Error     &&) noexcept = default;
    constexpr Error(Error const&) noexcept = default;

    Error& operator=(      Error&&) noexcept = delete;
    Error& operator=(const Error &) noexcept = delete;

    ~Error() = default;

    constexpr auto& code()     const noexcept;
    constexpr auto& value()    const noexcept;
    constexpr auto& message()  const noexcept;
    constexpr auto& context()  const noexcept;
    constexpr auto& location() const noexcept;

    constexpr explicit operator bool() const noexcept
    {
        return !(code_.value() == 0);
    }

private:
    Code     code_;         // error_code
    Message  message_;      // prefix clause
    Context  context_;      // execution context
    Location location_;     // source_location
};

inline constexpr auto& Error::code() const noexcept
{
    return code_;
}

inline constexpr auto& Error::value() const noexcept
{
    return code().value();
}

inline constexpr auto& Error::message() const noexcept
{
    return message_;
}

inline constexpr auto& Error::context() const noexcept
{
    return context_;
}

inline constexpr auto& Error::location() const noexcept
{
    return location_;
}

inline bool operator==(const Error& lhs, const Error& rhs)
{
    return lhs.code() == rhs.code();
}

inline bool operator!=(const Error& lhs, const Error& rhs)
{
    return !(lhs == rhs);
}

inline bool operator==(const Error& lhs, const ErrorCode& rhs)
{
    return lhs.code() == rhs;
}

inline bool operator!=(const Error& lhs, const ErrorCode& rhs)
{
    return !(lhs == rhs);
}

inline bool operator==(const ErrorCode& lhs, const Error& rhs)
{
    return lhs == rhs.code();
}

inline bool operator!=(const ErrorCode& lhs, const Error& rhs)
{
    return !(lhs == rhs);
}


}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif    // UCM_AAP_LIBRARY__UCM__ERROR_H_
