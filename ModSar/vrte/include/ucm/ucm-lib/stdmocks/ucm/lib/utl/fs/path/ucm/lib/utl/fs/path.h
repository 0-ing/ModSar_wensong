//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/utl/fs/path.h
/// @brief
/// @copyright    Robert Bosch GmbH 2018
/// @author       hbe1lud
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY_LIB_UTL_FS_PATH_H_
#define UCM_AAP_LIBRARY_LIB_UTL_FS_PATH_H_

#include <string>
#include <vector>
#include <stdexcept>
#include <initializer_list>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/mock/sequence.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace utl   {
namespace fs    {

namespace impl  {

inline bool gt(std::string const& , std::string const& , bool ) { return ucm::mock::Sequence::pop<bool>(); }

inline std::string join(std::string const&, std::string const&) { return ucm::mock::Sequence::pop<std::string>(); }
inline std::string join(std::initializer_list<std::string>) { return ucm::mock::Sequence::pop<std::string>(); }

} // namespace impl

inline std::string dirname(std::string) { return ucm::mock::Sequence::pop<std::string>(); }

template<typename... U>
std::string join(U&&...u)
{
    return ucm::mock::Sequence::pop<std::string>();
}

inline bool is_normal(std::string const&) { return ucm::mock::Sequence::pop<bool>(); }
inline bool is_relative(std::string const&) { return ucm::mock::Sequence::pop<bool>(); }
inline bool is_absolute(std::string const&) { return ucm::mock::Sequence::pop<bool>(); }

inline bool lt (std::string const&, std::string const&) { return ucm::mock::Sequence::pop<bool>(); } ///< 1nd strictly inside 2st
inline bool gt (std::string const&, std::string const&) { return ucm::mock::Sequence::pop<bool>(); } ///< 2nd strictly inside 1st
inline bool leq(std::string const&, std::string const&) { return ucm::mock::Sequence::pop<bool>(); } ///< 1nd same or inside 2st
inline bool geq(std::string const&, std::string const&) { return ucm::mock::Sequence::pop<bool>(); } ///< 2nd same or inside 1st

/// @brief Keep only maximal paths by means of path::geq comparison.
///
/// With "maximal" means a path including another (smaller) path.
/// A side effect is that paths also get sorted lexicographically. This is for 
/// efficiency.
inline std::vector<std::string> keep_max(std::vector<std::string>) { return ucm::mock::Sequence::pop<std::vector<std::string>>(); }

/// @brief Remove dots from path without consulting the file system.
/// I.e. not aware of links.
inline std::string normalize(std::string const&) { return ucm::mock::Sequence::pop<std::string>(); }

/// @brief Check if two files are disjoint
inline bool is_disjoint(std::string const&, std::string const&) { return ucm::mock::Sequence::pop<bool>(); }

/// @brief Check if two file lists are disjoint
inline bool is_disjoint(std::vector<std::string> const&, std::vector<std::string> const&) { return ucm::mock::Sequence::pop<bool>(); }


}    // namespace fs
}    // namespace utl
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif    // UCM_AAP_LIBRARY_LIB_UTL_FS_PATH_H_
