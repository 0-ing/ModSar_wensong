/// @copyright : 2022 Robert Bosch GmbH. All rights reserved.
#ifndef PUB_SUB_SUBSCRIBER_MSG_HPP
#define PUB_SUB_SUBSCRIBER_MSG_HPP

#include "pipc/utils/TrivialVariant.hpp"

namespace pipc
{
namespace pub_sub
{
/** @brief The types of messages a Subscriber can send. */
namespace SubscriberMsgs
{
/** @brief Inform the publisher that we want to subscribe. */
struct SubscriptionIndication
{
};

/** @brief Inform about unsubscription. */
struct UnsubscriptionIndication
{
};

enum Type
{
    kSubscriptionIndication,
    kUnsubscriptionIndication
};
using Container = utils::TrivialVariant<SubscriptionIndication, UnsubscriptionIndication>;
} // namespace SubscriberMsgs

using SubscriberMsg = SubscriberMsgs::Container;

} // namespace pub_sub
} // namespace pipc

#endif // PUB_SUB_SUBSCRIBER_MSG_HPP
