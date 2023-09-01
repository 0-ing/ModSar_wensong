/// @copyright : 2022 Robert Bosch GmbH. All rights reserved

#ifndef PIPC_SOCKET_ID_HPP
#define PIPC_SOCKET_ID_HPP

#include <cstdint>

namespace pipc
{
/**
 * @brief Definition of an Id for a Socket.
 *
 * The socket Id represents one pimp socket in PIPC, its Id being a UUID to identify its path in shmem.
 */
using ProcSocketId = uint16_t;

} // namespace pipc

#endif // PIPC_NODE_ID_HPP
