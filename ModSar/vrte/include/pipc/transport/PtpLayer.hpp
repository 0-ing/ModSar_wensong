/// @copyright : 2022 Robert Bosch GmbH. All rights reserved

#ifndef TRANSPORT_TRANSPORT_LAYER_HPP
#define TRANSPORT_TRANSPORT_LAYER_HPP

#include "Port.hpp"
#include "pipc/protocol/DefaultLayer.hpp"

namespace pipc
{
namespace transport
{
/**
 * @brief Transport layer.
 *
 * Encapsulates source and destination port, maybe a seq. no. later.
 */
class PtpLayer : public protocol::DefaultLayer
{
public:
    struct Header
    {
        /** @brief Equal operator (used mainly for testing). */
        inline bool operator==(const Header& other) const
        {
            return (dstPort == other.dstPort) && (srcPort == other.srcPort);
        }

        Port dstPort;
        Port srcPort;
    };

    /** @brief Reduced header for datagram messages. */
    struct DataHeader
    {
        /** @brief Equal operator (used mainly for testing). */
        inline bool operator==(const DataHeader& other) const
        {
            return (dstPort == other.dstPort);
        }

        Port dstPort;
    };

    /** @brief Equal operator. */
    inline bool operator==(const PtpLayer& other) const
    {
        return (dstPort_ == other.dstPort_) && (srcPort_ == other.srcPort_);
    }

    /** @brief Put this layer's header into place. */
    void prepare(Header& header)
    {
        // std::cout << "Transport (ctrl): Inserting header (dst|src " << getDstPort() << "|" << getSrcPort() << ")"
        //           << std::endl;
        header.dstPort = dstPort_;
        header.srcPort = srcPort_;
    }

    /** @brief Put a datagram header into place. */
    void prepare(DataHeader& header)
    {
        // std::cout << "Transport (data): Inserting header (dst " << getDstPort() << ")" << std::endl;
        header.dstPort = dstPort_ | 1;
    }

    /** @brief Initialize this layer. */
    void init(Port dstPort, Port srcPort)
    {
        setDstPort(dstPort);
        setSrcPort(srcPort);
    }

    inline Port getDstPort()
    {
        return GetPort(dstPort_);
    }

    inline Port getSrcPort() const
    {
        return GetPort(srcPort_);
    }

    inline void setDstPort(Port port)
    {
        dstPort_ = MakePort(port);
    }

    inline void setSrcPort(Port port)
    {
        srcPort_ = MakePort(port);
    }

    template<size_t NLayer, typename... TLayers>
    inline ReturnCode receive(PtpEndpoint<TLayers...>& endpoint, Message<PayloadRx, NLayer, TLayers...>& pdu)
    {
        // std::cout << "Got message from port: " << GetPort(pdu.header().srcPort) << std::endl;
        // HINT: We don't need to check for the the header's dstPort, we wouldn't be
        // receiving the message if it was wrong
        if (pdu.header().srcPort == dstPort_)
        {
            return protocol::Forward<NLayer>(endpoint, pdu);
        }
        else
        {
            return ReturnCode::kTransportError;
        }
    }

private:
    /** @brief The internal port to send messages to. */
    Port dstPort_{MakePort(INVALID_PORT)};
    /** @brief The internal port to receive messages from. */
    Port srcPort_{MakePort(INVALID_PORT)};
};

} // namespace transport
} // namespace pipc

#endif // TRANSPORT_TRANSPORT_LAYER_HPP
