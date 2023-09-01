//==============================================================================
// C O P Y R I G H T
//------------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//==============================================================================

/// @file         ucm/lib/swc/swc_types.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY_LIB_UCM_LIB_SWC__SWC_TYPES_H_
#define UCM_AAP_LIBRARY_LIB_UCM_LIB_SWC__SWC_TYPES_H_

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/types.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace swc   {

enum class Relation : unsigned
{
    kEQ, kGT, kLT, kGE, kLE, kNE, kAny
};

using swname_type = std::string;
using tstamp_type = std::uint64_t;
using unique_type = std::uint64_t;
using action_type = ara::ARATypes::ActionType;
using astate_type = ara::ARATypes::SwClusterStateType;
using aerror_type = ara::ARATypes::ApplicationErrorsType;


}    // namespace swc
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY_LIB_UCM_LIB_SWC__SWC_TYPES_H_

