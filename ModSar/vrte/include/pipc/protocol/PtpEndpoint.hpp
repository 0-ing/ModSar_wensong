#ifndef PIPC_PROTOCOL_PTP_ENDPOINT_HPP
#define PIPC_PROTOCOL_PTP_ENDPOINT_HPP

//#include "DefaultLayer.hpp"
#include "EndpointBase.hpp"
#include "TIEndpoint.hpp"
#include "pipc/pimp/Socket.hpp"
#include "pipc/session/ProviderId.hpp"
#include "pipc/transport/Port.hpp"

namespace pipc
{
namespace protocol
{
/**
 * @brief A specialization for a Point-to-Point Endpoint.
 *
 * A PTP Endpoint is used for (logical) Point-To-Point connections.
 * It can be used for sending and/or receiving messages.
 *
 * @param TNetworkLayer   The implementation for the network layer.
 * @param TTransportLayer The implementation for the transport layer.
 * @param TSessionLayer   The implementation for the session layer.
 * @param TAppLayer       The implementation for the app layer.
 */
template<typename TNetworkLayer, typename TTransportLayer, typename TSessionLayer, typename TAppLayer>
class PtpEndpoint : public EndpointBase<TNetworkLayer, TTransportLayer, TSessionLayer, TAppLayer>
{
    using ProviderId = session::ProviderId;
    using Port       = transport::Port;
    using Socket     = pimp::Socket;
    using BaseClass  = EndpointBase<TNetworkLayer, TTransportLayer, TSessionLayer, TAppLayer>;

public:
    /** @brief We adhere to the TIEndpoint interface. */
    inline operator TIEndpoint<PtpEndpoint>&()
    {
        return *reinterpret_cast<TIEndpoint<PtpEndpoint>*>(this);
    }

    /** @brief Default constructor. */
    constexpr PtpEndpoint() = default;

    /**
     * @brief Constructor with RAII initialization.
     *
     * @remark
     * Fully defined endpoint with ProviderId.
     */
    inline PtpEndpoint(session::ProviderId providerId, Socket& socket, Port dstPort, Port srcPort = 0)
    {
        init(socket, dstPort, srcPort);
        this->template getLayer<kSession>().init(providerId, LayerState::kIdle);
    }

    /** @brief Constructor with RAII initialization.
     *
     * @remark
     * Dynamic case with unknown endpoint, optional ProviderId, optional
     * SrcPort.
     */
    inline PtpEndpoint(ProviderId providerId, Port srcPort = 0)
    {
        this->template getLayer<kTransport>().setSrcPort(srcPort);
        this->template getLayer<kSession>().init(providerId);
    }

    inline Socket* getSocket() const
    {
        return this->template getLayer<kNetwork>().getSocket();
    }

    /**
     * @brief Set the initial parameters of the endpoint.
     *
     * The first two layers (socket & port) need to be known in order to enable
     * communication.
     */
    void init(Socket& socket, Port dstPort, Port srcPort = 0)
    {
        this->template getLayer<kNetwork>().init(socket);
        this->template getLayer<kTransport>().init(dstPort, srcPort);
    }

    /**
     * @brief Receive a message and optional arguments through the endpoint.
     *
     * @todo
     * Proper support of const for msg.
     */
    template<typename TMsg, typename... TArgs>
    inline ReturnCode receive(TMsg& msg, TArgs&&... args)
    {
        auto& nextLayer = this->template getLayer<kNetwork>();
        using PayloadRx = typename std::decay<decltype(nextLayer)>::type::PayloadRx;
        using TNewMsg   = typename BaseClass::template Message<PayloadRx, kNetwork>;
        auto& pdu       = *reinterpret_cast<TNewMsg*>(&msg);
        return nextLayer.template receive<kNetwork>(*this, pdu, std::forward<TArgs>(args)...);
    }

    /**
     * @brief Receive a message and optional arguments through the endpoint.
     *
     * @todo
     * This variant is used for testing, find out if we can use an rvalue ref without any
     * problems as default case.
     */
    template<typename TMsg, typename... TArgs>
    inline ReturnCode receive(TMsg&& msg, TArgs&&... args)
    {
        auto& nextLayer = this->template getLayer<kNetwork>();
        using PayloadRx = typename std::decay<decltype(nextLayer)>::type::PayloadRx;
        using TNewMsg   = typename BaseClass::template Message<PayloadRx, kNetwork>;
        auto& pdu       = *reinterpret_cast<TNewMsg*>(&msg);
        return nextLayer.template receive<kNetwork>(*this, pdu, std::forward<TArgs>(args)...);
    }
};

} // namespace protocol
} // namespace pipc

#endif // PIPC_PROTOCOL_PTP_ENDPOINT_HPP
