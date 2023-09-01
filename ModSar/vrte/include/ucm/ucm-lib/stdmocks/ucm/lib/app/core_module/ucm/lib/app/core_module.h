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

#include <memory>

#include "ucm/mock/sequence.h"

#include "ucm/lib/app/module.h"
#include "ucm/lib/app/core_context.h"
#include "ucm/lib/upd/transactions_manager.h"

namespace bosch {
namespace vrte {
namespace ucm {
namespace lib {
namespace app {

class CoreModule final
    : public Module
    , virtual protected ucm::mock::Sequence
{
public:
    explicit CoreModule(int argc, char** argv)
        : Module("", "", "", "")
        , context_(CoreContext::create(argc, argv))
    {}

    CoreModule(CoreModule&&) noexcept = delete;
    CoreModule& operator=(CoreModule&&) = delete;

    CoreModule(const CoreModule&) = delete;
    CoreModule& operator=(const CoreModule&) = delete;

    virtual ~CoreModule() = default;

    // *************************************************************************
    // Accessors Can be called in any phase
    // *************************************************************************

    upd::TransactionsManager& transactions_manager() noexcept;

    void parser_set(std::unique_ptr<cfg::Parser>&&) {}

    // *************************************************************************
    // Methods called by main() after startoff and before shutdown sequences
    // *************************************************************************
    bool exm_notify_running() noexcept { return pop<bool>(); }
    bool exm_notify_shutdown() noexcept { return pop<bool>(); }

    CoreContext& context() noexcept;

protected:
    virtual bool setup_config_derived()    noexcept override {return true; }
    virtual bool setup_module_derived()    noexcept override {return true; }
    virtual bool startoff_module_derived() noexcept override {return true; }
    virtual bool shutdown_module_derived() noexcept override {return true; }

private:
    // The instances below are available always
    CoreContext& context_;
};

inline CoreContext& CoreModule::context() noexcept
{
    return context_;
}

inline upd::TransactionsManager& CoreModule::transactions_manager() noexcept
{
    return pop<upd::TransactionsManager&>();
}

}    // namespace app
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY_LIB_APP_CORE_MODULE_H_
