//==============================================================================
// C O P Y R I G H T
//------------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//==============================================================================

/// @file         exm/ucm/ipc/exm_server.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_IPC__EXM_UCM_IPC__EXM_SERVER__H_
#define UCM_AAP_IPC__EXM_UCM_IPC__EXM_SERVER__H_

#include <string>
#include <utility>
#include <functional>
#include <system_error>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/ipc/ipc_server.h"
#include "exm/ucm/ipc/exm_mqconf.h"
#include "ucm/lib/ipc/ipc_message.h"
#include "exm/ucm/ipc/exm_message.h"

/// @addtogroup bosch_vrte_exm_ucm_ipc
/// @{

namespace bosch {
namespace vrte  {
namespace exm   {
namespace ucm   {
namespace ipc   {

/// @brief Wrapper around IPC server implementation for EXM
class EXM_Server : public bosch::vrte::ucm::lib::ipc::IPC_Server
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test__exm_ucm_ipc__EXM_Server, CTor_TEST);
#endif

public:
    using callback_type = std::function<bool(
            const EXM_Message::Action&, const std::string&)>;

    explicit EXM_Server(callback_type&&);

    EXM_Server(EXM_Server     &&) = default;
    EXM_Server(EXM_Server const&) = default;

    EXM_Server& operator=(EXM_Server     &&) = default;
    EXM_Server& operator=(EXM_Server const&) = default;

    virtual ~EXM_Server() = default;

protected:
    virtual void callback(
            bosch::vrte::ucm::lib::ipc::IPC_Message&&) noexcept override;

private:
    callback_type callback_{};
};


}    // namespace ipc
}    // namespace ucm
}    // namespace exm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif // UCM_AAP_IPC__EXM_UCM_IPC__EXM_SERVER__H_

