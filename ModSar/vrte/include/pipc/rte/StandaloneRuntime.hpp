#ifndef PIPC_RTE_STANDALONE_RUNTIME_HPP
#define PIPC_RTE_STANDALONE_RUNTIME_HPP

#include "IRuntime.hpp"
#include "pipc/Logger.hpp"
#include "pipc/NodeId.hpp"

namespace pipc
{
namespace rte
{
/**
 * @brief Standalone Runtime for PIPC.
 *
 * This runtime does nothing by its own and lets the apps manage themselves.
 *
 * @todo
 * For RPC Clients we need a runtime, which manages the sample pools.
 */
class StandaloneRuntime : public IRuntime
{
public:
    /**
     * @brief Returns the runtime instance.
     *
     * The first call of this function should provide a unique node id (by this node id the process is identified).
     * On the next consecutive calls, the id can be ommited.
     */
    static StandaloneRuntime& GetInstance(NodeId nodeId = 0)
    {
        static StandaloneRuntime runtime(nodeId);
        return runtime;
    }

    MsgDispatcher& getDispatcher() override
    {
        return transport::Runtime::GetDispatcher();
    }

    ReturnCode registerProvider(IApp& app) override
    {
        // Providers can initialize immediately in standalone mode
        app.init(true);
        return ReturnCode::kOk;
    }

    ReturnCode registerUser(IApp& app) override
    {
        // Users can initialize immediately in standalone mode
        app.init(true);
        return ReturnCode::kOk;
    }

    void unregisterProvider(IApp&) override
    {
    }

    void unregisterUser(IApp&) override
    {
    }

    /** @brief Notify the runtime that a provider is starting to offer. */
    void startOffer(IApp&) override
    {
    }

    /** @brief Notify the runtime that a provider is stopping to offer. */
    void stopOffer(IApp&) override
    {
    }

    /** @brief Returns the Id of this node. */
    NodeId getNodeId() const override
    {
        return nodeId_;
    }

private:
    /** @brief Private constructor with RAII initialization. */
    StandaloneRuntime(NodeId nodeId) : nodeId_(nodeId)
    {
        PIPC_LOG_DEBUG() << "Constructing standalone runtime with nodeId " << nodeId << std::endl;
    }

    /** @brief Id of this node. */
    NodeId nodeId_;
};

} // namespace rte
} // namespace pipc

#endif // PIPC_RTE_STANDALONE_RUNTIME_HPP
