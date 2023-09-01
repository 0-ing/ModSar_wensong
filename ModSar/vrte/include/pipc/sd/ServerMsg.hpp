#ifndef SD_SERVER_MSG_HPP
#define SD_SERVER_MSG_HPP

#include "ProcSocketId.hpp"
#include "SdPort.hpp"
#include "pipc/NodeId.hpp"
#include "pipc/ReturnCode.hpp"
#include "pipc/pimp/TISocket.hpp"
#include "pipc/session/ProviderId.hpp"
#include "pipc/transport/Message.hpp"
#include "pipc/utils/TrivialVariant.hpp"

#include <cstdint>

namespace pipc
{
namespace sd
{
/**
 * @brief Namespace containing all messages sent by the SD server.
 */
namespace ServerMsgs
{
/**
 * @brief Reply for ClientMsgs::RegisterProviderRequest.
 *
 * Registration was successfull if retCode is kOk. See @ref ReturnCode.
 */
struct RegisterProviderReply
{
    /** @brief Default constructor. */
    RegisterProviderReply() = default;

    /** @brief Constructor needed for emplacement semantics. */
    constexpr RegisterProviderReply(session::ProviderId providerId, ReturnCode retCode)
        : providerId(providerId), retCode(retCode)
    {
    }

    session::ProviderId providerId; /**< The provider id. */
    ReturnCode retCode;             /**< Return code. */
};

/**
 * @brief Reply for ClientMsgs::StartFindProviderRequest.
 *
 * Request is accepted if retCode is kOk. See @ref ReturnCode.
 */
struct StartFindProviderReply
{
    /** @brief Default constructor. */
    StartFindProviderReply() = default;

    /** @brief Constructor needed for emplacement semantics. */
    constexpr StartFindProviderReply(session::ProviderId providerId, ReturnCode retCode)
        : providerId(providerId), retCode(retCode)
    {
    }

    session::ProviderId providerId; /**< The provider id. */
    ReturnCode retCode;             /**< Return code. */
};

/**
 * @brief Notification sent to client applications if the status of the provider changes.
 *
 * This will happen in case of ClientMsgs::StartOfferNotification.
 */
struct ProviderOnlineNotification
{
    /** @brief Default constructor. */
    ProviderOnlineNotification() = default;

    /** @brief Constructor needed for emplacement semantics. */
    constexpr ProviderOnlineNotification(session::ProviderId providerId,
                                         transport::Port providerPort,
                                         ProcSocketId socketId)
        : providerId(providerId), providerPort(providerPort), socketId(socketId)
    {
    }

    session::ProviderId providerId; /**< The provider id. */
    transport::Port providerPort;   /**< The provider port. */
    ProcSocketId socketId;          /**< The provider socket id. */
};

/**
 * @brief Notification sent to client applications if the status of the provider changes.
 *
 * This will happen in case of ClientMsgs::StopOfferNotification
 */
struct ProviderOfflineNotification
{
    /** @brief Default constructor. */
    ProviderOfflineNotification() = default;

    /** @brief Constructor needed for emplacement semantics. */
    constexpr ProviderOfflineNotification(session::ProviderId providerId) : providerId(providerId)
    {
    }

    session::ProviderId providerId; /**< The provider id. */
};

/**
 * @brief Notification sent to client applications to connect to a proc socket.
 */
struct SocketConnectNotification
{
    /** @brief Default constructor. */
    SocketConnectNotification() = default;

    /** @brief Constructor needed for emplacement semantics. */
    constexpr SocketConnectNotification(ProcSocketId socketId, NodeId nodeId, pimp::ConnectionMode connectionMode)
        : socketId(socketId), nodeId(nodeId), connectionMode(connectionMode)
    {
    }

    ProcSocketId socketId; /**< The socket Id to connect to. */
    NodeId nodeId;         /**< The nodeId on the other side of the socket. */
    pimp::ConnectionMode
        connectionMode; /**< Info whether the socket needs to be connected in normal, crossover or loopback mode. */
};

/**
 * @brief Notification sent to client applications to disconnect from a proc socket.
 */
struct SocketOfflineNotification
{
    /** @brief Default constructor. */
    SocketOfflineNotification() = default;

    /** @brief Constructor needed for emplacement semantics. */
    constexpr SocketOfflineNotification(ProcSocketId socketId) : socketId(socketId)
    {
    }

    ProcSocketId socketId; /**< The socket Id to disconnect from. */
};

enum Type
{
    kRegisterProviderReply,
    kStartFindProviderReply,
    kProviderOnlineNotification,
    kProviderOfflineNotification,
    kSocketConnectNotification,
    kSocketOfflineNotification
};

using Container = utils::TrivialVariant<RegisterProviderReply,
                                        StartFindProviderReply,
                                        ProviderOnlineNotification,
                                        ProviderOfflineNotification,
                                        SocketConnectNotification,
                                        SocketOfflineNotification>;

/**
 * @brief Create a datagram for a ServerMsg of type T and return it.
 */
template<typename T, typename... Args>
static constexpr transport::Datagram<Container> CreateDatagram(Args&&... args)
{
    transport::Datagram<Container> msg;
    msg.header().dstPort = SdPort;
    msg.payload().template emplace<T>(std::forward<Args>(args)...);
    return msg;
}

} // namespace ServerMsgs
using ServerMsg = ServerMsgs::Container;

} // namespace sd
} // namespace pipc

#endif
