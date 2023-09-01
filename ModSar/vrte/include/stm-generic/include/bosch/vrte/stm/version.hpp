//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018-2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================
//
/// @file      libs/common/include/bosch/vrte/stm/version.hpp
/// @brief     STM Generic Version Information
/// @copyright Robert Bosch GmbH 2018-2021
/// @author    VRTE StM Team
//
//=============================================================================

#ifndef BOSCH_VRTE_STM_VERSION_HPP_INCLUDED
#define BOSCH_VRTE_STM_VERSION_HPP_INCLUDED

namespace bosch
{
namespace vrte
{
namespace stm
{

/// @brief Get revision hash of stm-generic.
/// Until we have an stm base lib this function is implemented in stmlog.
/// @return Git revision hash.
const char* GitHash();

}  // namespace stm
}  // namespace vrte
}  // namespace bosch

#endif  // BOSCH_VRTE_STM_VERSION_HPP_INCLUDED
