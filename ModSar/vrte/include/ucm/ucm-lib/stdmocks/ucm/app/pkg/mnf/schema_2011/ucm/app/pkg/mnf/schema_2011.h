//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         /tests/VRTE_UT/stdmocks/ucm/app/pkg/mnf/schema_2011.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks
/// @ingroup      bosch_vrte_ucm_app_pkg_mnf

#ifndef UCM_AAP_LIBRARY__UCM_APP_PKG_MNF__SCHEMA_2011_H_
#define UCM_AAP_LIBRARY__UCM_APP_PKG_MNF__SCHEMA_2011_H_


#include "ucm/lib/pkg/mnf/schema.h"

#include "ucm/mock/sequence.h"

/// @addtogroup bosch_vrte_ucm_app_pkg_mnf
/// @{

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace app   {
namespace pkg   {
namespace mnf   {

/// @class Schema2011
/// @ingroup bosch_vrte_ucm_app_pkg_mnf
/// @brief Manifest schema validator implementation for 20-11 format.

class Schema2011
        : public lib::pkg::mnf::Schema
          , protected virtual mock::Sequence
{

public:
    explicit Schema2011() = default;

    Schema2011(      Schema2011&&) = default;
    Schema2011(const Schema2011 &) = default;

    Schema2011& operator=(      Schema2011&&) = default;
    Schema2011& operator=(const Schema2011 &) = default;

    virtual ~Schema2011() = default;

protected:
    /// @brief Implementation of JSON buffer validator.
    /// @param[in] buff String object holding the manifest.
    /// @return true if the validation is successful, false otherwise
    virtual bool validate_json_buff_impl(const std::string&)
    {
        return pop<bool>();
    }

    /// @brief Implementation of JSON file validator.
    /// @param[in] buff String object holding the manifest.
    /// @return true if the validation is successful, false otherwise
    virtual bool validate_json_file_impl(const std::string&)
    {
        return pop<bool>();
    }
};

}    // namespace mnf
}    // namespace pkg
}    // namespace app
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif // UCM_AAP_LIBRARY__UCM_APP_PKG_MNF__SCHEMA_2011_H_
