//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file      IpcChannel.hpp
/// @brief     IPC Channel Header
/// @copyright Robert Bosch GmbH  2018
/// @author    Christopher Schwager

#ifndef UTILS_IPCCHANNEL_HPP_INCLUDED
#define UTILS_IPCCHANNEL_HPP_INCLUDED

#include "utils/FileDesc.hpp"
#include "utils/IpcClient.hpp"
#include "utils/IpcServer.hpp"
#include <stdint.h>

namespace exm
{
namespace utils
{
/// @class    IpcChannel
/// @brief    IPC Channel class based on pipes
class IpcChannel
{
public:
    /// @brief Default Constructor
    IpcChannel();

    /// @brief Destructor
    ~IpcChannel();

    /// @brief copy constructor not needed
    IpcChannel(const IpcChannel&) = delete;

    /// @brief Copy assignment operator 
    IpcChannel& operator=(const IpcChannel& other);

    /// @brief Initialize IpcChannel class.
    /// @param[in]   fd_read             File descriptor of the read end of a pipe. Expected to be
    /// non-blocking.
    /// @param[in]   fd_write            File descriptor of the write end of a pipe
    /// @param[in]   setNonBlockingRead  Directs the class to set fd_read to non-blocking. If false,
    /// options are not adjusted.
    /// @return  StdReturnType
    /// @retval  OK              OK
    /// @retval  GENERAL_ERROR   Error occurred
    StdReturnType Init(FileDesc fd_read, FileDesc fd_write, bool setNonBlockingRead);

    /// @brief Write data to the pipe
    /// If noOfBytesToWrite exceeds PIPE_BUF an error is returned.
    /// @param[in]   buffer              Data to be transferred
    /// @param[in]   noOfBytesToWrite    Number of bytes to write
    /// @return  StdReturnType
    /// @retval  OK              OK
    /// @retval  GENERAL_ERROR   Error occurred
    StdReturnType Write(const uint8_t* const buffer, const uint32_t noOfBytesToWrite) const;

    /// @brief Read data from the pipe.
    /// Use WaitForNewData to check for new data beforehand.
    /// @param[out]  buffer              Storage to write the read bytes
    /// @param[out]  bytesRead           Number of bytes read from channel
    /// @param[in]   maxNoOfBytesToRead  Space in buffer
    /// @return  StdReturnType
    /// @retval  OK              OK
    /// @retval  GENERAL_ERROR   Error occurred
    StdReturnType Read(
        uint8_t* const buffer, uint32_t* const bytesRead, const uint32_t maxNoOfBytesToRead) const;

    /// @brief Waits until data to read becomes available.
    /// @param[in] timeInMs Time to wait in ms.
    /// @return  StdReturnType
    /// @retval  OK              OK
    /// @retval  GENERAL_ERROR   Error occurred
    /// @retval  TIMEOUT         Wait timed out, no new data.
    StdReturnType WaitForNewData(const uint32_t timeInMs);

private:
    /// @brief   Client to handle write operations.
    IpcClient client;
    /// @brief   Server to handle read operations.
    IpcServer server;
};

} /* namespace utils */
} /* namespace exm */

#endif
