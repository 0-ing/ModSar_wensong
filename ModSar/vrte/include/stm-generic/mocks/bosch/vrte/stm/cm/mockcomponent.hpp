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
/// @file      tests/VRTE_UT/mocks/include/bosch/vrte/stm/cm/mockcomponent.hpp
/// @brief     Mock of STM class cm::CIComponent
/// @copyright Robert Bosch GmbH 2018-2022
/// @author    VRTE StM Team
//
//=============================================================================

#ifndef BOSCH_VRTE_STM_CM_MOCKCOMPONENT_HPP_INCLUDED
#define BOSCH_VRTE_STM_CM_MOCKCOMPONENT_HPP_INCLUDED

#include "bosch/vrte/stm/cm/icomponent.hpp"

#include "gmock/gmock.h"

namespace bosch
{
namespace vrte
{
namespace stm
{
namespace testing
{

class CMockComponent : public cm::CIComponent
{
public:
    MOCK_CONST_METHOD0(getName, const std::string&(void));
    MOCK_METHOD5(requestState, void(const std::string&, cm::ERequestMode, uint32_t, std::chrono::milliseconds, bool));
    MOCK_METHOD2(onStateChanged, void(const std::string&, uint64_t));
    MOCK_CONST_METHOD0(getState, const std::string&());
    MOCK_CONST_METHOD0(getPlugin, std::weak_ptr<cm::CIComponentPlugin>());
    MOCK_METHOD1(setPlugin, void(std::weak_ptr<cm::CIComponentPlugin>));
};

}  // namespace testing
}  // namespace stm
}  // namespace vrte
}  // namespace bosch

#endif  // BOSCH_VRTE_STM_CM_MOCKCOMPONENT_HPP_INCLUDED
