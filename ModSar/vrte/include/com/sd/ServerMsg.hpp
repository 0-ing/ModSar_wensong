/// @copyright : 2022 Robert Bosch GmbH. All rights reserved.

#ifndef COM_SD_SERVER_MSG_HPP
#define COM_SD_SERVER_MSG_HPP

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
 * @brief Namespace containing all messages sent by server applications.
 */
namespace ServerMsgs
{
/**
 * @brief Reply to ClientMsgs::RegisterServiceRequest.
 */
struct RegisterServiceReply
{
    /** @brief Default constructor. */
    RegisterServiceReply() = default;

    /** @brief Constructor needed for emplacement semantics. */
    constexpr RegisterServiceReply(ComErrc returnCode) : returnCode(returnCode)
    {
    }

    ComErrc returnCode; /**< The return code. */
};

/**
 * @brief Reply to ClientMsgs::FindServiceRequest.
 */
struct FindServiceReply
{
    /** @brief Default constructor. */
    FindServiceReply() = default;

    /** @brief Constructor needed for emplacement semantics. */
    constexpr FindServiceReply(ComErrc returnCode, InstanceId instanceId, uint8_t remainingInstanceIds)
        : returnCode(returnCode), instanceId(instanceId), remainingInstanceIds(remainingInstanceIds)
    {
    }

    ComErrc returnCode;           /**< The return code. */
    InstanceId instanceId;        /**< The instanceId. */
    uint8_t remainingInstanceIds; /**< No. of remaining instanceIds via followup messages. */
};

/**
 * @brief Reply to ClientMsgs::FindServiceRequest.
 */
struct StartFindServiceReply
{
    /** @brief Default constructor. */
    StartFindServiceReply() = default;

    /** @brief Constructor needed for emplacement semantics. */
    constexpr StartFindServiceReply(ComErrc returnCode, FindServiceId findServiceId)
        : returnCode(returnCode), findServiceId(findServiceId)
    {
    }

    ComErrc returnCode;          /**< The return code. */
    FindServiceId findServiceId; /**< The findServiceId. */
};

/**
 * @brief Notify about service availability change.
 *
 * @todo
 * It might be better to buffer the list of available instances at the Runtime side.
 * In that case only send "ServiceAvailabilityNotification" msgs with changed availability of single
 * instances instead of complete lists.
 */
struct FindServiceNotification
{
    /** @brief Default constructor. */
    FindServiceNotification() = default;

    /** @brief Constructor needed for emplacement semantics. */
    constexpr FindServiceNotification(InstanceId instanceId, FindServiceId findServiceId, uint8_t remainingInstanceIds)
        : instanceId(instanceId), findServiceId(findServiceId), remainingInstanceIds(remainingInstanceIds)
    {
    }

    InstanceId instanceId;        /**< The instanceId. */
    FindServiceId findServiceId;  /**< The findServiceId. */
    uint8_t remainingInstanceIds; /**< No. of remaining instanceIds via followup messages. */
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
    kRegisterServiceReply,
    kFindServiceReply,
    kStartFindServiceReply,
    kFindServiceNotification,
    kInstanceIdList,
    kNone
};

using Container = pipc::utils::
    TrivialVariant<RegisterServiceReply, FindServiceReply, StartFindServiceReply, FindServiceNotification, InstanceIdList>;

/**
 * @brief Create a datagram for a ServerMsg of type T and return it.
 */
template<typename T, typename... Args>
static constexpr pipc::transport::Datagram<Container> CreateDatagram(pipc::transport::Port port, Args&&... args)
{
    pipc::transport::Datagram<Container> msg;
    msg.header().dstPort = port;
    msg.payload().template emplace<T>(std::forward<Args>(args)...);
    return msg;
}

} // namespace ServerMsgs
using ServerMsg = ServerMsgs::Container;

} // namespace sd
} // namespace com

#endif // COM_SD_SERVER_MSG_HPP
