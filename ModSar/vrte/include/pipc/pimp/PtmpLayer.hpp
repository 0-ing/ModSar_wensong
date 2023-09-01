#ifndef PIMP_PTMP_LAYER_HPP
#define PIMP_PTMP_LAYER_HPP

#include "pipc/protocol/DefaultLayer.hpp"

namespace pipc
{
namespace pimp
{
/**
 * @brief PTMP Layer for PIMP Sockets.
 *
 * The PTMP Layer on the network layer simply passes the received messages.
 */
using PtmpLayer = protocol::DefaultLayer;

} // namespace pimp
} // namespace pipc

#endif // PIMP_PTMP_LAYER_HPP
