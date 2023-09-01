//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018-2022 by DENSO Corporation. All rights reserved.
//
// This file is property of DENSO Corporation. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================
//
/// @file      include/bosch/vrte/stm/nm/networkmanager.hpp
/// @brief     Class of Network Subcomponent Manager
/// @copyright DENSO Corporation 2018-2022
/// @author    VRTE StM Team
//
//=============================================================================

#ifndef BOSCH_VRTE_STM_NM_NMSUBCOMPONENTMANAGER_HPP_INCLUDED
#define BOSCH_VRTE_STM_NM_NMSUBCOMPONENTMANAGER_HPP_INCLUDED

#include "bosch/vrte/stm/eventloop.hpp"
#include "inetworkmanager.hpp"

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

namespace nm
{

class CNetworkManager : public CINetworkManager
{
public:
    /// @brief      Constructor
    /// @param f_eh Reference to EventHandler
    explicit CNetworkManager(eh::CIEventHandler& f_eh);

    /// @brief SM destructor
    virtual ~CNetworkManager();

    /// @brief get an event from event handler
    void acceptEvent(const uint64_t f_event, const std::string& f_data) override;

    /// @details Establishes all communications with other components.
    /// @brief Start event loop
    virtual void run();

protected:
    /// @brief Handle received event.
    /// @param f_event : received event
    /// @param f_data  : event payload
    /// @details Project side extension function shall forward all events it received
    /// to this functions after processing them
    virtual void handleEvent(uint64_t f_event, const std::string& f_data);

    eh::CIEventHandler& m_eh;  /// Reference to EventHandler
    CEventLoop          m_events;
};

}  // namespace nm
}  // namespace stm
}  // namespace vrte
}  // namespace bosch

#endif  // BOSCH_VRTE_STM_NM_NMSUBCOMPONENTMANAGER_HPP_INCLUDED
