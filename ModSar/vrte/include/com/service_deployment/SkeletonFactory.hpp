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
/// @file      SkeletonFactory.hpp
/// @brief     Implementation of a Factory for Skeleton objects
/// @copyright Robert Bosch GmbH 2021
/// @author    crg2fe
//=============================================================================

#ifndef COM_SERVICE_DEPLOYMENT_SKELETON_FACTORY_HPP
#define COM_SERVICE_DEPLOYMENT_SKELETON_FACTORY_HPP

/******************************************************
                CONFIGURATION INTERFACE
*******************************************************/
#include "config/IServiceIntfCfg.hpp"

/******************************************************
                FRONT-END CLASSES
*******************************************************/
#include "ara/com/SkeletonEvent.hpp"
#include "ara/com/SkeletonField.hpp"
#include "ara/com/SkeletonMethod.hpp"
#include "ara/runtime.h"

/******************************************************
                PIPC BINDING CLASSES
*******************************************************/
#include "binding_pipc/EventPublisher.hpp"
#include "binding_pipc/EventPublisherSerialized.hpp"
#include "binding_pipc/FieldPublisherSerialized.hpp"
#include "binding_pipc/MethodServerFireForget.hpp"
#include "binding_pipc/MethodServerFireForgetSerialized.hpp"
#include "binding_pipc/MethodServerSerialized.hpp"
#include "binding_pipc/S2SEventPublisher.hpp"

// Other includes
#include "sd/Runtime.hpp"

#include <string>
#include <utility>

namespace com
{
namespace service_deployment
{
/**
 * \brief Skeleton Factory class
 *
 * The factory provides provides an entry method \see createObjects(...) for a templated
 * code generation mechanism, which creates all implementation objects for Events, Fields and Methods
 * of a Skeleton.
 * We use parameter pack unrolling to distinguish between the different objects.
 * For each object to be generated, there exists a specific function overload,
 * which calls a corresponding object-specific create method.
 */
template<ara::com::NetworkBindingEnum NetworkBinding>
class SkeletonFactory;
// select MethodServerFF serialized or normal (if no method input Args)
namespace method_selector
{
template<typename... TArgs>
struct SkeletonMethodFireForgetImplSelector
{
    using MethodFireForgetImpl = binding_pipc::MethodServerFireForgetSerialized<TArgs...>;
};
template<>
struct SkeletonMethodFireForgetImplSelector<>
{
    using MethodFireForgetImpl = binding_pipc::MethodServerFireForget<>;
};
} // namespace method_selector

template<>
class SkeletonFactory<ara::com::NetworkBindingEnum::SOME_IP>
{
    // Front-End classes
    template<typename T>
    using Event = ara::com::SkeletonEvent<T>;
    template<typename T>
    using S2SEventImpl = binding_pipc::S2SEventPublisher<1U, T>;
    template<typename... TArgs>
    using MethodFireForget = ara::com::SkeletonMethodFireForget<TArgs...>;
    template<typename TMethodOutput, typename... TArgs>
    using Method = ara::com::SkeletonMethod<TMethodOutput, TArgs...>;
    // switch to this implementation later
    // template<typename T, bool hasGetter, bool hasSetter, bool hasNotifier>
    // using Field = ara::com::SkeletonField<T, hasGetter, hasSetter, hasNotifier>;
    template<typename T>
    using Field = ara::com::SkeletonField<T>;

    // Binding classes
    template<typename T>
    using EventSerializedImpl = binding_pipc::EventPublisherSerialized<1U, T>;
    template<typename TOutput, typename... TArgs>
    using MethodImpl = binding_pipc::MethodServerSerialized<TOutput, TArgs...>;
    template<typename... TArgs>
    using MethodFireForgetImpl =
        typename method_selector::SkeletonMethodFireForgetImplSelector<TArgs...>::MethodFireForgetImpl;
    template<typename T>
    using FieldImpl = binding_pipc::FieldPublisherSerialized<T>;

    // Serializers
    template<typename T>
    using ISerializer = com::serializer::ISerializer<T>;
    template<typename T>
    using IS2SSerializer = com::serializer::IS2SSerializer<T>;
    template<int N, typename... Types>
    using ADC = com::serializer::ArgumentDeserializerCarrier<N, Types...>;

    // E2E
    using IE2EProtector = com::e2e::IE2EProtector;
    using IE2EChecker   = com::e2e::IE2EChecker;

    // Other classes
    template<typename T>
    using UniquePtr = ara::com::UniquePtr<T>;

public:
    /** \brief Constructor, which takes the configuration object. */
    SkeletonFactory(const config::IServiceIntfCfgSomeIp& config_)
        : config(config_), context(config.getDeploymentContext())
    {
        processName = pipc::sd::Runtime::GetInstance().getProcessId();
        if (!processName.empty() && processName.front() == '/')
        {
            processName = processName.substr(1);
        }
    }

    /**
     * \brief Function to create the impl objects of a Skeleton.
     *
     * The methods createObjects(...) takes a parameter pack with objects to
     * be created and provides one overload for each kind of impl object
     * that needs to be constructed.
     * This function is the 'tail function' for the end of the parameter pack.
     */
    inline void createObjects()
    {
    }

    /** \brief Parameter unrolling specialization for an Event. */
    template<typename Type, typename... TArgs>
    void createObjects(Event<Type>& event,
                       const char* const name,
                       UniquePtr<com::serializer::ISerializer<Type>> serializer,
                       IE2EProtector* (*getProtector)(const InstanceIdentifier& f_instance,
                                                      const ara::core::String& eventName),
                       TArgs&&... args)
    {
        // Create the event
        const auto eventConfig = config.getEventConfig(name);

        event.pImpl = std::make_unique<EventSerializedImpl<Type>>(context,
                                                                  eventConfig,
                                                                  std::move(serializer),
                                                                  UniquePtr<IE2EProtector>(
                                                                      getProtector(context.instanceId, name)));

        // Get to the next object...
        createObjects(std::forward<TArgs>(args)...);
    }

    /** \brief Parameter unrolling specialization for a S2S Event. */
    template<typename Type, typename... TArgs>
    void createObjects(
        Event<Type>& event,
        const char* const name,
        UniquePtr<IS2SSerializer<Type>> (*getS2SEventSerializer)(const InstanceIdentifier& f_instance),
        com::s2s::S2SEventConfig (*getS2SEventConfig)(const InstanceIdentifier& f_instance, const uint32_t eventId),
        std::vector<com::s2s::S2SE2EProtectorConfig> (*getS2SE2EProtectorConfigs)(const InstanceIdentifier& f_instance,
                                                                                  const uint32_t eventId),
        TArgs&&... args)
    {
        // Create the event
        const auto eventConfig = config.getEventConfig(name);
        event.pImpl            = std::make_unique<S2SEventImpl<Type>>(context,
                                                           eventConfig,
                                                           getS2SEventConfig(context.instanceId, eventConfig.eventId),
                                                           getS2SEventSerializer(context.instanceId),
                                                           getS2SE2EProtectorConfigs(context.instanceId,
                                                                                     eventConfig.eventId));

        // Get to the next object...
        createObjects(std::forward<TArgs>(args)...);
    }

    /** \brief Parameter unrolling specialization for a Method. */
    template<typename TMethodOutput, typename... TMethodArgs, typename... TArgs>
    void createObjects(Method<TMethodOutput, TMethodArgs...>& method,
                       const char* const name,
                       binding::MethodQueue& methodQueue,
                       UniquePtr<ADC<sizeof...(TMethodArgs), TMethodArgs...>>&& adc,
                       IE2EChecker* (*getMethodChecker)(const InstanceIdentifier& f_instance,
                                                        const ara::core::String& methodName,
                                                        const ara::core::String& processName),
                       UniquePtr<ISerializer<TMethodOutput>>&& outputSerializer,
                       IE2EProtector* (*getMethodProtector)(const InstanceIdentifier& f_instance,
                                                            const ara::core::String& methodName,
                                                            const ara::core::String& processName),
                       TArgs&&... args)
    {
        // Create the method
        const auto methodConfig = config.getMethodConfig(name);
        method.pImpl            = std::make_unique<MethodImpl<TMethodOutput, TMethodArgs...>>(
            context,
            methodConfig,
            methodQueue,
            std::move(adc),
            UniquePtr<IE2EChecker>(getMethodChecker(context.instanceId, name, processName)),
            std::move(outputSerializer),
            UniquePtr<IE2EProtector>(getMethodProtector(context.instanceId, name, processName)));

        // Get to the next object...
        createObjects(std::forward<TArgs>(args)...);
    }

    /** \brief Parameter unrolling specialization for a serialized Fire & Forget Method. */
    template<typename... TMethodArgs, typename... TArgs>
    void createObjects(MethodFireForget<TMethodArgs...>& method,
                       const char* const name,
                       binding::MethodQueue& methodQueue,
                       UniquePtr<ADC<sizeof...(TMethodArgs), TMethodArgs...>>&& adc,
                       IE2EChecker* (*getMethodChecker)(const InstanceIdentifier& f_instance,
                                                        const ara::core::String& methodName,
                                                        const ara::core::String& processName),
                       TArgs&&... args)
    {
        // Create the method
        const auto methodConfig = config.getMethodConfig(name);
        method.pImpl            = std::make_unique<MethodFireForgetImpl<TMethodArgs...>>(context,
                                                                              methodConfig,
                                                                              methodQueue,
                                                                              std::move(adc),
                                                                              UniquePtr<IE2EChecker>(
                                                                                  getMethodChecker(context.instanceId,
                                                                                                   name,
                                                                                                   processName)));
        // Get to the next object...
        createObjects(std::forward<TArgs>(args)...);
    }

    /** \brief Parameter unrolling specialization for a non-serialized Fire & Forget Method. */
    template<typename... TMethodArgs, typename... TArgs>
    void createObjects(MethodFireForget<TMethodArgs...>& method,
                       const char* const name,
                       binding::MethodQueue& methodQueue,
                       TArgs&&... args)
    {
        // Create the method
        const auto methodConfig = config.getMethodConfig(name);
        method.pImpl            = std::make_unique<MethodFireForgetImpl<>>(context, methodConfig, methodQueue);
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
                       UniquePtr<ISerializer<T>>&& eventSerializer,
                       IE2EProtector* (*getProtector)(const InstanceIdentifier& f_instance,
                                                      const ara::core::String& eventName),
                       UniquePtr<ISerializer<T>>&& getterOutputSerializer,
                       UniquePtr<ISerializer<T>>&& setterOutputSerializer,
                       UniquePtr<ADC<1, T>>&& setterAdc,
                       IE2EChecker* (*getMethodChecker)(const InstanceIdentifier& f_instance,
                                                        const ara::core::String& methodName,
                                                        const ara::core::String& processName),
                       IE2EProtector* (*getMethodProtector)(const InstanceIdentifier& f_instance,
                                                            const ara::core::String& methodName,
                                                            const ara::core::String& processName),
                       binding::MethodQueue& methodQueue,
                       TArgs&&... args)
    {
        // Create the field
        const auto fieldConfig = config.getFieldConfig(name);
        UniquePtr<e2e::IE2EChecker> getterChecker;
        UniquePtr<e2e::IE2EProtector> getterProtector;
        UniquePtr<e2e::IE2EChecker> setterChecker;
        UniquePtr<e2e::IE2EProtector> setterProtector;
        if (fieldConfig.getter.methodName != nullptr)
        {
            getterChecker.reset(getMethodChecker(context.instanceId, fieldConfig.getter.methodName, processName));
            getterProtector.reset(getMethodProtector(context.instanceId, fieldConfig.getter.methodName, processName));
        }
        if (fieldConfig.setter.methodName != nullptr)
        {
            setterChecker.reset(getMethodChecker(context.instanceId, fieldConfig.setter.methodName, processName));
            setterProtector.reset(getMethodProtector(context.instanceId, fieldConfig.setter.methodName, processName));
        }
        field.pImpl.reset(new FieldImpl<T>{context,
                                           fieldConfig,
                                           std::move(eventSerializer),
                                           UniquePtr<IE2EProtector>(getProtector(context.instanceId, name)),
                                           std::move(getterOutputSerializer),
                                           std::move(setterOutputSerializer),
                                           std::move(setterAdc),
                                           std::move(getterChecker),
                                           std::move(getterProtector),
                                           std::move(setterChecker),
                                           std::move(setterProtector),
                                           methodQueue});

        // Get to the next object...
        createObjects(std::forward<TArgs>(args)...);
    }

private:
    const config::IServiceIntfCfgSomeIp& config;    ///< Configuration reader
    const config::DeploymentContextSomeIp& context; ///< Deployment context (buffered due to frequent access)
    ara::core::String processName;                  ///< Process Name
};

/**
 * \brief Skeleton Factory for IPC binding type.
 *
 * This factory creates serialized IPC skeleton objects.
 *
 * TODO: If this is a full copy & paste at the end, we should think about how we merge this.
 */
template<>
class SkeletonFactory<ara::com::NetworkBindingEnum::IPC>
{
    // Front-End classes
    template<typename T>
    using Event = ara::com::SkeletonEvent<T>;
    template<typename... TArgs>
    using MethodFireForget = ara::com::SkeletonMethodFireForget<TArgs...>;
    template<typename TMethodOutput, typename... TArgs>
    using Method = ara::com::SkeletonMethod<TMethodOutput, TArgs...>;
    // switch to this implementation later
    // template<typename T, bool hasGetter, bool hasSetter, bool hasNotifier>
    // using Field = ara::com::SkeletonField<T, hasGetter, hasSetter, hasNotifier>;
    template<typename T>
    using Field = ara::com::SkeletonField<T>;

    // Binding classes
    template<typename T>
    using EventImpl = binding_pipc::EventPublisher<T>;
    template<typename T>
    using EventSerializedImpl = binding_pipc::EventPublisherSerialized<1U, T>;
    template<typename TOutput, typename... TArgs>
    using MethodImpl = binding_pipc::MethodServerSerialized<TOutput, TArgs...>;
    template<typename... TArgs>
    using MethodFireForgetImpl =
        typename method_selector::SkeletonMethodFireForgetImplSelector<TArgs...>::MethodFireForgetImpl;
    template<typename T>
    using FieldImpl = binding_pipc::FieldPublisherSerialized<T>;

    // Serializers
    template<typename T>
    using ISerializer = com::serializer::ISerializer<T>;
    template<typename T>
    using IS2SSerializer = com::serializer::IS2SSerializer<T>;
    template<int N, typename... Types>
    using ADC = com::serializer::ArgumentDeserializerCarrier<N, Types...>;

    // E2E
    using IE2EProtector = com::e2e::IE2EProtector;
    using IE2EChecker   = com::e2e::IE2EChecker;

    // Other classes
    template<typename T>
    using UniquePtr = ara::com::UniquePtr<T>;

public:
    /** \brief Constructor, which takes the configuration object */
    SkeletonFactory(const config::IServiceIntfCfgIpc& config_) : config(config_), context(config.getDeploymentContext())
    {
        processName = pipc::sd::Runtime::GetInstance().getProcessId();
        if (!processName.empty() && processName.front() == '/')
        {
            processName = processName.substr(1);
        }
    }

    /**
     * \brief Function to create the impl objects of a Skeleton.
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
                       UniquePtr<com::serializer::ISerializer<Type>> serializer,
                       IE2EProtector* (*getProtector)(const InstanceIdentifier& f_instance,
                                                      const ara::core::String& eventName),
                       TArgs&&... args)
    {
        // Create the event
        const auto eventConfig = config.getEventConfig(name);

        if (eventConfig.useSerialization)
        {
            event.pImpl = std::make_unique<EventSerializedImpl<Type>>(context,
                                                                      eventConfig,
                                                                      std::move(serializer),
                                                                      UniquePtr<IE2EProtector>(
                                                                          getProtector(context.instanceId, name)));
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
                       UniquePtr<IS2SSerializer<Type>> (*)(const InstanceIdentifier& f_instance),
                       com::s2s::S2SEventConfig (*)(const InstanceIdentifier& f_instance, const uint32_t eventId),
                       std::vector<com::s2s::S2SE2EProtectorConfig> (*)(const InstanceIdentifier& f_instance,
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
                       binding::MethodQueue& methodQueue,
                       UniquePtr<ADC<sizeof...(TMethodArgs), TMethodArgs...>>&& adc,
                       IE2EChecker* (*getMethodChecker)(const InstanceIdentifier& f_instance,
                                                        const ara::core::String& methodName,
                                                        const ara::core::String& processName),
                       UniquePtr<ISerializer<TMethodOutput>>&& outputSerializer,
                       IE2EProtector* (*getMethodProtector)(const InstanceIdentifier& f_instance,
                                                            const ara::core::String& methodName,
                                                            const ara::core::String& processName),
                       TArgs&&... args)
    {
        // Create the method
        const auto methodConfig = config.getMethodConfig(name);
        method.pImpl            = std::make_unique<MethodImpl<TMethodOutput, TMethodArgs...>>(
            context,
            methodConfig,
            methodQueue,
            std::move(adc),
            UniquePtr<IE2EChecker>(getMethodChecker(context.instanceId, name, processName)),
            std::move(outputSerializer),
            UniquePtr<IE2EProtector>(getMethodProtector(context.instanceId, name, processName)));

        // Get to the next object...
        createObjects(std::forward<TArgs>(args)...);
    }

    /** \brief Parameter unrolling specialization for a serialized Fire & Forget Method. */
    template<typename... TMethodArgs, typename... TArgs>
    void createObjects(MethodFireForget<TMethodArgs...>& method,
                       const char* const name,
                       binding::MethodQueue& methodQueue,
                       UniquePtr<ADC<sizeof...(TMethodArgs), TMethodArgs...>>&& adc,
                       IE2EChecker* (*getMethodChecker)(const InstanceIdentifier& f_instance,
                                                        const ara::core::String& methodName,
                                                        const ara::core::String& processName),
                       TArgs&&... args)
    {
        // Create the method
        const auto methodConfig = config.getMethodConfig(name);
        method.pImpl            = std::make_unique<MethodFireForgetImpl<TMethodArgs...>>(context,
                                                                              methodConfig,
                                                                              methodQueue,
                                                                              std::move(adc),
                                                                              UniquePtr<IE2EChecker>(
                                                                                  getMethodChecker(context.instanceId,
                                                                                                   name,
                                                                                                   processName)));
        // Get to the next object...
        createObjects(std::forward<TArgs>(args)...);
    }

    /** \brief Parameter unrolling specialization for a non-serialized Fire & Forget Method. */
    template<typename... TMethodArgs, typename... TArgs>
    void createObjects(MethodFireForget<TMethodArgs...>& method,
                       const char* const name,
                       binding::MethodQueue& methodQueue,
                       TArgs&&... args)
    {
        // Create the method
        const auto methodConfig = config.getMethodConfig(name);
        method.pImpl            = std::make_unique<MethodFireForgetImpl<>>(context, methodConfig, methodQueue);
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
                       UniquePtr<ISerializer<T>>&& eventSerializer,
                       IE2EProtector* (*getProtector)(const InstanceIdentifier& f_instance,
                                                      const ara::core::String& eventName),
                       UniquePtr<ISerializer<T>>&& getterOutputSerializer,
                       UniquePtr<ISerializer<T>>&& setterOutputSerializer,
                       UniquePtr<ADC<1, T>>&& setterAdc,
                       IE2EChecker* (*getMethodChecker)(const InstanceIdentifier& f_instance,
                                                        const ara::core::String& methodName,
                                                        const ara::core::String& processName),
                       IE2EProtector* (*getMethodProtector)(const InstanceIdentifier& f_instance,
                                                            const ara::core::String& methodName,
                                                            const ara::core::String& processName),
                       binding::MethodQueue& methodQueue,
                       TArgs&&... args)
    {
        // Create the field
        const auto fieldConfig = config.getFieldConfig(name);
        UniquePtr<e2e::IE2EChecker> getterChecker;
        UniquePtr<e2e::IE2EProtector> getterProtector;
        UniquePtr<e2e::IE2EChecker> setterChecker;
        UniquePtr<e2e::IE2EProtector> setterProtector;
        if (fieldConfig.getter.methodName != nullptr)
        {
            getterChecker.reset(getMethodChecker(context.instanceId, fieldConfig.getter.methodName, processName));
            getterProtector.reset(getMethodProtector(context.instanceId, fieldConfig.getter.methodName, processName));
        }
        if (fieldConfig.setter.methodName != nullptr)
        {
            setterChecker.reset(getMethodChecker(context.instanceId, fieldConfig.setter.methodName, processName));
            setterProtector.reset(getMethodProtector(context.instanceId, fieldConfig.setter.methodName, processName));
        }
        field.pImpl.reset(new FieldImpl<T>{context,
                                           fieldConfig,
                                           std::move(eventSerializer),
                                           UniquePtr<IE2EProtector>(getProtector(context.instanceId, name)),
                                           std::move(getterOutputSerializer),
                                           std::move(setterOutputSerializer),
                                           std::move(setterAdc),
                                           std::move(getterChecker),
                                           std::move(getterProtector),
                                           std::move(setterChecker),
                                           std::move(setterProtector),
                                           methodQueue});

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

#endif // COM_SERVICE_DEPLOYMENT_SKELETON_FACTORY_HPP
