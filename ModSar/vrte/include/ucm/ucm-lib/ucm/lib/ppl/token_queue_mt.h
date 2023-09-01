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

#include "ucm/lib/ppl/token_queue.h"

namespace bosch {
namespace vrte {
namespace ucm {
namespace lib {
namespace ppl {

class TokenQueueMT : public TokenQueue
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_TokenQueueMT, PopWait);
    FRIEND_TEST(Test_TokenQueueMT, PopWait1);
    FRIEND_TEST(Test_TokenQueueMT, PopWait2);
    FRIEND_TEST(Test_TokenQueueMT, PopWait3);
    FRIEND_TEST(Test_TokenQueueMT, PopWait4);
    FRIEND_TEST(Test_TokenQueueMT, PopWait5);
    FRIEND_TEST(Test_TokenQueueMT, PopWait6);
    FRIEND_TEST(Test_TokenQueueMT, PopWait7);
    FRIEND_TEST(Test_TokenQueueMT, PopWait8);
    FRIEND_TEST(Test_TokenQueueMT, PopWaitFor1);
    FRIEND_TEST(Test_TokenQueueMT, PopWaitFor2);
    FRIEND_TEST(Test_TokenQueueMT, PopWaitFor3);
    FRIEND_TEST(Test_TokenQueueMT, PopWaitFor4);
    FRIEND_TEST(Test_TokenQueueMT, PopNoWait);
    FRIEND_TEST(Test_TokenQueueMT, Reset);
#endif

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

    virtual void reset() noexcept override;

    __attribute__((warn_unused_result))
    virtual Token* acquire() noexcept override;

    virtual Token* acquire(unsigned ms) noexcept;

    __attribute__((warn_unused_result))
    virtual Token* release(Token*) noexcept override;

    virtual std::size_t level() const noexcept override;

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
