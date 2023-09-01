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
/// @file      tests/VRTE_UT/mocks/include/bosch/vrte/stm/pluginmanager/mockpluginserver.hpp
/// @brief     <tbd>
/// @copyright Robert Bosch GmbH 2018-2022
/// @author    VRTE StM Team
//
//=============================================================================

#ifndef BOSCH_VRTE_STM_PLUGINMANAGER_MOCKPLUGINSERVER_HPP_INCLUDED
#define BOSCH_VRTE_STM_PLUGINMANAGER_MOCKPLUGINSERVER_HPP_INCLUDED

#include "bosch/vrte/stm/pluginmanager/pluginserver.hpp"
#include "gmock/gmock.h"

namespace bosch
{
namespace vrte
{
namespace stm
{
namespace pluginmanager
{

class CMockPluginServerFsmBase : public CIPluginServerFsmBase
{
public:
    virtual ~CMockPluginServerFsmBase() = default;
    MOCK_METHOD1(notifyNewState, void(const char*));
    MOCK_METHOD2(acceptEventCallBack, void(uint64_t, const std::string&));
    MOCK_METHOD3(stateChangeResult, void(const std::string&, const std::string&, bool));
};

}  // namespace pluginmanager
}  // namespace stm
}  // namespace vrte
}  // namespace bosch

#endif  // BOSCH_VRTE_STM_PLUGINMANAGER_MOCKPLUGINSERVER_HPP_INCLUDED
