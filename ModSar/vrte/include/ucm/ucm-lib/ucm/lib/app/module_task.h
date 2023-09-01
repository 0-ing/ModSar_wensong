//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2020 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/app/module_task.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY_LIB_APP_MODULE_TASK_H_
#define UCM_AAP_LIBRARY_LIB_APP_MODULE_TASK_H_

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/cfg/table.h"

namespace bosch {
namespace vrte {
namespace ucm {
namespace lib {
namespace app {

class ModuleTask
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_ModuleTask, Simple);
#endif

public:
    virtual ~ModuleTask() = default;

    virtual bool perform() noexcept = 0;

protected:
    ModuleTask() = default;

    ModuleTask(ModuleTask&&) noexcept = default;
    ModuleTask& operator=(ModuleTask&&) = default;

    ModuleTask(const ModuleTask&) = default;
    ModuleTask& operator=(const ModuleTask&) = default;
};

}    // namespace app
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY_LIB_APP_MODULE_TASK_H_
