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
/// @file      libs/sm/include/bosch/vrte/stm/sm/istartupmanager.hpp
/// @brief     Base Class of Startup Manager
/// @copyright Robert Bosch GmbH 2018-2022
/// @author    VRTE StM Team
//
//=============================================================================

#ifndef BOSCH_VRTE_STM_SM_ISTARTUPMANAGER_HPP_INCLUDED
#define BOSCH_VRTE_STM_SM_ISTARTUPMANAGER_HPP_INCLUDED

#include "bosch/vrte/stm/event.hpp"
#include "bosch/vrte/stm/types.hpp"

namespace bosch
{
namespace vrte
{
namespace stm
{
namespace sm
{

class CIStartupManager : public CIEventAcceptor
{
public:
    virtual ~CIStartupManager() = default;
};

}  // namespace sm
}  // namespace stm
}  // namespace vrte
}  // namespace bosch

#endif  // BOSCH_VRTE_STM_SM_ISTARTUPMANAGER_HPP_INCLUDED
