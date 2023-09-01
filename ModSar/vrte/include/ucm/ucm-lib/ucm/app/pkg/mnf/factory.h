//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/app/pkg/mnf/factory.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks
/// @ingroup      bosch_vrte_ucm_app_pkg_mnf

#ifndef UCM_AAP_LIBRARY__UCM_APP_PKG_MNF__FACTORY_H_
#define UCM_AAP_LIBRARY__UCM_APP_PKG_MNF__FACTORY_H_

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/pkg/mnf/factory.h"

/// @addtogroup bosch_vrte_ucm_app_pkg_mnf
/// @{

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace app   {
namespace pkg   {
namespace mnf   {

/// @class Factory
/// @ingroup bosch_vrte_ucm_app_pkg_mnf
/// @brief Implementation of manifest processing factory.
/// The class implements lib::pkg::mnf::Factory API providing default manifest
/// Parser and Schema.

class Factory : public lib::pkg::mnf::Factory
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test__ucm_app_pkg_mnf__Factory, TEST__CTor);
    FRIEND_TEST(Test__ucm_app_pkg_mnf__Factory, TEST__json_schema);
    FRIEND_TEST(Test__ucm_app_pkg_mnf__Factory, TEST__json_parser);
    FRIEND_TEST(Test__ucm_app_pkg_mnf__Factory, TEST__is_schema_supported);
    FRIEND_TEST(Test__ucm_app_pkg_mnf__Factory, TEST__is_parser_supported);
#endif

public:
    explicit Factory() = default;

    Factory(      Factory&&) = default;
    Factory(const Factory &) = default;

    Factory& operator=(      Factory&&) = default;
    Factory& operator=(const Factory &) = default;

    virtual ~Factory() = default;

    /// @brief Return a JSON parser for the specified manifest version.
    /// @param[in] maxv Manifest's major version
    /// @param[in] minv Manifest's minor version
    /// @return A unique pointer to a parser that implements Parser API.
    /// @throws std::runtime_error if no parser can be created.
    virtual std::unique_ptr<lib::pkg::mnf::Parser>
    json_parser(unsigned long maxv, unsigned long minv) override;

    /// @brief Return a JSON schema validator for the specified manifest.
    /// @param[in] maxv Manifest's major version
    /// @param[in] minv Manifest's minor version
    /// @return A unique pointer to a validator that implements Schema API.
    /// @throws std::runtime_error if no validator can be created.
    virtual std::unique_ptr<lib::pkg::mnf::Schema>
    json_schema(unsigned long maxv, unsigned long minv) override;

    /// @brief Check the factory if it can create validator.
    /// @param[in] maxv Manifest's major version
    /// @param[in] minv Manifest's minor version
    /// @retun true if the manifest version is supported, false otherwise
    virtual bool
    is_schema_supported(unsigned long maxv,
                        unsigned long minv) noexcept override;

    /// @brief Check the factory if it can create parser.
    /// @param[in] maxv Manifest's major version
    /// @param[in] minv Manifest's minor version
    /// @retun true if the manifest version is supported, false otherwise
    virtual bool
    is_parser_supported(unsigned long maxv,
                        unsigned long minv) noexcept override;
};

}    // namespace mnf
}    // namespace pkg
}    // namespace app
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif // UCM_AAP_LIBRARY__UCM_APP_PKG_MNF__FACTORY_H_
