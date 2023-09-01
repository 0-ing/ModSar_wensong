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
/// @file      tests/VRTE_UT/mocks/include/bosch/vrte/stm/sm/Mock_StartupManager.hpp
/// @brief     Mock for sm::CIStartupManager
/// @copyright Robert Bosch GmbH 2018-2022
/// @author    VRTE StM Team
//
//=============================================================================

#ifndef BOSCH_VRTE_STM_SM_MOCK_STARTUPMANAGER_HPP_INCLUDED
#define BOSCH_VRTE_STM_SM_MOCK_STARTUPMANAGER_HPP_INCLUDED

#include "gmock/gmock.h"

#include "bosch/vrte/stm/sm/istartupmanager.hpp"
#include "bosch/vrte/stm/types.hpp"

namespace bosch
{
namespace vrte
{
namespace stm
{
namespace testing
{

class Mock_StartupManager : public sm::CIStartupManager
{
public:
    virtual ~Mock_StartupManager() = default;

    MOCK_METHOD2(acceptEvent, void(const uint64_t f_event, const std::string& f_data));
};

}  // namespace testing
}  // namespace stm
}  // namespace vrte
}  // namespace bosch

#endif  // BOSCH_VRTE_STM_SM_MOCK_STARTUPMANAGER_HPP_INCLUDED
