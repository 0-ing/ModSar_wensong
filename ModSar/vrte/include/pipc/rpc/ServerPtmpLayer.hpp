/// @copyright : 2022 Robert Bosch GmbH. All rights reserved.

#ifndef PIPC_RPC_SERVER_PTMP_LAYER_HPP
#define PIPC_RPC_SERVER_PTMP_LAYER_HPP

#include "pipc/Logger.hpp"
#include "pipc/protocol/DefaultLayer.hpp"
#include "pipc/session/SessionId.hpp"
#include "pipc/utils/Command.hpp"

namespace pipc
{
namespace rpc
{
/**
 * @brief Ptmp Layer for a Server.
 *
 * Incoming notification to the server's endpoint are checked by this layer
 * If a client reported StateChange::kInvalid (disconnected) this layer
 * invalidates the pending requests of that client
 */
class ServerPtmpLayer : public protocol::DefaultLayer
{
private:
    using SessionId = session::SessionId;
    using Cmd       = utils::Command_1<void*, void, SessionId>;

public:
    /**
     * We need this method because there are processNotifications with different parameters
     */
    template<size_t NLayer, typename TPtmpEndpoint>
    constexpr void processNotification(TPtmpEndpoint& endpoint, StateChange change)
    {
        protocol::ForwardNotification<NLayer>(endpoint, change);
    }

    /**
     * Process notifications from:
     *  - Provider Endpoint disconnect
     *  - Provider Ptmp Layer received messages
     * If this version of processNotification is called with StateChange::kInvalid, then the client must be disconnected
     */
    template<size_t NLayer,
             size_t NEndpoints,
             typename T0,
             typename T1,
             typename T2,
             typename T3,
             typename T4,
             typename T5,
             typename T6,
             typename T7>
    // template<size_t NLayer, typename TPtmpEndpoint, typename TPtpEndpoint>
    inline void processNotification(protocol::PtmpEndpoint<NEndpoints, T0, T1, T2, T3, T4, T5, T6, T7>& endpoint,
                                            StateChange change,
                                            protocol::PtpEndpoint<T0, T1, T2, T3>& client)
    {
        if (change == StateChange::kInvalid)
        {
            PIPC_LOG_DEBUG() << "Receive disconnect notification from RPC Client " << std::endl;
            cmdOnDisconnect_(endpoint.idx(client));
        }
    }

    /**
     * @brief Register the command to be called when a client's disconnect notification is received.
     *
     * @param command the disconnect command to be registered.
     */
    template<typename... TArgs>
    inline void registerCmdOnDisconnect(TArgs&&... args)
    {
        cmdOnDisconnect_.set(std::forward<TArgs>(args)...);
    }

protected:
    Cmd cmdOnDisconnect_;
};

} // namespace rpc
} // namespace pipc

#endif // PIPC_RPC_SERVER_PTMP_LAYER_HPP
