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
/// @file      libs/common/include/bosch/vrte/stm/pluginmanager/ipluginmanager.hpp
/// @brief     Plugin Manager Interface of STM
/// @copyright Robert Bosch GmbH 2018-2022
/// @author    VRTE StM Team
//
//=============================================================================

#ifndef BOSCH_VRTE_STM_PLUGINMANAGER_IPLUGINMANAGER_HPP_INCLUDED
#define BOSCH_VRTE_STM_PLUGINMANAGER_IPLUGINMANAGER_HPP_INCLUDED

#include "bosch/vrte/stm/pluginmanager/plugin.hpp"

#include <functional>
#include <memory>  // std::shared_ptr
#include <string>
#include <vector>

namespace bosch
{
namespace vrte
{
namespace stm
{
namespace pluginmanager
{

///
/// \brief Manage plugins.
///
/// The PluginManager dlopens() all shared libraries found in the path
/// provided by the LOAD_STM_PLUGINS_PATH env variable.
///
class CIPluginManager
{
public:
    // For register callback function after reloading complete
    typedef std::function<void(std::weak_ptr<CIPlugin>)> callback_t;

    CIPluginManager()          = default;
    virtual ~CIPluginManager() = default;

    /// @brief Load (dlopen) all plugins.
    ///
    /// This function scans a directory for shared libraries starting with PLUGIN_STM_SIGNATURE
    /// and dlopen()'s them. It can be called multiple times (e.g. in case of SOTA) but should at
    /// least be called once upon start.
    ///
    /// @param[in] f_path        Lookup directory
    virtual void load(const std::string& f_path) = 0;

    /// @brief Get a plugin.
    ///
    /// @param[in] f_server      STM subcomponent that this plugin is for (CM, OSM, FGM, EH)
    /// @param[in] f_name        Plugin name (as returned by getName())
    /// @return                  Weak pointer to plugin (can become invalid anytime)
    virtual std::weak_ptr<CIPlugin> get(EServerPlugin f_server, const std::string& f_name) = 0;

    /// @brief Get a plugin.
    ///
    /// @param[in] f_server      STM subcomponent that this plugin is for (CM, OSM, FGM, EH)
    /// @param[in] f_name        Plugin name (as returned by getName())
    /// @param[in] f_type        Plugin type.
    /// @return                  Weak pointer to plugin (can become invalid anytime)
    virtual std::weak_ptr<CIPlugin> get(EServerPlugin f_server, EPluginType f_type, const std::string& f_name) = 0;

    /// @brief Get all loaded plugins of an STM subcomponent.
    /// @param[in] f_server      STM subcomponent that this plugin is for (CM, OSM, FGM, EH)
    /// @param[in] f_type        Plugin type.
    /// @return                  Weak pointers to plugins (can become invalid anytime)
    virtual std::vector<std::weak_ptr<CIPlugin>> getAll(EServerPlugin f_server, EPluginType f_type) = 0;

    /// @brief Add a statically linked plugin object.
    /// @param[in] f_plugin      Plugin object
    virtual void loadPluginStatic(std::shared_ptr<CIPlugin> f_plugin) = 0;

    /// @brief Unload a plugin.
    /// @param[in] f_server      STM subcomponent that this plugin is for (CM, OSM, FGM, EH)
    /// @param[in] f_name        Plugin name.
    /// @return                  true, when the plugin could be found and unload.
    virtual bool unload(EServerPlugin f_server, const std::string& f_name) = 0;

    /// @brief Unload all plugins with given server and type.
    /// @param[in] f_server      STM subcomponent that this plugin is for (CM, OSM, FGM, EH)
    /// @param[in] f_type        Plugin type.
    /// @return                  true, when the plugin could be found and unload.
    virtual bool unload(EServerPlugin f_server, EPluginType f_type) = 0;

    /// @brief Register a callback for given plugin.
    ///
    /// When this plugin is beeing loaded, the callback is called.
    /// A second call to registerCallback() with the same server and name
    /// will replace the old callback.
    ///
    /// @param[in] f_server      STM subcomponent that this plugin is for (CM, OSM, FGM, EH)
    /// @param[in] f_name        Plugin name.
    /// @param[in] f_callback    The callback function to be called.
    virtual void registerCallback(EServerPlugin f_server, const std::string& f_name, callback_t f_callback) = 0;
};

}  // namespace pluginmanager
}  // namespace stm
}  // namespace vrte
}  // namespace bosch

#endif  // BOSCH_VRTE_STM_PLUGINMANAGER_IPLUGINMANAGER_HPP_INCLUDED
