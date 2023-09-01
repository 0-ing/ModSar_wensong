/// @copyright : 2022 Robert Bosch GmbH. All rights reserved.
#ifndef PIPC_PUB_SUB_SUBSCRIPTION_STATE
#define PIPC_PUB_SUB_SUBSCRIPTION_STATE

#include <stdint.h>

namespace pipc
{
namespace pub_sub
{
/**
 * @brief Subscription state of a subscriber.
 *
 * This is the "public" state of the subscriber, as seen from outside.
 */
enum class SubscriberPublicState : uint8_t
{
    /** @brief Subscribed with publisher's confirmation. */
    kSubscribed,
    /** @brief Unsubscribed with publisher's confirmation. */
    kNotSubscribed,
    /** @brief Subscription requested, waiting for publisher's response. */
    kSubscriptionPending
};

} // namespace pub_sub
} // namespace pipc

#endif // PIPC_PUB_SUB_SUBSCRIPTION_STATE
