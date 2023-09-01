//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
/// @copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================
/// @file      IStateClient.hpp
/// @brief     Declaration/Definition of IStateClient
/// @author    Bastian Baetz
//=============================================================================

#ifndef _ISTATECLIENT_HPP_INCLUDED
#define _ISTATECLIENT_HPP_INCLUDED

#include "bosch/vrte/exm/IStateClientNotificator.hpp"
#include "bosch/vrte/exm/StateClientResult.hpp"
#include "bosch/vrte/exm/FuncGroupTransition.hpp"

#include "utils/vector.hpp"
#include "utils/PrimaryConfig.hpp"

namespace bosch
{
namespace vrte
{
namespace exm
{

/// @brief Interface for the client to issue SetState and GetState requests.
class IStateClient
{
public:

    /// @brief Statically configured upper limit for the maximum number of transition requests in a bulk transition.
    static constexpr uint32_t maxTransitionsPerRequest = ::exm::utils::maxTransitionsPerRequest;

    /// @brief Definition of a vector of transition requests to forward a bulk set of set state requests.
    /// @brief Type used to define bulk state transition.
    /// It is defined as a set of individual function group state transitions, each describing a single one.
    /// For more details on how to describe a single function group transition please see
    /// FuncGroupTransition type description.
    typedef ::exm::utils::vector<FuncGroupTransition, maxTransitionsPerRequest> TransitionRequests;


    /// @brief Empty default destructor
    virtual ~IStateClient()
    {
    }

    /// @brief Issues a SetState request to the execution manager.
    ///
    /// This call issues a request to set the state of the given function group.
    /// On successful or failed completion of the request, notifier will be called asynchronously.
    /// Two consecutive SetState requests on the same function group will cancel the first request and execute the second. This is a "last wins" strategy.
    /// @param[in] funcGroup         The Function Group to command. NULL-terminated string.
    /// @param[in] funcGroupState    The FG State to command the Function Group to. NULL-terminated string.
    /// @param[in] notifier          Reference to an object which wants to be notified upon completion. The notification call shall not block.
    /// @return See the description of #StateClientResult.
    virtual StateClientResult SetState(const char* const funcGroup,
            const char* const funcGroupState,
            IStateClientNotificator& notifier) = 0;

    /// @brief Issues a SetState request to the execution manager.
    ///
    /// This call issues a bulk set of requests to set all function groups in the list to a given state.
    /// Each element in the request will trigger an asynchronous SetStatePartFinished callback, and a single SetStateFinished callback on completion.
    /// No rollback will be performed if one or more requests fail, i.e. those Function Groups that successfully completed the transition will stay in the new state.
    /// Two consecutive SetState requests containing the same function group will cancel the first request for that function group and execute the second, effectively making the final SetStateFinished callback forwarding "Failed".
    /// Also, having a request for the same Function Group in one bulk request will cancel the first one. This is a "last wins" strategy.
    /// @param[in] request      A reference to a TransitionRequest vector of (Function Group, State) pairs, which shall perform a state change.
    /// @param[in] notifier     Reference to an object which wants to be notified upon completion. The notification call shall not block.
    /// @return See the description of #StateClientResult.
    virtual StateClientResult SetState(const TransitionRequests& request,
            IStateClientNotificator& notifier) = 0;

    /// @brief Issues a GetState request to the execution manager.
    ///
    /// This call issues a request to retrieve the state of the given function group.
    /// On successful or failed completion of the request, notifier will be called asynchronously.
    /// @traceid{SWS_EM_01028}  //R18-10
    /// @uptrace{RS_EM_00101}
    /// @uptrace{RS_AP_00131}
    /// @param[in]  funcGroup                The Function Group to command. NULL-terminated string.
    /// @param[out] funcGroupState           Pointer to a buffer to store the returning FG State.
    /// @param[in]  funcGroupStateMaxSize    Maximum allowed size for the FG State string, i.e. size of the buffer.
    /// @param[in]  notifier                 Reference to an object which wants to be notified upon completion. The notification call shall not block.
    /// @return See the description of #StateClientResult.
    virtual StateClientResult GetState(const char* const funcGroup,
            char* const funcGroupState, uint32_t funcGroupStateMaxSize,
            IStateClientNotificator& notifier) = 0;

    /// @brief Issues a GetState request to the execution manager.
    ///
    /// This call issues a request to retrieve the state of the given function group.
    /// In addition to the default GetState call, it will not return IN_TRANSITION, but will try to retrieve a valid state up until timeout is reached.
    /// On successful or failed completion of the request, notifier will be called asynchronously.
    /// @traceid{SWS_EM_01028}  //R18-10
    /// @uptrace{RS_EM_00101}
    /// @uptrace{RS_AP_00131}
    /// @param[in]  funcGroup                The Function Group to command. NULL-terminated string.
    /// @param[out] funcGroupState           Pointer to a buffer to store the returning FG State.
    /// @param[in]  funcGroupStateMaxSize    Maximum allowed size for the FG State string, i.e. size of the buffer.
    /// @param[in]  notifier                 Reference to an object which wants to be notified upon completion. The notification call shall not block.
    /// @param[in]  timeout                  Timeout in milliseconds to wait for a Function Group transition to complete.
    /// @return See the description of #StateClientResult.
    virtual StateClientResult GetState(const char* const funcGroup,
            char* const funcGroupState, uint32_t funcGroupStateMaxSize,
            IStateClientNotificator& notifier, uint32_t timeout) = 0;

    /// @brief Issues a GetExecutionError request to the execution manager.
    ///
    /// This call issues a request to retrieve the process which cause function group in error state.
    /// On successful or failed completion of the request, notifier will be called asynchronously.
    /// @param[in]  funcGroup                The Function Group to command. NULL-terminated string.
    /// @param[out] process           Pointer to a buffer to store the returning FG State.
    /// @param[in]  ProcessNameMaxSize    Maximum allowed size for the FG State string, i.e. size of the buffer.
    /// @param[in]  notifier                 Reference to an object which wants to be notified upon completion. The notification call shall not block.
    /// @return See the description of #StateClientResult.
    virtual StateClientResult GetExecutionError(const char* const funcGroup, char* const process, uint32_t ProcessNameMaxSize, IStateClientNotificator& notifier) = 0;        
};
}  //namespace exm
}  //namespace vrte
}  // namespace bosch

#endif // _ISTATECLIENT_HPP_INCLUDED
