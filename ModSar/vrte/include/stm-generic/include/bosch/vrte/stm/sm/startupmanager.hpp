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
/// @file      libs/sm/include/bosch/vrte/stm/sm/startupmanager.hpp
/// @brief     Class of Startup Manager
/// @copyright Robert Bosch GmbH 2018-2022
/// @author    VRTE StM Team
//
//=============================================================================

#ifndef BOSCH_VRTE_STM_SM_STARTUPMANAGER_HPP_INCLUDED
#define BOSCH_VRTE_STM_SM_STARTUPMANAGER_HPP_INCLUDED

#include "bosch/vrte/stm/eventloop.hpp"
#include "bosch/vrte/stm/sm/fgstartupconfiguration.hpp"
#include "bosch/vrte/stm/sm/istartupmanager.hpp"
#include "bosch/vrte/stm/thread.hpp"
#include "bosch/vrte/stm/types.hpp"

#include <list>
#include <map>
#include <set>
#include <string>
#include <vector>

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

namespace sm
{

class CStartupManager : public CIStartupManager
{

public:
    /// @brief      Constructor
    /// @param f_eh Reference to EventHandler
    CStartupManager(eh::CIEventHandler& f_eh);

    /// @brief SM destructor
    virtual ~CStartupManager();

    /// @brief get an event from event handler
    void acceptEvent(const uint64_t f_event, const std::string& f_data) override;

    //// @brief Establishes all communications with other components.
    ///         Register to receive information from CM via two interfaces
    ///         AllComponentsOfExecutableRegistered and AllComponentsOfExecutableReachedFirstState
    ///         Get state of MachineFG from FGM
    virtual void run();

protected:
    /// @brief   Check and activate FGs having no unresolved dependency to start
    /// @return  void
    /// @details Activates all FG having no unresolved dependency
    ///          Traverses m_listOfFGRemainingToStart from head to end
    ///          If an FG is OK to activate then request FGM to activate FG.
    ///          Update m_databaseFG and m_listOfFGRemainingToStart after activating
    ///          If m_listOfFGRemainingToStart gets empty, ends SM startup procedure
    ///          No check against conditions SM startup and initial machine startup
    void activateNextFGs();

    /// @brief Add new Function Group to list
    ///
    /// @param [in] f_fgInfo Function Group information
    bool addToFGDatabase(const FGStartupConfiguration& f_fgInfo);

    /// @brief Handle received event.
    /// @param f_event : received event
    /// @param f_data  : event payload
    /// @details Project side extension function shall forward all events it received
    /// to this functions after processing them
    ///          Processes Get MachineFG State Success event and sets machine state reached accordingly
    //           Calls outside EventLoop thread context shall be synchronized
    virtual void handleEvent(uint64_t f_event, const std::string& f_data) = 0;

    /// @brief Check Function Group has any unresolved dependency
    ///
    /// @param [in] f_fgInfo: Function Group information
    /// @return  true if given FG has at least one unresolved dependency
    //           Calls outside EventLoop thread context shall be synchronized
    bool hasUnresolvedDependencies(const FGStartupConfiguration& f_fgInfo) const;

    /// @brief Sends activation request events for given FG
    ///
    /// @param [in] f_fgInfo: Function Group information
    /// @details Sets activation status of this FG to requested
    //           Calls outside EventLoop thread context shall be synchronized
    void activateFG(const FGStartupConfiguration& f_fgInfo);

    /// @brief Triggers a new activation check after checking pre conditions
    ///
    /// @details Active if SM startup has not been reached and initial machine state startup has been reached
    ///          Invokes checkFGToActivate
    //           Calls outside EventLoop thread context shall be synchronized
    void processRemainingFGs();

    /// @brief Sets internally machine state startup reached to true and triggers a new activation check
    ///
    /// @details Active if SM startup has not been reached and initial machine startup has been reached
    ///          Invokes processRemainingFGs
    //           Calls outside EventLoop thread context shall be synchronized
    void machineStateStartupReached();

    /// @brief Returns status of machine state startup reached
    ///
    /// @return  true if machine state startup is reached
    /// @details Calls outside EventLoop thread context shall be synchronized
    bool isMachineStateStartupReached() const;

    /// @brief Resolves given sync point if configured
    ///
    /// @param [in] f_syncPoint: SyncPoint information to be checked against configured ones
    /// @details Calls outside EventLoop thread context shall be synchronized
    /// Does not initiate new activation check (processRemainingFGs() shall be called explicitly)
    void resolveFGSyncPoint(const FGSyncPoint& f_syncPoint);

    /// @brief  Check an FG is in database or not
    ///
    /// @param [in] f_FgName: Function Group name
    /// @return  true if the FG in database
    /// @details Calls outside EventLoop thread context shall be synchronized
    bool inDatabase(std::string f_fgName) const;

    /// @brief Notify to client of SM that StartupFinished reached
    /// @details Calls outside EventLoop thread context shall be synchronized
    void onStartupFinishedReached();

    CEventLoop m_events;

    bool m_startupFinished;

    bool m_isMachineStateStartupReached;  /// true if MachineFG reached Startup already

    std::map<std::string, FGStartupConfiguration> m_databaseFG;

    std::list<std::string> m_listOfFGRemainingToStart;

    struct SyncPointCompare
    {
        bool operator()(const FGSyncPoint& lhs, const FGSyncPoint& rhs) const
        {
            return (lhs.fgName < rhs.fgName) || ((!(rhs.fgName < lhs.fgName)) && (lhs.syncType < rhs.syncType));
        }
    };

    std::set<FGSyncPoint, SyncPointCompare> m_setUnresolvedFGSyncPoints;

    eh::CIEventHandler& m_eh;  /// Reference to EventHandler
};

}  // namespace sm
}  // namespace stm
}  // namespace vrte
}  // namespace bosch

#endif /* BOSCH_VRTE_STM_SM_STARTUPMANAGER_HPP_INCLUDED */
