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
/// @file      libs/common/include/bosch/vrte/stm/pluginmanager/types.hpp
/// @brief     Plugin enums and other types
/// @copyright Robert Bosch GmbH 2018-2022
/// @author    VRTE StM Team
//
//=============================================================================

#ifndef BOSCH_VRTE_STM_PLUGINMANAGER_TYPES_HPP_INCLUDED
#define BOSCH_VRTE_STM_PLUGINMANAGER_TYPES_HPP_INCLUDED

#include <cstdint>

namespace bosch
{
namespace vrte
{
namespace stm
{
namespace pluginmanager
{

static constexpr const char* PLUGIN_INIT_SYMBOL        = "plugin_init";
static constexpr const char* DEFAULT_LOAD_PLUGINS_PATH = "/opt/vrte/stm-aap-state-manager/lib";
static constexpr const char* PLUGIN_STM_SIGNATURE      = "rb-sm-plugin";

//! Enum for plugin types
enum class EPluginType : uint8_t
{
    //! state machine plugin
    stateMachine = 0,
    //! external interfce plugins loaded by default
    externalInterfaceDefault,
    //! external interface plugins loaded based on config
    externalInterfaceConfig,
    //! debug plugin
    debug
};

enum class EServerPlugin : uint8_t
{
    osm = 0,
    fgm,
    cm,
    eh,
    stm
};

class CIPlugin;

using plugin_init_func = CIPlugin* (*)();

#define STM_PLUGIN(class_plugin_name)                                                                                  \
    extern "C"                                                                                                         \
    {                                                                                                                  \
        bosch::vrte::stm::pluginmanager::CIPlugin* plugin_init()                                                       \
        {                                                                                                              \
            return new (std::nothrow) class_plugin_name;                                                               \
        }                                                                                                              \
    }

}  // namespace pluginmanager
}  // namespace stm
}  // namespace vrte
}  // namespace bosch

#endif  // BOSCH_VRTE_STM_PLUGINMANAGER_TYPES_HPP_INCLUDED
