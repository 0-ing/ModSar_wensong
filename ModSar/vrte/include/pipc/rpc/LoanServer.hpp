/// @copyright : 2022 Robert Bosch GmbH. All rights reserved.

#ifndef PIPC_RPC_LOAN_SERVER_HPP
#define PIPC_RPC_LOAN_SERVER_HPP

#include "LoanServerUntyped.hpp"
#include "Sample.hpp"

namespace pipc
{
namespace rpc
{
/**
 * @brief Class for processing Remote Procedure Calls using
 *
 *  This class can be used whenever the server is expecting requests and sending a reply.
 *  shared memory (loan-restitute) - Request & Reply
 */
template<typename TReply, typename TRequest, size_t RpcRequestsQueueSize = PIPC_MAX_PENDING_RPC_REQUESTS>
class LoanServer
    : public LoanServerUntyped<std::is_void<TReply>::value, std::is_void<TRequest>::value, RpcRequestsQueueSize>
{
private:
    using BaseClass = LoanServerUntyped<std::is_void<TReply>::value, std::is_void<TRequest>::value, RpcRequestsQueueSize>;
    using Executor        = typename ExecutorSelector<TReply, TRequest>::Executor;
    using GenericExecutor = typename BaseClass::Executor;
    using RpcSample       = Sample<TRequest, TReply>;

public:
    /**
     * @brief Constructor for registering this class with a runtime.
     *
     * @param providerId The Id used to identify the Client.
     * @param runtime The runtime used for this LoanServer.
     */
    LoanServer(const session::ProviderId& providerId, rte::IRuntime& runtime = rte::StandaloneRuntime::GetInstance())
        : BaseClass::LoanServerUntyped(providerId, runtime, sizeof(RpcSample), RpcSample::GetReplyOffset())
    {
    }

    /**
     * @brief Register the Executor function for the incoming requests.
     *
     * @param executor The executor function.
     * @return ReturnCode
     *   - kOk
     *   - kExecutorAlreadyRegistered
     */
    inline ReturnCode registerExecutor(Executor executor)
    {
        return BaseClass::registerExecutor(*reinterpret_cast<GenericExecutor*>(&executor));
    }
};

} // namespace rpc
} // namespace pipc

#endif // PIPC_RPC_LOAN_SERVER_HPP
