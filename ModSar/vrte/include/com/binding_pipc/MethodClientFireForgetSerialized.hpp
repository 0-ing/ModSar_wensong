/// @copyright : 2022 Robert Bosch GmbH. All rights reserved.

#ifndef COM_BINDING_PIPC_METHODCLIENTFIREFORGETSERIALIZED_HPP
#define COM_BINDING_PIPC_METHODCLIENTFIREFORGETSERIALIZED_HPP

#include "ara/com/IProxyMethodFireForget.hpp"
#include "ara/com/com_error_domain.h"
#include "ara/com/types.h"
#include "binding/SerializedSample.hpp"
#include "binding_pipc/MethodArgumentSerializationHelper.hpp"
#include "binding_pipc/ProviderIdGenerator.hpp"
#include "binding/ReadableComponentIdentifier.hpp"
#include "config/IServiceIntfCfg.hpp"
#include "e2e/IE2EProtector.hpp"
#include "pipc/rpc/LoanClientFireAndForgetUntyped.hpp"
#include "pipc/sd/Runtime.hpp"
#include "serializer/ArgumentSerializerCarrier.hpp"
#include "serializer/IDeserializer.hpp"
#include "serializer/ISerializer.hpp"
#include "utils/Logger.hpp"

namespace com
{
namespace binding_pipc
{
/**
 * @brief Method client variant for serialized FF methods
 *
 * This class shall not be used with void input, but MethodClientFireForget instead.
 *
 * @tparam TArgs Variadic template argument for the input args.
 *
 * @todo
 * Pending requests need to be handled internally when the server goes offline,
 * in case of loan-based RPC also for F&F!
 */
template<typename... TArgs>
class MethodClientFireForgetSerialized : public ara::com::IProxyMethodFireForget<TArgs...>
{
    static_assert(sizeof...(TArgs) > 0, "FF Method with no input arguments cannot be a serialized FF Method.");

public:
    /** \brief Declarations for readability and forwarding to derived classes */
    template<typename T>
    using UniquePtr     = ara::com::UniquePtr<T>;
    using ComErrc       = ara::com::ComErrc;
    using IE2EProtector = ::com::e2e::IE2EProtector;
    using Logger        = com::utils::Logger;

    /**
     * @brief Construct a new Method Client Fire Forget Serialized object for an IPC deployment
     *
     * @param baseId        Service information in the form of a pipc provider ID.
     * @param methodConfig  Configuration parameter pack
     * @param asc           Serializer pack used for sending
     * @param f_protector   protector for E2E protection.
     */
    MethodClientFireForgetSerialized(const config::DeploymentContextIpc& context,
                                     const config::MethodCfgIpc& methodConfig,
                                     UniquePtr<serializer::ArgumentSerializerCarrier<sizeof...(TArgs), TArgs...>>&& asc,
                                     UniquePtr<IE2EProtector>&& f_protector)
        : maxRequestSize_(methodConfig.requestMaxSerializationSize + binding::SerializedSample::GetHeaderSize()),
          methodClientImpl_(ProviderIdGenerator::Generate(context, methodConfig),
                            pipc::sd::Runtime::GetInstance(),
                            maxRequestSize_),
          serializerCarrier_(std::move(asc)),
          protector_(std::move(f_protector)),
          readableComponentId_{context, methodConfig.methodName}
    {
    }

    /**
     * @brief Construct a new Method Client Fire Forget Serialized object for a "SOME/IP" deployment
     *
     * @param baseId        Service information in the form of a pipc provider ID.
     * @param methodConfig  Configuration parameter pack
     * @param asc           Serialier pack used for sending
     * @param f_protector   protector for E2E protection.
     */
    MethodClientFireForgetSerialized(const config::DeploymentContextSomeIp& context,
                                     const config::MethodCfgSomeIp& methodConfig,
                                     UniquePtr<serializer::ArgumentSerializerCarrier<sizeof...(TArgs), TArgs...>>&& asc,
                                     UniquePtr<IE2EProtector>&& f_protector)
        : maxRequestSize_(methodConfig.requestMaxSerializationSize + binding::SerializedSample::GetHeaderSize()),
          methodClientImpl_(ProviderIdGenerator::Generate(context, methodConfig),
                            pipc::sd::Runtime::GetInstance(),
                            maxRequestSize_),
          serializerCarrier_(std::move(asc)),
          protector_(std::move(f_protector)),
          readableComponentId_{context, methodConfig.methodName}
    {
    }

    /**
     * @brief Implementation of the actual method call for serialized data.
     *
     * @param args The input arguments as specified by the user.
     */
    void operator()(const TArgs... args)
    {
        using SerializationHelper = MethodArgumentSerializationHelper<sizeof...(TArgs), sizeof...(TArgs), TArgs...>;
        // calculate the serialized size of the arguments:
        uint32_t argumentSizes[sizeof...(TArgs)];

        size_t e2eHeaderLength = protector_->getE2EHeaderLength();
        size_t sampleSize      = e2eHeaderLength
                            + SerializationHelper::calculateSize(argumentSizes, serializerCarrier_.get(), args...);

        if (sampleSize + binding::SerializedSample::GetHeaderSize() > maxRequestSize_)
        {
            Logger::GetInstance().LogError()
                << this->readableComponentId_
                << " Serialized client data doesn't fit into allocated slots: " << sampleSize << " vs. "
                << (maxRequestSize_ - binding::SerializedSample::GetHeaderSize())
                << "Consider changing the size configuration for this method.\n";
            return;
        }

        auto samplePtr = methodClientImpl_.allocate();
        if (!samplePtr)
        {
            Logger::GetInstance().LogError()
                << this->readableComponentId_
                << " Could not allocate space for method call. Configured maximum parallel messages are: "
                << methodClientImpl_.MaxSamples();
            return;
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
            return;
        }

        // Apply end-to-end protection if required.
        uint32_t e2eCounter{0};
        e2e::ProtectStatus protectStatus = protector_->protect(e2e::MessageType::kRequest,
                                                               e2e::MessageResult::kOk,
                                                               e2eCounter,
                                                               sample.data(),
                                                               sample.size());

        // The method will be sent only if protect function worked ok or if there is no profile configuration
        if (protectStatus != e2e::ProtectStatus::kOk && protectStatus != e2e::ProtectStatus::kProtectDisabled)
        {
            Logger::GetInstance().LogError()
                << this->readableComponentId_
                << " Protect function failed (protectStatus :" << static_cast<uint32_t>(protectStatus) << ")\n";
            return;
        }

        pipc::ReturnCode result = methodClientImpl_.sendRequest(std::move(samplePtr));

        if (result != pipc::ReturnCode::kOk)
        {
            Logger::GetInstance().LogError()
                << this->readableComponentId_
                << " Sending message failed with pipc error code: " << pipc::ToString(result) << "\n";
        }

        // TODO:Double check need for init call of LoanClient. When to do this?
    }

protected:
    size_t maxRequestSize_;                                        ///< Stored maximum size of the request.
    pipc::rpc::LoanClientFireAndForgetUntyped<> methodClientImpl_; ///< The underlying pipc method client implementation.
    UniquePtr<serializer::ArgumentSerializerCarrier<sizeof...(TArgs), TArgs...>> serializerCarrier_; ///< Serializer pack
    UniquePtr<IE2EProtector> protector_;                                                             ///< E2E protector
    binding::ReadableComponentIdentifier readableComponentId_; ///< Identifier for human-readable printouts
};
} // namespace binding_pipc
} // namespace com

#endif // COM_BINDING_PIPC_METHODCLIENTFIREFORGETSERIALIZED_HPP
