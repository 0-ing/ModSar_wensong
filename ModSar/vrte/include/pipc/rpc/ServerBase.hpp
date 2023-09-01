/// @copyright : 2022 Robert Bosch GmbH. All rights reserved.

#ifndef PIPC_RPC_SERVER_BASE_HPP
#define PIPC_RPC_SERVER_BASE_HPP

#include "ServerPtmpLayer.hpp"
#include "pipc/Config.hpp"
#include "pipc/rte/Provider.hpp"
#include "pipc/transport/Message.hpp"
#include "pipc/utils/Command.hpp"
#include "pipc/utils/Expect.hpp"
#include "pipc/utils/Function.hpp"

#include <mutex>

namespace pipc
{
namespace rpc
{
/**
 * @brief Base class for all RPC servers.
 *
 * Provides common variables and functions.
 *
 * @todo
 * pendingRequests is a candidate to be moved into this class, as it's
 * used by all inherited servers.
 * Maybe also the executor, revisit the structure when we build the delegates.
 */
template<size_t NUsers             = PIPC_MAX_SRVR_USERS,
         typename TServerPtpLayer  = protocol::DefaultLayer,
         typename TServerPtmpLayer = ServerPtmpLayer>
class ServerBase : public rte::Provider<NUsers, TServerPtpLayer, TServerPtmpLayer>
{
private:
    using BaseClass = rte::Provider<NUsers, TServerPtpLayer, TServerPtmpLayer>;

protected:
    using CmdProcess              = utils::Command_1<void*, bool>;
    using CmdDisconnect           = utils::Command_1<void*, void, session::SessionId>;
    using RequestReceivedCallback = utils::Function<void()>;
    using SessionId               = session::SessionId;

    /** @brief Take over the internal constructors of rte::Provider. */
    using BaseClass::BaseClass;

public:
    /**
     * @brief Return the request mutex;
     *
     * @return std::mutex& The request mutex.
     */
    std::mutex& getRequestMutex()
    {
        return requestMutex_;
    }

    /**
     * @brief Register the callback to be called upon request reception.
     *
     * @param callback the callback to be registered.
     * @return ReturnCode tells if a Cbk is already registered or passed callback is registered successfully.
     */
    ReturnCode registerRequestReceivedCallback(RequestReceivedCallback callback)
    {
        ReturnCode ret = ReturnCode::kCallbackAlreadyRegistered;
        if (!requestReceivedCallback_)
        {
            requestReceivedCallback_ = callback;
            ret                      = ReturnCode::kOk;
        }
        return ret;
    }

    /**
     * @brief Register the command to be called when a client's disconnect notification is received.
     *
     * Note that a default command is registered by all Server classes, which will handle
     * the removal of all pending requests related to the client.
     * If this command is overridden, the user needs to take care of calling the Server's
     * internal function invalidatePendingRequests(SessionId) manually.
     *
     * @todo
     * Reconsider this later, but wait until the protocol stack is refactored.
     * It might be worth introducing an interface, where we just override some notification function.
     *
     * @param command the disconnect command to be registered.
     */
    template<typename... TArgs>
    inline void overrideCmdOnDisconnect(TArgs&&... args)
    {
        this->getAppLayer().registerCmdOnDisconnect(std::forward<TArgs>(args)...);
    }

protected:
    /**
     * @brief Invalidate all pending requests with the given Session Id.
     *
     * Utility function called by inheriting classes.
     *
     * @param pendingRequests The queue with pending requests.
     * @param sessionId The sessionId of the disconnected client.
     */
    template<typename TRequest, typename TQueue>
    void invalidatePendingRequests(TQueue& pendingRequests, SessionId sessionId)
    {
        const std::lock_guard<std::mutex> lock(requestMutex_);
        TQueue validReqs;

        while (!pendingRequests.empty())
        {
            TRequest rpcRequest;
            // while() condition already checks that Queue is not empty, ReturnVal::kOk is sure to be returned (neglected)
            static_cast<void>(pendingRequests.try_pop(rpcRequest));
            // If the rpcRequest's sessionId is not matching the disconnected client sessionId then keep it
            if (rpcRequest.sessionId != sessionId)
            {
                validReqs.try_emplace(rpcRequest);
            }
        }
        // Move back all valid requests to the pendingRequests queue
        while (!validReqs.empty())
        {
            TRequest rpcRequest;
            validReqs.try_pop(rpcRequest);
            pendingRequests.try_emplace(rpcRequest);
        }
    }

    /** @brief Callback function called upon Request Reception - gives the command to process the next request. */
    RequestReceivedCallback requestReceivedCallback_;
    /** @brief Mutex for accessing the pendingRequests Queue. */
    std::mutex requestMutex_;
};

} // namespace rpc
} // namespace pipc

#endif // PIPC_RPC_SERVER_BASE_HPP
