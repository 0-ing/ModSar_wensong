//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/app/pkg/bin/v0102/swp_process.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks
/// @ingroup bosch_vrte_ucm_app_pkg_bin_v0102


#ifndef UCM_AAP_LIBRARY__UCM_APP_PKG_BIN_V0102__SWP_PROCESS_H_
#define UCM_AAP_LIBRARY__UCM_APP_PKG_BIN_V0102__SWP_PROCESS_H_

#include <array>
#include <vector>
#include <memory>
#include <utility>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/app/pkg/bin/v0102/data_block.h"
#include "ucm/app/pkg/bin/v0102/auth_block.h"
#include "ucm/app/pkg/bin/v01xx/swp_process.h"

/// @addtogroup bosch_vrte_ucm_app_pkg_bin_v0102
/// @{


namespace bosch {
namespace vrte  {
namespace ucm   {
namespace app   {
namespace pkg   {
namespace bin   {
namespace v0102 {

/// @class SWP_Process
/// @ingroup bosch_vrte_ucm_app_pkg_bin_v0102
/// @brief SWP_Process implementation.

class SWP_Process final : public v01xx::SWP_Process
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test__ucm_app_pkg_bin_v0102__SWP_Process, CTor);
#endif

    using Base = v01xx::SWP_Process;

public:
    explicit SWP_Process(Context_Ptr context,
                         const std::string& outdir,
                         const std::string& swpfile);

    SWP_Process(SWP_Process     &&) = default;
    SWP_Process(SWP_Process const&) = delete;

    SWP_Process& operator=(SWP_Process     &&) = delete;
    SWP_Process& operator=(SWP_Process const&) = delete;

    ~SWP_Process() = default;

protected:
    v01xx::BIT_Process& bitable() noexcept override;

    v01xx::DataBlock& data_block() noexcept override;
    v01xx::AuthBlock& auth_block() noexcept override;

    const v01xx::AuthBlock& auth_block() const noexcept override;
    const v01xx::DataBlock& data_block() const noexcept override;

private:
    DataBlock data_block_;
    AuthBlock auth_block_;
    v01xx::BIT_Process bitable_{};
};


}    // namespace v0102
}    // namespace bin
}    // namespace pkg
}    // namespace app
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif // UCM_AAP_LIBRARY__UCM_APP_PKG_BIN_V0102__SWP_PROCESS_H_
