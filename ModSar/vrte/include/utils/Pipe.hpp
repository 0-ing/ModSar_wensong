//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file      Pipe.hpp
/// @brief     Pipe Header
/// @copyright Robert Bosch GmbH  2018
/// @author

#ifndef UTILS_PIPE_HPP_INCLUDED
#define UTILS_PIPE_HPP_INCLUDED

#include "utils/FileDesc.hpp"

namespace exm
{
namespace utils
{

/// @brief   Pipe structure to hold read and write descriptor info.
struct Pipe
{
    FileDesc read_fd;  ///< @brief Read descriptor of Pipe
    FileDesc write_fd; ///< @brief Write descriptor of Pipe
};

}; /* namespace utils */
}; /* namespace exm */

#endif
