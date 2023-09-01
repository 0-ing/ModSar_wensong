/// @copyright : 2022 Robert Bosch GmbH. All rights reserved

#ifndef PIPC_TRANSPORT_PORT_HPP
#define PIPC_TRANSPORT_PORT_HPP

#include <stdint.h>

namespace pipc
{
namespace transport
{
/**
 * @brief Definition of a port.
 *
 * The port is merely an integer, which is used to route a message to a destination.
 * The purpose of this port is similar to how ports are utilized in network protocols.
 */
using Port                         = uint16_t;
static constexpr Port INVALID_PORT = 0x7FFF;

/** @brief Convert a logical port to the internal representation. */
constexpr Port MakePort(Port port)
{
    return static_cast<Port>(port * 2);
}

/** @brief Convert an internal port to the logical presentation. */
constexpr Port GetPort(Port port)
{
    return static_cast<Port>(port / 2);
}

/**
 * @brief PortPair used for endpoint communication
 */
struct PortPair
{
    Port ctrlPort;
    Port dataPort;

    /** @brief Equal operator. */
    inline bool operator==(const PortPair& other) const
    {
        bool same = ((ctrlPort == other.ctrlPort) && (dataPort == other.dataPort));
        return same;
    }
};

} // namespace transport
} // namespace pipc

#endif // PIPC_TRANSPORT_PORT_HPP
