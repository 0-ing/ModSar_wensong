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
/// @file      tests/VRTE_UT/mocks/include/bosch/vrte/stm/eh/mockeventhandler.hpp
/// @brief     Mock for eh::CIEventHandler
/// @copyright Robert Bosch GmbH 2018-2022
/// @author    VRTE StM Team
//
//=============================================================================

#ifndef BOSCH_VRTE_STM_EH_MOCKEVENTHANDLER_HPP_INCLUDED
#define BOSCH_VRTE_STM_EH_MOCKEVENTHANDLER_HPP_INCLUDED

#include "bosch/vrte/stm/eh/ieventhandler.hpp"
#include "bosch/vrte/stm/eh/iexternalinterface.hpp"
#include "bosch/vrte/stm/eventnamesgenerated.hpp"
#include "bosch/vrte/stm/types.hpp"
#include "gmock/gmock.h"

#include <sstream>
#include <string>

namespace bosch
{
namespace vrte
{
namespace stm
{
namespace testing
{

class Mock_EventHandler : public eh::CIEventHandler
{
public:
    MOCK_METHOD2(acceptEvent, void(const uint64_t, const std::string&));
    MOCK_METHOD1(intRegisterAtEventHandler, EStdReturnType(eh::CIExternalInterface& ehClient));
    MOCK_METHOD1(intRemoveClientAtEventHandler, EStdReturnType(eh::CIExternalInterface& ehClient));
    MOCK_METHOD1(registerClient, void(osm::CIOperationalStateManager*));
    MOCK_METHOD1(registerClient, void(fgm::CIFunctionGroupManager*));
    MOCK_METHOD1(registerClient, void(cm::CIComponentManager*));
    MOCK_METHOD1(registerClient, void(sm::CIStartupManager*));
    MOCK_METHOD1(registerClient, void(nm::CINetworkManager*));

    std::string getEventInfo(const uint64_t f_event, const std::string& f_data = std::string())
    {
        std::stringstream ss;
        std::string       eventName;

        auto it = bosch::vrte::stm::g_eventNameMap.find(f_event);

        if (it == bosch::vrte::stm::g_eventNameMap.end())
        {
            eventName = bosch::vrte::stm::strevent(f_event);
            ss << eventName;
        }
        else
        {
            eventName = it->second;
            ss << "<" << eventName << ">";
        }

        if (f_data != std::string())
        {
            ss << "<" << f_data << ">";
        }

        return ss.str();
    }
};

}  // namespace testing
}  // namespace stm
}  // namespace vrte
}  // namespace bosch

#endif  // BOSCH_VRTE_STM_EH_MOCKEVENTHANDLER_HPP_INCLUDED
