/// @copyright : 2022 Robert Bosch GmbH. All rights reserved.

#ifndef COM_SD_GATEWAYCLIENT_HPP
#define COM_SD_GATEWAYCLIENT_HPP

#include "Client.hpp"
#include "pipc/sd/Runtime.hpp"

namespace com
{
namespace sd
{
/**
 * @brief Implementing for ARA SD towards gateways.
 *
 * This implementation is used for managing an ARA SD client, which communicates
 * to gateways for additional deployments (e.g. Some/Ip, Dds) instead of the IPC
 * deployments. As opposed to IPC deployments, gateways are located in different
 * processes and need to be found via PIPC SD.
 *
 * This Client sits therefore between the ARA user layer and PIPC:
 * From the ARA perspective it acts as a Client providing SD services,
 * from the PIPC perspective it acts as a User App.
 */
class GatewayClient : public Client, public pipc::rte::IApp
{
public:
    using BaseClass  = Client;
    using ProviderId = pipc::session::ProviderId;

public:
    /** @brief Constructor with registration at the Runtime. */
    GatewayClient(FindServiceDispatcher& findServiceDispatcher,
                  NetworkBindingEnum binding,
                  const pipc::session::ProviderId& providerId,
                  pipc::transport::Port port,
                  pipc::rte::IRuntime& runtime = pipc::sd::Runtime::GetInstance());

    /** @brief Destructor with deregistration at the Runtime. */
    ~GatewayClient();

    /**
     * @brief Register a skeleton.
     *
     * @param serviceId
     * @param instanceIdentifier
     * @return Result<void> Whether the registration was successful.
     */
    Result<void> registerSkeleton(ServiceId serviceId, const InstanceIdentifier& instanceIdentifier);

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

    /** @brief Overrides of the pipc::rte::IApp interface. */
    const ProviderId& getProviderId() override;
    Port getPort() const override;
    bool isProvider() override;
    void init(bool standalone = false) override;
    void notifyProviderOnline(Socket& socket, Port port) override;
    void notifyProviderOffline() override;
    void notifySocketOffline(Socket& socket) override;

private:
    /**
     * @brief Wait until the connection to the SD Server is established.
     *
     * This method is used for means of lazy initialization.
     * During initialization of this Client, the PIPC daemon is requested to publish information
     * about the Server's availability once available.
     *
     * Upon first requiring the Server's facilities, this function will do a timed wait
     * and abort if a timeout occurs.
     */
    void waitForConnection();

    /** @brief The pipc provider id. */
    ProviderId providerId_;
    /** @brief Flag to check whether the client is connected to the server. */
    bool connected_;
    /**
     * @brief Flag to check whether this client is used.
     *
     * This flag checks whether the application depends on the functionality
     * of the gateway this client is connected to. If it is and the gateway
     * becomes offline, we are moving into an undefined state.
     *
     * @todo
     * Implement reinit capability.
     */
    bool used_;
};

} // namespace sd
} // namespace com

#endif // COM_SD_GATEWAYCLIENT_HPP
