//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2020 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/processing_vrte.h
/// @brief
/// @copyright    Robert Bosch GmbH 2018
/// @author       Vesselin Mladenov
/// @version
/// @remarks
/// @ingroup      bosch_vrte_ucm_vrte

#ifndef UCM_AAP_PROCESSING_VRTE_H_
#define UCM_AAP_PROCESSING_VRTE_H_

#include <memory>

#if defined(GOOGLE_TEST)
#include <gtest/gtest_prod.h>
#endif

#include "ucm/error.h"
#include "ucm/vrte/cfg/table.h"
#include "ucm/lib/app/module.h"
#include "ucm/lib/app/supp_module.h"
#include "ucm/lib/app/module_task.h"
#include "ucm/lib/app/core_context.h"
#include "ucm/lib/upd/transactions_manager.h"
#include "ucm/vrte/sec/ara_crypto_includes.h"

/// @addtogroup bosch_vrte_ucm_vrte
/// @{

namespace bosch {
namespace vrte {
namespace ucm {
namespace vrte {

/// @brief Provision of runtime services for VRTE platform.
///

class ProcessingVRTE : public lib::app::SuppModule
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_ucm_processing_vrte, setupConfigDerived_Success);
    FRIEND_TEST(Test_ucm_processing_vrte, setupLogService_Success);
    FRIEND_TEST(Test_ucm_processing_vrte, setupLogService_Failure);
    FRIEND_TEST(Test_ucm_processing_vrte, setupExmService_Success);
    FRIEND_TEST(Test_ucm_processing_vrte, setupExmService_Failure);
    FRIEND_TEST(Test_ucm_processing_vrte, setupStmService_Success);
    FRIEND_TEST(Test_ucm_processing_vrte, setupStmService_Failure);
    FRIEND_TEST(Test_ucm_processing_vrte, setupComService_Success);
    FRIEND_TEST(Test_ucm_processing_vrte, setupComService_Failure);
    FRIEND_TEST(Test_ucm_processing_vrte, setupAppInstaller_Success);
    FRIEND_TEST(Test_ucm_processing_vrte, setupAppInstaller_Failure);
    FRIEND_TEST(Test_ucm_processing_vrte, setupModuleDerived_Success);
    FRIEND_TEST(Test_ucm_processing_vrte, setupModuleDerived_Failure);
    FRIEND_TEST(Test_ucm_processing_vrte, startoffModuleDerived_Success_Failure);
    FRIEND_TEST(Test_ucm_processing_vrte, startoffNotifyDerived_Success);
    FRIEND_TEST(Test_ucm_processing_vrte, shutdownNotifyDerived_Success);
    FRIEND_TEST(Test_ucm_processing_vrte, shutdownModuleDerived_Success_Failure);
    FRIEND_TEST(Test_ucm_processing_vrte, factoryProcessingVRTE_Success);
#endif

public:
    explicit ProcessingVRTE(ucm::lib::app::CoreContext& context,
                            ucm::lib::upd::TransactionsManager& tmanager);

    ProcessingVRTE(ProcessingVRTE&&) noexcept = delete;
    ProcessingVRTE& operator=(ProcessingVRTE&&) = delete;

    ProcessingVRTE(const ProcessingVRTE&) = delete;
    ProcessingVRTE& operator=(const ProcessingVRTE&) = delete;

    virtual ~ProcessingVRTE() = default;

protected:
    virtual bool setup_config_derived() noexcept override;
    virtual bool setup_module_derived() noexcept override;
    virtual bool startoff_module_derived() noexcept override;
    virtual bool shutdown_module_derived() noexcept override;

private:
    cfg::Table                                    module_config_{};
    std::shared_ptr<ara::core::InstanceSpecifier> sec_instance_;
    std::shared_ptr<ara::core::InstanceSpecifier> key_instance_;

    bool setup_sys_service() noexcept;
    bool setup_log_service() noexcept;
    bool setup_com_service() noexcept;
    bool setup_stm_service() noexcept;
    bool setup_exm_service() noexcept;
    bool setup_app_installer() noexcept;
    bool setup_arc_service() noexcept;
};

}    // namespace vrte
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif // UCM_AAP_PROCESSING_VRTE_H_
