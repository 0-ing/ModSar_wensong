/// @copyright : 2022 Robert Bosch GmbH. All rights reserved.

#ifndef PIPC_RPC_LOAN_SERVER_PTP_LAYER_HPP
#define PIPC_RPC_LOAN_SERVER_PTP_LAYER_HPP

#include "pipc/Config.hpp"
#include "pipc/Logger.hpp"
#include "pipc/loan/Debitor.hpp"
#include "pipc/protocol/DefaultLayer.hpp"
#include "pipc/queue/SpScQueue.hpp"

namespace pipc
{
namespace rpc
{
/**
 * @brief Ptp Layer for a LoanServer.
 *
 * Incoming notification to the server's endpoint are checked by this layer
 * If a client reported StateChange::kInvalid (disconnected) this layer
 * invalidates the pending requests of that client
 *
 * @tparam MaxLoans The max. no. of loans from a client
 */
template<size_t MaxLoans = PIPC_MAX_CONCURRENT_CLIENT_REQUESTS>
class LoanServerPtpLayer : public protocol::DefaultLayer
{
private: /** @brief Type-agnostic Debitor class. */
    using Debitor = loan::Debitor<utils::Placeholder, MaxLoans>;

public:
    /** @brief getter for debitor*/
    Debitor& getDebitor()
    {
        return debitor_;
    };

protected:
    /** @brief Debitor class with access to SamplePool.*/
    Debitor debitor_;
};

} // namespace rpc
} // namespace pipc

#endif // PIPC_RPC_LOAN_SERVER_PTP_LAYER_HPP
