//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2020 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/app/core_module.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY_LIB_APP_CORE_MODULE_H_
#define UCM_AAP_LIBRARY_LIB_APP_CORE_MODULE_H_

#include <array>
#include <memory>

#include "ucm/lib/app/module.h"
#include "ucm/lib/app/core_context.h"
#include "ucm/lib/upd/transactions_manager.h"

namespace bosch {
namespace vrte {
namespace ucm {
namespace lib {
namespace app {

class CoreModule final : public Module
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_ucm_lib_app_core_module, CTor);
    FRIEND_TEST(Test_ucm_lib_app_core_module, startoff_module_derived);
    FRIEND_TEST(Test_ucm_lib_app_core_module, setup_module_derived);
    FRIEND_TEST(Test_ucm_lib_app_core_module, exm_notify_running);
#endif

    constexpr static size_t service_maxnum = 32;

public:
    explicit CoreModule(int argc, char** argv);

    CoreModule(CoreModule&&) noexcept = delete;
    CoreModule& operator=(CoreModule&&) = delete;

    CoreModule(const CoreModule&) = delete;
    CoreModule& operator=(const CoreModule&) = delete;

    ~CoreModule() = default;

    // *************************************************************************
    // Accessors Can be called in any phase
    // *************************************************************************

    CoreContext& context() noexcept;
    upd::TransactionsManager& transactions_manager() noexcept;

    // *************************************************************************
    // Methods to be called during setup_config() phase
    // *************************************************************************

    /// @brief Append a ConfigParser object to the list of configuration parsers
    void parser_set(std::unique_ptr<cfg::Parser>&&);

    std::pair<std::unique_ptr<ModuleTask>, std::unique_ptr<ModuleTask>>
    exm_notify_pair(std::unique_ptr<ModuleTask>&&,
                    std::unique_ptr<ModuleTask>&&) noexcept;

    // *************************************************************************
    // Methods called by main() after startoff and before shutdown sequences
    // *************************************************************************
    bool exm_notify_running() noexcept;
    bool exm_notify_shutdown() noexcept;

protected:
    virtual bool setup_config_derived() noexcept override;
    // Consider before and after methods for setup!
    virtual bool setup_module_derived() noexcept override;
    virtual bool startoff_module_derived() noexcept override;
    virtual bool shutdown_module_derived() noexcept override;

private:
    // The instances below are available always
    CoreContext& context_;
    upd::TransactionsManager tmanager_;
    std::array<Service*, service_maxnum> services_{};

    std::unique_ptr<ModuleTask> exm_notify_running_{};
    std::unique_ptr<ModuleTask> exm_notify_shutdown_{};
};

inline CoreContext& CoreModule::context() noexcept
{
    return context_;
}

inline upd::TransactionsManager& CoreModule::transactions_manager() noexcept
{
    return tmanager_;
}

}    // namespace app
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY_LIB_APP_CORE_MODULE_H_
