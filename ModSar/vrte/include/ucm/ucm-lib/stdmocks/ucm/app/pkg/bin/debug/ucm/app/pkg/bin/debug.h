//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/app/pkg/bin/debug.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY__UCM_APP_PKG_BIN__DEBUG_H_
#define UCM_AAP_LIBRARY__UCM_APP_PKG_BIN__DEBUG_H_

#include "ucm/lib/log/ref_logger.h"

#include "ucm/app/pkg/bin/v01xx/bitable.h"
#include "ucm/app/pkg/bin/v01xx/auth_block.h"
#include "ucm/app/pkg/bin/v01xx/data_block.h"

#include "ucm/app/pkg/bin/v0102/auth_block.h"
#include "ucm/app/pkg/bin/v0102/data_block.h"

	
namespace bosch {
namespace vrte  {
namespace ucm   {
namespace app   {
namespace pkg   {
namespace bin   {

namespace v01xx {

std::ostream& operator<<(std::ostream&, const DataBlock&) noexcept;
std::ostream& operator<<(std::ostream&, const AuthBlock&) noexcept;
std::ostream& operator<<(std::ostream&, const BITable::Fields&) noexcept;

}    // namespace v01xx


namespace v0102 {

std::ostream& operator<<(std::ostream&, const DataBlock&) noexcept;
std::ostream& operator<<(std::ostream&, const AuthBlock&) noexcept;

}    // namespace v0102


//namespace v0104 {
//
//std::ostream& operator<<(std::ostream&, const AuthTag&) noexcept;
//
//}    // namespace v0104


}    // namespace bin
}    // namespace pkg
}    // namespace app
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif    // UCM_AAP_LIBRARY__UCM_APP_PKG_BIN__DEBUG_H_
