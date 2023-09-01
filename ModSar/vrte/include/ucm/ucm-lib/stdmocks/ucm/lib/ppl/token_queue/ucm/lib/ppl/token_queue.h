//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/ppl/token_queue.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Vesselin Mladenov
/// @version
/// @remarks
///

#ifndef UCM_AAP_LIBRARY_LIB_PPL_TOKEN_QUEUE_H_
#define UCM_AAP_LIBRARY_LIB_PPL_TOKEN_QUEUE_H_


#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/mock/sequence.h"
#include "ucm/lib/ppl/token.h"

namespace bosch {
namespace vrte {
namespace ucm {
namespace lib {
namespace ppl {

/// @brief FIFO implementation based on single linked list for \ref Token
class TokenQueue
    : virtual protected ucm::mock::Sequence
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_TokenQueue, PushBack);
    FRIEND_TEST(Test_TokenQueue, PopFront);

    FRIEND_TEST(Test_TokenQueueMT, PopWait);
#endif

public:
    TokenQueue() noexcept = default;

    // copy semantics
    TokenQueue(const TokenQueue& other) = delete;
    TokenQueue& operator=(const TokenQueue&) = delete;

    // move semantic
    TokenQueue(TokenQueue&&) noexcept = delete;
    TokenQueue& operator=(TokenQueue&&) = delete;

    virtual ~TokenQueue() = default;

    virtual void reset() noexcept { pop<void>(); }

    __attribute__((warn_unused_result))
    virtual Token* acquire() noexcept { return pop<Token*>(); }

    __attribute__((warn_unused_result))
    virtual Token* release(Token*) noexcept { return nullptr; }

    virtual std::size_t level() const noexcept { return pop<std::size_t>(); }

protected:
    std::size_t level_{0};
    Token* head_{nullptr};
    Token* tail_{nullptr};
};

}    // namespace ppl
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif    // UCM_AAP_LIBRARY_LIB_PPL_TOKEN_QUEUE_H_
