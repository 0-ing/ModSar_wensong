/// @copyright : 2022 Robert Bosch GmbH. All rights reserved.
#ifndef PUB_SUB_SUBSCRIBER_BASE_PTP_LAYER_HPP
#define PUB_SUB_SUBSCRIBER_BASE_PTP_LAYER_HPP

#include "PublisherMsg.hpp"
#include "SubscriberInternalState.hpp"
#include "SubscriberMsg.hpp"
#include "SubscriberPublicState.hpp"
#include "pipc/Logger.hpp"
#include "pipc/protocol/DefaultLayer.hpp"
#include "pipc/utils/DeferredWriter.hpp"
#include "pipc/utils/Function.hpp"

#include <mutex>

namespace pipc
{
namespace pub_sub
{
/**
 * @brief SubscriberPtpLayer for all subscribers.
 *
 * This layer is the app layer for pub_sub component subscriber part.
 *
 * @todo
 * Do we call subscriptionStateChangeHandler only upon receiving notifications and
 * messages, or also in requestActivation and requestDeactivation?
 *
 * @todo
 * Reconsider thread-safe handling in the layers altogether. It might make more sense to wrap the
 * endpoint's receive function into a mutex and add processNotification in endpoint,
 * which locks the same mutex (for notifications coming from the runtime).
 */
class SubscriberPtpLayer : public protocol::DefaultLayer
{
public:
    using PayloadRx = PublisherMsg;

    /** @brief Default Constructor. */
    SubscriberPtpLayer()
        : mutex_(), state_(SubscriberInternalState::kInvalid), subscriptionState_(SubscriberPublicState::kNotSubscribed)
    {
    }

    /**
     * @brief Initialize the layer.
     */
    void init()
    {
        state_             = SubscriberInternalState::kInvalid;
        subscriptionState_ = SubscriberPublicState::kNotSubscribed;
    }

    /** @brief Get the internal state. */
    SubscriberInternalState getState()
    {
        return state_;
    };

    /** @brief Get the public subcription state. */
    inline SubscriberPublicState getSubscriptionState() const
    {
        return subscriptionState_;
    }

    /** @brief Process a state change from the session layer. */
    template<size_t N, typename... TLayers>
    inline void processNotification(PtpEndpoint<TLayers...>& endpoint, StateChange change)
    {
        const std::lock_guard<std::mutex> lock(mutex_);
        PIPC_LOG_DEBUG() << "SubscriberPtpLayer: Received notification " << protocol::ToString(change) << std::endl;
        // We were not connected yet
        if (state_ == SubscriberInternalState::kInvalid)
        {
            // We are able to request a connection now
            if (change == StateChange::kIdle)
            {
                // Check if we want to subscribe, in that case trigger an
                // immediate connection request
                if (subscriptionState_ == SubscriberPublicState::kSubscriptionPending)
                {
                    PIPC_LOG_DEBUG() << "SubscriberPtpLayer: Requesting connection" << std::endl;
                    static_cast<void>(endpoint.template getLayer<N - 1>().template requestActivation<N - 1>(endpoint));
                }
            }
            // We are are successfully connected
            else if (change == StateChange::kValid)
            {
                state_ = SubscriberInternalState::kNotSubscribed;
                if (subscriptionState_ == SubscriberPublicState::kSubscriptionPending)
                {
                    PIPC_LOG_DEBUG() << "SubscriberPtpLayer: Sending subscription request" << std::endl;
                    Message<SubscriberMsg, N, TLayers...> pdu;
                    pdu.payload().template emplace<SubscriberMsgs::SubscriptionIndication>();
                    state_             = SubscriberInternalState::kSubscriptionPending;
                    subscriptionState_ = SubscriberPublicState::kSubscriptionPending;
                    endpoint.send(pdu);
                }
            }
        }
        // We were connected and possibly also subscribed
        else
        {
            if (change == StateChange::kInvalid)
            {
                state_ = SubscriberInternalState::kInvalid;
                if (subscriptionState_ == SubscriberPublicState::kSubscribed)
                {
                    PIPC_LOG_DEBUG() << "SubscriberPtpLayer: Switching to subscription pending" << std::endl;
                    subscriptionState_ = SubscriberPublicState::kSubscriptionPending;
                    auto& handler      = subscriptionStateChangeHandler_.read();
                    if (handler)
                    {
                        handler(subscriptionState_);
                    }
                }
            }
            else
            {
                PIPC_LOG_ERROR() << "SubscriberPtpLayer: Unexpected ConnectionIdle notification while already connected"
                                 << std::endl;
            }
        }
    }

    /** @brief Subscribe to the publisher. */
    template<size_t N, typename... TLayers>
    ReturnCode requestActivation(PtpEndpoint<TLayers...>& endpoint)
    {
        const std::lock_guard<std::mutex> lock(mutex_);
        switch (state_)
        {
        case SubscriberInternalState::kSubscribed:
        case SubscriberInternalState::kSubscriptionPending:
        {
            return ReturnCode::kOk;
        }
        case SubscriberInternalState::kNotSubscribed:
        case SubscriberInternalState::kUnsubscriptionPending:
        {
            PIPC_LOG_DEBUG() << "SubscriberPtpLayer: Sending subscription request" << std::endl;
            Message<SubscriberMsg, N, TLayers...> pdu;
            pdu.payload().template emplace<SubscriberMsgs::SubscriptionIndication>();
            state_             = SubscriberInternalState::kSubscriptionPending;
            subscriptionState_ = SubscriberPublicState::kSubscriptionPending;
            endpoint.send(pdu);
            return ReturnCode::kOk;
        }
        case SubscriberInternalState::kInvalid:
        default:
        {
            // Even if we aren't permitted to connect, we are officially pending
            subscriptionState_ = SubscriberPublicState::kSubscriptionPending;
            // Try to initiate a connection now
            return (endpoint.template getLayer<N - 1>().template requestActivation<N - 1>(endpoint));
        }
        }
    }

    /** @brief Unsubscribe from the publisher. */
    template<size_t N, typename... TLayers>
    ReturnCode requestDeactivation(PtpEndpoint<TLayers...>& endpoint)
    {
        const std::lock_guard<std::mutex> lock(mutex_);
        switch (state_)
        {
        case SubscriberInternalState::kSubscribed:
        case SubscriberInternalState::kSubscriptionPending:
        {
            Message<SubscriberMsg, N, TLayers...> pdu;
            pdu.payload().template emplace<SubscriberMsgs::UnsubscriptionIndication>();
            state_             = SubscriberInternalState::kUnsubscriptionPending;
            subscriptionState_ = SubscriberPublicState::kNotSubscribed;
            endpoint.send(pdu);
            return ReturnCode::kOk;
        }
        case SubscriberInternalState::kNotSubscribed:
        case SubscriberInternalState::kUnsubscriptionPending:
        {
            return ReturnCode::kOk;
        }
        case SubscriberInternalState::kInvalid:
        default:
        {
            // Even if we aren't permitted to connect, we are officially pending
            subscriptionState_ = SubscriberPublicState::kNotSubscribed;
            return ReturnCode::kOk;
        }
        }
    }

    /** @brief Receive a message (from the publisher). */
    template<size_t NLayer, typename... TLayers>
    inline ReturnCode receive(PtpEndpoint<TLayers...>&, Message<PayloadRx, NLayer, TLayers...>& pdu)
    {
        const std::lock_guard<std::mutex> lock(mutex_);
        auto oldState              = subscriptionState_;
        bool msgUnderstood         = false;
        PublisherMsg& publisherMsg = pdu.payload();
        if (state_ == SubscriberInternalState::kSubscriptionPending)
        {
            if (publisherMsg.index() == PublisherMsgs::kSubscriptionAcknowledge)
            {
                msgUnderstood      = true;
                state_             = SubscriberInternalState::kSubscribed;
                subscriptionState_ = SubscriberPublicState::kSubscribed;
            }
        }
        else if (state_ == SubscriberInternalState::kUnsubscriptionPending)
        {
            if (publisherMsg.index() == PublisherMsgs::kUnsubscriptionAcknowledge)
            {
                msgUnderstood = true;
                state_        = SubscriberInternalState::kNotSubscribed;
            }
        }
        else if (state_ == SubscriberInternalState::kSubscribed)
        {
            if (publisherMsg.index() == PublisherMsgs::kUnsubscriptionNotification)
            {
                msgUnderstood = true;
                state_ = SubscriberInternalState::kSubscriptionPending;
                subscriptionState_ = SubscriberPublicState::kSubscriptionPending;
            }
        }

        if (oldState != subscriptionState_)
        {
            auto& handler = subscriptionStateChangeHandler_.read();
            if (handler)
            {
                handler(subscriptionState_);
            }
        }

        if (!msgUnderstood)
        {
            PIPC_LOG_ERROR() << "SubscriberPtpLayer: Couldn't understand publisher message." << std::endl;
            return ReturnCode::kAppError;
        }

        return ReturnCode::kOk;
    }

    /** @brief Set a subscription state change handler. */
    void setSubscriptionStateChangeHandler(utils::Function<void(SubscriberPublicState)> handler)
    {
        subscriptionStateChangeHandler_.write(handler);
    }

    /** @brief Get the event receive handler. */
    inline auto& getEventReceiveHandler()
    {
        return eventReceiveHandler_;
    }

    /** @brief Set an event receive handler. */
    void setEventReceiveHandler(utils::Function<void()> handler)
    {
        eventReceiveHandler_.write(handler);
    }

protected:
    /** @brief Subscription state change handler. */
    utils::DeferredWriter<utils::Function<void(SubscriberPublicState)>> subscriptionStateChangeHandler_;
    /** @brief Event receive handler. */
    utils::DeferredWriter<utils::Function<void()>> eventReceiveHandler_;
    /** @brief Mutex for accessing the subscription states. */
    std::mutex mutex_;
    /**
     * @brief Current state of this layer.
     *
     * @todo
     * Needs to be atomic, need to check transient states between requesting
     * changes and getting responses.
     */
    volatile SubscriberInternalState state_;
    /**
     * @brief Subscription state.
     *
     * @remark
     * Volatile because the state is changed by the middleware in the subscriber's
     * thread. The user can poll on the subscription state this way.
     *
     * @todo
     * Needs to be atomic, need to check transient states between requesting
     * changes and getting responses.
     */
    volatile SubscriberPublicState subscriptionState_;
};

} // namespace pub_sub
} // namespace pipc

#endif // PUB_SUB_SUBSCRIBER_BASE_PTP_LAYER_HPP
