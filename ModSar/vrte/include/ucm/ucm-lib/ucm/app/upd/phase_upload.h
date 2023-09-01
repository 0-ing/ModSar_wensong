//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2022 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/app/upd/phase_upload.h
/// @brief
/// @copyright    Robert Bosch GmbH 2022
/// @author       Vesselin Mladenov
/// @version
/// @remarks
/// @ingroup      bosch_vrte_ucm_app_upd

#ifndef UCM_AAP_LIBRARY__UCM_APP_UPD__PHASE_UPLOAD_H_
#define UCM_AAP_LIBRARY__UCM_APP_UPD__PHASE_UPLOAD_H_

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

/// @class PhaseUpload
/// @ingroup bosch_vrte_ucm_app_upd
/// @brief Provide default implementation of PhaseUpload.
///
class PhaseUpload final : public lib::upd::Phase
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test__ucm_app_upd__PhaseUpload, CTor);
    FRIEND_TEST(Test__ucm_app_upd__PhaseUpload, Setup);
    FRIEND_TEST(Test__ucm_app_upd__PhaseUpload, Verify);
    FRIEND_TEST(Test__ucm_app_upd__PhaseUpload, Perform);
    FRIEND_TEST(Test__ucm_app_upd__PhaseUpload, AfterSuccess);
    FRIEND_TEST(Test__ucm_app_upd__PhaseUpload, AfterFailure);
#endif

public:
    explicit PhaseUpload(lib::upd::UpdateContext& uctx);

    PhaseUpload(PhaseUpload     &&) = delete;
    PhaseUpload(PhaseUpload const&) = delete;

    PhaseUpload& operator=(PhaseUpload     &&) = delete;
    PhaseUpload& operator=(PhaseUpload const&) = delete;

    ~PhaseUpload() = default;

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
#endif    // UCM_AAP_LIBRARY__UCM_APP_UPD__PHASE_UPLOAD_H_
