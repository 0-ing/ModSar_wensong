//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/app/pkg/bin/v01xx/swp_compose.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks
/// @ingroup      bosch_vrte_ucm_app_pkg_bin_v01xx


#ifndef UCM_AAP_LIBRARY__UCM_APP_PKG_BIN_V01XX__SWP_COMPOSE_H_
#define UCM_AAP_LIBRARY__UCM_APP_PKG_BIN_V01XX__SWP_COMPOSE_H_

#include <array>
#include <vector>
#include <memory>
#include <utility>

#include "ucm/lib/sec/provider.h"
#include "ucm/app/pkg/bin/context.h"
#include "ucm/lib/pkg/bin/swp_compose.h"
#include "ucm/app/pkg/bin/v01xx/data_block.h"
#include "ucm/app/pkg/bin/v01xx/auth_block.h"
#include "ucm/app/pkg/bin/v01xx/bit_compose.h"

#include "ucm/mock/sequence.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace app   {
namespace pkg   {
namespace bin   {
namespace v01xx {

class SWP_Compose
        : public lib::pkg::bin::SWP_Compose
        , virtual protected ucm::mock::Sequence
{
    using Base = lib::pkg::bin::SWP_Compose;

protected:
    using Buffer = lib::buf::Model;
    using Context_Ptr = std::shared_ptr<Context>;

    explicit SWP_Compose(Context_Ptr ctx, const std::string& file)
        : Base{ctx->sec_provider(), file}
    {}

    SWP_Compose(SWP_Compose     &&) = default;
    SWP_Compose(SWP_Compose const&) = delete;

    SWP_Compose& operator=(SWP_Compose     &&) = default;
    SWP_Compose& operator=(SWP_Compose const&) = delete;

public:
    virtual ~SWP_Compose() = default;

    virtual Error generate() noexcept override { return pop<Error>(); }

    virtual void log_info() const noexcept override {}

protected:
    Buffer& ablock_buffer() noexcept { return pop<Buffer&>(); }
    Buffer& dblock_buffer() noexcept { return pop<Buffer&>(); }

    virtual BIT_Compose& bitable() noexcept = 0;

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

#endif // UCM_AAP_LIBRARY__UCM_APP_PKG_BIN_V01XX__SWP_COMPOSE_H_
