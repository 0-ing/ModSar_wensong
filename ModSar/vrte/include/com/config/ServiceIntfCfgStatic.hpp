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
/// @file      ServiceIntfCfgStatic.hpp
/// @brief     Implementation of a service config reader for static
/// configuration
/// @copyright Robert Bosch GmbH 2021
/// @author    crg2fe
//=============================================================================

#ifndef COM_SERVICE_DEPLOYMENT_SERVICE_INTF_CFG_STATIC_HPP
#define COM_SERVICE_DEPLOYMENT_SERVICE_INTF_CFG_STATIC_HPP

#include "IServiceIntfCfg.hpp"
#include "utils/array_ref.hpp"

#include <stdint.h>
#include <utility>

namespace com
{
namespace config
{
/******************************
 *
 * STRUCTS FOR CONFIGURATION CONTAINERS
 *
 * *****************************/

/** \brief Config for a SOME/IP Interface deployment */
struct ServiceIntfCfgSomeIp
{
    using EventConfigs_T  = utils::const_array_ref<EventCfgSomeIp>;
    using MethodConfigs_T = utils::const_array_ref<MethodCfgSomeIp>;
    using FieldConfigs_T  = utils::const_array_ref<FieldCfgSomeIp>;

    /**
     * \brief Constructor with forwarding the input arguments.
     *
     * This is a convenience feature to support direct list initialization.
     * If we don't define this constructor, we have to write the initializer
     * like this: {42, {MyEvents}, {MyMethods}, {MyFields}}
     */
    template<typename T1, typename T2, typename T3>
    ServiceIntfCfgSomeIp(const uint16_t _serviceInterfaceId, T1&& _eventConfigs, T2&& _methodConfigs, T3&& _fieldConfigs)
        : serviceInterfaceId(_serviceInterfaceId),
          eventConfigs(std::forward<T1>(_eventConfigs)),
          methodConfigs(std::forward<T2>(_methodConfigs)),
          fieldConfigs(std::forward<T3>(_fieldConfigs))
    {
    }

    const uint16_t serviceInterfaceId;
    const EventConfigs_T eventConfigs;
    const MethodConfigs_T methodConfigs;
    const FieldConfigs_T fieldConfigs;
};

/** \brief Config for a IPC Interface deployment */
struct ServiceIntfCfgIpc
{
    using EventConfigs_T  = utils::const_array_ref<EventCfgIpc>;
    using MethodConfigs_T = utils::const_array_ref<MethodCfgIpc>;
    using FieldConfigs_T  = utils::const_array_ref<FieldCfgIpc>;

    /**
     * \brief Constructor with forwarding the input arguments.
     *
     * This is a convenience feature to support direct list initialization.
     * If we don't define this constructor, we have to write the initializer
     * like this: {42, {MyEvents}, {MyMethods}, {MyFields}}
     */
    template<typename T1, typename T2, typename T3>
    ServiceIntfCfgIpc(uint64_t _serviceInterfaceId, T1&& _eventConfigs, T2&& _methodConfigs, T3&& _fieldConfigs)
        : serviceInterfaceId(_serviceInterfaceId),
          eventConfigs(std::forward<T1>(_eventConfigs)),
          methodConfigs(std::forward<T2>(_methodConfigs)),
          fieldConfigs(std::forward<T3>(_fieldConfigs))
    {
    }

    const uint64_t serviceInterfaceId;
    const EventConfigs_T eventConfigs;
    const MethodConfigs_T methodConfigs;
    const FieldConfigs_T fieldConfigs;
};

/** \brief Mapping element for a service instance */
struct ServiceInstMapping
{
    /**
     * \brief Constructor with forwarding the input arguments.
     *
     * This is a convenience feature to support direct list initialization.
     * If we don't define this constructor, we have to write the initializer
     * like this: {{"001"}, TransportBinding, &MyServiceIntfConfig}
     */
    ServiceInstMapping(const char* _instanceIdentifierName, NetworkBindingEnum _binding, const void* _config)
        : instanceIdentifierName((_instanceIdentifierName)), binding(_binding), config(_config)
    {
    }

    const char* instanceIdentifierName;
    NetworkBindingEnum binding;
    const void* config;
};

/**
 * \brief Top-level element for a service-specific configuration
 *
 * \remark We could add more information later, like version of the service
 * interface
 */
struct ServiceCfg
{
    /**
     * \brief Constructor with forwarding the input arguments.
     *
     * This is a convenience feature to support direct list initialization.
     * If we don't define this constructor, we have to write the initializer
     * like this: {42, {MyEvents}, {MyMethods}, {MyFields}}
     */
    template<typename T1>
    ServiceCfg(const char* _serviceName, T1&& _instanceMappings)
        : serviceName(_serviceName), instanceMappings(std::forward<T1>(_instanceMappings))
    {
    }

    const char* serviceName;
    utils::const_array_ref<ServiceInstMapping> instanceMappings;
};

class ServiceIntfCfgIpcStatic;
class ServiceIntfCfgSomeIpStatic;

/**
 * \brief Base class for a Service Interface Config
 */
class ServiceIntfCfgBaseStatic final : public IServiceIntfCfgBase
{
public:
    /** \brief Constructor, which takes an InstanceIdentifier and the service
     * config */
    ServiceIntfCfgBaseStatic(const InstanceIdentifier& _instanceId, const ServiceCfg& _config);

    /** \brief Get the transport binding of the service interface deployment */
    NetworkBindingEnum getNetworkBinding() const override;

    /** \brief Return a SOME/IP configuration object */
    ServiceIntfCfgSomeIpStatic getSomeIpConfig() const;

    /** \brief Return a IPC configuration object */
    ServiceIntfCfgIpcStatic getIpcConfig() const;

private:
    /** \brief Method to find the mapping of a given instanceId */
    const ServiceInstMapping* findInstance(InstanceIdentifier instanceId, const ServiceCfg& config) const;

    const ServiceCfg& config;            ///< Reference to the Service configuration container
    const InstanceIdentifier instanceId; ///< The Instance ID of the configuration
    const ServiceInstMapping* mapping;   ///< Pointer to the mapped configuration
};

/** \brief Config reader for a IPC configuration */
class ServiceIntfCfgIpcStatic final : public IServiceIntfCfgIpc
{
public:
    /** \brief Constructor, which takes a reference to the config container and a
     * context struct */
    ServiceIntfCfgIpcStatic(const ServiceIntfCfgIpc& _config, const DeploymentContextIpc& _context);

    /** \brief Get the configuration of a specific event */
    EventCfgIpc getEventConfig(const char* const name) const override;

    /** \brief Get the configuration of a specific method */
    MethodCfgIpc getMethodConfig(const char* const name) const override;

    /** \brief Get the configuration of a specific field */
    FieldCfgIpc getFieldConfig(const char* const name) const override;

    /** \brief Get the context associated with the deployment */
    const DeploymentContextIpc& getDeploymentContext() const override;

private:
    const ServiceIntfCfgIpc config;     ///< Reference to the service interface configuration
    const DeploymentContextIpc context; ///< Deployment context
};

/** \brief Config reader for a SOME/IP configuration */
class ServiceIntfCfgSomeIpStatic final : public IServiceIntfCfgSomeIp
{
public:
    /** \brief Constructor, which takes a reference to the config container */
    ServiceIntfCfgSomeIpStatic(const ServiceIntfCfgSomeIp& _config, const DeploymentContextSomeIp& _context);

    /** \brief Get the configuration of a specific event */
    EventCfgSomeIp getEventConfig(const char* const name) const override;

    /** \brief Get the configuration of a specific method */
    MethodCfgSomeIp getMethodConfig(const char* const name) const override;

    /** \brief Get the configuration of a specific field */
    FieldCfgSomeIp getFieldConfig(const char* const name) const override;

    /** \brief Get the context associated with the deployment */
    const DeploymentContextSomeIp& getDeploymentContext() const override;

private:
    const ServiceIntfCfgSomeIp config;     ///< Reference to the service interface configuration
    const DeploymentContextSomeIp context; ///< Deployment context
};

} // namespace config

} // namespace com

#endif // COM_SERVICE_DEPLOYMENT_SERVICE_INTF_CFG_STATIC_HPP
