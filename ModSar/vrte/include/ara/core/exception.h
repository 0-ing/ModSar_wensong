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

/// @file exception.h
/// @brief Base type for all AUTOSAR exception types.
//==============================================================================

#ifndef ARA_CORE_EXCEPTION_H_
#define ARA_CORE_EXCEPTION_H_

#include <exception>
#include <system_error>
#include <utility>
#include <ostream>

#include "ara/core/error_code.h"
#include "ara/core/string.h"

namespace ara {
namespace core {

/// @defgroup ARA_CORE_EXCEPTION Exception data type
/// @brief Base type for all AUTOSAR exception types
///
/// @traceid{SWS_CORE_00601}
class Exception : public std::exception {
    ErrorCode error_code_;

public:
    /// @brief Construct a new Exception object with a specific ErrorCode.
    /// @param err  the ErrorCode
    ///
    /// @traceid{SWS_CORE_00611}
    explicit Exception(ErrorCode err) noexcept : error_code_(std::move(err)) {}

    /// @brief Return the embedded ErrorCode that was given to the constructor.
    /// @returns reference to the embedded ErrorCode
    ///
    /// @traceid{SWS_CORE_00613}
    ErrorCode const& Error() const noexcept { return error_code_; }

    /// @brief Return the explanatory string.
    ///
    /// This function overrides the virtual function std::exception::what.
    /// All guarantees about the lifetime of the returned pointer
    /// that are given for std::exception::what are preserved.
    ///
    /// @returns a null-terminated string
    ///
    /// @traceid{SWS_CORE_00612}
    char const* what() const noexcept override {
        return error_code_.Domain().Message(error_code_.Value());
    }

protected:
    /// @brief Copy-assign another Exception to this instance.
    /// @param other  the other instance
    /// @returns *this, containing the contents of @a other
    ///
    /// @traceid{SWS_CORE_00614}
    Exception& operator=(Exception const& other) = default;
};

}  // namespace core
}  // namespace ara

#endif  // ARA_CORE_EXCEPTION_H_
