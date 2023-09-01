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

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/app/core_context.h"
#include "ucm/lib/app/module_factory.h"
#include "ucm/lib/upd/transactions_manager.h"

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
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace app   {

class Modreg final
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_Modreg, Simple);
    FRIEND_TEST(Test_ucm_lib_app_modreg, setup_config);
    FRIEND_TEST(Test_ucm_lib_app_modreg, setup_module);
    FRIEND_TEST(Test_ucm_lib_app_modreg, startoff_module);
    FRIEND_TEST(Test_ucm_lib_app_modreg, shutdown_module);
    FRIEND_TEST(Test_ucm_lib_app_modreg, modules_dtor);
    FRIEND_TEST(Test_ucm_lib_app_modreg, Other_methods);
#endif

public:
    constexpr static std::size_t maxmods = 8;

    Modreg() = default;

    Modreg(Modreg&&) = delete;
    Modreg& operator=(Modreg&&) = delete;

    Modreg(const Modreg&) = delete;
    Modreg& operator=(const Modreg&) = delete;

    ~Modreg() = default;

    static bool setup_config()    noexcept;
    static bool setup_module()    noexcept;
    static bool startoff_module() noexcept;
    static bool shutdown_module() noexcept;

    static void modules_dtor();
    static void modules_ctor(CoreContext&, upd::TransactionsManager&);

    static Module* module(std::size_t);

    static void factory_register(std::size_t, ModuleFactory*);

private:
    static std::size_t count_;
    static std::array<Module*, maxmods> modules_;
    static std::array<ModuleFactory*, maxmods> factories_;
};

}    // namespace app
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY_LIB_APP_MODREG_H_
