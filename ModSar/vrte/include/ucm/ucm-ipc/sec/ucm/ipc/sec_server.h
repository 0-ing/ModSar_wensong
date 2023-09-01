//==============================================================================
// C O P Y R I G H T
//------------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//==============================================================================

/// @file         sec/ucm/ipc/sec_server.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_IPC__SEC_UCM_IPC__SEC_SERVER__H_
#define UCM_AAP_IPC__SEC_UCM_IPC__SEC_SERVER__H_

#include <string>
#include <utility>
#include <functional>
#include <system_error>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/ipc/ipc_server.h"
#include "sec/ucm/ipc/sec_mqconf.h"
#include "ucm/lib/ipc/ipc_message.h"
#include "sec/ucm/ipc/sec_message.h"

/// @addtogroup bosch_vrte_sec_ucm_ipc
/// @{

namespace bosch {
namespace vrte  {
namespace sec   {
namespace ucm   {
namespace ipc   {

/// @brief Wrapper around IPC server implementation for SEC
class SEC_Server : public bosch::vrte::ucm::lib::ipc::IPC_Server
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test__sec_ucm_ipc__SEC_Server, CTor_TEST1);
#endif

public:
    using callback_type = std::function<bool(
            const SEC_Message::Action&, const std::string&)>;

    explicit SEC_Server(callback_type&&);

    SEC_Server(SEC_Server     &&) = default;
    SEC_Server(SEC_Server const&) = default;

    SEC_Server& operator=(SEC_Server     &&) = default;
    SEC_Server& operator=(SEC_Server const&) = default;

    virtual ~SEC_Server() = default;

protected:
    virtual void callback(
            bosch::vrte::ucm::lib::ipc::IPC_Message&&) noexcept override;

private:
    callback_type callback_{};
};


}    // namespace ipc
}    // namespace ucm
}    // namespace sec
}    // namespace vrte
}    // namespace bosch

/// @}

#endif // UCM_AAP_IPC__SEC_UCM_IPC__SEC_SERVER__H_

