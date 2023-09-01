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
/// @file      libs/common/include/bosch/vrte/stm/event.hpp
/// @brief     StM internal events
/// @copyright Robert Bosch GmbH 2018-2022
/// @author    VRTE StM Team
//
//=============================================================================

#ifndef BOSCH_VRTE_STM_EVENT_HPP_INCLUDED
#define BOSCH_VRTE_STM_EVENT_HPP_INCLUDED

#include "bosch/vrte/stm/eventconstants.hpp"
#include "bosch/vrte/stm/eventids.hpp"

#include <cstdint>
#include <string>
#include <vector>

namespace bosch
{
namespace vrte
{
namespace stm
{

/// @brief Convert event to human-readable string.
/// @param [in] event   Event ID
/// @return             Human-readable string. e.g. "<1|OSM|0x0A|0x00000>"
std::string strevent(uint64_t event, const std::string& f_data = std::string());

/// @brief Get the sender/context field of an event.
inline uint8_t GetEventSender(uint64_t f_event)
{
    return static_cast<uint8_t>((f_event & EV_MASK_SENDER) >> EV_OFFS_SENDER);
}

/// @brief Get the statemachine field of an event.
inline uint16_t GetEventStateMachine(uint64_t f_event)
{
    return static_cast<uint16_t>((f_event & EV_MASK_STATEMACHINE) >> EV_OFFS_STATEMACHINE);
}

/// @brief Get the data field of an event.
inline uint64_t GetEventData(uint64_t f_event)
{
    return (f_event & EV_MASK_DATA_MASK) >> EV_OFFS_DATA;
}

constexpr const char SEMICOLON_DELIMITER = ';';
constexpr const char COMMA_DELIMITER     = ',';

// Delimiter to be used when concatenating function group names in an event data string.
constexpr const char FUNCTION_GROUP_LIST_DELIMITER = ',';

// Delimiter to be used when concatenating a function group list with a requested state
// in an event data string.
constexpr const char FUNCTION_GROUP_STATE_ADD_DELIMITER = ';';

static_assert(FUNCTION_GROUP_LIST_DELIMITER != FUNCTION_GROUP_STATE_ADD_DELIMITER,
              "The fg list delimiter and the state append delimiter must not be the same.");

/// @brief Create an event data string encoding a list of function group names and a state.
///
/// @param f_fgNames    Function group names
/// @param f_state      State name
///
/// @return             Event data string
std::string CreateFGRequestData(const std::vector<std::string>& f_fgNames, const std::string& f_state);

/// @brief Parse list of function group names and state name from event data string.
///
/// @param f_data    [in]    Event data string
/// @param f_fgNames [out]   Function group names
/// @param f_state   [out]   State name
///
/// @return                  false, when the data string could not be parsed.
bool ParseFGRequestData(const std::string& f_data, std::vector<std::string>& f_fgNames, std::string& f_state);

/// @brief State Management internal event interface
/// @description All StM internal components consuming events have to implement this
class CIEventAcceptor
{
public:
    ///@brief consume an event containing payload
    ///@param[in] f_event : uint64_t event with structure as defined above
    ///@param[in] f_data  : payload of the event (std::string)
    virtual void acceptEvent(const uint64_t f_event, const std::string& f_data = std::string()) = 0;
};  // class CIEventAcceptor

}  // namespace stm
}  // namespace vrte
}  // namespace bosch

#endif  // BOSCH_VRTE_STM_EVENT_HPP_INCLUDED
