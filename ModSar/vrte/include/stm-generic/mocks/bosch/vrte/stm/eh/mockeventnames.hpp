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
/// @file      tests/VRTE_UT/mocks/include/bosch/vrte/stm/eh/mockeventnames.hpp
/// @brief     Mock for CIEventNames
/// @copyright Robert Bosch GmbH 2018-2022
/// @author    VRTE StM Team
//
//=============================================================================

#ifndef BOSCH_VRTE_STM_EH_MOCKEVENTNAMES_HPP_INCLUDED
#define BOSCH_VRTE_STM_EH_MOCKEVENTNAMES_HPP_INCLUDED

#include "bosch/vrte/stm/eh/ieventnames.hpp"
#include "bosch/vrte/stm/eventnamesgenerated.hpp"
#include "gmock/gmock.h"

#include <string>

namespace bosch
{
namespace vrte
{
namespace stm
{
namespace testing
{

class CMockEventNames : public eh::CIEventNames
{
public:
    MOCK_METHOD2(add, bool(uint64_t f_event, const std::string& f_name));

    bool get(uint64_t f_event, std::string& f_name)
    {
        bool result;

        auto it = bosch::vrte::stm::g_eventNameMap.find(f_event);

        if (it == bosch::vrte::stm::g_eventNameMap.end())
        {
            f_name = strevent(f_event);
            result = false;
        }
        else
        {
            f_name = it->second;
            result = true;
        }

        return result;
    }
};

}  // namespace testing
}  // namespace stm
}  // namespace vrte
}  // namespace bosch

#endif  // BOSCH_VRTE_STM_EH_MOCKEVENTNAMES_HPP_INCLUDED
