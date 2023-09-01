//==============================================================================
// C O P Y R I G H T
//------------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//==============================================================================

/// @file         ucm/lib/ipc/ipc_server.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_IPC__UCM_LIB_IPC__IPC_SERVER__H_
#define UCM_AAP_IPC__UCM_LIB_IPC__IPC_SERVER__H_

#include <utility>
#include <functional>
#include <system_error>
#include <array>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/ipc/c_mq_ipc.h"
#include "ucm/lib/ipc/ipc_message.h"

/// @addtogroup bosch_vrte_ucm_lib_ipc
/// @{

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace ipc   {

/// @brief Wrapper around IPC server implementation
class IPC_Server
{
#if defined(GOOGLE_TEST)
    friend class Test__ucm_lib_ipc__IPC_Server;
#endif

public:
    explicit IPC_Server(const std::string& servername,
                        const std::string& clientname);

    IPC_Server(IPC_Server     &&) = default;
    IPC_Server(IPC_Server const&) = default;

    IPC_Server& operator=(IPC_Server     &&) = default;
    IPC_Server& operator=(IPC_Server const&) = default;

    virtual ~IPC_Server();

    void listen() noexcept;

protected:
    virtual void callback(IPC_Message&& msg) noexcept;

private:
    struct mqipc_server  srv_{};
    struct mqipc_mqopts  rxopts_{};
    struct mqipc_srvopts srvopts_{};
    struct mqipc_peer    clients_[16];
    // array to store the name part of the clients mqueue
    // an array is used since memory should only be statically allocated
    std::array<char, UCM_MQIPC_NAMESIZE + 1> a_clientname_;
};


}    // namespace ipc
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif // UCM_AAP_IPC__UCM_LIB_IPC__IPC_SERVER__H_

