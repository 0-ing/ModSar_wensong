//==============================================================================
// C O P Y R I G H T
//------------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//==============================================================================

/// @file         ucm/lib/swc/fileops.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       hbe1lud
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY_LIB_UCM_LIB_FILEOPS_H_
#define UCM_AAP_LIBRARY_LIB_UCM_LIB_FILEOPS_H_

#include <stdexcept>
#include <system_error>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/swc/frecord.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace swc   {

void move_files    (FRecord const& src, FRecord const& dst);
void remove_files  (FRecord const& arg);

/// @brief Create chrooted file record, but don't move files.
/// @pre Must be in non-re-entrant state
FRecord chroot(FRecord const&, std::string const&);

/// @brief Create derooted file record, but don't move files.
/// @pre Must be in non-re-entrant state
FRecord deroot(FRecord const&);


/// @brief Normalize path list
///
/// Transforms list of paths to a collection of disjoint root dirs
std::vector<std::string> normalize(
                    std::string              const& root,
                    std::vector<std::string> const& list);

std::vector<std::string> join_root(FRecord const&);
std::vector<std::string> join_root(FRecord const&, std::string const&);



}    // namespace swc
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY_LIB_UCM_LIB_FILEOPS_H_

