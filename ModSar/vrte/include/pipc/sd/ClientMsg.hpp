#ifndef SD_CLIENT_MSG_HPP
#define SD_CLIENT_MSG_HPP

#include "SdPort.hpp"
#include "pipc/session/ProviderId.hpp"
#include "pipc/transport/Message.hpp"
#include "pipc/utils/TrivialVariant.hpp"

#include <cstdint>

namespace pipc
{
namespace sd
{
/**
 * @brief Namespace containing all messages sent by client applications.
 */
namespace ClientMsgs
{
/**
 * @brief Request to register a provider.
 */
struct RegisterProviderRequest
{
    /** @brief Default constructor. */
    RegisterProviderRequest() = default;

    /** @brief Constructor needed for emplacement semantics. */
    constexpr RegisterProviderRequest(session::ProviderId providerId, transport::Port providerPort, uint32_t segmentSize)
        : providerId(providerId), providerPort(providerPort), segmentSize(segmentSize)
    {
    }

    session::ProviderId providerId; /**< The provider id. */
    transport::Port providerPort;   /**< The provider port. */
    uint32_t segmentSize;           /**< Sample pool size to be created. No sample pool will be created in case
                                       this value is 0 */
};

/**
 * @brief Request to find provider.
 *
 * The requester will receive ServerMsgs::ProviderOnlineNotification and ServerMsgs::ProviderOfflineNotification
 * in case the status of the provider will change.
 */
struct StartFindProviderRequest
{
    /** @brief Default constructor. */
    StartFindProviderRequest() = default;

    /** @brief Constructor needed for emplacement semantics. */
    constexpr StartFindProviderRequest(session::ProviderId providerId, uint32_t segmentSize, uint16_t segmentSuffix)
        : providerId(providerId), segmentSize(segmentSize), segmentSuffix(segmentSuffix)
    {
    }

    session::ProviderId providerId; /**< The provider id. */
    uint32_t segmentSize;           /**< Sample pool size to be created. No sample pool will be created in case
                             this value is 0 */
    uint16_t segmentSuffix;         /**< Suffix that will be used to create the sample pool */
};

/**
 * @brief Notification to stop find provider.
 *
 * The requester will no longer receive ServerMsgs::ProviderOnlineNotification
 * and ServerMsgs::ProviderOfflineNotification.
 */
struct StopFindProviderNotification
{
    /** @brief Default constructor. */
    StopFindProviderNotification() = default;

    /** @brief Constructor needed for emplacement semantics. */
    constexpr StopFindProviderNotification(session::ProviderId providerId) : providerId(providerId)
    {
    }

    session::ProviderId providerId; /**< The provider id to stop find. */
};

/**
 * @brief Notification to unregister a provider.
 *
 * This will lead to a ServerMsgs::ProviderOfflineNotification, in case the provider is still offered.
 */
struct UnregisterProviderNotification
{
    /** @brief Default constructor. */
    UnregisterProviderNotification() = default;

    /** @brief Constructor needed for emplacement semantics. */
    constexpr UnregisterProviderNotification(session::ProviderId providerId) : providerId(providerId)
    {
    }

    session::ProviderId providerId; /**< The provider id */
};

/**
 * @brief Notification to start offering.
 *
 * This will lead to a ServerMsgs::ProviderOnlineNotification.
 */
struct StartOfferNotification
{
    /** @brief Default constructor. */
    StartOfferNotification() = default;

    /** @brief Constructor needed for emplacement semantics. */
    constexpr StartOfferNotification(session::ProviderId providerId) : providerId(providerId)
    {
    }

    session::ProviderId providerId; /**< The provider id. */
};

/**
 * @brief Notification to stop offering.
 *
 * This will lead to a ServerMsgs::ProviderOfflineNotification.
 */
struct StopOfferNotification
{
    /** @brief Default constructor. */
    StopOfferNotification() = default;

    /** @brief Constructor needed for emplacement semantics. */
    constexpr StopOfferNotification(session::ProviderId providerId) : providerId(providerId)
    {
    }

    session::ProviderId providerId; /**< The provider id. */
};

/**
 * @brief Notification about client shut down.
 */
struct ShutDownNotification
{
    /** @brief Default constructor. */
    ShutDownNotification() = default;
};

enum Type
{
    kRegisterProviderRequest,
    kStartFindProviderRequest,
    kStopFindProviderNotification,
    kUnregisterProviderNotification,
    kStartOfferNotification,
    kStopOfferNotification,
    kShutDownNotification
};

using Container = utils::TrivialVariant<RegisterProviderRequest,
                                        StartFindProviderRequest,
                                        StopFindProviderNotification,
                                        UnregisterProviderNotification,
                                        StartOfferNotification,
                                        StopOfferNotification,
                                        ShutDownNotification>;

/**
 * @brief Create a datagram for a ClientMsg of type T and return it.
 */
template<typename T, typename... Args>
static constexpr transport::Datagram<Container> CreateDatagram(Args&&... args)
{
    transport::Datagram<Container> msg;
    msg.header().dstPort = SdPort;
    msg.payload().template emplace<T>(std::forward<Args>(args)...);
    return msg;
}

} // namespace ClientMsgs
using ClientMsg = ClientMsgs::Container;

} // namespace sd
} // namespace pipc

#endif
