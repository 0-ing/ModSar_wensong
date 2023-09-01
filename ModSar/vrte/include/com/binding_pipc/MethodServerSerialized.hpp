/// @copyright : 2022 Robert Bosch GmbH. All rights reserved.

#ifndef COM_BINDING_PIPC_METHODSERVERSERIALIZED_HPP
#define COM_BINDING_PIPC_METHODSERVERSERIALIZED_HPP

#include "MethodServerBase.hpp"
#include "ara/com/ISkeletonMethod.hpp"
#include "binding/CallerClassSerialized.hpp"
#include "binding/MethodQueue.hpp"
#include "binding/ReadableComponentIdentifier.hpp"
#include "binding/SerializedSample.hpp"
#include "binding_pipc/ProviderIdGenerator.hpp"
#include "com/Types.hpp"
#include "config/ServiceIntfCfgStatic.hpp"
#include "e2e/IE2EChecker.hpp"
#include "e2e/IE2EProtector.hpp"
#include "pipc/sd/Runtime.hpp"
#include "serializer/ArgumentDeserializerCarrier.hpp"
#include "serializer/ISerializer.hpp"
#include "utils/Logger.hpp"

namespace com
{
namespace binding_pipc
{
template<typename TOutput, typename... TArgs>
class MethodServerSerialized : public MethodServerBase<TOutput>, public ara::com::ISkeletonMethod<TOutput, TArgs...>
{
public:
    /** \brief Declarations for readability and forwarding to derived classes */
    using Command               = pipc::utils::Command_1<void*, void>;
    using RequestTuple          = std::tuple<TArgs...>;
    using PipcServer            = pipc::rpc::LoanServerBase<std::is_void<TOutput>::value, (sizeof...(TArgs) == 0)>;
    using Placeholder           = pipc::utils::Placeholder;
    using Method                = typename ara::com::ISkeletonMethod<TOutput, TArgs...>::Method;
    using MethodQueue           = binding::MethodQueue;
    using E2EResult             = ara::com::e2e::Result;
    using E2EProfileCheckStatus = ara::com::e2e::ProfileCheckStatus;
    using Logger                = com::utils::Logger;

    /** @brief Templated constructor for both deployment types. */
    template<typename TContext, typename TConfig>
    MethodServerSerialized(
        const TContext& context,
        const TConfig& methodConfig,
        MethodQueue& methodQueue,
        UniquePtr<serializer::ArgumentDeserializerCarrier<sizeof...(TArgs), TArgs...>>&& argDeserializers,
        UniquePtr<e2e::IE2EChecker>&& argsChecker,
        UniquePtr<serializer::ISerializer<TOutput>> outputSerializer,
        UniquePtr<e2e::IE2EProtector>&& outputProtector)
        : method_(),
          methodQueue_(methodQueue),
          argDeserializers_(std::move(argDeserializers)),
          argsChecker_(std::move(argsChecker)),
          outputSerializer_(std::move(outputSerializer)),
          outputProtector_(std::move(outputProtector)),
          maxRequestSize_(methodConfig.requestMaxSerializationSize + binding::SerializedSample::GetHeaderSize()),
          maxReplySize_(methodConfig.responseMaxSerializationSize + binding::SerializedSample::GetHeaderSize()),
          pipcServer_(ProviderIdGenerator::Generate(context, methodConfig),
                      pipc::sd::Runtime::GetInstance(),
                      maxRequestSize_ + maxReplySize_,
                      maxRequestSize_),
          readableComponentId_{context, methodConfig.methodName}
    {
        pipcServer_.registerRequestReceivedCallback([this]() {
            Command processCmd{&ProcessNextRequest, this};
            methodQueue_.addMethodInvocation(processCmd);
        });
        pipcServer_.overrideCmdOnDisconnect(&OnDisconnectCbk, this);
    }

    /**
     * @brief Register a processing function.
     *
     * @param method The method to be called for processing.
     */
    void RegisterProcessingFunction(Method&& method) override
    {
        method_ = method;
        // This is called once by the FTLs, so we can start offering after registration
        pipcServer_.startOffer();
    }

private:
    /** @brief Static function wrapper for onDisconnectCbk. */
    static void OnDisconnectCbk(MethodServerSerialized* obj, pipc::session::SessionId sessionId)
    {
        obj->onDisconnectCbk(sessionId);
    }

    /**
     * @brief Process a disconnect of a client.
     *
     * @param sessionId The session id of the disconnected client.
     */
    void onDisconnectCbk(pipc::session::SessionId sessionId)
    {
        this->invalidatePendingReplies(sessionId);
        pipcServer_.invalidatePendingRequests(sessionId);
    }

    /** @brief Static function wrapper for processNextRequest. */
    static void ProcessNextRequest(MethodServerSerialized* obj)
    {
        obj->processNextRequest();
    }

    /**
     * @brief Process the next request of the method server.
     */
    void processNextRequest()
    {
        typename PipcServer::RpcRequest request;
        std::pair<binding::SerializedSample*, binding::SerializedSample*> dataPtrs;
        {
            // TODO: Cannot invoke methods in parallel
            // Implement refCount pattern for userEndpoint in pipc to remove limitation
            std::unique_lock<std::mutex> lock(pipcServer_.getRequestMutex());
            if (pipcServer_.getNextPendingRequest(request, dataPtrs) == pipc::ReturnVal::kOk)
            {
                uint32_t dataId{0};
                uint32_t sourceId{0};
                uint32_t messageCounter{0};
                E2EResult checkResult = argsChecker_->check(e2e::MessageType::kRequest,
                                                            e2e::MessageResult::kOk,
                                                            dataId,
                                                            sourceId,
                                                            messageCounter,
                                                            dataPtrs.first->data(),
                                                            dataPtrs.first->size());

                if (checkResult.checkStatus != E2EProfileCheckStatus::kOk
                    && checkResult.checkStatus != E2EProfileCheckStatus::kCheckDisabled)
                {
                    Logger::GetInstance().LogError()
                        << readableComponentId_
                        << "E2E check failed with error: " << static_cast<uint32_t>(checkResult.checkStatus);
                    methodQueue_.invokeE2EErrorHandler(checkResult.checkStatus, dataId, messageCounter);
                    // TODO: Serialize(?) and protect the E2E error response
                    pipcServer_.reply(request, false);
                    return;
                }
                binding::CallerClassSerialized<TOutput, TArgs...> callerc;
                uint32_t deserializeStart = static_cast<uint32_t>(argsChecker_->getE2EHeaderLength());
                Future<TOutput> future    = callerc.callerfunction(method_,
                                                                deserializeStart,
                                                                *dataPtrs.first,
                                                                argDeserializers_.get());
                if (!future.valid())
                {
                    Logger::GetInstance().LogError()
                        << readableComponentId_
                        << " Deserialization error or method caller function has not returned a valid future!\n";
                    pipcServer_.reply(request, false);
                    return;
                }
                // PIPC_LOG_ERROR() << "CHECKING IF FUTURE IS READY..." << std::endl;
                if (future.is_ready())
                {
                    // PIPC_LOG_ERROR() << "FUTURE READY, WRITING OUTPUT..." << std::endl;
                    auto validReply = writeOutput(sourceId, messageCounter, future, *dataPtrs.second);
                    pipcServer_.reply(request, validReply);
                }
                else
                {
                    // PIPC_LOG_ERROR() << "MOVING TO PENDING REPLIES..." << std::endl;
                    std::lock_guard<std::recursive_mutex> otherLock{this->pendingRepliesMutex_};
                    auto replyId      = this->addPendingReply(std::move(future), request, dataPtrs.second);
                    auto& movedFuture = this->pendingReplies_.back().future;
                    movedFuture.then([this, replyId, sourceId, messageCounter](Future<TOutput> future) {
                        processPendingReply(future, replyId, sourceId, messageCounter);
                    });
                }
            }
        }
    }

    /**
     * @brief Process a pending reply of a now-ready future.
     *
     * @param future The future, which has become ready.
     */
    inline void processPendingReply(Future<TOutput>& future,
                                    uint32_t replyId,
                                    uint32_t sourceId,
                                    uint32_t messageCounter)
    {
        std::lock_guard<std::recursive_mutex> lock{this->pendingRepliesMutex_};
        for (auto it = this->pendingReplies_.begin(); it != this->pendingReplies_.end(); it++)
        {
            if (it->replyId == replyId)
            {
                auto outputPtr  = reinterpret_cast<binding::SerializedSample*>(it->outputPtr);
                auto validReply = writeOutput(sourceId, messageCounter, future, *outputPtr);
                pipcServer_.reply(it->request, validReply);
                this->pendingReplies_.erase(it);
                break;
            }
        }
    }

    /**
     * @brief Write the output of the future into shm.
     *
     * @param sourceId Value from the E2E check.
     * @param messageCounter Value from the E2E check.
     * @param future Future containing the output.
     * @param serializedOutput Reference to the output in shm.
     * @return true If the output was written successfuly,
     * @return false if not.
     */
    bool writeOutput(uint32_t sourceId,
                     uint32_t messageCounter,
                     Future<TOutput>& future,
                     binding::SerializedSample& serializedOutput)
    {
        auto result = future.GetResult();
        if (!result.HasValue())
        {
            return false;
        }
        auto& output            = result.Value();
        uint32_t outputSize     = outputSerializer_->computeSerializedSize(&output);
        uint32_t serializeStart = static_cast<uint32_t>(outputProtector_->getE2EHeaderLength());
        uint32_t totalSize      = outputSize + serializeStart;
        if (!serializedOutput.resize(totalSize, maxReplySize_ - binding::SerializedSample::GetHeaderSize()))
        {
            Logger::GetInstance().LogError()
                << readableComponentId_
                << " Cannot serialize method output into shared memory!\n"
                   "Required "
                << totalSize << ", configured " << maxReplySize_ << ".\nConsider increasing sample size.\n";
            return false;
        }
        if (!outputSerializer_->serialize(serializedOutput.data() + serializeStart, outputSize, &output))
        {
            // Errors printed by generated serializers
            return false;
        }
        e2e::ProtectStatus protectStatus = outputProtector_->protect(e2e::MessageType::kResponse,
                                                                     e2e::MessageResult::kOk,
                                                                     sourceId,
                                                                     messageCounter,
                                                                     serializedOutput.data(),
                                                                     serializedOutput.size());
        if (protectStatus != e2e::ProtectStatus::kOk && protectStatus != e2e::ProtectStatus::kProtectDisabled)
        {
            // TODO: How can a protect fail, if the check was successful?
            Logger::GetInstance().LogError()
                << readableComponentId_ << " Protect function for method response failed (protectStatus :"
                << static_cast<uint32_t>(protectStatus) << ")\n";
            return false;
        }
        return true;
    }

    /** @brief The method to be called inside of the executor. */
    Method method_;
    /** @brief The method queue, which handles request processing. */
    MethodQueue& methodQueue_;
    /** @brief The argument deserializers. */
    UniquePtr<serializer::ArgumentDeserializerCarrier<sizeof...(TArgs), TArgs...>> argDeserializers_;
    /** @brief The E2E checker for the serialized arguments. */
    UniquePtr<e2e::IE2EChecker> argsChecker_;
    /** @brief The output serializer. */
    UniquePtr<serializer::ISerializer<TOutput>> outputSerializer_;
    /** @brief The E2E protector for the method output. */
    UniquePtr<e2e::IE2EProtector> outputProtector_;
    /** @brief Max size of the request message. */
    size_t maxRequestSize_;
    /** @brief Max size of the reply message. */
    size_t maxReplySize_;
    /** @brief The pipc server object. */
    PipcServer pipcServer_;
    /** @brief Identifier for human-friendly printouts. */
    binding::ReadableComponentIdentifier readableComponentId_;
};

} // namespace binding_pipc
} // namespace com

#endif // COM_BINDING_PIPC_METHODSERVERSERIALIZED_HPP
