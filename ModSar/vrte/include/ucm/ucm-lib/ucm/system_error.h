//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/system_error.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY__UCM_SYS__SYSTEM_ERROR_H_
#define UCM_AAP_LIBRARY__UCM_SYS__SYSTEM_ERROR_H_

#include "ucm/error_code.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace sys   {

#if defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wnon-virtual-dtor"
#endif

class UCM_ErrorDomainSystem : public ErrorDomain
{
    constexpr static err::id_type kId = 0x8830500000000001;

public:
    constexpr explicit UCM_ErrorDomainSystem() noexcept
        : ErrorDomain(kId)
    {}

    virtual char const* name() const noexcept override;

    virtual char const* message(err::value_type value) const noexcept override;
};

#if defined(__GNUC__)
#pragma GCC diagnostic pop
#endif

namespace internal {
constexpr UCM_ErrorDomainSystem ucm_error_domain_system;
}   // namespace internal

constexpr const ErrorDomain& UCM_ErrorDomainSystem_Get() noexcept
{
    return internal::ucm_error_domain_system;
}

constexpr ErrorCode make_error_code(int ev) noexcept
{
    return ErrorCode(static_cast<err::value_type>(ev),
                     UCM_ErrorDomainSystem_Get());
}

}    // namespace sys
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch


#endif    // UCM_AAP_LIBRARY__UCM_SYS__SYSTEM_ERROR_H_
