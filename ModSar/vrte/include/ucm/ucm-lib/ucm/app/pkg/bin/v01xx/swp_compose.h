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

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/sec/provider.h"
#include "ucm/app/pkg/bin/context.h"
#include "ucm/lib/pkg/bin/swp_compose.h"
#include "ucm/app/pkg/bin/v01xx/data_block.h"
#include "ucm/app/pkg/bin/v01xx/auth_block.h"
#include "ucm/app/pkg/bin/v01xx/bit_compose.h"


/// @addtogroup bosch_vrte_ucm_app_pkg_bin_v01xx
/// @{



namespace bosch {
namespace vrte  {
namespace ucm   {
namespace app   {
namespace pkg   {
namespace bin   {
namespace v01xx {

/// @class SWP_Compose
/// @ingroup bosch_vrte_ucm_app_pkg_bin_v01xx
/// @brief SWP_Compose implementation.

class SWP_Compose : public lib::pkg::bin::SWP_Compose
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test__ucm_app_pkg_bin_v01xx__SWP_Compose, CTor);
    FRIEND_TEST(Test__ucm_app_pkg_bin_v01xx__SWP_Compose, generate);
    FRIEND_TEST(Test__ucm_app_pkg_bin_v01xx__SWP_Compose, generate2);
    FRIEND_TEST(Test__ucm_app_pkg_bin_v01xx__SWP_Compose, log_info);
#endif

    using Base = lib::pkg::bin::SWP_Compose;

protected:
    using Buffer = lib::buf::Model;
    using Context_Ptr = std::shared_ptr<Context>;

    /// @brief Construct a generic SWP compositor for SWP format v01xx
    ///
    /// @param context A shared pointer to the context.
    /// @param swp_file The name of the output SWP file.
    explicit SWP_Compose(Context_Ptr context, const std::string& file);

    SWP_Compose(SWP_Compose     &&) = default;
    SWP_Compose(SWP_Compose const&) = delete;

    SWP_Compose& operator=(SWP_Compose     &&) = delete;
    SWP_Compose& operator=(SWP_Compose const&) = delete;

public:
    virtual ~SWP_Compose() = default;

    virtual Error generate() noexcept override;

    virtual void log_info() const noexcept override;

protected:
    Context_Ptr context_;

    Buffer& ablock_buffer() noexcept;
    Buffer& dblock_buffer() noexcept;

    virtual BIT_Compose& bitable() noexcept = 0;

    virtual DataBlock& data_block() noexcept = 0;
    virtual AuthBlock& auth_block() noexcept = 0;

    virtual const AuthBlock& auth_block() const noexcept = 0;
    virtual const DataBlock& data_block() const noexcept = 0;
};

inline lib::buf::Model& SWP_Compose::ablock_buffer() noexcept
{
    return context_->auth_buffer();
}

inline lib::buf::Model& SWP_Compose::dblock_buffer() noexcept
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

#endif // UCM_AAP_LIBRARY__UCM_APP_PKG_BIN_V01XX__SWP_COMPOSE_H_
