/// @copyright : 2022 Robert Bosch GmbH. All rights reserved.

#ifndef PIPC_RPC_SERVER_FIRE_AND_FORGET_HPP
#define PIPC_RPC_SERVER_FIRE_AND_FORGET_HPP

#include "ExecutorSelector.hpp"
#include "RequestMsg.hpp"
#include "ServerBase.hpp"
#include "pipc/queue/SpScQueue.hpp"

namespace pipc
{
namespace rpc
{
/**
 * @brief A "Fire And Forget" RPC server which sends no reply.
 *
 * This class can be used whenever the server is expecting requests without sending
 * a reply or any other kind of feedback, whether the request has been processed or not.
 *
 * @tparam TRequest The data type of the request.
 *  - void means no data is used for the request
 */
template<typename TRequest, size_t RpcRequestsQueueSize = PIPC_MAX_PENDING_RPC_REQUESTS>
class ServerFireAndForget : public ServerBase<>
{
private:
    using BaseClass       = ServerBase<>;
    using RequestDatagram = transport::Datagram<RequestMsg<TRequest>>;
    using SessionId       = session::SessionId;
    using RpcRequest      = RequestMsg<TRequest>;
    using Executor        = typename ExecutorSelector<void, TRequest>::Executor;

public:
    /**
     * @brief Constructor for registering this class with a runtime.
     *
     * @param providerId The Id used to identify the ClientFireAndForget.
     * @param replyReceivedCallback Callback invoked whenever a request is received.
     * @param runtime The runtime used for this ServerFireAndForget.
     */
    ServerFireAndForget(const session::ProviderId& providerId,
                        rte::IRuntime& runtime = rte::StandaloneRuntime::GetInstance())
        : ServerBase(providerId, runtime, &Receive, &ReceiveRequest)
    {
        overrideCmdOnDisconnect(&ServerFireAndForget::InvalidatePendingRequests, this);
    }

    /** @brief a method to register the Executor function for the incoming requests.
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
     * calling the executor for it.
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
            execute(request);
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
    /** @brief Call executor with a request & a void reply. */
    template<typename TReq = TRequest>
    inline typename std::enable_if<!std::is_void<TReq>::value, void>::type execute(RpcRequest& request)
    {
        executor_(request.data);
    }

    /** @brief Call executor with a void request & a void reply. */
    template<typename TReq = TRequest>
    inline typename std::enable_if<std::is_void<TReq>::value, void>::type execute(RpcRequest&)
    {
        executor_();
    }

    /** @brief A wrapper to receive a request. */
    static void ReceiveRequest(ServerFireAndForget& obj, Socket& socket, RequestDatagram* msg)
    {
        obj.receiveRequest(socket, *msg);
    }

    /** @brief Function for receiving a request. */
    inline void receiveRequest(Socket& socket, const RequestDatagram& msg)
    {
        auto clientEndpoint = endpoint_.get(msg.payload().sessionId);
        if (EXPECT_UNLIKELY(!clientEndpoint))
        {
            return;
        }

        if (EXPECT_UNLIKELY(clientEndpoint->getSocket() != &socket))
        {
            PIPC_LOG_ERROR() << "Rpc Server: SessionId doesn't match." << std::endl;
            return;
        }

        if (EXPECT_UNLIKELY(getSessionLayer().getState() != protocol::LayerState::kValid))
        {
            PIPC_LOG_ERROR() << "Rpc Server: Unexpected Request msg received." << std::endl;
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
                PIPC_LOG_INFO() << "Rpc Server: pending requests Queue is full." << std::endl;
                return;
            }
        }

        if (requestReceivedCallback_)
        {
            requestReceivedCallback_();
        }
    }

    /** @brief Wrapper to invalidatePendingRequests. */
    static void InvalidatePendingRequests(ServerFireAndForget* obj, SessionId sessionId)
    {
        obj->invalidatePendingRequests(sessionId);
    }

    /** @brief invalidate pending requests of disconnected clients
     *
     * @param sessionId the sessionId of the disconnected client.
     */
    void invalidatePendingRequests(SessionId sessionId)
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

#endif // PIPC_RPC_SERVER_FIRE_AND_FORGET_HPP
