/// @copyright : 2022 Robert Bosch GmbH. All rights reserved.

#ifndef COM_BINDING_PIPC_METHODCLIENT_HPP
#define COM_BINDING_PIPC_METHODCLIENT_HPP

#include "ara/com/IProxyMethod.hpp"
#include "ara/com/com_error_domain.h"
#include "ara/com/e2e/types.h"
#include "ara/com/types.h"
#include "ara/core/future.h"
#include "ara/core/promise.h"
#include "pipc/ReturnCode.hpp"
#include "pipc/rpc/Client.hpp"
#include "pipc/rpc/LoanClient.hpp"
#include "pipc/utils/Optional.hpp"

#include <map>
#include <type_traits>

namespace com
{
namespace binding_pipc
{
/**
 * @brief Base class to provide common functionality.
 * The common functionality provided includes request handling and two callback variants,
 * one for void output and one for all other.
 * The class already inherits the interface class IProxyMethod to allow a default implementation for GetSMState().
 * @tparam MethodOutput_T  The output type of the method call.
 * @tparam TArgs Variadic template argument for the input args.
 */
template<typename MethodOutput_T, typename... TArgs>
class MethodClientBase : public ara::com::IProxyMethod<MethodOutput_T, TArgs...>
{
    static_assert(!std::is_polymorphic<MethodOutput_T>::value, "Polymorphic MethodOutput types not supported");

public:
    using E2ESMState = ara::com::e2e::SMState;

    /**
     * @brief Implementation to get the E2E state machine state.
     * For non-serialized transfer, E2E is always disabled.
     * @return E2ESMState Always set to ara::com::e2e::SMState::kStateMDisabled.
     */
    E2ESMState GetSMState() const noexcept override
    {
        return E2ESMState::kStateMDisabled;
    }

    /**
     * @brief Callback implementation for non-void outputs.
     * Looks up the requestId in requestMap and sets the containing promise, if found.
     * Otherwise, it silently discards the sample.
     * TODO: Expected behavior?
     * If the request is found, but the sample is empty, the implementation sets an error on the promise.
     * @param sample    Moved-in SamplePtr, containing the expected method output. Output is copied into the promise.
     * @param requestId The callback is being called with a specific request ID coming from the transport.
     */
    template<typename T = MethodOutput_T, typename = typename std::enable_if<!std::is_void<T>::value>::type>
    void onCallback(pipc::loan::SamplePtr<T>&& sample, pipc::rpc::RequestId requestId)
    {
        std::lock_guard<std::mutex> lk(requestMapMutex_);
        auto foundSession = requestMap_.find(requestId);
        if (foundSession != requestMap_.end())
        {
            if (sample)
            {
                foundSession->second.set_value(*sample);
            }
            else
            {
                // TODO: This means we got a response, but it doesn't contain a valid sample.
                // Challenge: Application error transportation.
                foundSession->second.SetError(ara::com::ComErrc::kCommunicationStackError);
            }
            requestMap_.erase(foundSession);
        }
    }

    /**
     * @brief Callback implementation for void outputs.
     * Same as #onCallback, but instead of a sample pointer, one gets an Optional<void>, which is either set or not.
     * @param executedOk The input argument, indicating if the method call was properly executed or not.
     * @param requestId The callback is being called with a specific request ID coming from the transport.
     */
    template<typename T = MethodOutput_T, typename = typename std::enable_if<std::is_void<T>::value>::type>
    void onCallback(pipc::utils::Optional<void> executedOk, pipc::rpc::RequestId requestId)
    {
        std::lock_guard<std::mutex> lk(requestMapMutex_);
        auto foundSession = requestMap_.find(requestId);
        if (foundSession != requestMap_.end())
        {
            if (executedOk)
            {
                foundSession->second.set_value();
            }
            else
            {
                // TODO: This means we got a response, but it wasn't correctly executed.
                // Challenge: Application error transportation.
                foundSession->second.SetError(ara::com::ComErrc::kCommunicationStackError);
            }
            requestMap_.erase(foundSession);
        }
    }

    /**
     * @brief Callback invoked when the server goes offline
     * Invalidates all pending requests in case the server goes offline.
     */
    void onServerOffline()
    {
        std::lock_guard<std::mutex> lk(requestMapMutex_);
        for (auto & request : requestMap_)
        {
            request.second.SetError(ara::com::ComErrc::kCommunicationLinkError);
        }
        requestMap_.clear();
    }

protected:
    /**
     * @brief Support function to add an entry to the request map.
     * Tries to add a current request in form of a promise to the request map and returns the matching future.
     * @param requestId The request ID of the method call.
     * @param promise The promise that's kept to later inform the user of the response.
     * @return ara::core::Future<MethodOutput_T> A future of the method response type.
     */
    inline ara::core::Future<MethodOutput_T> insertInSessionMap(pipc::rpc::RequestId& requestId,
                                                                ara::core::Promise<MethodOutput_T>&& promise)
    {
        // Insert request in request map.
        std::lock_guard<std::mutex> lk(requestMapMutex_);

        auto future          = promise.get_future();
        auto insertionResult = requestMap_.insert(std::make_pair(requestId, std::move(promise)));
        // TODO: Code hard to test without a "stub" map. Will be adjusted with removal of std::map.
        // Quite an edge case, e.g. stale promises with request id overflow.
        if (!std::get<1>(insertionResult))
        {
            // Response can not be associated with request. This is quite a rare case.
            ara::core::Promise<MethodOutput_T> errorPromise;
            errorPromise.SetError(ara::com::ComErrorDomain::Errc::kNetworkBindingFailure);
            return errorPromise.get_future();
        }
        else
        {
            return future;
        }
    }

    // TODO: Session Map must change, that might be dynamic allocation.
    std::map<pipc::rpc::RequestId, ara::core::Promise<MethodOutput_T>> requestMap_; ///< Session map.
    std::mutex requestMapMutex_; ///< To avoid race conditions, request map is protected by a mutex.
};

/**
 * @brief Method call binding implementation for non-serialized, "single-copy" method calls.
 * Provides the operator(...) implementation required by the AUTOSAR method interface.
 * @tparam MethodOutput_T  The output type of the method call.
 * @tparam TArgs Variadic template argument for the input args.
 */
template<typename MethodOutput_T, typename... TArgs>
class MethodClient : public MethodClientBase<MethodOutput_T, TArgs...>
{
    static_assert(std::is_trivially_destructible<std::tuple<TArgs...>>::value,
                  "Arguments of method call must be trivial!");

public:
    /**
     * @brief Construct a new Method Caller Binding object.
     *
     * @param providerId The pipc providerId of the server this caller wants to call.
     * @param runtime The pipc runtime used to discover the server.
     */
    MethodClient(const pipc::session::ProviderId& providerId,
                 pipc::rte::IRuntime& runtime = pipc::rte::StandaloneRuntime::GetInstance())
        : MethodClientBase<MethodOutput_T, TArgs...>(),
          methodClientImpl_(providerId,
                           std::bind(&MethodClientBase<MethodOutput_T, TArgs...>::template onCallback<MethodOutput_T>,
                                     this,
                                     std::placeholders::_1,
                                     std::placeholders::_2),
                           runtime)
    {
        methodClientImpl_.registerServerOfflineCallback(
            std::bind(&MethodClientBase<MethodOutput_T, TArgs...>::onServerOffline, this));
    }

    /**
     * @brief Main implementation of the AUTOSAR method call API.
     * Limitation: Should support concurrent calls as required by SWS_CM_00032, but doesn't.
     * The protection of the request map is only done to protect it from concurrent access by the caller and the callback.
     * TODO: This is still the case with pipc due to allocate call in sendRequest.
     * @param args The variadic template argument list for the call.
     * @return ara::core::Future<MethodOutput_T> A future returned to the user to get the method call result.
     */
    ara::core::Future<MethodOutput_T> operator()(const TArgs... args)
    {
        ara::core::Promise<MethodOutput_T> promise;

        pipc::rpc::RequestId requestId;
        std::tuple<TArgs...> argumentTuple = {args...};
        pipc::ReturnCode result            = methodClientImpl_.sendRequest(argumentTuple, requestId);
        if (result != pipc::ReturnCode::kOk)
        {
            // Transmission error. Set NetworkBindingFailure and return.
            // Behavior described in SWS_CM_10440
            promise.SetError(ara::com::ComErrorDomain::Errc::kNetworkBindingFailure);
            return promise.get_future();
        }
        return this->insertInSessionMap(requestId, std::move(promise));
    }

protected:
    pipc::rpc::LoanClient<MethodOutput_T, std::tuple<TArgs...>> methodClientImpl_; ///< The transport implementation used.
};

/**
 * @brief Specialization of MethodBindingBase for no args input.
 *
 * @tparam MethodOutput_T  The output type of the method call.
 */
template<typename MethodOutput_T>
class MethodClient<MethodOutput_T, void> : public MethodClientBase<MethodOutput_T, void>
{
public:
    /**
     * @brief Construct a new Method Caller Binding object
     * Exact same as default implementation.
     * @param providerId The pipc providerId of the server this caller wants to call.
     * @param runtime The pipc runtime used to discover the server.
     */
    MethodClient(const pipc::session::ProviderId& providerId,
                 pipc::rte::IRuntime& runtime = pipc::rte::StandaloneRuntime::GetInstance())
        : MethodClientBase<MethodOutput_T, void>(),
          methodClientImpl_(providerId,
                           std::bind(&MethodClientBase<MethodOutput_T, void>::template onCallback<MethodOutput_T>,
                                     this,
                                     std::placeholders::_1,
                                     std::placeholders::_2),
                           runtime)
    {
        methodClientImpl_.registerServerOfflineCallback(
            std::bind(&MethodClientBase<MethodOutput_T, void>::onServerOffline, this));
    }

    /**
     * @brief Main implementation of the AUTOSAR method call API.
     * Same as default, but specialized for void, not forwarding any arguments to the implementation.
     * @return ara::core::Future<MethodOutput_T> A future returned to the user to get the method call result.
     */
    ara::core::Future<MethodOutput_T> operator()()
    {
        ara::core::Promise<MethodOutput_T> promise;

        pipc::rpc::RequestId requestId;
        pipc::ReturnCode result = methodClientImpl_.sendRequest(requestId);
        if (result != pipc::ReturnCode::kOk)
        {
            // Transmission error. Set NetworkBindingFailure and return.
            // Behavior described in SWS_CM_10440
            promise.SetError(ara::com::ComErrorDomain::Errc::kNetworkBindingFailure);
            return promise.get_future();
        }
        return this->insertInSessionMap(requestId, std::move(promise));
    }

protected:
    //
    //
    /**
     * @brief ImplTypeSelector is needed for a "void in"-"void out" variant of the impl.
     * The implementation for the false variant of B.
     * @tparam B A bool to check if the output type is void or not.
     * @tparam fake C++14 doesn't allow explicit template specialization in a class, the fake parameter is a needed
     * workaround.
     */
    template<bool B, typename fake = void>
    struct ImplTypeSelector
    {
        using ImplType = pipc::rpc::LoanClient<MethodOutput_T, void>;
    };

    /**
     * @brief Specialization of ImplTypeSelector for the true case.
     */
    template<typename fake>
    struct ImplTypeSelector<true, fake>
    {
        using ImplType = pipc::rpc::Client<void, void>;
    };

    typename ImplTypeSelector<std::is_void<MethodOutput_T>::value>::ImplType
        methodClientImpl_; ///< The selected methodClient implementation.
};

} // namespace binding_pipc
} // namespace com

#endif // COM_BINDING_PIPC_METHODCLIENT_HPP
