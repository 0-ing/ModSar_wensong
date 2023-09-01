/// @copyright : 2022 Robert Bosch GmbH. All rights reserved.

#ifndef COM_BINDING_PIPC_METHODCLIENTSERIALIZED_HPP
#define COM_BINDING_PIPC_METHODCLIENTSERIALIZED_HPP

#include "ara/com/IProxyMethod.hpp"
#include "ara/com/com_error_domain.h"
#include "ara/com/types.h"
#include "ara/core/promise.h"
#include "binding/ReadableComponentIdentifier.hpp"
#include "binding/SerializedSample.hpp"
#include "binding_pipc/MethodArgumentSerializationHelper.hpp"
#include "binding_pipc/ProviderIdGenerator.hpp"
#include "config/IServiceIntfCfg.hpp"
#include "e2e/IE2EChecker.hpp"
#include "e2e/IE2EProtector.hpp"
#include "pipc/rpc/LoanClientUntyped.hpp"
#include "pipc/sd/Runtime.hpp"
#include "serializer/ArgumentSerializerCarrier.hpp"
#include "serializer/IDeserializer.hpp"
#include "serializer/ISerializer.hpp"
#include "utils/Logger.hpp"

#include <map>

namespace com
{
namespace binding_pipc
{
/**
 * @brief Base class for serialized method clients
 *
 * Provides callback routine variants and request map handling.
 * @tparam MethodOutput_T  output arg type
 * @tparam TArgs Input arg types
 */
template<typename MethodOutput_T, typename... TArgs>
class MethodClientSerializedBase : public ara::com::IProxyMethod<MethodOutput_T, TArgs...>
{
    static_assert(!std::is_polymorphic<MethodOutput_T>::value, "Polymorphic MethodOutput types not supported");

protected:
    template<typename T>
    using UniquePtr             = ara::com::UniquePtr<T>;
    using Logger                = com::utils::Logger;
    using E2ESMState            = ara::com::e2e::SMState;
    using E2EProfileCheckStatus = ara::com::e2e::ProfileCheckStatus;
    using E2EErrc               = ara::com::e2e::E2EErrc;
    using PipcSamplePtr         = pipc::loan::SamplePtr<pipc::utils::Placeholder>;

    /**
     * @brief Construct a new Method Client Serialized Base object for both SOME/IP and IPC deployment
     *
     * Doesn't use any special fields of the config, thius this works.
     * @tparam TContext     Exact type of the deployment context. Must match TMethodCfg
     * @tparam TMethodCfg      Exact type of the configuration. Must match TContext
     * @param context       Service information (Deployment Context).
     * @param methodConfig  Configuration parameter pack.
     * @param deserializer  The deserializer for output deserialization.
     * @param f_checker     The checker to check the arriving content.
     *
     * @todo
     * Currently methods with void output are generated as fire and forget
     */
    template<typename TContext, typename TMethodCfg>
    MethodClientSerializedBase(const TContext& context,
                               const TMethodCfg& methodConfig,
                               UniquePtr<serializer::IDeserializer<MethodOutput_T>>&& deserializer,
                               UniquePtr<e2e::IE2EChecker>&& f_checker)
        : maxRequestSize_(methodConfig.requestMaxSerializationSize + binding::SerializedSample::GetHeaderSize()),
          maxResponseSize_(methodConfig.responseMaxSerializationSize + binding::SerializedSample::GetHeaderSize()),
          methodClientImpl_(ProviderIdGenerator::Generate(context, methodConfig),
                            std::bind(&MethodClientSerializedBase<MethodOutput_T,
                                                                  TArgs...>::template onCallback<MethodOutput_T>,
                                      this,
                                      std::placeholders::_1,
                                      std::placeholders::_2),
                            pipc::sd::Runtime::GetInstance(),
                            maxRequestSize_ + maxResponseSize_,
                            maxRequestSize_),
          outputDeserializer(std::move(deserializer)),
          checker(std::move(f_checker)),
          readableComponentId_({context, methodConfig.methodName})
    {
        // Disable smState from the start in case we have no checker.
        // (Determined via checking for a header length of 0).
        if (checker)
        {
            if (checker->getE2EHeaderLength() != 0)
            {
                this->smState = E2ESMState::kNoData;
                return;
            }
        }
        this->smState = E2ESMState::kStateMDisabled;
        methodClientImpl_.registerServerOfflineCallback(
            std::bind(&MethodClientSerializedBase<MethodOutput_T, TArgs...>::onServerOffline, this));
    }

    ~MethodClientSerializedBase() = default;

    /**
     * @brief onCallback for a non-void serialized output type.
     *
     * @tparam T Selection parameter to determine if output type is void.
     * @tparam std::enable_if<!std::is_void<T>::value>::type
     * @param samplePtr Sample ptr containing serialized data.
     * @param requestId Request ID the response is associated with
     */
    template<typename T = MethodOutput_T, typename = typename std::enable_if<!std::is_void<T>::value>::type>
    void onCallback(PipcSamplePtr&& samplePtr, pipc::rpc::RequestId requestId)
    {
        // Whole function under lock
        std::lock_guard<std::mutex> lk(this->requestMapMutex_);

        auto foundPair = this->requestMap_.find(requestId);
        if (foundPair == this->requestMap_.end())
        {
            Logger::GetInstance().LogError()
                << this->readableComponentId_ << " Received reply with unknown requestId: " << requestId << "\n";
            return;
        }
        // RequestId was found.
        RequestInfo& foundRequestInfo = foundPair->second;
        if (samplePtr)
        {
            auto& sample                      = *reinterpret_cast<binding::SerializedSample*>(samplePtr.get());
            ara::com::e2e::Result checkResult = checker->check(e2e::MessageType::kResponse,
                                                               e2e::MessageResult::kOk,
                                                               foundRequestInfo.e2eCounter,
                                                               sample.data(),
                                                               sample.size());

            this->smState = checkResult.smStatus;

            switch (checkResult.checkStatus)
            {
            case E2EProfileCheckStatus::kRepeated:
            case E2EProfileCheckStatus::kWrongSequence:
                Logger::GetInstance().LogWarn()
                    << this->readableComponentId_ << " E2E failed with wrong counter. No further processing!\n";
                // [SWS_CM_10465] discarded without any further processing
                // Entry remains in requestMap.
                return;
            case E2EProfileCheckStatus::kOk:
            case E2EProfileCheckStatus::kCheckDisabled:
            {
                T output{};
                uint32_t readbytes;
                size_t e2eHeaderLength = checker->getE2EHeaderLength();

                if (outputDeserializer->deserialize(sample.data() + e2eHeaderLength,
                                                    static_cast<uint32_t>(sample.size() - e2eHeaderLength),
                                                    &output,
                                                    &readbytes))
                {
                    foundRequestInfo.promise.set_value(output);
                }
                else
                {
                    Logger::GetInstance().LogError()
                        << this->readableComponentId_ << " Deserialization on reply reception failed.\n";
                    foundRequestInfo.promise.SetError(ara::com::ComErrc::kCommunicationStackError);
                }
                break;
            }
            case E2EProfileCheckStatus::kError:
                foundRequestInfo.promise.SetError(E2EErrc::kError);
                break;
            case E2EProfileCheckStatus::kNotAvailable:
                foundRequestInfo.promise.SetError(E2EErrc::kNotAvailable);
                break;
            case E2EProfileCheckStatus::kNoNewData:
                foundRequestInfo.promise.SetError(E2EErrc::kNoNewData);
                break;

            default:
                // not reach here
                break;
            }
        }
        else
        {
            Logger::GetInstance().LogError() << this->readableComponentId_ << " Received empty sample ptr.\n";
            foundRequestInfo.promise.SetError(ara::com::ComErrc::kCommunicationStackError);
        }
        // Remove entry from map.
        static_cast<void>(this->requestMap_.erase(foundPair));
    }

    /**
     * @brief Callback implementation for void outputs.
     *
     * @param executedOk The input argument, indicating if the method call was properly executed or not.
     * @param requestId The callback is being called with a specific request ID coming from the transport.
     */
    template<typename T = MethodOutput_T, typename = typename std::enable_if<std::is_void<T>::value>::type>
    void onCallback(pipc::utils::Optional<void> executedOk, pipc::rpc::RequestId requestId)
    {
        // Whole function under lock
        std::lock_guard<std::mutex> lk(requestMapMutex_);
        auto foundSession = requestMap_.find(requestId);
        if (foundSession == requestMap_.end())
        {
            Logger::GetInstance().LogWarn()
                << this->readableComponentId_ << " Received reply with unknown requestId: " << requestId << "\n";
            return;
        }
        if (executedOk)
        {
            foundSession->second.promise.set_value();
        }
        else
        {
            // TODO: This means we got a response, but it wasn't correctly executed.
            // Challenge: Application error transportation.
            foundSession->second.promise.SetError(ara::com::ComErrc::kCommunicationStackError);
        }
        requestMap_.erase(foundSession);
    }

    /**
     * @brief Getter for E2E state machine state.
     * @return E2ESMState The current state of the E2E state machine.
     */
    E2ESMState GetSMState() const noexcept override
    {
        return smState;
    }

    /**
     * @brief Callback invoked when the server goes offline
     * Invalidates all pending requests in case the server goes offline.
     */
    void onServerOffline()
    {
        std::lock_guard<std::mutex> lk(requestMapMutex_);
        for (auto& request : requestMap_)
        {
            request.second.promise.SetError(ara::com::ComErrc::kCommunicationLinkError);
        }
        requestMap_.clear();
    }

    /**
     * @brief Small struct containing information for a single request.
     *
     */
    struct RequestInfo
    {
        ara::core::Promise<MethodOutput_T> promise;
        uint32_t e2eCounter{0};
    };

    /**
     * @brief Support function to add an entry to the request map.
     *
     * Tries to add current request in form of a promise to the request map and returns the matching future.
     *
     * @param requestId The request ID of the method call.
     * @param requestInfo The info containing the promise that's kept to later inform the user of the response.
     * @return ara::core::Future<MethodOutput_T> A future of the method response type.
     */
    inline ara::core::Future<MethodOutput_T> insertInRequestMap(pipc::rpc::RequestId& requestId,
                                                                RequestInfo&& requestInfo)
    {
        auto future          = requestInfo.promise.get_future();
        auto insertionResult = requestMap_.insert(std::make_pair(requestId, std::move(requestInfo)));
        // Quite an edge case, e.g. stale promises with request id overflow.
        if (!std::get<1>(insertionResult))
        {
            ara::core::Promise<MethodOutput_T> errorPromise;
            errorPromise.SetError(ara::com::ComErrorDomain::Errc::kNetworkBindingFailure);
            return errorPromise.get_future();
        }
        else
        {
            return future;
        }
    }

    // TODO Session map may dynamically allocate memory, thus it is not ASIL-capable. Replace with bounded alternative.
    std::map<pipc::rpc::RequestId, RequestInfo>
        requestMap_; ///< Map to associate incoming responses with a given requestId to stored information of a request.
    std::mutex requestMapMutex_; ///< Used to protect the session map.
    E2ESMState smState;          ///< Most recent state of the E2E State Machine.

    size_t maxRequestSize_;  ///< Stored maximum size of the request.
    size_t maxResponseSize_; ///< Stored maximum size of the response.
    pipc::rpc::LoanClientUntyped<std::is_void<MethodOutput_T>::value>
        methodClientImpl_; //< The underlying pipc method client implementation.
    UniquePtr<serializer::ArgumentSerializerCarrier<sizeof...(TArgs), TArgs...>> serializerCarrier_; ///< Serializer pack
    UniquePtr<::com::serializer::IDeserializer<MethodOutput_T>> outputDeserializer; ///< Deserializer pack
    UniquePtr<e2e::IE2EProtector> protector_;                  ///< E2E protector for protecting requests
    UniquePtr<e2e::IE2EChecker> checker;                       ///< E2E checker for checking replies
    binding::ReadableComponentIdentifier readableComponentId_; ///< Identifier for human-readable printouts
};

/**
 * @brief Serialized method client implementation with non-void inputs.
 *
 * @tparam MethodOutput_T  output arg type
 * @tparam TArgs Input arg types
 */
template<typename MethodOutput_T, typename... TArgs>
class MethodClientSerialized : public MethodClientSerializedBase<MethodOutput_T, TArgs...>
{
    static_assert(!std::is_polymorphic<MethodOutput_T>::value, "Polymorphic MethodOutput types not supported");

public:
    using BaseClass = MethodClientSerializedBase<MethodOutput_T, TArgs...>;
    template<typename T>
    using UniquePtr = ara::com::UniquePtr<T>;
    using Logger    = com::utils::Logger;

    /**
     * @brief Constructor.
     *
     * @param context       Service information (Deployment Context).
     * @param methodConfig  Configuration parameter pack.
     * @param asc           Serialier pack used for sending
     * @param protector     protector for E2E protection.
     * @param deserializer  The deserializer for output deserialization. Can be left out for void outputs.
     * @param f_checker     The checker to check the arriving content. Checker with profile disabled can be used for
     * void outputs.
     */
    template<typename TContext, typename TMethodCfg>
    MethodClientSerialized(const TContext& context,
                           const TMethodCfg& methodConfig,
                           UniquePtr<serializer::ArgumentSerializerCarrier<sizeof...(TArgs), TArgs...>>&& asc,
                           UniquePtr<e2e::IE2EProtector>&& f_protector,
                           UniquePtr<serializer::IDeserializer<MethodOutput_T>>&& od = nullptr,
                           UniquePtr<e2e::IE2EChecker>&& f_checker                   = nullptr)
        : BaseClass(context, methodConfig, std::move(od), std::move(f_checker)),
          serializerCarrier_(std::move(asc)),
          protector_(std::move(f_protector))
    {
    }

    ~MethodClientSerialized() = default;

    /**
     * @brief Implementation of the actual method call for serialized data.
     *
     * @param args The input arguments as specified by the user.
     * @return ara::core::Future<MethodOutput_T> A future to handle incoming responses.
     */
    ara::core::Future<MethodOutput_T> operator()(const TArgs... args)
    {
        using SerializationHelper = MethodArgumentSerializationHelper<sizeof...(TArgs), sizeof...(TArgs), TArgs...>;
        // calculate the serialized size of the arguments:
        uint32_t argumentSizes[sizeof...(TArgs)];

        size_t e2eHeaderLength = protector_->getE2EHeaderLength();
        size_t sampleSize      = e2eHeaderLength
                            + SerializationHelper::calculateSize(argumentSizes, serializerCarrier_.get(), args...);

        if (sampleSize + binding::SerializedSample::GetHeaderSize() > this->maxRequestSize_)
        {
            Logger::GetInstance().LogError()
                << this->readableComponentId_
                << " Serialized client data doesn't fit into allocated slots: " << sampleSize << " vs. "
                << (this->maxRequestSize_ - binding::SerializedSample::GetHeaderSize())
                << " Consider changing the size configuration for this method.\n";
            ara::core::Promise<MethodOutput_T> promise;
            // TODO: Check spec for correct error code!
            promise.SetError(ara::com::ComErrc::kCommunicationStackError);
            return promise.get_future();
        }

        auto samplePtr = this->methodClientImpl_.allocate();
        if (!samplePtr)
        {
            Logger::GetInstance().LogError()
                << this->readableComponentId_
                << " Could not allocate space for method call.  Configured maximum parallel messages are: "
                << this->methodClientImpl_.MaxSamples() << "\n";
            ara::core::Promise<MethodOutput_T> promise;
            promise.SetError(ara::com::ComErrc::kSampleAllocationFailure);
            return promise.get_future();
        }

        // The full packet will look like this (each part multiple bytes):
        // ARA :                [ E2E HEADER | SERIALIZED_PAYLOAD ]
        // PIPC: [ SAMPLE_SIZE  |         SAMPLE                  ]
        auto& sample = *reinterpret_cast<binding::SerializedSample*>(samplePtr.get());
        // HINT: Size was already checked before
        static_cast<void>(sample.resize(sampleSize));
        bool serializationOk = SerializationHelper::serializeArguments(sample.data() + e2eHeaderLength,
                                                                       0,
                                                                       argumentSizes,
                                                                       serializerCarrier_.get(),
                                                                       args...);

        if (!serializationOk)
        {
            Logger::GetInstance().LogError()
                << this->readableComponentId_ << " Serialization of call arguments failed.\n";
            ara::core::Promise<MethodOutput_T> promise;
            promise.SetError(ara::com::ComErrc::kCommunicationStackError);
            return promise.get_future();
        }

        // Apply end-to-end protection if required.
        typename BaseClass::RequestInfo requestInfo;
        e2e::ProtectStatus protectStatus = protector_->protect(e2e::MessageType::kRequest,
                                                               e2e::MessageResult::kOk,
                                                               requestInfo.e2eCounter,
                                                               sample.data(),
                                                               sample.size());
        ;

        // Abort if protect function didn't work ok and there is a profile configuration
        if (protectStatus != e2e::ProtectStatus::kOk && protectStatus != e2e::ProtectStatus::kProtectDisabled)
        {
            Logger::GetInstance().LogError()
                << this->readableComponentId_
                << " Protect function failed (protectStatus :" << static_cast<uint32_t>(protectStatus) << ")\n";
            // TODO: Check spec for correct error code!
            requestInfo.promise.SetError(ara::com::ComErrc::kCommunicationStackError);
            return requestInfo.promise.get_future();
        }

        // We already draw the lock here to avoid a race condition between sending and insertion in session map.
        // Adding the entry first is not possible, as we don't have the requestId yet.
        {
            std::lock_guard<std::mutex> lk(this->requestMapMutex_);
            pipc::rpc::RequestId requestId = 0;
            // TODO: Send called under lock, is this an issue?
            pipc::ReturnCode result = this->methodClientImpl_.sendRequest(std::move(samplePtr), requestId);

            if (EXPECT_UNLIKELY(result != pipc::ReturnCode::kOk))
            {
                Logger::GetInstance().LogError()
                    << this->readableComponentId_
                    << " Sending message failed with pipc error code: " << pipc::ToString(result) << "\n";
                requestInfo.promise.SetError(ara::com::ComErrc::kNetworkBindingFailure);
                return requestInfo.promise.get_future();
            }
            return this->insertInRequestMap(requestId, std::move(requestInfo));
        }
    }

protected:
    UniquePtr<serializer::ArgumentSerializerCarrier<sizeof...(TArgs), TArgs...>> serializerCarrier_;
    UniquePtr<e2e::IE2EProtector> protector_;
};

/**
 * @brief Specialization of serialized method client implementation for void inputs.
 *
 * @tparam MethodOutput_T  output arg type
 */
template<typename MethodOutput_T>
class MethodClientSerialized<MethodOutput_T, void> : public MethodClientSerializedBase<MethodOutput_T, void>
{
    static_assert(!std::is_polymorphic<MethodOutput_T>::value, "Polymorphic MethodOutput types not supported");
    static_assert(!std::is_void<MethodOutput_T>::value,
                  "Serialized Methods with void in and void out is not allowed. Please use methodClient instead.");

public:
    using BaseClass = MethodClientSerializedBase<MethodOutput_T, void>;
    template<typename T>
    using UniquePtr = ara::com::UniquePtr<T>;
    using Logger    = com::utils::Logger;

    /**
     * @brief Constructor.
     *
     * @param context       Service information (Deployment Context).
     * @param methodConfig  Configuration parameter pack.
     * @param deserializer  The deserializer for output deserialization. Can be left out for void outputs.
     * @param f_checker     The checker to check the arriving content. Checker with profile disabled can be used for
     * void outputs.
     */
    template<typename TContext, typename TMethodCfg>
    MethodClientSerialized(const TContext& context,
                           const TMethodCfg& methodConfig,
                           UniquePtr<serializer::IDeserializer<MethodOutput_T>>&& od = nullptr,
                           UniquePtr<e2e::IE2EChecker>&& f_checker                   = nullptr)
        : BaseClass(context, methodConfig, std::move(od), std::move(f_checker))
    {
    }

    ~MethodClientSerialized() = default;

    /**
     * @brief Implementation of the actual method call with void input.
     *
     * @return ara::core::Future<MethodOutput_T> A future to handle incoming responses.
     */
    ara::core::Future<MethodOutput_T> operator()()
    {
        auto samplePtr = this->methodClientImpl_.allocate();
        if (!samplePtr)
        {
            Logger::GetInstance().LogError()
                << this->readableComponentId_
                << " Could not allocate a slot for method call.  Configured maximum parallel messages are: "
                << this->methodClientImpl_.MaxSamples() << "\n";
            ara::core::Promise<MethodOutput_T> promise;
            promise.SetError(ara::com::ComErrc::kSampleAllocationFailure);
            return promise.get_future();
        }
        pipc::rpc::RequestId requestId;
        typename BaseClass::RequestInfo requestInfo;

        {
            std::lock_guard<std::mutex> lk(this->requestMapMutex_);
            pipc::ReturnCode result = this->methodClientImpl_.sendRequest(std::move(samplePtr), requestId);
            if (result != pipc::ReturnCode::kOk)
            {
                // Transmission error. Set NetworkBindingFailure and return.
                // Behavior described in SWS_CM_10440
                Logger::GetInstance().LogError()
                    << this->readableComponentId_
                    << " Sending message failed with pipc error code:" << pipc::ToString(result) << "\n";
                requestInfo.promise.SetError(ara::com::ComErrorDomain::Errc::kNetworkBindingFailure);
                return requestInfo.promise.get_future();
            }
            return this->insertInRequestMap(requestId, std::move(requestInfo));
        }
    }
};

} // namespace binding_pipc
} // namespace com

#endif // COM_BINDING_PIPC_METHODCLIENTSERIALIZED_HPP
