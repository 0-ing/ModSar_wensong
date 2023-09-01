//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2022 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/app/pkg/bin/v0102/context.h
/// @brief
/// @copyright    Robert Bosch GmbH 2022
/// @author       Vesselin Mladenov
/// @version
/// @remarks
/// @ingroup bosch_vrte_ucm_app_pkg_bin_v0102


#ifndef UCM_AAP_LIBRARY__UCM_APP_PKG_BIN_V0102__CONTEXT_H_
#define UCM_AAP_LIBRARY__UCM_APP_PKG_BIN_V0102__CONTEXT_H_


#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/buf/array.h"
#include "ucm/app/pkg/bin/context.h"
#include "ucm/app/pkg/bin/v01xx/bitable.h"
#include "ucm/app/pkg/bin/v0102/auth_block.h"
#include "ucm/app/pkg/bin/v0102/data_block.h"

/// @addtogroup bosch_vrte_ucm_app_pkg_bin_v0102
/// @{


namespace bosch {
namespace vrte  {
namespace ucm   {
namespace app   {
namespace pkg   {
namespace bin   {
namespace v0102 {

/// @class Context
/// @ingroup bosch_vrte_ucm_app_pkg_bin_v0102
/// @brief Context implementation.

class Context : public bosch::vrte::ucm::app::pkg::bin::Context
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test__ucm_app_pkg_bin_v0102__Context, CTor);
#endif

    constexpr static size_t data_buff_size = DataBlock::total_size();
    constexpr static size_t auth_buff_size = AuthBlock::total_size();

    using Base     = bosch::vrte::ucm::app::pkg::bin::Context;
    using AuthBuff = bosch::vrte::ucm::lib::buf::Array<auth_buff_size>;
    using DataBuff = bosch::vrte::ucm::lib::buf::Array<data_buff_size>;

public:

    explicit Context(lib::sec::Provider& sec_provider);

    Context(Context     &&) = delete;
    Context(Context const&) = delete;

    Context& operator=(Context     &&) = delete;
    Context& operator=(Context const&) = delete;

    virtual ~Context() = default;

    Buffer& data_buffer() noexcept override;
    Buffer& auth_buffer() noexcept override;

private:
    AuthBuff auth_buffer_{};
    DataBuff data_buffer_{};
};

}    // namespace v0102
}    // namespace bin
}    // namespace pkg
}    // namespace app
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif // UCM_AAP_LIBRARY__UCM_APP_PKG_BIN_V0102__CONTEXT_H_
