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
/// @file      libs/fgm/include/bosch/vrte/stm/fgm/ifunctiongroup.hpp
/// @brief     State Management subcomponent FunctionGroup Interface
/// @copyright Robert Bosch GmbH 2018-2022
/// @author    VRTE StM Team
//
//=============================================================================

#ifndef BOSCH_VRTE_STM_FGM_IFUNCTIONGROUP_HPP_INCLUDED
#define BOSCH_VRTE_STM_FGM_IFUNCTIONGROUP_HPP_INCLUDED

#include <string>

namespace bosch
{
namespace vrte
{
namespace stm
{
namespace fgm
{

/// @brief This interface contains FunctionGroup information and methods to control FunctionGroup
class CIFunctionGroup
{
public:
    /// @brief Forward set state event to function group plugins.
    ///
    /// @param [in] f_event Event which function group will evaluate
    /// @param [in] f_data  Event payload
    virtual void acceptEvent(const uint64_t f_event, const std::string& f_data = std::string()) = 0;

    /// @brief Try to switch to new state.
    ///
    /// @param[in] state State name to broadcast
    virtual void setState(const std::string& f_state) = 0;

    /// @brief Get name of function group
    ///
    /// @return Function group name in std::string
    virtual const std::string& getName() const = 0;
};  // class CIFunctionGroup

}  // namespace fgm
}  // namespace stm
}  // namespace vrte
}  // namespace bosch

#endif /* BOSCH_VRTE_STM_FGM_IFUNCTIONGROUP_HPP_INCLUDED */
