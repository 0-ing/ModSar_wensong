/// @copyright : 2022 Robert Bosch GmbH. All rights reserved.
#ifndef PUB_SUB_SUBSCRIBER_BASE_HPP
#define PUB_SUB_SUBSCRIBER_BASE_HPP

#include "SubscriberPtpLayer.hpp"
#include "pipc/rte/StandaloneRuntime.hpp"
#include "pipc/rte/User.hpp"
#include "pipc/session/UserEndpoint.hpp"

namespace pipc
{
namespace pub_sub
{
/**
 * @brief SubscriberBase for all subscribers.
 */
template<typename TSubscriberPtpLayer = SubscriberPtpLayer>
class SubscriberBase : public rte::User<TSubscriberPtpLayer>
{
    using BaseClass = rte::User<TSubscriberPtpLayer>;

public:
    using BaseClass::BaseClass;

    /** @brief Get the current subscription state. */
    SubscriberPublicState getSubscriptionState() const
    {
        return this->getAppLayer().getSubscriptionState();
    }

    /** @brief Subscribe to the publisher. */
    void subscribe()
    {
        static_cast<void>(this->getAppLayer().template requestActivation<protocol::kApp>(this->endpoint_));
    }

    /** @brief Unsubscribe from the publisher. */
    void unsubscribe()
    {
        static_cast<void>(this->getAppLayer().template requestDeactivation<protocol::kApp>(this->endpoint_));
    }

    /** @brief Set a subscription state change handler. */
    void setSubscriptionStateChangeHandler(utils::Function<void(SubscriberPublicState)> handler)
    {
        this->getAppLayer().setSubscriptionStateChangeHandler(handler);
    }

    /** @brief Set an event receive handler. */
    void setEventReceiveHandler(utils::Function<void()> handler)
    {
        this->getAppLayer().setEventReceiveHandler(handler);
    }
};

} // namespace pub_sub
} // namespace pipc

#endif // PUB_SUB_SUBSCRIBER_BASE_HPP
