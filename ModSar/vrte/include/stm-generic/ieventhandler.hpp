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
/// @file      libs/eh/include/bosch/vrte/stm/eh/ieventhandler.hpp
/// @brief     Event Handler interface header
/// @copyright Robert Bosch GmbH 2018-2022
/// @author    VRTE StM Team
//
//=============================================================================

#ifndef BOSCH_VRTE_STM_EH_IEVENTHANDLER_HPP_INCLUDED
#define BOSCH_VRTE_STM_EH_IEVENTHANDLER_HPP_INCLUDED

#include "bosch/vrte/stm/event.hpp"
#include "bosch/vrte/stm/types.hpp"

namespace bosch
{
namespace vrte
{
namespace stm
{

namespace osm
{
class CIOperationalStateManager;
}

namespace fgm
{
class CIFunctionGroupManager;
}

namespace nm
{
class CINetworkManager;
}

namespace cm
{
class CIComponentManager;
}

namespace sm
{
class CIStartupManager;
}

namespace ecucfg
{
class CIConfigManager;
}

namespace eh
{

class CIExternalInterface;

/// @brief Class for the internal interface between eh and other stm components

class CIEventHandler : public CIEventAcceptor
{
public:
    /// @brief Default destructor
    virtual ~CIEventHandler() = default;

    /// @brief Method to register at Eventhandler
    /// @details This method allows other entities like stm components or ara::com interfaces implementation
    ///          classes, to register at EH in order to communicate with the rest of the stm, only registered
    ///          entities can get/send events via eventhandler
    /// @param[in] ehClient   client to be register
    /// @return EStdReturnType: registration status\n
    ///         OK = 0,     registration ok\n
    ///         NOT_OK = 1  registration not ok
    virtual EStdReturnType intRegisterAtEventHandler(CIExternalInterface& ehClient) = 0;

    /// @brief Method to remove a client from Eventhandler list
    /// @details This method allows the EH  registered clients, to  be removed from EH list so they will no
    ///          longer get events from it. After de-registration, the components will be still be able to send
    ///          events to EH, but won't receive any events via EH.
    ///          After invoking this call, the component may register again at EH.
    /// @param[in] ehClient    client to be deleted
    /// @return EStdReturnType: registration status\n
    ///         OK = 0,     de-registration ok\n
    ///         NOT_OK = 1  de-registration not ok
    virtual EStdReturnType intRemoveClientAtEventHandler(CIExternalInterface& ehClient) = 0;

    /// @brief Method to register OSM with Event Handler to receive events
    /// @param[in] f_iosm   Pointer to OSM object
    virtual void registerClient(osm::CIOperationalStateManager* f_iosm) = 0;

    /// @brief Method to register FGM with Event Handler to receive events
    /// @param[in] f_ifgm   Pointer to FGM object
    virtual void registerClient(fgm::CIFunctionGroupManager* f_ifgm) = 0;

    /// @brief Method to register NM with Event Handler to receive events
    /// @param[in] f_inms   Pointer to NM object
    virtual void registerClient(nm::CINetworkManager* f_inms) = 0;

    /// @brief Method to register CM with Event Handler to receive events
    /// @param[in]   f_icm Pointer to CM object
    virtual void registerClient(cm::CIComponentManager* f_icm) = 0;

    /// @brief Method to register SM with Event Handler to receive events
    /// @param[in] f_ism   Pointer to SM object
    virtual void registerClient(sm::CIStartupManager* f_ism) = 0;

    /// @brief Get detailed information of an event
    /// @param[in] f_event   Numerical event ID
    /// @param[in] f_data    Payload of the event
    /// @return const std::string / Matching event name (or a decoded event mask pattern
    ///                             in case of no match) along with the content of f_data
    virtual std::string getEventInfo(const uint64_t f_event, const std::string& f_data = std::string()) = 0;
};

}  // namespace eh
}  // namespace stm
}  // namespace vrte
}  // namespace bosch

#endif  // BOSCH_VRTE_STM_EH_IEVENTHANDLER_HPP_INCLUDED
