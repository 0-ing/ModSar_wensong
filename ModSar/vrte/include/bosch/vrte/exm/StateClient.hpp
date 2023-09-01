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
/// @file      StateClient.hpp
/// @brief     This file defines the class which represents the public API of EM
///            for requesting state changes (transitions) and getting state
///            information of function groups from EM.
/// @copyright Robert Bosch GmbH  2018
/// @author    Bastian Baetz
//=============================================================================

#ifndef _STATECLIENT_HPP_INCLUDED
#define _STATECLIENT_HPP_INCLUDED

#include "bosch/vrte/exm/IStateClient.hpp"
#include "utils/PrimaryConfig.hpp"
#include "utils/vector.hpp"

namespace exm
{
class FuncGroupClient;
}

namespace bosch
{
namespace vrte
{
namespace exm
{

/// @brief This class allows interaction with Execution Management by a State Management application.
/// It offers GetState methods to retrieve the current state of one function group and
/// SetState methods to initiate a state change of one or multiple function groups, including the MachineState
/// function group.
/// After instantiating this class, a user can call its methods right away.
/// Please note that connection to Execution Management is only set up and working if configuration marks the State Management Process as authorized to use this API.
/// In other words: configuration needs to assign "StateManager" role to a given Process, otherwise it will not be able to communicate with the Execution Manager.
///
/// @warning The operations made with the StateClient shall be monitored with a timeout. In this way, any IPC or execution manager internal error
///          can be caught by the State Manager.
class StateClient : public IStateClient
{
public:
    /// @brief Default constructor
    StateClient() noexcept;

    /// @brief Default destructor
    virtual ~StateClient() noexcept;

    /// @brief copy constructor
    StateClient(const StateClient& other);

    /// @brief copy assignment operator
    StateClient& operator=(const StateClient& other);

    /// @brief Issues a SetState request to the execution manager.
    ///
    /// This call issues a request to set the state of the given function group.
    /// On successful or failed completion of the request,
    /// notifier will be called asynchronously, with one SetStatePartFinished call and one SetStateFinished call.
    /// Two consecutive SetState requests on the same function group will cancel
    /// the first request and execute the second. This is a "last wins" strategy.
    /// @param[in] funcGroup         The Function Group to command. NULL-terminated string.
    /// @param[in] funcGroupState    The FG State to command the Function Group to. NULL-terminated string.
    /// @param[in] notifier          Reference to an object which wants to be notified upon completion. The notification call shall not block.
    /// @return See the description of StateClientResult.
    StateClientResult SetState(const char* const funcGroup, const char* const funcGroupState, IStateClientNotificator& notifier) noexcept override;

    /// @brief Issues multiple SetState requests to the execution manager.
    ///
    /// This call issues a bulk set of requests to set the function groups in the list to a given state.
    /// Each element in the request will trigger an asynchronous SetStatePartFinished callback, and a single SetStateFinished callback on completion.
    /// No rollback will be performed if one or more requests fail, i.e. those Function Groups that successfully completed the transition will stay in the new state.
    /// Two consecutive SetState requests containing the same function group will cancel the first request for that function group and execute the second,
    /// effectively making the final SetStateFinished callback forwarding "Failed".
    /// Also, having a request for the same Function Group in one bulk request will cancel the first one. This is a "last wins" strategy.
    /// @param[in] request      A reference to a TransitionRequest vector of (Function Group, State) pairs, which shall perform a state change.
    /// @param[in] notifier     Reference to an object which wants to be notified upon completion. The notification call shall not block.
    /// @return See the description of StateClientResult.
    StateClientResult SetState(const TransitionRequests& request, IStateClientNotificator& notifier) noexcept override;

    /// @brief Issues a GetState request to the execution manager.
    ///
    /// This call issues a request to retrieve the state of the given function group.
    /// On successful or failed completion of the request,
    /// notifier will be called asynchronously.
    /// @param[in]  funcGroup                The Function Group to command. NULL-terminated string.
    /// @param[out] funcGroupState           Pointer to a buffer to store the returning FG State.
    /// @param[in]  funcGroupStateMaxSize    Maximum allowed size for the FG State string, i.e. size of the buffer.
    /// @param[in]  notifier                 Reference to an object which wants to be notified upon completion. The notification call shall not block.
    /// @return See the description of StateClientResult.
    StateClientResult GetState(const char* const funcGroup, char* const funcGroupState, uint32_t funcGroupStateMaxSize, IStateClientNotificator& notifier) noexcept override;

    /// @brief Issues a GetState request to the execution manager.
    ///
    /// This call issues a request to retrieve the state of the given function group.
    /// In addition to the default GetState call, it will not return IN_TRANSITION, but
    /// will try to retrieve a valid state up until timeout is reached.
    /// On successful or failed completion of the request,
    /// notifier will be called asynchronously.
    /// @param[in]  funcGroup                The Function Group to command. NULL-terminated string.
    /// @param[out] funcGroupState           Pointer to a buffer to store the returning FG State.
    /// @param[in]  funcGroupStateMaxSize    Maximum allowed size for the FG State string, i.e. size of the buffer.
    /// @param[in]  notifier                 Reference to an object which wants to be notified upon completion. The notification call shall not block.
    /// @param[in]  timeoutMs                Timeout in milliseconds to wait for a Function Group transition to complete.
    /// @return See the description of StateClientResult.
    StateClientResult GetState(const char* const funcGroup, char* const funcGroupState, uint32_t funcGroupStateMaxSize, IStateClientNotificator& notifier, uint32_t timeoutMs) noexcept override;
   
    /// @brief Issues a GetExecutionError request to the execution manager.
    ///
    /// This call issues a request to retrieve the process which cause function group in error state.
    /// On successful or failed completion of the request, notifier will be called asynchronously.
    /// @param[in]  funcGroup                The Function Group to command. NULL-terminated string.
    /// @param[out] process           Pointer to a buffer to store the returning FG State.
    /// @param[in]  ProcessNameMaxSize    Maximum allowed size for the FG State string, i.e. size of the buffer.
    /// @param[in]  notifier                 Reference to an object which wants to be notified upon completion. The notification call shall not block.
    /// @return See the description of #StateClientResult.
    StateClientResult GetExecutionError(const char* const funcGroup,char* const process, uint32_t ProcessNameMaxSize, IStateClientNotificator& notifier) noexcept override;


protected:
    /// @brief Reference to the actual library implementation using the PIMPL pattern.
    ::exm::FuncGroupClient& impl;
};

} // namespace exm
} // namespace vrte
} // namespace bosch

#endif // _STATECLIENT_HPP_INCLUDED
