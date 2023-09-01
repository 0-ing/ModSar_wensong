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

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/app/module_task.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace app   {

class Module
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_ucm_lib_app_module, shutdown_module);
#endif

protected:
    explicit Module(const std::string& name,
                    const std::string& version,
                    const std::string& buildid,
                    const std::string& githash);

public:
    Module(Module     &&) = delete;
    Module(Module const&) = delete;

    Module& operator=(Module     &&) = delete;
    Module& operator=(Module const&) = delete;

    virtual ~Module() = default;

    const std::string& name()    const noexcept;
    const std::string& version() const noexcept;
    const std::string& buildid() const noexcept;
    const std::string& githash() const noexcept;
    const std::string& logname() const noexcept;

    /// @brief The method is called before the configuration is parsed.
    /// All setup/registration that do not require configuration happens here
    bool setup_config() noexcept;

    /// @brief The method is called after the configuration is created/parsed.
    /// All setup/registrations that depend on the configuration happens here
    bool setup_module() noexcept;

    /// @brief The method is called to "start" the module.
    /// The routines executed/threads started should not depend on modules
    /// that are initialized after the current module.
    bool startoff_module() noexcept;

    /// @brief The method is called to shutdown the module and its threads
    bool shutdown_module() noexcept;

protected:
    auto bconfig_flag() const noexcept;     // associated with setup_config()
    auto aconfig_flag() const noexcept;     // associated with setup_module()
    auto bmodule_flag() const noexcept;     // associated with startoff_module()
    auto emodule_flag() const noexcept;     // associated with shutdown_module()

    std::vector<std::unique_ptr<ModuleTask>> startoff_module_tasks_{};
    std::vector<std::unique_ptr<ModuleTask>> shutdown_module_tasks_{};

    virtual bool setup_config_derived() noexcept = 0;
    virtual bool setup_module_derived() noexcept = 0;
    virtual bool startoff_module_derived() noexcept = 0;
    virtual bool shutdown_module_derived() noexcept = 0;

private:
    std::string  name_;
    std::string  version_;
    std::string  buildid_;
    std::string  githash_;
    std::string  logname_;

    bool bconfig_flag_{false};      // associated with setup_config()
    bool aconfig_flag_{false};      // associated with setup_module()
    bool bmodule_flag_{false};      // associated with startoff_module()
    bool emodule_flag_{false};      // associated with shutdown_module()

    bool startoff_module_exec() noexcept;
    bool shutdown_module_exec() noexcept;
};

inline const std::string&  Module::name() const noexcept
{
    return name_;
}

inline const std::string&  Module::version() const noexcept
{
    return version_;
}

inline const std::string&  Module::buildid() const noexcept
{
    return buildid_;
}

inline const std::string&  Module::githash() const noexcept
{
    return githash_;
}

inline const std::string&  Module::logname() const noexcept
{
    return logname_;
}

inline auto Module::bconfig_flag() const noexcept
{
    return bconfig_flag_;
}

inline auto Module::aconfig_flag() const noexcept
{
    return aconfig_flag_;
}

inline auto Module::bmodule_flag() const noexcept
{
    return bmodule_flag_;
}

inline auto Module::emodule_flag() const noexcept
{
    return emodule_flag_;
}

}    // namespace app
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY__UCM_LIB_APP__MODULE_H_
