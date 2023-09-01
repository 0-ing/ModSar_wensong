#ifndef PIMP_PTP_LAYER_HPP
#define PIMP_PTP_LAYER_HPP

#include "pipc/Logger.hpp"
#include "pipc/protocol/DefaultLayer.hpp"
#include "pipc/protocol/Protocol.hpp"
// #include "Socket.hpp"

namespace pipc
{
namespace pimp
{
/**
 * @brief Network PTP layer.
 *
 * Encapsulates the socket we want to send to.
 * The network layer is the lowest layer we have, it also needs to provide
 * a send method.
 */
class PtpLayer : public protocol::DefaultLayer
{
public:
    /** @brief Equal operator. */
    inline bool operator==(const PtpLayer& other) const
    {
        return socket_ == other.socket_;
    }

    /** @brief Retrieve the current socket. */
    Socket* getSocket() const
    {
        return socket_;
    }

    /** @brief Send a message. */
    template<typename T>
    ReturnCode send(const T& msg)
    {
        // std::cout << "Sending something to socket " << socket_ << " (size " << sizeof(T) << ")" << std::endl;
        // TODO: Change ReturnVal to ReturnCode
        auto ret = socket_->send(msg);
        if (ret != ReturnVal::kOk)
        {
            // PIPC_LOG_ERROR() << "pimp::PtpLayer: Error sending to socket" << std::endl;
            return ReturnCode::kNetworkError;
        }
        return ReturnCode::kOk;
    }

    /** @brief Initialize the socket. */
    void init(Socket& socket)
    {
        socket_ = &socket;
    }

    /**
     * @brief Receive a message.
     */
    template<size_t NLayer, typename TMsg, typename T0, typename T1, typename T2, typename T3, typename... TArgs>
    inline ReturnCode receive(PtpEndpoint<T0, T1, T2, T3>& endpoint, TMsg& msg, Socket& socket, TArgs&&... args)
    {
        // Fast path: Assume the socket is as expected; consume it and pass on.
        if (&socket == socket_)
        {
            return protocol::Forward<NLayer>(endpoint, msg, std::forward<TArgs>(args)...);
        }
        else
        {
            return ReturnCode::kNetworkError;
        }
    }

private:
    /** @brief Pointer to the socket, where messages get sent through. */
    Socket* socket_;
};

} // namespace pimp
} // namespace pipc

#endif // PIMP_PTP_LAYER_HPP
