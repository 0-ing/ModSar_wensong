//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/app/pkg/bin/v01xx/swp_process.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks
/// @ingroup      bosch_vrte_ucm_app_pkg_bin_v01xx


#ifndef UCM_AAP_LIBRARY__UCM_APP_PKG_BIN_V01XX__SWP_PROCESS_H_
#define UCM_AAP_LIBRARY__UCM_APP_PKG_BIN_V01XX__SWP_PROCESS_H_

#include <array>
#include <vector>
#include <memory>
#include <utility>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/pkg/bin/error.h"
#include "ucm/lib/pkg/bin/swp_process.h"

#include "ucm/app/pkg/bin/context.h"
#include "ucm/app/pkg/bin/v01xx/data_block.h"
#include "ucm/app/pkg/bin/v01xx/auth_block.h"
#include "ucm/app/pkg/bin/v01xx/bit_process.h"

/// @addtogroup bosch_vrte_ucm_app_pkg_bin_v01xx
/// @{


namespace bosch {
namespace vrte  {
namespace ucm   {
namespace app   {
namespace pkg   {
namespace bin   {
namespace v01xx {

/// @class SWP_Process
/// @ingroup bosch_vrte_ucm_app_pkg_bin_v01xx
/// @brief SWP_Process implementation.

class SWP_Process : public lib::pkg::bin::SWP_Process
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test__ucm_app_pkg_bin_v01xx__SWP_Process, CTor);
    FRIEND_TEST(Test__ucm_app_pkg_bin_v01xx__SWP_Process, verify_file);
    FRIEND_TEST(Test__ucm_app_pkg_bin_v01xx__SWP_Process, verify_file_2);
    FRIEND_TEST(Test__ucm_app_pkg_bin_v01xx__SWP_Process, process_file);
    FRIEND_TEST(Test__ucm_app_pkg_bin_v01xx__SWP_Process, process_file_2);
    FRIEND_TEST(Test__ucm_app_pkg_bin_v01xx__SWP_Process, rec_verify);
    FRIEND_TEST(Test__ucm_app_pkg_bin_v01xx__SWP_Process, mnf_swpload);
#endif

    using Base = lib::pkg::bin::SWP_Process;

    // Block processing states
    enum class BState : unsigned
    {
        kHInit_,
        kDInit_,
        kHConv_,
        kReady_,
        kError_,
    };

protected:
    using Record = BITable::Fields;
    using Buffer = lib::buf::Model;
    using ErrorValue = lib::pkg::bin::ErrorValue;
    using Context_Ptr = std::shared_ptr<Context>;

    explicit SWP_Process(Context_Ptr context,
                         const std::string& outdir,
                         const std::string& swpfile);

    SWP_Process(SWP_Process     &&) = default;
    SWP_Process(SWP_Process const&) = delete;

    SWP_Process& operator=(SWP_Process     &&) = default;
    SWP_Process& operator=(SWP_Process const&) = delete;

public:
    virtual ~SWP_Process() = default;

protected:
    Context_Ptr context_;

    Buffer& ablock_buffer() noexcept;
    Buffer& dblock_buffer() noexcept;

    Error verify_file() noexcept override;

    Error process_file() noexcept override;

    virtual BIT_Process& bitable() noexcept = 0;

    virtual DataBlock& data_block() noexcept = 0;
    virtual AuthBlock& auth_block() noexcept = 0;

    virtual const AuthBlock& auth_block() const noexcept = 0;
    virtual const DataBlock& data_block() const noexcept = 0;

private:
    BState tag_state_{BState::kHInit_};

    void blk_reset() noexcept;

    Error tag_swpload() noexcept;
    Error tag_process() noexcept;
    Error blk_swpload() noexcept;
    Error blk_process() noexcept;
    Error bit_process() noexcept;
    Error mnf_swpload() noexcept;
    Error mnf_swpsave() noexcept;
    Error rec_swpsave() noexcept;
    Error bit_entries_verify() noexcept;

    Error rec_verify(const Record&) noexcept;
    Error rec_extract(const Record&, lib::utl::FileIO&) noexcept;
    Error rec_extract(const Record&, std::vector<uint8_t>&) noexcept;
};

inline lib::buf::Model& SWP_Process::ablock_buffer() noexcept
{
    return context_->auth_buffer();
}

inline lib::buf::Model& SWP_Process::dblock_buffer() noexcept
{
    return context_->data_buffer();
}


}    // namespace v01xx
}    // namespace bin
}    // namespace pkg
}    // namespace app
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif // UCM_AAP_LIBRARY__UCM_APP_PKG_BIN_V01XX__SWP_PROCESS_H_
