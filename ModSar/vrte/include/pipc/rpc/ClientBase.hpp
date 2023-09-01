/// @copyright : 2022 Robert Bosch GmbH. All rights reserved.

#ifndef PIPC_RPC_CLIENT_BASE_HPP
#define PIPC_RPC_CLIENT_BASE_HPP

#include "ClientPtpLayer.hpp"
#include "pipc/protocol/DefaultLayer.hpp"
#include "pipc/rte/User.hpp"
#include "pipc/utils/Function.hpp"

namespace pipc
{
namespace rpc
{
/**
 * @brief Base class for RPC Clients.
 *
 * Contains data & functionality common for all RPC clients.
 * Specifically stores a serverOfflineCallback in the base class,
 * which is an (optional) feature to inform the user that pending
 * requests will not be processed.
 *
 * @tparam TClientPtpLayer The app layer in the client's PtpEndpoint.
 */
template<typename TClientPtpLayer = ClientPtpLayer>
class ClientBase : public rte::User<TClientPtpLayer>
{
protected:
    using BaseClass = rte::User<TClientPtpLayer>;

    /** @brief Take over the internal constructors of rte::User. */
    using BaseClass::BaseClass;

    /**
     * @brief Destructor for all RPC clients.
     *
     * In the client's destructor we need to express our desire to not connect again
     * to the session layer, otherwise we try to immediately reconnect during the deconstruction.
     */
    ~ClientBase()
    {
        this->getAppLayer().setConnectionDesired(false);
    }

public:
    /**
     * @brief Register a callback to be informed whenever the server goes offline.
     *
     * @param cbk The callback invoked when the server goes offline.
     */
    constexpr void registerServerOfflineCallback(const utils::Function<void()>& cbk)
    {
        return this->getAppLayer().registerServerOfflineCallback(cbk);
    }
};

} // namespace rpc
} // namespace pipc

#endif // PIPC_RPC_CLIENT_BASE_HPP
