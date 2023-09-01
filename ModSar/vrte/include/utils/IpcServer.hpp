//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file      IpcServer.hpp
/// @brief     IPC Server Header
/// @copyright Robert Bosch GmbH  2018
/// @author    Christopher Schwager

#ifndef UTILS_IPCSERVER_HPP_INCLUDED
#define UTILS_IPCSERVER_HPP_INCLUDED

#include "utils/FileDesc.hpp"
#include "utils/StdReturnType.hpp"
#include <stdint.h>
#include <unistd.h>

namespace exm
{
namespace utils
{
/// @class    IpcServer
/// @brief    IPC Server class based on pipes
class IpcServer
{
public:
    /// @brief Default Constructor
    IpcServer();

    /// @brief Constructor
    /// @param[in]   fd      File descriptor of the read end of a pipe.
    IpcServer(FileDesc fd);

    /// @brief Destructor
    ~IpcServer();

    /// @brief copy constructor not needed
    IpcServer(const IpcServer&) = delete;

    /// @brief Copy assignment operator 
    IpcServer& operator=(const IpcServer& other);

    /// @brief Read data from the pipe.
    /// Use WaitForNewData to check for new data beforehand.
    /// @param[out]  buffer              Storage to write the read bytes
    /// @param[out]  bytesRead           Number of bytes read from channel
    /// @param[in]   maxNoOfBytesToRead  Space in buffer
    /// @return  StdReturnType
    /// @retval  OK              OK
    /// @retval  GENERAL_ERROR   Error occurred
    StdReturnType Read(
        uint8_t buffer[], uint32_t* const bytesRead, const uint32_t maxNoOfBytesToRead) const;

    /// @brief Waits until data to read becomes available.
    /// @param[in] timeInMs Time to wait in ms.
    /// @return  StdReturnType
    /// @retval  OK              OK
    /// @retval  GENERAL_ERROR   Error occurred
    /// @retval  TIMEOUT         Wait timed out, no new data.
    StdReturnType WaitForNewData(const uint32_t timeInMs);

    /// @brief Set file descriptor value.
    /// Also sets isSet to true.
    /// @param fdRead A valid file descriptor with set options.
    void SetFdRead(FileDesc fdRead);

    /// @brief Return code definition for poll() POSIX call.
    static constexpr ssize_t pollError = -1;
    /// @brief Return code definition for poll() POSIX call.
    static constexpr ssize_t pollTimeout = 0;
    /// @brief Return code definition for read() POSIX call.
    static constexpr ssize_t ReadError = -1;

private:
    /// @brief   File descriptor of the read end of a pipe. */
    FileDesc fd_read;
    /// @brief   Indicates if fd_read has been set. */
    bool isSet;
};

} /* namespace utils */
} /* namespace exm */

#endif
