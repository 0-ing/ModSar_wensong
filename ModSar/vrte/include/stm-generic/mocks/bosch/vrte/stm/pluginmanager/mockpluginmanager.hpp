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
/// @file      tests/VRTE_UT/mocks/include/bosch/vrte/stm/pluginmanager/mockpluginmanager.hpp
/// @brief     mock class of pluginmanager interface for STM unit test usage
/// @copyright Robert Bosch GmbH 2018-2022
/// @author    VRTE StM Team
//
//=============================================================================

#ifndef BOSCH_VRTE_STM_PLUGINMANAGER_MOCKPLUGINMANAGER_HPP_INCLUDED
#define BOSCH_VRTE_STM_PLUGINMANAGER_MOCKPLUGINMANAGER_HPP_INCLUDED

#include "bosch/vrte/stm/pluginmanager/pluginmanager.hpp"
#include "gmock/gmock.h"

namespace bosch
{
namespace vrte
{
namespace stm
{
namespace pluginmanager
{

class CMockPluginManager : public CIPluginManager
{
public:
    CMockPluginManager() {}
    virtual ~CMockPluginManager() {}
    MOCK_METHOD1(load, void(const std::string&));
    MOCK_METHOD1(loadPluginStatic, void(std::shared_ptr<CIPlugin>));
    MOCK_METHOD2(get, std::weak_ptr<CIPlugin>(pluginmanager::EServerPlugin, const std::string&));
    MOCK_METHOD3(get,
                 std::weak_ptr<CIPlugin>(pluginmanager::EServerPlugin, pluginmanager::EPluginType, const std::string&));
    MOCK_METHOD2(getAll,
                 std::vector<std::weak_ptr<CIPlugin>>(pluginmanager::EServerPlugin, pluginmanager::EPluginType));
    MOCK_METHOD2(unload, bool(pluginmanager::EServerPlugin, const std::string&));
    MOCK_METHOD2(unload, bool(pluginmanager::EServerPlugin, pluginmanager::EPluginType));
    MOCK_METHOD3(registerCallback, void(pluginmanager::EServerPlugin, const std::string&, callback_t));
    MOCK_METHOD2(unregisterCallback, void(pluginmanager::EServerPlugin, const std::string&));
};

}  // namespace pluginmanager
}  // namespace stm
}  // namespace vrte
}  // namespace bosch

#endif  // BOSCH_VRTE_STM_PLUGINMANAGER_MOCKPLUGINMANAGER_HPP_INCLUDED
