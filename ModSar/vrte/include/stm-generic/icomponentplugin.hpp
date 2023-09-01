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
/// @file      libs/cm/include/bosch/vrte/stm/cm/icomponentplugin.hpp
/// @brief     State Management internal interface for state handler input.
/// @copyright Robert Bosch GmbH 2018-2022
/// @author    VRTE StM Team
//
//=============================================================================

#ifndef BOSCH_VRTE_STM_CM_ICOMPONENTPLUGIN_HPP_INCLUDED
#define BOSCH_VRTE_STM_CM_ICOMPONENTPLUGIN_HPP_INCLUDED

#include "bosch/vrte/stm/cm/types.hpp"
#include "bosch/vrte/stm/pluginmanager/iplugin.hpp"

#include <cstdint>
#include <string>

namespace bosch
{
namespace vrte
{
namespace stm
{

class CIEventAcceptor;

namespace cm
{

class CIComponent;

/// @brief Component plugin interface.
class CIComponentPlugin : public virtual pluginmanager::CIPlugin
{
public:
    /// @brief Default destructor
    virtual ~CIComponentPlugin() = default;

    /// @brief Register component.
    ///
    /// @param[in] f_component  Component
    virtual void registerComponent(CIComponent* f_component) = 0;

    /// @brief Unregister component.
    ///
    /// @param[in] f_component  Component
    virtual void unregisterComponent(CIComponent* f_component) = 0;

    /// @brief Handle event.
    ///
    /// @param[in] f_event      Event
    virtual void acceptEvent(const uint64_t f_event) = 0;

    /// @brief Set pointer to EH.
    ///
    /// @param f_eh             Event Handler
    virtual void setEventHandler(CIEventAcceptor* f_eh) = 0;

    /// @brief Callback for state change requests.
    ///
    /// This callback will be called by every component once its state
    /// change finished (successfully or not).
    ///
    /// @param[in] f_component      Component
    /// @param[in] f_state          New component state
    /// @param[in] f_status         New component status
    virtual void requestCallback(CIComponent* f_component, const std::string& f_state, EStdReturnType f_status) = 0;
};

}  // namespace cm
}  // namespace stm
}  // namespace vrte
}  // namespace bosch

#endif  // BOSCH_VRTE_STM_CM_ICOMPONENTPLUGIN_HPP_INCLUDED
