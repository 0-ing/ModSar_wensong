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
/// @file      libs/eh/include/bosch/vrte/stm/eh/ieventnames.hpp
/// @brief     Interface header of the event names class
/// @copyright Robert Bosch GmbH 2018-2022
/// @author    VRTE StM Team
//
//=============================================================================

#ifndef BOSCH_VRTE_STM_EH_IEVENTNAMES_HPP_INCLUDED
#define BOSCH_VRTE_STM_EH_IEVENTNAMES_HPP_INCLUDED

#include <cstdint>
#include <string>

namespace bosch
{
namespace vrte
{
namespace stm
{
namespace eh
{

class CIEventNames
{
public:
    /// @brief Destructor of CIEventNames
    virtual ~CIEventNames() = default;

    /// @brief Add a name for an event
    /// @param[in] f_event   Numerical event ID
    /// @param[in] f_name    Event name string
    /// @return bool / true = success\n
    ///         false = Event name already exists with inputted name
    virtual bool add(uint64_t f_event, const std::string& f_name) = 0;

    /// @brief Get the name of an event
    /// @param[in] f_event Numerical event ID
    /// @param[out] f_name Event name (see return parameter)
    /// @return bool / true  = Event name found (returned in f_name)\n
    ///         false = Event name NOT found (decoded event mask pattern returned in f_name)
    virtual bool get(uint64_t f_event, std::string& f_name) = 0;
};  // class CIEventNames

}  // namespace eh
}  // namespace stm
}  // namespace vrte
}  // namespace bosch
#endif  // BOSCH_VRTE_STM_EH_IEVENTNAMES_HPP_INCLUDED
