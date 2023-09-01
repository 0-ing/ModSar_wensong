#ifndef PROTOTYPES_NODE_RCVR_QNX_HPP
#define PROTOTYPES_NODE_RCVR_QNX_HPP

#include "Message.hpp"

#include <iostream>
#include <sys/dispatch.h>

namespace pipc
{
namespace qnx
{
/**
 * @brief QNX-specific ReplyToken.
 *
 * Required to send a response to an incoming message, the
 * reply token shall have every information for that.
 */
using ReplyToken = int;

/** @brief Class for setting up a QNX channel. */
class Channel
{
public:
    /** @brief Constructor via path name. */
    Channel(const char* name) : name_(name), attach_(), isOpen_(false)
    {
    }

    /** @brief Destructor for closing the channel. */
    ~Channel();

    /** @brief Create the node. */
    void create();

    /** @brief Close the node. */
    void close();

    /**
     * @brief Receive a message and get a reply token.
     *
     * This version returns the message's recvid as replyToken, so the
     * receiver can choose an appropriate reply for the sender.
     * Note that the sender stays blocked until a reply has been sent.
     *
     * @return
     * True if a message has been received, false if the channel is closed.
     *
     * @todo
     * We can make this safer: replyToken can be an object, which checks
     * whether a reply has been sent upon destruction. If no reply has been
     * sent by the user, an empty reply can be sent automatically.
     */
    template<typename T>
    bool receive(Message<T>& msg, struct _msg_info& info, ReplyToken& replyToken)
    {
        return receive(*reinterpret_cast<Message<void>*>(&msg), sizeof(Message<T>), info, &replyToken);
    }

    /**
     * @brief Receive a message without the possiblity to reply.
     *
     * This version for receiving can be used, if the caller does not
     * need to send a reply message.
     *
     * @return
     * True if a message has been received, false if the channel is closed.
     */
    template<typename T>
    bool receive(Message<T>& msg, struct _msg_info& info)
    {
        return receive(*reinterpret_cast<Message<void>*>(&msg), sizeof(Message<T>), info);
    }

    /**
     * @brief Reply to a message.
     *
     * Send a reply to the message identified by the replyToken.
     *
     * @return
     * True if a message has been received, false if the channel is closed.
     */
    template<typename T>
    void reply(const T& msg, ReplyToken replyToken)
    {
        ::MsgReply(replyToken, EOK, reinterpret_cast<const void*>(&msg), sizeof(T));
    }

private:
    /**
     * @brief Receive a message.
     *
     * Blocks on the channel until a new message is received.
     * The caller gets the recvid of the message as replyToken,
     * so a reply can be sent if required.
     *
     * @return
     * True if a message has been received, false if the channel is closed.
     */
    bool receive(Message<void>& msg, size_t size, struct _msg_info& info, ReplyToken* replyToken = nullptr);

    /** @brief The name of the node (for internal reference). */
    const char* name_;
    /** @brief name_attach_t structure from QNX's name_attach call. */
    name_attach_t* attach_;
    /** @brief Info whether the node is currently open or not. */
    bool isOpen_;
};

} // namespace qnx
} // namespace pipc

#endif // PROTOTYPES_NODE_RCVR_QNX_HPP
