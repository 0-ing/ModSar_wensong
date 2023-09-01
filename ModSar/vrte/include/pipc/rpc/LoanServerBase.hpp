/// @copyright : 2022 Robert Bosch GmbH. All rights reserved.

#ifndef PIPC_RPC_LOAN_SERVER_BASE_HPP
#define PIPC_RPC_LOAN_SERVER_BASE_HPP

#include "LoanServerPtmpLayer.hpp"
#include "LoanServerPtpLayer.hpp"
#include "ReplyMsg.hpp"
#include "RequestMsg.hpp"
#include "ServerBase.hpp"
#include "pipc/loan/LoanMsg.hpp"
#include "pipc/loan/LoanedSamplePtr.hpp"

namespace pipc
{
namespace rpc
{
/**
 * @brief Base class for LoanServer.
 *
 * This base class can be used for "context-free" handling of requests.
 *
 * @todo
 * Get rid of template parameter in the LoanServerPtpLayer/Debitor class!
 */
template<bool VoidReply = false, bool VoidRequest = false, size_t RpcRequestsQueueSize = PIPC_MAX_PENDING_RPC_REQUESTS>
class LoanServerBase : public ServerBase<PIPC_MAX_SRVR_USERS, LoanServerPtpLayer<>, LoanServerPtmpLayer>
{
public:
    using BaseClass       = ServerBase<PIPC_MAX_SRVR_USERS, LoanServerPtpLayer<>, LoanServerPtmpLayer>;
    using Placeholder     = utils::Placeholder;
    using LoanId          = loan::LoanId;
    using RpcRequest      = RequestMsg<LoanId>;
    using RpcReply        = ReplyMsg<LoanId>;
    using RequestDatagram = transport::Datagram<RpcRequest>;

    static_assert(!(VoidReply && VoidRequest),
                  "TReply==void && TRequest==void is not a possible option (already covered by rpc::Server).");

public:
    /** @brief constructor to initialize the ServerBase class and initialize the debitor storage. */
    LoanServerBase(session::ProviderId providerId, rte::IRuntime& runtime, size_t sampleSize, size_t replyOffset)
        : BaseClass(providerId, runtime, &Receive, &ReceiveRequest), replyOffset_(replyOffset)
    {
        overrideCmdOnDisconnect(&LoanServerBase::InvalidatePendingRequests, this);
        this->getAppLayer().setStride(sampleSize);
    }

    /**
     * @brief Get the next pending request.
     *
     * @param request The object where the request will be written into.
     * @return ReturnVal OK or queue empty.
     */
    template<typename TRequest, typename TReply>
    ReturnVal getNextPendingRequest(RpcRequest& request, std::pair<TRequest*, TReply*>& dataPtrs)
    {
        // requestMutex has to be locked by the caller
        // const std::lock_guard<std::mutex> lock(this->requestMutex_);
        auto ret = this->pendingRequests_.try_pop(request);
        // Request queue could be empty
        if (ret == ReturnVal::kOk)
        {
            auto clientEndpoint = this->endpoint_.get(request.sessionId);
            auto requestPtr = clientEndpoint->template getLayer<protocol::kApp>().getDebitor().getRawPtr(request.data);
            dataPtrs.first  = reinterpret_cast<TRequest*>(requestPtr);
            dataPtrs.second = reinterpret_cast<TReply*>(&(requestPtr[replyOffset_]));
        }
        return ret;
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

    /**
     * @brief Reply to the given rpc request.
     *
     * Sends the loan back to the client.
     *
     * @param rpcRequest The request to be discarded.
     */
    void reply(const RpcRequest& rpcRequest, bool valid = true)
    {
        auto clientEndpoint = endpoint_.get(rpcRequest.sessionId);
        RpcReply reply;
        reply.requestId     = rpcRequest.requestId;
        reply.data          = rpcRequest.data;
        reply.hasValidReply = valid;
        clientEndpoint->sendDatagram(reply);
    }

private:
    /** @brief A wrapper to receive a request. */
    static void ReceiveRequest(LoanServerBase& obj, Socket& socket, RequestDatagram* msg)
    {
        obj.receiveRequest(socket, *msg);
    }

    /** @brief Function for receiving a request. */
    inline void receiveRequest(Socket& socket, const RequestDatagram& msg)
    {
        PIPC_LOG_DEBUG() << "Rpc Server " << this->getSessionLayer().getProviderId().toString()
                         << ": Received a request." << std::endl;

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

        loan::LoanId loanId = msg.payload().data;
        auto rawPtr         = clientEndpoint->template getLayer<protocol::kApp>().getDebitor().getRawPtr(loanId);
        if (EXPECT_UNLIKELY(!rawPtr))
        {
            PIPC_LOG_ERROR() << "Rpc Server: Got invalid loan msg." << std::endl;
            // Sending empty reply to notify the client that the request is dropped
            RpcReply reply;
            reply.requestId     = msg.payload().requestId;
            reply.data          = loanId;
            reply.hasValidReply = false;
            clientEndpoint->sendDatagram(reply);
            return;
        }

        ReturnVal ret;
        {
            // TODO: Think about pushing also the dataPtrs into the pending requests queue
            const std::lock_guard<std::mutex> lock(requestMutex_);
            ret = pendingRequests_.try_emplace(msg.payload());
        }
        // In case of pending requests queue is full
        if (EXPECT_UNLIKELY(ret == ReturnVal::kQueueFull))
        {
            PIPC_LOG_ERROR() << "Rpc Server: Pending requests queue is full." << std::endl;
            // Sending empty reply to notify the client that the request is dropped
            RpcReply reply;
            reply.requestId     = msg.payload().requestId;
            reply.data          = loanId;
            reply.hasValidReply = false;
            clientEndpoint->sendDatagram(reply);
            return;
        }

        if (requestReceivedCallback_)
        {
            requestReceivedCallback_();
        }
    }

    /** @brief Wrapper to invalidatePendingRequests. */
    static void InvalidatePendingRequests(LoanServerBase* obj, SessionId sessionId)
    {
        obj->invalidatePendingRequests(sessionId);
    }

protected:
    /** @brief Queue to store the pending requests [to be processed in ProcessNextRequest()]*/
    SpScQueue<RpcRequest, RpcRequestsQueueSize> pendingRequests_;
    /** @brief The offset used to find the start of the reply in a sample. */
    size_t replyOffset_;
};

} // namespace rpc
} // namespace pipc

#endif // PIPC_RPC_LOAN_SERVER_BASE_HPP
