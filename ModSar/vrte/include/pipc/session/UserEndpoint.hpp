/// @copyright : 2022 Robert Bosch GmbH. All rights reserved.

#ifndef PIPC_SESSION_USER_ENDPOINT_HPP
#define PIPC_SESSION_USER_ENDPOINT_HPP

#include "UserPtpLayer.hpp"
#include "pipc/pimp/PtpLayer.hpp"
#include "pipc/protocol/DefaultLayer.hpp"
#include "pipc/protocol/Layer.hpp"
#include "pipc/protocol/Message.hpp"
#include "pipc/protocol/Protocol.hpp"
#include "pipc/protocol/PtpEndpoint.hpp"
#include "pipc/transport/PtpLayer.hpp"

namespace pipc
{
namespace session
{
/**
 * @brief An endpoint definition for a session user.
 *
 * This endpoint specializes a generic endpoint to fit to the requirements of a
 * session user. All layers except the app layer are pre-configured,
 * also this endpoint provides APIs for managing the user's connection.
 */

template<typename TAppLayer = protocol::DefaultLayer>
class UserEndpoint : public protocol::PtpEndpoint<pimp::PtpLayer, transport::PtpLayer, UserPtpLayer, TAppLayer>
{
    using BaseClass        = protocol::PtpEndpoint<pimp::PtpLayer, transport::PtpLayer, UserPtpLayer, TAppLayer>;
    using LayerType        = protocol::LayerType;
    using LayerState       = protocol::LayerState;
    using LayerStateChange = protocol::LayerStateChange;

public:
    using BaseClass::BaseClass;
    using NetworkLayer   = pimp::PtpLayer;
    using TransportLayer = transport::PtpLayer;
    using SessionLayer   = UserPtpLayer;
    using AppLayer       = TAppLayer;

    /**
     * @brief Destructor.
     *
     * The destructor calls the destructor callback of the session layer,
     * which automatically sends a disconnect notification if a session is active.
     */
    ~UserEndpoint()
    {
        this->template getLayer<LayerType::kSession>().template destroy<LayerType::kSession>(*this);
    }

    /**
     * @brief Function to set the provider info.
     */
    void init(pimp::Socket& socket, transport::Port port)
    {
        this->template getLayer<protocol::kNetwork>().init(socket);
        this->template getLayer<protocol::kTransport>().setDstPort(port);
        protocol::ForwardNotification<protocol::kTransport>(*this, LayerStateChange::kValid);
    }

    /** @brief Wrapper to receive a msg. */
    static void Receive(UserEndpoint& obj, pimp::Socket& socket, protocol::Placeholder* msg)
    {
        obj.receive(*msg, socket);
    }

    /** @brief Try to connect to the provider. */
    ReturnCode requestConnection()
    {
        return this->template getLayer<LayerType::kSession>().template requestActivation<LayerType::kSession>(*this);
    }

    /** @brief Get the current connection state. */
    LayerState getConnectionState()
    {
        return this->template getLayer<LayerType::kSession>().template getState();
    }
};

} // namespace session
} // namespace pipc

#endif // PIPC_SESSION_USER_ENDPOINT_HPP
