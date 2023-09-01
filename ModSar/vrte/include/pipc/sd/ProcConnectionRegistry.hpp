#ifndef PIPC_PROC_CONNECTION_REGISTRY_HPP
#define PIPC_PROC_CONNECTION_REGISTRY_HPP

#include "ProcConnectionEntry.hpp"
#include "ProcSocketId.hpp"
#include "pipc/Config.hpp"
#include "pipc/NodeId.hpp"
#include "pipc/utils/Registry.hpp"

namespace pipc
{
namespace sd
{
/**
 * @brief Registry with all process connections.
 *
 * It is used by a process to communicate with other processes.
 */
class ProcConnectionRegistry : public utils::Registry<ProcSocketId, ProcConnectionEntry, PIPC_MAX_PROC_CONNECTIONS>
{
public:
    using ConnectionMode = pimp::ConnectionMode;
    /**
     * @brief Adds a new connection to the registry.
     *
     */
    bool addConnection(ProcSocketId socketId, NodeId nodeId, ConnectionMode connectionMode)
    {
        bool created         = false;
        auto connectionEntry = get(socketId, created);

        if (connectionEntry == nullptr)
        {
            // Register full
            return false;
        }

        if (created)
        {
            char path[sizeof(PIPC_PREFIX_PROC_SOCKETS) + 5];
            strcpy(path, PIPC_PREFIX_PROC_SOCKETS);
            sprintf(&path[sizeof(PIPC_PREFIX_PROC_SOCKETS) - 1], "%u", socketId);

            if (connectionEntry->socket.connect(path, connectionMode, nodeId) == ReturnVal::kOk)
            {
                connectionEntry->listener.start();
                return true;
            }
            else
            {
                // Remove the last element because connect was not successful
                size_--;
            }
        }
        else
        {
            if (connectionEntry->socket.getConnectionMode() == connectionMode)
            {
                return true;
            }
            else
            {
                // Stop the listener if we get wrong connectionMode ?
                connectionEntry->listener.stop();
            }
        }
        return false;
    }
};

} // namespace sd
} // namespace pipc

#endif
