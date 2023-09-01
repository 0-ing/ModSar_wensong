#ifndef PIPC_PROC_REG_QNX_SERVER_HPP
#define PIPC_PROC_REG_QNX_SERVER_HPP

#include "pipc/utils/String.hpp"
#include "pipc/proc_reg/ClientMsg.hpp"
#include "pipc/proc_reg/ServerMsg.hpp"
#include "pipc/qnx/Channel.hpp"
#include "pipc/qnx/Message.hpp"
#include "pipc/qnx/Types.hpp"

#include <unistd.h>

namespace pipc
{
namespace proc_reg
{
/** @brief QNX-specific reply token. */
using ReplyToken = qnx::ReplyToken;

/**
 * @brief QNX-specific implementation of the proc registration server.
 *
 * This class uses a QNX channel internally to implement the daemon's process
 * registration server. It provides an OS-agnostic interface to handle
 * registration requests for the daemon.
 */
class Server
{
public:
    /** @brief Default constructor. */
    Server()
    {
        channel.create();
    }

    /** @brief Stop receiving requests. */
    void stop()
    {
        channel.close();
    }

    /** @brief Receive a request for a proc registration.
     *
     * Blocks on the channel until a valid request is received or the server is
     * shut down.
     *
     * @return
     * True if a valid request is received, false if the server is shut down.
     */
    bool receiveRequest(ClientMsg& reqMsg, ReplyToken& replyToken)
    {
        qnx::Message<ClientMsg> qnxMsg;
        qnx::MsgInfo msgInfo;
        qnx::ClientInfo clientInfo;
        bool running;
        do
        {
            running = channel.receive(qnxMsg, msgInfo, replyToken);
            if (running)
            {
                bool valid = (qnxMsg.payload.id == ClientMsg::Id::kRegisterReq);
                if (valid)
                {
                    static_cast<void>(ConnectClientInfo_r(msgInfo.scoid, &clientInfo, 0));
                    qnxMsg.payload.uid = clientInfo.cred.euid;
                    reqMsg             = qnxMsg.payload;
                    return true;
                }
                else
                {
                    std::cout << "ProcRegServer: Ignoring unknown message." << std::endl;
                }
            }
        } while (running);
        return running;
    }

    template<typename T>
    inline void sendResponse(const T& msg, ReplyToken replyToken)
    {
        channel.reply(msg, replyToken);
    }

private:
    qnx::Channel channel{PIPC_DAEMON_PATH};
};

} // namespace proc_reg
} // namespace pipc

#endif // PIPC_PROC_REG_QNX_SERVER_HPP
