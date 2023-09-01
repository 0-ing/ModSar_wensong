/// @copyright : 2022 Robert Bosch GmbH. All rights reserved.

#ifndef COM_BINDING_PIPC_METHODSERVERFIREANDFORGET_HPP
#define COM_BINDING_PIPC_METHODSERVERFIREANDFORGET_HPP

#include "ara/com/ISkeletonMethod.hpp"
#include "binding/MethodQueue.hpp"
#include "binding_pipc/ProviderIdGenerator.hpp"
#include "com/Types.hpp"
#include "config/ServiceIntfCfgStatic.hpp"
#include "pipc/rpc/LoanServerFireAndForget.hpp"
#include "pipc/rpc/ServerFireAndForget.hpp"
#include "pipc/sd/Runtime.hpp"
#include "utils/Apply.hpp"

namespace com
{
namespace binding_pipc
{
/** @brief PipcFFServerSelector to get a loan-based RPC Server. */
template<typename... TArgs>
struct PipcFFServerSelector
{
    using Server = pipc::rpc::LoanServerFireAndForget<std::tuple<TArgs...>>;
};

/**
 * @brief PipcFFServerSelector to get a RPC Server without input.
 */
template<>
struct PipcFFServerSelector<>
{
    using Server = pipc::rpc::ServerFireAndForget<void>;
};

template<typename... TArgs>
class MethodServerFireForget : public ara::com::ISkeletonMethodFireForget<TArgs...>
{
public:
    /** \brief Declarations for readability and forwarding to derived classes */
    using Command      = pipc::utils::Command_1<void*, void>;
    using MethodCfgIpc = com::config::MethodCfgIpc;
    using MethodQueue  = binding::MethodQueue;
    using RequestTuple = std::tuple<TArgs...>;
    using PipcServer   = typename PipcFFServerSelector<TArgs...>::Server;
    using Method       = std::function<void(const TArgs&...)>;

    // Constructor for IPC deployment.
    MethodServerFireForget(const config::DeploymentContextIpc& context,
                           const MethodCfgIpc& methodConfig,
                           MethodQueue& methodQueue)
        : pipcServer_(ProviderIdGenerator::Generate(context, methodConfig), pipc::sd::Runtime::GetInstance()),
          method_(),
          methodQueue_(methodQueue)
    {
        registerExecutor();
        pipcServer_.registerRequestReceivedCallback([this]() {
            Command processCmd{&ProcessNextRequest, this};
            methodQueue_.addMethodInvocation(processCmd);
        });
    }

    // Constructor for Some/Ip deployment.
    MethodServerFireForget(const config::DeploymentContextSomeIp& context,
                           const config::MethodCfgSomeIp& methodConfig,
                           MethodQueue& methodQueue)
        : pipcServer_(ProviderIdGenerator::Generate(context, methodConfig), pipc::sd::Runtime::GetInstance()),
          method_(),
          methodQueue_(methodQueue)
    {
        static_assert(sizeof...(TArgs) == 0, "SomeIp Method with input arguments cannot be a non-serialized Method.");

        registerExecutor();
        pipcServer_.registerRequestReceivedCallback([this]() {
            Command processCmd{&ProcessNextRequest, this};
            methodQueue_.addMethodInvocation(processCmd);
        });
    }

    void RegisterProcessingFunction(std::function<void(const TArgs...)>&& f_func) override
    {
        method_ = f_func;
        // This is called once by the FTLs, so we can start offering after registration
        pipcServer_.startOffer();
    }

private:
    /**
     * @brief Register an executor
     *
     * @tparam N
     */
    template<size_t N = sizeof...(TArgs)>
    typename std::enable_if<(N > 0), void>::type registerExecutor()
    {
        pipcServer_.registerExecutor([this](const RequestTuple& requestData) { utils::Apply(method_, requestData); });
    }

    template<size_t N = sizeof...(TArgs)>
    typename std::enable_if<(N == 0), void>::type registerExecutor()
    {
        pipcServer_.registerExecutor([this]() { method_(); });
    }

    static void ProcessNextRequest(MethodServerFireForget* obj)
    {
        obj->processNextRequest();
    }

    void processNextRequest()
    {
        // Info whether more requests are present is taken from method queue
        static_cast<void>(pipcServer_.processNextRequest());
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

#endif // COM_BINDING_PIPC_METHODSERVERFIREANDFORGET_HPP
