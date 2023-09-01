/// @copyright : 2022 Robert Bosch GmbH. All rights reserved.

#ifndef COM_BINDING_PIPC_METHODSERVERFIREFORGETSERIALIZED_HPP
#define COM_BINDING_PIPC_METHODSERVERFIREFORGETSERIALIZED_HPP

#include "ara/com/ISkeletonMethod.hpp"
#include "binding/CallerClassFireForgetSerialized.hpp"
#include "binding/MethodQueue.hpp"
#include "binding_pipc/ProviderIdGenerator.hpp"
#include "com/Types.hpp"
#include "config/ServiceIntfCfgStatic.hpp"
#include "e2e/IE2EChecker.hpp"
#include "pipc/rpc/LoanServerFireAndForgetUntyped.hpp"
#include "pipc/sd/Runtime.hpp"
#include "serializer/ArgumentDeserializerCarrier.hpp"
#include "utils/Apply.hpp"

namespace com
{
namespace binding_pipc
{
template<typename... TArgs>
class MethodServerFireForgetSerialized : public ara::com::ISkeletonMethodFireForget<TArgs...>
{
    static_assert(sizeof...(TArgs) > 0, "FF Method with no input arguments cannot be a serialized FF Method.");

public:
    /** \brief Declarations for readability and forwarding to derived classes */
    using Command               = pipc::utils::Command_1<void*, void>;
    using ComErrc               = ara::com::ComErrc;
    using MethodQueue           = binding::MethodQueue;
    using RequestTuple          = std::tuple<TArgs...>;
    using PipcServer            = pipc::rpc::LoanServerFireAndForgetUntyped<>;
    using Placeholder           = pipc::utils::Placeholder;
    using Method                = std::function<void(const TArgs&...)>;
    using E2EResult             = ara::com::e2e::Result;
    using E2EProfileCheckStatus = ara::com::e2e::ProfileCheckStatus;

    /** @brief Constructor for IPC deployment. */
    MethodServerFireForgetSerialized(
        const config::DeploymentContextIpc& context,
        const config::MethodCfgIpc& methodCfg,
        MethodQueue& methodQueue,
        UniquePtr<serializer::ArgumentDeserializerCarrier<sizeof...(TArgs), TArgs...>>&& argDeserializers,
        UniquePtr<e2e::IE2EChecker>&& argsChecker)
        : method_(),
          methodQueue_(methodQueue),
          argDeserializers_(std::move(argDeserializers)),
          argsChecker_(std::move(argsChecker)),
          pipcServer_(ProviderIdGenerator::Generate(context, methodCfg),
                      pipc::sd::Runtime::GetInstance(),
                      methodCfg.requestMaxSerializationSize + binding::SerializedSample::GetHeaderSize())
    {
        pipcServer_.registerExecutor([this](const Placeholder& requestData) { execute(requestData); });
        pipcServer_.registerRequestReceivedCallback([this]() {
            Command processCmd{&ProcessNextRequest, this};
            methodQueue_.addMethodInvocation(processCmd);
        });
    }

    /** @brief Constructor for Some/Ip deployment. */
    MethodServerFireForgetSerialized(
        const config::DeploymentContextSomeIp& context,
        const config::MethodCfgSomeIp& methodCfg,
        MethodQueue& methodQueue,
        UniquePtr<serializer::ArgumentDeserializerCarrier<sizeof...(TArgs), TArgs...>>&& argDeserializers,
        UniquePtr<e2e::IE2EChecker>&& argsChecker)
        : method_(),
          methodQueue_(methodQueue),
          argDeserializers_(std::move(argDeserializers)),
          argsChecker_(std::move(argsChecker)),
          pipcServer_(ProviderIdGenerator::Generate(context, methodCfg),
                      pipc::sd::Runtime::GetInstance(),
                      methodCfg.requestMaxSerializationSize + binding::SerializedSample::GetHeaderSize())
    {
        pipcServer_.registerExecutor([this](const Placeholder& requestData) { execute(requestData); });
        pipcServer_.registerRequestReceivedCallback([this]() {
            Command processCmd{&ProcessNextRequest, this};
            methodQueue_.addMethodInvocation(processCmd);
        });
    }

    void RegisterProcessingFunction(std::function<void(const TArgs...)>&& method) override
    {
        method_ = method;
        // This is called once by the FTLs, so we can start offering after registration
        pipcServer_.startOffer();
    }

private:
    static void ProcessNextRequest(MethodServerFireForgetSerialized* obj)
    {
        obj->processNextRequest();
    }

    void processNextRequest()
    {
        // Info whether more requests are present is taken from method queue
        static_cast<void>(pipcServer_.processNextRequest());
    }

    void execute(const Placeholder& requestData)
    {
        const binding::SerializedSample& requestSample = *reinterpret_cast<const binding::SerializedSample*>(
            &requestData);
        uint32_t dataId{0};
        uint32_t sourceId{0};
        uint32_t message_counter{0};
        E2EResult checkResult = argsChecker_->check(e2e::MessageType::kRequest,
                                                    e2e::MessageResult::kOk,
                                                    dataId,
                                                    sourceId,
                                                    message_counter,
                                                    requestSample.data(),
                                                    requestSample.size());
        if (checkResult.checkStatus == E2EProfileCheckStatus::kOk
            || checkResult.checkStatus == E2EProfileCheckStatus::kCheckDisabled)
        {
            binding::CallerClassFireForgetSerialized<TArgs...> callerc;
            uint32_t deserializeStart = static_cast<uint32_t>(argsChecker_->getE2EHeaderLength());
            callerc.callerfunction(method_, deserializeStart, requestSample, argDeserializers_.get());
            return;
        }
        methodQueue_.invokeE2EErrorHandler(checkResult.checkStatus, dataId, message_counter);
    }

    /** @brief The method to be called inside of the executor. */
    Method method_;
    /** @brief The method queue, which handles request processing. */
    MethodQueue& methodQueue_;
    /** @brief The argument deserializers. */
    UniquePtr<serializer::ArgumentDeserializerCarrier<sizeof...(TArgs), TArgs...>> argDeserializers_;
    /** @brief The E2E checker for the serialized arguments. */
    UniquePtr<e2e::IE2EChecker> argsChecker_;
    /** @brief The pipc server object. */
    PipcServer pipcServer_;
};

} // namespace binding_pipc
} // namespace com

#endif // COM_BINDING_PIPC_METHODSERVERFIREFORGETSERIALIZED_HPP
