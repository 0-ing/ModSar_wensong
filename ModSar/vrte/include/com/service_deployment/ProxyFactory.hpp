//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================
//
/// @file      ProxyFactory.hpp
/// @brief     Implementation of a Factory for Proxy objects
/// @copyright Robert Bosch GmbH 2021
/// @author    crg2fe
//=============================================================================

#ifndef COM_SERVICE_DEPLOYMENT_PROXY_FACTORY_HPP
#define COM_SERVICE_DEPLOYMENT_PROXY_FACTORY_HPP

/******************************************************
                CONFIGURATION INTERFACE
*******************************************************/
#include "config/IServiceIntfCfg.hpp"

/******************************************************
                FRONT-END CLASSES
*******************************************************/
#include "ara/com/ProxyEvent.hpp"
#include "ara/com/ProxyField.hpp"
#include "ara/com/ProxyMethod.hpp"
#include "ara/runtime.h"

/******************************************************
                IOX BINDING CLASSES
*******************************************************/
#include "binding_pipc/EventSubscriber.hpp"
#include "binding_pipc/EventSubscriberSerialized.hpp"
#include "binding_pipc/FieldSubscriberSerialized.hpp"
#include "binding_pipc/MethodClientFireForget.hpp"
#include "binding_pipc/MethodClientFireForgetSerialized.hpp"
#include "binding_pipc/MethodClientSerialized.hpp"
#include "binding_pipc/S2SEventSubscriber.hpp"

// Other includes
#include "pipc/sd/Runtime.hpp"
#include "sd/Runtime.hpp"

#include <string>
#include <utility>

namespace com
{
namespace service_deployment
{
/**
 * \brief Proxy Factory class
 *
 * The factory provides provides an entry method \see createObjects(...) for a templated
 * code generation mechanism, which creates all implementation objects for Events, Fields and Methods
 * of a Proxy.
 * We use parameter pack unrolling to distinguish between the different objects.
 * For each object to be generated, there exists a specific function overload,
 * which calls a corresponding object-specific create method.
 */
template<ara::com::NetworkBindingEnum NetworkBinding>
class ProxyFactory;

// select MethodClientFF serialized or normal (if no method input Args)
namespace method_selector
{
template<typename... TArgs>
struct ProxyMethodFireForgetImplSelector
{
    using MethodFireForgetImpl = binding_pipc::MethodClientFireForgetSerialized<TArgs...>;
};
template<>
struct ProxyMethodFireForgetImplSelector<>
{
    using MethodFireForgetImpl = binding_pipc::MethodClientFireForget<void>;
};
} // namespace method_selector
template<>
class ProxyFactory<ara::com::NetworkBindingEnum::SOME_IP>
{
    // Front-End classes
    template<typename T>
    using Event = ara::com::ProxyEvent<T>;
    template<typename... TArgs>
    using MethodFireForget = ara::com::ProxyMethodFireForget<TArgs...>;
    template<typename TMethodOutput, typename... TArgs>
    using Method = ara::com::ProxyMethod<TMethodOutput, TArgs...>;

    // switch to this implementation later
    // template<typename T, bool hasGetter, bool hasSetter, bool hasNotifier>
    // using Field = ara::com::ProxyField<T, hasGetter, hasSetter, hasNotifier>;
    template<typename T>
    using Field = ara::com::ProxyField<T>;

    // Binding classes
    // TODO: Template argument N (max number of subscribed samples) was previously 10.
    // It is now set to 11 to be backward compatible to the previous solution.
    // Internally we don't increment anymore, but users expect to create a cache of 10 samples
    // and still receive another one, as suggested in the COM EXP document.
    // TODO: How to configure the overall max value for this?
    template<typename T>
    using EventSerializedImpl = binding_pipc::EventSubscriberSerialized<11U, T>;
    template<typename T>
    using S2SEventImpl = binding_pipc::S2SEventSubscriber<11U, T>;
    template<typename TOutput, typename... TArgs>
    using MethodImpl = binding_pipc::MethodClientSerialized<TOutput, TArgs...>;
    template<typename... TArgs>
    using MethodFireForgetImpl =
        typename method_selector::ProxyMethodFireForgetImplSelector<TArgs...>::MethodFireForgetImpl;
    template<typename T>
    using FieldImpl = binding_pipc::FieldSubscriberSerialized<11U, T>;

    // Serializers
    template<typename T>
    using IDeserializer = com::serializer::IDeserializer<T>;
    template<typename T>
    using IS2SDeserializer = com::serializer::IS2SDeserializer<T>;
    template<int N, typename... Types>
    using Asc = com::serializer::ArgumentSerializerCarrier<N, Types...>;

    // E2E
    using IE2EProtector = com::e2e::IE2EProtector;
    using IE2EChecker   = com::e2e::IE2EChecker;

    // Other classes
    template<typename T>
    using UniquePtr = ara::com::UniquePtr<T>;

public:
    /** \brief Constructor, which takes the configuration object */
    ProxyFactory(const config::IServiceIntfCfgSomeIp& config_) : config(config_), context(config.getDeploymentContext())
    {
        processName = pipc::sd::Runtime::GetInstance().getProcessId();
        if (!processName.empty() && processName.front() == '/')
        {
            processName = processName.substr(1);
        }
    }

    /**
     * \brief Function to create the impl objects of a Proxy.
     *
     * The methods createObjects(...) takes a parameter pack with objects to
     * be created and provides one overload for each kind of impl object
     * that needs to be constructed.
     * This function is the 'tail function' for the end of the parameter pack.
     */
    inline void createObjects()
    {
    }

    /** \brief Parameter unrolling specialization for creating an Event. */
    template<typename Type, typename... TArgs>
    void createObjects(Event<Type>& event,
                       const char* const name,
                       UniquePtr<com::serializer::IDeserializer<Type>> deserializer,
                       UniquePtr<IE2EChecker> e2eChecker,
                       TArgs&&... args)
    {
        // Create the event
        const auto eventConfig = config.getEventConfig(name);
        event.pImpl            = std::make_unique<EventSerializedImpl<Type>>(context,
                                                                  eventConfig,
                                                                  std::move(deserializer),
                                                                  std::move(e2eChecker));

        // Get to the next object...
        createObjects(std::forward<TArgs>(args)...);
    }

    template<typename Type, typename... TArgs>
    void createObjects(Event<Type>& event,
                       const char* const name,
                       UniquePtr<IS2SDeserializer<Type>> deserializer,
                       com::s2s::S2SEventConfig&& s2sEventConfig,
                       std::vector<com::s2s::S2SE2ECheckerConfig> (
                           *getS2SE2ECheckerConfigs)(const InstanceIdentifier& f_instance, const uint32_t eventId),
                       TArgs&&... args)
    {
        // Create the event
        const auto eventConfig = config.getEventConfig(name);
        event.pImpl            = std::make_unique<S2SEventImpl<Type>>(context,
                                                           eventConfig,
                                                           std::move(deserializer),
                                                           std::move(s2sEventConfig),
                                                           getS2SE2ECheckerConfigs(context.instanceId,
                                                                                   eventConfig.eventId));
        // Get to the next object...
        createObjects(std::forward<TArgs>(args)...);
    }

    /** \brief Parameter unrolling specialization for a Method. */
    template<typename TMethodOutput, typename... TMethodArgs, typename... TArgs>
    void createObjects(Method<TMethodOutput, TMethodArgs...>& method,
                       const char* const name,
                       UniquePtr<Asc<sizeof...(TMethodArgs), TMethodArgs...>>&& asc,
                       UniquePtr<IDeserializer<TMethodOutput>>&& outputDeserializer,
                       IE2EProtector* (*getMethodProtector)(const InstanceIdentifier& f_instance,
                                                            const ara::core::String& methodName,
                                                            const ara::core::String& processName),
                       IE2EChecker* (*getMethodChecker)(const InstanceIdentifier& f_instance,
                                                        const ara::core::String& methodName,
                                                        const ara::core::String& processName),
                       TArgs&&... args)
    {
        // Create the method
        const auto methodConfig = config.getMethodConfig(name);
        method.pImpl            = std::make_unique<MethodImpl<TMethodOutput, TMethodArgs...>>(
            context,
            methodConfig,
            std::move(asc),
            UniquePtr<IE2EProtector>(getMethodProtector(context.instanceId, name, processName)),
            std::move(outputDeserializer),
            UniquePtr<IE2EChecker>(getMethodChecker(context.instanceId, name, processName)));

        // Get to the next object...
        createObjects(std::forward<TArgs>(args)...);
    }

    /** \brief Parameter unrolling specialization for a serialized Fire & Forget Method. */
    template<typename... TMethodArgs, typename... TArgs>
    void createObjects(MethodFireForget<TMethodArgs...>& method,
                       const char* const name,
                       UniquePtr<Asc<sizeof...(TMethodArgs), TMethodArgs...>>&& asc,
                       IE2EProtector* (*getMethodProtector)(const InstanceIdentifier& f_instance,
                                                            const ara::core::String& methodName,
                                                            const ara::core::String& processName),
                       TArgs&&... args)
    {
        // Create the method
        const auto methodConfig = config.getMethodConfig(name);
        method.pImpl            = std::make_unique<MethodFireForgetImpl<TMethodArgs...>>(context,
                                                                              methodConfig,
                                                                              std::move(asc),
                                                                              UniquePtr<IE2EProtector>(
                                                                                  getMethodProtector(context.instanceId,
                                                                                                     name,
                                                                                                     processName)));

        // Get to the next object...
        createObjects(std::forward<TArgs>(args)...);
    }

    /** \brief Parameter unrolling specialization for a non-serialized Fire & Forget Method. */
    template<typename... TMethodArgs, typename... TArgs>
    void createObjects(MethodFireForget<TMethodArgs...>& method, const char* const name, TArgs&&... args)
    {
        // Create the method
        const auto methodConfig = config.getMethodConfig(name);
        method.pImpl            = std::make_unique<MethodFireForgetImpl<>>(context, methodConfig);

        // Get to the next object...
        createObjects(std::forward<TArgs>(args)...);
    }

    /** \brief Parameter unrolling specialization for a Field. */
    // switch to this implementation later
    // template<typename T, bool hasGetter, bool hasSetter, bool hasNotifier, typename... TArgs>
    // void createObjects(Field<T, hasGetter, hasSetter, hasNotifier>& field,
    template<typename T, typename... TArgs>
    void createObjects(Field<T>& field,
                       const char* const name,
                       UniquePtr<IDeserializer<T>>&& eventDeserializer,
                       UniquePtr<IE2EChecker>&& e2eChecker,
                       UniquePtr<IDeserializer<T>>&& getterOutputDeserializer,
                       UniquePtr<IDeserializer<T>>&& setterOutputDeserializer,
                       UniquePtr<Asc<1, T>>&& setterAsc,
                       IE2EProtector* (*getMethodProtector)(const InstanceIdentifier& f_instance,
                                                            const ara::core::String& methodName,
                                                            const ara::core::String& processName),
                       IE2EChecker* (*getMethodChecker)(const InstanceIdentifier& f_instance,
                                                        const ara::core::String& methodName,
                                                        const ara::core::String& processName),
                       TArgs&&... args)
    {
        // Create the field
        const auto fieldConfig = config.getFieldConfig(name);
        UniquePtr<e2e::IE2EChecker> getterChecker;
        UniquePtr<e2e::IE2EChecker> setterChecker;
        UniquePtr<e2e::IE2EProtector> setterProtector;
        if (fieldConfig.getter.methodName != nullptr)
        {
            getterChecker.reset(getMethodChecker(context.instanceId, fieldConfig.getter.methodName, processName));
        }
        if (fieldConfig.setter.methodName != nullptr)
        {
            setterChecker.reset(getMethodChecker(context.instanceId, fieldConfig.setter.methodName, processName));
            setterProtector.reset(getMethodProtector(context.instanceId, fieldConfig.setter.methodName, processName));
        }
        field.pImpl = std::make_unique<FieldImpl<T>>(context,
                                                     fieldConfig,
                                                     std::move(eventDeserializer),
                                                     std::move(e2eChecker),
                                                     std::move(getterOutputDeserializer),
                                                     std::move(setterOutputDeserializer),
                                                     std::move(setterAsc),
                                                     std::move(getterChecker),
                                                     std::move(setterProtector),
                                                     std::move(setterChecker));

        // Get to the next object...
        createObjects(std::forward<TArgs>(args)...);
    }

private:
    const config::IServiceIntfCfgSomeIp& config;    ///< Configuration reader
    const config::DeploymentContextSomeIp& context; ///< Deployment context (buffered due to frequent access)
    ara::core::String processName;                  ///< Process Name
};

template<>
class ProxyFactory<ara::com::NetworkBindingEnum::IPC>
{
    // Front-End classes
    template<typename T>
    using Event = ara::com::ProxyEvent<T>;
    template<typename... TArgs>
    using MethodFireForget = ara::com::ProxyMethodFireForget<TArgs...>;
    template<typename TMethodOutput, typename... TArgs>
    using Method = ara::com::ProxyMethod<TMethodOutput, TArgs...>;
    // switch to this implementation later
    // template<typename T, bool hasGetter, bool hasSetter, bool hasNotifier>
    // using Field = ara::com::ProxyField<T, hasGetter, hasSetter, hasNotifier>;
    template<typename T>
    using Field = ara::com::ProxyField<T>;

    // Binding classes
    template<typename T>
    using EventImpl = binding_pipc::EventSubscriber<T>;
    template<typename T>
    using EventSerializedImpl = binding_pipc::EventSubscriberSerialized<10U, T>;
    // template<typename T>
    // using S2SEventImpl = binding_iox::S2SEventSubscriberIoxSerialized<10U, T>;
    template<typename TOutput, typename... TArgs>
    using MethodImpl = binding_pipc::MethodClientSerialized<TOutput, TArgs...>;
    template<typename... TArgs>
    using MethodFireForgetImpl =
        typename method_selector::ProxyMethodFireForgetImplSelector<TArgs...>::MethodFireForgetImpl;
    template<typename T>
    using FieldImpl = binding_pipc::FieldSubscriberSerialized<11U, T>;

    // Serializers
    template<typename T>
    using IDeserializer = com::serializer::IDeserializer<T>;
    template<typename T>
    using IS2SDeserializer = com::serializer::IS2SDeserializer<T>;
    template<int N, typename... Types>
    using Asc = com::serializer::ArgumentSerializerCarrier<N, Types...>;

    // E2E
    using IE2EProtector = com::e2e::IE2EProtector;
    using IE2EChecker   = com::e2e::IE2EChecker;

    // Other classes
    template<typename T>
    using UniquePtr = ara::com::UniquePtr<T>;

public:
    /** \brief Constructor, which takes the configuration object */
    ProxyFactory(const config::IServiceIntfCfgIpc& config_) : config(config_), context(config.getDeploymentContext())
    {
        processName = pipc::sd::Runtime::GetInstance().getProcessId();
        if (!processName.empty() && processName.front() == '/')
        {
            processName = processName.substr(1);
        }
    }

    /**
     * \brief Function to create the impl objects of a Proxy.
     *
     * The methods createObjects(...) takes a parameter pack with objects to
     * be created and provides one overload for each kind of impl object
     * that needs to be constructed.
     * This function is the 'tail function' for the end of the parameter pack.
     */
    inline void createObjects()
    {
    }

    /** \brief Parameter unrolling specialization for creating an Event. */
    template<typename Type, typename... TArgs>
    void createObjects(Event<Type>& event,
                       const char* const name,
                       UniquePtr<com::serializer::IDeserializer<Type>> deserializer,
                       UniquePtr<IE2EChecker> e2eChecker,
                       TArgs&&... args)
    {
        // Create the event
        const auto eventConfig = config.getEventConfig(name);

        if (eventConfig.useSerialization)
        {
            event.pImpl = std::make_unique<EventSerializedImpl<Type>>(context,
                                                                      eventConfig,
                                                                      std::move(deserializer),
                                                                      std::move(e2eChecker));
        }
        else
        {
            event.pImpl = std::make_unique<EventImpl<Type>>(context, eventConfig);
        }

        // Get to the next object...
        createObjects(std::forward<TArgs>(args)...);
    }

    template<typename Type, typename... TArgs>
    void createObjects(Event<Type>&,
                       const char* const,
                       UniquePtr<IS2SDeserializer<Type>>,
                       com::s2s::S2SEventConfig&&,
                       std::vector<com::s2s::S2SE2ECheckerConfig> (*)(const InstanceIdentifier& f_instance,
                                                                      const uint32_t eventId),
                       TArgs&&... args)
    {
        // We cannot have s2s events with ipc configuration.
        // This function is here to not have compiler errors

        // Get to the next object...
        createObjects(std::forward<TArgs>(args)...);
    }

    /** \brief Parameter unrolling specialization for a Method. */
    template<typename TMethodOutput, typename... TMethodArgs, typename... TArgs>
    void createObjects(Method<TMethodOutput, TMethodArgs...>& method,
                       const char* const name,
                       UniquePtr<Asc<sizeof...(TMethodArgs), TMethodArgs...>>&& asc,
                       UniquePtr<IDeserializer<TMethodOutput>>&& outputDeserializer,
                       IE2EProtector* (*getMethodProtector)(const InstanceIdentifier& f_instance,
                                                            const ara::core::String& methodName,
                                                            const ara::core::String& processName),
                       IE2EChecker* (*getMethodChecker)(const InstanceIdentifier& f_instance,
                                                        const ara::core::String& methodName,
                                                        const ara::core::String& processName),
                       TArgs&&... args)
    {
        // Create the method
        const auto methodConfig = config.getMethodConfig(name);
        method.pImpl            = std::make_unique<MethodImpl<TMethodOutput, TMethodArgs...>>(
            context,
            methodConfig,
            std::move(asc),
            UniquePtr<IE2EProtector>(getMethodProtector(context.instanceId, name, processName)),
            std::move(outputDeserializer),
            UniquePtr<IE2EChecker>(getMethodChecker(context.instanceId, name, processName)));

        // Get to the next object...
        createObjects(std::forward<TArgs>(args)...);
    }

    /** \brief Parameter unrolling specialization for a serialized Fire & Forget Method. */
    template<typename... TMethodArgs, typename... TArgs>
    void createObjects(MethodFireForget<TMethodArgs...>& method,
                       const char* const name,
                       UniquePtr<Asc<sizeof...(TMethodArgs), TMethodArgs...>>&& asc,
                       IE2EProtector* (*getMethodProtector)(const InstanceIdentifier& f_instance,
                                                            const ara::core::String& methodName,
                                                            const ara::core::String& processName),
                       TArgs&&... args)
    {
        // Create the method
        const auto methodConfig = config.getMethodConfig(name);
        method.pImpl            = std::make_unique<MethodFireForgetImpl<TMethodArgs...>>(context,
                                                                              methodConfig,
                                                                              std::move(asc),
                                                                              UniquePtr<IE2EProtector>(
                                                                                  getMethodProtector(context.instanceId,
                                                                                                     name,
                                                                                                     processName)));

        // Get to the next object...
        createObjects(std::forward<TArgs>(args)...);
    }

    /** \brief Parameter unrolling specialization for a non-serialized Fire & Forget Method. */
    template<typename... TMethodArgs, typename... TArgs>
    void createObjects(MethodFireForget<TMethodArgs...>& method, const char* const name, TArgs&&... args)
    {
        // Create the method
        const auto methodConfig = config.getMethodConfig(name);
        method.pImpl            = std::make_unique<MethodFireForgetImpl<>>(context, methodConfig);

        // Get to the next object...
        createObjects(std::forward<TArgs>(args)...);
    }

    /** \brief Parameter unrolling specialization for a Field. */
    // switch to this implementation later
    // template<typename T, bool hasGetter, bool hasSetter, bool hasNotifier, typename... TArgs>
    // void createObjects(Field<T, hasGetter, hasSetter, hasNotifier>& field,
    template<typename T, typename... TArgs>
    void createObjects(Field<T>& field,
                       const char* const name,
                       UniquePtr<IDeserializer<T>>&& eventDeserializer,
                       UniquePtr<IE2EChecker>&& e2eChecker,
                       UniquePtr<IDeserializer<T>>&& getterOutputDeserializer,
                       UniquePtr<IDeserializer<T>>&& setterOutputDeserializer,
                       UniquePtr<Asc<1, T>>&& setterAsc,
                       IE2EProtector* (*getMethodProtector)(const InstanceIdentifier& f_instance,
                                                            const ara::core::String& methodName,
                                                            const ara::core::String& processName),
                       IE2EChecker* (*getMethodChecker)(const InstanceIdentifier& f_instance,
                                                        const ara::core::String& methodName,
                                                        const ara::core::String& processName),
                       TArgs&&... args)
    {
        // Create the field
        const auto fieldConfig = config.getFieldConfig(name);
        UniquePtr<e2e::IE2EChecker> getterChecker;
        UniquePtr<e2e::IE2EChecker> setterChecker;
        UniquePtr<e2e::IE2EProtector> setterProtector;
        if (fieldConfig.getter.methodName != nullptr)
        {
            getterChecker.reset(getMethodChecker(context.instanceId, fieldConfig.getter.methodName, processName));
        }
        if (fieldConfig.setter.methodName != nullptr)
        {
            setterChecker.reset(getMethodChecker(context.instanceId, fieldConfig.setter.methodName, processName));
            setterProtector.reset(getMethodProtector(context.instanceId, fieldConfig.setter.methodName, processName));
        }
        field.pImpl = std::make_unique<FieldImpl<T>>(context,
                                                     fieldConfig,
                                                     std::move(eventDeserializer),
                                                     std::move(e2eChecker),
                                                     std::move(getterOutputDeserializer),
                                                     std::move(setterOutputDeserializer),
                                                     std::move(setterAsc),
                                                     std::move(getterChecker),
                                                     std::move(setterProtector),
                                                     std::move(setterChecker));

        // Get to the next object...
        createObjects(std::forward<TArgs>(args)...);
    }

private:
    const config::IServiceIntfCfgIpc& config;    ///< Configuration reader
    const config::DeploymentContextIpc& context; ///< Deployment context (buffered due to frequent access)
    ara::core::String processName;               ///< Process Name
};

} // namespace service_deployment
} // namespace com

#endif // COM_SERVICE_DEPLOYMENT_PROXY_FACTORY_HPP
