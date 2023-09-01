//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/ppl/thread_pipeline.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY_LIB_PPL_THREAD_PIPELINE_H_
#define UCM_AAP_LIBRARY_LIB_PPL_THREAD_PIPELINE_H_

#include <queue>
#include <mutex>
#include <condition_variable>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/utl/thread.h"
#include "ucm/lib/ppl/worker.h"


namespace bosch {
namespace vrte {
namespace ucm {
namespace lib {
namespace ppl {

class ThreadPipeline final : public lib::utl::Thread
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_ucm_lib_ppl_ThreadPipeline, Cancel);
    FRIEND_TEST(Test_ucm_lib_ppl_ThreadPipeline, Enqueue);
#endif

public:
    explicit ThreadPipeline(utl::ThreadAttr&&, utl::ThreadFactory&);

    // copy semantics
    ThreadPipeline(const ThreadPipeline&) = delete;
    ThreadPipeline& operator=(const ThreadPipeline&) = delete;

    // move semantic
    ThreadPipeline(ThreadPipeline&&) = delete;
    ThreadPipeline& operator=(ThreadPipeline&&) = delete;

    virtual ~ThreadPipeline() = default;

    void enqueue(std::shared_ptr<Worker> worker);

protected:
    void thread_cancel() noexcept override;
    void thread_function() noexcept override;

private:
    bool aborted_{false};
    bool notified_{false};
    mutable std::mutex mutex_{};
    std::condition_variable cond_{};
    std::shared_ptr<Worker> worker_execd_{};
    std::queue<std::shared_ptr<Worker>> worker_queue_{};

    std::shared_ptr<Worker> retrieve() noexcept;
    std::shared_ptr<Worker> _pop_worker() noexcept;
    std::shared_ptr<Worker> _nul_worker() noexcept;
};

}    // namespace ppl
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif    // UCM_AAP_LIBRARY_LIB_PPL_THREAD_PIPELINE_H_
