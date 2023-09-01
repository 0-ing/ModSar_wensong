/// @copyright : 2022 Robert Bosch GmbH. All rights reserved.

#ifndef PIPC_RPC_LOAN_SERVER_FIRE_AND_FORGET_HPP
#define PIPC_RPC_LOAN_SERVER_FIRE_AND_FORGET_HPP

#include "LoanServer.hpp"

namespace pipc
{
namespace rpc
{
/**
 * @brief A "Fire And Forget" RPC server which sends no reply.
 *
 * This class uses shared memory to receive requests.
 * This class can be used whenever the server is expecting requests without sending
 * a reply or any other kind of feedback, whether the request has been processed or not.
 *
 * @tparam TRequest The data type of the request.
 *  - void means no data is used for the request
 * @tparam RpcRequestsQueueSize the queue size of PendingRequests.
 */
template<typename TRequest, size_t RpcRequestsQueueSize = PIPC_MAX_PENDING_RPC_REQUESTS>
using LoanServerFireAndForget = LoanServer<void, TRequest, RpcRequestsQueueSize>;

} // namespace rpc
} // namespace pipc

#endif // PIPC_RPC_LOAN_SERVER_FIRE_AND_FORGET_HPP
