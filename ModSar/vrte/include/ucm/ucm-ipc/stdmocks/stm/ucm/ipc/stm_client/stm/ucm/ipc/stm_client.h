//==============================================================================
// C O P Y R I G H T
//------------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//==============================================================================

/// @file         stm/ucm/ipc/stm_client.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author
/// @version
/// @remarks

#ifndef UCM_AAP_IPC__STM_UCM_IPC__STM_CLIENT__H_
#define UCM_AAP_IPC__STM_UCM_IPC__STM_CLIENT__H_

#include <system_error>


#include "ucm/lib/ipc/ipc_client.h"
#include "stm_message.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace ipc   {

/// @brief Wrapper around the IPC client implementation
class STM_Client : public bosch::vrte::ucm::lib::ipc::IPC_Client
{

public:
    explicit STM_Client(const std::string, std::string,
                        uint64_t) = default;

    STM_Client(STM_Client     &&) = default;
    STM_Client(STM_Client const&) = default;

    STM_Client& operator=(STM_Client     &&) = default;
    STM_Client& operator=(STM_Client const&) = default;

    virtual ~STM_Client() = default;

    std::error_condition request(
            const STM_Message::Action&,
            const std::vector<std::string>&) noexcept
    {
        return pop<std::error_condition>();
    }

    std::error_condition response(STM_Message::Action&,
                                  STM_Message::Result&,
                                  std::vector<std::string>&) noexcept
    {
        return pop<std::error_condition>();
    }
};

}    // namespace ipc
}    // namespace ucm
}    // namespace exm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_IPC__STM_UCM_IPC__STM_CLIENT__H_

