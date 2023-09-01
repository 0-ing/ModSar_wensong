//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/vrte/sec/proxy_impl.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks
/// @ingroup      bosch_vrte_ucm_vrte_sec

#ifndef UCM_AAP_PROCESSING_VRTE__UCM_VRTE_SEC__PROXY_IMPL_H_
#define UCM_AAP_PROCESSING_VRTE__UCM_VRTE_SEC__PROXY_IMPL_H_

#include <memory>
#include <string>
#include <cstdint>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/sec/proxy.h"
#include "ucm/lib/ipc/ipc_client.h"
#include "sec/ucm/ipc/sec_client.h"
#include "sec/ucm/ipc/sec_message.h"

/// @addtogroup bosch_vrte_ucm_vrte_sec
/// @{

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace vrte  {
namespace sec   {

/// @brief SEC proxy implementation.
///

class ProxyImpl final : public lib::sec::Proxy
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test__ucm_vrte_sec__Proxy, CTor);
#endif

    constexpr static uint64_t sec_client_uuid = 42;

public:
    virtual ~ProxyImpl() = default;

    explicit ProxyImpl() = default;

    ProxyImpl(ProxyImpl     &&) = default;
    ProxyImpl(ProxyImpl const&) = delete;

    ProxyImpl& operator=(ProxyImpl     &&) = default;
    ProxyImpl& operator=(ProxyImpl const&) = delete;

    /// @brief Start SEC IPC Client
    /// @param [IN]  None
    /// @param [OUT] None
    /// @return  Success or failure
    ///          - TRUE : SEC IPC Client started successfully
    ///          - FALSE : SEC IPC Client failed to start
    bool
    startoff() noexcept override;

    /// @brief Shutdown SEC IPC Client
    /// @param [IN]  None
    /// @param [OUT] None
    /// @return  Success or failure
    ///          - TRUE : SEC IPC Client terminated successfully
    ///          - FALSE : SEC IPC Client failed to terminate
    bool
    shutdown() noexcept override;

    /// @brief Send IPC message of App action for SWC and
    ///        check IPC response
    /// @param [IN] Application action of type :lib::sec::AppAction
    ///             SWC name of type : std::string
    /// @param [OUT] None
    /// @return  IPC interaction Success or failure
    ///          - TRUE : IPC result Successful
    ///          - FALSE : IPC result failed
    bool
    app_action(const lib::sec::AppAction&, const std::string&)
    noexcept override;

private:
protected:
    std::unique_ptr<bosch::vrte::sec::ucm::ipc::SEC_Client> sec_client_{};
};

}    // namespace sec
}    // namespace vrte
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif    // UCM_AAP_PROCESSING_VRTE__UCM_VRTE_SEC__PROXY_IMPL_H_
