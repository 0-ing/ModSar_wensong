//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/exception.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY__UCM__EXCEPTION_H_
#define UCM_AAP_LIBRARY__UCM__EXCEPTION_H_

#include <utility>
#include <exception>
#include <system_error>

#include "ucm/error_code.h"

namespace bosch {
namespace vrte  {
namespace ucm   {

/// @brief Base type for all AUTOSAR exception types
class Exception : public std::exception
{
public:
    /// @brief Construct a new Exception object with a specific ErrorCode.
    /// @param err  the ErrorCode
    explicit Exception(ErrorCode&& err) noexcept
        : error_code_(std::move(err))
    {}

    /// @brief Return the embedded ErrorCode that was given to the constructor.
    /// @returns reference to the embedded ErrorCode
    const ErrorCode& error_code() const noexcept
    {
        return error_code_;
    }

    /// @brief Return the explanatory string.
    ///
    /// This function overrides the virtual function std::exception::what.
    /// All guarantees about the lifetime of the returned pointer
    /// that are given for std::exception::what are preserved.
    ///
    /// @returns a null-terminated string
    char const* what() const noexcept override
    {
        return std::exception::what();
    }
private:
    const ErrorCode error_code_;
};

}    // namespace ucm
}    // namespace vrte
}    // namespace bosch


#endif    // UCM_AAP_LIBRARY__UCM__EXCEPTION_H_
