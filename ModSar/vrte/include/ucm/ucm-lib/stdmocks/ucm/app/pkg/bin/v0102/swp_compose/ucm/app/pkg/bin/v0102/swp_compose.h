//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/app/pkg/bin/v0102/swp_compose.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks
/// @ingroup bosch_vrte_ucm_app_pkg_bin_v0102


#ifndef UCM_AAP_LIBRARY__UCM_APP_PKG_BIN_V0102__SWP_COMPOSE_H_
#define UCM_AAP_LIBRARY__UCM_APP_PKG_BIN_V0102__SWP_COMPOSE_H_

#include <array>
#include <vector>
#include <memory>
#include <utility>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/app/pkg/bin/v0102/data_block.h"
#include "ucm/app/pkg/bin/v0102/auth_block.h"
#include "ucm/app/pkg/bin/v01xx/swp_compose.h"

#include "ucm/mock/sequence.h"

/// @addtogroup bosch_vrte_ucm_app_pkg_bin_v0102
/// @{


namespace bosch {
namespace vrte  {
namespace ucm   {
namespace app   {
namespace pkg   {
namespace bin   {
namespace v0102 {

class SWP_Compose final : public v01xx::SWP_Compose
                        , virtual protected ucm::mock::Sequence
{
    using Base = v01xx::SWP_Compose;

public:
    explicit SWP_Compose(Context_Ptr ctx, const std::string& file)
                        : v01xx::SWP_Compose(ctx, file)
    , data_block_{DataBlock::create(ctx, ctx->data_buffer())}
    , auth_block_{AuthBlock::create(ctx, ctx->auth_buffer())}
    , bitable_{bit_create()}
    {}

    SWP_Compose(SWP_Compose     &&) = default;
    SWP_Compose(SWP_Compose const&) = delete;

    SWP_Compose& operator=(SWP_Compose     &&) = default;
    SWP_Compose& operator=(SWP_Compose const&) = delete;

    ~SWP_Compose() = default;

    virtual void log_info() const noexcept override {}

protected:

    v01xx::BIT_Compose& bitable() noexcept override
    { return pop<v01xx::BIT_Compose&>(); }

    v01xx::DataBlock& data_block() noexcept override
    { return pop<v01xx::DataBlock&>(); }
    v01xx::AuthBlock& auth_block() noexcept override
    { return pop<v01xx::AuthBlock&>(); }

    const v01xx::AuthBlock& auth_block() const noexcept override
    { return pop<v01xx::AuthBlock&>(); }
    const v01xx::DataBlock& data_block() const noexcept override
    { return pop<v01xx::DataBlock&>(); }

private:
    DataBlock data_block_;
    AuthBlock auth_block_;
    v01xx::BIT_Compose bitable_;

    static v01xx::BIT_Compose bit_create()
    { return pop<v01xx::BIT_Compose>(); }
};


}    // namespace v0102
}    // namespace bin
}    // namespace pkg
}    // namespace app
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif // UCM_AAP_LIBRARY__UCM_APP_PKG_BIN_V0102__SWP_COMPOSE_H_
