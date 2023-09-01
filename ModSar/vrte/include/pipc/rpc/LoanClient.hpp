/// @copyright : 2022 Robert Bosch GmbH. All rights reserved.

#ifndef PIPC_RPC_LOAN_CLIENT_HPP
#define PIPC_RPC_LOAN_CLIENT_HPP

#include "LoanClientUntyped.hpp"
#include "Sample.hpp"

namespace pipc
{
namespace rpc
{
/**
 * @brief Implementation for SHM RPC clients.
 *
 * This class provides end-user functionality for all SHM RPC clients.
 * The API is typed for request and reply types similar to the self-contained RPC Client.
 *
 * @tparam TReply The data type of the reply.
 * @tparam TRequest The data type of the request.
 * @tparam MaxLoans Corresponds to the maximum no. of concurrent pending requests.
 */
template<typename TReply, typename TRequest, size_t MaxLoans = PIPC_MAX_CONCURRENT_CLIENT_REQUESTS>
class LoanClient : public LoanClientUntyped<std::is_void<TReply>::value, MaxLoans>
{
private:
    using BaseClass        = LoanClientUntyped<std::is_void<TReply>::value, MaxLoans>;
    using SamplePtrRequest = loan::SamplePtr<TRequest>;
    using SamplePtrReply   = loan::SamplePtr<TReply>;
    static_assert(!(std::is_void<TRequest>::value && std::is_void<TReply>::value),
                  "TReply==void && TRequest==void is not a possible option (already covered by rpc::Client).");

    // CallbackSelector is needed for ReplyReceivedCallback with a void reply.
    // C++14 doesn't allow explicit template specialization in a class, the fake parameter is a needed workaround.
    template<bool B, typename fake = void>
    struct CallbackSelector
    {
        using Callback = utils::Function<void(SamplePtrReply&&, RequestId)>;
    };
    template<typename fake>
    struct CallbackSelector<true, fake>
    {
        using Callback = utils::Function<void(utils::Optional<void>, RequestId)>;
    };

public:
    using ReplyReceivedCallback = typename CallbackSelector<std::is_void<TReply>::value>::Callback;
    using RpcSample = Sample<TRequest, TReply>;

    /**
     * @brief Construct the LoanClient and register it at the runtime.
     *
     * @param providerId The ProviderId of the server.
     * @param replyReceivedCallback The callback invoked when receiving a reply.
     * @param runtime The runtime to be used.
     */
    LoanClient(const session::ProviderId& providerId,
               const ReplyReceivedCallback& replyReceivedCallback,
               rte::IRuntime& runtime = rte::StandaloneRuntime::GetInstance())
        : BaseClass::LoanClientUntyped(providerId,
                                       *reinterpret_cast<const typename BaseClass::ReplyReceivedCallback*>(
                                           &replyReceivedCallback),
                                       runtime,
                                       sizeof(RpcSample),
                                       RpcSample::GetReplyOffset())
    {
    }

    /**
     * @brief Allocate a RPC request sample.
     *
     * @remark
     * Only available if TRequest is not void.
     */
    template<typename T = TRequest, typename = typename std::enable_if<!std::is_void<T>::value>::type>
    constexpr SamplePtrRequest allocate()
    {
        return BaseClass::template allocate<T>();
    }

    /**
     * @brief Send a request to be processed by the server.
     *
     * Variant for sending requests with input data.
     *
     * @param request The data of the request.
     * @param[out] requestId The Id used to map the request to a reply.
     * @return
     *  - kOk : Sending was successful
     *  - kNetworkError : There was an error sending to the socket
     *  - kNotConnected : Connection to the server is not established
     */
    template<typename T = TRequest, typename = typename std::enable_if<!std::is_void<T>::value>::type>
    ReturnCode sendRequest(const T& request, RequestId& requestId)
    {
        auto samplePtr = allocate();
        if (EXPECT_UNLIKELY(!samplePtr))
        {
            return ReturnCode::kMaxSamplesReached;
        }
        *samplePtr = request;
        return BaseClass::sendRequest(samplePtr, requestId);
    }

    /**
     * @brief Send a request to be processed by the server.
     *
     * Variant for sending requests without input data.
     *
     * @param request The data of the request.
     * @param[out] requestId The Id used to map the request to a reply.
     * @return
     *  - kOk : Sending was successful
     *  - kNetworkError : There was an error sending to the socket
     *  - kNotConnected : Connection to the server is not established
     */
    template<typename T = TRequest, typename = typename std::enable_if<std::is_void<T>::value>::type>
    ReturnCode sendRequest(RequestId& requestId)
    {
        auto samplePtr = BaseClass::allocate();
        if (EXPECT_UNLIKELY(!samplePtr))
        {
            return ReturnCode::kMaxSamplesReached;
        }
        return BaseClass::sendRequest(samplePtr, requestId);
    }

    /**
     * @brief Send a request to be processed by the server.
     *
     * Variant for sending a pre-allocated sample.
     *
     * @param request The data of the request.
     * @param[out] requestId The Id used to map the request to a reply.
     * @return
     *  - kOk : Sending was successful
     *  - kNetworkError : There was an error sending to the socket
     *  - kNotConnected : Connection to the server is not established
     */
    inline ReturnCode sendRequest(SamplePtrRequest&& request, RequestId& requestId)
    {
        auto& samplePtr = static_cast<typename BaseClass::SamplePtr&>(request);
        return BaseClass::sendRequest(samplePtr, requestId);
    }
};

} // namespace rpc
} // namespace pipc

#endif
