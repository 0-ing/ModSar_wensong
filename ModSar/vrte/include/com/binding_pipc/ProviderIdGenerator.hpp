/// @copyright : 2022 Robert Bosch GmbH. All rights reserved.

#ifndef COM_BINDING_PIPC_PROVIDERIDGENERATOR_HPP
#define COM_BINDING_PIPC_PROVIDERIDGENERATOR_HPP

#include "binding/ReadableComponentIdentifier.hpp"
#include "config/IServiceIntfCfg.hpp"
#include "pipc/session/ProviderId.hpp"

namespace com
{
namespace binding_pipc
{
/**
 * @brief Wrapper class to collect generators for pipc provider IDs from various inputs.
 *
 * These functions convert configuration and identifiers of AUTOSAR Adaptive into internal identifiers for pipc.
 * Modifying this function allows us to decouple pipc identifiers and ara::com identifiers even further.
 */
class ProviderIdGenerator
{
public:
    /**
     * @brief Generate provider ID for an IPC method.
     *
     * @param context The AUTOSAR service deployment configuration
     * @param config  The specific method deployment configuration
     * @return pipc::session::ProviderId A provider ID
     */
    static pipc::session::ProviderId Generate(const config::DeploymentContextIpc& context,
                                              const config::MethodCfgIpc& config)
    {
        return pipc::session::ProviderId{context.serviceInterfaceId,
                                         context.instanceId,
                                         config.methodId,
                                         static_cast<uint8_t>(ara::com::NetworkBindingEnum::IPC)};
    }

    /**
     * @brief Generate provider ID for a SOMEIP method.
     *
     * @param context The AUTOSAR service deployment configuration
     * @param config  The specific method deployment configuration
     * @return pipc::session::ProviderId A provider ID
     */
    static pipc::session::ProviderId Generate(const config::DeploymentContextSomeIp& context,
                                              const config::MethodCfgSomeIp& config)
    {
        return pipc::session::ProviderId{context.serviceInterfaceId,
                                         context.instanceId,
                                         config.methodId,
                                         static_cast<uint8_t>(ara::com::NetworkBindingEnum::SOME_IP)};
    }

    /**
     * @brief Generate provider ID for a SOMEIP event.
     *
     * @param context The AUTOSAR service deployment configuration
     * @param config  The specific event deployment configuration
     * @return pipc::session::ProviderId A provider ID
     */
    static pipc::session::ProviderId Generate(const config::DeploymentContextSomeIp& context,
                                              const config::EventCfgSomeIp& eventCfg)
    {
        return pipc::session::ProviderId{context.serviceInterfaceId,
                                         context.instanceId,
                                         static_cast<uint16_t>(eventCfg.eventId | 0x8000U),
                                         static_cast<uint8_t>(ara::com::NetworkBindingEnum::SOME_IP)};
    }

    /**
     * @brief Generate provider ID for an IPC event.
     *
     * @param context The AUTOSAR service deployment configuration
     * @param config  The specific event deployment configuration
     * @return pipc::session::ProviderId A provider ID
     */
    static pipc::session::ProviderId Generate(const config::DeploymentContextIpc& context,
                                              const config::EventCfgIpc& eventCfg)
    {
        return pipc::session::ProviderId{context.serviceInterfaceId,
                                         context.instanceId,
                                         static_cast<uint16_t>(eventCfg.eventId | 0x8000U),
                                         static_cast<uint8_t>(ara::com::NetworkBindingEnum::IPC)};
    }
};

} // namespace binding_pipc
} // namespace com

#endif // COM_BINDING_PIPC_PROVIDERIDGENERATOR_HPP
