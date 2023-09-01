/// @copyright : 2022 Robert Bosch GmbH. All rights reserved.

#ifndef PIPC_RPC_CLIENT_PTP_LAYER_HPP
#define PIPC_RPC_CLIENT_PTP_LAYER_HPP

#include "pipc/Logger.hpp"
#include "pipc/protocol/DefaultLayer.hpp"
#include "pipc/utils/Function.hpp"

namespace pipc
{
namespace rpc
{
/**
 * @brief ClientPtpLayer for all RPC clients.
 *
 * This layer is the app layer for the RPC clients.
 * It is designed to automatically connect to the server.
 */
class ClientPtpLayer : public protocol::DefaultLayer
{
public:
    /** @brief Default Constructor. */
    ClientPtpLayer() : serverOfflineCallback_(), connectionDesired_(true)
    {
    }

    /** @brief Process a state change from the session layer. */
    template<size_t NLayer, typename... TLayers>
    inline void processNotification(PtpEndpoint<TLayers...>& endpoint, StateChange change)
    {
        switch (change)
        {
        // We are connected now
        case StateChange::kValid:
        {
            break;
        }
        // The server has gone offline
        case StateChange::kInvalid:
        {
            if (serverOfflineCallback_)
            {
                serverOfflineCallback_();
            }
            break;
        }
        // We are able to request a connection now
        case StateChange::kIdle:
        {
            if (connectionDesired_)
            {
                // HINT:
                // We don't need to check the return value of requestActivation, as we have just received a notification
                // that we are able to request a connection.
                static_cast<void>(
                    (endpoint.template getLayer<NLayer - 1>().template requestActivation<NLayer - 1>(endpoint)));
            }
            break;
        }
        // HINT: This code is unreachable
        default:
            break;
        }
    }

    /** @brief Register a callback when the server goes offline. */
    void registerServerOfflineCallback(const utils::Function<void()>& cbk)
    {
        serverOfflineCallback_ = cbk;
    }

    /** @brief Set whether we want to request a connection when we can. */
    void setConnectionDesired(bool desire)
    {
        connectionDesired_ = desire;
    }

protected:
    /**
     * @brief Callback which is called, whenever the server is offline.
     *
     * This callback gives the user the opportunity to react to a server
     * going offline. As the user needs to manage pending requests outside
     * of this class, he also needs to take care of cancelling them when
     * appropriate.
     *
     * @todo
     * Use DeferredWriter here? If we don't, replacing the callback during
     * runtime might destroy the function while it is being executed.
     * Otherwise we have to state it must not be changed once registered
     * to be safe.
     */
    utils::Function<void()> serverOfflineCallback_;

    /**
     * @brief Flag to indicate whether we want to request a connection.
     *
     * This flag is used to express the desire of connecting or not
     * if we have the possibilty.
     *
     * @remark
     * This flag is required for destruction of this layer.
     * Upon destruction the user layer sends a notification that it has disconnected,
     * we need to express in the client that we do not want to connect again.
     */
    bool connectionDesired_;
};

} // namespace rpc
} // namespace pipc

#endif // PUB_SUB_SUBSCRIBER_BASE_PTP_LAYER_HPP
