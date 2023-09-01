#ifndef SD_APP_REGISTRY_HPP
#define SD_APP_REGISTRY_HPP

#include "AppEntry.hpp"
#include "pipc/Config.hpp"
#include "pipc/utils/Registry.hpp"

namespace pipc
{
namespace sd
{
/** @brief The registry where all of the IApps will be stored. */
using AppRegistry = utils::Registry<rte::IApp*, AppEntry, PIPC_DAEMON_MAX_SERVICE_COMPONENTS>;

} // namespace sd
} // namespace pipc

#endif
