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
/// @file      tests/VRTE_UT/mocks/include/bosch/vrte/stm/persistency/mockpersistencyhandler.hpp
/// @brief     Mock of STM class persistency::CIPersistencyHandler
/// @copyright Robert Bosch GmbH 2018-2022
/// @author    VRTE StM Team
//
//=============================================================================

#ifndef BOSCH_VRTE_STM_PERSISTENCY_MOCKPERSISTENCYHANDLER_HPP_INCLUDED
#define BOSCH_VRTE_STM_PERSISTENCY_MOCKPERSISTENCYHANDLER_HPP_INCLUDED

#include "bosch/vrte/stm/persistency/ipersistencyhandler.hpp"

#include "gmock/gmock.h"

namespace bosch
{
namespace vrte
{
namespace stm
{
namespace testing
{

class CMockPersistencyHandler : public persistency::CIPersistencyHandler
{
public:
    MOCK_METHOD0(initialize, void());
    MOCK_METHOD2(writeToFile, bool(const std::string&, const std::string&));
    MOCK_CONST_METHOD2(readFromFile, bool(const std::string&, std::string&));
    MOCK_METHOD1(resetValue, bool(const std::string&));
    MOCK_METHOD0(flush, void());
};

}  // namespace testing
}  // namespace stm
}  // namespace vrte
}  // namespace bosch

#endif  // BOSCH_VRTE_STM_PERSISTENCY_MOCKPERSISTENCYHANDLER_HPP_INCLUDED
