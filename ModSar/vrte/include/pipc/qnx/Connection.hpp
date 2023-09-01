#ifndef NODE_SND_QNX_HPP
#define NODE_SND_QNX_HPP

#include "Message.hpp"
#include "Types.hpp"

#include <stddef.h>
#include <stdint.h>

namespace pipc
{
namespace qnx
{
/** @brief Class for setting up a QNX connection. */
class Connection
{
public:
    /** @brief Constructor via path name. */
    Connection(const char* channelName) : nodeId_(channelName)
    {
    }

    /**
     * @brief Constructor via tuple of pid/chid.
     */
    Connection(pid_t pId, ChannelId chId) : nodeId_(nullptr), pId_(pId), chId_(chId)
    {
    }

    /** @brief Destructor */
    ~Connection();

    /** @brief Connect to the node */
    bool connect();

    /** @brief Disconnect from the node */
    void disconnect();

    /**
     * @brief Send a QNX message of type T over the connection.
     *
     * @return
     * True if the send was successful, false otherwise.
     */
    template<typename T>
    bool send(const Message<T>& msg)
    {
        return send(reinterpret_cast<const void*>(&msg), sizeof(Message<T>));
    }

    /**
     * @brief Send a QNX message of type T over the connection and receive a
     * reply.
     *
     * @return
     * True if the send was successful, false otherwise.
     */
    template<typename T, typename U>
    bool send(const Message<T>& msg, U& reply)
    {
        return send(reinterpret_cast<const void*>(&msg),
                    sizeof(Message<T>),
                    reinterpret_cast<void*>(&reply),
                    sizeof(reply));
    }

private:
    /** @brief Internal send method. */
    bool send(const void* msg, size_t size, void* reply = nullptr, size_t sizeReply = 0);

    /** @brief Id of the node to connect to (if connecting via path). */
    const char* nodeId_;
    /** @brief pid of the node to connect to (if connecting via pid/chid tuple).
     */
    pid_t pId_;
    /** @brief chid of the node to connect to (if connecting via pid/chid tuple).
     */
    ChannelId chId_;
    /** @brief QNX coid required for addressing the right connection */
    int coId_ = -1;
};

} // namespace qnx
} // namespace pipc

#endif // NODE_SND_QNX_HPP
