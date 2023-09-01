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
/// @file      tests/VRTE_UT/mocks/include/bosch/vrte/stm/fgm/Mock_FunctionGroupInterface.hpp
/// @brief     Mock class for CIFunctionGroup
/// @copyright Robert Bosch GmbH 2018-2022
/// @author    VRTE StM Team
//
//=============================================================================

#ifndef BOSCH_VRTE_STM_FGM_MOCK_FUNCTIONGROUPINTERFACE_HPP_INCLUDED
#define BOSCH_VRTE_STM_FGM_MOCK_FUNCTIONGROUPINTERFACE_HPP_INCLUDED

#include "bosch/vrte/stm/fgm/ifunctiongroup.hpp"

#include "gmock/gmock.h"

#include <memory>
#include <string>

namespace bosch
{
namespace vrte
{
namespace stm
{
namespace testing
{
class Mock_CFunctionGroup : public fgm::CIFunctionGroup
{
public:
    Mock_CFunctionGroup(const std::string& f_name)
    {
        m_name = f_name;
    }
    virtual ~Mock_CFunctionGroup() = default;

    MOCK_METHOD2(acceptEvent, void(const uint64_t f_event, const std::string& f_data));
    MOCK_METHOD1(setState, void(const std::string& f_state));

    const std::string& getName() const override
    {
        return m_name;
    }

protected:
    std::string m_name;
};

}  // namespace testing
}  // namespace stm
}  // namespace vrte
}  // namespace bosch

#endif  // BOSCH_VRTE_STM_FGM_MOCK_FUNCTIONGROUPINTERFACE_HPP_INCLUDED
