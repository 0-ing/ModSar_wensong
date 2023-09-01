#ifndef SESSION_PROVIDER_MSG_HPP
#define SESSION_PROVIDER_MSG_HPP

#include "SessionId.hpp"
#include "pipc/utils/TrivialVariant.hpp"

namespace pipc
{
namespace session
{
/** @brief The types of messages a user can send. */
namespace ProviderMsgs
{
/** @brief Acknowledge a connection request. */
struct ConnectionAcknowledge
{
    /** @brief I heard rust doesn't need this boilerplate. */
    ConnectionAcknowledge() = default;

    /** @brief I heard rust doesn't need this boilerplate. */
    ConnectionAcknowledge(SessionId sessionId) : sessionId(sessionId)
    {
    }

    SessionId sessionId;
};

/** @brief Deny a connection request. */
struct ConnectionDeny
{
};

enum Type
{
    kConnectionAcknowledge,
    kConnectionDeny
};
using Container = utils::TrivialVariant<ConnectionAcknowledge, ConnectionDeny>;
} // namespace ProviderMsgs

using ProviderMsg = ProviderMsgs::Container;

} // namespace session
} // namespace pipc

#endif // SESSION_PROVIDER_MSG_HPP
