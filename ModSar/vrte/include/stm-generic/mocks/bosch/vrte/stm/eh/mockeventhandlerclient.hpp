//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018-2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================
//
/// @file      tests/VRTE_UT/mocks/include/bosch/vrte/stm/eh/mockeventhandlerclient.hpp
/// @brief     Mock class of Event Handler client for unit test
/// @copyright Robert Bosch GmbH 2018-2021
/// @author    VRTE StM Team
//
//=============================================================================

#ifndef BOSCH_VRTE_STM_EH_MOCKEVENTHANDLERCLIENT_HPP_INCLUDED
#define BOSCH_VRTE_STM_EH_MOCKEVENTHANDLERCLIENT_HPP_INCLUDED

#include "bosch/vrte/stm/eh/iexternalinterface.hpp"
#include "gmock/gmock.h"

namespace bosch
{
namespace vrte
{
namespace stm
{
namespace testing
{

class CMockEventHandlerClient : public eh::CIExternalInterface
{
public:
    CMockEventHandlerClient()          = default;
    virtual ~CMockEventHandlerClient() = default;

    MOCK_METHOD2(acceptEventFromEh, void(uint64_t f_event, const std::string& f_data));
};

}  // namespace testing
}  // namespace stm
}  // namespace vrte
}  // namespace bosch

#endif  // BOSCH_VRTE_STM_EH_MOCKEVENTHANDLERCLIENT_HPP_INCLUDED
