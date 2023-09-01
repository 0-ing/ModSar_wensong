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
/// @file      libs/sm/include/bosch/vrte/stm/sm/fgstartupconfiguration.hpp
/// @brief     lass of Startup Manager
/// @copyright Robert Bosch GmbH 2018-2022
/// @author    VRTE StM Team
//
//=============================================================================

#ifndef BOSCH_VRTE_STM_SM_FGSTARTUPCONFIGURATION_HPP_INCLUDED
#define BOSCH_VRTE_STM_SM_FGSTARTUPCONFIGURATION_HPP_INCLUDED

#include <string>
#include <vector>

namespace bosch
{
namespace vrte
{
namespace stm
{
namespace sm
{

/// @brief FG synchronisation point definition
struct FGSyncPoint
{
    enum SyncPointType : uint16_t
    {
        kFGActivated = 0,
        kFreeDefined
    };

    // Name of function group whose activation is a syncronization point
    std::string fgName;

    // Type of synchronisation
    SyncPointType syncType;
};

/// @brief Internal startup configuration struct
struct FGStartupConfiguration
{
    /// @brief      Constructor
    /// @param f_name Name of function group (FG) which is being configured
    /// @param f_event Event to send for the activation of this FG
    /// @param f_eventData Data part of the event for the activation of this FG
    /// @param f_fgDependencies List of function groups start of whom is
    /// prerequisite for the activation of this FG
    FGStartupConfiguration(const std::string&              f_name,
                           uint64_t                        f_event,
                           const std::string&              f_eventData,
                           const std::vector<FGSyncPoint>& f_fgDependencies = {})
        : activation{f_event, f_eventData}
        , name{f_name}
        , fgDependencies{f_fgDependencies}
    {
    }

    struct
    {
        // Event to send for activation.
        uint64_t event;

        // Data part of the event for activation
        std::string eventData;
    } activation;

    // Function group name
    std::string name;

    // List of function groups that have to be started before requesting
    // initial state change of this function group.
    std::vector<FGSyncPoint> fgDependencies;
};

}  // namespace sm
}  // namespace stm
}  // namespace vrte
}  // namespace bosch

#endif /* BOSCH_VRTE_STM_SM_FGSTARTUPCONFIGURATION_HPP_INCLUDED */
