/// @copyright : 2022 Robert Bosch GmbH. All rights reserved

#ifndef PIPC_NODE_ID_HPP
#define PIPC_NODE_ID_HPP

#include <cstdint>

namespace pipc
{
/**
 * @brief Definition of an Id for a Node.
 *
 * A node represents one process in PIPC, its Node Id being a UUID to identify it.
 */
using NodeId = uint16_t;

} // namespace pipc

#endif // PIPC_NODE_ID_HPP
