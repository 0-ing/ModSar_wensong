//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file      IpcClient.hpp
/// @brief     IPC Client Header
/// @copyright Robert Bosch GmbH  2018
/// @author    Christopher Schwager

#ifndef UTILS_IPCCLIENT_HPP_INCLUDED
#define UTILS_IPCCLIENT_HPP_INCLUDED

#include "utils/FileDesc.hpp"
#include "utils/StdReturnType.hpp"
#include <stdint.h>

namespace exm
{
namespace utils
{
/// @class    IpcClient
/// @brief    IPC Client class based on pipes
class IpcClient
{
public:
    /// @brief Constructor
    IpcClient();

    /// @brief Constructor
    /// @param[in]   fd      File descriptor of the write end of a pipe
    IpcClient(const FileDesc fd);

    /// @brief Destructor
    ~IpcClient();

    /// @brief copy constructor not needed
    IpcClient(const IpcClient&) = delete;

    /// @brief Copy assignment operator 
    IpcClient& operator=(const IpcClient& other);

    /// @brief Write data to the pipe
    /// If noOfBytesToWrite exceeds PIPE_BUF an error is returned.
    /// @param[in]   buffer              Data to be transferred
    /// @param[in]   noOfBytesToWrite    Number of bytes to write
    /// @return  StdReturnType
    /// @retval  OK              OK
    /// @retval  GENERAL_ERROR   Error occurred
    StdReturnType Write(const uint8_t buffer[], const uint32_t noOfBytesToWrite) const;

    /// @brief Setter for file descriptor
    /// Also sets isSet to true.
    /// @param fdWrite Valid, initialized file descriptor
    void setFdWrite(const FileDesc fdWrite);

private:
    /// @brief   File descriptor of the write end of a pipe. */
    FileDesc fd_write;
    /// @brief   Indicates if fd_write has been set. */
    bool isSet;
};

} /* namespace utils */
} /* namespace exm */

#endif
