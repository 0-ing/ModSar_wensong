/// @copyright : 2022 Robert Bosch GmbH. All rights reserved.

#ifndef PIPC_SESSION_PROVIDER_ENDPOINT_HPP
#define PIPC_SESSION_PROVIDER_ENDPOINT_HPP

#include "ProviderPtmpLayer.hpp"
#include "ProviderPtpLayer.hpp"
#include "pipc/pimp/PtmpLayer.hpp"
#include "pipc/pimp/PtpLayer.hpp"
#include "pipc/protocol/DefaultLayer.hpp"
#include "pipc/protocol/Layer.hpp"
#include "pipc/protocol/PtmpEndpoint.hpp"
#include "pipc/transport/PtmpLayer.hpp"
#include "pipc/transport/PtpLayer.hpp"

namespace pipc
{
namespace session
{
template<size_t NUsers, typename TAppLayer = protocol::DefaultLayer, typename TAppPtmpLayer = protocol::DefaultLayer>
class ProviderEndpoint : public protocol::PtmpEndpoint<NUsers,
                                                       pimp::PtpLayer,
                                                       transport::PtpLayer,
                                                       session::ProviderPtpLayer,
                                                       TAppLayer,
                                                       pimp::PtmpLayer,
                                                       transport::PtmpLayer,
                                                       ProviderPtmpLayer,
                                                       TAppPtmpLayer>
{
    using BaseClass = protocol::PtmpEndpoint<NUsers,
                                             pimp::PtpLayer,
                                             transport::PtpLayer,
                                             session::ProviderPtpLayer,
                                             TAppLayer,
                                             pimp::PtmpLayer,
                                             transport::PtmpLayer,
                                             ProviderPtmpLayer,
                                             TAppPtmpLayer>;
    /** @brief StateChange shortcut. */
    using StateChange = protocol::LayerStateChange;

public:
    using BaseClass::BaseClass;
    using Socket = pimp::Socket;

    /** @brief Constructor with RAII initialization.
     *
     * @remark
     * Dynamic case with unknown endpoint, optional ProviderId, optional
     * SrcPort.
     */
    inline ProviderEndpoint(ProviderId providerId, transport::Port srcPort = 0)
    {
        this->template getLayer<protocol::kTransport>().setSrcPort(srcPort);
        this->template getLayer<protocol::kSession>().init(providerId);
    }

    /**
     * @brief Disconnect all Users related to a socket from the list.
     */
    inline void disconnect(const Socket& socket)
    {
        PIPC_LOG_INFO() << "Disconnecting socket: " << socket.getName() << std::endl;
        for (auto& entry : this->getEndpointEntries())
        {
            if ((entry.valid) && entry.endpoint.getSocket() == &socket)
            {
                protocol::ForwardNotification<protocol::kSession>(*this, StateChange::kInvalid, entry.endpoint);
                // TODO: Invalidate in a certain order (which one?) and then deallocate the entry
                // We probably want to invalidate the session layer to block answering requests first,
                // and then invalidate the app layer
                this->deallocate(this->idx(entry.endpoint));
            }
        }
    }
};

} // namespace session
} // namespace pipc

#endif // PIPC_SESSION_PROVIDER_ENDPOINT_HPP
