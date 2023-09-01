//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2022 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/app/upd/phase_stream.h
/// @brief
/// @copyright    Robert Bosch GmbH 2022
/// @author       Vesselin Mladenov
/// @version
/// @remarks
/// @ingroup      bosch_vrte_ucm_app_upd

#ifndef UCM_AAP_LIBRARY__UCM_APP_UPD__PHASE_STREAM_H_
#define UCM_AAP_LIBRARY__UCM_APP_UPD__PHASE_STREAM_H_

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/dev/image.h"
#include "ucm/lib/dev/device.h"

#include "ucm/lib/upd/phase.h"

/// @addtogroup bosch_vrte_ucm_app_upd
/// @{

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace app   {
namespace upd   {

/// @class PhaseStream
/// @ingroup bosch_vrte_ucm_app_upd
/// @brief Provide default implementation of PhaseStream.
///
class PhaseStream final : public lib::upd::Phase
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test__ucm_app_upd__PhaseStream, CTor);
    FRIEND_TEST(Test__ucm_app_upd__PhaseStream, Setup);
    FRIEND_TEST(Test__ucm_app_upd__PhaseStream, Verify);
    FRIEND_TEST(Test__ucm_app_upd__PhaseStream, Perform);
    FRIEND_TEST(Test__ucm_app_upd__PhaseStream, LockImage);
    FRIEND_TEST(Test__ucm_app_upd__PhaseStream, LockDevice);
    FRIEND_TEST(Test__ucm_app_upd__PhaseStream, TargetDevid);
    FRIEND_TEST(Test__ucm_app_upd__PhaseStream, AfterSuccess);
    FRIEND_TEST(Test__ucm_app_upd__PhaseStream, AfterFailure);
#endif

public:
    explicit PhaseStream(lib::upd::UpdateContext& uctx);

    PhaseStream(PhaseStream     &&) = delete;
    PhaseStream(PhaseStream const&) = delete;

    PhaseStream& operator=(PhaseStream     &&) = delete;
    PhaseStream& operator=(PhaseStream const&) = delete;

    ~PhaseStream() = default;

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
#endif    // UCM_AAP_LIBRARY__UCM_APP_UPD__PHASE_STREAM_H_
