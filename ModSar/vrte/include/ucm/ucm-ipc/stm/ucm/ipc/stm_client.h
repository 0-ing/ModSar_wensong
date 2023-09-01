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

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

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
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test__stm_ucm_ipc__STM_Client, CTor_TEST);
#endif

public:
    explicit STM_Client(const std::string servername, std::string clientname,
                        uint64_t uuid);

    STM_Client(STM_Client     &&) = default;
    STM_Client(STM_Client const&) = default;

    STM_Client& operator=(STM_Client     &&) = default;
    STM_Client& operator=(STM_Client const&) = default;

    virtual ~STM_Client() = default;

    std::error_condition request(
            const STM_Message::Action&, const std::vector<std::string>&) noexcept;

    std::error_condition response(STM_Message::Action&,
                                  STM_Message::Result&,
                                  std::vector<std::string>& clusters) noexcept;
};

}    // namespace ipc
}    // namespace ucm
}    // namespace exm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_IPC__STM_UCM_IPC__STM_CLIENT__H_

