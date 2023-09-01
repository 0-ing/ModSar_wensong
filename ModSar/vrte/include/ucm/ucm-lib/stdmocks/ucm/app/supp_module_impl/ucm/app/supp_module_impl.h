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

#include "ucm/lib/cfg/table.h"
#include "ucm/lib/cfg/parser.h"
#include "ucm/lib/app/module.h"
#include "ucm/lib/app/core_module.h"
#include "ucm/lib/app/supp_module.h"
#include "ucm/lib/app/module_task.h"
#include "ucm/lib/dev/memory_layout.h"

#include "ucm/mock/sequence.h"


namespace bosch {
namespace vrte {
namespace ucm {

class SuppModuleImpl
        : public lib::app::SuppModule
        , virtual protected ucm::mock::Sequence
{
public:
    explicit SuppModuleImpl(std::shared_ptr<lib::app::CoreModule>& arg)
        : lib::app::SuppModule(arg)
    {
        pop<void>();
    }

    SuppModuleImpl(SuppModuleImpl&&) noexcept = default;
    SuppModuleImpl& operator=(SuppModuleImpl&&) = default;

    SuppModuleImpl(const SuppModuleImpl&) = delete;
    SuppModuleImpl& operator=(const SuppModuleImpl&) = delete;

    virtual ~SuppModuleImpl() = default;

protected:
    virtual bool setup_config_derived() noexcept override { return pop<bool>(); }
    virtual bool setup_module_derived() noexcept override { return pop<bool>(); }
    virtual bool startoff_module_derived() noexcept override { return pop<bool>(); }
    virtual bool startoff_notify_derived() noexcept override { return pop<bool>(); }
    virtual bool shutdown_notify_derived() noexcept override { return pop<bool>(); }
    virtual bool shutdown_module_derived() noexcept override { return pop<bool>(); }
};

}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY_APP_SUPP_MODULE_H_
