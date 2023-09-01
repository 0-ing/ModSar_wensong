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
/// @file      tests/VRTE_UT/mocks/include/bosch/vrte/stm/fgm/Mock_FunctionGroupPlugin.hpp
/// @brief     Mock class for CIFunctionGroup
/// @copyright Robert Bosch GmbH 2018-2022
/// @author    VRTE StM Team
//
//=============================================================================

#ifndef BOSCH_VRTE_STM_FGM_MOCK_FUNCTIONGROUPPLUGIN_HPP_INCLUDED
#define BOSCH_VRTE_STM_FGM_MOCK_FUNCTIONGROUPPLUGIN_HPP_INCLUDED

#include "bosch/vrte/stm/fgm/ifunctiongroupplugin.hpp"

#include "gmock/gmock.h"

namespace bosch
{
namespace vrte
{
namespace stm
{
namespace testing
{

class Mock_CFunctionGroupPlugin : public fgm::CIFunctionGroupPlugin
{
public:
    // CIPlugin
    MOCK_CONST_METHOD0(getVersion, uint32_t());
    MOCK_CONST_METHOD0(getName, const std::string&());
    MOCK_CONST_METHOD0(getType, pluginmanager::EPluginType());
    MOCK_CONST_METHOD0(getServer, pluginmanager::EServerPlugin());

    // CIEventAcceptor
    MOCK_METHOD2(acceptEvent, void(const uint64_t f_event, const std::string& f_data));

    // CIFunctionGroupPlugin
    MOCK_METHOD3(create,
                 void(eh::CIEventHandler& f_eh, fgm::CIFunctionGroup& f_fg, fgm::CIFunctionGroupManager& f_fgm));
    MOCK_METHOD0(destroy, void());
};

}  // namespace testing
}  // namespace stm
}  // namespace vrte
}  // namespace bosch

#endif  // BOSCH_VRTE_STM_FGM_MOCK_FUNCTIONGROUPPLUGIN_HPP_INCLUDED
