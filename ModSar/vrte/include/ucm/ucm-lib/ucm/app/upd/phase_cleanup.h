//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2022 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/app/upd/phase_cleanup.h
/// @brief
/// @copyright    Robert Bosch GmbH 2022
/// @author       Vesselin Mladenov
/// @version
/// @remarks
/// @ingroup      bosch_vrte_ucm_app_upd

#ifndef UCM_AAP_LIBRARY__UCM_APP_UPD__PHASE_CLEANUP_H_
#define UCM_AAP_LIBRARY__UCM_APP_UPD__PHASE_CLEANUP_H_

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/upd/phase.h"

/// @addtogroup bosch_vrte_ucm_app_upd
/// @{

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace app   {
namespace upd   {

/// @class PhaseCleanup
/// @ingroup bosch_vrte_ucm_app_upd
/// @brief Provide default implementation of PhaseCleanup.
///
class PhaseCleanup final : public lib::upd::Phase
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test__ucm_app_upd__PhaseCleanup, CTor);
    FRIEND_TEST(Test__ucm_app_upd__PhaseCleanup, Setup);
    FRIEND_TEST(Test__ucm_app_upd__PhaseCleanup, Verify);
    FRIEND_TEST(Test__ucm_app_upd__PhaseCleanup, Perform);
    FRIEND_TEST(Test__ucm_app_upd__PhaseCleanup, AfterSuccess);
    FRIEND_TEST(Test__ucm_app_upd__PhaseCleanup, AfterFailure);
#endif

public:
    explicit PhaseCleanup(lib::upd::UpdateContext& uctx);

    PhaseCleanup(PhaseCleanup     &&) = delete;
    PhaseCleanup(PhaseCleanup const&) = delete;

    PhaseCleanup& operator=(PhaseCleanup     &&) = delete;
    PhaseCleanup& operator=(PhaseCleanup const&) = delete;

    ~PhaseCleanup() = default;

    ara_error_type setup() noexcept override;

    ara_error_type verify() noexcept override;

    ara_error_type perform() noexcept override;

    ara_error_type after_failure() noexcept override;

    ara_error_type after_success() noexcept override;
};

}    // namespace upd
}    // namespace app
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}
#endif    // UCM_AAP_LIBRARY__UCM_APP_UPD__PHASE_CLEANUP_H_
