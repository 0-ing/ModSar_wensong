//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/utl/fs/filesystem.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       hbe1lud
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY_LIB_UTL_FS_FILESYSTEM_H_
#define UCM_AAP_LIBRARY_LIB_UTL_FS_FILESYSTEM_H_


#include <string>

#include <sys/mock_stat.h>
#include "ucm/mock/sequence.h"

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace utl   {
namespace fs    {

/// @brief Check if path exists on file system.
inline bool exist(std::string const&) { return ucm::mock::Sequence::pop<bool>(); }

/// @brief Get part of path which exists on file system.
inline std::string existing_part(std::string) { return ucm::mock::Sequence::pop<std::string>(); }

/// @brief Get first part of path which does not exist on file system.
inline std::string first_non_existing_part(std::string) { return ucm::mock::Sequence::pop<std::string>(); }

/// @brief recursive mkdir (mkdir -p)
inline void mkdirp(std::string, mode_t = S_IRWXU) { return ucm::mock::Sequence::pop<void>(); }

/// @brief recursive file removal (rm -rf)
inline void rmrf(std::string const&) { return ucm::mock::Sequence::pop<void>(); }

/// @brief move file
/// @pre not re-entrant
inline void move(std::string const&, std::string const&) { return ucm::mock::Sequence::pop<void>(); }

}    // namespace fs
}    // namespace utl
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif    // UCM_AAP_LIBRARY_LIB_UTL_FS_FILESYSTEM_H_
