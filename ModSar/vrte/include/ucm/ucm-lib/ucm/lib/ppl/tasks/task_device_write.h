//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2020 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/ppl/tasks/task_device_write.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY_LIB_PPL_TASKS_TASK_DEVICE_WRITE_H_
#define UCM_AAP_LIBRARY_LIB_PPL_TASKS_TASK_DEVICE_WRITE_H_

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/ppl/task.h"
#include "ucm/lib/dev/posix.h"

namespace bosch {
namespace vrte {
namespace ucm {
namespace lib {
namespace ppl {

class TaskDeviceWrite : public Task
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_ucm_lib_ppl_tasks_TaskDeviceWrite, CTor);
    FRIEND_TEST(Test_ucm_lib_ppl_tasks_TaskDeviceWrite, ImplBefore);
    FRIEND_TEST(Test_ucm_lib_ppl_tasks_TaskDeviceWrite, ImplExecute);
    FRIEND_TEST(Test_ucm_lib_ppl_tasks_TaskDeviceWrite, ImplAfterFailure);
    FRIEND_TEST(Test_ucm_lib_ppl_tasks_TaskDeviceWrite, ImplAfterSuccess);
#endif

public:
    explicit TaskDeviceWrite(Tag&&, Callbacks&&,
                             std::unique_ptr<dev::Posix>&&) noexcept;

    // copy semantics
    TaskDeviceWrite(const TaskDeviceWrite& other) = delete;
    TaskDeviceWrite& operator=(const TaskDeviceWrite&) = delete;

    // move semantic
    TaskDeviceWrite(TaskDeviceWrite&&) = delete;
    TaskDeviceWrite& operator=(TaskDeviceWrite&&) = delete;

    virtual ~TaskDeviceWrite();

protected:
    virtual bool impl_before() noexcept override;

    virtual bool impl_execute(InOutArgs& args) noexcept override;

    virtual bool impl_after_failure() noexcept override;

    virtual bool impl_after_success() noexcept override;

private:
    std::size_t expected_{0};
    std::size_t progress_{0};
    std::unique_ptr<dev::Posix> device_{};

    ssize_t perform_write(const char*, size_t) noexcept;
};

}    // namespace ppl
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif    // UCM_AAP_LIBRARY_LIB_PPL_TASKS_TASK_DEVICE_WRITE_H_
