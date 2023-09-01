//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================
//
/// @file      triggeroutosmenum.hpp
/// @brief     Enum for STM trigger out OSM state
/// @copyright Robert Bosch GmbH 2021
/// @author    VRTE StM Team
//=============================================================================

#ifndef TRIGGEROUTOSMENUM_HPP_INCLUDED
#define TRIGGEROUTOSMENUM_HPP_INCLUDED

#include "ara/sm/impl_type_osmstatetype.h"
#include <map>
#include <string>

namespace bosch
{
namespace vrte
{
namespace stm
{
namespace exampleapp
{

static std::map<ara::sm::OsmStateType, std::string> OsmStateTypeMap = {
    {ara::sm::OsmStateType::kOsmInit, "OsmInit"},
    {ara::sm::OsmStateType::kOsmRunEntered, "OsmRunEntered"},
    {ara::sm::OsmStateType::kOsmRunReached, "OsmRunReached"},
    {ara::sm::OsmStateType::kOsmPrepareShutdownEntered, "OsmPrepareShutdownEntered"},
    {ara::sm::OsmStateType::kOsmPrepareShutdownReached, "OsmPrepareShutdownReached"},
    {ara::sm::OsmStateType::kOsmUpdateEntered, "OsmUpdateEntered"},
    {ara::sm::OsmStateType::kOsmUpdateReached, "OsmUpdateReached"},
    {ara::sm::OsmStateType::kOsmShutdownEntered, "OsmShutdownEntered"},
    {ara::sm::OsmStateType::kOsmShutdownReached, "OsmShutdownReached"},
    {ara::sm::OsmStateType::kOsmPointOfNoReturnReached, "OsmPointOfNoReturnReached"},
    {ara::sm::OsmStateType::kOsmShutdownReachedTrue, "OsmShutdownReachedTrue"},
    {ara::sm::OsmStateType::kOsmDiagnosticEntered, "OsmDiagnosticEntered"},
    {ara::sm::OsmStateType::kOsmDiagnosticReached, "OsmDiagnosticReached"},
    {ara::sm::OsmStateType::kOsmCalibrateEntered, "OsmCalibrateEntered"},
    {ara::sm::OsmStateType::kOsmCalibrateReached, "OsmCalibrateReached"},
};

inline static std::string OsmStateToString(uint8_t f_state)
{
    return OsmStateTypeMap[static_cast<ara::sm::OsmStateType>(f_state)];
}

}  // namespace exampleapp
}  // namespace stm
}  // namespace vrte
}  // namespace bosch

#endif  // TRIGGEROUTOSMENUM_HPP_INCLUDED
