//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
/// @copyright Robert Bosch GmbH 2018. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file      AppInstId.hpp
/// @brief     Type Definition: AppInstId
/// @author    Christopher Schwager

#ifndef UTILS_IAPPINSTID_HPP_INCLUDED
#define UTILS_IAPPINSTID_HPP_INCLUDED

#include "utils/Dependency.hpp"
#include "utils/PrimaryConfig.hpp"
#include "utils/vector.hpp"
#include <stdint.h>

namespace exm
{
/// @brief Representation of an Application Instance as Identifier
enum class AppInstId : int16_t
{
    INVALID = -1,      ///< @brief Invalid Application Instance ID
    FIRST_VALID_ID = 0 ///< @brief First valid Application Instance ID
};

typedef utils::vector<AppInstId, utils::PROCESS_MAX> AppInstIds;
typedef utils::vector<utils::Dependency<AppInstId>,utils::MAX_PROCESS_DEPENDENCY> DependenciesWithAppId;
typedef utils::vector<utils::Dependency<AppInstId>,utils::MAX_PROCESS_RESOLVER> ResolversWithAppId;


namespace app_inst_id
{

/// @brief Returns the Application Instance Identifier by ID
/// @param id   Instance ID in the form of a signed integer
/// @return AppInstId
inline AppInstId FromId(int32_t id)
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
        AppInstId>(id);
}
}

} /* namespace exm */

#endif
