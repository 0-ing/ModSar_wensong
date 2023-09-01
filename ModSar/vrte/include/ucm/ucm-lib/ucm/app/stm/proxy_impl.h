//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/app/stm/proxy_impl.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks
/// @ingroup      bosch_vrte_ucm_app_stm

#ifndef UCM_AAP_LIBRARY__UCM_APP_STM__PROXY_IMPL_H_
#define UCM_AAP_LIBRARY__UCM_APP_STM__PROXY_IMPL_H_

#include <string>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/stm/proxy.h"

/// @addtogroup bosch_vrte_ucm_app_stm
/// @{

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace app   {
namespace stm   {

/// @class ProxyImpl
/// @ingroup bosch_vrte_ucm_app_stm
/// @brief Provide a dummy implementation of the base class.
/// All methods return success (i.e. either true or no error)
class ProxyImpl : public lib::stm::Proxy
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test__ucm_app_stm__ProxyImpl, CTor);
#endif
public:
    explicit ProxyImpl() = default;

    ProxyImpl(ProxyImpl     &&) = default;
    ProxyImpl(ProxyImpl const&) = default;

    ProxyImpl& operator=(ProxyImpl     &&) = default;
    ProxyImpl& operator=(ProxyImpl const&) = default;

    virtual ~ProxyImpl() = default;

    /// @brief Start the service.
    virtual bool startoff() noexcept override;

    /// @brief Stop the service.
    virtual bool shutdown() noexcept override;

    /// @brief Instruct STM to reset the machine.
    virtual Error reset_machine() noexcept override;

    /// @brief Instruct STM to enter update state.
    virtual Error update_enter() noexcept override;

    /// @brief Instruct STM to leave update state.
    virtual Error update_leave() noexcept override;

    /// @brief Request STM to put the listed entries in verify state.
    /// @param fg_list List of FGs to be transitioned
    virtual Error
    fg_verify(const std::vector<lib::stm::FG_Ident>& fg_list)
    noexcept override;

    /// @brief Request STM to put the listed entries in activate state.
    /// @param fg_list List of FGs to be transitioned
    virtual Error
    fg_activate(const std::vector<lib::stm::FG_Ident>& fg_list)
    noexcept override;

    /// @brief Request STM to put the listed entries in rollback state.
    /// @param fg_list List of FGs to be transitioned
    virtual Error
    fg_rollback(const std::vector<lib::stm::FG_Ident>& fg_list)
    noexcept override;
};


}    // namespace stm
}    // namespace app
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif    // UCM_AAP_LIBRARY__UCM_APP_STM__PROXY_IMPL_H_
