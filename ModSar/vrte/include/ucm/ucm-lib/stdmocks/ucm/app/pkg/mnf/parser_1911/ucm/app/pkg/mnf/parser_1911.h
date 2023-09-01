//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         /tests/VRTE_UT/stdmocks/ucm/app/pkg/mnf/parser_1911.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks
/// @ingroup      bosch_vrte_ucm_app_pkg_mnf

#ifndef UCM_AAP_LIBRARY__UCM_APP_PKG_MNF__PARSER_1911_H_
#define UCM_AAP_LIBRARY__UCM_APP_PKG_MNF__PARSER_1911_H_


#include "ucm/lib/pkg/mnf/parser.h"

#include "ucm/mock/sequence.h"

/// @addtogroup bosch_vrte_ucm_app_pkg_mnf
/// @{

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace app   {
namespace pkg   {
namespace mnf   {

/// @class Parser1911
/// @ingroup bosch_vrte_ucm_app_pkg_mnf
/// @brief Implementation of manifest parser for 19-11 format.

class Parser1911
        : public lib::pkg::mnf::Parser
        , protected virtual mock::Sequence
{

public:
    explicit Parser1911() = default;

    Parser1911(      Parser1911&&) = default;
    Parser1911(const Parser1911 &) = default;

    Parser1911& operator=(      Parser1911&&) = default;
    Parser1911& operator=(const Parser1911 &) = default;

    virtual ~Parser1911() = default;

protected:
    /// @brief Parse a manifest buffer and return result from the parsing.
    /// @param[in] butt A buffer containing the manifest
    /// @returns Result(Manifest) on success
    /// @returns Result(Error) on failure
    /// @throws May throw any kind of std::exception
    virtual lib::pkg::mnf::Result
    parse_buff_impl(const std::string&)
    {
        return pop<lib::pkg::mnf::Result>();
    }

    /// @brief Parse a manifest file and return result from the parsing.
    /// @param[in] file A file containing the manifest
    /// @returns Result(Manifest) on success
    /// @returns Result(Error) on failure
    /// @throws May throw any kind of std::exception
    virtual lib::pkg::mnf::Result
    parse_file_impl(const std::string&)
    {
        return pop<lib::pkg::mnf::Result>();
    }
};

}    // namespace mnf
}    // namespace pkg
}    // namespace app
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif // UCM_AAP_LIBRARY__UCM_APP_PKG_MNF__PARSER_1911_H_
