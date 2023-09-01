//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/ppl/pipelines_manager.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Vesselin Mladenov
/// @version
/// @remarks
///

#ifndef UCM_AAP_LIBRARY_LIB_PPL_PIPELINES_MANAGER_H_
#define UCM_AAP_LIBRARY_LIB_PPL_PIPELINES_MANAGER_H_

#include <mutex>
#include <queue>
#include <memory>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/ppl/instance.h"
#include "ucm/lib/ppl/thread_pipeline.h"


namespace bosch {
namespace vrte {
namespace ucm {
namespace lib {
namespace ppl {

class PipelinesManager final
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_ucm_lib_ppl_PipelinesManager, CTor);
    FRIEND_TEST(Test_ucm_lib_ppl_PipelinesManager, Thread);
    FRIEND_TEST(Test_ucm_lib_ppl_PipelinesManager, Acquire);
    FRIEND_TEST(Test_ucm_lib_ppl_PipelinesManager, ThreadsStartoff);
    FRIEND_TEST(Test_ucm_lib_ppl_PipelinesManager, ThreadsShutdown);
#endif

public:

    explicit PipelinesManager(size_t ppls, size_t nths,
                              size_t nelem, size_t esize);

    // move semantic
    PipelinesManager(PipelinesManager&&) = delete;
    PipelinesManager& operator=(PipelinesManager&&) = delete;

    // copy semantics
    PipelinesManager(const PipelinesManager& other) = delete;
    PipelinesManager& operator=(const PipelinesManager&) = delete;

    ~PipelinesManager();

    std::shared_ptr<Instance> acquire();

    ThreadPipeline& thread(size_t idx);

    void threads_startoff(utl::ThreadFactory&);
    void threads_shutdown();

private:
    std::size_t nthreads_;
    mutable std::mutex mutex_{};
    std::vector<std::shared_ptr<Instance>> cache_{};
    std::vector<std::unique_ptr<ThreadPipeline>> threads_{};
};

}    // namespace ppl
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif    // UCM_AAP_LIBRARY_LIB_PPL_PIPELINES_MANAGER_H_
