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
/// @file      tests/VRTE_UT/mocks/include/bosch/vrte/stm/osm/mockfsmmanagerosm.hpp
/// @brief     Fsm Manager Mock class of OSM header file
/// @copyright Robert Bosch GmbH 2018-2022
/// @author    VRTE StM Team
//
//=============================================================================

#ifndef BOSCH_VRTE_STM_OSM_MOCKFSMMANAGEROSM_HPP_INCLUDED
#define BOSCH_VRTE_STM_OSM_MOCKFSMMANAGEROSM_HPP_INCLUDED

#include "bosch/vrte/stm/pluginmanager/pluginfsm.hpp"
#include "bosch/vrte/stm/pluginmanager/pluginserver.hpp"
#include "gmock/gmock.h"

namespace bosch
{
namespace vrte
{
namespace stm
{

class CMockFsmManagerOSM : public pluginmanager::CIPluginFsmBase
{
public:
    CMockFsmManagerOSM(){};
    virtual ~CMockFsmManagerOSM(){};
    MOCK_CONST_METHOD0(getName, const std::string&());
    MOCK_CONST_METHOD0(getVersion, uint32_t());
    MOCK_CONST_METHOD0(getType, pluginmanager::EPluginType());
    MOCK_CONST_METHOD0(getServer, pluginmanager::EServerPlugin());
    MOCK_METHOD1(registerServer, void(pluginmanager::CIPluginServerFsmBase*));
    MOCK_METHOD2(acceptEvent, void(const uint64_t, const std::string&));
    MOCK_CONST_METHOD0(getCurrentState, const char*());
};

}  // namespace stm
}  // namespace vrte
}  // namespace bosch

#endif  // BOSCH_VRTE_STM_OSM_MOCKFSMMANAGEROSM_HPP_INCLUDED
