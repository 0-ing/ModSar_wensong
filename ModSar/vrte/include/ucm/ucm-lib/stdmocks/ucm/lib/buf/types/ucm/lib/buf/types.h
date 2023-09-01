//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/buf/types.h
/// @brief        UCM flexible buffers specific types.
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks
/// @ingroup bosch_vrte_ucm_lib_buf

#ifndef UCM_AAP_LIBRARY__UCM_LIB_BUF__TYPES_H_
#define UCM_AAP_LIBRARY__UCM_LIB_BUF__TYPES_H_

#include <sys/types.h>

#include <cstddef>

#include "ucm/lib/utl/offset.h"

/// @addtogroup bosch_vrte_ucm_lib_buf
/// @{

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace buf   {

/// @brief Distinct type for file offsets.
using iofile_offset = utl::Offset<off_t>;

/// @brief Distinct type for memory offsets.
using memory_offset = utl::Offset<std::size_t>;

}    // namespace buf
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif    // UCM_AAP_LIBRARY__UCM_LIB_BUF__TYPES_H_
