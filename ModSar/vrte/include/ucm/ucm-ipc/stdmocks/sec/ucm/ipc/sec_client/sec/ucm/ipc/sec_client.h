//==============================================================================
// C O P Y R I G H T
//------------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//==============================================================================

/// @file         sec/ucm/ipc/sec_client.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_IPC__SEC_UCM_IPC__SEC_CLIENT__H_
#define UCM_AAP_IPC__SEC_UCM_IPC__SEC_CLIENT__H_

#include <system_error>

#include "ucm/mock/sequence.h"
#include "ucm/lib/ipc/ipc_client.h"
#include "sec/ucm/ipc/sec_message.h"

namespace bosch {
namespace vrte  {
namespace sec   {
namespace ucm   {
namespace ipc   {

/// @brief Wrapper around the IPC client implementation
class SEC_Client
        : public bosch::vrte::ucm::lib::ipc::IPC_Client
{

public:
    explicit SEC_Client(uint64_t uuid)
    : bosch::vrte::ucm::lib::ipc::IPC_Client(uuid)
    {
        pop<void>();
    }

    SEC_Client(SEC_Client     &&) = default;
    SEC_Client(SEC_Client const&) = default;

    SEC_Client& operator=(SEC_Client     &&) = default;
    SEC_Client& operator=(SEC_Client const&) = default;

    virtual ~SEC_Client() = default;

    std::error_condition request(
            const SEC_Message::Action&, const std::string&) noexcept
    {
        return pop<std::error_condition>();
    }

    std::error_condition response(SEC_Message::Action&,
                                  SEC_Message::Result&,
                                  std::string& swc_result) noexcept
    {
        swc_result = pop<std::string>();
        return pop<std::error_condition>();
    }

};

}    // namespace ipc
}    // namespace ucm
}    // namespace sec
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_IPC__SEC_UCM_IPC__SEC_CLIENT__H_

