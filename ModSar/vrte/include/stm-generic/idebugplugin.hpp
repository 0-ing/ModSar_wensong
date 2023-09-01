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
/// @file      libs/common/include/bosch/vrte/stm/pluginmanager/idebugplugin.hpp
/// @brief     Interface for debug plugins.
/// @copyright Robert Bosch GmbH 2018-2022
/// @author    VRTE StM Team
//
//=============================================================================

#ifndef BOSCH_VRTE_STM_PLUGINMANAGER_IDEBUGPLUGIN_HPP_INCLUDED
#define BOSCH_VRTE_STM_PLUGINMANAGER_IDEBUGPLUGIN_HPP_INCLUDED

#include "bosch/vrte/stm/pluginmanager/plugin.hpp"

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

namespace cm
{
class CIComponentManager;
}  // namespace cm

namespace fgm
{
class CFunctionGroupManager;
}  // namespace fgm

namespace nm
{
class CNetworkManager;
}  // namespace nm

namespace osm
{
class COperationalStateManager;
}  // namespace osm

namespace sm
{
class CStartupManager;
}  // namespace sm

namespace pluginmanager
{

/// @brief Debug plugins are optional and get access to all internal components.
class CIDebugPlugin : public virtual CIPlugin
{
public:
    virtual ~CIDebugPlugin() = default;

    /// @brief Start the plugin logic.
    ///
    /// @param f_eh         Reference to EH
    /// @param f_cm         Reference to CM
    /// @param f_fgm        Reference to FGM
    /// @param f_nm         Reference to NM
    /// @param f_osm        Reference to OSM
    /// @param f_sm         Reference to SM

    virtual void run(eh::CIEventHandler&            f_eh,
                     cm::CIComponentManager&        f_cm,
                     fgm::CFunctionGroupManager&    f_fgm,
                     nm::CNetworkManager&           f_nm,
                     osm::COperationalStateManager& f_osm,
                     sm::CStartupManager&           f_sm) = 0;
};

}  // namespace pluginmanager
}  // namespace stm
}  // namespace vrte
}  // namespace bosch

#endif  // BOSCH_VRTE_STM_PLUGINMANAGER_IDEBUGPLUGIN_HPP_INCLUDED
