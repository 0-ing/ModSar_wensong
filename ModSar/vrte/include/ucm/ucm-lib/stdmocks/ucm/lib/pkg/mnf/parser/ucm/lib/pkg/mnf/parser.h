//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/pkg/mnf/parser.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY__UCM_LIB_PKG_MNF__PARSER_H_
#define UCM_AAP_LIBRARY__UCM_LIB_PKG_MNF__PARSER_H_

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/pkg/mnf/types.h"

#include "ucm/mock/sequence.h"

/// @defgroup bosch_vrte_ucm_lib_pkg_mnf__Parser
/// @ingroup bosch_vrte_ucm_lib_pkg_mnf
/// @{

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace pkg   {
namespace mnf   {

/// @brief API class for the manifest parser
class Parser
    : protected virtual mock::Sequence
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test__ucm_lib_pkg_mnf__Parser, CTor);
    FRIEND_TEST(Test__ucm_lib_pkg_mnf__Parser, TEST__parse_buff);
    FRIEND_TEST(Test__ucm_lib_pkg_mnf__Parser, TEST__parse_file);
#endif

public:
    virtual ~Parser() = default;

    /// @brief Parse a manifest file and return result from the parsing.
    /// The method parses a manifest file, by passing it to the parse_file_impl
    /// virtual method and catching possible exceptions generated.
    /// @param file A file containing the manifest
    /// @returns Result(Manifest) on success
    /// @returns Result(Error) on failure
    Result parse_file(const std::string& str) noexcept
    {
        return parse_file_impl(str);
    }

    /// @brief Parse a buffer and return result from the parsing.
    /// The method parses a manifest buffer, by passing it to the
    /// parse_buff_impl virtual method and catching possible exceptions
    /// generated.
    /// @param[in] buff A buffer containing the manifest
    /// @returns Result(Manifest) on success
    /// @returns Result(Error) on failure
    Result parse_buff(const std::string& str) noexcept
    {
        return parse_buff_impl(str);
    }

protected:
    explicit Parser() = default;

    Parser(      Parser&&) = default;
    Parser(const Parser &) = default;

    Parser& operator=(      Parser&&) = default;
    Parser& operator=(const Parser &) = default;

    /// @brief Parse a manifest buffer and return result from the parsing.
    /// A pure virtual method defining API for parsing a manifest buffer.
    /// @param[in] butt A buffer containing the manifest
    /// @returns Result(Manifest) on success
    /// @returns Result(Error) on failure
    /// @throws May throw any kind of std::exception
    virtual Result parse_buff_impl(const std::string&) = 0;

    /// @brief Parse a manifest file and return result from the parsing.
    /// A pure virtual method defining API for parsing a manifest file.
    /// @param[in] file A file containing the manifest
    /// @returns Result(Manifest) on success
    /// @returns Result(Error) on failure
    /// @throws May throw any kind of std::exception
    virtual Result parse_file_impl(const std::string&) = 0;
};

}    // namespace mnf
}    // namespace pkg
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif // UCM_AAP_LIBRARY__UCM_LIB_PKG_MNF__PARSER_H_
