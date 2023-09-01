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

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace utl   {
namespace fs    {

namespace impl  {

bool gt(std::string const& u, std::string const& v, bool eq);

std::string join(std::string const&, std::string const&);
std::string join(std::initializer_list<std::string>);

} // namespace impl

std::string dirname(std::string);

template<typename... U>
std::string join(U&&...u)
{
    return impl::join(std::initializer_list<std::string>{
            static_cast<U&&>(u)...
    });
}

bool is_normal(std::string const&);
bool is_relative(std::string const&);
bool is_absolute(std::string const&);

bool lt (std::string const&, std::string const&); ///< 1nd strictly inside 2st
bool gt (std::string const&, std::string const&); ///< 2nd strictly inside 1st
bool leq(std::string const&, std::string const&); ///< 1nd same or inside 2st
bool geq(std::string const&, std::string const&); ///< 2nd same or inside 1st

/// @brief Keep only maximal paths by means of path::geq comparison.
///
/// With "maximal" means a path including another (smaller) path.
/// A side effect is that paths also get sorted lexicographically. This is for 
/// efficiency.
std::vector<std::string> keep_max(std::vector<std::string>);

/// @brief Remove dots from path without consulting the file system.
/// I.e. not aware of links.
std::string normalize(std::string const&);

/// @brief Check if two files are disjoint
bool is_disjoint(std::string const&, std::string const&);

/// @brief Check if two file lists are disjoint
bool is_disjoint(std::vector<std::string> const&, std::vector<std::string> const&);


}    // namespace fs
}    // namespace utl
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif    // UCM_AAP_LIBRARY_LIB_UTL_FS_PATH_H_
