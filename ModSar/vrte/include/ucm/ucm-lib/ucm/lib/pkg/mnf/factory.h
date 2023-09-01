//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/pkg/mnf/factory.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY__UCM_LIB_PKG_MNF__FACTORY_H_
#define UCM_AAP_LIBRARY__UCM_LIB_PKG_MNF__FACTORY_H_

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/pkg/mnf/types.h"
#include "ucm/lib/pkg/mnf/parser.h"
#include "ucm/lib/pkg/mnf/schema.h"

/// @defgroup bosch_vrte_ucm_lib_pkg_mnf__Factory
/// @ingroup bosch_vrte_ucm_lib_pkg_mnf
/// @{

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace pkg   {
namespace mnf   {

/// @brief Abstract class for manifest processing factory.
/// Any module that wants to provide a manifest parser and/or schema validator
/// must implement this API and register it with the manifest Service.
class Factory
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test__ucm_lib_pkg_mnf__Factory, CTor);
#endif

public:
    virtual ~Factory() = default;

    /// @brief Return a JSON parser for the specified manifest version.
    /// When creating a Parser the factory may chose to ignore or not the
    /// passed parameters.
    /// @param[in] maxv Manifest's major version
    /// @param[in] minv Manifest's minor version
    /// @return A unique pointer to a parser that implements Parser API.
    /// @throws std::runtime_error if no parser can be created.
    virtual std::unique_ptr<Parser>
    json_parser(unsigned long maxv,
                unsigned long minv) = 0;

    /// @brief Return a JSON schema validator for the specified manifest.
    /// When creating a Schema validator the factory may chose to ignore or not
    /// the passed parameters.
    /// @param[in] maxv Manifest's major version
    /// @param[in] minv Manifest's minor version
    /// @return A unique pointer to a validator that implements Schema API.
    /// @throws std::runtime_error if no validator can be created.
    virtual std::unique_ptr<Schema>
    json_schema(unsigned long maxv,
                unsigned long minv) = 0;


    /// @brief Check the factory if it can create validator.
    /// The implemented Factory should override this method in order to provide
    /// information if it is able to create a schema validator for the specified
    /// manifest major and minor versions.
    /// @param[in] maxv Manifest's major version
    /// @param[in] minv Manifest's minor version
    /// @retun true if the manifest version is supported, false otherwise
    virtual bool
    is_schema_supported(unsigned long maxv,
                        unsigned long minv) noexcept = 0;

    /// @brief Check the factory if it can create parser.
    /// The implemented Factory should override this method in order to provide
    /// information if it is able to create a parser for the specified manifest
    /// major and minor versions.
    /// @param[in] maxv Manifest's major version
    /// @param[in] minv Manifest's minor version
    /// @retun true if the manifest version is supported, false otherwise
    virtual bool
    is_parser_supported(unsigned long maxv,
                        unsigned long minv) noexcept = 0;

protected:
    explicit Factory() = default;

    Factory(      Factory&&) = default;
    Factory(const Factory &) = default;

    Factory& operator=(      Factory&&) = default;
    Factory& operator=(const Factory &) = default;
};

}    // namespace mnf
}    // namespace pkg
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif // UCM_AAP_LIBRARY__UCM_LIB_PKG_MNF__FACTORY_H_
