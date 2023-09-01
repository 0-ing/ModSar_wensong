/// @copyright : 2022 Robert Bosch GmbH. All rights reserved.

#ifndef PUB_SUB_PUBLISHER_PTMP_LAYER_HPP
#define PUB_SUB_PUBLISHER_PTMP_LAYER_HPP

#include "PublisherMsg.hpp"
#include "SubscriberMsg.hpp"
#include "pipc/Logger.hpp"
#include "pipc/ReturnCode.hpp"
#include "pipc/protocol/DefaultLayer.hpp"
#include "pipc/protocol/EndpointId.hpp"
#include "pipc/utils/Expect.hpp"
#include "pipc/utils/Function.hpp"

#include <atomic>
#include <mutex>

namespace pipc
{
namespace pub_sub
{
/**
 * @brief PublisherPtmpLayer for all publishers.
 *
 * Contains the following type-independent elements:
 * - Subscription handling
 * - The subscriber bitmask
 * - State management of the Publisher
 * - Base functions for sending data of type T
 *
 * @todo
 * processNotification needs to be implemented (unsubscribe upon disconnect).
 */
class PublisherPtmpLayer : public protocol::DefaultLayer
{
public:
    using PayloadRx = SubscriberMsg;

    /** @brief Default constructor. */
    PublisherPtmpLayer() : lock_(), activeSubscribers_(0)
    {
    }

    /**
     * @brief Activate a subscriber.
     *
     * @return True if there were no active subscribers before activating one.
     */
    inline bool activateSubscriber(size_t idx)
    {
        auto activeSubscribers = activeSubscribers_;
        activeSubscribers_     = (activeSubscribers | (1UL << idx));
        // There was no active subscribers, but one was activated
        return activeSubscribers == 0UL;
    }

    /**
     * @brief Deactivate a subscriber.
     *
     * @return True if the last subscriber was deactivated.
     */
    inline bool deactivateSubscriber(size_t idx)
    {
        auto activeSubscribers = activeSubscribers_;
        activeSubscribers_     = (activeSubscribers & ~(1UL << idx));
        // The last subscriber was deactivated
        return activeSubscribers_ == 0UL;
    }

    /**
     * @brief Function used to check if there are any active subscribers
     */
    bool hasSubscribers()
    {
        return (activeSubscribers_ != 0UL);
    }

    /**
     * @brief Set a callback to be invoked when the publisher has subscribers.
     */
    void setHasSubscribersCallback(const utils::Function<void(bool)>& callback)
    {
        hasSubscribersCallback_ = callback;
    }

    /**
     * @brief Unset the hasSubscribers callback.
     */
    void unsetHasSubscribersCallback()
    {
        hasSubscribersCallback_ = nullptr;
    }

    /**
     * @brief Start the subscription offer of the publisher.
     */
    template<typename TPtmpEndpoint>
    void startOfferSubscription(TPtmpEndpoint& endpoint)
    {
        if (!isOffering_)
        {
            const std::lock_guard<std::mutex> lock(this->lock_);
            PublisherMsg msg;
            msg.emplace<PublisherMsgs::SubscriptionAcknowledge>();
            auto activeSubscribers  = activeSubscribers_;
            protocol::EndpointId id = 0;
            while (activeSubscribers)
            {
                if (activeSubscribers & 1U)
                {
                    auto subscriber = endpoint.get(id);
                    subscriber->send(msg);
                }
                activeSubscribers >>= 1U;
                id = static_cast<protocol::EndpointId>(id + 1U);
            }
            isOffering_ = true;
        }
    }

    /**
     * @brief Stop the subscription offer of the publisher.
     *
     */
    template<typename TPtmpEndpoint>
    void stopOfferSubscription(TPtmpEndpoint& endpoint)
    {
        if (isOffering_)
        {
            const std::lock_guard<std::mutex> lock(this->lock_);
            PublisherMsg msg;
            msg.emplace<PublisherMsgs::UnsubscriptionNotification>();
            auto activeSubscribers  = activeSubscribers_;
            protocol::EndpointId id = 0;
            while (activeSubscribers)
            {
                if (activeSubscribers & 1U)
                {
                    auto subscriber = endpoint.get(id);
                    subscriber->send(msg);
                }
                activeSubscribers >>= 1U;
                id = static_cast<protocol::EndpointId>(id + 1U);
            }
            isOffering_ = false;
        }
    }

    /**
     * We need this method because there are processNotifications with different parameters
     */
    template<size_t NLayer, typename TPtmpEndpoint>
    constexpr void processNotification(TPtmpEndpoint& endpoint, StateChange change)
    {
        protocol::ForwardNotification<NLayer>(endpoint, change);
    }

    /**
     * Process notifications from:
     *  - Provider Endpoint disconnect
     *  - Provider Ptmp Layer received messages
     * If this version of processNotification is called with StateChange::kInvalid, then the subscriber must be
     * deactivated
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
            PIPC_LOG_INFO() << "Deactivate subscriber due to disconnect" << std::endl;
            bool callSubscribersCallback = false;
            {
                const std::lock_guard<std::mutex> lock(this->lock_);
                callSubscribersCallback = deactivateSubscriber(endpoint.idx(subscriber));
            }
            if (hasSubscribersCallback_ && callSubscribersCallback)
            {
                hasSubscribersCallback_(false);
            }
        }

        protocol::ForwardNotification<NLayer>(endpoint, change, subscriber);
    }

    /**
     * @brief Receive a message (from a subscriber).
     */
    template<size_t NLayer,
             typename TMsg,
             size_t NEndpoints,
             typename T0,
             typename T1,
             typename T2,
             typename T3,
             typename T4,
             typename T5,
             typename T6,
             typename T7>
    inline ReturnCode receive(protocol::PtmpEndpoint<NEndpoints, T0, T1, T2, T3, T4, T5, T6, T7>& endpoint,
                              TMsg& pdu,
                              protocol::PtpEndpoint<T0, T1, T2, T3>& subscriber)
    {
        bool callSubscribersCallback = false;
        bool hasSubscribers          = false;
        {
            const std::lock_guard<std::mutex> lock(this->lock_);
            PublisherMsg reply;
            switch (pdu.payload().index())
            {
            case SubscriberMsgs::kSubscriptionIndication:
            {
                if (isOffering_)
                {
                    reply.emplace<PublisherMsgs::SubscriptionAcknowledge>();
                    subscriber.send(reply);
                }
                callSubscribersCallback = activateSubscriber(endpoint.idx(subscriber));
                hasSubscribers          = true;
                break;
            }
            case SubscriberMsgs::kUnsubscriptionIndication:
            {
                reply.emplace<PublisherMsgs::UnsubscriptionAcknowledge>();
                callSubscribersCallback = deactivateSubscriber(endpoint.idx(subscriber));
                hasSubscribers          = false;
                subscriber.send(reply);
                break;
            }
            default:
            {
                PIPC_LOG_ERROR() << "PublisherPtmpLayer: Received invalid subscriber message." << std::endl;
                return ReturnCode::kInvalidSubscriptionMsg;
            }
            }
        }
        // The call should be done out the mutex lock
        if (hasSubscribersCallback_ && callSubscribersCallback)
        {
            hasSubscribersCallback_(hasSubscribers);
        }

        return ReturnCode::kOk;
    }

    /**
     * @brief Send a datagram to the subscribers.
     *
     * @remark
     * Data messages are only sent to subscribers, which are actively subscribed.
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
    inline void sendData(protocol::PtmpEndpoint<NEndpoints, T0, T1, T2, T3, T4, T5, T6, T7>& endpoint, const TMsg& msg)
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
        do
        {
            if (activeSubscribers & 1UL)
            {
                auto ret = subscriber->endpoint.sendDatagram(msg);
                if (EXPECT_UNLIKELY(ret != ReturnCode::kOk))
                {
                    PIPC_LOG_ERROR() << "Error sending to socket: " << (int)ret << std::endl;
                    // exit(1);
                }
            }
            subscriber++;
            activeSubscribers >>= 1UL;
        } while (activeSubscribers != 0UL);
    }

protected:
    /** @brief Lock for accessing the subscriber endpoints. */
    std::mutex lock_;
    /**
     * @brief Callback invoked when the publisher has subscribers.
     *
     * This callback is invoked everytime the no. of subscribers
     * changes from none to some or vice versa.
     */
    utils::Function<void(bool)> hasSubscribersCallback_;
    /**
     * @brief Bitmask with each bit set for an active subscriber.
     */
    uint64_t activeSubscribers_{0};
    /** @brief Flag whether the publisher is currently offering subscription. */
    bool isOffering_{true};
};

} // namespace pub_sub
} // namespace pipc

#endif // PUB_SUB_PUBLISHER_PTMP_LAYER_HPP
