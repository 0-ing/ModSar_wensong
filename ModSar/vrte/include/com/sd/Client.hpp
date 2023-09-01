/// @copyright : 2022 Robert Bosch GmbH. All rights reserved.

#ifndef COM_SD_CLIENT_HPP
#define COM_SD_CLIENT_HPP

#include "ClientMsg.hpp"
#include "ServerMsg.hpp"
#include "pipc/rte/StandaloneRuntime.hpp"
#include "pipc/utils/FastSemaphore.hpp"
#include "sd/FindServiceDispatcher.hpp"

namespace com
{
namespace sd
{
/**
 * @brief Implementation for ARA SD with IPC deployments.
 *
 * This implementation realizes the Client side of the ARA SD protocol via PIPC & PIMP Sockets.
 * It is directly utilized for IPC deployments, in which case the ARA SD Server lies with in
 * the com daemon and is always available.
 *
 * @todo
 * Add the IApp interface, we need it for handling SocketOfflineNotification.
 */
class Client
{
protected:
    /** @brief Protected constructor for inheriting classes. */
    Client(FindServiceDispatcher& findServiceDispatcher,
           NetworkBindingEnum binding,
           pipc::transport::Port port,
           pipc::rte::IRuntime& runtime);

public:
    /** @brief Constructor with registration at the pipc Runtime. */
    Client(FindServiceDispatcher& findServiceDispatcher, pipc::pimp::Socket& socket, pipc::transport::Port port);

    /** @brief Destructor with deregistration at the pipc Runtime. */
    ~Client();

public:
    /**
     * @brief Register a skeleton.
     *
     * @param serviceId
     * @param instanceIdentifier
     * @return Result<void> Whether the registration was successful.
     */
    Result<void> registerSkeleton(ServiceId serviceId, const InstanceIdentifier& instanceIdentifier);

    /**
     * @brief Unregister a skeleton.
     *
     * @param serviceId
     * @param instanceIdentifier
     */
    void unregisterSkeleton(ServiceId serviceId, const InstanceIdentifier& instanceIdentifier);

    /**
     * @brief Register a proxy.
     *
     * @remark Stub for future implementations
     *
     * @param serviceId
     * @param instanceIdentifier
     * @return Result<void> Whether the registration was successful.
     */
    Result<void> registerProxy(ServiceId serviceId, const InstanceIdentifier& instanceIdentifier);

    /**
     * @brief Start offering a service.
     *
     * @param serviceId
     * @param instanceIdentifier
     */
    void offerService(ServiceId serviceId, const InstanceIdentifier& instanceIdentifier);

    /**
     * @brief Stop offering a service.
     *
     * @param serviceId
     * @param instanceIdentifier
     */
    void stopOfferService(ServiceId serviceId, const InstanceIdentifier& instanceIdentifier);

    /**
     * @brief Request FindService with an InstanceIdentifierContainer.
     *
     * @param serviceId
     * @param instanceIds
     * @return Result<ServiceHandleContainer> Returned service handles.
     */
    Result<ServiceHandleContainer> findService(ServiceId serviceId, const InstanceIdentifierContainer& instanceIds);

    /**
     * @brief Request StartFindService with an InstanceIdentifierContainer.
     *
     * @param findServiceHandler
     * @param serviceId
     * @param instanceIds
     * @return Result<FindServiceHandle> The received find service handle.
     */
    Result<FindServiceHandle> startFindService(const FindServiceHandler& findServiceHandler,
                                               ServiceId serviceId,
                                               const InstanceIdentifierContainer& instanceIds);

    /**
     * @brief Stop finding a service.
     *
     * @param findServiceHandle
     */
    void stopFindService(FindServiceHandle findServiceHandle);

protected:
    /**
     * @brief A buffer for storing received messages and instance lists from the Server.
     *
     * Requests are transmitted in a sender context, received in a receiver context
     * and eventually evaluated in the sender context.
     * A safe evaluation without overrides of received replies is ensured via a transaction mutex,
     * which protects the request-reply transaction to the server.
     *
     * However, pending notifications might already be present in the socket and require processing before the reply of
     * a request can be received. Using the transaction mutex would result in a deadlock, thus we need a separate buffer
     * for handling notifications.
     */
    struct RxBuffer
    {
        /** @brief Default constructor. */
        RxBuffer() : msg(), serviceHandles()
        {
        }

        /** @brief The received message from the Server. */
        ServerMsg msg;
        /** @brief The list of received serviceHandles. */
        ServiceHandleContainer serviceHandles;
    };

    /** @brief Wrapper to receive a msg. */
    static void Receive(Client& obj, pipc::pimp::Socket& socket, pipc::transport::Datagram<ServerMsg>* msg);

    /** @brief Function to receive a SD message. */
    inline void receive(pipc::pimp::Socket& socket, pipc::transport::Datagram<ServerMsg>& msg);

    /** @brief Logic for receiving a RegisterServiceReply message. */
    inline void receiveRegisterServiceReply(const ServerMsgs::RegisterServiceReply& msg);

    /** @brief Logic for receiving a FindServiceReply message. */
    inline void receiveFindServiceReply(const ServerMsgs::FindServiceReply& msg);

    /** @brief Logic for receiving a StartFindServiceReply message. */
    inline void receiveStartFindServiceReply(const ServerMsgs::StartFindServiceReply& msg);

    /** @brief Logic for receiving a FindServiceNotification message. */
    inline void receiveFindServiceNotification(const ServerMsgs::FindServiceNotification& msg);

    /** @brief Logic for receiving a InstanceIdList message. */
    inline void receiveInstanceIdList(const ServerMsgs::InstanceIdList& msg);

    /** @brief Send a message to the server. */
    void send(pipc::transport::Datagram<ClientMsg>& msg);

    /**
     * @brief Send messages with remaining instanceIds to the server.
     *
     * If there is more than one element in instanceIds,
     * starts with the second element and keeps sending InstanceIdList messages,
     * until all InstanceIdentifiers are transmitted.
     */
    void sendRemainingInstanceIds(const InstanceIdentifierContainer& instanceIds);

    /** @brief The PIMP Socket used to communicate to the SD Server. */
    pipc::pimp::Socket* socket_;
    /** @brief The PIPC Port used to communicate to the SD Server. */
    pipc::transport::Port port_;
    /** @brief The PIPC Runtime. */
    pipc::rte::IRuntime& runtime_;
    /** @brief Dispatcher to handle calling of FindServiceHandlers. */
    FindServiceDispatcher& findServiceDispatcher_;
    /**
     * @brief Last findServiceHandler given to a startFindService call.
     *
     * @remark
     * We need to buffer the address of the findServiceHandler, so we can
     * add it to the findServiceDispatcher in the context of the thread
     * receiving the reply.
     * If we add it in the sending thread, a race condition might lead to
     * the first FindServiceNotification of the request not being resolvable.
     */
    const FindServiceHandler* lastFindServiceHandler_;
    /**
     * @brief Buffer for incoming messages.
     *
     * @remark
     * Only used if we need to buffer multi-part messages.
     */
    RxBuffer msgBuffer_;
    /**
     * @brief Buffer for received replies.
     *
     * @remark
     * Always used to protect against overrides of followup
     * notifications.
     */
    RxBuffer replyBuffer_;
    /** @brief Pointer to the active instanceId container to be filled. */
    ServiceHandleContainer* activeServiceHandleBuffer_;
    /** @brief Signal for a completed reception of a reply. */
    pipc::utils::FastSemaphore replyReceivedSignal_;
    /**
     * @brief Mutex for sending to and receiving from the Server.
     *
     * @remark
     * The Client only supports synchronuous RPC calls for requests,
     * this mutex assures that exclusive access to it is given for
     * each RPC transaction.
     */
    std::mutex transactionMutex_;
    /** @brief Check whether what we receive is what we expect. */
    ServerMsgs::Type expectedReply_;
    /** @brief Remaining instanceIds to be received. */
    uint8_t remainingInstanceIds_;
    /** @brief Information for which binding the client is used. */
    NetworkBindingEnum binding_;
};

} // namespace sd
} // namespace com

#endif // COM_SD_CLIENT_HPP
