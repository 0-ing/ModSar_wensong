//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/pkg/mnf/types.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks
///
/// @ingroup bosch_vrte_ucm_lib_pkg_mnf

#ifndef UCM_AAP_LIBRARY__UCM_LIB_PKG_MNF__TYPES_H_
#define UCM_AAP_LIBRARY__UCM_LIB_PKG_MNF__TYPES_H_

#include <string>

#include "ucm/lib/types.h"
#include "ara/core/result.h"
#include "ucm/lib/pkg/mnf/model/manifest.h"

/// @addtogroup bosch_vrte_ucm_lib_pkg_mnf
/// @{

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace pkg   {
namespace mnf   {

/// @brief Error type for the manifest parsing service.
/// Error type for the manifest parsing service, which resolves to a
/// Adaptive AUTOSAR error code define for UCM.
using Error  = ara_error_type;

/// @brief Result type for the manifest parsing service.
/// An object of this type is returned as a result of manifest parsing
/// operation. In essence it is the C++17 std::optional<>
using Result = ::ara::core::Result<Manifest, Error>;

/// @brief Convert an \ref UpdateAction value to a string.
std::string action_str(const UpdateAction& action) noexcept;

}    // namespace mnf
}    // namespace pkg
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif // UCM_AAP_LIBRARY__UCM_LIB_PKG_MNF__TYPES_H_
