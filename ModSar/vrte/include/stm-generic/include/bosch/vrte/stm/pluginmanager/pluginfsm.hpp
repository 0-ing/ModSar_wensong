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
/// @file      libs/common/include/bosch/vrte/stm/pluginmanager/pluginfsm.hpp
/// @brief     Plugin statemachine interface for STM
/// @copyright Robert Bosch GmbH 2018-2022
/// @author    VRTE StM Team
//
//=============================================================================

#ifndef BOSCH_VRTE_STM_PLUGINMANAGER_PLUGINFSM_HPP_INCLUDED
#define BOSCH_VRTE_STM_PLUGINMANAGER_PLUGINFSM_HPP_INCLUDED

#include "bosch/vrte/stm/pluginmanager/iplugin.hpp"

namespace bosch
{
namespace vrte
{
namespace stm
{
namespace pluginmanager
{

class CIPluginServerFsmBase;

///
/// \brief Interface for plugins containing a FSM.
///
/// Plugins derived from this interface accept a server object and callback
/// functions for communication with other parts of the STM.
///
class CIPluginFsmBase : public virtual CIPlugin
{
public:
    /// @brief Destructor of CIPlugin
    virtual ~CIPluginFsmBase() = default;
    /// @brief Register pointer of server component
    /// @param [in] f_server STM subcomponent that this plugin is for (CM, OSM, FGM, EH)
    virtual void registerServer(CIPluginServerFsmBase* f_server) = 0;
    /// @brief Get current state of plugin statemachine
    virtual const char* getCurrentState() const = 0;
    /// @brief Get event from STM subcomponent
    /// @param [in] f_event eventID
    /// @param [in] f_data  event payload
    virtual void acceptEvent(const uint64_t f_event, const std::string& f_data = std::string()) = 0;
};

}  // namespace pluginmanager
}  // namespace stm
}  // namespace vrte
}  // namespace bosch

#endif  // BOSCH_VRTE_STM_PLUGINMANAGER_PLUGINFSM_HPP_INCLUDED
