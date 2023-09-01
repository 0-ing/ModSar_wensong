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
/// @file      libs/common/include/bosch/vrte/stm/pluginmanager/iplugin.hpp
/// @brief     Plugin interface for STM
/// @copyright Robert Bosch GmbH 2018-2022
/// @author    VRTE StM Team
//
//=============================================================================

#ifndef BOSCH_VRTE_STM_PLUGINMANAGER_IPLUGIN_HPP_INCLUDED
#define BOSCH_VRTE_STM_PLUGINMANAGER_IPLUGIN_HPP_INCLUDED

#include "bosch/vrte/stm/pluginmanager/types.hpp"

#include <string>

namespace bosch
{
namespace vrte
{
namespace stm
{
namespace pluginmanager
{

/// @brief Plugin interface
class CIPlugin
{
public:
    /// @brief Destructor
    virtual ~CIPlugin() = default;

    /// @brief Get plugin version
    virtual uint32_t getVersion() const = 0;

    /// @brief Get the name of plugin
    virtual const std::string& getName() const = 0;

    /// @brief Get the type of plugin
    virtual EPluginType getType() const = 0;

    /// @brief Get STM's subcomponent that this plugin is for (CM, OSM, FGM, EH)
    virtual EServerPlugin getServer() const = 0;
};

}  // namespace pluginmanager
}  // namespace stm
}  // namespace vrte
}  // namespace bosch

#endif  // BOSCH_VRTE_STM_PLUGINMANAGER_IPLUGIN_HPP_INCLUDED
