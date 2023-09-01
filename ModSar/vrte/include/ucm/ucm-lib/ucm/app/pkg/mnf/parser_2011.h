//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/app/pkg/mnf/parser_2011.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks
/// @ingroup      bosch_vrte_ucm_app_pkg_mnf

#ifndef UCM_AAP_LIBRARY__UCM_APP_PKG_MNF__PARSER_2011_H_
#define UCM_AAP_LIBRARY__UCM_APP_PKG_MNF__PARSER_2011_H_

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/pkg/mnf/parser.h"

/// @addtogroup bosch_vrte_ucm_app_pkg_mnf
/// @{
	
namespace bosch {
namespace vrte  {
namespace ucm   {
namespace app   {
namespace pkg   {
namespace mnf   {

/// @class Parser2011
/// @ingroup bosch_vrte_ucm_app_pkg_mnf
/// @brief Implementation of manifest parser for 20-11 format.

class Parser2011 : public lib::pkg::mnf::Parser
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test__ucm_app_pkg_mnf__Parser2011, TEST__CTor);
    FRIEND_TEST(Test__ucm_app_pkg_mnf__Parser2011, TEST__parse_buff_impl);
    FRIEND_TEST(Test__ucm_app_pkg_mnf__Parser2011, TEST__parse_file_impl);
#endif

public:
    explicit Parser2011() = default;

    Parser2011(      Parser2011&&) = default;
    Parser2011(const Parser2011 &) = default;

    Parser2011& operator=(      Parser2011&&) = default;
    Parser2011& operator=(const Parser2011 &) = default;

    virtual ~Parser2011() = default;

protected:
    /// @brief Parse a manifest buffer and return result from the parsing.
    /// @param[in] butt A buffer containing the manifest
    /// @returns Result(Manifest) on success
    /// @returns Result(Error) on failure
    /// @throws May throw any kind of std::exception
    virtual lib::pkg::mnf::Result
    parse_buff_impl(const std::string&) override;

    /// @brief Parse a manifest file and return result from the parsing.
    /// @param[in] file A file containing the manifest
    /// @returns Result(Manifest) on success
    /// @returns Result(Error) on failure
    /// @throws May throw any kind of std::exception
    virtual lib::pkg::mnf::Result
    parse_file_impl(const std::string&) override;
};

}    // namespace mnf
}    // namespace pkg
}    // namespace app
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif // UCM_AAP_LIBRARY__UCM_APP_PKG_MNF__PARSER_2011_H_
