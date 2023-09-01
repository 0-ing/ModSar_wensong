/// @copyright : 2022 Robert Bosch GmbH. All rights reserved.
#ifndef PIPC_PUB_SUB_LOAN_PUBLISHER_PTMP_LAYER_HPP
#define PIPC_PUB_SUB_LOAN_PUBLISHER_PTMP_LAYER_HPP

#include "PublisherPtmpLayer.hpp"
#include "pipc/loan/Creditor.hpp"

namespace pipc
{
namespace pub_sub
{
/**
 * @brief Publisher implementation for loan-restitute messaging.
 *
 * Similar to the PublisherImpl for self-contained messages
 * with the following adaptions:
 * - Contains the creditor logic for managing loaned sample ptrs
 * - Holds a bitfield with the bit set for each valid subscriber in the list
 *   (used for initial debitor states when sending loans)
 *
 * @remark
 * Thread safety: Not thread-safe!
 * Operations modifying or reading from the endpoints must be protected by a
 * lock.
 * Operations related to restitutions can happen concurrently.
 *
 */
template<size_t NLoans>
class LoanPublisherPtmpLayer : public PublisherPtmpLayer
{
    using BaseClass = PublisherPtmpLayer;
    using Creditor  = loan::Creditor<NLoans>;
    using LoanId    = loan::LoanId;
    template<typename T>
    using SamplePtr = loan::SamplePtr<T>;

public:
    /**
     * We need this method because there are processNotifications with different parameters.
     */
    template<size_t NLayer, typename TPtmpEndpoint>
    constexpr void processNotification(TPtmpEndpoint& endpoint, StateChange change)
    {
        protocol::ForwardNotification<NLayer>(endpoint, change);
    }

    /**
     * Process notifications from:
     *  - Provider Endpoint disconnect.
     *  - Provider Ptmp Layer received messages.
     * If this version of processNotification is called with StateChange::kInvalid, then the subscriber must be deactivated.
     */
    template<size_t NLayer,
             size_t NEndpoints,
             typename T0,
             typename T1,
             typename T2,
             typename T3,
             typename T4,
             typename T5,
             typename T6,
             typename T7>
    inline void processNotification(protocol::PtmpEndpoint<NEndpoints, T0, T1, T2, T3, T4, T5, T6, T7>& endpoint,
                                    StateChange change,
                                    protocol::PtpEndpoint<T0, T1, T2, T3>& subscriber)
    {
        if (change == StateChange::kInvalid)
        {
            bool callSubscribersCallback = false;
            {
                const std::lock_guard<std::mutex> lock(this->lock_);
                auto subscriberIdx      = endpoint.idx(subscriber);
                callSubscribersCallback = deactivateSubscriber(subscriberIdx);
                creditor_.reclaim(static_cast<loan::DebitorId>(subscriberIdx));
                PIPC_LOG_INFO() << "Deactivated subscriber " << static_cast<uint32_t>(subscriberIdx)
                                << " due to disconnect" << std::endl;
            }
            if (this->hasSubscribersCallback_ && callSubscribersCallback)
            {
                this->hasSubscribersCallback_(false);
            }
        }

        protocol::ForwardNotification<NLayer>(endpoint, change, subscriber);
    }

    /** @brief Forward a restitution to the creditor logic. */
    constexpr ReturnCode restitute(LoanId loanId)
    {
        return creditor_.restitute(loanId);
    }

    /**
     * @brief Send a datagram to the subscribers.
     */
    template<typename TMsg,
             size_t NEndpoints,
             typename T0,
             typename T1,
             typename T2,
             typename T3,
             typename T4,
             typename T5,
             typename T6,
             typename T7>
    inline void sendData(protocol::PtmpEndpoint<NEndpoints, T0, T1, T2, T3, T4, T5, T6, T7>& endpoint,
                         SamplePtr<TMsg>& samplePtr)
    {
        if (EXPECT_UNLIKELY(!isOffering_))
        {
            return;
        }

        const std::lock_guard<std::mutex> lock(this->lock_);
        auto activeSubscribers = this->activeSubscribers_;
        if (EXPECT_UNLIKELY(!activeSubscribers))
        {
            return;
        }

        auto subscriber = &endpoint.getEndpointEntries()[0];
        auto loanBaseId = creditor_.loan(samplePtr, activeSubscribers);
        size_t i        = 0U;
        do
        {
            if (activeSubscribers & 1UL)
            {
                PIPC_LOG_VERBOSE() << "LoanPublisherPtmpLayer: Sending loan to subscriber no. " << i << std::endl;
                auto ret = subscriber->endpoint.sendDatagram(loanBaseId.get(i));
                if (EXPECT_UNLIKELY(ret != ReturnCode::kOk))
                {
                    PIPC_LOG_ERROR() << "LoanPublisherPtmpLayer: Error sending to socket: " << (int)ret << std::endl;
                    restitute(loanBaseId.get(i));
                }
            }
            subscriber++;
            activeSubscribers >>= 1UL;
            i++;
        } while (activeSubscribers != 0UL);
    }

    /** @brief Get the creditor. */
    Creditor& getCreditor()
    {
        return creditor_;
    }

private:
    /** @brief The creditor logic. */
    Creditor creditor_;
};

} // namespace pub_sub
} // namespace pipc

#endif // PIPC_PUB_SUB_LOAN_PUBLISHER_PTMP_LAYER_HPP
