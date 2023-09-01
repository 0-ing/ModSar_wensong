//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/generic_error.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY__UCM__GENERIC_ERROR_H_
#define UCM_AAP_LIBRARY__UCM__GENERIC_ERROR_H_

#include "ucm/error_code.h"
#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

namespace bosch {
namespace vrte  {
namespace ucm   {

enum class ErrorValue : err::value_type
{
    kSuccess,
    kFailure,
    kBadRealloc,        ///< Operation will cause realloc
    kContinuation,      ///< An intermediate result is OK
};

#if defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wnon-virtual-dtor"
#endif

class UCM_ErrorDomainGeneric : public ErrorDomain
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test__ucm__UCM_ErrorDomainGeneric, CTor);
#endif
    constexpr static err::id_type kId = 0x8830300000000002;

public:
    constexpr explicit UCM_ErrorDomainGeneric() noexcept
        : ErrorDomain(kId)
    {}

    virtual char const* name() const noexcept override;

    virtual char const* message(err::value_type value) const noexcept override;
};

#if defined(__GNUC__)
#pragma GCC diagnostic pop
#endif

namespace internal {
constexpr UCM_ErrorDomainGeneric ucm_error_domain_generic;
}   // namespace internal

constexpr const ErrorDomain& UCM_ErrorDomainGeneric_Get() noexcept
{
    return internal::ucm_error_domain_generic;
}

constexpr ErrorCode make_error_code(ErrorValue ev) noexcept
{
    return ErrorCode(static_cast<err::value_type>(ev),
                     UCM_ErrorDomainGeneric_Get());
}

}    // namespace ucm
}    // namespace vrte
}    // namespace bosch


#endif    // UCM_AAP_LIBRARY__UCM__GENERIC_ERROR_H_
