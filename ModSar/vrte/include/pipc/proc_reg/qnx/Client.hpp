#ifndef PIPC_PROC_REG_QNX_CLIENT_HPP
#define PIPC_PROC_REG_QNX_CLIENT_HPP

#include "pipc/proc_reg/ClientMsg.hpp"
#include "pipc/proc_reg/ServerMsg.hpp"
#include "pipc/qnx/Connection.hpp"
#include "pipc/qnx/Message.hpp"
#include "pipc/qnx/Types.hpp"
#include "pipc/utils/String.hpp"

#include <unistd.h>

namespace pipc
{
namespace proc_reg
{
/**
 * @brief QNX-specific implementation of the proc registration client.
 *
 * This class uses a QNX connection internally to implement the process
 * registration client. It provides an OS-agnostic interface to handle
 * registration requests towards the daemon.
 *
 * @todo
 * Component split is unclear:
 * - Split by layers proc_reg and service_discovery later?
 * - Introduce runtime classes for daemon and proc?
 */
class Client
{
public:
    /** @brief Default constructor. */
    Client()
    {
        // connection.connect();
    }

    /** @brief Receive a request for a proc registration.
     *
     * Blocks on the channel until a valid response is received or the server is
     * shut down.
     *
     * @return
     * True if a valid request is sent, false if the server is shut down.
     */
    bool sendRequest(const ClientMsg& reqMsg, ServerMsg& repMsg)
    {
        qnx::Message<ClientMsg> qnxReqMsg;
        qnxReqMsg.payload = reqMsg;
        auto success      = connection.connect();
        if (success)
        {
            success = connection.send(qnxReqMsg, repMsg);
        }
        return success;
    }

private:
    qnx::Connection connection{PIPC_DAEMON_PATH};
};

} // namespace proc_reg
} // namespace pipc

#endif // PIPC_PROC_REG_QNX_CLIENT_HPP
