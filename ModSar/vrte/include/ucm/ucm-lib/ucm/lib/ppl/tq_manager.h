//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/ppl/tq_manager.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Vesselin Mladenov
/// @version
/// @remarks
///

#ifndef UCM_AAP_LIBRARY_LIB_PPL_TQ_MANAGER_H_
#define UCM_AAP_LIBRARY_LIB_PPL_TQ_MANAGER_H_

#include <atomic>
#include <cstddef>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/ppl/bucket.h"
#include "ucm/lib/ppl/token_queue_mt.h"

namespace bosch {
namespace vrte {
namespace ucm {
namespace lib {
namespace ppl {

class TQManager final
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_TQManager, Constructor1);
    FRIEND_TEST(Test_TQManager, Constructor2);
    FRIEND_TEST(Test_TQManager, CreateToken);
    FRIEND_TEST(Test_TQManager, ReleaseToken);
    FRIEND_TEST(Test_TQManager, AcquireToken);
    FRIEND_TEST(Test_TQManager, ForwardToken);
    FRIEND_TEST(Test_TQManager, SendbackToken);
    FRIEND_TEST(Test_TQManager, InjectIncoming);
    FRIEND_TEST(Test_TQManager, InjectFeedback);

    FRIEND_TEST(Test_Worker, Operator1);
#endif

    constexpr static unsigned timeout() noexcept
    {
        return 1000*600; // 10 minutes
    }

public:
    explicit TQManager(std::shared_ptr<Bucket> bucket) noexcept;

    // copy semantics
    TQManager(const TQManager& other) = delete;
    TQManager& operator=(const TQManager&) = delete;

    // move semantic
    TQManager(TQManager&&) noexcept = default;
    TQManager& operator=(TQManager&&) = default;

    virtual ~TQManager() = default;

    void reset() noexcept;

    void chain_next(std::shared_ptr<TQManager> other) noexcept;
    void chain_prev(std::shared_ptr<TQManager> other) noexcept;

    /// @brief create a new Token, allocating memory and calling constructor
    Token* token_create();

    /// @brief acquire a Token from the bucket_
    Token* token_acquire(const Tag& tag) noexcept;

    /// @brief release the Token to the bucket_
    __attribute__((warn_unused_result))
    Token* token_release(Token*) noexcept;

    /// @brief inject the token into \ref tq_incoming_ queue
    __attribute__((warn_unused_result))
    Token* inject_incoming(Token*) noexcept;

    /// @brief inject the token into \ref tq_feedback_ queue
    __attribute__((warn_unused_result))
    Token* inject_feedback(Token*) noexcept;

    /// @brief inject the token into \ref tq_next_ queue
    __attribute__((warn_unused_result))
    Token* forward_token(Token*) noexcept;

    /// @brief inject the token into \ref tq_prev_ queue
    __attribute__((warn_unused_result))
    Token* feedback_token(Token*) noexcept;

    ///@brief wait for a token to appear in \ref tq_incoming_ and return it
    __attribute__((warn_unused_result))
    Token* wait_incoming_token() noexcept;

    ///@brief wait for a token to appear in \ref tq_feedback_ and return it
    __attribute__((warn_unused_result))
    Token* wait_feedback_token() noexcept;

    ///@brief fetch a token from \ref tq_incoming_, no wait
    __attribute__((warn_unused_result))
    Token* fetch_incoming_token() noexcept;

    ///@brief fetch a token from \ref tq_feedback_, no wait
    __attribute__((warn_unused_result))
    Token* fetch_feedback_token() noexcept;

    std::shared_ptr<Bucket> bucket() noexcept;

    bool has_next() const noexcept;
    bool has_prev() const noexcept;

private:
    std::shared_ptr<Bucket> bucket_;
    std::weak_ptr<TQManager> tqm_next_{};
    std::weak_ptr<TQManager> tqm_prev_{};
    std::shared_ptr<TokenQueueMT> tq_incoming_;
    std::shared_ptr<TokenQueueMT> tq_feedback_;
};

inline std::shared_ptr<Bucket> TQManager::bucket() noexcept
{
    return bucket_;
}

inline Token* TQManager::token_create()
{
    return new Token;
}

inline Token* TQManager::token_acquire(const Tag& tag) noexcept
{
    return bucket_->token_acquire(tag);
}

inline Token* TQManager::token_release(Token* token) noexcept
{
    return bucket_->token_release(token);
}

inline Token* TQManager::wait_incoming_token() noexcept
{
    return tq_incoming_->acquire(timeout());
}

inline Token* TQManager::wait_feedback_token() noexcept
{
    return tq_feedback_->acquire(timeout());
}

inline Token* TQManager::fetch_incoming_token() noexcept
{
    return tq_incoming_->acquire();
}

inline Token* TQManager::fetch_feedback_token() noexcept
{
    return tq_feedback_->acquire();
}

}    // namespace ppl
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif    // UCM_AAP_LIBRARY_LIB_PPL_TQ_MANAGER_H_
