//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/ppl/token_queue_mt.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Vesselin Mladenov
/// @version
/// @remarks
///

#ifndef UCM_AAP_LIBRARY_LIB_PPL_TOKEN_QUEUE_MT_H_
#define UCM_AAP_LIBRARY_LIB_PPL_TOKEN_QUEUE_MT_H_

#include <mutex>
#include <condition_variable>


#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/mock/sequence.h"
#include "ucm/lib/ppl/token_queue.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace ppl   {

class TokenQueueMT
    : public TokenQueue
{
    using Base = TokenQueue;

public:
    TokenQueueMT() noexcept = default;

    // copy semantics
    TokenQueueMT(const TokenQueueMT& other) = delete;
    TokenQueueMT& operator=(const TokenQueueMT&) = delete;

    // move semantic
    TokenQueueMT(TokenQueueMT&&) noexcept = delete;
    TokenQueueMT& operator=(TokenQueueMT&&) = delete;

    virtual ~TokenQueueMT() = default;

    virtual void reset() noexcept override { pop<void>(); }

    __attribute__((warn_unused_result))
    virtual Token* acquire() noexcept override { return pop<Token*>(); }

    virtual Token* acquire(unsigned) noexcept { return pop<Token*>(); }

    __attribute__((warn_unused_result))
    virtual Token* release(Token*) noexcept override { return nullptr; }

    virtual std::size_t level() const noexcept override { return pop<std::size_t>(); }

protected:
    bool notified_{false};
    mutable std::mutex mutex_{};
    std::condition_variable cond_{};
};


}    // namespace pipeline
}    // namespace core
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif    // UCM_AAP_LIBRARY_LIB_PPL_TOKEN_QUEUE_MT_H_
