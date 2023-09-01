/// @copyright : 2022 Robert Bosch GmbH. All rights reserved.

#ifndef PIPC_RPC_REPLY_MSG_HPP
#define PIPC_RPC_REPLY_MSG_HPP

#include "RequestId.hpp"
#include "pipc/loan/LoanId.hpp"
#include "pipc/utils/Optional.hpp"

namespace pipc
{
namespace rpc
{
/** @brief A reply message sent by the server to the client. */
template<typename T>
struct ReplyMsg
{
    /** @brief Request Id to map this reply to its request message. */
    RequestId requestId;
    /** @brief The reply data. */
    utils::Optional<T> data;
};

/**
 * @brief A reply message sent by the server to the client.
 *
 * Specialization for loans.
 */
template<>
struct ReplyMsg<loan::LoanId>
{
    /** @brief Request Id to map this reply to its request message. */
    RequestId requestId;
    /** @brief The reply data. */
    loan::LoanId data;
    /** @brief Info whether the loan contains a valid reply. */
    bool hasValidReply{true};
};

} // namespace rpc
} // namespace pipc

#endif // PIPC_RPC_REPLY_MSG_HPP
