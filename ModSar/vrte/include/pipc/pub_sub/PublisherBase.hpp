/// @copyright : 2022 Robert Bosch GmbH. All rights reserved.
#ifndef PUB_SUB_PUBLISHER_BASE_HPP
#define PUB_SUB_PUBLISHER_BASE_HPP

#include "PublisherPtmpLayer.hpp"
#include "pipc/Config.hpp"
#include "pipc/rte/Provider.hpp"

namespace pipc
{
namespace pub_sub
{
namespace internal
{
/**
 * @brief PublisherBase for type-independent implementation parts of Publisher.
 *
 * Contains the following type-independent elements:
 * - Subscription handling
 * - The subscriber list
 * - State management of the Publisher
 * - Base functions for sending data of type T
 *
 * The PTMP layer is a template parameter, since the exact handling of
 * subscription requests and sending data messages can vary depending on
 * the publisher implementation.
 *
 * @remark
 * The base class is carefully designed to minimize code duplication and
 * optimize branch prediction:
 * The ReceiveRequest callback with the subscription logic is the same for all
 * publishers, meaning the same function will be registered at the
 * MsgDispatcher.
 *
 * @todo
 * Implement offer/stopOffer.
 */
template<size_t NSubscribers = PIPC_MAX_USERS_PER_PROVIDER, typename TPublisherPtmpLayer = PublisherPtmpLayer>
class PublisherBase : public rte::Provider<NSubscribers, protocol::DefaultLayer, TPublisherPtmpLayer>
{
    static_assert(NSubscribers <= 64U, "Pub/Sub implementation currently supports max. 64 subscribers.");
    using BaseClass = rte::Provider<NSubscribers, protocol::DefaultLayer, TPublisherPtmpLayer>;

public:
    using BaseClass::BaseClass;

    /**
     * @brief Function used to check if there are any active subscribers
     */
    inline bool hasSubscribers()
    {
        return this->getAppLayer().hasSubscribers();
    }

    /**
     * @brief Set a callback to be invoked when the publisher has subscribers.
     */
    inline void setHasSubscribersCallback(const utils::Function<void(bool)>& callback)
    {
        this->getAppLayer().setHasSubscribersCallback(callback);
    }

    /**
     * @brief Unset the hasSubscribers callback.
     */
    inline void unsetHasSubscribersCallback()
    {
        this->getAppLayer().unsetHasSubscribersCallback();
    }

    /**
     * @brief Start offering subscriptions to the publisher.
     *
     * In case the subscription is offered, pending subscription
     * requests will be acknowledged.
     */
    inline void startOfferSubscription()
    {
        this->getAppLayer().startOfferSubscription(this->endpoint_);
    }

    /**
     * @brief Stop offering subscriptions to the publisher.
     *
     * In case the subscription offer is stopped, all active
     * subscriptions will be reset to pending subscriptions.
     */
    inline void stopOfferSubscription()
    {
        this->getAppLayer().stopOfferSubscription(this->endpoint_);
    }
};

} // namespace internal

} // namespace pub_sub
} // namespace pipc

#endif // PUB_SUB_PUBLISHER_BASE_HPP
