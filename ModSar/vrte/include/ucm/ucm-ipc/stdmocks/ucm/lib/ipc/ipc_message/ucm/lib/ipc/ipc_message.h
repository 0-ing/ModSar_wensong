//==============================================================================
// C O P Y R I G H T
//------------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//==============================================================================

/// @file         ucm/lib/ipc/ipc_message.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_IPC__UCM_LIB_IPC__IPC_MESSAGE__H_
#define UCM_AAP_IPC__UCM_LIB_IPC__IPC_MESSAGE__H_

#include <system_error>

#include "ucm/mock/sequence.h"
#include "ucm/lib/ipc/c_ipc_msg.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace ipc   {

/// @brief Wrapper around struct ucm_ipcmsg
class IPC_Message : virtual protected ucm::mock::Sequence
{

public:
    explicit IPC_Message(struct ucm_ipcmsg&) noexcept {}

    IPC_Message(IPC_Message     &&) = default;
    IPC_Message(IPC_Message const&) = default;

    IPC_Message& operator=(IPC_Message     &&) = default;
    IPC_Message& operator=(IPC_Message const&) = default;

    virtual ~IPC_Message() = default;

    ucm_ipcmsg& buffer() noexcept { return pop<ucm_ipcmsg&>(); }

    /// @brief Write data to the message
    /// @param sbuff Data buffer to append to the message data
    /// @param slen Size of the data buffer
    /// @return std::error_condition produced by std::generic_category()
    std::error_condition write(const void *sbuff, size_t slen) noexcept
    {
        return pop<std::error_condition>();
    }

    /// @brief Read data from the message
    /// @param dbuff Data buffer to writer to
    /// @param dlen Size of the data buffer
    /// @return std::error_condition produced by std::generic_category()
    std::error_condition read(void *dbuff, size_t& dlen) noexcept
    {
        return pop<std::error_condition>();
    }
};


}    // namespace ipc
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_IPC__UCM_LIB_IPC__IPC_MESSAGE__H_

