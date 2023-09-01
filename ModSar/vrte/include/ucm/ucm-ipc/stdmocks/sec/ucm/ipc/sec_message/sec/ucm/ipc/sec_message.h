//==============================================================================
// C O P Y R I G H T
//------------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//==============================================================================

/// @file         sec/ucm/ipc/sec_message.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_IPC__SEC_UCM_IPC__SEC_MESSAGE__H_
#define UCM_AAP_IPC__SEC_UCM_IPC__SEC_MESSAGE__H_

#include <system_error>

#include "ucm/mock/sequence.h"
#include "ucm/lib/ipc/ipc_message.h"

namespace bosch {
namespace vrte  {
namespace sec   {
namespace ucm   {
namespace ipc   {

class SEC_Message
        : public bosch::vrte::ucm::lib::ipc::IPC_Message
{

public:
    enum class Action : uint32_t
    {
      kUpdate,
      kInstall,
      kRemove,
      kFailure
    };

    static const char *action_cstr(const Action&) noexcept
    { 
      return pop<const char*>();
    }

    enum class Result : unsigned
    {
      kSuccess,
      kFailure
    };

    static const char *result_cstr(const Result&) noexcept
    { 
      return pop<const char*>();
    }

    explicit SEC_Message(struct ucm_ipcmsg& ptr) noexcept
    : bosch::vrte::ucm::lib::ipc::IPC_Message(ptr)
    {}

    SEC_Message(SEC_Message     &&) = default;
    SEC_Message(SEC_Message const&) = default;

    SEC_Message& operator=(SEC_Message     &&) = default;
    SEC_Message& operator=(SEC_Message const&) = default;

    virtual ~SEC_Message() = default;

    std::error_condition
    make_request(const Action&, const std::string&) noexcept
    {
        return pop<std::error_condition>();
    }

    void read_request(Action&, std::string&) noexcept{}

    void save_response(const Result&) noexcept{}

    void read_response(Action&, Result&, std::string&) noexcept{}
};


}    // namespace ipc
}    // namespace ucm
}    // namespace sec
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_IPC__SEC_UCM_IPC__SEC_MESSAGE__H_

