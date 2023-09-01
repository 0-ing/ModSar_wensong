//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/ppl/worker.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Vesselin Mladenov
/// @version
/// @remarks
///

#ifndef UCM_AAP_LIBRARY_LIB_PPL_WORKER_H_
#define UCM_AAP_LIBRARY_LIB_PPL_WORKER_H_

#include <atomic>
#include <cstddef>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/ppl/task.h"
#include "ucm/lib/ppl/tq_manager.h"
#include "ucm/lib/utl/async_barrier.h"

namespace bosch {
namespace vrte {
namespace ucm {
namespace lib {
namespace ppl {

class Worker
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_ucm_lib_ppl_Worker, CTor);
    FRIEND_TEST(Test_ucm_lib_ppl_Worker, TQMChain);
    FRIEND_TEST(Test_ucm_lib_ppl_Worker, TokenAborts);
    FRIEND_TEST(Test_ucm_lib_ppl_Worker, TokenTerminates);
    FRIEND_TEST(Test_ucm_lib_ppl_Worker, TokenHasFailure);
    FRIEND_TEST(Test_ucm_lib_ppl_Worker, ReleaseTokens);
    FRIEND_TEST(Test_ucm_lib_ppl_Worker, AbortTasks);
    FRIEND_TEST(Test_ucm_lib_ppl_Worker, TerminateTasks);
    FRIEND_TEST(Test_ucm_lib_ppl_Worker, ForwardTerminate);
    FRIEND_TEST(Test_ucm_lib_ppl_Worker, FeedbackTerminate);
    FRIEND_TEST(Test_ucm_lib_ppl_Worker, RunTasks);
    FRIEND_TEST(Test_ucm_lib_ppl_Worker, RunTasksWait);
    FRIEND_TEST(Test_ucm_lib_ppl_Worker, RunTasksPeak);
    FRIEND_TEST(Test_ucm_lib_ppl_Worker, RunTasksChain);
    FRIEND_TEST(Test_ucm_lib_ppl_Worker, RunProducer);
    FRIEND_TEST(Test_ucm_lib_ppl_Instance, Terminate);
    FRIEND_TEST(Test_ucm_lib_ppl_Instance, TerminateWait);
#endif

public:
    explicit Worker(const std::string& name,
                    std::shared_ptr<Bucket> bucket) noexcept;

    // copy semantics
    Worker(const Worker& other) = delete;
    Worker& operator=(const Worker&) = delete;

    // move semantic
    Worker(Worker&&) noexcept = delete;
    Worker& operator=(Worker&&) = delete;

    virtual ~Worker();

    void chain_next(Worker* other) noexcept;
    void chain_prev(Worker* other) noexcept;

    void act_as_producer(bool) noexcept;
    bool act_as_producer() const noexcept;

    template<typename _Derived, typename... _Rest>
    void create_task(_Rest&&... rest)
    {
        Tag tag = bucket_->factor_increase();
        try {
            auto rv = register_task(std::move(std::make_unique<_Derived>(
                    std::move(tag), std::move(task_callbacks()),
                    std::forward<_Rest>(rest)...)));
            if (rv != true)
                throw std::runtime_error("Failed to register task!");
        } catch (...) {
            bucket_->factor_decrease();
            std::rethrow_exception(std::current_exception());
        }
    }

    template<typename _Derived, typename... _Rest>
    void create_task(std::string&& name, _Rest&&... rest)
    {
        Tag tag = bucket_->factor_increase();
        try {
            auto rv = register_task(std::move(std::make_unique<_Derived>(
                    std::move(name), std::move(tag),
                    std::move(task_callbacks()),
                    std::forward<_Rest>(rest)...)));
            if (rv != true)
                throw std::runtime_error("Failed to register task!");
        } catch (...) {
            bucket_->factor_decrease();
            std::rethrow_exception(std::current_exception());
        }
    }

    bool run_tasks() noexcept;

    bool run_tasks_wait() noexcept;

    bool run_tasks_peak() const noexcept;

    bool run_tasks_chain(bool) noexcept;

    __attribute__((warn_unused_result))
    Token* create_token();

    __attribute__((warn_unused_result))
    Token* acquire_token(std::size_t tid) noexcept;

    __attribute__((warn_unused_result))
    Token* inject_incoming(Token*) noexcept;

    __attribute__((warn_unused_result))
    Token* inject_feedback(Token*) noexcept;

    const std::string& name() const noexcept;

    std::shared_ptr<TQManager> tq_manager() noexcept;

    const Signal& result_for_task(std::size_t idx) const;

    const Signal& status() const noexcept;

protected:
    Signal status_{};
    std::string name_{};
    bool act_as_producer_{false};
    utl::AsyncBarrier barrier_{};
    std::shared_ptr<Bucket> bucket_;
    std::shared_ptr<TQManager> tqm_;
    std::vector<std::unique_ptr<Task>> tasks_{};

    void abort_tasks() noexcept;

    bool run_producer() noexcept;

    bool result(bool flag) noexcept;

    void release_tokens() noexcept;

    void terminate_tasks() noexcept;

    bool token_aborts(Token*) noexcept;

    bool token_terminates(Token*) noexcept;

    bool token_hasfailure(Token*) noexcept;

    __attribute__((warn_unused_result))
    Token* forward_terminate(Token*) noexcept;

    __attribute__((warn_unused_result))
    Token* feedback_terminate(Token*) noexcept;

    bool register_task(std::unique_ptr<Task>&&);

    Task::Callbacks task_callbacks() const noexcept;

    bool run_tasks_chain(std::size_t, Token*) noexcept;
};

inline const std::string& Worker::name() const noexcept
{
    return name_;
}

inline const Signal& Worker::status() const noexcept
{
    return status_;
}

inline void Worker::act_as_producer(bool flag) noexcept
{
    act_as_producer_ = flag;
}

inline bool Worker::act_as_producer() const noexcept
{
    return act_as_producer_;
}

inline Token* Worker::create_token()
{
    return tqm_->token_create();
}

inline Token* Worker::acquire_token(std::size_t tid) noexcept
{
    return tqm_->token_acquire(tid);
}

inline Token* Worker::inject_incoming(Token* token) noexcept
{
    return tqm_->inject_incoming(token);
}

inline Token* Worker::inject_feedback(Token* token) noexcept
{
    return tqm_->inject_feedback(token);
}

inline std::shared_ptr<TQManager> Worker::tq_manager() noexcept
{
    return tqm_;
}

inline const Signal& Worker::result_for_task(std::size_t idx) const
{
    return tasks_.at(idx)->status();
}

inline bool Worker::run_tasks_wait() noexcept
{
    return barrier_.wait();
}

inline bool Worker::run_tasks_peak() const noexcept
{
    return barrier_.peak();
}

}    // namespace ppl
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif    // UCM_AAP_LIBRARY_LIB_PPL_WORKER_H_
