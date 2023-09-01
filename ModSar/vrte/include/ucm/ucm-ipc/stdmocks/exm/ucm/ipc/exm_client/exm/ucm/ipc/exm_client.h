//==============================================================================
// C O P Y R I G H T
//------------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//==============================================================================

/// @file         exm/ucm/ipc/exm_client.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_IPC__EXM_UCM_IPC__EXM_CLIENT__H_
#define UCM_AAP_IPC__EXM_UCM_IPC__EXM_CLIENT__H_

#include <system_error>


#include "ucm/lib/ipc/ipc_client.h"
#include "exm/ucm/ipc/exm_message.h"

namespace bosch {
namespace vrte  {
namespace exm   {
namespace ucm   {
namespace ipc   {

/// @brief Wrapper around the IPC client implementation
class EXM_Client : public bosch::vrte::ucm::lib::ipc::IPC_Client
{

public:
    explicit EXM_Client(uint64_t) {}

    EXM_Client(EXM_Client     &&) = default;
    EXM_Client(EXM_Client const&) = default;

    EXM_Client& operator=(EXM_Client     &&) = default;
    EXM_Client& operator=(EXM_Client const&) = default;

    virtual ~EXM_Client() = default;

    std::error_condition request(
            const EXM_Message::Action&, const std::string&) noexcept
    {
        return pop<std::error_condition>();
    }

    std::error_condition response(EXM_Message::Action&,
                                  EXM_Message::Result&,
                                  std::string&) noexcept
    {
        return pop<std::error_condition>();
    }
};

}    // namespace ipc
}    // namespace ucm
}    // namespace exm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_IPC__EXM_UCM_IPC__EXM_CLIENT__H_

