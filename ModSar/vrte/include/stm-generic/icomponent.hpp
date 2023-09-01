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
/// @file      libs/cm/include/bosch/vrte/stm/cm/icomponent.hpp
/// @brief     Interface definition for Component Proxy class CComponent.
/// @copyright Robert Bosch GmbH 2018-2022
/// @author    VRTE StM Team
//
//=============================================================================

#ifndef BOSCH_VRTE_STM_CM_ICOMPONENT_HPP_INCLUDED
#define BOSCH_VRTE_STM_CM_ICOMPONENT_HPP_INCLUDED

#include "bosch/vrte/stm/cm/types.hpp"

#include <chrono>
#include <memory>
#include <string>

namespace bosch
{
namespace vrte
{
namespace stm
{
namespace cm
{

class CIComponentPlugin;

class CIComponent
{
public:
    /// @brief Default destructor
    virtual ~CIComponent() = default;

    /// @brief Get the components name.
    ///
    /// @return                 Name
    virtual const std::string& getName() const = 0;

    /// @brief Request the connected component to move to new state.
    ///
    /// If a state request is already running, the new request will be queued.
    /// In case the component is configured to be an extended component
    /// The currently running transition will be aborted and a new one started.
    ///
    /// @param[in] f_state          Component state to be set.
    /// @param[in] f_mode           RequestMode (e.g. force/voluntary)
    /// @param[in] f_retries        Number of retries before a kForced request is sent.
    ///                             Ignored if f_mode already is set to kForced.
    ///                             Will result in the first + f_retries + forced requests in total.
    ///                             Every retry will have
    /// @param[in] f_timeout        Timeout for requests.
    /// @param[in] f_abortCurrent   Abort any currently ongoing requests.
    virtual void requestState(const std::string&        f_state,
                              ERequestMode              f_mode,
                              uint32_t                  f_retries,
                              std::chrono::milliseconds f_timeout,
                              bool                      f_abortCurrent = false) = 0;

    /// @brief Callback on changed component state.
    ///
    /// Will call the callback function provided in requestState().
    ///
    /// @param[in] f_state      New component state.
    /// @param[in] f_event      New component status (encoded in event).
    virtual void onStateChanged(const std::string& f_state, uint64_t f_event) = 0;

    /// @brief Get last confirmed state.
    ///
    /// @return                 Last requested state.
    virtual const std::string& getState() const = 0;

    /// @brief Return plugin this component is mapped to.
    ///
    /// @return                 Pointer to plugin.
    virtual std::weak_ptr<CIComponentPlugin> getPlugin() const = 0;

    /// @brief Set the plugin for this component.
    ///
    /// @param f_plugin         Plugin for this component
    virtual void setPlugin(std::weak_ptr<CIComponentPlugin> f_plugin) = 0;
};

}  // namespace cm
}  // namespace stm
}  // namespace vrte
}  // namespace bosch

#endif  // BOSCH_VRTE_STM_CM_ICOMPONENT_HPP_INCLUDED
