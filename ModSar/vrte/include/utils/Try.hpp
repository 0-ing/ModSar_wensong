//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file      Try.hpp
/// @brief     Header providing the "TRY" macros
/// @copyright Robert Bosch GmbH  2018
/// @author    Arnaud Riess

#ifndef UTILS_TRY_HPP_INCLUDED
#define UTILS_TRY_HPP_INCLUDED

#include "log/Log.hpp"
#include "utils/StdReturnType.hpp"

/// @brief The TRY macro can be used to check if an expression of type StdReturnType is
/// an error, and if it is, it automatically returns that error. This is useful
/// for propagating errors outwards without all the verbosity.
///
/// Example:
///
/// StdReturnType SomeFunction()
/// {
///     // If either of these functions error out, we simply propagate it outwards.
///     TRY(SomePossiblyErroringFunction());
///     TRY(SomeOtherPossiblyErroringFunction());
///
///     // They did not error out, run some other code.
///     /* Some other code */
///
///     // We never errored, so we return without an error.
///     return StdReturnType::OK;
/// }
// PRQA MS "TRY" 4127 # No further check required for arguments within TRY statement
#define TRY(result)                                  \
    do                                               \
    {                                                \
        const ::exm::StdReturnType actualResult = (result); \
        if (actualResult != ::exm::StdReturnType::OK)       \
        {                                            \
            return actualResult;                     \
        }                                            \
    } while (0)

/// @brief The TRY_MSG macro can be used to check if an expression of type StdReturnType is
/// an error, and if it is, it automatically logs an error message and returns that error. This is
/// useful for propagating errors outwards without all the verbosity.
// PRQA MS "TRY_MSG" 4127 # No further check required for arguments within TRY statement
#define TRY_MSG(result, msg, ...)                    \
    do                                               \
    {                                                \
        const ::exm::StdReturnType actualResult = (result); \
        if (actualResult != ::exm::StdReturnType::OK)       \
        {                                            \
            ::exm::log::Log(::exm::Severity::ERROR, msg, ##__VA_ARGS__);     \
            return actualResult;                     \
        }                                            \
    } while (0)

/// @brief Checks an argument validty. If the condition fails, then StdReturnType::INVALID_ARGUMENTS
/// is returned.
#define ASSERT_ARG(condition)                        \
    do                                               \
    {                                                \
        if (!(condition))                            \
        {                                            \
            return ::exm::StdReturnType::INVALID_ARGUMENTS; \
        }                                            \
    } while (0)


#endif
