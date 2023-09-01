//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/pkg/bin/debug.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY__UCM_LIB_PKG_BIN__DEBUG_H_
#define UCM_AAP_LIBRARY__UCM_LIB_PKG_BIN__DEBUG_H_

#include "ucm/lib/buf/model.h"
#include "ucm/lib/log/ref_logger.h"
#include "ucm/lib/pkg/bin/auth_block.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace pkg   {
namespace bin   {

std::ostream& operator<<(std::ostream&, const AuthBlock&) noexcept;
std::ostream& operator<<(std::ostream&, const buf::Model&) noexcept;


}    // namespace bin
}    // namespace pkg
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif    // UCM_AAP_LIBRARY__UCM_LIB_PKG_BIN__DEBUG_H_
