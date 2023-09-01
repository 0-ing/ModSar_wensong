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
/// @file      libs/common/include/bosch/vrte/stm/pluginmanager/pluginserver.hpp
/// @brief     Plugin server interface for STM
/// @copyright Robert Bosch GmbH 2018-2022
/// @author    VRTE StM Team
//
//=============================================================================

#ifndef BOSCH_VRTE_STM_PLUGINMANAGER_PLUGINSERVER_HPP_INCLUDED
#define BOSCH_VRTE_STM_PLUGINMANAGER_PLUGINSERVER_HPP_INCLUDED

#include "bosch/vrte/stm/logging.hpp"

#include <stdint.h>
#include <string>

namespace bosch
{
namespace vrte
{
namespace stm
{
namespace pluginmanager
{

///
/// \brief Pure virtual interface for STM components containing plugins.
///
/// Use this interface if you want your plugin to be able to add traces or send events
/// to the STM subcomponent.
///
class CIPluginServerFsmBase
{
public:
    /// @brief Destructor.
    virtual ~CIPluginServerFsmBase() = default;

    /// @brief Broadcast to all clients the new state.
    ///
    /// @param[in] state State name to broadcast
    virtual void notifyNewState(const char* state) = 0;

    /// @brief To allow plugins to be able to send events with payload to STM subcomponents.
    ///
    /// @param[in] event Event id
    /// @param[in] data  Event payload
    virtual void acceptEventCallBack(const uint64_t event, const std::string& data = std::string()) = 0;

    /// @brief Inform the server about the result of a FG state change request.
    ///
    /// @param[in] f_fgName  Function group name
    /// @param[in] f_state   Function group state
    /// @param[in] f_success Change state result
    virtual void stateChangeResult(const std::string& f_fgName, const std::string& f_state, bool f_success) = 0;
};

}  // namespace pluginmanager
}  // namespace stm
}  // namespace vrte
}  // namespace bosch

#endif  // BOSCH_VRTE_STM_PLUGINMANAGER_PLUGINSERVER_HPP_INCLUDED
