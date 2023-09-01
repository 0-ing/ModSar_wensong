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
/// @file      libs/fgm/include/bosch/vrte/stm/fgm/ifunctiongroupmanager.hpp
/// @brief     State Management subcomponent FunctionGroupManager
///            Interfaces for other StM-Subcomponent(EH, OSM, SM) to work with FGM
///            EH will also implement callback methods of CFgmFgStateClientInterface to receive
///              asynchronous return form FGM
///            SM will also implement callback methods of CFgmFgActiveClientInterface to receive
///              asynchronous return form FGM
///            OSM will also implement callback methods of CFgmStateReachedClientInterface to receive
///              asynchronous return form FGM
/// @copyright Robert Bosch GmbH 2018-2022
/// @author    VRTE StM Team
//
//=============================================================================

#ifndef BOSCH_VRTE_STM_FGM_IFUNCTIONGROUPMANAGER_HPP_INCLUDED
#define BOSCH_VRTE_STM_FGM_IFUNCTIONGROUPMANAGER_HPP_INCLUDED

#include "bosch/vrte/stm/event.hpp"

namespace bosch
{
namespace vrte
{
namespace stm
{
namespace fgm
{

/// @brief This class contains published interfaces to StM-internal components (EH, SM, OSM,...)
class CIFunctionGroupManager : public CIEventAcceptor
{
public:
};  // class CIFunctionGroupManager

}  // namespace fgm
}  // namespace stm
}  // namespace vrte
}  // namespace bosch

#endif  // BOSCH_VRTE_STM_FGM_IFUNCTIONGROUPMANAGER_HPP_INCLUDED
