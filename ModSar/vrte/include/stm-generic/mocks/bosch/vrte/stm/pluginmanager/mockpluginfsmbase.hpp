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
/// @file      tests/VRTE_UT/mocks/include/bosch/vrte/stm/pluginmanager/mockpluginfsmbase.hpp
/// @brief     Mock class for pluginmanager::CIPluginFsmBase
/// @copyright Robert Bosch GmbH 2018-2022
/// @author    VRTE StM Team
//
//=============================================================================

#ifndef BOSCH_VRTE_STM_PLUGINMANAGER_MOCKPLUGINFSMBASE_HPP_INCLUDED
#define BOSCH_VRTE_STM_PLUGINMANAGER_MOCKPLUGINFSMBASE_HPP_INCLUDED

#include "bosch/vrte/stm/pluginmanager/pluginfsm.hpp"
#include "gmock/gmock.h"

namespace bosch
{
namespace vrte
{
namespace stm
{
namespace pluginmanager
{

class CMockPluginFsmBase : public CIPluginFsmBase
{
public:
    MOCK_CONST_METHOD0(getVersion, uint32_t());
    MOCK_CONST_METHOD0(getName, const std::string&());
    MOCK_CONST_METHOD0(getType, EPluginType());
    MOCK_CONST_METHOD0(getServer, EServerPlugin());
    MOCK_METHOD1(registerServer, void(CIPluginServerFsmBase* f_server));
    MOCK_CONST_METHOD0(getCurrentState, const char*());
    MOCK_METHOD2(acceptEvent, void(const uint64_t f_event, const std::string& f_data));
};

}  // namespace pluginmanager
}  // namespace stm
}  // namespace vrte
}  // namespace bosch

#endif  // BOSCH_VRTE_STM_PLUGINMANAGER_MOCKPLUGINFSMBASE_HPP_INCLUDED
