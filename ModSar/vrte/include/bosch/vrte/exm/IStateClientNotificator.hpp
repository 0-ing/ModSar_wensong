//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================
//
/// @file      IStateClientNotificator.hpp
/// @brief     Interface to retrieve state client notifications
/// @copyright Robert Bosch GmbH  2018
/// @author    Bastian Baetz
//=============================================================================

#ifndef _ISTATECLIENTNOTIFICATOR_HPP_INCLUDED
#define _ISTATECLIENTNOTIFICATOR_HPP_INCLUDED

#include "bosch/vrte/exm/StateClientResult.hpp"

namespace bosch
{
namespace vrte
{
namespace exm
{

    /// @brief Interface to retrieve state client notifications.
    /// Once a message from Execution Management is returned to the caller, the State Client library notifies the caller using this interface.
    class IStateClientNotificator
    {
        public:
            /// @brief Default destructor.
            virtual ~IStateClientNotificator()
            {
            }


            /// @brief Method to inform of completion of one part of a SetState request.
            ///
            /// Notifications are called consecutively from a StateClient thread, so the implementation of this method shall be as short as possible and not block.
            /// @param[in] result           Indication of the result of the request. If OK, state change was successfully performed. For other values see StateClientRequest documentation.
            /// @param[in] funcGroup        The function group on which the request was performed.
            /// @param[in] funcGroupState   The function group state that has been reached.
            virtual void SetStatePartFinished(StateClientResult result,
                    const char* funcGroup, const char* funcGroupState) = 0;

            /// @brief Method to inform of completion of the entire SetState request.
            ///
            /// Notifications are called consecutively from a StateClient thread, so the implementation of this method shall be as short as possible and not block.
            /// @param[in] result                   Indication of the result of the request. If OK, state change was successfully performed. For other values see StateClientRequest documentation.
            /// @param[in] nrOfFailedTransitions    Indication of the number of failed or missing transitions. 0 if result is OK.
            virtual void SetStateFinished(StateClientResult result,
                    uint32_t nrOfFailedTransitions) = 0;

            /// @brief Method to inform of completion of a GetState request.
            ///
            /// Notifications are called consecutively from a StateClient thread, so the implementation of this method shall be as short as possible and not block.
            /// @param[in] result                Indication of the result of the request. If OK, state change was successfully performed. For other values see StateClientRequest documentation.
            /// @param[in] funcGroupState        Pointer to the Function Group State identifier in the form of a NULL terminated string.
            /// @param[in] funcGroupStateSize    Size of the returned Function Group State identifier string.
            virtual void GetStateFinished(StateClientResult result,
                    const char* funcGroupState, uint32_t funcGroupStateSize) = 0;

            /// @brief Method to inform of completion of a GetExecutionErrorFinished request.
            ///
            /// Notifications are called consecutively from a StateClient thread, so the implementation of this method shall be as short as possible and not block.
            /// @param[in] result               Indication of the result of the request. If OK, state change was successfully performed. For other values see StateClientRequest documentation.
            /// @param[in] process              Pointer to the process identifier in the form of a NULL terminated string.
            /// @param[in] processNameSize      Size of the returned process name identifier string.
            virtual void GetExecutionErrorFinished(StateClientResult result,
                    const char* process, uint32_t processNameSize) = 0;
    };

}  // namespace exm
}  //namespace vrte
}  //namespace bosch

#endif // _ISTATECLIENTNOTIFICATOR_HPP_INCLUDED
