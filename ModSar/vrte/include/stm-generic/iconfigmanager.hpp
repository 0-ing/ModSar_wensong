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
/// @file      libs/common/include/bosch/vrte/stm/ecucfg/iconfigmanager.hpp
/// @brief     Interface definition for Config Manager class.
/// @copyright Robert Bosch GmbH 2018-2022
/// @author    VRTE StM Team
//
//=============================================================================

#ifndef BOSCH_VRTE_STM_ECUCFG_ICONFIGMANAGER_HPP_INCLUDED
#define BOSCH_VRTE_STM_ECUCFG_ICONFIGMANAGER_HPP_INCLUDED

#include "bosch/vrte/stm/event.hpp"
#include <cstdint>
#include <map>
#include <string>
#include <vector>

namespace bosch
{
namespace vrte
{
namespace stm
{
namespace ecucfg
{

/// @brief  Function Group information struct
///         This struct contains FG name, FG initialized state, list of FG state and PHM recovery actions mapping
struct FunctionGroupInfo
{
    std::string                     m_fgName;
    std::string                     m_fgInitState;
    std::vector<std::string>        m_fgStateList;
    std::map<uint32_t, std::string> m_fgRecoveryActions;
    bool m_hasTriggerInOutInterface;  //! Flag indicating if the Function group has a TriggerInOut interface
};

class CIConfigManager
{
public:
    /// @brief Default destructor
    ///
    virtual ~CIConfigManager() = default;

    /// @brief      Get list of Function Group configurations
    ///
    /// @return     List of FG data information
    virtual const std::vector<FunctionGroupInfo> getFGDataInfoList() = 0;

    /// @brief      Reload the data from ECUCFG file
    ///
    /// @return     true (Success) or false (Failure)
    virtual bool reloadEcuCfg() = 0;
};

}  // namespace ecucfg
}  // namespace stm
}  // namespace vrte
}  // namespace bosch

#endif  // BOSCH_VRTE_STM_ECUCFG_ICONFIGMANAGER_HPP_INCLUDED
