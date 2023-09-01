//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file      Channel.hpp
/// @brief     Channel classes allow sending and receiving of function group messages using pipes
/// @copyright Robert Bosch GmbH  2018
/// @author    baetz

#ifndef EXM_CHANNEL_HPP_INCLUDED
#define EXM_CHANNEL_HPP_INCLUDED

#include "FileDesc.hpp"
#include "IChannel.hpp"
#include "IChannelMessage.hpp"
#include "IpcChannel.hpp"

namespace exm
{

/// @brief Channel classes allow sending and receiving of function group messages using pipes.
/// Communication is one on one, i.e. there is one sender and on receiver of messages.
/// After initialization with file descriptors, the class can send and receive variable sized
/// messages. These messages are sent in one piece, but on reception, first the header is read an
/// checked before reading out the payload. The implementation is agnostic to the actual message and
/// header format, relying only on the IChannelMessage interface.
class Channel : public IChannel
{
public:
    /// @brief Default constructor.
    Channel();

    /// @brief Destructor.
    virtual ~Channel();

    /// @brief copy constructor not needed
    Channel(const Channel&) = delete;

    /// @brief copy assignment operator not needed
    Channel& operator=(const Channel&) = delete;

    /// @brief Initializes the communication channel.
    /// Automatically sets the read descriptor to non-blocking mode.
    /// @param fd_read   File descriptor to read from.
    /// @param fd_write  File descriptor to write to.
    /// @return StdReturnType
    /// @retval  OK on success
    /// @retval  GENERAL_ERROR if fd_read or fd_write is invalid or options can't be set.
    ///
    virtual StdReturnType Init(const FileDesc fd_read, const FileDesc fd_write);
    virtual StdReturnType Init(const FileDesc fd_read, const FileDesc fd_write, const bool isBlocking);

    /// @brief Send a message over the channel
    /// @param message   The message to be sent
    /// @return  StdReturnType
    /// @retval  OK if the message was successfully sent
    /// @retval  INVALID_ARGUMENTS if nullptr is passed
    /// @retval  GENERAL_ERROR   if an error in the message format was detected, or if sending
    /// failed.
    virtual StdReturnType SendMessage(IChannelMessage* const message);

    /// @brief Reads the next complete message from the pipe.
    /// @param message   A pointer to a message, which contains the buffer for receiving the
    /// message.
    /// @return  StdReturnType
    /// @retval  OK if the next message was successfully received
    /// @retval  INVALID_ARGUMENTS if nullptr is passed
    /// @retval  GENERAL_ERROR   if an error in the message format was detected, or if receiving
    /// failed.
    virtual StdReturnType ReadNextMessage(IChannelMessage* const message);

    /// @brief Waits until data to read becomes available.
    /// @param[in] timeInMs Time to wait in ms.
    /// @return  StdReturnType
    /// @retval  OK              OK
    /// @retval  GENERAL_ERROR   Error occurred
    /// @retval  TIMEOUT         Wait timed out, no new data.
    virtual StdReturnType WaitForNewData(const uint32_t timeInMs);

private:
    utils::IpcChannel ipcChannel; ///< The actual IPC channel implementation taken from utilities.
};

} // namespace exm

#endif // EXM_CHANNEL_HPP_INCLUDED
