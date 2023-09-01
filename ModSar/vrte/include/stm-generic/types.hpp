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
/// @file      libs/cm/include/bosch/vrte/stm/cm/types.hpp
/// @brief     Enums and typedefs for ComponentManager.
/// @copyright Robert Bosch GmbH 2018-2022
/// @author    VRTE StM Team
//
//=============================================================================

#ifndef BOSCH_VRTE_STM_CM_TYPES_HPP_INCLUDED
#define BOSCH_VRTE_STM_CM_TYPES_HPP_INCLUDED

#include "bosch/vrte/stm/types.hpp"

#include <functional>

namespace bosch
{
namespace vrte
{
namespace stm
{
namespace cm
{

using callback_t   = std::function<void(const std::string&, EStdReturnType)>;
using connection_t = uint16_t;

enum class ERequestMode : uint8_t
{
    kInvalid   = 0U,  ///< Component has to ignore this request
    kVoluntary = 1U,  ///< Component can decline state request
    kForced    = 2U   ///< Component has to carry out state request
};

}  // namespace cm
}  // namespace stm
}  // namespace vrte
}  // namespace bosch

#endif  // BOSCH_VRTE_STM_CM_TYPES_HPP_INCLUDED
