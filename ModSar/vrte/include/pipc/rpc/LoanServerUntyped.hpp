/// @copyright : 2022 Robert Bosch GmbH. All rights reserved.

#ifndef PIPC_RPC_LOANSERVERUNTYPED_HPP
#define PIPC_RPC_LOANSERVERUNTYPED_HPP

#include "ExecutorSelector.hpp"
#include "LoanServerBase.hpp"

namespace pipc
{
namespace rpc
{
/**
 * @brief Untyped implementation for Loan Server with synchronuous executor invocation.
 *
 * @todo
 * Get rid of template parameter in the LoanServerPtpLayer/Debitor class!
 */
template<bool VoidReply = false, bool VoidRequest = false, size_t RpcRequestsQueueSize = PIPC_MAX_PENDING_RPC_REQUESTS>
class LoanServerUntyped : public LoanServerBase<VoidReply, VoidRequest, RpcRequestsQueueSize>
{
protected:
    using BaseClass       = LoanServerBase<VoidReply, VoidRequest, RpcRequestsQueueSize>;
    using Placeholder     = utils::Placeholder;
    using LoanId          = loan::LoanId;
    using RpcRequest      = RequestMsg<LoanId>;
    using RpcReply        = ReplyMsg<LoanId>;
    using RequestDatagram = transport::Datagram<RpcRequest>;

    static_assert(!(VoidReply && VoidRequest),
                  "TReply==void && TRequest==void is not a possible option (already covered by rpc::Server).");

    using Executor = typename GenericExecutorSelector<VoidReply, VoidRequest>::Executor;

public:
    /** @brief Same constructor(s) as the base class. */
    using BaseClass::BaseClass;

    /**
     * @brief Register the Executor function for the incoming requests.
     *
     * @param executor The executor function.
     * @return ReturnCode
     *   - kOk
     *   - kExecutorAlreadyRegistered
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
     * Calls the matching executor for the pending request and send the back reply.
     *
     * @return boolean If there are anymore pending requests in the queue
     */
    bool processNextRequest()
    {
        // TODO: Cannot invoke executors in parallel
        // Implement refCount pattern for userEndpoint to remove limitation
        const std::lock_guard<std::mutex> lock(this->requestMutex_);
        RpcRequest requestMsg;
        if (this->pendingRequests_.try_pop(requestMsg) == ReturnVal::kOk)
        {
            auto clientEndpoint = this->endpoint_.get(requestMsg.sessionId);
            // Account for a potential race condition with a disconnect
            // HINT: We could still send to the wrong endpoint, but this can be handled
            // at the client side via the requestId
            if (clientEndpoint)
            {
                RpcReply replyMsg;
                auto request = clientEndpoint->template getLayer<protocol::kApp>().getDebitor().getRawPtr(
                    requestMsg.data);
                // Execute will set the reply value in the samplePtr directly
                execute(*request);
                // Prepare the replyMsg to be sent to the client
                replyMsg.requestId     = requestMsg.requestId;
                replyMsg.data          = requestMsg.data;
                replyMsg.hasValidReply = true;
                clientEndpoint->sendDatagram(replyMsg);
            }
        }
        return !this->pendingRequests_.empty();
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
    template<bool VoidRep = VoidReply, bool VoidReq = VoidRequest>
    inline typename std::enable_if<!VoidRep && !VoidReq, void>::type execute(Placeholder& request)
    {
        Placeholder& reply = (&request)[this->replyOffset_];
        executor_(reply, request);
    }

    /** @brief Call executor with a reply & a void request. */
    template<bool VoidRep = VoidReply, bool VoidReq = VoidRequest>
    inline typename std::enable_if<!VoidRep && VoidReq, void>::type execute(Placeholder& request)
    {
        Placeholder& reply = (&request)[this->replyOffset_];
        executor_(reply);
    }

    /** @brief Call executor with a request & a void reply. */
    template<bool VoidRep = VoidReply, bool VoidReq = VoidRequest>
    inline typename std::enable_if<VoidRep && !VoidReq, void>::type execute(Placeholder& request)
    {
        executor_(request);
    }

protected:
    /** @brief The callback function which will process the RPC request. */
    Executor executor_ = nullptr;
};

} // namespace rpc
} // namespace pipc

#endif // PIPC_RPC_LOANSERVERUNTYPED_HPP
