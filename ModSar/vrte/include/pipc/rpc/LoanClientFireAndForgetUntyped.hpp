/// @copyright : 2022 Robert Bosch GmbH. All rights reserved.

#ifndef PIPC_RPC_LOAN_CLIENT_FIRE_AND_FORGET_UNTYPED_HPP
#define PIPC_RPC_LOAN_CLIENT_FIRE_AND_FORGET_UNTYPED_HPP

#include "LoanClientBase.hpp"

namespace pipc
{
namespace rpc
{
/**
 * @brief A base class for SHM RPC Fire And Forget clients.
 *
 * This class provides (untyped) base functionality for all SHM RPC F&F clients.
 *
 * @tparam MaxLoans Corresponds to the maximum no. of concurrent pending requests.
 */
template<size_t MaxLoans = PIPC_MAX_CONCURRENT_CLIENT_REQUESTS>
class LoanClientFireAndForgetUntyped : public LoanClientBase<MaxLoans>
{
private:
    using BaseClass = LoanClientBase<MaxLoans>;
    using LoanId    = loan::LoanId;
    using SamplePtr = loan::SamplePtr<utils::Placeholder>;

public:
    using Creditor      = loan::Creditor<MaxLoans>;
    using ReplyDatagram = transport::Datagram<ReplyMsg<LoanId>>;
    using LayerState    = protocol::LayerState;

    /**
     * @brief Construct the LoanClientFireAndForgetUntyped and register it at the runtime.
     *
     * @param providerId The ProviderId of the server.
     * @param runtime The runtime to be used.
     * @param sampleSize The size of one RPC sample (only the request).
     */
    LoanClientFireAndForgetUntyped(const session::ProviderId& providerId, rte::IRuntime& runtime, size_t sampleSize)
        : BaseClass(providerId, runtime, sampleSize, &BaseClass::Receive, &ReceiveReply)
    {
    }

    /**
     * @brief Send a request based on a given sample pointer.
     */
    inline ReturnCode sendRequest(SamplePtr&& sample)
    {
        return sendRequest(sample);
    }

protected:
    /**
     * @brief Send a request based on a given sample pointer.
     *
     * Internal method, also used by inheriting classes.
     */
    inline ReturnCode sendRequest(SamplePtr& sample)
    {
        RequestId requestId;
        return BaseClass::sendRequest(sample, requestId);
    }

private:
    /** @brief Static function wrapper to receive a reply. */
    static void ReceiveReply(LoanClientFireAndForgetUntyped& obj, pimp::Socket& socket, ReplyDatagram* msg)
    {
        obj.receiveReply(socket, *msg);
    }

    /**
     * @brief Receive a reply to a prior request.
     */
    void receiveReply(pimp::Socket& socket, const ReplyDatagram& msg)
    {
        if (EXPECT_UNLIKELY(this->getNetworkLayer().getSocket() != &socket))
        {
            PIPC_LOG_ERROR() << "Rpc Client FF: Got reply msg with invalid identity." << std::endl;
            return;
        }
        if (EXPECT_UNLIKELY(this->getSessionLayer().getState() != LayerState::kValid))
        {
            PIPC_LOG_ERROR() << "Rpc Client FF: Got reply msg while not connected." << std::endl;
            return;
        }

        LoanId loanId      = msg.payload().data;
        Creditor& creditor = this->getAppLayer().getCreditor();
        auto ret           = creditor.restitute(loanId);
        if (EXPECT_UNLIKELY(ret != ReturnCode::kOk))
        {
            // TODO: A loan might be stuck forever, crash?
            PIPC_LOG_FATAL() << "Rpc Client FF: Error restituting loan from reply msg: " << (int)ret << std::endl;
        }
    }
};

} // namespace rpc
} // namespace pipc

#endif // PIPC_RPC_LOAN_CLIENT_FIRE_AND_FORGET_UNTYPED_HPP
