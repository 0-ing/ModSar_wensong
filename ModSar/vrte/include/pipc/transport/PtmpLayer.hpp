/// @copyright : 2022 Robert Bosch GmbH. All rights reserved

#ifndef TRANSPORT_TRANSPORT_MULTI_LAYER
#define TRANSPORT_TRANSPORT_MULTI_LAYER

#include "Port.hpp"
#include "pipc/protocol/DefaultLayer.hpp"

namespace pipc
{
namespace transport
{
/**
 * @brief PTMP Layer on the transport level.
 *
 * Similar to the PtpLayer, but expects incoming messages
 * from different ports and therefore doesn't contain a dstPort.
 */
class PtmpLayer : public protocol::DefaultLayer
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

    /** @brief Initialize this layer. */
    void init(Port srcPort)
    {
        setSrcPort(srcPort);
    }

    inline Port getSrcPort() const
    {
        return GetPort(srcPort_);
    }

    inline void setSrcPort(Port port)
    {
        srcPort_ = MakePort(port);
    }

private:
    /** @brief The internal port to receive messages from. */
    Port srcPort_{MakePort(INVALID_PORT)};
};

} // namespace transport
} // namespace pipc

#endif // TRANSPORT_TRANSPORT_MULTI_LAYER
