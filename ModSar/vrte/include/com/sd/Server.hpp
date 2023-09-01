/// @copyright : 2022 Robert Bosch GmbH. All rights reserved.

#ifndef COM_SD_SERVER_HPP
#define COM_SD_SERVER_HPP

#include "ClientMsg.hpp"
#include "ServerMsg.hpp"
#include "ara/core/map.h"
#include "pipc/rte/StandaloneRuntime.hpp"
#include "pipc/utils/FastSemaphore.hpp"
#include "utils/Logger.hpp"

namespace com
{
namespace sd
{
/**
 * @brief Default implementation for a ARA SD Server.
 *
 * This is the most basic implementation of an ARA SD Server, which is used
 * for IPC deployments and sitting in the arapipcd.
 *
 * @todo
 * Try this class out with CRTP instead of virtual of selected functions.
 */
class Server
{
public:
    /**
     * @brief Constructor with registration at the Runtime.
     *
     * @todo
     * Check whether a Runtime makes sense here.
     */
    Server(pipc::transport::Port port, pipc::rte::IRuntime& runtime = pipc::rte::StandaloneRuntime::GetInstance());

    /** @brief Destructor with deregistration at the Runtime. */
    ~Server();

protected:
    /**
     * @brief Struct for storing a pending request.
     *
     * This struct is used to buffer the information of requests
     * consisting of multi-part messages,
     * so that the Server cannot be indefinitely blocked by a client
     * sending an incomplete multi-part message.
     */
    struct PendingRequest
    {
        /** @brief Explicit constructor needed for emplace semantics. */
        template<typename T>
        inline PendingRequest(pipc::pimp::Socket* socket, const T& requestMsg, InstanceId instanceId)
            : socket(socket),
              msg(),
              requestedInstanceIds({instanceId}),
              remainingInstanceIds(requestMsg.remainingInstanceIds)
        {
            msg.emplace(requestMsg);
        }

        /** @brief The socket which initiated the request. */
        pipc::pimp::Socket* socket;
        /** @brief The initial message of the request. */
        ClientMsg msg;
        /** @brief The instanceIds received through InstanceIdList messages. */
        InstanceIdContainer requestedInstanceIds;
        /** @brief Counter for the remaining instanceIds. */
        uint8_t remainingInstanceIds;
    };

    /** @brief Struct for a list of pending requests. */
    struct PendingRequests
    {
        /** @brief Convenience function to find a request via socket. */
        auto find(const pipc::pimp::Socket& socket)
        {
            return std::find_if(items.begin(), items.end(), [&socket](const PendingRequest& request) -> bool {
                return request.socket == &socket;
            });
        }

        /**
         * @brief Convenience function to insert a request via socket.
         *
         * Adds or replaces the entry with the given information.
         * If the entry already exists, prints an error message.
         */
        template<typename TMsg>
        void addOrReplace(pipc::pimp::Socket& socket, const TMsg& msg)
        {
            auto it = find(socket);
            if (it == items.end())
            {
                items.emplace_back(&socket, msg, msg.instanceId);
            }
            // HINT: Could happen due to internal error at the client side
            else
            {
                com::utils::Logger::GetInstance().LogError() << "Overriding incomplete request.\n";
                it->msg.emplace(msg);
                it->requestedInstanceIds.clear();
                it->requestedInstanceIds.emplace_back(msg.instanceId);
            }
        }

        /** @brief The list of requests. */
        ara::core::Vector<PendingRequest> items;
    };

    /** @brief Struct for storing instance-related info. */
    struct InstanceInfo
    {
        /** @brief Explicit constructor needed for emplace semantics. */
        constexpr InstanceInfo(pipc::pimp::Socket* socket, InstanceId instanceId, bool isOffered)
            : socket(socket), instanceId(instanceId), isOffered(isOffered)
        {
        }
        /**
         * @brief The provider app, identified by its socket to the server.
         */
        pipc::pimp::Socket* socket;
        /** @brief The related instanceId. */
        InstanceId instanceId;
        /** @brief Info whether the instance is currently offered. */
        bool isOffered;
    };

    /** @brief Struct for storing a requester for all available service instances. */
    struct AllInstanceRequester
    {
        /** @brief Explicit constructor needed for emplace semantics. */
        constexpr AllInstanceRequester(pipc::pimp::Socket& socket, FindServiceId findServiceId)
            : socket(&socket), findServiceId(findServiceId)
        {
        }

        /** @brief The requester app, identified by its socket to the server. */
        pipc::pimp::Socket* socket;
        /** @brief The handle used for reporting availability updates. */
        FindServiceId findServiceId;
    };

    /** @brief Struct for storing a requester for all available service instances. */
    struct SomeInstanceRequester
    {
        /** @brief Explicit constructor needed for emplace semantics. */
        inline SomeInstanceRequester(pipc::pimp::Socket& socket,
                                     InstanceIdContainer& instanceIds,
                                     FindServiceId findServiceId)
            : socket(&socket), instanceIds(std::move(instanceIds)), findServiceId(findServiceId)
        {
        }

        /** @brief Convenience function to check whether the requester wants to know about the given instanceId. */
        bool requests(InstanceId instanceId) const
        {
            auto it = std::find_if(instanceIds.begin(),
                                   instanceIds.end(),
                                   [&instanceId](const InstanceId& other) -> bool { return other == instanceId; });
            return (it != instanceIds.end());
        }

        /** @brief The requester app, identified by its socket to the server. */
        pipc::pimp::Socket* socket;
        /** @brief The list of requested instanceIds. */
        InstanceIdContainer instanceIds;
        /** @brief The handle used for reporting availability updates. */
        FindServiceId findServiceId;
    };

    /** @brief Struct for storing service-related info. */
    struct ServiceInfo
    {
        /** @brief Convenience function to find an instance via instanceId. */
        auto find(InstanceId instanceId)
        {
            return std::find_if(instances.begin(), instances.end(), [&instanceId](const InstanceInfo& instance) -> bool {
                return instance.instanceId == instanceId;
            });
        }

        /**
         * @brief Add a new requester to be considered for availability updates.
         *
         * @remark
         * Note that requestedInstanceIds is consumed in this function and left
         * in an undefined state (the local variable or owning PendingRequest struct is erased
         * shortly after).
         */
        void addRequester(pipc::pimp::Socket& socket,
                          InstanceIdContainer& requestedInstanceIds,
                          FindServiceId findServiceId)
        {
            if (static_cast<InstanceId>(requestedInstanceIds[0]) == ALL_INSTANCE_IDS)
            {
                allInstanceRequesters.emplace_back(socket, findServiceId);
            }
            else
            {
                someInstanceRequesters.emplace_back(socket, requestedInstanceIds, findServiceId);
            }
        }

        /** @brief List of all created instances of the service. */
        ara::core::Vector<InstanceInfo> instances;
        /** @brief List of requesters for all instances. */
        ara::core::Vector<AllInstanceRequester> allInstanceRequesters;
        /** @brief List of requesters for some instances. */
        ara::core::Vector<SomeInstanceRequester> someInstanceRequesters;
    };

    /**
     * @brief Return the subset list of available instances.
     *
     * @remark
     * In case no instances are available, the container holds one item with NO_INSTANCE_IDS.
     */
    InstanceIdContainer getAvailableInstanceIds(ServiceId serviceId, const InstanceIdContainer& requestedInstanceIds);

    /** @brief Wrapper to receive a msg. */
    static void Receive(Server& obj, pipc::pimp::Socket& socket, pipc::transport::Datagram<ClientMsg>* msg);

    /** @brief Function to receive a SD message. */
    void receive(pipc::pimp::Socket& socket, pipc::transport::Datagram<ClientMsg>& msg);

    /** @brief Logic for receiving a RegisterServiceRequest message. */
    void receiveRegisterServiceRequest(pipc::pimp::Socket& socket, const ClientMsgs::RegisterServiceRequest& msg);

    /** @brief Logic for receiving a UnregisterServiceNotification message. */
    void receiveUnregisterServiceNotification(pipc::pimp::Socket& socket,
                                              const ClientMsgs::UnregisterServiceNotification& msg);

    /** @brief Logic for receiving a StartOfferServiceNotification message. */
    void receiveStartOfferServiceNotification(pipc::pimp::Socket& socket,
                                              const ClientMsgs::StartOfferServiceNotification& msg);

    /** @brief Logic for receiving a StopOfferServiceNotification message. */
    void receiveStopOfferServiceNotification(pipc::pimp::Socket& socket,
                                             const ClientMsgs::StopOfferServiceNotification& msg);

    /** @brief Logic for receiving a FindServiceRequest message. */
    void receiveFindServiceRequest(pipc::pimp::Socket& socket, const ClientMsgs::FindServiceRequest& msg);

    /** @brief Logic for receiving a StartFindServiceRequest message. */
    void receiveStartFindServiceRequest(pipc::pimp::Socket& socket, const ClientMsgs::StartFindServiceRequest& msg);

    /** @brief Logic for receiving a StopFindServiceNotification message. */
    void receiveStopFindServiceNotification(pipc::pimp::Socket& socket,
                                            const ClientMsgs::StopFindServiceNotification& msg);

    /** @brief Logic for receiving a InstanceIdList message. */
    void receiveInstanceIdList(pipc::pimp::Socket& socket, const ClientMsgs::InstanceIdList& msg);

    /** @brief Handle a start offer of a service. */
    virtual void handleStartOffer(const ServiceInfo& service, ServiceId serviceId, InstanceId instanceId);

    /** @brief Handle a stop offer of a service. */
    virtual void handleStopOffer(const ServiceInfo& service, ServiceId serviceId, InstanceId instanceId);

    /** @brief Go through active requesters and send FindServiceNotifications, if necessary. */
    void handleFindServiceNotifications(const ServiceInfo& service, ServiceId serviceId, InstanceId changedInstanceId);

    /** @brief Send a FindServiceReply message. */
    virtual void sendFindServiceReply(pipc::pimp::Socket& socket,
                                      ServiceId serviceId,
                                      const InstanceIdContainer& requestedInstanceIds);

    /** @brief Send a StartFindServiceReply message. */
    virtual void sendStartFindServiceReply(pipc::pimp::Socket& socket,
                                           ServiceId serviceId,
                                           InstanceIdContainer& requestedInstanceIds);

    /** @brief Send a message to a client. */
    void send(pipc::pimp::Socket& socket, pipc::transport::Datagram<ServerMsg>& msg);

    /**
     * @brief Send messages with remaining instanceIds to the client.
     *
     * If there is more than one element in instanceIds,
     * starts with the second element and keeps sending InstanceIdList messages,
     * until all InstanceIdentifiers are transmitted.
     */
    void sendRemainingInstanceIds(pipc::pimp::Socket& socket, const InstanceIdContainer& instanceIds);

    /** @brief The PIPC Runtime. */
    pipc::rte::IRuntime& runtime_;
    /** @brief The map with the service registry. */
    ara::core::Map<ServiceId, ServiceInfo> services_;
    /** @brief Mutex for accessing the service map. */
    std::recursive_mutex servicesMutex_;
    /** @brief The list of pending requests. */
    PendingRequests pendingRequests_;
    /** @brief Mutex for accessing the pending requests list. */
    std::mutex pendingRequestsMutex_;
    /**
     * @brief Mutex for sending multi-part messages.
     *
     * @remark
     * A multi-part FindServiceNotification could interleave with
     * a multi-part (Start-)FindServiceReply without this mutex.
     */
    std::mutex txMutex_;
    /** @brief The PIPC Port used to communicate to the SD Clients. */
    pipc::transport::Port port_;
    /** @brief The next findServiceId to be given. */
    FindServiceId nextFindServiceId_;
};

} // namespace sd
} // namespace com

#endif // COM_SD_SERVER_HPP
