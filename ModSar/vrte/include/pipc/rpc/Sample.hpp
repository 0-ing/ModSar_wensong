/// @copyright : 2022 Robert Bosch GmbH. All rights reserved.

#ifndef PIPC_RPC_SAMPLE_HPP
#define PIPC_RPC_SAMPLE_HPP

#include "RequestId.hpp"
#include "pipc/utils/Optional.hpp"

namespace pipc
{
namespace rpc
{
/**
 * @brief A RPC sample for zero-copy RPC.
 *
 * The RPC sample consists of request and reply data, both layed out sequentially in memory.
 * @tparam TReq: request type
 * @tparam TRep: reply type
 */
template<typename TReq, typename TRep>
struct Sample
{
    /** @brief The request. */
    TReq request;
    /** @brief The reply. */
    TRep reply;

    /** @brief Get the offset where the reply data starts. */
    constexpr static size_t GetReplyOffset()
    {
        return offsetof(Sample, reply);
    }
};

/**
 * @brief A RPC sample for zero-copy RPC.
 *
 * Partial specialization for no request data.
 */
template<typename TRep>
struct Sample<void, TRep>
{
    /** @brief The reply. */
    TRep reply;

    /** @brief Get the offset where the reply data starts. */
    constexpr static size_t GetReplyOffset()
    {
        return 0U;
    }
};

/**
 * @brief A RPC sample for zero-copy RPC.
 *
 * Partial specialization for no reply data.
 */
template<typename TReq>
struct Sample<TReq, void>
{
    /** @brief The request. */
    TReq request;

    /** @brief Get the offset where the reply data starts. */
    constexpr static size_t GetReplyOffset()
    {
        return 0U;
    }
};

} // namespace rpc
} // namespace pipc

#endif // PIPC_RPC_SAMPLE_HPP
