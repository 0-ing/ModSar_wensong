//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018-2022 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================
//
/// @file      libs/common/include/bosch/vrte/stm/stringutils.hpp
/// @brief     String utility functions.
/// @copyright Robert Bosch GmbH 2018-2022
/// @author    VRTE StM Team
//
//=============================================================================

#ifndef BOSCH_VRTE_STM_STRINGUTILS_HPP_INCLUDED
#define BOSCH_VRTE_STM_STRINGUTILS_HPP_INCLUDED

#include <string>
#include <vector>

namespace bosch
{
namespace vrte
{
namespace stm
{

/// @brief Split a string by delimiter.
///
/// @param f_str        Input string
/// @param f_delim      Delimiter
///
/// @return             Vector of strings
///
/// Example:
/// auto vec = SplitString("a;b;c", ';');  // ret == { "a", "b", "c" }
std::vector<std::string> SplitString(const std::string& f_str, const char f_delim);

/// @brief Join a vector a strings with a separator.
///
/// @param f_vec        Vector of strings
/// @param f_separator  Separator
///
/// @return             String
///
/// Example:
/// auto vec = JoinStrings({ "a", "b", "c" }, ';');  // ret == "a;b;c"
std::string JoinStrings(const std::vector<std::string>& f_vec, const char f_separator);

/// @brief Convert string to all lower characters.
///
/// @param f_str        Input string
///
/// @return             All lower case string
std::string ToLower(const std::string& f_str);

/// @brief Check if string is in list.
///
/// @param f_str        Input string
/// @param f_list       List of strings
///
/// @return             true if f_str is in f_list.
bool InList(const std::string& f_str, const std::vector<std::string>& f_list);

/// @brief Remove f_str from f_list.
///
/// @details When the list contains multiple elements matching f_str,
///          then all of them are being removed.
///
/// @param f_str        Input string
/// @param f_list       List of strings
///
/// @return             true if f_str was in f_list.
bool RemoveFromList(const std::string& f_str, std::vector<std::string>& f_list);

/// @brief Convert string to uint16
///
/// This function could be implemented with a template parameter
/// as output type to support multiple integer sizes, but
/// due to safety considerations we only explicitly implement
/// and test the types we need.
///
/// As in sscanf, a negative value will return 2^16-x.
/// (e.g. -1 will result 65535)
///
/// @param f_str        Input string
/// @param f_out        Output integer
///
/// @return             true if conversion was successfull.
bool ToUint16(const std::string& f_str, uint16_t& f_out);

/// @brief Convert string to uint32
///
/// This function could be implemented with a template parameter
/// as output type to support multiple integer sizes, but
/// due to safety considerations we only explicitly implement
/// and test the types we need.
///
/// As in sscanf, a negative value will return 2^32-x.
/// (e.g. -1 will result 4,294,967,295)
///
/// @param f_str        Input string
/// @param f_out        Output integer
///
/// @return             true if conversion was successfull.
bool ToUint32(const std::string& f_str, uint32_t& f_out);

}  // namespace stm
}  // namespace vrte
}  // namespace bosch

#endif  // BOSCH_VRTE_STM_STRINGUTILS_HPP_INCLUDED
