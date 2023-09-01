//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
/// @copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================
/// @file      IChannel.hpp
/// @brief     Declaration/Definition of IChannel
/// @author    baetz
//=============================================================================
#ifndef ICHANNEL_HPP_INCLUDED
#define ICHANNEL_HPP_INCLUDED

#include "FileDesc.hpp"
#include "IChannelMessage.hpp"
#include "StdReturnType.hpp"

namespace exm
{

/// @brief Class for the communication channel
class IChannel
{
public:
    /// @brief Destructor.

    virtual ~IChannel() {
    } // Not covered: Deleting destructors of pure virtual base classes can not be called.

    /// @brief Initializes the communication channel.
    /// Automatically sets the read descriptor to non-blocking mode.
    /// @param fd_read   File descriptor to read from.
    /// @param fd_write  File descriptor to write to.
    /// @return StdReturnType
    /// @retval  OK on success
    /// @retval  GENERAL_ERROR if fd_read or fd_write is invalid or options can't be set.

    virtual StdReturnType Init(FileDesc fd_read, FileDesc fd_write) = 0;
    virtual StdReturnType Init(FileDesc fd_read, FileDesc fd_write, bool isBlocking) = 0;

    /// @brief Send a message over the channel
    /// @param message   The message to be sent
    /// @return  StdReturnType
    /// @retval  OK if the message was successfully sent
    /// @retval  INVALID_ARGUMENTS if nullptr is passed
    /// @retval  GENERAL_ERROR   if an error in the message format was detected, or if sending
    /// failed.

    virtual StdReturnType SendMessage(IChannelMessage* const message) = 0;

    /// @brief Reads the next complete message from the pipe.
    /// @param message   A pointer to a message, which contains the buffer for receiving the
    /// message.
    /// @return  StdReturnType
    /// @retval  OK if the next message was successfully received
    /// @retval  INVALID_ARGUMENTS if nullptr is passed
    /// @retval  GENERAL_ERROR   if an error in the message format was detected, or if receiving
    /// failed.

    virtual StdReturnType ReadNextMessage(IChannelMessage* const message) = 0;

    /// @brief Waits until data to read becomes available.
    /// @param[in] timeInMs Time to wait in ms.
    /// @return  StdReturnType
    /// @retval  OK              OK
    /// @retval  GENERAL_ERROR   Error occurred
    /// @retval  TIMEOUT         Wait timed out, no new data.

    virtual StdReturnType WaitForNewData(const uint32_t timeInMs) = 0;
};

} // namespace exm

#endif // ICHANNEL_HPP_INCLUDED
