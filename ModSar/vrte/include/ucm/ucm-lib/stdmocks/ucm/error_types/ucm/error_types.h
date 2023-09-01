//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/error_types.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY__UCM__ERROR_TYPES_H_
#define UCM_AAP_LIBRARY__UCM__ERROR_TYPES_H_

#include <cstdint>

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace err   {

using id_type      = std::uint64_t;
using value_type   = std::int32_t;

}    // namespace err
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch


#endif    // UCM_AAP_LIBRARY__UCM__ERROR_TYPES_H_
