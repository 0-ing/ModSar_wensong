//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2020 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/app/module.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY__UCM_LIB_APP__MODULE_H_
#define UCM_AAP_LIBRARY__UCM_LIB_APP__MODULE_H_

#include <vector>
#include <memory>
#include <string>

#include "ucm/mock/sequence.h"
#include "ucm/lib/app/module_task.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace app   {

class Module : virtual protected ucm::mock::Sequence
{
protected:

    explicit Module(const std::string&,
                    const std::string&,
                    const std::string&,
                    const std::string&) {}

public:
    Module(Module     &&) = delete;
    Module(Module const&) = delete;

    Module& operator=(Module     &&) = delete;
    Module& operator=(Module const&) = delete;

    virtual ~Module() = default;

    const std::string&  name() const noexcept { return pop<std::string const&>(); }
    const std::string&  version() const noexcept { return pop<std::string const&>(); }
    const std::string&  buildid() const noexcept { return pop<std::string const&>(); }
    const std::string&  logname() const noexcept { return pop<std::string const&>(); }

    bool setup_config() noexcept { return pop<bool>(); }
    bool setup_module() noexcept { return pop<bool>(); }
    bool startoff_module() noexcept { return pop<bool>(); }
    bool shutdown_module() noexcept { return pop<bool>(); }

protected:
    auto bconfig_flag() const noexcept { return pop<bool>(); }
    auto aconfig_flag() const noexcept { return pop<bool>(); }
    auto bmodule_flag() const noexcept { return pop<bool>(); }
    auto emodule_flag() const noexcept { return pop<bool>(); }

    std::vector<std::unique_ptr<ModuleTask>> startoff_module_tasks_{};
    std::vector<std::unique_ptr<ModuleTask>> shutdown_module_tasks_{};

    virtual bool setup_config_derived() noexcept = 0;
    virtual bool setup_module_derived() noexcept = 0;
    virtual bool startoff_module_derived() noexcept = 0;
    virtual bool shutdown_module_derived() noexcept = 0;
};

}    // namespace app
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY__UCM_LIB_APP__MODULE_H_
