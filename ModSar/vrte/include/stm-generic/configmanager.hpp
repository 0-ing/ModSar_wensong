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
/// @file      libs/common/include/bosch/vrte/stm/ecucfg/configmanager.hpp
/// @brief     Config Manager header file
/// @copyright Robert Bosch GmbH 2018-2021
/// @author    VRTE StM Team
//
//=============================================================================

#ifndef BOSCH_VRTE_STM_ECUCFG_CONFIGMANAGER_HPP_INCLUDED
#define BOSCH_VRTE_STM_ECUCFG_CONFIGMANAGER_HPP_INCLUDED

#include "bosch/vrte/stm/ecucfg/iconfigmanager.hpp"
#include "bosch/vrte/stm/eventloop.hpp"

namespace bosch
{
namespace vrte
{
namespace stm
{

namespace eh
{
class CIEventHandler;
}

namespace ecucfg
{
class CConfigManager : public CIConfigManager
{
public:
    /// @brief Constructor
    ///
    CConfigManager();

    /// @brief Destructor
    ///
    virtual ~CConfigManager() = default;
};

}  // namespace ecucfg
}  // namespace stm
}  // namespace vrte
}  // namespace bosch

#endif  // BOSCH_VRTE_STM_ECUCFG_CONFIGMANAGER_HPP_INCLUDED
