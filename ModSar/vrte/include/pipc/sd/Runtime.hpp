#ifndef SD_RUNTIME_HPP
#define SD_RUNTIME_HPP

#include "AppRegistry.hpp"
#include "ClientMsg.hpp"
#include "ProcConnectionRegistry.hpp"
#include "SdPort.hpp"
#include "ServerMsg.hpp"
#include "pipc/pimp/Listener.hpp"
#include "pipc/proc_reg/Client.hpp"
#include "pipc/rte/IRuntime.hpp"
#include "pipc/utils/ErrorHandler.hpp"
#include "pipc/utils/FastSemaphore.hpp"

#include <cstring>
#include <mutex>
#include <stdlib.h>

namespace pipc
{
namespace sd
{
class Runtime : public rte::IRuntime
{
public:
    /**
     * @brief Returns the runtime instance.
     *
     * The first call of this function should provide a unique name (by this name the process is identified).
     * On the next consecutive calls, the name can be omitted.
     */
    static Runtime& GetInstance(const char* name = nullptr)
    {
        static Runtime runtime(name);
        return runtime;
    }

    /**
     * @brief Destructor.
     */
    ~Runtime()
    {
        sdListener_.stop();

        auto clientMsg = ClientMsgs::CreateDatagram<ClientMsgs::ShutDownNotification>();
        send(clientMsg);

        getDispatcher().unregisterCbk(SdPort);

        sdSocket_.close();
    }

    /** @brief Get the message dispatcher. */
    MsgDispatcher& getDispatcher() override
    {
        return transport::Runtime::GetDispatcher();
    }

    /** @brief Get the processId. */
    const char* getProcessId() const
    {
        return processId_;
    }

    /** @brief Get the SD Socket. */
    pimp::Socket& getSdSocket()
    {
        return sdSocket_;
    }

    /**
     * @brief Function used to register a new Service Provider.
     *
     * @return ReturnCode::kOk if successful. See @ref ReturnCode.
     */
    ReturnCode registerProvider(rte::IApp& app) override
    {
        if (!app.isProvider())
        {
            return ReturnCode::kSdInvalidInput;
        }
        auto& providerId = app.getProviderId();
        PIPC_LOG_DEBUG() << "Registering Provider with ProviderId: " << providerId.toString() << std::endl;

        AppEntry* entry;
        {
            std::lock_guard<std::mutex> appsLk(appsMutex_);
            entry = apps_.get(&app);
            if (entry == nullptr)
            {
                return ReturnCode::kSdRegistryFull;
            }
            if (entry->state != AppEntry::RegisterState::kNotRegistered)
            {
                return ReturnCode::kSdAlreadyRegistered;
            }
            entry->state = AppEntry::RegisterState::kRegistrationPending;
        }

        auto clientMsg = ClientMsgs::CreateDatagram<ClientMsgs::RegisterProviderRequest>(providerId,
                                                                                         app.getPort(),
                                                                                         app.getSegmentSize());
        ReturnCode response;
        {
            std::lock_guard<std::mutex> registerLk(registerProviderMutex_);
            send(clientMsg);

            providerAcknowledgeSemaphore_.wait();
            response = lastProviderRegisterResponse_;
        }

        {
            std::lock_guard<std::mutex> appsLk(appsMutex_);
            if (response == ReturnCode::kOk)
            {
                app.init(false);
                entry->state = AppEntry::RegisterState::kRegistered;
            }
        }
        return response;
    }

    /**
     * @brief Function used to register a new Service User.
     *
     * @return ReturnCode::kOk if successful. See @ref ReturnCode.
     */
    ReturnCode registerUser(rte::IApp& app) override
    {
        if (app.isProvider())
        {
            return ReturnCode::kSdInvalidInput;
        }

        auto& providerId = app.getProviderId();
        PIPC_LOG_DEBUG() << "Registerung User with ProviderId: " << providerId.toString() << std::endl;

        AppEntry* entry;
        {
            std::lock_guard<std::mutex> appsLk(appsMutex_);
            entry = apps_.get(&app);
            if (entry == nullptr)
            {
                return ReturnCode::kSdRegistryFull;
            }
            if (entry->state != AppEntry::RegisterState::kNotRegistered)
            {
                return ReturnCode::kSdAlreadyRegistered;
            }
            entry->state = AppEntry::RegisterState::kRegistrationPending;
        }

        auto clientMsg = ClientMsgs::CreateDatagram<ClientMsgs::StartFindProviderRequest>(providerId,
                                                                                          app.getSegmentSize(),
                                                                                          app.getPort());
        ReturnCode response;
        {
            std::lock_guard<std::mutex> registerLk(registerUserMutex_);
            send(clientMsg);

            userAcknowledgeSemaphore_.wait();
            response = lastUserRegisterResponse_;
        }

        {
            std::lock_guard<std::mutex> appsLk(appsMutex_);
            if (response == ReturnCode::kOk)
            {
                app.init(false);
                entry->state = AppEntry::RegisterState::kRegistered;
            }
        }
        return response;
    }

    /** @brief Notify the runtime that a provider is starting to offer. */
    void startOffer(rte::IApp& app) override
    {
        {
            std::lock_guard<std::mutex> appsLk(appsMutex_);
            auto entry = apps_.find(&app);
            if (entry == nullptr || (entry->state != AppEntry::RegisterState::kRegistered) || !app.isProvider())
            {
                return;
            }
        }

        auto& providerId = app.getProviderId();
        PIPC_LOG_DEBUG() << "StartOffer: " << providerId.toString() << std::endl;

        auto clientMsg = ClientMsgs::CreateDatagram<ClientMsgs::StartOfferNotification>(providerId);
        send(clientMsg);
    }

    /** @brief Notify the runtime that a provider is stopping to offer. */
    void stopOffer(rte::IApp& app) override
    {
        {
            std::lock_guard<std::mutex> appsLk(appsMutex_);
            auto entry = apps_.find(&app);
            if (entry == nullptr || (entry->state != AppEntry::RegisterState::kRegistered) || !app.isProvider())
            {
                return;
            }
        }

        auto& providerId = app.getProviderId();
        PIPC_LOG_DEBUG() << "StopOffer: " << providerId.toString() << std::endl;

        auto clientMsg = ClientMsgs::CreateDatagram<ClientMsgs::StopOfferNotification>(providerId);
        send(clientMsg);
    }

    /** @brief Unregister a Service Provider from the runtime. */
    void unregisterProvider(rte::IApp& app) override
    {
        auto& providerId = app.getProviderId();
        {
            std::lock_guard<std::mutex> appsLk(appsMutex_);
            auto entry = apps_.find(&app);
            if (entry == nullptr || (entry->state == AppEntry::RegisterState::kNotRegistered))
            {
                return;
            }

            PIPC_LOG_DEBUG() << "Unregister Provider: " << providerId.toString() << std::endl;
            entry->state = AppEntry::RegisterState::kNotRegistered;
        }

        auto clientMsg = ClientMsgs::CreateDatagram<ClientMsgs::UnregisterProviderNotification>(providerId);
        send(clientMsg);
    }

    /** @brief Unregister a Service User from the runtime. */
    void unregisterUser(rte::IApp& app) override
    {
        auto& providerId                  = app.getProviderId();
        size_t countOfSameRegisteredUsers = 0;
        {
            std::lock_guard<std::mutex> appsLk(appsMutex_);
            auto entry = apps_.find(&app);
            if (entry == nullptr || (entry->state == AppEntry::RegisterState::kNotRegistered))
            {
                return;
            }

            PIPC_LOG_DEBUG() << "UnregisterUser: " << providerId.toString() << std::endl;
            entry->state = AppEntry::RegisterState::kNotRegistered;
            for (auto user = apps_.begin(); user != apps_.end(); user++)
            {
                if ((user->state == AppEntry::RegisterState::kRegistered) && !user->app->isProvider()
                    && user->app->getProviderId() == providerId)
                {
                    countOfSameRegisteredUsers++;
                }
            }
        }

        if (countOfSameRegisteredUsers == 0)
        {
            auto clientMsg = ClientMsgs::CreateDatagram<ClientMsgs::StopFindProviderNotification>(providerId);
            send(clientMsg);
        }
    }

    /** @brief Return the Node Id assigned to this process. */
    NodeId getNodeId() const override
    {
        return nodeId_;
    }

protected:
    /** @brief Private constructor with RAII initialization. */
    Runtime(const char* name)
    {
        init(name);
    }

private:
    /** @brief Constructor used for testing. */
    Runtime()
    {
    }

    /** @brief Initialization function. */
    void init(const char* name)
    {
        if (name == nullptr)
        {
            utils::ErrorHandler::CriticalError(utils::ErrorType::kGeneral, "No name provided to the SD Runtime!");
            return;
        }
        PIPC_LOG_DEBUG() << "Starting SD Runtime with Process Id " << name << std::endl;

        proc_reg::Client client;
        proc_reg::ClientMsg request;
        proc_reg::ServerMsg response;

        request.id = proc_reg::ClientMsg::Id::kRegisterReq;
        strcpy(request.procIdentifier, name);
        strcpy(processId_, name);

        bool clientConnected = false;
        uint8_t numTries     = 20;

        while (numTries > 0)
        {
            if (client.sendRequest(request, response))
            {
                clientConnected = true;
                break;
            }
            usleep(100000);
            numTries--;
        }

        if (!clientConnected)
        {
            utils::ErrorHandler::CriticalError(utils::ErrorType::kGeneral,
                                               "Client was not able to establish a connection with the server!");
            return;
        }

        if (response.id != proc_reg::ServerMsg::Id::kRegisterAck)
        {
            utils::ErrorHandler::CriticalError(utils::ErrorType::kGeneral, "Process registration denied by the server!");
            return;
        }

        char path[sizeof(PIPC_PREFIX_SD_SOCKETS) + 5];
        strcpy(path, PIPC_PREFIX_SD_SOCKETS);
        sprintf(&path[sizeof(PIPC_PREFIX_SD_SOCKETS) - 1], "%u", response.nodeId);

        if (sdSocket_.connect(path) != ReturnVal::kOk)
        {
            utils::ErrorHandler::CriticalError(utils::ErrorType::kGeneral, "Cannot connect to sd socket!");
            return;
        }

        nodeId_  = response.nodeId;
        auto ret = getDispatcher().registerCbk(SdPort, &ReceiveSdMessage, *this);
        if (ret != ReturnCode::kOk)
        {
            utils::ErrorHandler::CriticalError(utils::ErrorType::kGeneral,
                                               "Could not register SdPort at MsgDispatcher!",
                                               ret);
            return;
        }

        sdListener_.start();
    }

    /**
     * @brief Function wrapper to receive a SD message.
     */
    static void ReceiveSdMessage(Runtime& obj, pimp::Socket& socket, transport::Datagram<ServerMsgs::Container>* msg)
    {
        obj.receiveSdMessage(socket, *msg);
    }

    /**
     * @brief Function to receive a SD message.
     */
    void receiveSdMessage(pimp::Socket& socket, transport::Datagram<ServerMsgs::Container>& msg)
    {
        // Assert for the correct identity of the daemon
        if (&socket != &sdSocket_)
        {
            PIPC_LOG_ERROR() << "Pipc Sd Runtime: Got message with invalid identity." << std::endl;
            return;
        }

        auto& serverMsg = msg.payload();
        switch (serverMsg.index())
        {
        case sd::ServerMsgs::kRegisterProviderReply:
        {
            receiveRegisterProviderReply(serverMsg.get<sd::ServerMsgs::RegisterProviderReply>());
            break;
        }
        case sd::ServerMsgs::kStartFindProviderReply:
        {
            receiveStartFindProviderReply(serverMsg.get<sd::ServerMsgs::StartFindProviderReply>());
            break;
        }
        case sd::ServerMsgs::kProviderOnlineNotification:
        {
            receiveProviderOnlineNotification(serverMsg.get<sd::ServerMsgs::ProviderOnlineNotification>());
            break;
        }
        case sd::ServerMsgs::kProviderOfflineNotification:
        {
            receiveProviderOfflineNotification(serverMsg.get<sd::ServerMsgs::ProviderOfflineNotification>());
            break;
        }
        case sd::ServerMsgs::kSocketConnectNotification:
        {
            receiveSocketConnectNotification(serverMsg.get<sd::ServerMsgs::SocketConnectNotification>());
            break;
        }
        case sd::ServerMsgs::kSocketOfflineNotification:
        {
            receiveSocketOfflineNotification(serverMsg.get<sd::ServerMsgs::SocketOfflineNotification>());
            break;
        }
        default:
        {
            PIPC_LOG_ERROR() << "Unknown ServerMsg with index: " << serverMsg.index() << std::endl;
            break;
        }
        }
    }

    /** @brief Method that will be called in case of Register Provider Reply. */
    void receiveRegisterProviderReply(const sd::ServerMsgs::RegisterProviderReply& msg)
    {
        PIPC_LOG_DEBUG() << "Received RegisterProvider reply for ProviderId " << msg.providerId.toString() << ": "
                         << ToString(msg.retCode) << std::endl;
        lastProviderRegisterResponse_ = msg.retCode;
        providerAcknowledgeSemaphore_.post();
    }

    /** @brief Method that will be called in case of Start Find Provider Reply. */
    void receiveStartFindProviderReply(const sd::ServerMsgs::StartFindProviderReply& msg)
    {
        PIPC_LOG_DEBUG() << "Received RegisterUser reply for ProviderId " << msg.providerId.toString() << ": "
                         << ToString(msg.retCode) << std::endl;
        lastUserRegisterResponse_ = msg.retCode;
        userAcknowledgeSemaphore_.post();
    }

    /** @brief Method that will be called in case of Provider Online Notification. */
    void receiveProviderOnlineNotification(const sd::ServerMsgs::ProviderOnlineNotification& msg)
    {
        PIPC_LOG_DEBUG() << "Received ProviderOnlineNotification : " << msg.providerId.toString() << std::endl;
        auto socketEntry = procConnectionsRegistry_.find(msg.socketId);
        if (socketEntry)
        {
            std::lock_guard<std::mutex> appsLk(appsMutex_);
            uint16_t idx = 0;
            for (auto entry = apps_.begin(); entry != apps_.end(); entry++)
            {
                auto app = entry->app;
                // Users that are kRegistered and kRegistrationPending will receive the notification
                if ((entry->state != AppEntry::RegisterState::kNotRegistered) && !app->isProvider()
                    && app->getProviderId() == msg.providerId)
                {
                    PIPC_LOG_DEBUG() << "Notifying user no. : " << idx++ << std::endl;
                    app->notifyProviderOnline(socketEntry->socket, msg.providerPort);
                }
            }
        }
    }

    /** @brief Method that will be called in case of Provider Offline Notification. */
    void receiveProviderOfflineNotification(const sd::ServerMsgs::ProviderOfflineNotification& msg)
    {
        PIPC_LOG_DEBUG() << "Received ProviderOfflineNotification: " << msg.providerId.toString() << std::endl;
        std::lock_guard<std::mutex> appsLk(appsMutex_);
        for (auto entry = apps_.begin(); entry != apps_.end(); entry++)
        {
            auto app = entry->app;
            // Users that are kRegistered and kRegistrationPending will receive the notification
            if ((entry->state != AppEntry::RegisterState::kNotRegistered) && !app->isProvider()
                && app->getProviderId() == msg.providerId)
            {
                app->notifyProviderOffline();
            }
        }
    }

    /** @brief Method that will be called in case of Socket Connect Notification. */
    void receiveSocketConnectNotification(const sd::ServerMsgs::SocketConnectNotification& msg)
    {
        PIPC_LOG_DEBUG() << "Received notification to connect to : " << msg.socketId << std::endl;
        if (procConnectionsRegistry_.addConnection(msg.socketId, msg.nodeId, msg.connectionMode))
        {
            PIPC_LOG_INFO() << "Connected to node id: " << msg.nodeId << ", socket id: " << msg.socketId << std::endl;
        }
        else
        {
            PIPC_LOG_ERROR() << "Failed to connect to socket id:  " << msg.socketId << std::endl;
        }
    }

    /** @brief Method that will be called in case of Socket Offline Notification. */
    void receiveSocketOfflineNotification(const sd::ServerMsgs::SocketOfflineNotification& msg)
    {
        PIPC_LOG_DEBUG() << "Received SocketOfflineNotification for socket id: " << msg.socketId << std::endl;
        auto socketEntry = procConnectionsRegistry_.find(msg.socketId);
        if (socketEntry)
        {
            {
                std::lock_guard<std::mutex> appsLk(appsMutex_);
                for (auto entry = apps_.begin(); entry != apps_.end(); entry++)
                {
                    // Users that are kRegistered and kRegistrationPending will receive the notification
                    if (entry->state != AppEntry::RegisterState::kNotRegistered)
                    {
                        entry->app->notifySocketOffline(socketEntry->socket);
                    }
                }
            }
            // After the discussions from Story 18063, for now we can still listen
            // on the socket even if the process is dead.
            // socketEntry->listener.stop();
        }
    }

    /**
     * @brief Wrapper to send a message to the daemon.
     *
     * Failing to send a message to the daemon is considered critical,
     * as the condition is not handled and we enter an undefined state.
     */
    template<typename T>
    void send(T& msg)
    {
        auto ret = sdSocket_.send(msg);
        if (ret != ReturnVal::kOk)
        {
            utils::ErrorHandler::CriticalError(utils::ErrorType::kGeneral, "Could not send SD message to Daemon!");
        }
    }

    /** @brief Process ID String (used for debugging). */
    char processId_[PIPC_MAX_PROCID_STRING_LENGTH];
    /** @brief Client's socket used for Service Discovery. */
    pimp::Socket sdSocket_;
    /** @brief Listener for the SD Socket. */
    pimp::Listener<transport::MsgDispatcher> sdListener_{sdSocket_, transport::Runtime::GetDispatcher()};
    /** @brief Id of this node. */
    NodeId nodeId_{0};
    /** @brief Process connection registry (contains connections to other processes). */
    ProcConnectionRegistry procConnectionsRegistry_;
    /** @brief Registry with all Apps managed by the runtime. */
    AppRegistry apps_;
    /** @brief Mutex for accessing the AppRegistry. */
    std::mutex appsMutex_;
    /** @brief Mutex for registering a Provider. */
    std::mutex registerProviderMutex_;
    /** @brief Mutex for registering a User. */
    std::mutex registerUserMutex_;
    /** @brief Signal for reply to a Provider registration request. */
    utils::FastSemaphore providerAcknowledgeSemaphore_{0, false};
    /** @brief Signal for reply to a User registration request. */
    utils::FastSemaphore userAcknowledgeSemaphore_{0, false};
    /** @brief Buffer for reply to the last Provider registration request. */
    ReturnCode lastProviderRegisterResponse_;
    /** @brief Buffer for reply to the last User registration request. */
    ReturnCode lastUserRegisterResponse_;
};

} // namespace sd
} // namespace pipc

#endif
