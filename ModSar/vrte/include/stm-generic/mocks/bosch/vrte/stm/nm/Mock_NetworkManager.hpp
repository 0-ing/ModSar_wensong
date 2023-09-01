//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018-2022 by DENSO Corporation. All rights reserved.
//
// This file is property of DENSO Corporation. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================
//
/// @file      tests/VRTE_UT/mocks/include/bosch/vrte/stm/nm/Mock_NetworkManager.hpp
/// @brief     Mock for nm::CINetworkManager
/// @copyright DENSO Corporation 2018-2022
/// @author    VRTE StM Team
//
//=============================================================================

#ifndef BOSCH_VRTE_STM_NM_MOCK_NMSUBCOMPONENT_HPP_INCLUDED
#define BOSCH_VRTE_STM_NM_MOCK_NMSUBCOMPONENT_HPP_INCLUDED

#include "gmock/gmock.h"

#include "bosch/vrte/stm/nm/inetworkmanager.hpp"
#include "bosch/vrte/stm/types.hpp"

namespace bosch
{
namespace vrte
{
namespace stm
{
namespace testing
{

class Mock_NetworkManager : public nm::CINetworkManager
{
public:
    virtual ~Mock_NetworkManager() = default;

    MOCK_METHOD2(acceptEvent, void(const uint64_t f_event, const std::string& f_data));
};

}  // namespace testing
}  // namespace stm
}  // namespace vrte
}  // namespace bosch

#endif  // BOSCH_VRTE_STM_NM_MOCK_NMSUBCOMPONENT_HPP_INCLUDED
