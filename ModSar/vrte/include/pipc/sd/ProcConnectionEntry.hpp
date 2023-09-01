#ifndef PIPC_PROC_CONNECTION_ENTRY_HPP
#define PIPC_PROC_CONNECTION_ENTRY_HPP

#include "ProcSocketId.hpp"
#include "pipc/pimp/Listener.hpp"
#include "pipc/transport/Runtime.hpp"

namespace pipc
{
namespace sd
{
/**
 * @brief Structure used as an entry in the ProcConnectionRegistry.
 *
 * This structure contains all information that allows a process to communicate with other processes.
 */
struct ProcConnectionEntry
{
    /**
     * @brief Default contructor.
     */
    ProcConnectionEntry() : socketId(0xFFFFU), socket(), listener(socket, transport::Runtime::GetDispatcher())
    {
    }

    /** @brief Method to get the key for the registry. */
    const ProcSocketId& getKey() const
    {
        return socketId;
    }

    /** @brief Method to set the ykey for the registry. */
    void setKey(const ProcSocketId& key)
    {
        socketId = key;
    }

    /** @brief ID of the socket. */
    ProcSocketId socketId;
    /** @brief Socket that allows communication with other processes. */
    pimp::Socket socket;
    /** @brief Listener on the socket. */
    pimp::Listener<transport::MsgDispatcher> listener;
};

} // namespace sd
} // namespace pipc

#endif
