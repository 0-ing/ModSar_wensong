//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/pkg/bin/error.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY__UCM_LIB_PKG_BIN__ERROR_H_
#define UCM_AAP_LIBRARY__UCM_LIB_PKG_BIN__ERROR_H_

#include <system_error>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/error.h"
#include "ucm/error_code.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace pkg   {
namespace bin   {


enum class ErrorValue : err::value_type
{
    kSuccess,           ///< Result of operation is OK
    kFailure,           ///< Result of operation is KO
    kMissing,           ///< A required component is missing
    kSecurity,          ///< Security has not been set for the SWP service
    kOverflow,          ///< The loaded data will overflow the container
    kUnderflow,         ///< The loaded data is not sufficient
    kAuthTagSec,        ///< Failed to verify AuthTag
    kAuthTagFmt,        ///< Bad format of the AuthTag
    kInvalidBuff,       ///< Invalid internal buffer
    kInvalidSize,       ///< Invalid size of a buffer
    kInvalidState,      ///< Invalid internal state for SWP subsystem
    kInvalidField,      ///< A parsed or calculated field holds invalid value
    kGroupMismatch,     ///< Expected and read group mismatch
    kMissingManifest,   ///< Manifest is missing from SWP
    kMissingArtefact,   ///< Artefact is missing from SWP
    kSequenceMismatch,  ///< Expected and read sequence mismatch
};

#if defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wnon-virtual-dtor"
#endif

class UCM_LIB_PKG_BIN_ErrorDomain : public ErrorDomain
{
    constexpr static err::id_type kId = 0x8830300000000083;

public:
    constexpr explicit UCM_LIB_PKG_BIN_ErrorDomain() noexcept
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
constexpr UCM_LIB_PKG_BIN_ErrorDomain pkg_bin_error_domain;
}   // namespace internal

constexpr const ErrorDomain& get_error_domain() noexcept
{
    return internal::pkg_bin_error_domain;
}

constexpr ErrorCode make_error_code(ErrorValue ev) noexcept
{
    return ErrorCode(static_cast<err::value_type>(ev), get_error_domain());
}

}    // namespace bin
}    // namespace pkg
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif    // UCM_AAP_LIBRARY__UCM_LIB_PKG_BIN__ERROR_H_
