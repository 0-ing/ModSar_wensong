//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2022 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/sys/service.h
/// @brief
/// @copyright    Robert Bosch GmbH 2022
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY__UCM_LIB_SYS__SERVICE_H_
#define UCM_AAP_LIBRARY__UCM_LIB_SYS__SERVICE_H_

#include <string>
#include <memory>
#include <cstdint>


#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/error.h"
#include "ucm/lib/app/service.h"
#include "ucm/lib/utl/thread_factory.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace sys   {

class Service final : public app::Service
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test__ucm_lib_sys__Service, CTor);
    FRIEND_TEST(Test__ucm_lib_sys__Service, FactorySet);
    FRIEND_TEST(Test__ucm_lib_sys__Service, SetupNolock);
    FRIEND_TEST(Test__ucm_lib_sys__Service, StartoffNolock);
    FRIEND_TEST(Test__ucm_lib_sys__Service, ShutdownNolock);
#endif

    using Base = app::Service;

public:
    explicit Service();

    Service(      Service&&) = delete;
    Service(const Service &) = delete;

    Service& operator=(Service      &&) = delete;
    Service& operator=(Service const &) = delete;

    ~Service() = default;

    utl::ThreadFactory& thread_factory_get();

    Error factory_set(std::unique_ptr<utl::ThreadFactory>&&) noexcept;

protected:
    bool setup_nolock()    noexcept override;
    bool startoff_nolock() noexcept override;
    bool shutdown_nolock() noexcept override;

private:
    std::unique_ptr<utl::ThreadFactory> factory_{};
};

}    // namespace sys
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif    // UCM_AAP_LIBRARY__UCM_LIB_SYS__SERVICE_H_
