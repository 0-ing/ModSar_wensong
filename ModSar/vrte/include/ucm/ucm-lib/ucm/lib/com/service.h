//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/com/service.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY__UCM_LIB_COM__SERVICE__H_
#define UCM_AAP_LIBRARY__UCM_LIB_COM__SERVICE__H_

#include <mutex>
#include <memory>


#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/types.h"
#include "ucm/error.h"
#include "ucm/lib/types.h"
#include "ucm/lib/com/proxy.h"
#include "ucm/lib/app/service.h"

/// @defgroup bosch_vrte_ucm_lib_com__Service__ut COM Service class
/// @ingroup bosch_vrte_ucm_lib_com__ut
/// @{

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace com   {

/// @brief Declaration for UCM wide COM service.
class Service final : public app::Service
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test__ucm_lib_com__Service, CTor);
    FRIEND_TEST(Test__ucm_lib_com__Service, ProxySet);
    FRIEND_TEST(Test__ucm_lib_com__Service, SetupNolock);
    FRIEND_TEST(Test__ucm_lib_com__Service, StartoffNolock);
    FRIEND_TEST(Test__ucm_lib_com__Service, ShutdownNolock);
#endif

    using Base = app::Service;

public:
    explicit Service();

    Service(      Service&&) = delete;
    Service(const Service &) = delete;

    Service& operator=(      Service&&) = delete;
    Service& operator=(const Service &) = delete;

    ~Service() = default;

    /// @brief Install a service object that executes the platform requests.
    Error proxy_set(std::unique_ptr<Proxy>&&) noexcept;

protected:
    bool setup_nolock()    noexcept override;
    bool startoff_nolock() noexcept override;
    bool shutdown_nolock() noexcept override;

private:
    std::unique_ptr<Proxy> proxy_{};
};

}    // namespace com
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif    // UCM_AAP_LIBRARY__UCM_LIB_COM__SERVICE__H_
