/// @copyright : 2022 Robert Bosch GmbH. All rights reserved.
#ifndef PIPC_PUB_SUB_SUBSCRIBER_STATE
#define PIPC_PUB_SUB_SUBSCRIBER_STATE

#include <stdint.h>

namespace pipc
{
namespace pub_sub
{
/**
 * @brief Subscriber state of a subscriber.
 *
 * This is the "internal" state of the subscriber, the state it is actually in.
 */
enum class SubscriberInternalState : uint8_t
{
    /** @brief Subscribed with publisher's confirmation. */
    kSubscribed,
    /** @brief Subscription pending. */
    kSubscriptionPending,
    /** @brief Unsubscribed with publisher's confirmation. */
    kNotSubscribed,
    /** @brief Unsubscription pending. */
    kUnsubscriptionPending,
    /**
     * @brief Invalid, cannot subscribe (yet).
     *
     * @todo
     * This state is kind of redundant, we could also ask the lower layer for its state
     * (connected / not connected). But currently such a callback is missing
     * in the protocol API and this eliminates the need to introduce it.
     * This state would make sense if we were allowed to connect but not subscribe
     * for some use case, though..
     */
    kInvalid
};

} // namespace pub_sub
} // namespace pipc

#endif // PIPC_PUB_SUB_SUBSCRIBER_STATE
