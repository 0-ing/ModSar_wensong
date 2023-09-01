/// @copyright : 2022 Robert Bosch GmbH. All rights reserved.

#ifndef COM_BINDING_PIPC_METHODSERVERBASE_HPP
#define COM_BINDING_PIPC_METHODSERVERBASE_HPP

#include "com/Types.hpp"
#include "pipc/rpc/LoanServerBase.hpp"

#include <map>

namespace com
{
namespace binding_pipc
{
/**
 * @brief Base class for all method servers.
 *
 * @tparam TOutput The data type of the method output.
 */
template<typename TOutput>
class MethodServerBase
{
    using RpcRequest  = pipc::rpc::RequestMsg<pipc::loan::LoanId>;
    using Placeholder = pipc::utils::Placeholder;

public:
    MethodServerBase() : pendingReplies_(), pendingRepliesMutex_(), nextReplyId_(0)
    {
    }

protected:
    /**
     * @brief Struct for storing data related to a pending reply.
     */
    struct PendingReply
    {
        PendingReply(Future<TOutput>&& future, const RpcRequest& request, void* outputPtr, uint32_t replyId)
            : future(std::move(future)), request(request), outputPtr(outputPtr), replyId(replyId)
        {
        }

        /** @brief The future which will contain the value of the reply. */
        Future<TOutput> future;
        /** @brief The pipc rpc request structure. */
        RpcRequest request;
        /** @brief Pointer to the reply in shm. */
        void* outputPtr;
        /** @brief Id of the reply. */
        uint32_t replyId;
    };

    /**
     * @brief Add a pending reply and return the associated reply id.
     *
     * @remark
     * Must be called under lock, as the caller is expected to add a then() invocation to the future.
     *
     * @param future The future of the pending reply.
     * @param request The pipc rpc request of the pending reply.
     * @param outputPtr Pointer to the reply in shm.
     * @return uint32_t The assigned reply id.
     */
    inline uint32_t addPendingReply(Future<TOutput>&& future, const RpcRequest& request, void* outputPtr)
    {
        auto replyId = nextReplyId_++;
        pendingReplies_.emplace_back(std::move(future), request, outputPtr, replyId);
        return replyId;
    }

    /**
     * @brief Invalidate all pending replies related to a session id.
     *
     * @param sessionId The PIPC session id.
     */
    void invalidatePendingReplies(pipc::session::SessionId sessionId)
    {
        std::lock_guard<std::recursive_mutex> lock{pendingRepliesMutex_};
        for (auto it = pendingReplies_.begin(); it != pendingReplies_.end(); /* no increment */)
        {
            if (it->request.sessionId == sessionId)
            {
                it = pendingReplies_.erase(it);
            }
            else
            {
                ++it;
            }
        }
    }

    /** @brief Vector with all currently pending replies. */
    std::vector<PendingReply> pendingReplies_;
    /**
     * @brief Mutex for accessing the pending replies queue.
     *
     * @remark
     * Needs to be a recursive mutex, as it could be locked by the same
     * context twice, if a Future.then() call gets resolved immediately
     * after registration.
     */
    std::recursive_mutex pendingRepliesMutex_;
    /** @brief The next reply id. */
    uint32_t nextReplyId_;
};

} // namespace binding_pipc
} // namespace com

#endif // COM_BINDING_PIPC_METHODSERVERBASE_HPP
