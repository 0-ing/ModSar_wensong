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
/// @file      tests/VRTE_UT/mocks/include/bosch/vrte/stm/osm/Mock_OperationalStateManager.hpp
/// @brief     Unittest of OperationalStateManager Mock Class
/// @copyright Robert Bosch GmbH 2018-2022
/// @author    VRTE StM Team
//
//=============================================================================

#ifndef BOSCH_VRTE_STM_OSM_MOCK_OPERATIONALSTATEMANAGER_HPP_INCLUDED
#define BOSCH_VRTE_STM_OSM_MOCK_OPERATIONALSTATEMANAGER_HPP_INCLUDED

#include "bosch/vrte/stm/osm/ioperationalstatemanager.hpp"
#include "bosch/vrte/stm/types.hpp"
#include "gmock/gmock.h"

namespace bosch
{
namespace vrte
{
namespace stm
{
namespace testing
{

class Mock_OperationalStateManager : public osm::CIOperationalStateManager
{
public:
    MOCK_METHOD2(acceptEvent, void(const uint64_t f_event, const std::string& f_data));
};

}  // namespace testing
}  // namespace stm
}  // namespace vrte
}  // namespace bosch

#endif  // BOSCH_VRTE_STM_OSM_MOCK_OPERATIONALSTATEMANAGER_HPP_INCLUDED
