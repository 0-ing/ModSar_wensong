/// @copyright : 2022 Robert Bosch GmbH. All rights reserved

#ifndef TRANSPORT_MAILBOX_HPP
#define TRANSPORT_MAILBOX_HPP

#include "Message.hpp"
#include "pipc/Config.hpp"
#include "pipc/queue/SpScQueue.hpp"

namespace pipc
{
namespace transport
{
/**
 * @brief MsgTransceiver for sending and receiving data of type T.
 *
 * TODO:
 * Do we need a separate mailbox class?
 * The queue type should be selectable here, then this makes sense.
 */
template<typename T, size_t MaxMsgs = PIPC_MAX_CONCURRENT_SUBSCRIBER_MSGS>
struct Mailbox
{
    constexpr static size_t Size()
    {
        return MaxMsgs;
    }
    /** @brief Queue for storing received messages. */
    SpScQueue<T, PIPC_MAX_CONCURRENT_SUBSCRIBER_MSGS> msgs_;
};

} // namespace transport
} // namespace pipc

#endif // TRANSPORT_MAILBOX_HPP
