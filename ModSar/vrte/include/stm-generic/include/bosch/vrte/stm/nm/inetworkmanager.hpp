//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018-2022 by DENSO Corporation. All rights reserved.
//
// This file is property of DENSO Corporation. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================
//
/// @file      include/bosch/vrte/stm/nm/inetworkmanager.hpp
/// @brief     Base class for Network management subcomponent
/// @copyright DENSO Corporation 2018-2022
/// @author    VRTE StM Team
//
//=============================================================================

#ifndef BOSCH_VRTE_STM_NM_INMSUBCOMPONENTMANAGER_HPP_INCLUDED
#define BOSCH_VRTE_STM_NM_INMSUBCOMPONENTMANAGER_HPP_INCLUDED

#include "bosch/vrte/stm/event.hpp"
#include "bosch/vrte/stm/types.hpp"

namespace bosch
{
namespace vrte
{
namespace stm
{
namespace nm
{

class CINetworkManager : public CIEventAcceptor
{
public:
    virtual ~CINetworkManager() = default;
};

}  // namespace nm
}  // namespace stm
}  // namespace vrte
}  // namespace bosch

#endif  // BOSCH_VRTE_STM_NM_INMSUBCOMPONENTMANAGER_HPP_INCLUDED
