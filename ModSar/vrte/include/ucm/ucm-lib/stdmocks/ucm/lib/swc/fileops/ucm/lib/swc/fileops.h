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

#include "ucm/mock/sequence.h"
#include "ucm/lib/swc/frecord.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace swc   {

inline void move_files    (FRecord const& src, FRecord const& dst) {ucm::mock::Sequence::pop<void>();}
inline void remove_files  (FRecord const& arg)  {ucm::mock::Sequence::pop<void>();}

/// @brief Create chrooted file record, but don't move files.
/// @pre Must be in non-re-entrant state
inline FRecord chroot(FRecord const&, std::string const&) {return ucm::mock::Sequence::pop<FRecord>();}

/// @brief Create derooted file record, but don't move files.
/// @pre Must be in non-re-entrant state
inline FRecord deroot(FRecord const&) {return ucm::mock::Sequence::pop<FRecord>();}

/// @brief Get unit directory
inline std::string unit_dir (FRecord const&)  {return ucm::mock::Sequence::pop<std::string>();}

/// @brief Get backup root directory
inline std::string backup_root (FRecord const&)  {return ucm::mock::Sequence::pop<std::string>();}

/// @brief Get temporary extraction root directory
inline std::string extract_root (FRecord const&)  {return ucm::mock::Sequence::pop<std::string>();}

/// @brief Normalize path list
///
/// Transforms list of paths to a collection of disjoint root dirs
inline std::vector<std::string> normalize(
                    std::string              const& root,
                    std::vector<std::string> const& list)  {return ucm::mock::Sequence::pop<std::vector<std::string>>();}

inline std::vector<std::string> join_root(FRecord const&)  {return ucm::mock::Sequence::pop<std::vector<std::string>>();}
inline std::vector<std::string> join_root(FRecord const&, std::string const&)  {return ucm::mock::Sequence::pop<std::vector<std::string>>();}



}    // namespace swc
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY_LIB_UCM_LIB_FILEOPS_H_

