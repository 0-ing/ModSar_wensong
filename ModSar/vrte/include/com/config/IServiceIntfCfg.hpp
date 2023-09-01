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
/// @file      IServiceIntfCfg.hpp
/// @brief     Interface of the service deployment configuration
/// @copyright Robert Bosch GmbH 2021
/// @author    crg2fe
//=============================================================================

#ifndef COM_CONFIG_ISERVICE_INTF_CFG_HPP
#define COM_CONFIG_ISERVICE_INTF_CFG_HPP

#include "ara/com/types.h"

namespace com
{
namespace config
{
using ara::com::InstanceIdentifier;
using ara::com::NetworkBindingEnum;

/******************************
 *
 * SOME/IP DATA STRUCTS
 *
 * *****************************/

/** \brief SOME/IP event config */
struct EventCfgSomeIp
{
    const char* eventName;         ///< SHORT-NAME of the event
    uint16_t eventId;              ///< SOME/IP event ID. Allowed range is 0..32767, while 0 and 32767 is reserved.
    uint32_t maxSerializationSize; ///< Max Serialization size
    bool sessionHandling;
    ara::com::TransportLayerProtocolEnum transportProtocol;
    uint32_t eventSegmentLength;
    // Not yet supported
    // ara::com::SerializationTechnologyEnum serializer; ///< Argument to select the serialization technology for the event.
};

/** \brief SOME/IP method config */
struct MethodCfgSomeIp
{
    const char* methodName; ///< SHORT-NAME of the method
    uint16_t methodId;      ///< SOME/IP method ID. Allowed range is 0..32767, while 0 and 32767 is reserved.
    uint32_t requestMaxSerializationSize;  ///< Max Serialization size for request
    uint32_t responseMaxSerializationSize; ///< Max Serialization size for response
};

/** \brief SOME/IP field config */
struct FieldCfgSomeIp
{
    const char* fieldName;   ///< SHORT-NAME of the field
    bool hasGetter;        ///< Indication if the field has a getter.
    bool hasSetter;        ///< Indication if the field has a setter.
    bool hasNotifier;      ///< Indication if the field has a notifier.
    MethodCfgSomeIp getter;  ///< Getter method configuration.
    MethodCfgSomeIp setter;  ///< Setter method configuration.
    EventCfgSomeIp notifier; ///< Notification event configuration.
};

/**
 * \brief Context of a SOME/IP deployment config
 *
 * The context is a container, which consists of all information relevant
 * to the deployment, but not specific to Events, Fields or Methods
 */
struct DeploymentContextSomeIp
{
    const char* serviceName;       ///< The name of the deployed service
    InstanceIdentifier instanceId; ///< The Instance ID
    uint16_t serviceInterfaceId;   ///< The SOME/IP Service Interface ID
};

/******************************
 *
 * IPC DATA STRUCTS
 *
 * *****************************/

/** \brief IPC event config */
struct EventCfgIpc
{
    const char* eventName;         ///< Name/ID of the event.
    uint16_t eventId;              ///< ID of the event.
    bool useSerialization;         ///< True if we need to use serialization
    uint32_t maxSerializationSize; ///< Max Serialization size
};

/** \brief IPC method config */
struct MethodCfgIpc
{
    const char* methodName;                ///< Name/ID of the method.
    uint16_t methodId;                     ///< ID of the method.
    bool useSerialization;                 ///< True if we need to use serialization
    uint32_t requestMaxSerializationSize;  ///< Max Serialization size
    uint32_t responseMaxSerializationSize; ///< Max Serialization size
};

/** \brief IPC field config */
struct FieldCfgIpc
{
    const char* fieldName; ///< Name of the field.
    bool hasGetter;        ///< Indication if the field has a getter.
    bool hasSetter;        ///< Indication if the field has a setter.
    bool hasNotifier;      ///< Indication if the field has a notifier.
    MethodCfgIpc getter;   ///< Getter method configuration.
    MethodCfgIpc setter;   ///< Setter method configuration.
    EventCfgIpc notifier;  ///< Notification event configuration.
};

/**
 * \brief Context of a IPC deployment config
 *
 * The context is a container, which consists of all information relevant
 * to the deployment, but not specific to Events, Fields or Methods
 */
struct DeploymentContextIpc
{
    const char* serviceName;       ///< The name of the deployed service
    InstanceIdentifier instanceId; ///< The Instance ID
    uint64_t serviceInterfaceId;   ///< The IPC Service Interface ID
};

/******************************
 *
 * INTERFACES
 *
 * *****************************/

/**
 * \brief Interface for a service interface deployment base config
 *
 * This interface acts as a starting point to read a configuration.
 * The user needs to find out the actual binding via getNetworkBinding()
 * and then call getBindingSpecificCfg() with the actual binding as template
 * parameter to get a concrete configuration object.
 *
 * TODO:
 * We could getBindingSpecificCfg() add to the interface, but then we would loose
 * the ability to do skeleton creation on-stack
 */
class IServiceIntfCfgBase
{
public:
    /** \brief Get the transport binding of the service interface deployment */
    virtual ara::com::NetworkBindingEnum getNetworkBinding() const = 0;
};

/** \brief Interface for a SOME/IP service interface config */
class IServiceIntfCfgSomeIp
{
public:
    /** \brief Get the configuration of a specific event */
    virtual EventCfgSomeIp getEventConfig(const char* const name) const = 0;

    /** \brief Get the configuration of a specific method */
    virtual MethodCfgSomeIp getMethodConfig(const char* const name) const = 0;

    /** \brief Get the configuration of a specific field */
    virtual FieldCfgSomeIp getFieldConfig(const char* const name) const = 0;

    /** \brief Get the context associated with the deployment */
    virtual const DeploymentContextSomeIp& getDeploymentContext() const = 0;
};

/**
 * \brief Interface for a IPC service interface config
 */
class IServiceIntfCfgIpc
{
public:
    /** \brief Get the configuration of a specific event */
    virtual EventCfgIpc getEventConfig(const char* const name) const = 0;

    /** \brief Get the configuration of a specific method */
    virtual MethodCfgIpc getMethodConfig(const char* const name) const = 0;

    /** \brief Get the configuration of a specific field */
    virtual FieldCfgIpc getFieldConfig(const char* const name) const = 0;

    /** \brief Get the context associated with the deployment */
    virtual const DeploymentContextIpc& getDeploymentContext() const = 0;
};

} // namespace config

} // namespace com

#endif // COM_CONFIG_ISERVICE_INTF_CFG_HPP
