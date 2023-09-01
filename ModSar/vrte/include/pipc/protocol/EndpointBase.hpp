#ifndef PROTOCOL_ENDPOINT_BASE_HPP
#define PROTOCOL_ENDPOINT_BASE_HPP

#include "Message.hpp"
//#include "Protocol.hpp"
#include "Layer.hpp"
#include "TIMessage.hpp"
#include "pipc/ReturnCode.hpp"
#include "pipc/utils/Tuple.hpp"

#include <iostream>
#include <tuple>

namespace pipc
{
namespace protocol
{
namespace internal
{
/**
 * @brief Definition of a Datagram with only 2 layers and specific headers.
 *
 * @todo
 * If we define a datagram like this we cannot insert a network header
 * (currently not used anyway, though).
 *
 * @todo
 * Doesn't belong here, clean up when refactoring the protocol component.
 */
template<typename TPayload, typename TNetworkHeader, typename TTransportHeader>
class Datagram
{
public:
    TTransportHeader& header() const
    {
        return data_.template get<protocol::kTransport>();
    }

    TPayload& payload() const
    {
        return data_.template get<protocol::kTransport + 1>();
    }

private:
    alignas(8) utils::Tuple<TNetworkHeader, TTransportHeader, TPayload> data_;
};

} // namespace internal

/**
 * @brief Base class for an Endpoint with a configurable protocol stack of up to 4 layers.
 *
 * Layers are set from low to high, defining Network, Transport, Session & App.
 * The lowest layer must provide a send function. Layers can be stubbed
 * out by providing a 'DefaultLayer' class as template argument.
 * EndpointBase provides send & receive functions and some
 * helpers.
 *
 * Compared to the OSI's definition of Service Access Points,
 * the Endpoint provides the following methods to layers via the
 * Protocol API:
 * REQ:
 * - For requesting messages to be sent, the layers call the Endpoint's
 *   send function directly
 * - For requesting state changes, the Endpoint is requested explicitly
 *   by an external trigger outside of the layers
 *
 * CONF:
 * - Return codes are handled primarily by the Endpoint
 *
 * IND:
 * - Layers pass on notifications about changes of their state
 *   instead of indications
 *
 * RESP:
 * - Responses to notifications are handled in the layers' implementation
 *
 * @param TNetworkLayer   The implementation for the network layer.
 * @param TTransportLayer The implementation for the transport layer.
 * @param TSessionLayer   The implementation for the session layer.
 * @param TAppLayer       The implementation for the app layer.
 */
template<typename TNetworkLayer, typename TTransportLayer, typename TSessionLayer, typename TAppLayer>
class EndpointBase
{
public:
    /** @brief Short form for messages over this endpoint. */
    template<typename T, size_t NLayer = kApp>
    using Message = Message<T, NLayer, TNetworkLayer, TTransportLayer, TSessionLayer, TAppLayer>;

    template<typename T, size_t NLayer>
    constexpr Message<T, NLayer> createMessage()
    {
        return Message<T, NLayer>{};
    }

    /** @brief Check whether this endpoint is identical to another one up to NLayer. */
    template<size_t NLayer>
    bool isSame(const EndpointBase& other) const
    {
        bool same = true;
        same &= getLayer<kNetwork>() == other.getLayer<kNetwork>();
        if (NLayer >= kTransport)
        {
            same &= getLayer<kTransport>() == other.getLayer<kTransport>();
        }
        if (NLayer >= kSession)
        {
            same &= getLayer<kSession>() == other.getLayer<kSession>();
        }
        if (NLayer >= kApp)
        {
            same &= getLayer<kApp>() == other.getLayer<kApp>();
        }
        return same;
    }

    /**
     * @brief Send a pre-allocated message.
     */
    template<typename T, size_t NLayer>
    ReturnCode send(Message<T, NLayer>& pdu)
    {
        // std::cout << "EndpointBase: Sending pdu..." << std::endl;
        // TODO: Which layers do we check before sending?
        getLayer<kNetwork>().prepare(pdu.template getHeader<kNetwork>());
        if (NLayer > kTransport)
        {
            getLayer<kTransport>().prepare(pdu.template getHeader<kTransport>());
        }
        if (NLayer > kSession)
        {
            getLayer<kSession>().prepare(pdu.template getHeader<kSession>());
        }
        if (NLayer > kApp)
        {
            getLayer<kApp>().prepare(pdu.template getHeader<kApp>());
        }
        return getLayer<kNetwork>().send(pdu);
    }

    /**
     * @brief Send a SDU message of type T through the endpoint.
     * Messages over this api are sent via the control link
     *
     * @param NLayer : The headers to consider for sending (by default all).
     */
    template<typename T, size_t NLayer = kApp>
    ReturnCode send(const T& sdu)
    {
        Message<T, NLayer> pdu;
        // TODO: Which layers do we check before sending?
        getLayer<kNetwork>().prepare(pdu.template getHeader<kNetwork>());
        if (NLayer >= kTransport)
        {
            getLayer<kTransport>().prepare(pdu.template getHeader<kTransport>());
        }
        if (NLayer >= kSession)
        {
            getLayer<kSession>().prepare(pdu.template getHeader<kSession>());
        }
        if (NLayer >= kApp)
        {
            getLayer<kApp>().prepare(pdu.template getHeader<kApp>());
        }
        pdu.payload() = sdu;
        return getLayer<kNetwork>().send(pdu);
    }

    /**
     * @brief Send a datagram message of type T through the endpoint.
     *
     * This variant is used to directly reach an endpoint without going through
     * the protocol stack.
     *
     * @todo
     * A datagram is not part of a default protocol stack.
     * Clean this up with the protocol component refactoring.
     */
    template<typename T>
    ReturnCode sendDatagram(const T& msg)
    {
        internal::Datagram<T, typename TNetworkLayer::Header, typename TTransportLayer::DataHeader> pdu;
        getLayer<kTransport>().prepare(pdu.header());
        pdu.payload() = msg;
        return getLayer<kNetwork>().send(pdu);
    }

    /** @brief Get a specific layer of the endpoint. */
    template<size_t N>
    inline auto& getLayer()
    {
        return std::get<N>(layers_);
    }

    template<size_t N>
    inline const auto& getLayer() const
    {
        return std::get<N>(layers_);
    }

protected:
    /**
     * @brief All layers combined in a tuple.
     *
     * @remark
     * Dev Hint:
     * If you see errors like Endpoint cannot be copied because std::tuple of this variable
     * doesn't provide a copy assignment, it is because one of the single layers doesn't provide it.
     * Unfortunately C++ cannot tell which layer it is...
     *
     * @todo
     * utils::Tuple leads to strange warnings. Better use std::tuple
     * for now (or ever), as it is more sophisticated.
     */
    std::tuple<TNetworkLayer, TTransportLayer, TSessionLayer, TAppLayer> layers_;
};

} // namespace protocol
} // namespace pipc

#endif // PROTOCOL_ENDPOINT_BASE_HPP
