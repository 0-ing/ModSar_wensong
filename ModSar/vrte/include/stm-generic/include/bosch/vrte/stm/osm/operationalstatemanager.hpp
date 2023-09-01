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
/// @file      libs/osm/include/bosch/vrte/stm/osm/operationalstatemanager.hpp
/// @brief     Operational State Manager header file
/// @copyright Robert Bosch GmbH 2018-2022
/// @author    VRTE StM Team
//
//=============================================================================

#ifndef BOSCH_VRTE_STM_OSM_OPERATIONALSTATEMANAGER_HPP_INCLUDED
#define BOSCH_VRTE_STM_OSM_OPERATIONALSTATEMANAGER_HPP_INCLUDED

#include "bosch/vrte/stm/eventloop.hpp"
#include "bosch/vrte/stm/pluginmanager/ipluginmanager.hpp"
#include "bosch/vrte/stm/pluginmanager/plugin.hpp"
#include "bosch/vrte/stm/pluginmanager/pluginfsm.hpp"
#include "bosch/vrte/stm/pluginmanager/pluginserver.hpp"

// osm includes
#include "bosch/vrte/stm/osm/ioperationalstatemanager.hpp"

#include <cstdint>
#include <memory>
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
}

namespace osm
{

/// \brief Implementation of Operational State Manager Interface and Plugin Server Fsm Interface.
class COperationalStateManager : public CIOperationalStateManager, public pluginmanager::CIPluginServerFsmBase
{

public:
    /// \brief OSM Constructor.
    ///  Create Fsm Manager object of OSM to manage the main state machine.
    ///
    /// \param[in] f_eh:            Reference to Event Handler, to register the event callbacks
    /// \param     f_pluginManager: Reference to Plugin Manager, to get list of plugins
    explicit COperationalStateManager(eh::CIEventHandler& f_eh, pluginmanager::CIPluginManager& f_pluginManager);

    /// \brief OSM Destructor.
    ~COperationalStateManager();

    /// \brief Overload acceptEvent(uint64_t, std::string) method to allow
    ///  stm-subcomponents to send events with payload.
    ///
    /// \param[in] f_event: the event OSM shall evaluate
    /// \param[in] f_data:  the associated data OSM shall evaluate
    void acceptEvent(const uint64_t f_event, const std::string& f_data) override;

    /// \brief Broadcast to all OSM clients new state changed.
    ///
    /// \param[in] pArg: New operational state
    void notifyNewState(const char* pArg) override;

    /// \brief Overload acceptEventCallBack() method to allow plugins can be
    /// able to send events with payload to stm-subcomponents.
    ///
    /// \param[in] f_event: the event OSM shall evaluate
    /// \param[in] f_data:  the associated data OSM shall evaluate
    void acceptEventCallBack(uint64_t f_event, const std::string& f_data) override;

    /// @brief See documentation in pluginmanager::CIPluginServerFsmBase
    void stateChangeResult(const std::string& /*f_fgName*/, const std::string& /*f_state*/, bool /*f_success*/) override
    {
        // noop in OSM
    }

    /// \brief Implementation of the OSM component runner to start event loop.
    virtual void run();

protected:
    /// \brief Handle received event.
    /// \param[in] f_event: received event
    /// \param[in] f_data:  received data
    virtual void handleEvent(uint64_t f_event, const std::string& f_data) = 0;

    CEventLoop                                    m_events;
    std::weak_ptr<pluginmanager::CIPluginFsmBase> spPluggedFSM;
    eh::CIEventHandler&                           m_eh;
};

}  // namespace osm
}  // namespace stm
}  // namespace vrte
}  // namespace bosch

#endif  // BOSCH_VRTE_STM_OSM_OPERATIONALSTATEMANAGER_HPP_INCLUDED
