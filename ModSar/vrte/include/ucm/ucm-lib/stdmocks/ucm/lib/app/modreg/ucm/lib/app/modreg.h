//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2020 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/app/modreg.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY_LIB_APP_MODREG_H_
#define UCM_AAP_LIBRARY_LIB_APP_MODREG_H_

#include <array>
#include <memory>

#include "ucm/mock/sequence.h"
#include "ucm/lib/app/core_module.h"
#include "ucm/lib/app/module_factory.h"

extern "C" {

#define UCM_MODULE_DEFAULT_IMPL             0
#define UCM_MODULE_PROCESSING_SW            1
#define UCM_MODULE_PROCESSING_HW            2
#define UCM_MODULE_PKGMANAGER_API           3
#define UCM_MODULE_COMMUNICATION_UDS        4
#define UCM_MODULE_COMMUNICATION_WEB        5
#define UCM_MODULE_VARIATION_ADDON          6

#define CONSTRUCTOR_PRIORITY_0 4201
#define CONSTRUCTOR_PRIORITY_1 4202
#define CONSTRUCTOR_PRIORITY_2 4203
#define CONSTRUCTOR_PRIORITY_3 4204
#define CONSTRUCTOR_PRIORITY_4 4205
#define CONSTRUCTOR_PRIORITY_5 4206
#define CONSTRUCTOR_PRIORITY_6 4207
#define CONSTRUCTOR_PRIORITY_7 4208

extern void modreg_0(void);
extern void modreg_1(void);
extern void modreg_2(void);
extern void modreg_3(void);
extern void modreg_4(void);
extern void modreg_5(void);
extern void modreg_6(void);
extern void modreg_7(void);

} // extern "C"

namespace bosch {
namespace vrte {
namespace ucm {
namespace lib {
namespace app {

class Modreg final
    : virtual protected ucm::mock::Sequence
{

public:
    constexpr static std::size_t maxmods = 8;

    Modreg() = default;

    Modreg(Modreg&&) = delete;
    Modreg& operator=(Modreg&&) = delete;

    Modreg(const Modreg&) = delete;
    Modreg& operator=(const Modreg&) = delete;

    ~Modreg() = default;

    static bool setup_config() noexcept { return pop<bool>(); }
    static bool setup_module() noexcept { return pop<bool>(); }
    static bool startoff_module() { return pop<bool>(); }
    static bool startoff_notify() { return pop<bool>(); }
    static void shutdown_notify() { return pop<void>(); }
    static void shutdown_module() { return pop<void>(); }

    static void modules_dtor() { return pop<void>(); }
    static void modules_ctor(CoreContext&, upd::TransactionsManager&)
    {
        return pop<void>();
    }

    static Module* module(std::size_t) { return pop<Module*>(); }

    static void factory_register(std::size_t, ModuleFactory*) {}
};

}    // namespace app
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY_LIB_APP_MODREG_H_
