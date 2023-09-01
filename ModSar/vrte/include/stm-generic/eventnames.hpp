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
/// @file      libs/eh/include/bosch/vrte/stm/eh/eventnames.hpp
/// @brief     Header of the event names class
/// @copyright Robert Bosch GmbH 2018-2022
/// @author    VRTE StM Team
//
//=============================================================================

#ifndef BOSCH_VRTE_STM_EH_EVENTNAMES_HPP_INCLUDED
#define BOSCH_VRTE_STM_EH_EVENTNAMES_HPP_INCLUDED

#include "bosch/vrte/stm/eh/ieventnames.hpp"

#include <cstdint>
#include <map>

namespace bosch
{
namespace vrte
{
namespace stm
{
namespace eh
{

class CEventNames : public CIEventNames
{
public:
    /// @brief Constructor of CEventNames
    /// @param[in] f_eventNameMap   Event map <numerical event ID, event name>
    CEventNames(std::map<uint64_t, const std::string>& f_eventNameMap);

    /// @brief Destructor of CEventNames
    virtual ~CEventNames() = default;

    /// @brief Method to insert event to event map
    /// @param[in] f_event  Numerical event ID
    /// @param[in] f_name   Event Name
    /// @return bool / true = success\n
    ///         false = Event name already exists with inputted name
    bool add(uint64_t f_event, const std::string& f_name) override;

    /// @brief Method to get event name based on event ID
    /// @param[in] f_event Numerical event ID
    /// @param[out] f_name Event Name
    /// @return bool / true  = Event name found (returned in f_name)\n
    ///         false = Event name NOT found (decoded event mask pattern returned in f_name)
    bool get(uint64_t f_event, std::string& f_name) override;

private:
    std::map<uint64_t, const std::string>& m_eventNameMap;
    std::string                            m_nameUnknown;
};  // class CEventNames

}  // namespace eh
}  // namespace stm
}  // namespace vrte
}  // namespace bosch
#endif  // BOSCH_VRTE_STM_EH_EVENTNAMES_HPP_INCLUDED
