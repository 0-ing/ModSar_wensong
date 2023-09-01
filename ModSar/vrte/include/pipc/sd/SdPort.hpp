/// @copyright : 2022 Robert Bosch GmbH. All rights reserved

#ifndef PIPC_SD_PORT_HPP
#define PIPC_SD_PORT_HPP

#include "pipc/transport/Port.hpp"

namespace pipc
{
namespace sd
{
/**
 * @brief The port used for PIPC Service Discovery.
 *
 * PIPC Service Discovery always runs over Port 0. This port is reserved and not configurable.
 */
static constexpr transport::Port SdPort = 0U;

} // namespace sd
} // namespace pipc

#endif // PIPC_SD_PORT_HPP
