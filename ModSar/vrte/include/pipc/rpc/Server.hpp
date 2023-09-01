/// @copyright : 2022 Robert Bosch GmbH. All rights reserved.

#ifndef PIPC_RPC_SERVER_HPP
#define PIPC_RPC_SERVER_HPP

#include "ExecutorSelector.hpp"
#include "ReplyMsg.hpp"
#include "RequestMsg.hpp"
#include "ServerBase.hpp"
#include "pipc/queue/SpScQueue.hpp"

namespace pipc
{
namespace rpc
{
/**
 * @brief A class for processing Remote Procedure Calls.
 *
 * This class can be used whenever the server is expecting requests and sending a reply.
 *
 * @tparam TRequest The data type of the request.
 * @tparam TReply The data type of the reply.
 *
 * Supported functionalities:
 * - Support for sync mode (immediate processing of a response by calling processNextRequest())
 * - Support for async mode (queue request for later processing through the command)
 * - API sync & async handling of requests
 */
template<typename TReply, typename TRequest, size_t RpcRequestsQueueSize = PIPC_MAX_PENDING_RPC_REQUESTS>
class Server : public ServerBase<>
{
private:
    using BaseClass       = ServerBase<>;
    using RequestDatagram = transport::Datagram<RequestMsg<TRequest>>;
    using SessionId       = session::SessionId;
    using ProviderId      = session::ProviderId;
    using RpcRequest      = RequestMsg<TRequest>;
    using RpcReply        = ReplyMsg<TReply>;
    using IRuntime        = rte::IRuntime;
    using Socket          = pimp::Socket;
    using Executor        = typename ExecutorSelector<TReply, TRequest>::Executor;

public:
    /**
     * @brief Constructor for registering this class with a runtime.
     *
     * @param providerId The Id used to identify the Client.
     * @param runtime The runtime used for this Server.
     */
    inline Server(const ProviderId& providerId, IRuntime& runtime = rte::StandaloneRuntime::GetInstance())
        : ServerBase(providerId, runtime, &Receive, &ReceiveRequest)
    {
        overrideCmdOnDisconnect(&Server::InvalidatePendingRequests, this);
    }

    /**
     * @brief a method to register the Executor function for the incoming requests.
     *
     * @param executor the executor function.
     * @return ReturnCode tells if an is already registered or passed executor is registered successfully.
     */
    ReturnCode registerExecutor(Executor executor)
    {
        ReturnCode ret = ReturnCode::kExecutorAlreadyRegistered;
        if (!executor_)
        {
            executor_ = executor;
            ret       = ReturnCode::kOk;
        }
        return ret;
    }

    /**
     * @brief Method to process the next pending request.
     *
     * Process a request with request data of type TRequest,
     * calling the executor for it and sending the reply.
     *
     * @return boolean : is there anymore pending requests in the queue
     */
    bool processNextRequest()
    {
        RpcRequest request;
        ReturnVal ret;

        {
            const std::lock_guard<std::mutex> lock(requestMutex_);
            ret = pendingRequests_.try_pop(request);
        }
        if (ret == ReturnVal::kOk)
        {
            RpcReply reply;
            reply.requestId = request.requestId;
            reply.data.emplace();
            execute(request, reply);
            auto clientEndpoint = endpoint_.get(request.sessionId);
            // Account for a potential race condition with a disconnect
            // HINT: We could still send to the wrong endpoint, but this can be handled
            // at the client side via the requestId
            if (clientEndpoint)
            {
                clientEndpoint->sendDatagram(reply);
            }
        }
        return !pendingRequests_.empty();
    }

    /**
     * @brief calls the Provider startOffer() (only if an executor is registered).
     *
     * @return ReturnCode tells if NoExecutorRegistered or reuturning the Provider ReturnCode for calling startOffer().
     */
    ReturnCode startOffer()
    {
        if (EXPECT_UNLIKELY(!executor_))
        {
            PIPC_LOG_ERROR() << "Rpc Server: Can't offer without an executor." << std::endl;
            return ReturnCode::kNoExecutorRegistered;
        }
        return BaseClass::startOffer();
    }

private:
    /** @brief Call executor with a request & a reply. */
    template<typename TRep = TReply, typename TReq = TRequest>
    inline typename std::enable_if<!std::is_void<TRep>::value && !std::is_void<TReq>::value, void>::type execute(
        RpcRequest& request,
        RpcReply& reply)
    {
        executor_(reply.data.value(), request.data);
    }

    /** @brief Call executor with a reply & a void request. */
    template<typename TRep = TReply, typename TReq = TRequest>
    inline typename std::enable_if<!std::is_void<TRep>::value && std::is_void<TReq>::value, void>::type execute(
        RpcRequest&,
        RpcReply& reply)
    {
        executor_(reply.data.value());
    }

    /** @brief Call executor with a request & a void reply. */
    template<typename TRep = TReply, typename TReq = TRequest>
    inline typename std::enable_if<std::is_void<TRep>::value && !std::is_void<TReq>::value, void>::type execute(
        RpcRequest& request,
        RpcReply&)
    {
        executor_(request.data);
    }

    /** @brief Call executor with a void request & a void reply. */
    template<typename TRep = TReply, typename TReq = TRequest>
    inline typename std::enable_if<std::is_void<TRep>::value && std::is_void<TReq>::value, void>::type execute(
        RpcRequest&,
        RpcReply&)
    {
        executor_();
    }

    /** @brief A wrapper to receive a request. */
    static void ReceiveRequest(Server& obj, Socket& socket, RequestDatagram* msg)
    {
        obj.receiveRequest(socket, *msg);
    }

    /** @brief Function for receiving a request. */
    inline void receiveRequest(Socket& socket, const RequestDatagram& msg)
    {
        PIPC_LOG_DEBUG() << "Rpc Server: Received a request." << std::endl;

        if (EXPECT_UNLIKELY(getSessionLayer().getState() != protocol::LayerState::kValid))
        {
            PIPC_LOG_ERROR() << "Rpc Server: Received a request while not offering." << std::endl;
            return;
        }

        auto clientEndpoint = endpoint_.get(msg.payload().sessionId);
        if (EXPECT_UNLIKELY(!clientEndpoint))
        {
            PIPC_LOG_ERROR() << "Rpc Server: Received a request with invalid sessionId." << std::endl;
            return;
        }

        if (EXPECT_UNLIKELY(clientEndpoint->getSocket() != &socket))
        {
            PIPC_LOG_ERROR() << "Rpc Server: Received a request from invalid socket." << std::endl;
            return;
        }

        {
            ReturnVal ret;
            {
                const std::lock_guard<std::mutex> lock(requestMutex_);
                ret = pendingRequests_.try_emplace(msg.payload());
            }
            // In case of pending requests queue is full
            if (EXPECT_UNLIKELY(ret == ReturnVal::kQueueFull))
            {
                PIPC_LOG_ERROR() << "Rpc Server: Pending requests queue is full." << std::endl;
                // Sending empty reply to notify the client that the request is dropped
                RpcReply reply;
                reply.requestId = msg.payload().requestId;
                reply.data.reset();
                clientEndpoint->sendDatagram(reply);
                return;
            }
        }

        if (requestReceivedCallback_)
        {
            requestReceivedCallback_();
        }
    }

    /** @brief Wrapper to invalidatePendingRequests. */
    static void InvalidatePendingRequests(Server* obj, SessionId sessionId)
    {
        obj->invalidatePendingRequests(sessionId);
    }

    /**
     * @brief Invalidate pending requests of disconnected clients.
     *
     * @param sessionId the sessionId of the disconnected client.
     */
    inline void invalidatePendingRequests(SessionId sessionId)
    {
        BaseClass::invalidatePendingRequests<RpcRequest>(pendingRequests_, sessionId);
    }

    /** @brief the callback function which will process the RPC request */
    Executor executor_ = nullptr;
    /** @brief Queue to store the pending requests messages [to be processed in ProcessNextRequest()]*/
    SpScQueue<RpcRequest, RpcRequestsQueueSize> pendingRequests_;
};

} // namespace rpc
} // namespace pipc

#endif // PIPC_RPC_SERVER_HPP
