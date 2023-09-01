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
/// @file      libs/cm/include/bosch/vrte/stm/cm/componentpluginbase.hpp
/// @brief     State Management subcomponent ComponentManager
///            This class wraps/simplifies the pluginmanager interface
///            for project specific state handlers
///
/// @copyright Robert Bosch GmbH 2018-2022
/// @author    VRTE StM Team
//
//=============================================================================

#ifndef BOSCH_VRTE_STM_CM_COMPONENTPLUGINBASE_HPP_INCLUDED
#define BOSCH_VRTE_STM_CM_COMPONENTPLUGINBASE_HPP_INCLUDED

#include "bosch/vrte/stm/cm/icomponentplugin.hpp"
#include "bosch/vrte/stm/cm/types.hpp"
#include "bosch/vrte/stm/pluginmanager/plugin.hpp"

#include <chrono>
#include <map>
#include <mutex>
#include <string>
#include <utility>

namespace bosch
{
namespace vrte
{
namespace stm
{
namespace cm
{

class CIComponentManager;

/// @brief Base class for component plugin implementations.
///
/// A plugin can be used for multiple components.
/// If a plugin requests a state change, this will be done for
/// all mapped components. The state change will only be considered
/// successfull, once all components finished.
class CComponentPluginBase : public CIComponentPlugin, public pluginmanager::CPlugin
{
public:
    /// @brief Constructor
    ///
    /// @param[in] f_name     Plugin name
    /// @param[in] f_version  Plugin version
    /// @param[in] f_type     Plugin type
    /// @param[in] f_server   Plugin server
    CComponentPluginBase(const std::string&           f_name,
                         uint32_t                     f_version,
                         pluginmanager::EPluginType   f_type,
                         pluginmanager::EServerPlugin f_server);

    /// @brief Destructor
    virtual ~CComponentPluginBase();

    /// @brief See documentation in CIComponentPlugin.
    void registerComponent(CIComponent* f_component) override;

    /// @brief See documentation in CIComponentPlugin.
    void unregisterComponent(CIComponent* f_component) override;

    /// @brief See documentation in CIComponentPlugin.
    void setEventHandler(CIEventAcceptor* f_eh) override;

    /// @brief See documentation in CIPluginBase.
    void requestCallback(CIComponent* f_component, const std::string& f_state, EStdReturnType f_status) override;

protected:
    /// @brief Request a state change on all registered components.
    ///
    /// The callback will only be called once all connected components finished (or failed).
    /// For error reporting, every failed request will send the EV_CM_ERROR_COMPONENT_STATE_CHANGE_FAILED
    /// event.
    ///
    /// @param[in] f_state          Component state to be set.
    /// @param[in] f_mode           RequestMode (e.g. force/voluntary)
    /// @param[in] f_retries        Number of retries before a kForced request is sent.
    ///                             Ignored if f_mode already is set to kForced.
    ///                             Will result in the first + f_retries + forced requests in total.
    ///                             Every retry will have
    /// @param[in] f_timeout        Timeout for requests.
    /// @param[in] f_callback       Function to be called when the transition finished.
    /// @param[in] f_abortCurrent   Abort any currently ongoing requests.
    virtual void requestState(const std::string&        f_state,
                              ERequestMode              f_mode,
                              uint32_t                  f_retries,
                              std::chrono::milliseconds f_timeout,
                              callback_t                f_callback,
                              bool                      f_abortCurrent = false);

    /// @brief Forward event to EH.
    ///
    /// Will do nothing before the event handler has been assigned.
    ///
    /// @param f_event              Event
    void forwardToEH(uint64_t f_event);

    CIEventAcceptor*             m_eh = nullptr;
    std::string                  m_name;
    uint32_t                     m_version;
    pluginmanager::EPluginType   m_type;
    pluginmanager::EServerPlugin m_server;

    // Additional information stored with component references.
    struct ComponentData
    {
        // The current component state.
        std::string state;

        // The current component status.
        EStdReturnType status;
    };

    // List of components serviced by this plugin.
    std::map<CIComponent*, ComponentData> m_components;
    std::recursive_mutex                  m_componentsMutex;

    // The last requested component state/mode.
    // This will be used if a component registered after a state change
    // for the whole plugin was requested.
    std::string               m_lastRequestedState;
    ERequestMode              m_lastRequestedMode    = ERequestMode::kInvalid;
    uint32_t                  m_lastRequestedRetries = 0;
    std::chrono::milliseconds m_lastRequestedTimeout;
    bool                      m_lastRequestedAbortCurrent = false;

    callback_t m_callback;
};

}  // namespace cm
}  // namespace stm
}  // namespace vrte
}  // namespace bosch

#endif  // BOSCH_VRTE_STM_CM_COMPONENTPLUGINBASE_HPP_INCLUDED
