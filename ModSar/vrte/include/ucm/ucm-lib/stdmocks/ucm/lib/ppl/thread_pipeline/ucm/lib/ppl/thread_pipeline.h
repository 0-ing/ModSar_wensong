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

#include "ucm/mock/sequence.h"
#include "ucm/lib/utl/thread.h"
#include "ucm/lib/ppl/worker.h"


namespace bosch {
namespace vrte {
namespace ucm {
namespace lib {
namespace ppl {

class ThreadPipeline final
    : public lib::utl::Thread
    , virtual protected ucm::mock::Sequence
{

public:
    explicit ThreadPipeline(utl::ThreadAttr&& attr,
                            utl::ThreadFactory& factory)
    : lib::utl::Thread(std::move(attr), factory)
    {}

    // copy semantics
    ThreadPipeline(const ThreadPipeline&) = delete;
    ThreadPipeline& operator=(const ThreadPipeline&) = delete;

    // move semantic
    ThreadPipeline(ThreadPipeline&&) = delete;
    ThreadPipeline& operator=(ThreadPipeline&&) = delete;

    virtual ~ThreadPipeline() = default;

    void enqueue(std::shared_ptr<Worker>) { pop<void>(); }

protected:
    void thread_cancel() noexcept override { pop<void>(); }
    void thread_function() noexcept override { pop<void>(); }
};

}    // namespace ppl
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif    // UCM_AAP_LIBRARY_LIB_PPL_THREAD_PIPELINE_H_
