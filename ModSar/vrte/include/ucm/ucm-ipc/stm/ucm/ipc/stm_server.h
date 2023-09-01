//==============================================================================
// C O P Y R I G H T
//------------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//==============================================================================

/// @file         stm/ucm/ipc/stm_server.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author
/// @version
/// @remarks

#ifndef UCM_AAP_IPC__STM_UCM_IPC__STM_SERVER__H_
#define UCM_AAP_IPC__STM_UCM_IPC__STM_SERVER__H_

#include <string>
#include <utility>
#include <functional>
#include <system_error>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/ipc/ipc_server.h"
#include "ucm/lib/ipc/ipc_message.h"
#include "stm_message.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace ipc   {

/// @brief Wrapper around IPC server implementation
class STM_Server : public bosch::vrte::ucm::lib::ipc::IPC_Server
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test__stm_ucm_ipc__STM_Server, CTor_TEST);
#endif

public:
    using callback_type = std::function<bool(
            const STM_Message::Action&, const std::vector<std::string>&)>;

    explicit STM_Server(const std::string servername, std::string clientname,
                        callback_type&&);

    STM_Server(STM_Server     &&) = default;
    STM_Server(STM_Server const&) = default;

    STM_Server& operator=(STM_Server     &&) = default;
    STM_Server& operator=(STM_Server const&) = default;

    virtual ~STM_Server() = default;

protected:
    virtual void callback(
            bosch::vrte::ucm::lib::ipc::IPC_Message&&) noexcept override;

private:
    /// called by method callback
    callback_type callback_{};
};


}    // namespace ipc
}    // namespace ucm
}    // namespace exm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_IPC__STM_UCM_IPC__STM_SERVER__H_

