/// @copyright : 2022 Robert Bosch GmbH. All rights reserved.

#ifndef PIPC_RPC_EXECUTORSELECTOR_HPP
#define PIPC_RPC_EXECUTORSELECTOR_HPP

#include "pipc/utils/Function.hpp"
#include "pipc/utils/Placeholder.hpp"

namespace pipc
{
namespace rpc
{
/**
 * @brief ExecutorSelector struct used to select the required executor signature.
 *
 * Depending on whether TReply or TRequest is void, we need the right executor signature.
 */
template<typename TRep, typename TReq>
struct ExecutorSelector
{
    using Executor = utils::Function<void(TRep&, const TReq&)>;
};

/** @brief ExecutorSelector specialization for void request. */
template<typename TRep>
struct ExecutorSelector<TRep, void>
{
    using Executor = utils::Function<void(TRep&)>;
};

/** @brief ExecutorSelector specialization for void reply. */
template<typename TReq>
struct ExecutorSelector<void, TReq>
{
    using Executor = utils::Function<void(const TReq&)>;
};

/** @brief ExecutorSelector specialization for void request & void reply. */
template<>
struct ExecutorSelector<void, void>
{
    using Executor = utils::Function<void()>;
};

/**
 * @brief GenericExecutorSelector struct used to select the required executor signature.
 *
 * Depending on whether TReply or TRequest is void, we need the right exeuctor signature.
 */
template<bool VoidRep, bool VoidReq>
struct GenericExecutorSelector
{
    using Executor = utils::Function<void(utils::Placeholder&, const utils::Placeholder&)>;
};

/** @brief GenericExecutorSelector specialization for void request. */
template<bool VoidRep>
struct GenericExecutorSelector<VoidRep, true>
{
    using Executor = utils::Function<void(utils::Placeholder&)>;
};

/** @brief GenericExecutorSelector specialization for void reply. */
template<bool VoidReq>
struct GenericExecutorSelector<true, VoidReq>
{
    using Executor = utils::Function<void(const utils::Placeholder&)>;
};

/** @brief GenericExecutorSelector specialization for void request & void reply. */
template<>
struct GenericExecutorSelector<true, true>
{
    using Executor = utils::Function<void()>;
};

} // namespace rpc
} // namespace pipc

#endif // PIPC_RPC_EXECUTORSELECTOR_HPP
