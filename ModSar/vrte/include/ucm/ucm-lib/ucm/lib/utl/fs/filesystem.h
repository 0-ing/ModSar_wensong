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

#include <ftw.h>
#include <sys/stat.h>

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
bool exist(std::string const& arg);

/// @brief Get part of path which exists on file system.
std::string existing_part(std::string path);

/// @brief Get first part of path which does not exist on file system.
std::string first_non_existing_part(std::string path);

/// @brief recursive mkdir (mkdir -p)
void mkdirp(std::string path, mode_t mode = S_IRWXU);

/// @brief recursive file removal (rm -rf)
void rmrf(std::string const& path);

/// @brief move file
/// @pre not re-entrant
void move(std::string const& src, std::string const& dst);


//=============================================================================
//
// details exposed for unit tests

namespace impl  {

bool         str_exist           (char const* arg);
char*        str_existing_part   (char* str, bool next);
std::string  existing_part_helper(std::string& path, bool next);

struct MoveByCopy
{
    std::string root   {};
    std::size_t offset {};

    static void move   (
        std::string const& src,
        std::string const& dst);

    static int  callback (
        const char*        filename,
        const struct stat* pstat,
        int                fileflags,
        struct FTW*        pftw);

    static MoveByCopy& instance ();
};


} // namespace impl

//=============================================================================

}    // namespace fs
}    // namespace utl
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif    // UCM_AAP_LIBRARY_LIB_UTL_FS_FILESYSTEM_H_
