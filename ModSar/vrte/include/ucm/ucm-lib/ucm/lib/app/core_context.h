//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2020 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/app/core_context.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY__UCM_LIB_APP__CORE_CONTEXT_H_
#define UCM_AAP_LIBRARY__UCM_LIB_APP__CORE_CONTEXT_H_

#include <memory>
#include <cstddef>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/cfg/table.h"
#include "ucm/lib/com/service.h"
#include "ucm/lib/stm/service.h"
#include "ucm/lib/exm/service.h"
#include "ucm/lib/sec/service.h"
#include "ucm/lib/sys/service.h"
#include "ucm/lib/swc/service.h"
#include "ucm/lib/arc/service.h"
#include "ucm/lib/ppl/service.h"
#include "ucm/lib/upd/service.h"
#include "ucm/lib/stm/ucm_state.h"
#include "ucm/lib/cfg/registry.h"
#include "ucm/lib/pkg/mnf/service.h"
#include "ucm/lib/pkg/bin/service.h"
#include "ucm/lib/dev/memory_layout.h"
#include "ucm/lib/dev/device_factory_registry.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace app   {

class CoreContext final
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test__ucm_lib_app__CoreContext, CTor);
#endif

    static std::unique_ptr<CoreContext> instance_;

    explicit CoreContext(int argc, char** argv) noexcept;

public:

    // Primordial services
    using sysService  = sys::Service;
    using cfgRegistry = cfg::Registry;

    // Foreign services
    using comService = com::Service;
    using stmService = stm::Service;
    using exmService = exm::Service;
    using secService = sec::Service;

    // Internal services
    using pplService = ppl::Service;
    using arcService = arc::Service;
    using swcService = swc::Service;
    using updService = upd::Service;
    using sdbService = swc::db::Service;
    using mnfService = pkg::mnf::Service;
    using swpService = pkg::bin::Service;

    /// @brief Create the CoreContext instance.
    static CoreContext& create(int argc, char** argv) noexcept;

    /// @brief Get the CoreContext instance.
    static CoreContext& get() noexcept;

    CoreContext(CoreContext&&)      = delete;
    CoreContext(CoreContext const&) = delete;

    CoreContext& operator=(CoreContext     &&) = delete;
    CoreContext& operator=(CoreContext const&) = delete;

    ~CoreContext() = default;

    // Primordial services
    cfg::Table&     config() noexcept;
    cfg::Registry&  cfg_registry() noexcept;
    sysService&     sys_service() noexcept;

    // Foreign services
    comService& com_service() noexcept;
    stmService& stm_service() noexcept;
    exmService& exm_service() noexcept;
    secService& sec_service() noexcept;
    auto& sec_provider() noexcept;

    // Internal services
    pplService& ppl_service() noexcept;
    arcService& arc_service() noexcept;
    sdbService& sdb_service() noexcept;
    swcService& swc_service() noexcept;
    mnfService& mnf_service() noexcept;
    swpService& swp_service() noexcept;
    updService& upd_service() noexcept;

    auto& ucm_state() noexcept;

    auto& memory_layout() noexcept;
    auto& mkdev_registry() noexcept;


private:
    // Primordial services
    cfg::Table     config_;
    cfg::Registry  cfg_registry_{};
    sysService     sys_service_;

    // Foreign services
    comService com_service_;
    stmService stm_service_;
    exmService exm_service_;
    secService sec_service_;
    sec::Provider sec_provider_;

    // Internal services
    pplService ppl_service_;
    arcService arc_service_;
    sdbService sdb_service_;
    swcService swc_service_;
    mnfService mnf_service_;
    swpService swp_service_;
    updService upd_service_;

    stm::UCM_State              ucm_state_{};
    dev::MemoryLayout           memory_layout_{};
    dev::DeviceFactoryRegistry  mkdev_registry_{};
};

inline cfg::Table& CoreContext::config() noexcept
{
    return config_;
}

inline cfg::Registry& CoreContext::cfg_registry() noexcept
{
    return cfg_registry_;
}

inline sys::Service& CoreContext::sys_service() noexcept
{
    return sys_service_;
}

inline com::Service& CoreContext::com_service() noexcept
{
    return com_service_;
}

inline stm::Service& CoreContext::stm_service() noexcept
{
    return stm_service_;
}

inline exm::Service& CoreContext::exm_service() noexcept
{
    return exm_service_;
}

inline sec::Service& CoreContext::sec_service() noexcept
{
    return sec_service_;
}

inline auto& CoreContext::sec_provider() noexcept
{
    return sec_provider_;
}

inline ppl::Service& CoreContext::ppl_service() noexcept
{
    return ppl_service_;
}

inline arc::Service& CoreContext::arc_service() noexcept
{
    return arc_service_;
}

inline swc::db::Service& CoreContext::sdb_service() noexcept
{
    return sdb_service_;
}

inline swc::Service& CoreContext::swc_service() noexcept
{
    return swc_service_;
}

inline pkg::mnf::Service& CoreContext::mnf_service() noexcept
{
    return mnf_service_;
}

inline pkg::bin::Service& CoreContext::swp_service() noexcept
{
    return swp_service_;
}

inline upd::Service& CoreContext::upd_service() noexcept
{
    return upd_service_;
}

inline auto& CoreContext::ucm_state() noexcept
{
    return ucm_state_;
}

inline auto& CoreContext::memory_layout() noexcept
{
    return memory_layout_;
}

inline auto& CoreContext::mkdev_registry() noexcept
{
    return mkdev_registry_;
}


}    // namespace app
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY_LIB_UPD_CORE_CONTEXT_H_
