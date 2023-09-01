//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/exm/service.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY__UCM_LIB_EXM__SERVICE_H_
#define UCM_AAP_LIBRARY__UCM_LIB_EXM__SERVICE_H_

#include <string>
#include <memory>
#include <cstdint>


#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/error.h"
#include "ucm/lib/app/service.h"

#include "ucm/lib/exm/types.h"
#include "ucm/lib/exm/proxy.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace exm   {

class Service final : public app::Service
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test__ucm_lib_exm__Service, CTor);
    FRIEND_TEST(Test__ucm_lib_exm__Service, ProxySet);
    FRIEND_TEST(Test__ucm_lib_exm__Service, AppAction);
    FRIEND_TEST(Test__ucm_lib_exm__Service, SetupNolock);
    FRIEND_TEST(Test__ucm_lib_exm__Service, StartoffNolock);
    FRIEND_TEST(Test__ucm_lib_exm__Service, ShutdownNolock);
#endif

    using Base = app::Service;

public:
    explicit Service();

    Service(      Service&&) = delete;
    Service(const Service &) = delete;

    Service& operator=(Service      &&) = delete;
    Service& operator=(Service const &) = delete;

    ~Service() = default;

    Error proxy_set(std::unique_ptr<Proxy>&&) noexcept;

    bool app_action(const AppAction&, const std::string&) noexcept;

protected:
    bool setup_nolock()    noexcept override;
    bool startoff_nolock() noexcept override;
    bool shutdown_nolock() noexcept override;

private:
    std::unique_ptr<Proxy> proxy_{};
};

}    // namespace exm
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif    // UCM_AAP_LIBRARY__UCM_LIB_EXM__SERVICE_H_
