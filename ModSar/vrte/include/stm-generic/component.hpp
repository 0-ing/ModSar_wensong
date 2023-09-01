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
/// @file      libs/cm/include/bosch/vrte/stm/cm/component.hpp
/// @brief     CComponent acts as a proxy for connected components.
///            For each connected component there is one instance of CComponent.
/// @copyright Robert Bosch GmbH 2018-2022
/// @author    VRTE StM Team
//
//=============================================================================

#ifndef BOSCH_VRTE_STM_CM_COMPONENT_HPP_INCLUDED
#define BOSCH_VRTE_STM_CM_COMPONENT_HPP_INCLUDED

#include "bosch/vrte/stm/cm/icomponent.hpp"
#include "bosch/vrte/stm/cm/types.hpp"
#include "bosch/vrte/stm/thread.hpp"
#include "bosch/vrte/stm/timeoutthread.hpp"

#include <memory>
#include <mutex>
#include <queue>
#include <string>

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
class CIPlugin;
}  // namespace pluginmanager

namespace cm
{

constexpr const char COMPONENT_STATE_REQUEST_DATA_PART_SEPARATOR = ';';

class CIComponentManager;
class CIComponentPlugin;

/// @brief Proxy to connected components.
///
/// CComponent allows for asynchronously requesting state changes on connected components.
class CComponent : public CIComponent
{
public:
    /// @brief Constructor
    ///
    /// The constructor will connect the created object with the plugin.
    ///
    /// @param [in] f_cm                Reference to ComponentManager.
    /// @param [in] f_eh                Reference to EventHandler.
    /// @param [in] f_name              Component name.
    /// @param [in] f_plugin            State machine plugin
    CComponent(CIComponentManager&              f_cm,
               eh::CIEventHandler&              f_eh,
               const std::string&               f_name,
               std::weak_ptr<CIComponentPlugin> f_plugin);

    /// @brief Destructor
    virtual ~CComponent();

    /// @brief See documentation in CIComponent
    const std::string& getName() const override
    {
        return m_name;
    }

    /// @brief See documentation in CIComponent
    void requestState(const std::string&        f_state,
                      ERequestMode              f_mode,
                      uint32_t                  f_retries,
                      std::chrono::milliseconds f_timeout,
                      bool                      f_abortCurrent = false) override;

    /// @brief See documentation in CIComponent
    void onStateChanged(const std::string& f_state, uint64_t f_event) override;

    /// @brief Check if a state transition is currently ongoing.
    ///
    /// @return                 true if no transition is ongoing.
    bool isStateTransitionFinished() const;

    /// @brief See documentation in CIComponent
    const std::string& getState() const override
    {
        return m_confirmedState;
    }

    /// @brief See documentation in CIComponent
    std::weak_ptr<CIComponentPlugin> getPlugin() const override
    {
        return m_plugin;
    }

    /// @brief See documentation in CIComponent
    void setPlugin(std::weak_ptr<CIComponentPlugin> f_plugin) override
    {
        m_plugin = f_plugin;
    }

    /// @brief Callback method for when an FSM plugin was loaded.
    ///
    /// In SOTA it might happen that the corresponding plugin for a component
    /// has been unloaded. This method will be called as soon as it is loaded again.
    ///
    /// @param f_plugin             Weak pointer to the new FSM plugin.
    void onPluginLoaded(std::weak_ptr<pluginmanager::CIPlugin> f_plugin);

protected:
    // A request consists of a state and mode.
    struct Request
    {
        std::string               state;
        ERequestMode              mode;
        uint32_t                  retries;
        std::chrono::milliseconds timeout;
    };

    /// @brief Timeout callback for request timeouts.
    void timeoutCallback();

    /// @brief Forward the request to the external interaface.
    ///
    /// A timeout thread is also started that makes sure this request
    /// will be aborted once the request timeout is reached.
    ///
    /// @param[in] f_request    Request
    void sendRequest(const Request& f_request);

    /// @brief Decrease retry counter if possible.
    ///
    /// Check if the request can be retried (retry counter > 0 or retry type == kForced).
    ///
    /// @param[inout] f_request Request to update
    /// @return                 true if a retry is possible.
    bool decreaseRetryCounter(Request& f_request);

    CIComponentManager&              m_cm;
    eh::CIEventHandler&              m_eh;
    std::weak_ptr<CIComponentPlugin> m_plugin;
    std::string                      m_name;

    std::string m_confirmedState;

    std::queue<Request> m_requests;
    mutable std::mutex  m_requestsMutex;

    CTimeoutThread m_timeout;
};

}  // namespace cm
}  // namespace stm
}  // namespace vrte
}  // namespace bosch

#endif  // BOSCH_VRTE_STM_CM_COMPONENT_HPP_INCLUDED
