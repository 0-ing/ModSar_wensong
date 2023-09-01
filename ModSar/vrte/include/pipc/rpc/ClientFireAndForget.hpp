/// @copyright : 2022 Robert Bosch GmbH. All rights reserved.

#ifndef PIPC_RPC_CLIENT_FIRE_AND_FORGET_HPP
#define PIPC_RPC_CLIENT_FIRE_AND_FORGET_HPP

#include "ClientBase.hpp"
#include "RequestMsg.hpp"
#include "pipc/protocol/Layer.hpp"

#include <type_traits>

namespace pipc
{
namespace rpc
{
/**
 * @brief A "Fire And Forget" RPC client which supports self-contained messaging.
 *
 * This class can be used whenever requests need to be sent without expecting
 * a reply or any other kind of feedback, whether the server has processed
 * the request.
 *
 * @tparam TRequest The data type of the request.
 *  - void means no data is used for the request
 */
template<typename TRequest>
class ClientFireAndForget : public ClientBase<>
{
    using BaseClass = ClientBase<>;

public:
    /**
     * @brief Constructor for registering this class with a runtime.
     *
     * @param providerId The Id used to identify the ServerFireAndForget.
     * @param replyReceivedCallback Callback invoked whenever a reply is received.
     * @param runtime The runtime used for this ClientFireAndForget.
     */
    ClientFireAndForget(const session::ProviderId& providerId,
                        rte::IRuntime& runtime = rte::StandaloneRuntime::GetInstance())
        : ClientBase(providerId, runtime, &Receive), nextRequestId(0)
    {
    }

public:
    /**
     * @brief Send a request to be processed by the server.
     *
     * Variant for sending requests with input data.
     *
     * @param request The data of the request.
     * @return
     *  - kOk : Sending was successful
     *  - kNetworkError : There was an error sending to the socket
     *  - kNotConnected : Connection to the server is not established
     */
    template<typename T = TRequest, typename = typename std::enable_if<!std::is_void<T>::value>::type>
    ReturnCode sendRequest(const T& request)
    {
        if (getSessionLayer().getState() == LayerState::kValid)
        {
            RequestMsg<TRequest> msg;
            msg.requestId = nextRequestId++;
            msg.sessionId = getSessionLayer().getSessionId();
            msg.data      = request;
            return endpoint_.sendDatagram(msg);
        }
        else
        {
            return ReturnCode::kNotConnected;
        }
    }

    /**
     * @brief Send a request to be processed by the server.
     *
     * Variant for sending requests without input data.
     *
     * @return
     *  - kOk : Sending was successful
     *  - kNetworkError : There was an error sending to the socket
     *  - kNotConnected : Connection to the server is not established
     */
    template<typename T = TRequest, typename = typename std::enable_if<std::is_void<T>::value>::type>
    ReturnCode sendRequest()
    {
        if (getSessionLayer().getState() == LayerState::kValid)
        {
            RequestMsg<TRequest> msg;
            msg.requestId = nextRequestId;
            msg.sessionId = getSessionLayer().getSessionId();
            return endpoint_.sendDatagram(msg);
        }
        else
        {
            return ReturnCode::kNotConnected;
        }
    }

private:
    /**
     * @brief Next request Id used, when a request is sent.
     *
     * The request Id is sent together with a request and incremented after
     * each send operation.
     *
     * @todo
     * Do we want to get rid of this for Fire And Forget?
     */
    RequestId nextRequestId;
};

} // namespace rpc
} // namespace pipc

#endif // PIPC_RPC_CLIENT_FIRE_AND_FORGET_HPP
