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
/// @file      libs/osm/include/bosch/vrte/stm/osm/ioperationalstatemanager.hpp
/// @brief     Operational State Manager interfaces
/// @copyright Robert Bosch GmbH 2018-2022
/// @author    VRTE StM Team
//
//=============================================================================

#ifndef BOSCH_VRTE_STM_OSM_IOPERATIONALSTATEMANAGER_HPP_INCLUDED
#define BOSCH_VRTE_STM_OSM_IOPERATIONALSTATEMANAGER_HPP_INCLUDED

#include "bosch/vrte/stm/event.hpp"
#include "bosch/vrte/stm/types.hpp"

namespace bosch
{
namespace vrte
{
namespace stm
{
namespace osm
{

/// \brief Interface of Operational State Manager which derived from Event Interface.
class CIOperationalStateManager : public CIEventAcceptor
{
public:
    virtual ~CIOperationalStateManager() = default;
};

}  // namespace osm
}  // namespace stm
}  // namespace vrte
}  // namespace bosch

#endif  // BOSCH_VRTE_STM_OSM_IOPERATIONALSTATEMANAGER_HPP_INCLUDED
