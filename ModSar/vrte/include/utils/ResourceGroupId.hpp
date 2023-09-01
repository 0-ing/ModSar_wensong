//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file      ResourceGroupId.hpp
/// @brief     Type Definition: ResourceGroupId
/// @copyright Robert Bosch GmbH  2018
/// @author    Jyothi Kuntegowda

#ifndef UTILS_RESOURCEGROUPID_HPP_INCLUDED
#define UTILS_RESOURCEGROUPID_HPP_INCLUDED

#include <stdint.h>
#include "utils/String.hpp"
#include "utils/PrimaryConfig.hpp"

namespace exm
{

/// @brief    Representation of a Resource Group as Identifier
enum class ResourceGroupId : int16_t
{
    INVALID = -1,  ///< @brief Invalid Resource Group ID.
    MACHINE_RESOURCEGROUP_ID = 0 ///< @brief First usable Resource Group ID.
};

static_assert(::exm::utils::MAX_RESOURCE_GROUP <= 32767, "Max no. of resource groups must fit into a sint16 integer");


namespace resource_group_id
{
    
/// @brief Returns the Resource Group ID by index
/// @param index   Index of the Resource Group
/// @return ResourceGroupId 
inline ResourceGroupId FromIndex(int16_t index)
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
        ResourceGroupId>(index + static_cast<int16_t>(ResourceGroupId::MACHINE_RESOURCEGROUP_ID));
}
}

} /* namespace exm */

#endif
