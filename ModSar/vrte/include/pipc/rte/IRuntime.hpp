#ifndef PIPC_RTE_RUNTIME_HPP
#define PIPC_RTE_RUNTIME_HPP

#include "IApp.hpp"
#include "pipc/NodeId.hpp"
#include "pipc/ReturnCode.hpp"
#include "pipc/transport/Runtime.hpp"

namespace pipc
{
namespace rte
{
/**
 * @brief Runtime of PIPC.
 *
 * The runtime contains singleton instances of all classes, which we (usually)
 * need only once. So we provide ...
 * - A MsgDispatcher for callback registration
 * - A list of all registered "apps", which we can use to broadcast some information to all of them
 *   (e.g. a socket is not available any longer or a ProviderId has become available)
 *
 * Specific runtimes have to inherit from this class and implement the methods to register & unregister apps.
 *
 * @todo
 * If we want to support two runtimes at the same time later, we have to add one more indirection.
 * Idea:
 * Have one base class with a list of derived runtimes, the derived runtimes register themselves at
 * the base class upon first usage. The base class receives and forwards the messages to the runtimes.
 */
class IRuntime
{
public:
    using MsgDispatcher = transport::MsgDispatcher;
    using ProviderId    = session::ProviderId;

    /** @brief Get the message dispatcher. */
    virtual MsgDispatcher& getDispatcher() = 0;

    /**
     * @brief Function used to register a new Service Provider.
     *
     * @return True if the Provider's resources are set up & acknowledged, otherwise false.
     */
    virtual ReturnCode registerProvider(IApp& app) = 0;

    /**
     * @brief Function used to register a new Service User.
     *
     * @return True if the Provider's resources are set up & acknowledged, otherwise false.
     *
     * @todo
     * Do we have a case where registerUser fails?
     */
    virtual ReturnCode registerUser(IApp& app) = 0;

    /** @brief Notify the runtime that a provider is starting to offer. */
    virtual void startOffer(IApp& app) = 0;

    /** @brief Notify the runtime that a provider is stopping to offer. */
    virtual void stopOffer(IApp& app) = 0;

    /** @brief Unregister a Service Provider from the runtime. */
    virtual void unregisterProvider(IApp& app) = 0;

    /** @brief Unregister a Service User from the runtime. */
    virtual void unregisterUser(IApp& app) = 0;

    /** @brief Return this node's Id. */
    virtual NodeId getNodeId() const = 0;
};

} // namespace rte
} // namespace pipc

#endif // PIPC_RTE_RUNTIME_HPP
