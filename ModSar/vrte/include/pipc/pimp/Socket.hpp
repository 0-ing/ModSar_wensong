/// @copyright : 2022 Robert Bosch GmbH. All rights reserved.
#ifndef PIPC_PIMP_SOCKET_HPP
#define PIPC_PIMP_SOCKET_HPP

#include "Channel.hpp"
#include "Queue.hpp"
#include "TISocket.hpp"
#include "pipc/NodeId.hpp"
#include "pipc/shmem/Mapping.hpp"

#include <mutex>
#include <thread>

namespace pipc
{
/** @brief Forward declaration of listener class. */
namespace transport
{
template<typename TSocket>
class Listener;
}

namespace pimp
{
namespace internal
{
/**
 * @brief Channel configuration for pimp sockets.
 *
 * Sockets based on pimp are configured to use custom queue implementations with
 * E2E protection of queue state and payload.
 *
 * TODO:
 * Combining the PIMP Queues with a simple semaphore mechanism will
 * lead to spurious notification faults due to the Multi Producer nature.
 * Either use a SP queue with a writer lock or accept these situations
 * at the receiver side.
 */
template<size_t MaxPayload, size_t Length>
using Channel = pimp::Channel<Queue<MaxPayload, Length, e2e::E2EProtection::kInverse, e2e::E2EProtection::kInverse>>;

/** @brief List of of the possible socket connection type. */
enum class ConnectionMode
{
    kStraight = 0,
    kCrossover,
    kLoopBack
};

/**
 * @brief Internal overlay structure for a channel pair.
 *
 * The channel pair overlay is used as an aid to find the
 * addresses or tx and rx channels when creating a PIMP
 * socket in shared memory.
 */
template<size_t MaxPayload, size_t Length>
struct ChannelPair
{
    Channel<MaxPayload, Length> ch0;
    Channel<MaxPayload, Length> ch1;
};

/**
 * @brief Socket class for setting up a duplex connection.
 *
 * A PIMP socket consists of a pair of queues, one for sending
 * and one for receiving data. It is accessible via a path in shared memory.
 * Additionally a socket contains the information which node is available at
 * the other side of it, given through its node Id.
 */
template<size_t MaxPayLoad, size_t Length>
class Socket
{
    template<typename TSocket>
    friend class transport::Listener;
    using TChannel     = Channel<MaxPayLoad, Length>;
    using TChannelPair = ChannelPair<MaxPayLoad, Length>;

public:
    /** @brief Storage for a slot with unknown content. */
    using SlotStorage = typename TChannel::Queue::SlotStorage;

    /** @brief We adhere to the TISocket interface. */
    constexpr operator TISocket<Socket>&()
    {
        return *reinterpret_cast<TISocket<Socket>*>(this);
    }

    /** @brief Get the underlying file descriptor. */
    int getFd()
    {
        return mapping_.getFd();
    }

    /** @brief Get the name of the socket. */
    utils::String getName() const
    {
        return mapping_.getName();
    }

    /** @brief Get the id of the node on the other side. */
    inline NodeId getNodeId() const
    {
        return nodeId_;
    }

    /** @brief Get the connection mode. */
    inline ConnectionMode getConnectionMode() const
    {
        return connectionMode_;
    }

    /**
     * @brief Create a socket.
     *
     * Creates a mem-mapped file with the given name and constructs a
     * Socket into the mapped memory.
     *
     * @param name The name of the socket, used as path in shared memory.
     * @param mode The access permissions for the socket.
     * @param nodeId Id for the node on the other side of the socket.
     */
    inline ReturnVal create(const char* name, mode_t mode = 0600, NodeId nodeId = 0) noexcept
    {
        auto err = mapping_.create(name, mode, sizeof(TChannelPair));
        if (err == 0)
        {
            TChannelPair* tmp = new (mapping_.get()) TChannelPair;
            tx_               = &tmp->ch0;
            rx_               = &tmp->ch1;
            nodeId_           = nodeId;
            return ReturnVal::kOk;
        }
        else
        {
            return ReturnVal::kGeneralError;
        }
    }

    /**
     * @brief Connect to a socket.
     *
     * Opens a mem-mapped file with the given name and connects to the
     * socket's channels.
     * @param name The name of the socket, used as path in shared memory.
     * @param connectionMode Info whether to connect in cross-over mode or not.
     * @param nodeId Id for the node on the other side of the socket.
     *
     * If connectionMode is false, the channels will be connected vice-versa to the TODO
     * create call. If connectionMode is true, the order is the same as the create
     * call.
     */
    inline ReturnVal connect(const char* name,
                             ConnectionMode connectionMode = ConnectionMode::kStraight,
                             NodeId nodeId                 = 0) noexcept
    {
        auto err = mapping_.open(name, sizeof(TChannelPair));
        if (err == 0)
        {
            auto* tmp = reinterpret_cast<TChannelPair*>(mapping_.get());
            switch (connectionMode)
            {
            case ConnectionMode::kStraight:
            {
                tx_ = &tmp->ch1;
                rx_ = &tmp->ch0;
                break;
            }
            case ConnectionMode::kCrossover:
            {
                tx_ = &tmp->ch0;
                rx_ = &tmp->ch1;
                break;
            }
            case ConnectionMode::kLoopBack:
            {
                tx_ = &tmp->ch0;
                rx_ = &tmp->ch0;
                break;
            }
            default:
            {
                return ReturnVal::kGeneralError;
            }
            }

            connectionMode_ = connectionMode;
            nodeId_         = nodeId;
            return ReturnVal::kOk;
        }
        else
        {
            return ReturnVal::kGeneralError;
        }
    }

    /**
     * @brief Connect to a socket via loop_back.
     *
     * Connects to the an existing socket's channels vice-versa without
     * creating a new mapping to it.
     */
    inline ReturnVal loop_back(Socket& socket)
    {
        auto* tmp = reinterpret_cast<TChannelPair*>(socket.mapping_.get());
        tx_       = &tmp->ch1;
        rx_       = &tmp->ch0;
        return ReturnVal::kOk;
    }

    void close()
    {
        mapping_.close();
    }

    /** @brief Send a message over the socket. */
    template<typename T>
    inline ReturnVal send(const T& val)
    {
        return send_emplace<T>(val);
    }

    /** @brief Send function with in-place construction into the queue. */
    template<typename T, typename... Args>
    inline ReturnVal send_emplace(Args&&... args)
    {
        // With this lock we avoid that another thread completes a follow-up send and notifies the receiver while we have not
        // finished the emplace. 
        std::lock_guard<std::mutex> lock(sendNotificationMutex_);
        auto ret = tx_->queue.template try_emplace<T>(std::forward<Args&&>(args)...);
        if (ret == ReturnVal::kOk)
        {
            tx_->signal.post();
        }
        return ret;
    }

    /**
     * @brief Send a message over without notification.
     *
     * @remark For benchmarks only.
     */
    template<typename T>
    inline ReturnVal send_no_notify(const T& val)
    {
        return send_emplace_no_notify<T>(val);
    }

    /**
     * @brief Send_emplace without notifiaction.
     *
     * @remark For benchmarks only.
     */
    template<typename T, typename... Args>
    inline ReturnVal send_emplace_no_notify(Args&&... args)
    {
        auto ret = tx_->queue.template try_emplace<T>(std::forward<Args&&>(args)...);
        if (ret == ReturnVal::kOk)
        {
        }
        else
        {
            std::cout << "Error during socket send: " << (int)ret << std::endl;
        }
        return ret;
    }

    /**
     * @brief Method to try to receive from a socket (non-blocking).
     */
    template<typename T>
    inline ReturnVal try_receive(T& val)
    {
        return rx_->queue.try_pop(val);
    }

    /** @brief Try to peek into the receive queue. */
    template<typename T>
    inline ReturnVal try_peek(T*& val)
    {
        return rx_->queue.template try_peek<T>(val);
    }

    /** @brief Pop from the receive queue without looking at the data again. */
    inline ReturnVal try_pop()
    {
        return rx_->queue.try_pop();
    }

    /**
     * @brief Wait for a signal on the receive channel.
     */
    inline void wait()
    {
        rx_->signal.wait();
    }

    inline void notify_self()
    {
        rx_->signal.post();
    }

    /** @brief Check which type of payload protection is configured for the socket. */
    static constexpr e2e::E2EProtection GetPayloadProtection()
    {
        return TChannel::Queue::GetPayloadProtection();
    }

private:
    /** @brief The underlying shmem mapping. */
    shmem::Mapping mapping_;
    /** @brief Channel for sending messages. */
    TChannel* tx_;
    /** @brief Mutex to make the send+notification operation atomic regarding other send+notification operations. */
    std::mutex sendNotificationMutex_;
    /** @brief Channel for receiving messages. */
    TChannel* rx_;
    /** @brief The id of the node on the other side of the socket. */
    NodeId nodeId_;
    /** @brief Mode of the connection*/
    ConnectionMode connectionMode_{ConnectionMode::kStraight};
};

} // namespace internal

/** @brief Default Socket used for apps. */
using Socket         = internal::Socket<PIPC_PIMP_APP_MAX_PAYLOAD_SIZE, PIPC_PIMP_APP_QUEUE_SIZE>;
using ConnectionMode = internal::ConnectionMode;

} // namespace pimp
} // namespace pipc

#endif // PIPC_PIMP_SOCKET_HPP
