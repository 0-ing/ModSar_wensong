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
/// @file      libs/fgm/include/bosch/vrte/stm/fgm/functiongroupmanager.hpp
/// @brief     State Management subcomponent FunctionGroupManager, main class
/// @copyright Robert Bosch GmbH 2018-2022
/// @author    VRTE StM Team
//
//=============================================================================

#ifndef BOSCH_VRTE_STM_FGM_FUNCTIONGROUPMANAGER_HPP_INCLUDED
#define BOSCH_VRTE_STM_FGM_FUNCTIONGROUPMANAGER_HPP_INCLUDED

#include <memory>
#include <string>
#include <vector>

// event
#include "bosch/vrte/stm/eventloop.hpp"

// fgm
#include "bosch/vrte/stm/fgm/ifunctiongroup.hpp"
#include "bosch/vrte/stm/fgm/ifunctiongroupmanager.hpp"

#include "bosch/vrte/stm/pluginmanager/pluginmanager.hpp"

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

namespace fgm
{

/// @brief The main class of FGM - CFunctionGroupManager
class CFunctionGroupManager : public CIFunctionGroupManager
{
public:
    /// @brief Initialize data member of class CFunctionGroupManager.
    ///        Get configured data from ECUConfig.
    ///        FGM registers to each FunctionGroup to receive and handle their notifications.
    /// @param [in] f_eh: Back reference to event handler
    explicit CFunctionGroupManager(eh::CIEventHandler& f_eh);

    /// @brief Destructor. Stops running FGMMainThread.
    ///        Unregister to each FunctionGroup to not receive and handle their notifications.
    ///        Do activities to release resources if any.
    virtual ~CFunctionGroupManager();

    /// @brief Implement method of interface CIEventAcceptor::acceptEvent().
    ///        Create a EventTask and add it into the queue of FGM-tasks to be processed later
    ///
    /// @param [in] f_event: The event FGM shall evaluate
    /// @param [in] f_data:  Event payload
    void acceptEvent(const uint64_t f_event, const std::string& f_data) override;

    /// @brief Start event loop
    virtual void run();

    /// @brief Get function group by name.
    ///
    /// @param [in] f_fgName: Function group name
    ///
    /// @return               Invalid pointer when the function group does not exists.
    std::shared_ptr<CIFunctionGroup> getFunctionGroup(const std::string& f_fgName) const;

protected:
    /// @brief Classify the FGM-task and dispatch it to appropriate handler.
    ///
    /// @param [in] f_event: Received event
    /// @param [in] f_data:  Optional string data
    virtual void handleEvent(uint64_t f_event, const std::string& f_data);

    ///< List of all FunctionGroup
    std::vector<std::shared_ptr<CIFunctionGroup>> m_functionGroups;

    ///< Reference to EH component
    eh::CIEventHandler& m_eh;

    CEventLoop m_events;
};  // class CFunctionGroupManager

}  // namespace fgm
}  // namespace stm
}  // namespace vrte
}  // namespace bosch

#endif  // BOSCH_VRTE_STM_FGM_FUNCTIONGROUPMANAGER_HPP_INCLUDED
