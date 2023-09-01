//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/ppl/task.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Vesselin Mladenov
/// @version
/// @remarks
///

#ifndef UCM_AAP_LIBRARY_LIB_PPL_TASK_H_
#define UCM_AAP_LIBRARY_LIB_PPL_TASK_H_

#include <atomic>
#include <memory>
#include <utility>
#include <functional>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/mock/sequence.h"
#include "ucm/lib/ppl/tag.h"
#include "ucm/lib/ppl/token.h"
#include "ucm/lib/ppl/signal.h"
#include "ucm/lib/ppl/bucket.h"

namespace bosch {
namespace vrte {
namespace ucm {
namespace lib {
namespace ppl {

/// @brief The base class for any Task that is run by Worker.
class Task
    : virtual protected ucm::mock::Sequence
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_ucm_lib_ppl_Task, Runner);
    FRIEND_TEST(Test_ucm_lib_ppl_Task, Constructor);
    FRIEND_TEST(Test_ucm_lib_ppl_Task, AfterSuccess);
    FRIEND_TEST(Test_ucm_lib_ppl_Task, AfterFailure);
    FRIEND_TEST(Test_ucm_lib_ppl_Task, ForwardSignal);
    FRIEND_TEST(Test_ucm_lib_ppl_Task, FeedbackSignal);
    FRIEND_TEST(Test_ucm_lib_ppl_Task, BroadcastSignal);
#endif

public:
    struct Callbacks
    {
        std::function<Token*()> token_create_{};
        std::function<Token*(Token*)> token_release_{};
        std::function<Token*(const Tag&)> token_acquire_{};
    };

    struct InOutArgs
    {
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_Task_InOutArgs, Constructor);
#endif

        InOutArgs() noexcept = default;
        InOutArgs(Token* token) noexcept
            : input_token_{token}
        {
        }

        Token* input_token_{nullptr};
        Token* forward_token_{nullptr};
        Token* feedback_token_{nullptr};
    };

    explicit Task(std::string&& name, Tag&& tag, Callbacks&& callbacks) noexcept
        : tag_(std::move(tag))
        , name_(std::move(name))
        , token_create_cb_{std::move(callbacks.token_create_)}
        , token_release_cb_{std::move(callbacks.token_release_)}
        , token_acquire_cb_{std::move(callbacks.token_acquire_)}
    {
    }
    // copy semantics
    Task(const Task& other) = delete;
    Task& operator=(const Task&) = delete;

    // move semantic
    Task(Task&&) = delete;
    Task& operator=(Task&&) = delete;

    virtual ~Task();

    const std::string& name() const noexcept;

    /// @brief Method called when a Task is put into a Worker queue.
    /// The method is automatically invoked by the Worker right before the Task
    /// is placed into its queue. If the method fails, the Task is most probably
    /// not placed in the Worker's queue. Usually this is done within th
    /// Worker::create_task method and leads to an exception being thrown
    /// if this before method returns false
    __attribute__((warn_unused_result))
    bool before() noexcept { return pop<bool>(); }

    /// @brief method invoked by a pipeline worker
    __attribute__((warn_unused_result))
    bool execute(InOutArgs&) noexcept { return pop<bool>(); }

    /// @brief Executed after the execute method fails
    /// @note automatically invoked by the worker
    bool after_failure() noexcept { return pop<bool>(); }

    /// @brief Executed after the execute method succeeds
    /// @note automatically invoked by the worker
    bool after_success() noexcept { return pop<bool>(); }

    bool is_task_complete() const noexcept;

    bool unit_done() const noexcept;

    void unit_begin() noexcept;

    const Signal& status() const noexcept;

protected:
    Tag tag_{};
    std::string name_{};
    bool complete_{false};
    bool unit_done_{false};
    Signal status_{Signal::Result::Ok};
    std::atomic_bool after_flag_{false};

    void unit_complete() noexcept;

    void task_complete() noexcept;

    virtual bool impl_before() noexcept = 0;

    virtual bool impl_execute(InOutArgs&) noexcept = 0;

    virtual bool impl_after_failure() noexcept = 0;

    virtual bool impl_after_success() noexcept = 0;

    __attribute__((warn_unused_result))
    Token* token_create() noexcept;

    __attribute__((warn_unused_result))
    Token* token_release(Token*) noexcept;

    __attribute__((warn_unused_result))
    Token* token_acquire(const Tag&) noexcept;

    __attribute__((warn_unused_result))
    Token* input_token(InOutArgs&) noexcept;

    __attribute__((warn_unused_result))
    Token* forward_token(InOutArgs&, Token*) noexcept;

    __attribute__((warn_unused_result))
    Token* feedback_token(InOutArgs&, Token*) noexcept;

    void forward_signal(InOutArgs&, Signal&&) noexcept { pop<void>(); }

    void feedback_signal(InOutArgs&, Signal&&) noexcept { pop<void>(); }

    void broadcast_signal(InOutArgs&, Signal&&) noexcept { pop<void>(); }

private:
    std::function<Token*()> token_create_cb_{};
    std::function<Token*(Token*)> token_release_cb_{};
    std::function<Token*(const Tag&)> token_acquire_cb_{};
};

inline const std::string& Task::name() const noexcept
{
    return pop<std::string const&>();
}

inline const Signal& Task::status() const noexcept
{
    return pop<Signal const&>();
}

inline bool Task::is_task_complete() const noexcept
{
    return pop<bool>();
}

inline bool Task::unit_done() const noexcept
{
    return pop<bool>();
}

inline void Task::unit_begin() noexcept
{
    pop<void>();
}

inline void Task::unit_complete() noexcept
{
    pop<void>();
}

inline void Task::task_complete() noexcept
{
    pop<void>();
}

inline Token* Task::token_create() noexcept
{
    return pop<Token*>();
}

inline Token* Task::token_release(Token*) noexcept
{
    return pop<Token*>();
}

inline Token* Task::token_acquire(const Tag&) noexcept
{
    return pop<Token*>();
}

inline Token* Task::input_token(Task::InOutArgs&) noexcept
{
    return pop<Token*>();
}

inline Token* Task::forward_token(Task::InOutArgs&, Token*) noexcept
{
     return nullptr;
}

inline Token* Task::feedback_token(Task::InOutArgs&, Token*) noexcept
{
    return nullptr;
}

}    // namespace ppl
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif    // UCM_AAP_LIBRARY_LIB_PPL_TASK_H_
