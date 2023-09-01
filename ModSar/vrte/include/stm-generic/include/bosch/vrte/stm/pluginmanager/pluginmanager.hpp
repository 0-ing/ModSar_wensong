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
/// @file      libs/common/include/bosch/vrte/stm/pluginmanager/pluginmanager.hpp
/// @brief     Plugin Manager Implementation of STM header file
/// @copyright Robert Bosch GmbH 2018-2022
/// @author    VRTE StM Team
//
//=============================================================================

#ifndef BOSCH_VRTE_STM_PLUGINMANAGER_PLUGINMANAGER_HPP_INCLUDED
#define BOSCH_VRTE_STM_PLUGINMANAGER_PLUGINMANAGER_HPP_INCLUDED

#include "bosch/vrte/stm/pluginmanager/ipluginmanager.hpp"

#include <chrono>
#include <cstdint>
#include <map>
#include <memory>  // std::shared_ptr
#include <mutex>
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

// Timeout for waiting of all references to a plugin object to be removed.
constexpr std::chrono::milliseconds PLUGINMANAGER_CLEAR_WAIT_TIMEOUT = std::chrono::seconds(5);

/// @brief Implementation of the PluginManager interface.
class CPluginManager : public CIPluginManager
{
public:
    CPluginManager();
    virtual ~CPluginManager();

    // Please check CIPluginManager for documentation of overridden methods.
    void                    load(const std::string& f_path) override;
    std::weak_ptr<CIPlugin> get(EServerPlugin f_server, const std::string& f_name) override;
    std::weak_ptr<CIPlugin> get(EServerPlugin f_server, EPluginType f_type, const std::string& f_name) override;
    std::vector<std::weak_ptr<CIPlugin>> getAll(EServerPlugin f_server, EPluginType f_type) override;
    void                                 loadPluginStatic(std::shared_ptr<CIPlugin> f_plugin) override;
    bool                                 unload(EServerPlugin f_server, const std::string& f_name) override;
    bool                                 unload(EServerPlugin f_server, EPluginType f_type) override;
    void registerCallback(EServerPlugin f_server, const std::string& f_name, callback_t f_callback) override;

protected:
    /// @brief Check if the given plugin has the version configured
    ///        in the version table.
    ///
    /// @param [in] f_plugin    Plugin
    /// @return                 true, if the plugin version is correct.
    bool checkVersion(const std::shared_ptr<CIPlugin>& f_plugin) const;

    /// @brief Call dlopen() on given file path.
    ///
    /// @param [in] f_path      plugin path
    void* dlopen(const std::string& f_path);

    /// @brief Load symbol
    /// @param [in] f_handle
    /// @param [in] f_symbol
    void* dlsym(void* f_handle, const std::string& f_symbol);

    /// @brief Inform all callbacks that have been registered for given plugin.
    ///
    /// @param [in] f_plugin    Plugin, that has just been added.
    void informCallbacks(std::shared_ptr<CIPlugin> f_plugin);

    /// @brief  Unload all plugins
    /// @return true, when all plugins could be found and unload.
    bool unloadAll();

    /// @brief Init version of plugins for each stm-component
    void initVersionTable();

    /// @brief Check if a plugin with given path has already been loaded.
    ///
    /// @param [in] f_path      Plugin path
    /// @return                 true, if this plugin is already loaded
    bool isPluginLoaded(const std::string& f_path) const;

    struct PluginData
    {
        //! Shared pointer to the plugin.
        std::shared_ptr<CIPlugin> ptr;

        //! Complete path to the plugin file (if its not a static plugin).
        std::string filepath;

        //! Handle as returned by dlopen().
        void* handle = nullptr;

        /// @brief Clear members
        ///
        /// Will call dlclose() on handle if no more references to
        /// the plugin exist.
        ///
        /// Does not return an error when dlclose() fails, because
        /// there would be no way for the caller to repair the issue
        /// and the object could still be destroyed.
        ///
        /// @param[in] f_timeout Amount of time we wait for all references to
        ///                      be unlocked.
        /// @return              false, when dlclose cannot be called due to
        ///                      other references to a plugin still exist.
        bool clear(const std::chrono::milliseconds& f_timeout);
    };

    /// @brief Unload a plugin idefentified by given filter.
    ///
    /// @param[in] f_filter     f_filter(pluginData) shall return true on the
    ///                         plugin(s) that shall be unloaded.
    /// @return                 false, if no plugin has been unloaded
    bool unloadInternal(std::function<bool(PluginData& f_data)> f_filter);

    //! Map of server type to map of plugin name to plugin object.
    std::vector<PluginData> m_plugins;

    //! Mutex protecting access to member variables.
    std::recursive_mutex m_mutex;

    //! Registered callbacks.
    std::map<EServerPlugin, std::map<std::string, callback_t>> m_callbacks;

    //! Table of supported versions.
    std::map<EServerPlugin, std::map<EPluginType, uint32_t>> m_versionsMap;

    //! Amount of time we wait for all references to be unloaded before calling dlclose()
    std::chrono::milliseconds m_unloadTimeout = PLUGINMANAGER_CLEAR_WAIT_TIMEOUT;
};

}  // namespace pluginmanager
}  // namespace stm
}  // namespace vrte
}  // namespace bosch

#endif  // BOSCH_VRTE_STM_PLUGINMANAGER_PLUGINMANAGER_HPP_INCLUDED
