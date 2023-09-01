//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/app/pkg/bin/types.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks
/// @ingroup      bosch_vrte_ucm_app_pkg_bin


#ifndef UCM_AAP_LIBRARY__UCM_APP_PKG_BIN__TYPES_H_
#define UCM_AAP_LIBRARY__UCM_APP_PKG_BIN__TYPES_H_

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/pkg/bin/types.h"

/// @addtogroup bosch_vrte_ucm_app_pkg_bin
/// @{


namespace bosch {
namespace vrte  {
namespace ucm   {
namespace app   {
namespace pkg   {
namespace bin   {

using sfile_pair = lib::pkg::bin::sfile_pair;


}    // namespace bin
}    // namespace pkg
}    // namespace app
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif // UCM_AAP_LIBRARY__UCM_APP_PKG_BIN__TYPES_H_
