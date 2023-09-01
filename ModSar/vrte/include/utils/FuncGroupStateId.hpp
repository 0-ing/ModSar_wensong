//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
/// @copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file      FuncGroupStateId.hpp
/// @brief     Type Definition: FuncGroupStateId
/// @author    Christopher Schwager

#ifndef UTILS_IFUNCGROUPSTATEID_HPP_INCLUDED
#define UTILS_IFUNCGROUPSTATEID_HPP_INCLUDED

#include <stdint.h>

namespace exm
{

/// @brief    Representation of a Function Group State as Identifier
enum class FuncGroupStateId : int16_t
{
    INTRANSITION = -4,  ///< @brief In Transition
    CANCELED = -3,      ///< @brief Current state transition was canceled due to a net SetState call
    ERROR = -2,         ///< @brief Error State
    INVALID = -1,       ///< @brief Invalid Function Group State Id
    OFF = 0,            ///< @brief Off State
    FIRST_VALID_ID = 1, ///< @brief Alias for the first ID that is not OFF and valid.

};

namespace func_group_state_id
{
/// @brief Returns the Function Group State ID by index
/// @param index   Index of the Function Group State
/// @return FuncGroupId 
inline FuncGroupStateId FromIndex(uint32_t index)
{
    return static_cast< // PRQA S 3013 #  The enum is used as a type safe integer. We evaluated
                        // different options, such as storing the integer in a class. However we
                        // would need the class to be fully constexpr compatible, as we need the
                        // associated constants such as INVALID and co. to be compile time
                        // evaluated, as otherwise we have a race between the global constructors at
                        // runtime. However making the class fully constexpr compatible makes gcc
                        // consider the class to be an aggregate type. There however is an arcane
                        // flag in gcc called -Waggregate-return which was meant to forbid returning
                        // structs from functions in legacy C. gcc however marks modern C++
                        // aggregates the exact same way and thus if you have that flag set, it
                        // accidentally fires. Therefore the best solution for now is to simply keep
                        // the enum.
        FuncGroupStateId>(index + static_cast<uint32_t>(FuncGroupStateId::FIRST_VALID_ID));
}
}

/// @brief Namespace to locate Adaptive AUTOSAR-defined Function Group States.
namespace FuncGroupState
{
constexpr const char* OFF = "Off";           ///< No Process is assigned to OFF state.
constexpr const char* STARTUP = "Startup";   ///< Identifier for Machine State "Startup".
constexpr const char* SHUTDOWN = "Shutdown"; ///< Identifier for Machine State "Shutdown".
constexpr const char* RESTART = "Restart";   ///< Identifier for Machine State "Shutdown".
}

} /* namespace exm */

#endif
