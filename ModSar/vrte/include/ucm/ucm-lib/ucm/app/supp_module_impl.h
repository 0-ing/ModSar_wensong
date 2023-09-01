//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2020 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/app/supp_module_impl.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY_APP_SUPP_MODULE_H_
#define UCM_AAP_LIBRARY_APP_SUPP_MODULE_H_

#include <memory>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/cfg/table.h"
#include "ucm/lib/cfg/parser.h"
#include "ucm/lib/app/supp_module.h"
#include "ucm/lib/app/module_task.h"
#include "ucm/lib/dev/memory_layout.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace app   {

class SuppModuleImpl : public lib::app::SuppModule
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test__ucm__SuppModuleImpl, CTor);
    FRIEND_TEST(Test__ucm__SuppModuleImpl, setup_sys_service_ok);
    FRIEND_TEST(Test__ucm__SuppModuleImpl, setup_sys_service_ko);
    FRIEND_TEST(Test__ucm__SuppModuleImpl, setup_com_service_ok);
    FRIEND_TEST(Test__ucm__SuppModuleImpl, setup_com_service_ko);
    FRIEND_TEST(Test__ucm__SuppModuleImpl, setup_stm_service_ok);
    FRIEND_TEST(Test__ucm__SuppModuleImpl, setup_stm_service_ko);
    FRIEND_TEST(Test__ucm__SuppModuleImpl, setup_exm_service_ok);
    FRIEND_TEST(Test__ucm__SuppModuleImpl, setup_exm_service_ko);
    FRIEND_TEST(Test__ucm__SuppModuleImpl, setup_sec_service_ok);
    FRIEND_TEST(Test__ucm__SuppModuleImpl, setup_sec_service_ko);
    FRIEND_TEST(Test__ucm__SuppModuleImpl, setup_mnf_service_ok);
    FRIEND_TEST(Test__ucm__SuppModuleImpl, setup_mnf_service_ko);
    FRIEND_TEST(Test__ucm__SuppModuleImpl, setup_swp_service_ok);
    FRIEND_TEST(Test__ucm__SuppModuleImpl, setup_swp_service_ko);
    FRIEND_TEST(Test__ucm__SuppModuleImpl, setup_upd_service_ok);
    FRIEND_TEST(Test__ucm__SuppModuleImpl, setup_upd_service_ko);
    FRIEND_TEST(Test__ucm__SuppModuleImpl, setup_config_derived_ok);
    FRIEND_TEST(Test__ucm__SuppModuleImpl, setup_module_derived_ok);
    FRIEND_TEST(Test__ucm__SuppModuleImpl, startoff_module_derived);
    FRIEND_TEST(Test__ucm__SuppModuleImpl, shutdown_module_derived);
#endif
public:
    explicit SuppModuleImpl(lib::app::CoreContext& ctx,
                            lib::upd::TransactionsManager& tmanager);

    SuppModuleImpl(SuppModuleImpl&&) noexcept = delete;
    SuppModuleImpl& operator=(SuppModuleImpl&&) = delete;

    SuppModuleImpl(const SuppModuleImpl&) = delete;
    SuppModuleImpl& operator=(const SuppModuleImpl&) = delete;

    virtual ~SuppModuleImpl() = default;

protected:
    virtual bool setup_config_derived() noexcept override;
    virtual bool setup_module_derived() noexcept override;
    virtual bool startoff_module_derived() noexcept override;
    virtual bool shutdown_module_derived() noexcept override;

private:
    bool setup_sys_service() noexcept;
    bool setup_com_service() noexcept;
    bool setup_stm_service() noexcept;
    bool setup_exm_service() noexcept;
    bool setup_sec_service() noexcept;
    bool setup_mnf_service() noexcept;
    bool setup_swp_service() noexcept;
    bool setup_upd_service() noexcept;
};

}    // namespace app
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY_APP_SUPP_MODULE_H_
