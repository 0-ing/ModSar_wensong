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
/// @file      libs/fgm/include/bosch/vrte/stm/fgm/functiongroup.hpp
/// @brief     State Management subcomponent FunctionGroupManager
///            provides:
///              + information of a specific Function Group
///              + APIs to FGM to invoke remote call SetStat/GetState and handle
///                asynchronous result from ExM
/// @copyright Robert Bosch GmbH 2018-2022
/// @author    VRTE StM Team
//
//=============================================================================

#ifndef BOSCH_VRTE_STM_FGM_FUNCTIONGROUP_HPP_INCLUDED
#define BOSCH_VRTE_STM_FGM_FUNCTIONGROUP_HPP_INCLUDED

#include <memory>
#include <string>
#include <vector>

#include "bosch/vrte/stm/fgm/ifunctiongroup.hpp"

namespace bosch
{
namespace vrte
{
namespace stm
{

namespace eh
{
class CIEventHandler;
}  // namespace eh

namespace pluginmanager
{
class CIPluginManager;
}  // namespace pluginmanager

namespace fgm
{

class CIFunctionGroupPlugin;
class CIFunctionGroupManager;

/// @brief This class acts as a proxy to the FSM plugin of a function group.
class CFunctionGroup : public CIFunctionGroup
{
public:
    /// @brief Constructor
    ///
    /// @param [in] f_name             Function group name
    /// @param [in] f_pluginName       Plugin name related to function group
    /// @param [in] f_eh               Reference to EventHandler
    /// @param [in] f_pluginManager    Reference to plugin manager
    /// @param [in] f_fgm              Reference to FunctionGroupManager
    CFunctionGroup(const std::string&              f_name,
                   const std::string&              f_pluginName,
                   eh::CIEventHandler&             f_eh,
                   pluginmanager::CIPluginManager& f_pluginManager,
                   CIFunctionGroupManager&         f_fgm);

    /// @brief Destructor
    virtual ~CFunctionGroup();

    /// @brief See documentation in CIFunctionGroup
    void acceptEvent(const uint64_t f_event, const std::string& f_data) override;

    /// @brief See documentation in CIFunctionGroup
    const std::string& getName() const override;

protected:
    std::string                          m_name;
    std::string                          m_pluginName;
    eh::CIEventHandler&                  m_eh;
    pluginmanager::CIPluginManager&      m_pluginManager;
    CIFunctionGroupManager&              m_fgm;
    std::weak_ptr<CIFunctionGroupPlugin> m_plugin;
};  // class CFunctionGroup

}  // namespace fgm
}  // namespace stm
}  // namespace vrte
}  // namespace bosch

#endif  // BOSCH_VRTE_STM_FGM_FUNCTIONGROUP_HPP_INCLUDED
