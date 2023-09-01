/// @copyright : 2022 Robert Bosch GmbH. All rights reserved.

#ifndef PIPC_RPC_LOAN_CLIENT_PTP_LAYER_HPP
#define PIPC_RPC_LOAN_CLIENT_PTP_LAYER_HPP

#include "ClientPtpLayer.hpp"
#include "pipc/loan/Creditor.hpp"

namespace pipc
{
namespace rpc
{
/**
 * @brief LoanClientPtpLayer for all SHM RPC clients.
 *
 * This layer is the app layer for the SHM RPC clients.
 * It extends the Client Ptp Layer with a creditor logic,
 * which is manages the active loans and reclaims them upon
 * server disconnect.
 *
 * @todo
 * The template param needs to get out of here, we need to move Creditor into
 * LoanClientBase/LoanClientBaseFireAndForget and connect the processNotification
 * with a Command.
 */
template<size_t NLoans>
class LoanClientPtpLayer : public ClientPtpLayer
{
    using Creditor = loan::Creditor<NLoans>;
    using LoanId   = loan::LoanId;

public:
    /**
     * @brief Process a notification from the session layer.
     */
    template<size_t NLayer, typename... TLayers>
    inline void processNotification(PtpEndpoint<TLayers...>& endpoint, StateChange change)
    {
        // If the server has gone offline, treat the pending requests as lost
        if (change == StateChange::kInvalid)
        {
            // HINT: Creditor is designed to support multiple debitors, but
            // for RPC we only have one server debitor with ID 0.
            creditor_.reclaim(0);
        }
        ClientPtpLayer::processNotification<NLayer>(endpoint, change);
    }

    /** @brief Get the creditor. */
    Creditor& getCreditor()
    {
        return creditor_;
    }

private:
    /** @brief The creditor logic. */
    Creditor creditor_;
};

} // namespace rpc
} // namespace pipc

#endif
