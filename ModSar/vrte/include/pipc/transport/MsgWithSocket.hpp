/// @copyright : 2022 Robert Bosch GmbH. All rights reserved

#ifndef TRANSPORT_MSG_WITH_SOCKET_HPP
#define TRANSPORT_MSG_WITH_SOCKET_HPP

#include "Message.hpp"

namespace pipc
{
namespace transport
{
/** @brief Message and socket that it was sent through. */
template<typename TMsg, typename TSocket>
struct MsgWithSocket
{
    MsgWithSocket() = default;
    inline MsgWithSocket(TSocket& socket, const TMsg& message) noexcept : skt(&socket), msg(message)
    {
    }

    /**
     * @brief Pointer to the socket.
     *
     * @remark
     * The type must be a pointer, since this struct will end up in bounded
     * queues.
     */
    TSocket* skt;
    /** @brief The message. */
    TMsg msg;
};

} // namespace transport
} // namespace pipc

#endif // TRANSPORT_MSG_WITH_SOCKET_HPP
