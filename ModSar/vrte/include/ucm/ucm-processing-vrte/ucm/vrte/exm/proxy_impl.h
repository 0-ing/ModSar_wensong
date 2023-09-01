//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/vrte/exm/proxy_impl.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks
/// @ingroup      bosch_vrte_ucm_vrte_exm

#ifndef UCM_AAP_PROCESSING_VRTE__UCM_VRTE_EXM__PROXY_IMPL_H_
#define UCM_AAP_PROCESSING_VRTE__UCM_VRTE_EXM__PROXY_IMPL_H_

#include <memory>
#include <string>
#include <cstdint>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/exm/proxy.h"
#include "ucm/lib/ipc/ipc_client.h"
#include "exm/ucm/ipc/exm_client.h"
#include "exm/ucm/ipc/exm_message.h"

/// @addtogroup bosch_vrte_ucm_vrte_exm
/// @{

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace vrte  {
namespace exm   {

/// @brief EXM Proxy implementation.
///

class ProxyImpl : public lib::exm::Proxy
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test__ucm_vrte_exm__Proxy, CTor);
#endif

    constexpr static uint64_t exm_client_uuid = UCM_MQIPC_CLIENT_UUID_DEFAULT;

public:
    virtual ~ProxyImpl() = default;

    explicit ProxyImpl() = default;

    ProxyImpl(ProxyImpl     &&) = default;
    ProxyImpl(ProxyImpl const&) = delete;

    ProxyImpl& operator=(ProxyImpl     &&) = default;
    ProxyImpl& operator=(ProxyImpl const&) = delete;

    /// @brief Start EXM IPC Client
    /// @param [IN]  None
    /// @param [OUT] None
    /// @return  Success or failure
    ///          - TRUE : EXM IPC Client started successfully
    ///          - FALSE : EXM IPC Client failed to start
    virtual bool
    startoff() noexcept override;

    /// @brief Shutdown EXM IPC Client
    /// @param [IN]  None
    /// @param [OUT] None
    /// @return  Success or failure
    ///          - TRUE : EXM IPC Client terminated successfully
    ///          - FALSE : EXM IPC Client failed to terminate
    virtual bool
    shutdown() noexcept override;

    /// @brief Send IPC message of App action for SWC and
    ///        check IPC response
    /// @param [IN] Application action of type :lib::exm::AppAction
    ///             SWC name of type : std::string
    /// @param [OUT] None
    /// @return  IPC interaction Success or failure
    ///          - TRUE : IPC result Successful
    ///          - FALSE : IPC result failed
    virtual bool
    app_action(const lib::exm::AppAction&, const std::string&)
    noexcept override;

private:
protected:
    std::unique_ptr<bosch::vrte::exm::ucm::ipc::EXM_Client> exm_client_{};
};

}    // namespace exm
}    // namespace vrte
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif    // UCM_AAP_PROCESSING_VRTE__UCM_VRTE_EXM__PROXY_IMPL_H_
