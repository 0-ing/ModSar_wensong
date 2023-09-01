//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         tests/VRTE_UT/stdmocks/ucm/lib/buf/error.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY__UCM_LIB_BUF__ERROR_H_
#define UCM_AAP_LIBRARY__UCM_LIB_BUF__ERROR_H_

#include "ucm/error.h"
#include "ucm/error_code.h"

#include "ucm/mock/sequence.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace buf   {

/// @brief Error values associated with this Error domain.
enum class ErrorValue : err::value_type
{
    kSuccess,           ///< Result of operation is OK
    kFailure,           ///< Result of operation is KO
    kOverrun,          ///< The loaded data will overflow the container
    kUnderrun,         ///< The loaded data is not sufficient
    kInvalidBuff,       ///< Invalid internal buffer
};

#if defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wnon-virtual-dtor"
#endif

class UCM_LIB_BUF_ErrorDomain : public ErrorDomain
{
    constexpr static err::id_type kId = 0x8830300000000022;

public:
    constexpr explicit UCM_LIB_BUF_ErrorDomain() noexcept
        : ErrorDomain(kId)
    {}

    virtual char const* name() const noexcept override
    { return ""; }

    virtual char const* message(err::value_type) const noexcept override
    { return ""; }
};

#if defined(__GNUC__)
#pragma GCC diagnostic pop
#endif

namespace internal {
constexpr UCM_LIB_BUF_ErrorDomain ucm_buf_error_domain;
}   // namespace internal

constexpr const ErrorDomain& UCM_LIB_BUF_ErrorDomain_Get() noexcept
{
    return internal::ucm_buf_error_domain;
}

constexpr ErrorCode make_error_code(ErrorValue ev) noexcept
{
    return ErrorCode(static_cast<err::value_type>(ev),
                     UCM_LIB_BUF_ErrorDomain_Get());
}


}    // namespace buf
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif // UCM_AAP_LIBRARY__UCM_LIB_BUF__ERROR_H_
