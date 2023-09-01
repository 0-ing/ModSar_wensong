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
/// @file      tests/VRTE_UT/mocks/include/bosch/vrte/stm/cm/mockcomponentmanager.hpp
/// @brief     Mock of STM class cm::CIComponentManager
/// @copyright Robert Bosch GmbH 2018-2022
/// @author    VRTE StM Team
//
//=============================================================================

#ifndef BOSCH_VRTE_STM_CM_MOCKCOMPONENTMANAGER_HPP_INCLUDED
#define BOSCH_VRTE_STM_CM_MOCKCOMPONENTMANAGER_HPP_INCLUDED

#include "bosch/vrte/stm/cm/icomponentmanager.hpp"

#include "gmock/gmock.h"

namespace bosch
{
namespace vrte
{
namespace stm
{
namespace testing
{

class CMockComponentManager : public cm::CIComponentManager
{
public:
    MOCK_METHOD1(forwardToEventHandler, void(uint64_t));
    MOCK_METHOD0(getComponentDebugInfos, std::vector<ComponentDebugInfo>());
    MOCK_METHOD2(acceptEvent, void(const uint64_t f_event, const std::string& f_data));
};

}  // namespace testing
}  // namespace stm
}  // namespace vrte
}  // namespace bosch

#endif  // BOSCH_VRTE_STM_CM_MOCKCOMPONENTMANAGER_HPP_INCLUDED
