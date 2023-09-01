//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2017 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file      StateMachine.hpp
/// @brief     Header file for StateMachine class
/// @copyright Robert Bosch GmbH  2017
/// @author

#ifndef _STATEMACHINE_HPP_INCLUDED
#define _STATEMACHINE_HPP_INCLUDED

#include <stdint.h>

#include "../../ldr/inc/ldr/InstanceState.hpp"
#include "log/Debug.hpp"

namespace exm
{
namespace ldr
{
/// @class    StateMachine
/// @brief    StateMachine class hold state information of an Instance
class StateMachine
{
public:

    ///< @brief StateMachine Constructor , initializes to state to EMPTY
    StateMachine() : state(InstanceState::EMPTY),
            error_code(ErrorCodeInstance::ERROR_NONE)
    {
    }

    ///< @brief StateMachine Destructor
    ~StateMachine()
    {
    }

    /// @brief No copy constructor needed.
    StateMachine(const StateMachine&) = delete;

    /// @brief No copy assignment operator needed.
    StateMachine& operator=(const StateMachine&) = delete;

    /// @brief Get the current state
    /// @return Instance state
    InstanceState get_state() { return state; }

    /// @brief Set the current state
    /// @param[in] state_ Instance state
    /// @return status of the function call
    /// @retval 0 = success
    /// @retval -1 = failed
    int8_t set_state( InstanceState state_ );

    /// @brief set error_code and call set_state(ERROR)
    /// @param[in] code Error code
    /// @return status of the function call
    /// @retval 0 = success
    /// @retval -1 = failed
    int32_t set_error_state( ErrorCodeInstance code )
    {
        error_code = code;
        return set_state(InstanceState::ERROR);
    }

    /// @brief Get the error code
    /// @return Error code
    ErrorCodeInstance get_error_code()  { return error_code; }

private :
    InstanceState state;                                                ///< @brief State machine variable to hold current state information  */
    ErrorCodeInstance error_code;                                       ///< @brief error code representing the ERROR state */
};

} /* namespace mfe */
} /* namespace exm */
#endif
