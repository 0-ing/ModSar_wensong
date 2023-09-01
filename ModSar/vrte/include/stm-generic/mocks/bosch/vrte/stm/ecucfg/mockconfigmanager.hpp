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
/// @file      tests/VRTE_UT/mocks/include/bosch/vrte/stm/ecucfg/mockconfigmanager.hpp
/// @brief     Mock of STM class ecucfg::CIConfigManager
/// @copyright Robert Bosch GmbH 2018-2021
/// @author    VRTE StM Team
//
//=============================================================================

#ifndef BOSCH_VRTE_STM_ECUCFG_MOCKCONFIGMANAGER_HPP_INCLUDED
#define BOSCH_VRTE_STM_ECUCFG_MOCKCONFIGMANAGER_HPP_INCLUDED

#include "bosch/vrte/stm/ecucfg/iconfigmanager.hpp"

#include "gmock/gmock.h"

namespace bosch
{
namespace vrte
{
namespace stm
{
namespace testing
{

class CMockConfigManager : public ecucfg::CIConfigManager
{
public:
    MOCK_METHOD0(getFGDataInfoList, const std::vector<ecucfg::FunctionGroupInfo>());
    MOCK_METHOD0(reloadEcuCfg, bool());
};

}  // namespace testing
}  // namespace stm
}  // namespace vrte
}  // namespace bosch

#endif  // BOSCH_VRTE_STM_ECUCFG_MOCKCONFIGMANAGER_HPP_INCLUDED
