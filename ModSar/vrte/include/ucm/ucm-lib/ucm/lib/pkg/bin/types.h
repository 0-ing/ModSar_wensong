//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/pkg/bin/types.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY__UCM_LIB_PKG_BIN__TYPES_H_
#define UCM_AAP_LIBRARY__UCM_LIB_PKG_BIN__TYPES_H_

#include <string>
#include <cstddef>

#include "ucm/types.h"
#include "ucm/lib/utl/cast.h"
#include "ucm/lib/utl/offset.h"
#include "ucm/lib/pkg/bin/error.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace pkg   {
namespace bin   {

using size_type = std::size_t;


template<typename T, typename U>
static Error conv_value(T& dst, U& src) noexcept
{
    try {
        dst = lib::utl::cast<T>(src);
    }
    catch (...) {
        return Error(ErrorValue::kInvalidField);
    }
    return Error(ErrorValue::kSuccess);
}

using iofile_offset = utl::Offset<off_t>;
using memory_offset = utl::Offset<size_type>;

/// @brief File pair type.
///
/// std::get<0> - file name
/// std::get<1> - file type
///
/// type == "ucms_manifest"     : UCMS manifest
/// type == "ucms_binaryimage"  : UCMS binary image
/// type == "ucms_application"  : UCMS tar application
using sfile_pair = std::pair<std::string, std::string>;

}    // namespace bin
}    // namespace pkg
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif    // UCM_AAP_LIBRARY__UCM_LIB_PKG_BIN__TYPES_H_
