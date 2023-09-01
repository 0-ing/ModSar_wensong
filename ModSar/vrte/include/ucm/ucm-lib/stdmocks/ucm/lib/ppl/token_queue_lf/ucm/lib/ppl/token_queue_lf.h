//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/ppl/token_queue_lf.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Vesselin Mladenov
/// @version
/// @remarks
///

#ifndef UCM_AAP_LIBRARY_LIB_PPL_TOKEN_QUEUE_LF_H_
#define UCM_AAP_LIBRARY_LIB_PPL_TOKEN_QUEUE_LF_H_

#include <mutex>
#include <condition_variable>


#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/mock/sequence.h"
#include "ucm/lib/ppl/factor.h"
#include "ucm/lib/ppl/token_queue.h"

namespace bosch {
namespace vrte {
namespace ucm {
namespace lib {
namespace ppl {

class TokenQueueLF
    : public TokenQueue
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_ucm_lib_ppl_TokenQueueLF, CTor);
    FRIEND_TEST(Test_ucm_lib_ppl_TokenQueueLF, Reset);
    FRIEND_TEST(Test_ucm_lib_ppl_TokenQueueLF, Release);
    FRIEND_TEST(Test_ucm_lib_ppl_TokenQueueLF, Acquire0);
    FRIEND_TEST(Test_ucm_lib_ppl_TokenQueueLF, Acquire1);
    FRIEND_TEST(Test_ucm_lib_ppl_TokenQueueLF, Acquire2);
    FRIEND_TEST(Test_ucm_lib_ppl_TokenQueueLF, Acquire3);
    FRIEND_TEST(Test_ucm_lib_ppl_TokenQueueLF, ReleaseBaseimpl);
    FRIEND_TEST(Test_ucm_lib_ppl_TokenQueueLF, FactorIncrease);
    FRIEND_TEST(Test_ucm_lib_ppl_TokenQueueLF, FactorDecrease);
#endif

    using Base = TokenQueue;

public:
    TokenQueueLF(const Tag::taskid_type& maxfactor)
        : factor_(maxfactor)
    {
    }

    // copy semantics
    TokenQueueLF(const TokenQueueLF& other) = delete;
    TokenQueueLF& operator=(const TokenQueueLF&) = delete;

    // move semantic
    TokenQueueLF(TokenQueueLF&&) noexcept = delete;
    TokenQueueLF& operator=(TokenQueueLF&&) = delete;

    virtual ~TokenQueueLF() = default;

    virtual void reset() noexcept override { pop<void>(); }

    __attribute__((warn_unused_result))
    virtual Token* acquire() noexcept override { return nullptr; }

    __attribute__((warn_unused_result))
    virtual Token* release(Token*) noexcept override { return pop<Token*>(); }

    __attribute__((warn_unused_result))
    virtual Token* acquire(const Tag&) noexcept { return pop<Token*>(); }

    virtual void release_baseimpl(Token*) noexcept { pop<void>(); }

    Tag factor_increase() { return pop<Tag>(); }

    void factor_decrease() { pop<void>(); }

protected:
    Factor factor_;
    bool notified_{false};
    mutable std::mutex mutex_{};
    std::condition_variable cond_{};
};


}    // namespace ppl
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif    // UCM_AAP_LIBRARY_LIB_PPL_TOKEN_QUEUE_LF_H_
