//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2019 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/stm/service.h
/// @brief
/// @copyright    Robert Bosch GmbH 2019
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY__UCM_LIB_STM__SERVICE__H_
#define UCM_AAP_LIBRARY__UCM_LIB_STM__SERVICE__H_

#include <map>
#include <mutex>
#include <memory>


#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/types.h"
#include "ucm/lib/types.h"
#include "ucm/lib/app/service.h"

#include "ucm/lib/stm/error.h"
#include "ucm/lib/stm/proxy.h"
#include "ucm/lib/stm/fg_cache.h"

/// @defgroup bosch_vrte_ucm_lib_stm__Service__ut STM Service class
/// @ingroup bosch_vrte_ucm_lib_stm__ut
/// @{

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace stm   {

/// @brief Declaration for UCM wide STM service.
class Service final : public app::Service
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test__ucm_lib_stm__Service, CTor);
    FRIEND_TEST(Test__ucm_lib_stm__Service, Setup);
    FRIEND_TEST(Test__ucm_lib_stm__Service, Startoff);
    FRIEND_TEST(Test__ucm_lib_stm__Service, Shutdown);
    FRIEND_TEST(Test__ucm_lib_stm__Service, ResetMachine);
    FRIEND_TEST(Test__ucm_lib_stm__Service, UpdateEnter);
    FRIEND_TEST(Test__ucm_lib_stm__Service, UpdateLeave);
    FRIEND_TEST(Test__ucm_lib_stm__Service, FG_Verify);
    FRIEND_TEST(Test__ucm_lib_stm__Service, FG_Activate);
    FRIEND_TEST(Test__ucm_lib_stm__Service, FG_Rollback);
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

    /// @brief Instruct STM to reset the machine.
    Error reset_machine() noexcept;

    /// @brief Instruct STM to enter update state.
    Error update_enter() noexcept;

    /// @brief Instruct STM to leave update state.
    Error update_leave() noexcept;

    /// @brief Request STM to put the listed entries in verify state.
    /// @param fg_list List of FGs to be transitioned
    Error fg_verify(const std::vector<std::string>& fg_list) noexcept;

    /// @brief Request STM to put the listed entries in activate state.
    /// @param fg_list List of FGs to be transitioned
    Error fg_activate(const std::vector<std::string>& fg_list) noexcept;

    /// @brief Request STM to put the listed entries in rollback state.
    /// @param fg_list List of FGs to be transitioned
    Error fg_rollback(const std::vector<std::string>& fg_list) noexcept;

protected:
    bool setup_nolock()    noexcept override;
    bool startoff_nolock() noexcept override;
    bool shutdown_nolock() noexcept override;

private:
    FG_Cache fg_cache_{};
    std::unique_ptr<Proxy> proxy_{};
};

}    // namespace stm
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif    // UCM_AAP_LIBRARY__UCM_LIB_STM__SERVICE__H_
