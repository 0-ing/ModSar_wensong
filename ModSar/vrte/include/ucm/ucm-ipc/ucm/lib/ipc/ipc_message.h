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

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/ipc/c_ipc_msg.h"

/// @addtogroup bosch_vrte_ucm_lib_ipc
/// @{

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace ipc   {

/// @brief Wrapper around struct ucm_ipcmsg
class IPC_Message
{
#if defined(GOOGLE_TEST)
    friend class Test__ucm_lib_ipc__IPC_Message;
#endif

public:
    explicit IPC_Message(struct ucm_ipcmsg& ref) noexcept;

    IPC_Message(IPC_Message     &&) = default;
    IPC_Message(IPC_Message const&) = default;

    IPC_Message& operator=(IPC_Message     &&) = delete;
    IPC_Message& operator=(IPC_Message const&) = delete;

    virtual ~IPC_Message() = default;

    auto& buffer() noexcept;

    /// @brief Write data to the message
    /// @param sbuff Data buffer to append to the message data
    /// @param slen Size of the data buffer
    /// @return std::error_condition produced by std::generic_category()
    std::error_condition write(const void *sbuff, size_t slen) noexcept;

    /// @brief Read data from the message
    /// @param dbuff Data buffer to writer to
    /// @param dlen Size of the data buffer
    /// @return std::error_condition produced by std::generic_category()
    std::error_condition read(void *dbuff, size_t& dlen) noexcept;

protected:
    size_t cursor_{0};
    struct ucm_ipcmsg& msg_;
};

inline auto& IPC_Message::buffer() noexcept
{
    return msg_;
}

}    // namespace ipc
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif // UCM_AAP_IPC__UCM_LIB_IPC__IPC_MESSAGE__H_

