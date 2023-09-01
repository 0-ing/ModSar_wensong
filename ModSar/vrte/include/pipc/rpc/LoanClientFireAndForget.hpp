/// @copyright : 2022 Robert Bosch GmbH. All rights reserved.

#ifndef PIPC_RPC_LOAN_CLIENT_FIRE_AND_FORGET_HPP
#define PIPC_RPC_LOAN_CLIENT_FIRE_AND_FORGET_HPP

#include "LoanClientFireAndForgetUntyped.hpp"

namespace pipc
{
namespace rpc
{
/**
 * @brief Implementation for SHM RPC Fire And Forget clients.
 *
 * This class provides end-user functionality for all SHM RPC F&F clients.
 * The API is typed for request types similar to the self-contained RPC Client.
 *
 * @tparam TRequest The data type of the request.
 * @tparam MaxLoans Corresponds to the maximum no. of concurrent pending requests.
 */
template<typename TRequest, size_t MaxLoans = PIPC_MAX_CONCURRENT_CLIENT_REQUESTS>
class LoanClientFireAndForget : public LoanClientFireAndForgetUntyped<MaxLoans>
{
    static_assert(!std::is_void<TRequest>::value, "A Loan F&F Client cannot have a void request.");

private:
    using BaseClass        = LoanClientFireAndForgetUntyped<MaxLoans>;
    using SamplePtrRequest = loan::SamplePtr<TRequest>;

public:
    /**
     * @brief Construct the LoanClientFireAndForget and register it at the runtime.
     *
     * @param providerId The ProviderId of the server.
     * @param runtime The runtime to be used.
     */
    LoanClientFireAndForget(const session::ProviderId& providerId,
                            rte::IRuntime& runtime = rte::StandaloneRuntime::GetInstance())
        : BaseClass(providerId, runtime, sizeof(TRequest))
    {
    }

    /** @brief Allocate a RPC request sample. */
    constexpr SamplePtrRequest allocate()
    {
        return BaseClass::template allocate<TRequest>();
    }

    /**
     * @brief Send a request to be processed by the server.
     *
     * @param request The data of the request.
     * @return
     *  - kOk : Sending was successful
     *  - kNetworkError : There was an error sending to the socket
     *  - kNotConnected : Connection to the server is not established
     */
    ReturnCode sendRequest(const TRequest& request)
    {
        auto samplePtr = allocate();
        if (EXPECT_UNLIKELY(!samplePtr))
        {
            return ReturnCode::kMaxSamplesReached;
        }
        *samplePtr = request;
        return BaseClass::sendRequest(samplePtr);
    }

    /**
     * @brief Send a request to be processed by the server.
     *
     * Variant for sending a pre-allocated sample.
     *
     * @param request The data of the request.
     * @return
     *  - kOk : Sending was successful
     *  - kNetworkError : There was an error sending to the socket
     *  - kNotConnected : Connection to the server is not established
     */
    ReturnCode sendRequest(SamplePtrRequest&& request)
    {
        auto& samplePtr = static_cast<typename BaseClass::SamplePtr&>(request);
        return BaseClass::sendRequest(samplePtr);
    }
};

} // namespace rpc
} // namespace pipc

#endif // PIPC_RPC_LOAN_CLIENT_FIRE_AND_FORGET_HPP
