//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/ppl/tasks/task_files_save.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY_LIB_PPL_TASKS_TASK_FILE_SAVE_H_
#define UCM_AAP_LIBRARY_LIB_PPL_TASKS_TASK_FILE_SAVE_H_

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/mock/sequence.h"
#include "ucm/lib/ppl/task.h"
#include "ucm/lib/utl/file_io.h"


namespace bosch {
namespace vrte {
namespace ucm {
namespace lib {
namespace ppl {

class TaskFileSave : public Task
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_ucm_lib_ppl_tasks_TaskFileSave, CTor);
    FRIEND_TEST(Test_ucm_lib_ppl_tasks_TaskFileSave, ImplBefore1);
    FRIEND_TEST(Test_ucm_lib_ppl_tasks_TaskFileSave, ImplBefore2);
    FRIEND_TEST(Test_ucm_lib_ppl_tasks_TaskFileSave, ImplExecute);
    FRIEND_TEST(Test_ucm_lib_ppl_tasks_TaskFileSave, ImplAfterFailure);
    FRIEND_TEST(Test_ucm_lib_ppl_tasks_TaskFileSave, ImplAfterSuccess);
#endif

public:
    explicit TaskFileSave(Tag&& tag, Callbacks&& callbacks, const std::string& file)
    : Task(std::move(std::string("TaskFileSave")),
           std::move(tag), std::move(callbacks))
    , file_(file)
    {
    }

    // copy semantics
    TaskFileSave(const TaskFileSave& other) = delete;
    TaskFileSave& operator=(const TaskFileSave&) = delete;

    // move semantic
    TaskFileSave(TaskFileSave&&) = delete;
    TaskFileSave& operator=(TaskFileSave&&) = delete;

    virtual ~TaskFileSave() = default;

protected:
    virtual bool impl_before() noexcept override { return pop<bool>(); }

    virtual bool impl_execute(InOutArgs& args) noexcept override { return pop<bool>(); }

    virtual bool impl_after_failure() noexcept override { return pop<bool>(); }

    virtual bool impl_after_success() noexcept override { return pop<bool>(); }

private:
    utl::FileIO file_{};
    std::size_t expected_{0};
    std::size_t progress_{0};
};

}    // namespace ppl
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif    // UCM_AAP_LIBRARY_LIB_PPL_TASKS_TASK_FILE_SAVE_H_
