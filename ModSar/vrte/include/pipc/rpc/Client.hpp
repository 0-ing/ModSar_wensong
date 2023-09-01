/// @copyright : 2022 Robert Bosch GmbH. All rights reserved.

#ifndef PIPC_RPC_CLIENT_HPP
#define PIPC_RPC_CLIENT_HPP

#include "ClientFireAndForget.hpp"
#include "ReplyMsg.hpp"
#include "RequestMsg.hpp"
#include "pipc/protocol/Layer.hpp"
#include "pipc/transport/Message.hpp"

#include <type_traits>

namespace pipc
{
namespace rpc
{
/**
 * @brief A RPC client which supports self-contained messaging.
 *
 * This client can be used for typical RPC request->reply scenarios.
 *
 * @tparam TReply The data type of the reply.
 *  - void means no real data is returned in the reply, but a reply
 *    is still sent by the server to signalize that the request has been processed
 * @tparam TRequest The data type of the request.
 *  - void means no data is used for the request
 */
template<typename TReply, typename TRequest>
class Client : public ClientBase<>
{
private:
    using BaseClass = ClientBase<>;
    template<typename T>
    using Optional              = utils::Optional<T>;
    using LayerState            = protocol::LayerState;
    using ReplyDatagram         = transport::Datagram<ReplyMsg<TReply>>;
    using ReplyReceivedCallback = utils::Function<void(const Optional<TReply>&, RequestId)>;
    using Socket                = pimp::Socket;

public:
    /**
     * @brief Constructor for registering the Client with a runtime.
     *
     * @param providerId The Id used to identify the Server.
     * @param replyReceivedCallback Callback invoked whenever a reply is received.
     * @param runtime The runtime used for this Client.
     *
     * @remark
     * Note that the replyReceivedCallback has to be given as constructor parameter.
     * This makes it easier to handle connecting under the hood, as the
     * replyReceivedCallback is always valid after instantiation.
     */
    Client(const session::ProviderId& providerId,
           const ReplyReceivedCallback& replyReceivedCallback,
           rte::IRuntime& runtime = rte::StandaloneRuntime::GetInstance())
        : BaseClass::ClientBase(providerId, runtime, &BaseClass::Receive, &ReceiveReply),
          replyReceivedCallback_(replyReceivedCallback),
          nextRequestId(0)
    {
    }

    /**
     * @brief Send a request to be processed by the server.
     *
     * Variant for sending requests with input data.
     *
     * @param request The data of the request.
     * @param[out] requestId The Id used to map the request to a reply.
     * @return
     *  - kOk : Sending was successful
     *  - kNetworkError : There was an error sending to the socket
     *  - kNotConnected : Connection to the server is not established
     */
    template<typename T = TRequest, typename = typename std::enable_if<!std::is_void<T>::value>::type>
    ReturnCode sendRequest(const T& request, RequestId& requestId)
    {
        if (this->getSessionLayer().getState() == LayerState::kValid)
        {
            requestId = nextRequestId++;
            RequestMsg<TRequest> msg;
            msg.requestId = requestId;
            msg.sessionId = this->getSessionLayer().getSessionId();
            msg.data      = request;
            return this->endpoint_.sendDatagram(msg);
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
     * @param[out] requestId The Id used to map the request to a reply.
     * @return
     *  - kOk : Sending was successful
     *  - kNetworkError : There was an error sending to the socket
     *  - kNotConnected : Connection to the server is not established
     */
    template<typename T = TRequest, typename = typename std::enable_if<std::is_void<T>::value>::type>
    ReturnCode sendRequest(RequestId& requestId)
    {
        if (this->getSessionLayer().getState() == LayerState::kValid)
        {
            requestId = nextRequestId++;
            RequestMsg<TRequest> msg;
            msg.requestId = requestId;
            msg.sessionId = this->getSessionLayer().getSessionId();
            return this->endpoint_.sendDatagram(msg);
        }
        else
        {
            return ReturnCode::kNotConnected;
        }
    }

private:
    /** @brief Wrapper to receive a reply. */
    static void ReceiveReply(Client<TReply, TRequest>& obj, Socket& socket, ReplyDatagram* msg)
    {
        obj.receiveReply(socket, *msg);
    }

    /** @brief Function for receiving a reply. */
    inline void receiveReply(Socket& socket, const ReplyDatagram& msg)
    {
        // Assert for the correct identity of the server
        if (this->getNetworkLayer().getSocket() == &socket)
        {
            // Assert we really are connected and expect replies
            // HINT: Corrupted messages could reach this function,
            // as datagrams bypass the protocol stack
            if (this->getSessionLayer().getState() == protocol::LayerState::kValid)
            {
                replyReceivedCallback_(msg.payload().data, msg.payload().requestId);
            }
            else
            {
                PIPC_LOG_ERROR() << "Rpc Client: Unexpected reply msg received." << std::endl;
            }
        }
        else
        {
            PIPC_LOG_ERROR() << "Rpc Client: Got reply msg with invalid identity." << std::endl;
        }
    }

    /**
     * @brief Callback for receiving replies from the server.
     *
     * The callback is invoked whenever the client receives a reply to a previous request.
     * The reply data is wrapped in an Optional. If the Optional does not have a value,
     * this means the server was not able to process the request.
     */
    ReplyReceivedCallback replyReceivedCallback_;

    /**
     * @brief Next request Id used, when a request is sent.
     *
     * The request Id is sent together with a request and incremented after
     * each send operation.
     */
    RequestId nextRequestId;
};

} // namespace rpc
} // namespace pipc

#endif // PIPC_RPC_CLIENT_HPP
