/// @copyright : 2022 Robert Bosch GmbH. All rights reserved.
#ifndef PUB_SUB_LOAN_SUBSCRIBER_PTP_LAYER_HPP
#define PUB_SUB_LOAN_SUBSCRIBER_PTP_LAYER_HPP

#include "SubscriberPtpLayer.hpp"
#include "pipc/loan/Debitor.hpp"
#include "pipc/loan/LoanedSamplePtr.hpp"
#include "pipc/protocol/Message.hpp"
#include "pipc/transport/Mailbox.hpp"

namespace pipc
{
namespace pub_sub
{
/**
 * @brief SubscriberPtpLayer for all subscribers.
 */
class LoanSubscriberPtpLayer : public SubscriberPtpLayer
{
    /** @brief Type-agnostic SamplePtr. */
    using SamplePtr = loan::LoanedSamplePtr<utils::Placeholder>;
    /** @brief Type-agnostic Debitor class. */
    using Debitor = loan::Debitor<utils::Placeholder, PIPC_MAX_CONCURRENT_PUBLISHER_MSGS>;
    /** @brief Type-agnostic Mailbox. */
    using Mailbox = transport::Mailbox<SamplePtr, PIPC_MAX_CONCURRENT_SUBSCRIBER_MSGS>;

public:
    LoanSubscriberPtpLayer() = default;

    Mailbox& getMailbox()
    {
        return mailbox_;
    }

    const Mailbox& getMailbox() const
    {
        return mailbox_;
    }

    Debitor& getDebitor()
    {
        return debitor_;
    }

    /** @brief Process a state change from the session layer. */
    template<size_t N, typename... TLayers>
    inline void processNotification(PtpEndpoint<TLayers...>& endpoint, StateChange change)
    {
        if (change == StateChange::kInvalid)
        {
            // Samples are invalid now, clean out the mailbox
            SamplePtr samplePtr;
            ReturnVal ret;
            do
            {
                ret = mailbox_.msgs_.try_pop(samplePtr);
            } while (ret != ReturnVal::kQueueEmpty);
        }
        SubscriberPtpLayer::processNotification<N>(endpoint, change);
    }

protected:
    /**
     * @brief Debitor class with access to SamplePool.
     */
    Debitor debitor_;
    /** @brief Mailbox with loaned sample ptrs. */
    Mailbox mailbox_;
};

} // namespace pub_sub
} // namespace pipc

#endif // PUB_SUB_LOAN_SUBSCRIBER_PTP_LAYER_HPP
