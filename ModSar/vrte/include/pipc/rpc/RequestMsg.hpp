/// @copyright : 2022 Robert Bosch GmbH. All rights reserved.

#ifndef PIPC_RPC_REQUEST_MSG_HPP
#define PIPC_RPC_REQUEST_MSG_HPP

#include "RequestId.hpp"
#include "pipc/session/SessionId.hpp"

namespace pipc
{
namespace rpc
{
/** @brief A request message sent by the client to the server. */
template<typename T>
struct RequestMsg
{
    /** @brief Equal operator. */
    constexpr bool operator==(const RequestMsg& other) const
    {
        return (requestId == other.requestId && sessionId == other.sessionId && data == other.data);
    }

    /** @brief Request Id to map this reply to its request message. */
    RequestId requestId;
    /** @brief Session Id required to identify the client within the server. */
    session::SessionId sessionId;
    /** @brief The request data. */
    T data;
};

/**
 * @brief A request message sent by the client to the server.
 *
 * Template specialization for a request without data.
 */
template<>
struct RequestMsg<void>
{
    /** @brief Equal operator. */
    constexpr bool operator==(const RequestMsg& other) const
    {
        return (requestId == other.requestId && sessionId == other.sessionId);
    }

    /** @brief Request Id to map this reply to its request message. */
    RequestId requestId;
    /** @brief Session Id required to identify the client within the server. */
    session::SessionId sessionId;
};

} // namespace rpc
} // namespace pipc

#endif // PIPC_RPC_REQUEST_MSG_HPP
