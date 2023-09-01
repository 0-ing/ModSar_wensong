//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/ppl/tasks/task_file_load.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY_LIB_PPL_TASKS_TASK_FILE_LOAD_H_
#define UCM_AAP_LIBRARY_LIB_PPL_TASKS_TASK_FILE_LOAD_H_

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/ppl/task.h"
#include "ucm/lib/utl/file_io.h"

namespace bosch {
namespace vrte {
namespace ucm {
namespace lib {
namespace ppl {

class TaskFileLoad : public Task
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_ucm_lib_ppl_tasks_TaskFileLoad, CTor);
    FRIEND_TEST(Test_ucm_lib_ppl_tasks_TaskFileLoad, LoadToken);
    FRIEND_TEST(Test_ucm_lib_ppl_tasks_TaskFileLoad, ImplBefore);
    FRIEND_TEST(Test_ucm_lib_ppl_tasks_TaskFileLoad, ImplExecute);
    FRIEND_TEST(Test_ucm_lib_ppl_tasks_TaskFileLoad, ImplAfterFailure);
    FRIEND_TEST(Test_ucm_lib_ppl_tasks_TaskFileLoad, ImplAfterSuccess);
#endif

public:
    explicit TaskFileLoad(Tag&&, Callbacks&&, const std::string& file);

    // copy semantics
    TaskFileLoad(const TaskFileLoad& other) = delete;
    TaskFileLoad& operator=(const TaskFileLoad&) = delete;

    // move semantic
    TaskFileLoad(TaskFileLoad&&) = delete;
    TaskFileLoad& operator=(TaskFileLoad&&) = delete;

    virtual ~TaskFileLoad() = default;

protected:
    virtual bool impl_before() noexcept override;

    virtual bool impl_execute(InOutArgs& args) noexcept override;

    virtual bool impl_after_failure() noexcept override;

    virtual bool impl_after_success() noexcept override;

private:
    utl::FileIO file_{};
    std::size_t expected_{0};
    std::size_t progress_{0};

    bool load_token(Token*) noexcept;
};


}    // namespace ppl
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif    // UCM_AAP_LIBRARY_LIB_PPL_TASKS_TASK_FILE_LOAD_H_
