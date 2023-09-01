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
/// @file      tests/VRTE_UT/mocks/include/bosch/vrte/stm/eh/mockcomponentstaterequest.hpp
/// @brief     Mock for cm::CComponentStateRequestInterface
/// @copyright Robert Bosch GmbH 2018-2021
/// @author    VRTE StM Team
//
//=============================================================================

#ifndef BOSCH_VRTE_STM_EH_MOCKCOMPONENTSTATEREQUEST_HPP_INCLUDED
#define BOSCH_VRTE_STM_EH_MOCKCOMPONENTSTATEREQUEST_HPP_INCLUDED

#include "bosch/vrte/stm/cm/componentstaterequestinterface.hpp"
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

class Mock_ComponentStateRequest : public cm::CComponentStateRequestInterface
{
public:
    Mock_ComponentStateRequest() {}

    MOCK_METHOD3(vComponentStateRequest, void(const std::string&, const std::string&, const cm::RequestMode&));
};

}  // namespace testing
}  // namespace stm
}  // namespace vrte
}  // namespace bosch

#endif  // BOSCH_VRTE_STM_EH_MOCKCOMPONENTSTATEREQUEST_HPP_INCLUDED
