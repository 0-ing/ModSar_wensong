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

#include "ucm/mock/sequence.h"
#include "ucm/lib/ppl/task.h"
#include "ucm/lib/ppl/tq_manager.h"
#include "ucm/lib/utl/async_barrier.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace ppl   {

class Worker
    : virtual protected ucm::mock::Sequence
{

public:
    explicit Worker(const std::string&,
                    std::shared_ptr<Bucket>) noexcept
    {
    }

    // copy semantics
    Worker(const Worker& other) = delete;
    Worker& operator=(const Worker&) = delete;

    // move semantic
    Worker(Worker&&) noexcept = delete;
    Worker& operator=(Worker&&) = delete;

    virtual ~Worker() = default;

    void chain_next(Worker*) noexcept { pop<void>(); }
    void chain_prev(Worker*) noexcept { pop<void>(); }

    void act_as_producer(bool) noexcept;
    bool act_as_producer() const noexcept;

    template<typename _Derived, typename... _Rest>
    void create_task(_Rest&&...)
    {
       pop<void>();
    }

    template<typename _Derived, typename... _Rest>
    void create_task(std::string&& name, _Rest&&... rest)
    {
        pop<void>();
    }

    bool run_tasks() noexcept { return pop<bool>(); }

    bool run_tasks_wait() noexcept;

    bool run_tasks_peak() const noexcept;

    bool run_tasks_chain(bool) noexcept { return pop<bool>(); }

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
    std::vector<std::unique_ptr<Task>> tasks_{};

    void abort_tasks() noexcept { pop<void>(); }

    bool run_producer() noexcept { return pop<bool>(); }

    bool result(bool) noexcept { return pop<bool>(); }

    void release_tokens() noexcept { pop<void>(); }

    void terminate_tasks() noexcept { pop<void>(); }

    bool token_aborts(Token*) noexcept { return pop<bool>(); }

    bool token_terminates(Token*) noexcept { return pop<bool>(); }

    bool token_hasfailure(Token*) noexcept { return pop<bool>(); }

    __attribute__((warn_unused_result))
    Token* forward_terminate(Token*) noexcept { return pop<Token*>(); }

    __attribute__((warn_unused_result))
    Token* feedback_terminate(Token*) noexcept { return pop<Token*>(); }

    bool register_task(std::unique_ptr<Task>&&) { return pop<bool>(); }

    Task::Callbacks task_callbacks() const noexcept { return pop<Task::Callbacks>(); }

    bool run_tasks_chain(std::size_t, Token*) noexcept { return pop<bool>(); }
};

inline const std::string& Worker::name() const noexcept
{
    return pop<std::string const&>();
}

inline const Signal& Worker::status() const noexcept
{
    return pop<Signal const&>();
}

inline void Worker::act_as_producer(bool) noexcept
{
    pop<void>();
}

inline bool Worker::act_as_producer() const noexcept
{
    return pop<bool>();
}

inline Token* Worker::create_token()
{
    return pop<Token*>();
}

inline Token* Worker::acquire_token(std::size_t) noexcept
{
    return pop<Token*>();
}

inline Token* Worker::inject_incoming(Token*) noexcept
{
    return pop<Token*>();
}

inline Token* Worker::inject_feedback(Token*) noexcept
{
    return pop<Token*>();
}

inline std::shared_ptr<TQManager> Worker::tq_manager() noexcept
{
    return pop<std::shared_ptr<TQManager>>();
}

inline const Signal& Worker::result_for_task(std::size_t) const
{
    return pop<Signal const&>();
}

inline bool Worker::run_tasks_wait() noexcept
{
    return pop<bool>();
}

inline bool Worker::run_tasks_peak() const noexcept
{
    return pop<bool>();
}

}    // namespace ppl
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif    // UCM_AAP_LIBRARY_LIB_PPL_WORKER_H_
