#ifndef PIPC_PROC_REG_LINUX_CLIENT_HPP
#define PIPC_PROC_REG_LINUX_CLIENT_HPP

#include "pipc/linux/UdsConnection.hpp"
#include "pipc/proc_reg/ClientMsg.hpp"
#include "pipc/proc_reg/ServerMsg.hpp"

namespace pipc
{
namespace proc_reg
{
/**
 * @brief Linux-specific implementation of the proc registration client.
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
        m_udsClient.close();
        if (!m_udsClient.connect(PIPC_DAEMON_PATH))
        {
            return false;
        }

        if (!m_udsClient.send(reqMsg))
        {
            return false;
        }

        return m_udsClient.recv(repMsg);
    }

private:
    linux_uds::UdsConnection m_udsClient;
};

} // namespace proc_reg
} // namespace pipc

#endif // PIPC_PROC_REG_LINUX_CLIENT_HPP
