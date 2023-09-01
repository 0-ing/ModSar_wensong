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
/// @file      libs/cm/include/bosch/vrte/stm/cm/componentmanager.hpp
/// @brief     State Management subcomponent ComponentManager, main class
/// @copyright Robert Bosch GmbH 2018-2022
/// @author    VRTE StM Team
//
//=============================================================================

#ifndef BOSCH_VRTE_STM_CM_COMPONENTMANAGER_HPP_INCLUDED
#define BOSCH_VRTE_STM_CM_COMPONENTMANAGER_HPP_INCLUDED

#include "bosch/vrte/stm/cm/icomponentmanager.hpp"
#include "bosch/vrte/stm/eventloop.hpp"

#include <map>
#include <memory>
#include <mutex>
#include <string>
#include <vector>

namespace bosch
{
namespace vrte
{
namespace stm
{

namespace eh
{
class CIEventHandler;
}  // namespace eh

namespace pluginmanager
{
class CIPluginManager;
}  // namespace pluginmanager

namespace cm
{

class CComponentStateRequestInterface;
class CIComponent;
class CComponent;
class CIComponentPlugin;

// Component name for the default state handler. all components not handled by
// any other state handler are handled by the state handler with this name.
constexpr char CM_COMP_NAME_DEFAULT[] = "default";

/// @brief Handling of component states.
///
/// The ComponentManager (CM) loads all plugins and tries to match them with the configured
/// components. The CM will forward any incoming events to the plugins and incoming component
/// state changes from the external interface to the internal component objects.
class CComponentManager : public CIComponentManager
{
public:
    /// @brief Constructor
    ///
    /// @param[in] f_eh         Reference to EventHandler
    /// @param[in] f_plugins    Reference to PluginManager
    CComponentManager(eh::CIEventHandler& f_eh, pluginmanager::CIPluginManager& f_plugins);

    /// @brief Destructor
    virtual ~CComponentManager();

    /// @brief See documentation in CIEventAcceptor
    void acceptEvent(const uint64_t f_event, const std::string& f_data) override;

    /// @brief See documentation in CIComponentManager
    std::vector<ComponentDebugInfo> getComponentDebugInfos() override;

    /// @brief Start the event processing loop.
    virtual void run();

protected:
    /// @brief Handle received event.
    ///
    /// @param[in] f_event       Received event
    /// @param[in] f_data        Received event payload
    virtual void handleEvent(uint64_t f_event, const std::string& f_data);

    /// @brief Called whenever a component registeres.
    ///
    /// @param[in] f_component  Registered component
    virtual void onComponentRegistered(std::shared_ptr<CIComponent> f_component);

    /// @brief Called whenever a component changes its state.
    ///
    /// @param[in] f_component  Component
    virtual void onComponentChangedState(std::shared_ptr<CIComponent> f_component);

    /// @brief Forward event to all plugins.
    ///
    /// @param[in] f_event      Event
    void forwardToPlugins(uint64_t f_event);

    /// @brief Get FSM plugin by name.
    ///
    /// If the plugin with given name could not be found it tries to find the
    /// default state machine. If that cannot be found either, it returns nullptr.
    ///
    /// @param[in] f_name           plugin name.
    /// @return                     Pointer to FSM or null if FSM is not available.
    std::weak_ptr<CIComponentPlugin> getPlugin(const std::string& f_name);

    CEventLoop          m_events;
    eh::CIEventHandler& m_eh;

    pluginmanager::CIPluginManager& m_plugins;

    /// Map connection IDs to components (index in m_components).
    std::map<connection_t, std::shared_ptr<CComponent>> m_components;
    std::mutex                                          m_componentsMutex;
};

}  // namespace cm
}  // namespace stm
}  // namespace vrte
}  // namespace bosch

#endif  // BOSCH_VRTE_STM_CM_COMPONENTMANAGER_HPP_INCLUDED
