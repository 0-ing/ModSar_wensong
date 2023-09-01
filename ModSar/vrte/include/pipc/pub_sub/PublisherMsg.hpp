/// @copyright : 2022 Robert Bosch GmbH. All rights reserved.
#ifndef PIPC_PUB_SUB_PUBLISHER_MSG_HPP
#define PIPC_PUB_SUB_PUBLISHER_MSG_HPP

#include "pipc/utils/TrivialVariant.hpp"

namespace pipc
{
namespace pub_sub
{
/** @brief The types of messages a Publisher can send. */
namespace PublisherMsgs
{
/** @brief Inform subscription acknowledge. */
struct SubscriptionAcknowledge
{
};

/** @brief Inform about unsubscription acknowledge. */
struct UnsubscriptionAcknowledge
{
};

/** @brief Inform about a forced unsubscription. */
struct UnsubscriptionNotification
{
};

enum Type
{
    kSubscriptionAcknowledge,
    kUnsubscriptionAcknowledge,
    kUnsubscriptionNotification
};
using Container = utils::TrivialVariant<SubscriptionAcknowledge, UnsubscriptionAcknowledge, UnsubscriptionNotification>;
} // namespace PublisherMsgs

using PublisherMsg = PublisherMsgs::Container;

} // namespace pub_sub
} // namespace pipc

#endif // PIPC_PUB_SUB_PUBLISHER_MSG_HPP
