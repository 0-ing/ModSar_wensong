/// @copyright : 2022 Robert Bosch GmbH. All rights reserved.

#ifndef PIPC_RPC_REQUEST_ID_HPP
#define PIPC_RPC_REQUEST_ID_HPP

#include <stdint.h>

namespace pipc
{
namespace rpc
{
/**
 * @brief Definition of a Request Id.
 *
 * The Request Id is a sequence counter incremented sent with & increment for sending requests from the client to the
 * server. It is stated in both request and reply messages and is used to create a mapping between those messages.
 */
using RequestId = uint16_t;

} // namespace rpc
} // namespace pipc

#endif // PIPC_RPC_REQUEST_ID_HPP
