//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file      FuncGroupId.hpp
/// @brief     Type Definition: FuncGroupId
/// @copyright Robert Bosch GmbH  2018
/// @author    Christopher Schwager

#ifndef UTILS_IFUNCGROUPID_HPP_INCLUDED
#define UTILS_IFUNCGROUPID_HPP_INCLUDED

#include "utils/PrimaryConfig.hpp"
#include "utils/vector.hpp"

#include <stdint.h>

namespace exm
{

/// @brief    Representation of a Function Group as Identifier
enum class FuncGroupId : int16_t
{
    INVALID = -1,  ///< @brief Invalid Function Group ID.
    FIRST_VALID_ID ///< @brief First usable Function Group ID.
};

typedef utils::vector<FuncGroupId, utils::MAX_FUNC_GROUP> FuncGroupIds;

namespace func_group_id
{

/// @brief Returns the Function Group ID by index
/// @param index   Index of the Function Group
/// @return FuncGroupId
inline FuncGroupId FromIndex(uint32_t index)
{
    return static_cast< // PRQA S 3013 #  The enum is used as a type safe integer. We evaluated
                        // different options, such as storing the integer in a class. However we
                        // would need the class to be fully constexpr compatible, as we need the
                        // associated constants such as INVALID and co. to be compile time
                        // evaluated, as otherwise we have a race between the global constructors at
                        // runtime. However making the class fully constexpr compatible makes gcc
                        // consider the class to be an aggregate type. There however is an arcane
                        // flag in gcc called -Waggregate-return which was meant to forbid returning
                        // structs from functions in legacy C. gcc however marks modern C++
                        // aggregates the exact same way and thus if you have that flag set, it
                        // accidentally fires. Therefore the best solution for now is to simply keep
                        // the enum.
        FuncGroupId>(index + static_cast<uint32_t>(FuncGroupId::FIRST_VALID_ID));
}
}

/// @brief    Namespace to locate Adaptive AUTOSAR-defined Function Groups.
namespace FuncGroup
{
constexpr const char* MachineFG  = "MachineFG"; ///< @brief Basic Function Group used for
                                                     ///< Platform Initialization and Shutdown.
}

} /* namespace exm */

#endif
