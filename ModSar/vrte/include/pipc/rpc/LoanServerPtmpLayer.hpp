/// @copyright : 2022 Robert Bosch GmbH. All rights reserved.

#ifndef PIPC_RPC_LOAN_SERVER_PTMP_LAYER_HPP
#define PIPC_RPC_LOAN_SERVER_PTMP_LAYER_HPP

#include "ServerPtmpLayer.hpp"
#include "pipc/Logger.hpp"
#include "pipc/protocol/Layer.hpp"

#include <cstddef>

namespace pipc
{
namespace rpc
{
/**
 * @brief Ptmp Layer for a LoanServer.
 *
 * Incoming notification to the server's endpoint are checked by this layer
 * If a client reported StateChange::kInvalid (disconnected) this layer
 * invalidates the pending requests of that client
 */
class LoanServerPtmpLayer : public ServerPtmpLayer
{
public:
    /**
     * We need this method because there are processNotifications with different parameters.
     *
     * @todo
     * This method is already available in ServerPtmpLayer, but doesn't get found.
     */
    template<size_t NLayer, typename TPtmpEndpoint>
    constexpr void processNotification(TPtmpEndpoint& endpoint, StateChange change)
    {
        protocol::ForwardNotification<NLayer>(endpoint, change);
    }

    /**
     * @brief Process notifications from:
     *  - Provider Endpoint disconnect
     *  - Provider Ptmp Layer received messages
     * If this version of processNotification is called with StateChange::kInvalid, then the client must be disconnected
     */
    template<size_t NLayer,
             size_t NEndpoints,
             typename T0,
             typename T1,
             typename T2,
             typename T3,
             typename T4,
             typename T5,
             typename T6,
             typename T7>
    inline void processNotification(protocol::PtmpEndpoint<NEndpoints, T0, T1, T2, T3, T4, T5, T6, T7>& endpoint,
                                            StateChange change,
                                            protocol::PtpEndpoint<T0, T1, T2, T3>& client)
    {
        // Connect notification
        if (change == StateChange::kValid)
        {
            const session::ProviderId& providerId = endpoint.template getLayer<protocol::kSession>().getProviderId();
            auto nodeId                           = client.getSocket()->getNodeId();
            auto port                             = client.template getLayer<protocol::kTransport>().getDstPort();
            auto path                             = providerId.toString(nodeId, port);
            client.template getLayer<protocol::kApp>().getDebitor().init(path, stride_);
            auto success = client.template getLayer<protocol::kApp>().getDebitor().openSampleStorage();
            if (!success)
            {
                PIPC_LOG_ERROR() << "LoanServerPtmpLayer: Could not open sample storage" << std::endl;
                // TODO: Deny the connection request if the sample storage cannot be opened?
            }
        }
        // disconnect notification
        else if (change == StateChange::kInvalid)
        {
            PIPC_LOG_DEBUG() << "Received disconnect notification from RPC Client " << std::endl;
            cmdOnDisconnect_(endpoint.idx(client));
        }
    }

    /** @brief set stride size.*/
    void setStride(size_t stride)
    {
        stride_ = stride;
    }

protected:
    /** @brief stride size of the debitor.*/
    size_t stride_;
};

} // namespace rpc
} // namespace pipc

#endif // PIPC_RPC_LOAN_SERVER_PTMP_LAYER_HPP
