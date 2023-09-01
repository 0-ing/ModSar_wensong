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
/// @file      libs/common/include/bosch/vrte/stm/types.hpp
/// @brief     stm internal types
/// @copyright Robert Bosch GmbH 2018-2021
/// @author    VRTE StM Team
//
//=============================================================================

#ifndef BOSCH_VRTE_STM_TYPES_HPP_INCLUDED
#define BOSCH_VRTE_STM_TYPES_HPP_INCLUDED

#include <cstdint>  // uint8_t

namespace bosch
{
namespace vrte
{
namespace stm
{

/// @brief StatusType as
///        synchronous return type for register / unregister calls
///        asyncronous return type for ResponseData
///        and further use cases (to be extended)
///
enum class EStdReturnType : uint8_t
{
    OK     = 0,  ///< (un)registration ok or ResponseData valid
    NOT_OK = 1   ///< (un)registration not ok or ResponseData invalid
};

}  // namespace stm
}  // namespace vrte
}  // namespace bosch

#endif  // BOSCH_VRTE_STM_TYPES_HPP_INCLUDED
