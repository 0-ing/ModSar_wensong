//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2022 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/app/upd/phase_install.h
/// @brief
/// @copyright    Robert Bosch GmbH 2022
/// @author       Vesselin Mladenov
/// @version
/// @remarks
/// @ingroup      bosch_vrte_ucm_app_upd

#ifndef UCM_AAP_LIBRARY__UCM_APP_UPD__PHASE_INSTALL_H_
#define UCM_AAP_LIBRARY__UCM_APP_UPD__PHASE_INSTALL_H_

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/upd/phase.h"
#include "ucm/lib/dev/image.h"
#include "ucm/lib/dev/device.h"


/// @addtogroup bosch_vrte_ucm_app_upd
/// @{

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace app   {
namespace upd   {

/// @class PhaseInstall
/// @ingroup bosch_vrte_ucm_app_upd
/// @brief Provide default implementation of PhaseInstall.
///
class PhaseInstall final : public lib::upd::Phase
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test__ucm_app_upd__PhaseInstall, CTor);
    FRIEND_TEST(Test__ucm_app_upd__PhaseInstall, Setup);
    FRIEND_TEST(Test__ucm_app_upd__PhaseInstall, Verify);
    FRIEND_TEST(Test__ucm_app_upd__PhaseInstall, Perform);
    FRIEND_TEST(Test__ucm_app_upd__PhaseInstall, LockImage);
    FRIEND_TEST(Test__ucm_app_upd__PhaseInstall, LockDevice);
    FRIEND_TEST(Test__ucm_app_upd__PhaseInstall, TargetDevid);
    FRIEND_TEST(Test__ucm_app_upd__PhaseInstall, AfterSuccess);
    FRIEND_TEST(Test__ucm_app_upd__PhaseInstall, AfterFailure);
#endif

public:
    explicit PhaseInstall(lib::upd::UpdateContext& uctx);

    PhaseInstall(PhaseInstall     &&) = delete;
    PhaseInstall(PhaseInstall const&) = delete;

    PhaseInstall& operator=(PhaseInstall     &&) = delete;
    PhaseInstall& operator=(PhaseInstall const&) = delete;

    ~PhaseInstall() = default;

    ara_error_type setup() noexcept override;

    ara_error_type verify() noexcept override;

    ara_error_type perform() noexcept override;

    ara_error_type after_failure() noexcept override;

    ara_error_type after_success() noexcept override;

private:
    std::shared_ptr<lib::dev::Image>  image_{};
    std::shared_ptr<lib::dev::Device> devspecs_{};

    id_type target_devid() noexcept;

    ara_error_type lock_image(const std::string&) noexcept;

    ara_error_type lock_device(const std::string&, const id_type&) noexcept;
};

}    // namespace upd
}    // namespace app
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}
#endif    // UCM_AAP_LIBRARY__UCM_APP_UPD__PHASE_INSTALL_H_
