/// @copyright : 2022 Robert Bosch GmbH. All rights reserved.

#ifndef COM_SD_RUNTIME_HPP
#define COM_SD_RUNTIME_HPP

#include "Client.hpp"
#include "GatewayClient.hpp"
#include "IRuntime.hpp"
#include "pipc/utils/Optional.hpp"
#include "sd/FindServiceDispatcher.hpp"

namespace com
{
namespace sd
{
/**
 * @brief Runtime class for ARA SD.
 *
 * This implementation is most commonly used in all ara::com User Apps.
 * It realizes the Client side of the ARA SD protocol via PIPC & PIMP Sockets.
 */
class Runtime : public IRuntime
{
protected:
    /** @brief Constructor with setup of the SD Clients. */
    Runtime();

    /** @brief Destructor. */
    ~Runtime() = default;

public:
    /**
     * @brief Returns the runtime instance.
     */
    static Runtime& GetInstance();

    /** @brief Overrides of the ARA SD IRuntime interface. */
    Result<void> registerSkeleton(ServiceId serviceId, const InstanceIdentifier& instanceIdentifier) override;
    void unregisterSkeleton(ServiceId serviceId, const InstanceIdentifier& instanceIdentifier) override;
    /** @brief Stub for future implementations. */
    Result<void> registerProxy(ServiceId serviceId, const InstanceIdentifier& instanceIdentifier) override;
    void offerService(ServiceId serviceId, const InstanceIdentifier& instanceIdentifier) override;
    void stopOfferService(ServiceId serviceId, const InstanceIdentifier& instanceIdentifier) override;
    Result<ServiceHandleContainer> findService(ServiceId serviceId,
                                               const InstanceIdentifier& instanceIdentifier) override;
    Result<ServiceHandleContainer> findService(ServiceId serviceId,
                                               const ara::core::InstanceSpecifier& instanceSpecifier) override;
    Result<FindServiceHandle> startFindService(const FindServiceHandler& findServiceHandler,
                                               ServiceId serviceId,
                                               const InstanceIdentifier& instanceIdentifier) override;
    Result<FindServiceHandle> startFindService(const FindServiceHandler& findServiceHandler,
                                               ServiceId serviceId,
                                               const ara::core::InstanceSpecifier& instanceSpecifier) override;
    void stopFindService(FindServiceHandle findServiceHandle) override;

private:
    /** @brief Request FindService with an InstanceIdentifierContainer. */
    Result<ServiceHandleContainer> findService(ServiceId serviceId, const InstanceIdentifierContainer& instanceIds);

    /** @brief Request StartFindService with an InstanceIdentifierContainer. */
    Result<FindServiceHandle> startFindService(const FindServiceHandler& findServiceHandler,
                                               ServiceId serviceId,
                                               const InstanceIdentifierContainer& instanceIds);

    /** @brief Dispatcher to handle calling of FindServiceHandlers. */
    FindServiceDispatcher findServiceDispatcher_;
    /** @brief The SD Client for Ipc deployments. */
    Client ipcClient_;
    /** @brief The SD Client for Some/Ip deployments. */
    GatewayClient someIpClient_;
};

} // namespace sd
} // namespace com

#endif // COM_SD_RUNTIME_HPP
