#ifndef PIPC_RTE_IAPP_HPP
#define PIPC_RTE_IAPP_HPP

#include "pipc/pimp/Socket.hpp"
#include "pipc/protocol/Layer.hpp"
#include "pipc/session/ProviderId.hpp"
#include "pipc/transport/Port.hpp"

namespace pipc
{
namespace rte
{
/**
 * @brief Interface for a PIPC app.
 *
 * This interface provides an API to control service providers & users from outside,
 * for example via a runtime. This way the runtime can forward availability information
 * about providers and sockets.
 */
class IApp
{
protected:
    IApp() = default;

public:
    using ProviderId = session::ProviderId;
    using Socket     = pimp::Socket;
    using Port       = transport::Port;
    using LayerState = protocol::LayerState;

    /** @brief Get the ProviderId associated with the app. */
    virtual const ProviderId& getProviderId() = 0;

    /** @brief Get the port. */
    virtual Port getPort() const = 0;

    /** @brief Get the segment size. */
    virtual uint32_t getSegmentSize() const
    {
        return 0;
    }

    /** @brief Check if the App is a Provider or a User. */
    virtual bool isProvider() = 0;

    /** @brief Initialize an app. */
    virtual void init(bool standalone = false) = 0;

    /** @brief Inform the app that a Provider has become available. */
    virtual void notifyProviderOnline(Socket& socket, Port port) = 0;

    /** @brief Inform the app that a Provider has become unavailable. */
    virtual void notifyProviderOffline() = 0;

    /** @brief Inform the app that a socket has become unavailable. */
    virtual void notifySocketOffline(Socket& socket) = 0;
};

} // namespace rte
} // namespace pipc

#endif // PIPC_RTE_IAPP_HPP
