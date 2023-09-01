//==============================================================================
// C O P Y R I G H T
//------------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//==============================================================================

/// @file         stm/ucm/ipc/stm_message.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author
/// @version
/// @remarks

#ifndef UCM_AAP_IPC__ARA_CLIENT_IPC__ARA_CLIENT_MESSAGE__H_
#define UCM_AAP_IPC__ARA_CLIENT_IPC__ARA_CLIENT_MESSAGE__H_

#include <system_error>

#include "ucm/lib/ipc/ipc_message.h"
#include <array>
#include <string>
#include <vector>

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace ipc   {


class STM_Message : public bosch::vrte::ucm::lib::ipc::IPC_Message
{

public:
    // actions for STM UpdateRequest
    enum class Action : uint32_t
    {
      kResetMachine,
      kStopUpdateSession,
    #ifdef ARA_VERSION_20_11
      kStartUpdateSession,
    #else
      kRequestUpdateSession,
    #endif
      kPrepareUpdate,
      kVerifyUpdate,
      kPrepareRollback,
      kFailure
    };

    static const char *action_cstr(const Action&) noexcept
    {
        return pop<const char *>();
    }

    enum class Result : unsigned
    {
      kSuccess,
      kFailure
    };

    static const char *result_cstr(const Result&) noexcept
    {
        return pop<const char *>();
    }

    explicit STM_Message(struct ucm_ipcmsg&) noexcept = default;

    STM_Message(STM_Message     &&) = default;
    STM_Message(STM_Message const&) = default;

    STM_Message& operator=(STM_Message     &&) = default;
    STM_Message& operator=(STM_Message const&) = default;

    virtual ~STM_Message() = default;

    std::error_condition
    make_request(const Action&, const std::vector<std::string>&) noexcept
    {
        return pop<std::error_condition>();
    }

    void read_request(Action&, std::vector<std::string>&) noexcept {}

    void save_response(const Result&) noexcept {}

    void read_response(Action&, Result&, std::vector<std::string>&) noexcept {}
};


}    // namespace ipc
}    // namespace ucm
}    // namespace exm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_IPC__ARA_CLIENT_IPC__ARA_CLIENT_MESSAGE__H_

