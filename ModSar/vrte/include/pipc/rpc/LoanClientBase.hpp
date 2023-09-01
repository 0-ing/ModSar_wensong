/// @copyright : 2022 Robert Bosch GmbH. All rights reserved.

#ifndef PIPC_RPC_LOAN_CLIENT_BASE_HPP
#define PIPC_RPC_LOAN_CLIENT_BASE_HPP

#include "ClientBase.hpp"
#include "LoanClientPtpLayer.hpp"
#include "ReplyMsg.hpp"
#include "RequestId.hpp"
#include "RequestMsg.hpp"
#include "pipc/loan/SamplePool.hpp"
#include "pipc/loan/SamplePtr.hpp"
#include "pipc/queue/MpMcQueue.hpp"
#include "pipc/transport/Message.hpp"
#include "pipc/utils/Expect.hpp"
#include "pipc/utils/Function.hpp"
#include "pipc/utils/Optional.hpp"
#include "pipc/utils/Placeholder.hpp"

namespace pipc
{
namespace rpc
{
/**
 * @brief Internal base class for all SHM RPC loan clients.
 *
 * @tparam MaxLoans Corresponds to the maximum no. of concurrent pending requests.
 */
template<size_t MaxLoans = PIPC_MAX_CONCURRENT_CLIENT_REQUESTS>
class LoanClientBase : public ClientBase<LoanClientPtpLayer<MaxLoans>>
{
private:
    using BaseClass = ClientBase<LoanClientPtpLayer<MaxLoans>>;
    using LoanId    = loan::LoanId;
    using SamplePtr = loan::SamplePtr<utils::Placeholder>;

public:
    using Creditor   = loan::Creditor<MaxLoans>;
    using SamplePool = loan::SamplePool<utils::Placeholder, MaxLoans, MpMcQueue<loan::SampleId, MaxLoans>>;
    using LayerState = protocol::LayerState;

protected:
    /**
     * @brief Construct the LoanClientBase and register it at the runtime.
     *
     * Protected constructor with callback passthrough for inheriting classes.
     *
     * @tparam TCallbacks The types of the callbacks to be registered for dispatch.
     * @param providerId The ProviderId of the server.
     * @param runtime The runtime to be used.
     * @param sampleSize The size of one RPC sample (only the request).
     * @param callbacks The callbacks to be registered for dispatch.
     */
    template<typename... TCallbacks>
    LoanClientBase(const session::ProviderId& providerId,
                   rte::IRuntime& runtime,
                   size_t sampleSize,
                   TCallbacks&&... callbacks)
        : BaseClass::ClientBase(providerId, runtime), samplePool_(sampleSize)
    {
        this->doRegistration(std::forward<TCallbacks>(callbacks)...);
    }

public:
    /**
     * @brief Initialize the clients' SamplePool.
     */
    void init(bool standalone) override
    {
        session::ProviderId& providerId = this->getSessionLayer().getProviderId();
        NodeId nodeId                   = this->runtime_.getNodeId();
        transport::Port port            = this->getTransportLayer().getSrcPort();

        auto path = providerId.toString(nodeId, port);
        samplePool_.setPath(path);
        if (standalone)
        {
            samplePool_.create();
        }
        else
        {
            samplePool_.open();
        }
        BaseClass::init(standalone);
    }

    /** @brief Get the Segment Size. */
    uint32_t getSegmentSize() const override
    {
        return static_cast<uint32_t>(samplePool_.capacity());
    }

    /** @brief Allocate a RPC sample and cast it to the desired type. */
    template<typename T = utils::Placeholder>
    inline loan::SamplePtr<T> allocate()
    {
        auto sample = samplePool_.allocate();
        // TODO: Redundant move operator?
        return std::move(static_cast<loan::SamplePtr<T>&>(sample));
    }

    /** @brief Report the max. no. of samples this client manages. */
    static constexpr size_t MaxSamples()
    {
        return MaxLoans;
    }

protected:
    /**
     * @brief Send a request based on a given sample pointer.
     *
     * Internal method, also used by inheriting classes.
     */
    ReturnCode sendRequest(SamplePtr& sample, RequestId& requestId)
    {
        if (this->getSessionLayer().getState() == LayerState::kValid)
        {
            auto& creditor = this->getAppLayer().getCreditor();
            auto loanId    = creditor.loan(sample, 1U);
            requestId      = loanId.getSeqCnt();

            RequestMsg<LoanId> msg;
            msg.requestId = requestId;
            msg.sessionId = this->getSessionLayer().getSessionId();
            msg.data      = loanId;

            auto ret = this->endpoint_.sendDatagram(msg);
            if (ret != ReturnCode::kOk)
            {
                creditor.restitute(loanId);
            }
            return ret;
        }
        else
        {
            PIPC_LOG_ERROR() << "RPC Client " << this->getSessionLayer().getProviderId().toString()
                             << ": Tried to send a request while not connected" << std::endl;
            return ReturnCode::kNotConnected;
        }
    }

    /** @brief The sample pool with RPC samples. */
    SamplePool samplePool_;
};

} // namespace rpc
} // namespace pipc

#endif // PIPC_RPC_LOAN_CLIENT_BASE_HPP
