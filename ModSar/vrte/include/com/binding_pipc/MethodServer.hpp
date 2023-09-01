/// @copyright : 2022 Robert Bosch GmbH. All rights reserved.

#ifndef COM_BINDING_PIPC_METHODSERVER_HPP
#define COM_BINDING_PIPC_METHODSERVER_HPP

#include "MethodServerBase.hpp"
#include "ara/com/ISkeletonMethod.hpp"
#include "binding/MethodQueue.hpp"
#include "binding_pipc/ProviderIdGenerator.hpp"
#include "com/Types.hpp"
#include "config/ServiceIntfCfgStatic.hpp"
#include "pipc/sd/Runtime.hpp"
#include "utils/Apply.hpp"

namespace com
{
namespace binding_pipc
{
/**
 * @brief Class for implementing non-serialized method servers on top of pipc.
 *
 * @tparam TOutput The output data type of the method.
 * @tparam TArgs The input arguments of the method.
 */
template<typename TOutput, typename... TArgs>
class MethodServer : public MethodServerBase<TOutput>, public ara::com::ISkeletonMethod<TOutput, TArgs...>
{
public:
    /** \brief Declarations for readability and forwarding to derived classes */
    using PipcServer    = pipc::rpc::LoanServerBase<std::is_void<TOutput>::value, (sizeof...(TArgs) == 0)>;
    using PipcSessionId = pipc::session::SessionId;
    using CmdProcess    = pipc::utils::Command_1<void*, void>;
    using CmdDisconnect = pipc::utils::Command_1<void*, void, PipcSessionId>;
    using MethodCfgIpc  = com::config::MethodCfgIpc;
    using MethodQueue   = binding::MethodQueue;
    using RequestTuple  = std::tuple<TArgs...>;

    using Placeholder = pipc::utils::Placeholder;
    using Method      = typename ara::com::ISkeletonMethod<TOutput, TArgs...>::Method;

    /** @brief Constructor for IPC deployment. */
    MethodServer(const config::DeploymentContextIpc& context, const MethodCfgIpc& methodConfig, MethodQueue& methodQueue)
        : pipcServer_(ProviderIdGenerator::Generate(context, methodConfig),
                      pipc::sd::Runtime::GetInstance(),
                      sizeof(RequestTuple),
                      sizeof(TOutput)),
          method_(),
          methodQueue_(methodQueue)
    {
        pipcServer_.registerRequestReceivedCallback([this]() {
            CmdProcess processCmd{&ProcessNextRequest, this};
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
    static void OnDisconnectCbk(MethodServer* obj, pipc::session::SessionId sessionId)
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
    static void ProcessNextRequest(MethodServer* obj)
    {
        obj->processNextRequest();
    }

    /**
     * @brief Process the next request of the method server.
     */
    void processNextRequest()
    {
        typename PipcServer::RpcRequest request;
        std::pair<RequestTuple*, TOutput*> dataPtrs;
        {
            // TODO: Cannot invoke methods in parallel
            // Implement refCount pattern for userEndpoint in pipc to remove limitation
            std::unique_lock<std::mutex> lock(pipcServer_.getRequestMutex());
            if (pipcServer_.getNextPendingRequest(request, dataPtrs) == pipc::ReturnVal::kOk)
            {
                Future<TOutput> future = execute(dataPtrs);
                if (future.is_ready())
                {
                    bool valid = writeOutput(future, *dataPtrs.second);
                    pipcServer_.reply(request, valid);
                }
                else
                {
                    std::lock_guard<std::recursive_mutex> otherLock{this->pendingRepliesMutex_};
                    auto replyId      = this->addPendingReply(std::move(future), request, dataPtrs.second);
                    auto& movedFuture = this->pendingReplies_.back().future;
                    movedFuture.then([this, replyId](Future<TOutput> future) { processPendingReply(future, replyId); });
                }
            }
        }
    }

    /**
     * @brief Process a pending reply of a now-ready future.
     *
     * @param future The future, which has become ready.
     */
    inline void processPendingReply(Future<TOutput>& future, uint32_t replyId)
    {
        std::lock_guard<std::recursive_mutex> lock{this->pendingRepliesMutex_};
        for (auto it = this->pendingReplies_.begin(); it != this->pendingReplies_.end(); it++)
        {
            if (it->replyId == replyId)
            {
                auto outputPtr = reinterpret_cast<TOutput*>(it->outputPtr);
                bool valid     = writeOutput(future, *outputPtr);
                pipcServer_.reply(it->request, valid);
                this->pendingReplies_.erase(it);
                break;
            }
        }
    }

    /**
     * @brief Write the output of the future into shm.
     *
     * @param future Future containing the output.
     * @param output Reference to the output in shm.
     * @return true If the output was written successfuly,
     * @return false if not.
     */
    bool writeOutput(Future<TOutput>& future, TOutput& output)
    {
        auto result = future.GetResult();
        if (!result.HasValue())
        {
            return false;
        }
        output = result.Value();
        return true;
    }

    /** @brief Call method with a request. */
    template<bool VoidReq = (sizeof...(TArgs) == 0)>
    inline typename std::enable_if<!VoidReq, Future<TOutput>>::type execute(
        std::pair<RequestTuple*, TOutput*>& castDataPtrs)
    {
        return utils::Apply(method_, *castDataPtrs.first);
    }

    /** @brief Call method with a void request. */
    template<bool VoidReq = (sizeof...(TArgs) == 0)>
    inline typename std::enable_if<VoidReq, Future<TOutput>>::type execute(std::pair<RequestTuple*, TOutput*>&)
    {
        return method_();
    }

    /** @brief The pipc server object. */
    PipcServer pipcServer_;
    /** @brief The method to be called inside of the executor. */
    Method method_;
    /** @brief The method queue, which handles request processing. */
    MethodQueue& methodQueue_;
};

} // namespace binding_pipc
} // namespace com

#endif // COM_BINDING_PIPC_METHODSERVER_HPP
