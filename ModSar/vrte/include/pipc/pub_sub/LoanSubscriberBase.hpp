/// @copyright : 2022 Robert Bosch GmbH. All rights reserved.
#ifndef PUB_SUB_LOAN_SUBSCRIBER_BASE_HPP
#define PUB_SUB_LOAN_SUBSCRIBER_BASE_HPP

#include "LoanSubscriberPtpLayer.hpp"
#include "SubscriberBase.hpp"
#include "pipc/loan/LoanMsg.hpp"
#include "pipc/loan/LoanedSamplePtr.hpp"
#include "pipc/protocol/Message.hpp"

namespace pipc
{
namespace pub_sub
{
/**
 * @brief LoanSubscriberBase for all subscribers with loan-restitute messaging.
 */
class LoanSubscriberBase : public SubscriberBase<LoanSubscriberPtpLayer>
{
    using BaseClass = SubscriberBase<LoanSubscriberPtpLayer>;
    using LoanMsg   = loan::LoanMsg;
    using SamplePtr = loan::LoanedSamplePtr<protocol::Placeholder>;

public:
    /** @brief Constructor including size per sample slot. */
    LoanSubscriberBase(session::ProviderId providerId, rte::IRuntime& runtime, size_t stride)
        : BaseClass(providerId, runtime)
    {
        this->getAppLayer().getDebitor().init(providerId.toString(), stride);
        auto& dispatcher = runtime.getDispatcher();
        auto port        = dispatcher.registerCbk(&Receive, &ReceiveLoan, *this);
        endpoint_.getLayer<protocol::kTransport>().setSrcPort(port);
        if (port != transport::INVALID_PORT)
        {
            runtime_.registerUser(*this);
        }
        else
        {
            PIPC_LOG_ERROR() << "Couldn't register Subscriber with ProviderId " << providerId.toString() << std::endl;
        }
    }

    /** @brief Notify the subscriber that a provider is available. */
    void notifyProviderOnline(pimp::Socket& socket, transport::Port port) override
    {
        this->getAppLayer().getDebitor().openSampleStorage();
        BaseClass::notifyProviderOnline(socket, port);
    }

private:
    /**
     * @brief Wrapper to receive a value.
     */
    static void ReceiveLoan(LoanSubscriberBase& obj, pimp::Socket& socket, transport::Datagram<LoanMsg>* msg)
    {
        obj.receiveLoan(socket, *msg);
    }

    /** @brief Function for receiving a value. */
    inline void receiveLoan(pimp::Socket& socket, const transport::Datagram<LoanMsg>& msg)
    {
        PIPC_LOG_VERBOSE() << "LoanSubscriber " << this->getSessionLayer().getProviderId().toString()
                           << ": Received loan message" << std::endl;
        typename SamplePtr::TDeleter deleter{&SendRestitution, this};
        loan::LoanId loanId = msg.payload();
        auto samplePtr      = getAppLayer().getDebitor().getSamplePtr(loanId, deleter);
        if (EXPECT_UNLIKELY(!samplePtr))
        {
            PIPC_LOG_WARN() << "LoanSubscriber " << getSessionLayer().getProviderId().toString()
                            << ": Got invalid loan msg." << std::endl;
            return;
        }
        // Assert for the correct identity of the publisher
        if (EXPECT_UNLIKELY(this->endpoint_.template getLayer<protocol::kNetwork>().getSocket() != &socket))
        {
            PIPC_LOG_WARN() << "LoanSubscriber " << getSessionLayer().getProviderId().toString()
                            << ": Got data message with invalid identity." << std::endl;
            return;
        }
        // Assert that we expect a message at all
        if (EXPECT_UNLIKELY(getSubscriptionState() != SubscriberPublicState::kSubscribed))
        {
            PIPC_LOG_WARN() << "LoanSubscriber " << getSessionLayer().getProviderId().toString()
                            << ": Unexpected loan msg received." << std::endl;
            return;
        }

        ReturnVal ret = getAppLayer().getMailbox().msgs_.try_push(std::move(samplePtr));
        if (EXPECT_UNLIKELY(ret != ReturnVal::kOk))
        {
            PIPC_LOG_ERROR() << "LoanSubscriber " << getSessionLayer().getProviderId().toString()
                             << ": Mailbox is full, couldn't store message." << std::endl;
            // TODO: check if restitution is sent properly in this case
            return;
        }
        auto& handler = this->getAppLayer().getEventReceiveHandler().read();
        if (handler)
        {
            handler();
        }
    }

    /**
     * @brief Wrapper to send a restitution.
     */
    static void SendRestitution(LoanSubscriberBase* obj, LoanMsg msg)
    {
        obj->sendRestitution(msg);
    }

    /** @brief Function for sending a restitution. */
    inline void sendRestitution(LoanMsg msg)
    {
        this->endpoint_.sendDatagram<LoanMsg>(msg);
    }
};

} // namespace pub_sub
} // namespace pipc

#endif // PUB_SUB_LOAN_SUBSCRIBER_BASE_HPP
