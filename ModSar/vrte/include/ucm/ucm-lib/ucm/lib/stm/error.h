//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/stm/error.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY__UCM_LIB_STM__ERROR_H_
#define UCM_AAP_LIBRARY__UCM_LIB_STM__ERROR_H_

#include <system_error>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/error.h"
#include "ucm/error_code.h"

/// @defgroup bosch_vrte_ucm_lib_stm__error__ut Error facility for STM
/// @ingroup bosch_vrte_ucm_lib_stm__ut
/// @{

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace stm   {

/// @brief Error codes returned by STM API
enum class ErrorValue : err::value_type
{
    kSuccess,       ///< State change OK
    kFailure,       ///< State change failed
    kPending,       ///< State change pending
    kTimeout,       ///< State change timeout
    kService,       ///< State change cannot happen as STM is unavailable
    kMissing,       ///< A required component was not found
    kWorking,       ///< An operation is already underway
    kMismatch,      ///< Mismatch between the request and response
    kInternal,      ///< Internal error
    kExternal,      ///< External error
    kInvalidState,  ///< Invalid FG State
    kDuplicate,     ///< A unique component is already created/registered
};

#if defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wnon-virtual-dtor"
#endif

/// @brief STM Error Domain class.
class STM_ErrorDomain : public ErrorDomain
{
    constexpr static err::id_type kId = 0x8830300000000043;

public:
    constexpr explicit STM_ErrorDomain() noexcept
        : ErrorDomain(kId)
    {}

    /// @brief Return name of the error domain.
    virtual char const* name() const noexcept override;

    /// @brief Translate an error value to error message for this domain.
    virtual char const* message(err::value_type value) const noexcept override;
};

#if defined(__GNUC__)
#pragma GCC diagnostic pop
#endif

namespace internal {
constexpr STM_ErrorDomain stm_error_domain;
}   // namespace internal

/// @brief Return a reference to the STM error domain
constexpr const ErrorDomain& get_error_domain() noexcept
{
    return internal::stm_error_domain;
}

/// @brief Construct an \ref ErrorCode from \ref ErrorValue
constexpr ErrorCode make_error_code(ErrorValue ev) noexcept
{
    return ErrorCode(static_cast<err::value_type>(ev), get_error_domain());
}

}    // namespace stm
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif    // UCM_AAP_LIBRARY__UCM_LIB_STM__ERROR_H_
