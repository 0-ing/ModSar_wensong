//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/stm/proxy.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY__UCM_LIB_STM__PROXY_H_
#define UCM_AAP_LIBRARY__UCM_LIB_STM__PROXY_H_

#include <string>
#include <vector>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/stm/error.h"
#include "ucm/lib/stm/fg_ident.h"
#include "ucm/lib/stm/fg_state.h"

/// @defgroup bosch_vrte_ucm_lib_stm__Proxy__ut STM proxy API
/// @ingroup bosch_vrte_ucm_lib_stm__ut
/// @{

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace stm   {

/// @brief Provide an API for interaction with STM instance.
class Proxy
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test__ucm_lib_stm__Proxy, CTor);
#endif
public:
    virtual ~Proxy() = default;

    /// @brief Start the service.
    virtual bool startoff() noexcept = 0;

    /// @brief Stop the service.
    virtual bool shutdown() noexcept = 0;

    /// @brief Instruct STM to reset the machine.
    virtual Error reset_machine() noexcept = 0;

    /// @brief Instruct STM to enter update state.
    virtual Error update_enter() noexcept = 0;

    /// @brief Instruct STM to leave update state.
    virtual Error update_leave() noexcept = 0;

    /// @brief Request STM to put the listed entries in verify state.
    /// @param fg_list List of FGs to be transitioned
    virtual Error
    fg_verify(const std::vector<FG_Ident>& fg_list) noexcept = 0;

    /// @brief Request STM to put the listed entries in activate state.
    /// @param fg_list List of FGs to be transitioned
    virtual Error
    fg_activate(const std::vector<FG_Ident>& fg_list) noexcept = 0;

    /// @brief Request STM to put the listed entries in rollback state.
    /// @param fg_list List of FGs to be transitioned
    virtual Error
    fg_rollback(const std::vector<FG_Ident>& fg_list) noexcept = 0;

protected:
    explicit Proxy() = default;

    Proxy(Proxy     &&) = default;
    Proxy(Proxy const&) = default;

    Proxy& operator=(Proxy     &&) = default;
    Proxy& operator=(Proxy const&) = default;
};


}    // namespace stm
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif    // UCM_AAP_LIBRARY__UCM_LIB_STM__PROXY_H_
