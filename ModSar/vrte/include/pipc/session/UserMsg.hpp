/// @copyright : 2022 Robert Bosch GmbH. All rights reserved.

#ifndef SESSION_USER_MSG_HPP
#define SESSION_USER_MSG_HPP

#include "ProviderId.hpp"
#include "pipc/utils/TrivialVariant.hpp"

namespace pipc
{
namespace session
{
/** @brief The types of messages a user can send. */
namespace UserMsgs
{
/** @brief Request a connection. */
struct ConnectionRequest
{
    /** @brief Boilerplate. */
    ConnectionRequest() = default;

    /** @brief Boilerplate. */
    ConnectionRequest(ProviderId providerId) : providerId(providerId)
    {
    }

    /** @brief Equal operator. */
    inline bool operator==(const ConnectionRequest& other) const
    {
        return providerId == other.providerId;
    }

    ProviderId providerId;
};

/** @brief Notify the provider we want to disconnect. */
struct DisconnectNotification
{
    /** @brief Equal operator. */
    inline bool operator==(const DisconnectNotification&) const
    {
        return true;
    }
};

enum Type
{
    kConnectionRequest,
    kDisconnectNotification
};
using Container = utils::TrivialVariant<ConnectionRequest, DisconnectNotification>;
} // namespace UserMsgs

using UserMsg = UserMsgs::Container;

} // namespace session
} // namespace pipc

#endif // SESSION_USER_MSG_HPP
