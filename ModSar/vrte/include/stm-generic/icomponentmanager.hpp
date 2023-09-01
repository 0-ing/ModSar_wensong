//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018-2022 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================
//
/// @file      libs/cm/include/bosch/vrte/stm/cm/icomponentmanager.hpp
/// @brief     State Management internal interface for cm::ComponentManager
/// @copyright Robert Bosch GmbH 2018-2022
/// @author    VRTE StM Team
//
//=============================================================================

#ifndef BOSCH_VRTE_STM_CM_ICOMPONENTMANAGER_HPP_INCLUDED
#define BOSCH_VRTE_STM_CM_ICOMPONENTMANAGER_HPP_INCLUDED

#include "bosch/vrte/stm/cm/types.hpp"
#include "bosch/vrte/stm/event.hpp"
#include "bosch/vrte/stm/types.hpp"

#include <string>
#include <vector>

namespace bosch
{
namespace vrte
{
namespace stm
{
namespace cm
{

/// @brief Handling of component states.
class CIComponentManager : public CIEventAcceptor
{
public:
    /// @brief Default destructor
    virtual ~CIComponentManager() = default;

    /// @brief Debug informations of a connected component.
    struct ComponentDebugInfo
    {
        // Component name
        std::string name;

        // Current state
        std::string state;

        // Plugin name
        std::string plugin;
    };

    /// @brief Get information of all connected components for debug purposes.
    ///
    /// @return                 List of component debug information.
    virtual std::vector<ComponentDebugInfo> getComponentDebugInfos() = 0;
};

}  // namespace cm
}  // namespace stm
}  // namespace vrte
}  // namespace bosch

#endif  // BOSCH_VRTE_STM_CM_ICOMPONENTMANAGER_HPP_INCLUDED
