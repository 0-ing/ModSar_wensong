/// @copyright : 2022 Robert Bosch GmbH. All rights reserved.

#ifndef COM_SD_CLIENT_MSG_HPP
#define COM_SD_CLIENT_MSG_HPP

#include "Service.hpp"
#include "com/Types.hpp"
#include "pipc/transport/Message.hpp"
#include "pipc/utils/TrivialVariant.hpp"

#include <cstdint>

namespace com
{
namespace sd
{
/**
 * @brief Namespace containing all messages sent by client applications.
 */
namespace ClientMsgs
{
/**
 * @brief Request to register a service instance.
 */
struct RegisterServiceRequest
{
    /** @brief Default constructor. */
    RegisterServiceRequest() = default;

    /** @brief Constructor needed for emplacement semantics. */
    constexpr RegisterServiceRequest(ServiceId serviceId, InstanceId instanceId)
        : serviceId(serviceId), instanceId(instanceId)
    {
    }

    ServiceId serviceId;   /**< The serviceId. */
    InstanceId instanceId; /**< The instanceId. */
};

/**
 * @brief Notification to unregister a service instance.
 */
struct UnregisterServiceNotification
{
    /** @brief Default constructor. */
    UnregisterServiceNotification() = default;

    /** @brief Constructor needed for emplacement semantics. */
    constexpr UnregisterServiceNotification(ServiceId serviceId, InstanceId instanceId)
        : serviceId(serviceId), instanceId(instanceId)
    {
    }

    ServiceId serviceId;   /**< The serviceId. */
    InstanceId instanceId; /**< The instanceId. */
};

/**
 * @brief Notification to start offering a service instance.
 */
struct StartOfferServiceNotification
{
    /** @brief Default constructor. */
    StartOfferServiceNotification() = default;

    /** @brief Constructor needed for emplacement semantics. */
    constexpr StartOfferServiceNotification(ServiceId serviceId, InstanceId instanceId)
        : serviceId(serviceId), instanceId(instanceId)
    {
    }

    ServiceId serviceId;   /**< The serviceId. */
    InstanceId instanceId; /**< The instanceId. */
};

/**
 * @brief Notification to stop offering a service instance.
 */
struct StopOfferServiceNotification
{
    /** @brief Default constructor. */
    StopOfferServiceNotification() = default;

    /** @brief Constructor needed for emplacement semantics. */
    constexpr StopOfferServiceNotification(ServiceId serviceId, InstanceId instanceId)
        : serviceId(serviceId), instanceId(instanceId)
    {
    }

    ServiceId serviceId;   /**< The serviceId. */
    InstanceId instanceId; /**< The instanceId. */
};

/**
 * @brief Request to get available service instances.
 */
struct FindServiceRequest
{
    /** @brief Default constructor. */
    FindServiceRequest() = default;

    /** @brief Constructor needed for emplacement semantics. */
    constexpr FindServiceRequest(ServiceId serviceId, InstanceId instanceId, uint8_t remainingInstanceIds = 0U)
        : serviceId(serviceId), instanceId(instanceId), remainingInstanceIds(remainingInstanceIds)
    {
    }

    ServiceId serviceId;          /**< The serviceId. */
    InstanceId instanceId;        /**< The instanceId. */
    uint8_t remainingInstanceIds; /**< No. of remaining instanceIds via followup messages. */
};

/**
 * @brief Request to get available service instances and availability updates.
 */
struct StartFindServiceRequest
{
    /** @brief Default constructor. */
    StartFindServiceRequest() = default;

    /** @brief Constructor needed for emplacement semantics. */
    constexpr StartFindServiceRequest(ServiceId serviceId, InstanceId instanceId, uint8_t remainingInstanceIds = 0U)
        : serviceId(serviceId), instanceId(instanceId), remainingInstanceIds(remainingInstanceIds)
    {
    }

    ServiceId serviceId;          /**< The serviceId. */
    InstanceId instanceId;        /**< The instanceId. */
    uint8_t remainingInstanceIds; /**< No. of remaining instanceIds via followup messages. */
};

/**
 * @brief Notification to not send further availability updates.
 */
struct StopFindServiceNotification
{
    /** @brief Default constructor. */
    StopFindServiceNotification() = default;

    /** @brief Constructor needed for emplacement semantics. */
    constexpr StopFindServiceNotification(FindServiceId findServiceId) : findServiceId(findServiceId)
    {
    }

    FindServiceId findServiceId; /**< The findServiceId. */
};

/**
 * @brief Followup message with up to 4 InstanceIds.
 */
struct InstanceIdList
{
    /** @brief Default constructor. */
    InstanceIdList() = default;

    InstanceId instanceIds[4U]; /**< The instanceIds. */
};

enum Type
{
    kRegisterServiceRequest,
    kUnregisterServiceNotification,
    kStartOfferServiceNotification,
    kStopOfferServiceNotification,
    kFindServiceRequest,
    kStartFindServiceRequest,
    kStopFindServiceNotification,
    kInstanceIdList
};

using Container = pipc::utils::TrivialVariant<RegisterServiceRequest,
                                              UnregisterServiceNotification,
                                              StartOfferServiceNotification,
                                              StopOfferServiceNotification,
                                              FindServiceRequest,
                                              StartFindServiceRequest,
                                              StopFindServiceNotification,
                                              InstanceIdList>;

/**
 * @brief Create a datagram for a ClientMsg of type T and return it.
 */
template<typename T, typename... Args>
static constexpr pipc::transport::Datagram<Container> CreateDatagram(pipc::transport::Port port, Args&&... args)
{
    pipc::transport::Datagram<Container> msg;
    msg.header().dstPort = port;
    msg.payload().template emplace<T>(std::forward<Args>(args)...);
    return msg;
}

} // namespace ClientMsgs
using ClientMsg = ClientMsgs::Container;

} // namespace sd
} // namespace com

#endif // COM_SD_CLIENT_MSG_HPP
