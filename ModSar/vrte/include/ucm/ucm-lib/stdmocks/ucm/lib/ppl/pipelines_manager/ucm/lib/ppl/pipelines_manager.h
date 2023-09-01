//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         tests/VRTE_UT/ucm/lib/ppl/pipelines_manager/ucm/lib/ppl/pipelines_manager.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Vesselin Mladenov
/// @version
/// @remarks
///

#ifndef UCM_AAP_LIBRARY_LIB_PPL_PIPELINES_MANAGER_H_
#define UCM_AAP_LIBRARY_LIB_PPL_PIPELINES_MANAGER_H_

#include <memory>

#include "ucm/mock/sequence.h"
#include "ucm/lib/ppl/instance.h"
#include "ucm/lib/ppl/thread_pipeline.h"


namespace bosch {
namespace vrte {
namespace ucm {
namespace lib {
namespace ppl {

class PipelinesManager final
    : virtual protected ucm::mock::Sequence
{
public:

    explicit PipelinesManager(size_t, size_t, size_t, size_t)
    {
        pop<void>();
    }

    // move semantic
    PipelinesManager(PipelinesManager&&) = delete;
    PipelinesManager& operator=(PipelinesManager&&) = delete;

    // copy semantics
    PipelinesManager(const PipelinesManager& other) = delete;
    PipelinesManager& operator=(const PipelinesManager&) = delete;

    ~PipelinesManager() {};

    std::shared_ptr<Instance> acquire()
    {
        return pop<std::shared_ptr<Instance>>();
    }

    ThreadPipeline& thread(size_t) { return pop<ThreadPipeline&>(); }

    void threads_startoff(utl::ThreadFactory&)
    {
        pop<void>();
    }

    void threads_shutdown()
    {
        pop<void>();
    }
};

}    // namespace ppl
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif    // UCM_AAP_LIBRARY_LIB_PPL_PIPELINES_MANAGER_H_
