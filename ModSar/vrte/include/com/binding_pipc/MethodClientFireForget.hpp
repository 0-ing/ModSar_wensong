/// @copyright : 2022 Robert Bosch GmbH. All rights reserved.

#ifndef COM_BINDING_PIPC_METHODCLIENTFIREFORGET_HPP
#define COM_BINDING_PIPC_METHODCLIENTFIREFORGET_HPP

#include "ara/com/IProxyMethodFireForget.hpp"
#include "ara/com/types.h"
#include "binding_pipc/ProviderIdGenerator.hpp"
#include "config/ServiceIntfCfgStatic.hpp"
#include "pipc/rpc/ClientFireAndForget.hpp"
#include "pipc/rpc/LoanClientFireAndForget.hpp"
#include "utils/Logger.hpp"

namespace com
{
namespace binding_pipc
{
/**
 * @brief Method implementation for a F&F client.
 *
 * @todo
 * Pending requests need to be handled internally when the server goes offline,
 * in case of loan-based RPC also for F&F!
 * Function currently not used, requires config ctors and proper logging.
 */
template<typename... TArgs>
class MethodClientFireForget : public ara::com::IProxyMethodFireForget<TArgs...>
{
public:
    /**
     * @brief Constructor for Ipc & Some/Ip deployments.
     *
     * @param context
     * @param methodConfig
     */
    template<typename TContext, typename TMethodCfg>
    MethodClientFireForget(const TContext& context, const TMethodCfg& methodConfig)
        : methodClientImpl_(ProviderIdGenerator::Generate(context, methodConfig), pipc::sd::Runtime::GetInstance())
    {
    }

    /**
     * @brief Overloaded function call operator
     * Shall adhere to SWS_CM_90435.
     * As the underlying pipc implementation supports variadic template, call is just forwarded.
     * @param args The variadic template list of input arguments
     */
    virtual void operator()(const TArgs... args) override
    {
        pipc::loan::SamplePtr<std::tuple<TArgs...>> sample = methodClientImpl_.allocate();
        if (!sample)
        {
            utils::Logger::GetInstance().LogError()
                << "FF method with ID: " << methodClientImpl_.getProviderId().toString()
                << "Could not allocate space for method call. Probably too many messages in flight?"
                << "Configured maximum is: " << methodClientImpl_.MaxSamples();
            return;
        }
        *sample.get()        = std::move(args...);
        pipc::ReturnCode ret = methodClientImpl_.sendRequest(std::move(sample));
        if (ret != pipc::ReturnCode::kOk)
        {
            // Do not report error, but log a message.
            utils::Logger::GetInstance().LogError()
                << "MethodClientFireForget with ID: " << methodClientImpl_.getProviderId().toString()
                << " Sending failed with pipc return code: " << pipc::ToString(ret);
        }
    }

protected:
    pipc::rpc::LoanClientFireAndForget<std::tuple<TArgs...>> methodClientImpl_; ///< The implementation used.
};

/**
 * @brief Method implementation for a F&F client (void input specialization).
 */
template<>
class MethodClientFireForget<void> : public ara::com::IProxyMethodFireForget<>
{
public:
    /**
     * @brief Constructor for Ipc & Some/Ip deployments.
     *
     * @param context
     * @param methodConfig
     */
    template<typename TContext, typename TMethodCfg>
    MethodClientFireForget(const TContext& context, const TMethodCfg& methodConfig)
        : methodClientImpl_(ProviderIdGenerator::Generate(context, methodConfig), pipc::sd::Runtime::GetInstance())
    {
    }

    /**
     * @brief Overloaded function call operator
     *
     * Shall adhere to SWS_CM_90435.
     * As the underlying pipc implementation supports variadic template, call is just forwarded.
     *
     * @param args The variadic template list of input arguments
     */
    virtual void operator()() override
    {
        pipc::ReturnCode ret = methodClientImpl_.sendRequest();
        if (ret != pipc::ReturnCode::kOk)
        {
            // Do not report error, but log a message.
            utils::Logger::GetInstance().LogError()
                << "MethodClientFireForget with ID: " << methodClientImpl_.getProviderId().toString()
                << " Sending failed with pipc return code: " << pipc::ToString(ret);
        }
    }

protected:
    pipc::rpc::ClientFireAndForget<void> methodClientImpl_; ///< The implementation used.
};

} // namespace binding_pipc
} // namespace com

#endif // COM_BINDING_PIPC_METHODCLIENTFIREFORGET_HPP
