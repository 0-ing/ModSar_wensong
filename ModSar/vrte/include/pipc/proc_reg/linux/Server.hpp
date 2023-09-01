#ifndef PIPC_PROC_REG_LINUX_SERVER_HPP
#define PIPC_PROC_REG_LINUX_SERVER_HPP

#include "pipc/linux/UdsConnection.hpp"
#include "pipc/linux/UdsListener.hpp"
#include "pipc/proc_reg/ClientMsg.hpp"
#include "pipc/proc_reg/ServerMsg.hpp"

#include <iostream>

namespace pipc
{
namespace proc_reg
{
/** @brief Linux-specific reply token. */
using ReplyToken = int;

/**
 * @brief Linux-specific implementation of the proc registration server.
 *
 */
class Server
{
public:
    /** @brief Default constructor. */
    Server()
    {
        m_clientListener.createSocket(PIPC_DAEMON_PATH);
    }

    /** @brief Stop the server and close its sockets. */
    void stop()
    {
        m_clientListener.close();
        m_udsServer.close();
    }

    /** @brief Receive a request for a proc registration.
     *
     * Blocks on the channel until a valid request is received or the server is
     * shut down.
     *
     * @return
     * True if a valid request is received, false if the server is shut down.
     */
    bool receiveRequest(ClientMsg& reqMsg, ReplyToken&)
    {
        int clientFd = m_clientListener.acceptClient();
        m_udsServer.close();
        if (!m_udsServer.connect(clientFd))
        {
            return false;
        }

        if (m_udsServer.recv(reqMsg))
        {
            if (reqMsg.id == ClientMsg::Id::kRegisterReq)
            {
                linux_uds::UdsPeerCredentials credentials;
                if (m_udsServer.getPeerCredentials(credentials))
                {
                    reqMsg.uid = credentials.uid;
                    return true;
                }
            }
            else
            {
                std::cout << "ProcRegServer: Ignoring unknown message." << std::endl;
            }
        }

        return false;
    }

    template<typename T>
    inline void sendResponse(const T& msg, ReplyToken)
    {
        m_udsServer.send(msg);
    }

private:
    linux_uds::UdsListener m_clientListener;
    linux_uds::UdsConnection m_udsServer;
};

} // namespace proc_reg
} // namespace pipc

#endif // PIPC_PROC_REG_LINUX_SERVER_HPP
