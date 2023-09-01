/// @copyright : 2022 Robert Bosch GmbH. All rights reserved.

#ifndef PIPC_RPC_LOAN_CLIENT_UNTYPED_HPP
#define PIPC_RPC_LOAN_CLIENT_UNTYPED_HPP

#include "LoanClientBase.hpp"

namespace pipc
{
namespace rpc
{
/**
 * @brief A class for SHM RPC clients without type safety.
 *
 * This class serves as an untyped SHM RPC client. It can be either used directly
 * (for internal use cases like binding implementations) or be enhanced to provide
 * a type-safe RPC SHM Client.
 *
 * @tparam MaxLoans Corresponds to the maximum no. of concurrent pending requests.
 * @tparam VoidReply Info whether a reply contains data or not.
 */
template<bool VoidReply = false, size_t MaxLoans = PIPC_MAX_CONCURRENT_CLIENT_REQUESTS>
class LoanClientUntyped : public LoanClientBase<MaxLoans>
{
private:
    using BaseClass = LoanClientBase<MaxLoans>;

public:
    using SamplePtr = loan::SamplePtr<utils::Placeholder>;

    // CallbackSelector is needed for ReplyReceivedCallback with a void reply.
    // C++14 doesn't allow explicit template specialization in a class, the fake parameter is a needed workaround.
    template<bool B, typename fake = void>
    struct CallbackSelector
    {
        using Callback = utils::Function<void(SamplePtr&&, RequestId)>;
    };
    template<typename fake>
    struct CallbackSelector<true, fake>
    {
        using Callback = utils::Function<void(utils::Optional<void>, RequestId)>;
    };

    using Creditor              = loan::Creditor<MaxLoans>;
    using LayerState            = protocol::LayerState;
    using LoanId                = loan::LoanId;
    using ReplyDatagram         = transport::Datagram<ReplyMsg<LoanId>>;
    using ReplyReceivedCallback = typename CallbackSelector<VoidReply>::Callback;
    using SamplePool            = loan::SamplePool<utils::Placeholder, MaxLoans, MpMcQueue<loan::SampleId, MaxLoans>>;

    /**
     * @brief Construct the LoanClientUntyped and register it at the runtime.
     *
     * @param providerId The ProviderId of the server.
     * @param replyReceivedCallback The callback invoked when receiving a reply.
     * @param runtime The runtime to be used.
     * @param sampleSize The size of one RPC sample (request & reply combined).
     * @param replyOffset The offset in the sample, where the reply starts.
     */
    LoanClientUntyped(const session::ProviderId& providerId,
                      const ReplyReceivedCallback& replyReceivedCallback,
                      rte::IRuntime& runtime,
                      size_t sampleSize,
                      size_t replyOffset = 0UL)
        : BaseClass(providerId, runtime, sampleSize, &BaseClass::Receive, &ReceiveReply),
          replyReceivedCallback_(replyReceivedCallback),
          replyOffset_(replyOffset)
    {
    }

    /**
     * @brief Send a request based on a given sample pointer.
     */
    inline ReturnCode sendRequest(SamplePtr&& sample, RequestId& requestId)
    {
        return BaseClass::sendRequest(sample, requestId);
    }

protected:
    /** @brief Make the BaseClass' sendRequest available to direct inheritors. */
    using BaseClass::sendRequest;

private:
    /** @brief Static function wrapper to receive a reply. */
    static void ReceiveReply(LoanClientUntyped& obj, pimp::Socket& socket, ReplyDatagram* msg)
    {
        obj.receiveReply(socket, *msg);
    }

    /**
     * @brief Receive a reply to a prior request.
     *
     * Variant for replies with data.
     */
    template<bool B = VoidReply>
    typename std::enable_if<!B, void>::type receiveReply(pimp::Socket& socket, const ReplyDatagram& msg)
    {
        if (EXPECT_UNLIKELY(this->getNetworkLayer().getSocket() != &socket))
        {
            PIPC_LOG_ERROR() << "Rpc Client: Got reply msg with invalid identity." << std::endl;
            return;
        }
        if (EXPECT_UNLIKELY(this->getSessionLayer().getState() != LayerState::kValid))
        {
            PIPC_LOG_ERROR() << "Rpc Client: Got reply msg while not connected." << std::endl;
            return;
        }
        if (EXPECT_UNLIKELY(!msg.payload().hasValidReply))
        {
            PIPC_LOG_ERROR() << "Rpc Client: Got reply msg with empty payload." << std::endl;
            LoanId loanId      = msg.payload().data;
            Creditor& creditor = this->getAppLayer().getCreditor();
            auto ret           = creditor.restitute(loanId);
            if (EXPECT_UNLIKELY(ret != ReturnCode::kOk))
            {
                // TODO: A loan might be stuck forever, crash?
                PIPC_LOG_FATAL() << "Rpc Client: Error restituting loan from reply msg: " << ToString(ret) << std::endl;
            }
            SamplePtr emptyReplySample;
            replyReceivedCallback_(std::move(emptyReplySample), msg.payload().requestId);
            return;
        }

        Creditor& creditor = this->getAppLayer().getCreditor();
        typename Creditor::Deleter reclaimCmd;
        LoanId loanId = msg.payload().data;
        auto ret      = creditor.release(loanId, reclaimCmd);
        if (EXPECT_UNLIKELY(ret != ReturnCode::kOk))
        {
            // TODO: A loan might be stuck forever, crash?
            PIPC_LOG_FATAL() << "Rpc Client: Error releasing loan from reply msg: " << ToString(ret) << std::endl;
            SamplePtr emptyReplySample;
            replyReceivedCallback_(std::move(emptyReplySample), msg.payload().requestId);
            return;
        }

        auto replyAddress = reinterpret_cast<utils::Placeholder*>(this->samplePool_.getAddress(loanId.getSampleId())
                                                                  + replyOffset_);
        SamplePtr replySample{replyAddress, reclaimCmd, loanId.getSampleId()};
        replyReceivedCallback_(std::move(replySample), msg.payload().requestId);
    }

    /**
     * @brief Receive a reply to a prior request.
     *
     * Variant for void replies.
     */
    template<bool B = VoidReply>
    typename std::enable_if<B, void>::type receiveReply(pimp::Socket& socket, const ReplyDatagram& msg)
    {
        if (EXPECT_UNLIKELY(this->getNetworkLayer().getSocket() != &socket))
        {
            PIPC_LOG_ERROR() << "Rpc Client: Got reply msg with invalid identity." << std::endl;
            return;
        }
        if (EXPECT_UNLIKELY(this->getSessionLayer().getState() != protocol::LayerState::kValid))
        {
            PIPC_LOG_ERROR() << "Rpc Client: Got reply msg while not connected." << std::endl;
            return;
        }
        if (EXPECT_UNLIKELY(!msg.payload().hasValidReply))
        {
            PIPC_LOG_ERROR() << "Rpc Client: Got reply msg with empty payload." << std::endl;
            LoanId loanId      = msg.payload().data;
            Creditor& creditor = this->getAppLayer().getCreditor();
            auto ret           = creditor.restitute(loanId);
            if (EXPECT_UNLIKELY(ret != ReturnCode::kOk))
            {
                // TODO: A loan might be stuck forever, crash?
                PIPC_LOG_FATAL() << "Rpc Client: Error restituting loan from reply msg: " << ToString(ret) << std::endl;
            }
            replyReceivedCallback_(false, msg.payload().requestId);
            return;
        }

        Creditor& creditor = this->getAppLayer().getCreditor();
        LoanId loanId      = msg.payload().data;
        auto ret           = creditor.restitute(loanId);
        if (EXPECT_UNLIKELY(ret != ReturnCode::kOk))
        {
            // TODO: A loan might be stuck forever, crash?
            PIPC_LOG_FATAL() << "Rpc Client: Error restituting loan from reply msg: " << ToString(ret) << std::endl;
            replyReceivedCallback_(false, msg.payload().requestId);
            return;
        }

        replyReceivedCallback_(true, msg.payload().requestId);
    }

    /** @brief The callback to be registered by the user to handle replies. */
    ReplyReceivedCallback replyReceivedCallback_;
    /** @brief The offset used to find the start of the reply in a sample. */
    size_t replyOffset_;
};

} // namespace rpc
} // namespace pipc

#endif // PIPC_RPC_LOAN_CLIENT_UNTYPED_HPP
