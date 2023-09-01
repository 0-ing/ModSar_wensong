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
/// @file      libs/common/include/bosch/vrte/stm/utilitymacros.hpp
/// @brief     stm utility macros
/// @copyright Robert Bosch GmbH 2018-2021
/// @author    VRTE StM Team
//
//=============================================================================
#ifndef BOSCH_VRTE_STM_UTILITYMACROS_HPP_INCLUDED
#define BOSCH_VRTE_STM_UTILITYMACROS_HPP_INCLUDED

/// @brief: Macro to delete the copy and move constructors and assignment operators.

#define DELETE_COPY_MOVE_CONSTRUCTORS_AND_ASSIGNMENT_OPS(className)                                                    \
                                                                                                                       \
    className(const className&)  = delete;                                                                             \
    className(const className&&) = delete;                                                                             \
    className&  operator=(const className&) = delete;                                                                  \
    className&& operator=(const className&&) = delete

namespace bosch
{
namespace vrte
{
namespace stm
{
}  // namespace stm
}  // namespace vrte
}  // namespace bosch

#endif  // BOSCH_VRTE_STM_UTILITYMACROS_HPP_INCLUDED
