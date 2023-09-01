//==============================================================================
// C O P Y R I G H T
//------------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//==============================================================================

/// @file         ucm/lib/ipc/ipc_client.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_IPC__UCM_LIB_IPC__IPC_CLIENT__H_
#define UCM_AAP_IPC__UCM_LIB_IPC__IPC_CLIENT__H_

#include <system_error>

#include "ucm/mock/sequence.h"

#include "ucm/lib/ipc/c_mq_ipc.h"
#include "ucm/lib/ipc/ipc_message.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace ipc   {

/// @brief Wrapper around the IPC client implementation
class IPC_Client : virtual protected ucm::mock::Sequence
{

public:
    explicit IPC_Client(const std::string&,
                        const std::string&,
                        uint64_t) {}

    explicit IPC_Client(uint64_t) {}

    IPC_Client(IPC_Client     &&) = default;
    IPC_Client(IPC_Client const&) = default;

    IPC_Client& operator=(IPC_Client     &&) = default;
    IPC_Client& operator=(IPC_Client const&) = default;

    virtual ~IPC_Client() = default;

    /// @brief Send a prepared in the buffer EXEC message
    std::error_condition send() noexcept
    {
        return pop<std::error_condition>();
    }


    /// @brief Send a ping to the server
    IPC_Message ping() noexcept { return pop<IPC_Message>(); }

    /// @brief Send a ping to the server
    IPC_Message kill() noexcept { return pop<IPC_Message>(); }

};

}    // namespace ipc
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_IPC__UCM_LIB_IPC__IPC_CLIENT__H_

