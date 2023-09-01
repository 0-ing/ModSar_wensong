//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/vrte/stm/proxy_impl.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks
/// @ingroup      bosch_vrte_ucm_vrte_stm

#ifndef UCM_AAP_PROCESSING_VRTE__UCM_VRTE_STM__PROXY_IMPL_H_
#define UCM_AAP_PROCESSING_VRTE__UCM_VRTE_STM__PROXY_IMPL_H_

#include <memory>
#include <vector>
#include <string>


#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/stm/proxy.h"
#include "ucm/vrte/stm/ara_proxy.h"

/// @addtogroup bosch_vrte_ucm_vrte_stm
/// @{

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace vrte  {
namespace stm   {

/// @brief Implementation of STM Proxy API for VRTE STM
class ProxyImpl : public lib::stm::Proxy
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test__ucm_vrte_stm__ProxyImpl, CTor);
    FRIEND_TEST(Test__ucm_vrte_stm__ProxyImpl, Startoff);
    FRIEND_TEST(Test__ucm_vrte_stm__ProxyImpl, Shutdown);
    FRIEND_TEST(Test__ucm_vrte_stm__ProxyImpl, ResetMachine);
    FRIEND_TEST(Test__ucm_vrte_stm__ProxyImpl, UpdateEnter);
    FRIEND_TEST(Test__ucm_vrte_stm__ProxyImpl, UpdateLeave);
    FRIEND_TEST(Test__ucm_vrte_stm__ProxyImpl, FG_Verify);
    FRIEND_TEST(Test__ucm_vrte_stm__ProxyImpl, FG_Activate);
    FRIEND_TEST(Test__ucm_vrte_stm__ProxyImpl, FG_Rollback);
#endif
public:
    explicit ProxyImpl() = default;

    ProxyImpl(ProxyImpl     &&) = delete;
    ProxyImpl(ProxyImpl const&) = delete;

    ProxyImpl& operator=(ProxyImpl     &&) = delete;
    ProxyImpl& operator=(ProxyImpl const&) = delete;

    virtual ~ProxyImpl() = default;

    /// @brief Subscribe to the STM service and start using it.
    /// @param [IN]  None
    /// @param [OUT] None
    /// @return true on success, false otherwise
    virtual bool startoff() noexcept override;

    /// @brief Un-subscribe to the STM service and stop using it.
    /// @param [IN]  None
    /// @param [OUT] None
    /// @return  true on success, false otherwise
    virtual bool shutdown() noexcept override;

    /// @brief Instruct STM to reset the machine.
    /// @param [IN]  None
    /// @param [OUT] None
    /// @return Success or failure
    virtual Error reset_machine() noexcept override;

    /// @brief Instruct STM to enter update state.
    /// @param [IN]  None
    /// @param [OUT] None
    /// @return Success or failure
    virtual Error update_enter() noexcept override;

    /// @brief Instruct STM to leave update state.
    /// @param [IN]  None
    /// @param [OUT] None
    /// @return Success or failure
    virtual Error update_leave() noexcept override;

    /// @brief Request STM to put the listed entries in verify state.
    /// @param  [IN] fg_list List of FGs to be transitioned
    /// @param [OUT] None
    /// @return Success or failure
    virtual Error
    fg_verify(const std::vector<lib::stm::FG_Ident>& fg_list)
    noexcept override;

    /// @brief Request STM to put the listed entries in activate state.
    /// @param [IN] fg_list List of FGs to be transitioned
    /// @param [OUT] None
    /// @return Success or failure
    virtual Error
    fg_activate(const std::vector<lib::stm::FG_Ident>& fg_list)
    noexcept override;

    /// @brief Request STM to put the listed entries in rollback state.
    /// @param [IN] fg_list List of FGs to be transitioned
    /// @param [OUT] None
    /// @return Success or failure
    virtual Error
    fg_rollback(const std::vector<lib::stm::FG_Ident>& fg_list)
    noexcept override;

private:
    AraProxy aracomif_{};   ///< ARA::COM proxy to the service itself

    bool subscription_check() noexcept;
};


}    // namespace stm
}    // namespace vrte
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif    // UCM_AAP_PROCESSING_VRTE__UCM_VRTE_STM__PROXY_IMPL_H_
