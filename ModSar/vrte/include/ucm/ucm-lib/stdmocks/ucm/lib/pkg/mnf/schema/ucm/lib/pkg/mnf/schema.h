//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/pkg/mnf/schema.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY__UCM_LIB_PKG_MNF__SCHEMA_H_
#define UCM_AAP_LIBRARY__UCM_LIB_PKG_MNF__SCHEMA_H_

#include <string>

#include "ucm/mock/sequence.h"

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/pkg/mnf/types.h"

/// @defgroup bosch_vrte_ucm_lib_pkg_mnf__Schema
/// @ingroup bosch_vrte_ucm_lib_pkg_mnf
/// @{


namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace pkg   {
namespace mnf   {

/// @brief API class for the manifest schema validator.
class Schema
    : protected virtual mock::Sequence
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test__ucm_lib_pkg_mnf__Schema, TEST__CTor);
    FRIEND_TEST(Test__ucm_lib_pkg_mnf__Schema, TEST__validate_json_buff);
    FRIEND_TEST(Test__ucm_lib_pkg_mnf__Schema, TEST__validate_json_file);
#endif

public:
    virtual ~Schema() = default;

    /// @brief Validate a JSON manifest stored in buff.
    /// @param[in] buff String object holding the manifest.
    /// @return true if the validation is successful, false otherwise
    bool validate_json_buff(const std::string& str) noexcept
    {
        return validate_json_buff_impl(str);
    }

    /// @brief Validate a JSON manifest stored in file.
    /// @param[in] file File containing the manifest.
    /// @return true if the validation is successful, false otherwise
    bool validate_json_file(const std::string& str) noexcept
    {
        return validate_json_file_impl(str);
    }

protected:
    explicit Schema() = default;

    Schema(      Schema&&) = default;
    Schema(const Schema &) = default;

    Schema& operator=(      Schema&&) = default;
    Schema& operator=(const Schema &) = default;

    /// @brief Prototype for JSON buffer validator.
    /// The derived class should implement this method in order to perform
    /// the real validation. The method is called from validate_json_buff.
    /// @param[in] buff String object holding the manifest.
    /// @return true if the validation is successful, false otherwise
    virtual bool validate_json_buff_impl(const std::string& buff) = 0;


    /// @brief Prototype for JSON file validator.
    /// The derived class should implement this method in order to perform
    /// the real validation. The method is called from validate_json_file.
    /// @param[in] buff String object holding the manifest.
    /// @return true if the validation is successful, false otherwise
    virtual bool validate_json_file_impl(const std::string& file) = 0;
};

}    // namespace mnf
}    // namespace pkg
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif // UCM_AAP_LIBRARY__UCM_LIB_PKG_MNF__SCHEMA_H_
