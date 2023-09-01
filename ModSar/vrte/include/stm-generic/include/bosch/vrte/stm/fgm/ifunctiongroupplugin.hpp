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
/// @file      libs/fgm/include/bosch/vrte/stm/fgm/ifunctiongroupplugin.hpp
/// @brief     Interface for FGM plugins.
/// @copyright Robert Bosch GmbH 2018-2022
/// @author    VRTE StM Team
//
//=============================================================================

#ifndef BOSCH_VRTE_STM_FGM_IFUNCTIONGROUPPLUGIN_HPP_INCLUDED
#define BOSCH_VRTE_STM_FGM_IFUNCTIONGROUPPLUGIN_HPP_INCLUDED

#include "bosch/vrte/stm/event.hpp"
#include "bosch/vrte/stm/pluginmanager/iplugin.hpp"

namespace bosch
{
namespace vrte
{
namespace stm
{

class CIEventNames;

namespace eh
{
class CIEventHandler;
}  // namespace eh

namespace fgm
{

class CIFunctionGroup;
class CIFunctionGroupManager;

/// @brief Interface for FGM plugins
class CIFunctionGroupPlugin : public virtual pluginmanager::CIPlugin, public CIEventAcceptor
{
public:
    /**
     * @brief Create the internal state machine.
     *
     * @param f_eh      EventHandler
     * @param f_fg      FunctionGroup
     */
    virtual void create(eh::CIEventHandler& f_eh, CIFunctionGroup& f_fg, CIFunctionGroupManager& f_fgm) = 0;

    /**
     * @brief Destroy the internal state machine.
     */
    virtual void destroy() = 0;
};  // class CIFunctionGroupPlugin

}  // namespace fgm
}  // namespace stm
}  // namespace vrte
}  // namespace bosch

#endif  // BOSCH_VRTE_STM_FGM_IFUNCTIONGROUPPLUGIN_HPP_INCLUDED
