/// @copyright : 2022 Robert Bosch GmbH. All rights reserved.

#ifndef COM_SD_CONFIG_HPP
#define COM_SD_CONFIG_HPP

#include "pipc/transport/Port.hpp"
#include "pipc/session/ProviderId.hpp"

namespace com
{
namespace sd
{
/**
 * @brief The port used for ARA Service Discovery with IPC deployments.
 */
static constexpr pipc::transport::Port SdPortIpc = 1U;

/**
 * @brief The port used for ARA Service Discovery with Some/Ip deployments.
 */
static constexpr pipc::transport::Port SdPortSomeIp = 2U;

/**
 * @brief The provierId used for ARA Service Discovery with Some/Ip deployments.
 */
static constexpr pipc::session::ProviderId ProviderIdSomeIp{1, 1, 1, 3};

} // namespace sd
} // namespace com

#endif // COM_SD_CONFIG_HPP
