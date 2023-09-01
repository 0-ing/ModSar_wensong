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
/// @file      tests/VRTE_UT/mocks/include/bosch/vrte/stm/cm/mockcomponentplugin.hpp
/// @brief     Mock of STM class cm::CIComponentPlugin
/// @copyright Robert Bosch GmbH 2018-2022
/// @author    VRTE StM Team
//
//=============================================================================

#ifndef BOSCH_VRTE_STM_CM_MOCKCOMPONENTPLUGIN_HPP_INCLUDED
#define BOSCH_VRTE_STM_CM_MOCKCOMPONENTPLUGIN_HPP_INCLUDED

#include "bosch/vrte/stm/cm/icomponentplugin.hpp"

#include "gmock/gmock.h"

namespace bosch
{
namespace vrte
{
namespace stm
{
namespace testing
{

class CMockComponentPlugin : public cm::CIComponentPlugin
{
public:
    MOCK_METHOD1(registerComponent, void(cm::CIComponent*));
    MOCK_METHOD1(unregisterComponent, void(cm::CIComponent*));

    MOCK_METHOD1(acceptEvent, void(const uint64_t));
    MOCK_METHOD1(setEventHandler, void(CIEventAcceptor*));

    MOCK_CONST_METHOD0(getVersion, uint32_t());
    MOCK_CONST_METHOD0(getName, const std::string&());
    MOCK_CONST_METHOD0(getType, pluginmanager::EPluginType());
    MOCK_CONST_METHOD0(getServer, pluginmanager::EServerPlugin());
    MOCK_METHOD3(requestCallback, void(cm::CIComponent*, const std::string&, EStdReturnType));
};

}  // namespace testing
}  // namespace stm
}  // namespace vrte
}  // namespace bosch

#endif  // BOSCH_VRTE_STM_CM_MOCKCOMPONENTPLUGIN_HPP_INCLUDED
