//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2022 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         tests/VRTE_UT/stdmocks/ucm/app/pkg/bin/v01xx/swp_process/ucm/app/pkg/bin/v01xx/swp_process.h
/// @brief
/// @copyright    Robert Bosch GmbH 2022
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

#include "ucm/lib/pkg/bin/error.h"
#include "ucm/lib/pkg/bin/swp_process.h"

#include "ucm/app/pkg/bin/context.h"
#include "ucm/app/pkg/bin/v01xx/data_block.h"
#include "ucm/app/pkg/bin/v01xx/auth_block.h"
#include "ucm/app/pkg/bin/v01xx/bit_process.h"

#include "ucm/mock/sequence.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace app   {
namespace pkg   {
namespace bin   {
namespace v01xx {

class SWP_Process
        : public lib::pkg::bin::SWP_Process
        , virtual protected ucm::mock::Sequence
{
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

public:
    using Record = BITable::Fields;
    using Buffer = lib::buf::Model;
    using ErrorValue = lib::pkg::bin::ErrorValue;
    using Context_Ptr = std::shared_ptr<Context>;

    explicit SWP_Process(Context_Ptr,
                         const std::string& outdir,
                         const std::string& swpfile)
        : lib::pkg::bin::SWP_Process(outdir, swpfile)
    {}

    SWP_Process(SWP_Process     &&) = default;
    SWP_Process(SWP_Process const&) = delete;

    SWP_Process& operator=(SWP_Process     &&) = default;
    SWP_Process& operator=(SWP_Process const&) = delete;

public:
    virtual ~SWP_Process() = default;

protected:
    Buffer& ablock_buffer() noexcept
    { return pop<Buffer&>(); }

    Buffer& dblock_buffer() noexcept
    { return pop<Buffer&>(); }

    Error verify_file() noexcept override
    { return pop<Error>(); }

    Error process_file() noexcept override
    { return pop<Error>(); }

    virtual BIT_Process& bitable() noexcept = 0;

    virtual DataBlock& data_block() noexcept = 0;
    virtual AuthBlock& auth_block() noexcept = 0;

    virtual const AuthBlock& auth_block() const noexcept = 0;
    virtual const DataBlock& data_block() const noexcept = 0;
};

}    // namespace v01xx
}    // namespace bin
}    // namespace pkg
}    // namespace app
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif // UCM_AAP_LIBRARY__UCM_APP_PKG_BIN_V01XX__SWP_PROCESS_H_
