//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/vrte/stm/ara_proxy.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @version
/// @remarks
/// @ingroup      bosch_vrte_ucm_vrte_stm

#ifndef UCM_AAP_PROCESSING_VRTE__UCM_VRTE_STM__ARA_PROXY_H_
#define UCM_AAP_PROCESSING_VRTE__UCM_VRTE_STM__ARA_PROXY_H_

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include <mutex>
#include <chrono>
#include <memory>

#include "ucm/lib/log/logger.h"
#include "ucm/lib/stm/fg_ident.h"
#include "ucm/lib/stm/fg_state.h"
#include "ucm/vrte/stm/aracom_includes.h"

/// @addtogroup bosch_vrte_ucm_vrte_stm
/// @{


namespace bosch  {
namespace vrte   {
namespace ucm    {
namespace vrte   {
namespace stm    {

/// @brief Adaptor class for calling STM API.
class AraProxy final
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test__ucm_vrte_stm__AraProxy, CTor);
    FRIEND_TEST(Test__ucm_vrte_stm__AraProxy, Subscribe);
    FRIEND_TEST(Test__ucm_vrte_stm__AraProxy, ResetMachine);
    FRIEND_TEST(Test__ucm_vrte_stm__AraProxy, UpdateSession);
    FRIEND_TEST(Test__ucm_vrte_stm__AraProxy, StopUpdateSession);
    FRIEND_TEST(Test__ucm_vrte_stm__AraProxy, PrepareUpdate);
    FRIEND_TEST(Test__ucm_vrte_stm__AraProxy, VerifyUpdate);
    FRIEND_TEST(Test__ucm_vrte_stm__AraProxy, PrepareRollback);
#endif

    /// @brief Default ara::com/stm timeout
    constexpr static const auto timeout() noexcept
    {
        return std::chrono::seconds(3600);
    }

    /// @brief Default ARA::COM instance ID
    constexpr static const char* ara_instance_id = "1";

    /// @brief Default ARA::COM POSIX MQ name
    constexpr static const char* ara_mq_app_name =
                "/UpdateConfigurationManagement";

    using runtime_type  = ::ara::Runtime;

public:
    using result_type   = ::ara::core::future_status;
    using instance_type = ::ara::com::InstanceIdentifier;
    using araproxy_type = ::ara::sm::update_request::proxy::UpdateRequestProxy;
    using ARATypes      = ucm::lib::ara::ARATypes;

    /// @brief Construct the adaptor object and
    /// initialize the ARA::COM instance.
    explicit AraProxy();

    AraProxy(AraProxy     &&) = delete;
    AraProxy(AraProxy const&) = delete;

    AraProxy& operator=(AraProxy     &&) = delete;
    AraProxy& operator=(AraProxy const&) = delete;

    ~AraProxy();

    /// @brief Provide subscription status
    /// @param [IN]  None
    /// @param [OUT] None
    /// @return Subscription status TRUE or FALSE
    bool subscribed() const noexcept;

    /// @brief Subscribe to the STM service.
    /// @param [IN] None
    /// @param [OUT] None
    /// @return Void
    void SubscribeService();

    /// @brief Request STM to reset the machine.
    /// @param [IN] None
    /// @param [OUT] None
    /// @return Application Errors
    ::ara::sm::update_request::OutputResetMachine
     ResetMachine();

#ifdef ARA_VERSION_20_11
    /// @brief Request STM to leave update state.
    /// @param [IN] None
    /// @param [OUT] None
    /// @return void
    void StopUpdateSession();

    /// @brief Request STM to enter update state.
    /// @param [IN] None
    /// @param [OUT] None
    /// @return Application Errors
    ::ara::sm::update_request::OutputStartUpdateSession 
      StartUpdateSession();
#else
    /// @brief Request STM to leave update state.
    /// @param [IN] None
    /// @param [OUT] None
    /// @return Application Errors
    ::ara::sm::update_request::OutputStopUpdateSession 
      StopUpdateSession();

    /// @brief Request STM to enter update state.
    /// @param [IN] ] FG list
    /// @param [OUT] None
    /// @return Application Errors
    ::ara::sm::update_request::OutputRequestUpdateSession
      RequestUpdateSession();
#endif

    /// @brief Request STM to prepare the given FGs for update.
    /// @param [IN] ] FG list
    /// @param [OUT] None
    /// @return Application Errors
    ::ara::sm::update_request::OutputPrepareUpdate
     PrepareUpdate(const std::vector<lib::stm::FG_Ident>& fg_list);

    /// @brief Request STM to verify the update of the given FGs.
    /// @param [IN] FG list
    /// @param [OUT] None
    /// @return Application Errors
    ::ara::sm::update_request::OutputVerifyUpdate
     VerifyUpdate(const std::vector<lib::stm::FG_Ident>& fg_list);

    /// @brief Request STM to prepare the given FGs for rollback.
    /// @param [IN] FG list
    /// @param [OUT] None
    /// @return Application Errors
    ::ara::sm::update_request::OutputPrepareRollback
     PrepareRollback(const std::vector<lib::stm::FG_Ident>& fg_list);

private:
    /// @brief Convert the internal UCM function group list to STM compatible.
    ::ara::sm::FunctionGroupList
     convert_clusters_to_ara(const std::vector<lib::stm::FG_Ident>& fg_list);

    runtime_type&                  ara_runtime_;
    instance_type                  ara_instance_;
    mutable std::mutex             mutex_{};
    std::unique_ptr<araproxy_type> araproxy_{};
};


}    // namespace stm
}    // namespace vrte
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif // UCM_AAP_PROCESSING_VRTE__UCM_VRTE_STM__ARA_PROXY_H_
