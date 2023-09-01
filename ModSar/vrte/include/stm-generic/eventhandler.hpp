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
/// @file      libs/eh/include/bosch/vrte/stm/eh/eventhandler.hpp
/// @brief     Event Handler header file
/// @copyright Robert Bosch GmbH 2018-2022
/// @author    VRTE StM Team
//
//=============================================================================

#ifndef BOSCH_VRTE_STM_EH_EVENTHANDLER_HPP_INCLUDED
#define BOSCH_VRTE_STM_EH_EVENTHANDLER_HPP_INCLUDED

#include <array>
#include <vector>

// Event Handler configuration
#include "bosch/vrte/stm/eh/ieventhandler.hpp"
#include "bosch/vrte/stm/eh/ieventnames.hpp"

// Interaction with other StM sub-components
#include "bosch/vrte/stm/eventloop.hpp"

#include "bosch/vrte/stm/cm/icomponentmanager.hpp"
#include "bosch/vrte/stm/ecucfg/iconfigmanager.hpp"
#include "bosch/vrte/stm/fgm/ifunctiongroupmanager.hpp"
#include "bosch/vrte/stm/nm/inetworkmanager.hpp"
#include "bosch/vrte/stm/osm/ioperationalstatemanager.hpp"
#include "bosch/vrte/stm/sm/istartupmanager.hpp"

namespace bosch
{
namespace vrte
{
namespace stm
{
namespace eh
{

class CIExternalInterface;  // Forward declaration for registration of clients

/// @brief Main class of the event handler

class CEventHandler : public CIEventHandler
{
public:
    /// @brief Constructor of EventHandler class
    ///
    /// Initialize data member of CEventLoop and set event name
    /// @param[in] f_eventNames    Event name
    CEventHandler(CIEventNames& f_eventNames);

    /// @brief Public destructor
    /// @details EventHandler main thread will be stopped by sending itself an event
    ///          All communication to other stm components will stop
    ~CEventHandler();

    /// @brief Overload acceptEvent(uint64_t) method to allow stm-subcomponents to send events with payload
    /// @details This function accepts event (uint64_t) and associated data (std::string)
    /// @param[in] f_event    Event ID
    /// @param[in] f_data     Event payload
    void acceptEvent(const uint64_t f_event, const std::string& f_data = std::string()) override;

    /// @brief Method used by stm entities ( ara::com interface objects and stm subcomponents) to register at eh
    /// @details After successfully registration at event handler, clients will get ALL events that arrive at eh
    /// @param[in] ehClient    Client to be registered
    /// @return Registration status
    EStdReturnType intRegisterAtEventHandler(CIExternalInterface& ehClient) override;

    /// @brief Method used by stm entities ( ara::com interface objects and stm subcomponents) to unregister at eh
    /// @details After successfully unregistration at event handler, clients wont get any events, communication
    ///          to other stm components will stop
    /// @param[in] ehClient    Client to be unregistered
    /// @return Unregistration status
    EStdReturnType intRemoveClientAtEventHandler(CIExternalInterface& ehClient) override;

    /// @brief Method to register OSM with Event Handler to receive events
    /// @param[in]    f_iosm : Pointer to OSM object
    void registerClient(osm::CIOperationalStateManager* f_iosm) override;

    /// @brief Method to register FGM with Event Handler to receive events
    /// @param[in] f_ifgm     Pointer to FGM object
    void registerClient(fgm::CIFunctionGroupManager* f_ifgm) override;

    /// @brief Method to register NM with Event Handler to receive events
    /// @param[in] f_inms    Pointer to NM object
    void registerClient(nm::CINetworkManager* f_inms) override;

    /// @brief Method to register CM with Event Handler to receive events
    /// @param[in] f_icm    Pointer to CM object
    void registerClient(cm::CIComponentManager* f_icm) override;

    /// @brief Method to register SM with Event Handler to receive events
    /// @param[in] f_ism    Pointer to SM object
    void registerClient(sm::CIStartupManager* f_ism) override;

    /// @brief Get event name based on event ID and combine it with inputted data
    /// @param[in] f_event    Event ID
    /// @param[in] f_data     Event payload
    /// @return const std::string / Matching event name (or a decoded event mask pattern
    ///                 in case of no match) along with the content of f_data
    std::string getEventInfo(const uint64_t f_event, const std::string& f_data = std::string()) override;

    /// @brief Check validity of registered subcomponents and start event loop.
    /// @details Project can decide if it is acceptable to proceed with one or more sub-components not registered.
    ///          Side-effect is that the unregistred components do not receive any events and cannot function properly.
    /// @returns true if all the sub-components are registered, false otherwise
    virtual bool run();

    /// @brief Stop event handling.
    /// @details This methods needs to be called before clients are destroyed, because
    ///          otherwise the EH will call acceptEvent() on freed memory.
    void stop();

protected:
    /// @brief Handle received event.
    /// @param[in] f_event  Event ID
    /// @param[in] f_data   Event payload
    virtual void handleEvent(uint64_t f_event, const std::string& f_data = std::string());

private:
    CEventLoop m_events;

    std::array<CIEventAcceptor*, EV_ID_ALL> m_contexts = {{nullptr}};

    // list of EH clients
    std::vector<CIExternalInterface*> m_ehClients;

    //! Event names object to maintain the STM wide event map (add and get event names).
    CIEventNames& m_eventNames;
};
}  // namespace eh
}  // namespace stm
}  // namespace vrte
}  // namespace bosch

#endif  // BOSCH_VRTE_STM_EH_EVENTHANDLER_HPP_INCLUDED
