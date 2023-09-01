//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2020 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/vrte/exm/exm_notify_running.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Vesselin Mladenov
/// @version
/// @remarks
/// @ingroup      bosch_vrte_ucm_vrte_exm

#ifndef UCM_AAP_PROCESSING_VRTE_EXM_NOTIFY_RUNNING_H_
#define UCM_AAP_PROCESSING_VRTE_EXM_NOTIFY_RUNNING_H_

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/app/module_task.h"

/// @addtogroup bosch_vrte_ucm_vrte_exm
/// @{

namespace bosch {
namespace vrte {
namespace ucm {
namespace vrte {
namespace exm {


/// @brief EXM running notification implementation.
///

class ExmNotifyRunning final : public lib::app::ModuleTask
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_ucm_vrte_exm_ExmNotifyRunning, CTor);
    FRIEND_TEST(Test_ucm_vrte_exm_ExmNotifyRunning, Perform);
#endif

public:
    explicit ExmNotifyRunning() = default;

    ExmNotifyRunning(ExmNotifyRunning&&) noexcept = default;
    ExmNotifyRunning& operator=(ExmNotifyRunning&&) = default;

    ExmNotifyRunning(const ExmNotifyRunning&) = default;
    ExmNotifyRunning& operator=(const ExmNotifyRunning&) = default;

    ~ExmNotifyRunning() = default;

    /// @brief Notify Running state to EXM
    /// @param [IN] None
    /// @return  Reporting status success or failure,
    ///          - TRUE : Running state notified
    ///          - FALSE : Failed to report Running state
    virtual bool perform() noexcept override;
};

}    // namespace exm
}    // namespace vrte
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif // UCM_AAP_PROCESSING_VRTE_EXM_NOTIFY_RUNNING_H_
