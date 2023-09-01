//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/pkg/mnf/service.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks


#ifndef UCM_AAP_LIBRARY__UCM_LIB_PKG_MNF__SERVICE_H_
#define UCM_AAP_LIBRARY__UCM_LIB_PKG_MNF__SERVICE_H_

#include <array>
#include <memory>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/app/service.h"

#include "ucm/lib/pkg/mnf/factory.h"

/// @defgroup bosch_vrte_ucm_lib_pkg_mnf__Service
/// @ingroup bosch_vrte_ucm_lib_pkg_mnf
/// @{


namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace pkg   {
namespace mnf   {


/// @brief Manifest parsing service class.
/// The class itself acts as a facade to the manifest parsing facilities and
/// the rest of the UCM implementation should use its parse_buff and
/// parse_file methods for manifest parsing.
class Service final : public app::Service
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test__ucm_lib_pkg_mnf__Service, TEST__CTor);
    FRIEND_TEST(Test__ucm_lib_pkg_mnf__Service, TEST__is_buff_json);
    FRIEND_TEST(Test__ucm_lib_pkg_mnf__Service, TEST__is_file_json);
    FRIEND_TEST(Test__ucm_lib_pkg_mnf__Service, TEST__parse_buff);
    FRIEND_TEST(Test__ucm_lib_pkg_mnf__Service, TEST__parse_file);
    FRIEND_TEST(Test__ucm_lib_pkg_mnf__Service, SetupNolock);
    FRIEND_TEST(Test__ucm_lib_pkg_mnf__Service, StartoffNolock);
    FRIEND_TEST(Test__ucm_lib_pkg_mnf__Service, ShutdownNolock);
#endif

    using Base = app::Service;

private:
    /// @brief Try to determine if the buff content is a valid JSON manifest.
    /// @param[in] buff A string object containing the manifest
    /// @param[out] maxv The major version of the manifest
    /// @param[out] minv The minor version of the manifest
    /// @returns true if the passed string is valid JSON manifest
    /// @returns false if the passed string is NOT a valid JSON manifest
    static bool is_buff_json(const std::string& buff,
                             unsigned long& maxv, unsigned long& minv) noexcept;

    /// @brief Try to determine if the file content is a valid JSON manifest.
    /// @param[in] file A file containing the manifest
    /// @param[out] maxv The major version of the manifest
    /// @param[out] minv The minor version of the manifest
    /// @returns true if the passed file is valid JSON manifest
    /// @returns false if the passed file is NOT a valid JSON manifest
    /// @note The method internally calls is_buff_json
    static bool is_file_json(const std::string& file,
                             unsigned long& maxv, unsigned long& minv) noexcept;

public:
    explicit Service();

    Service(      Service&&) = delete;
    Service(const Service &) = delete;

    Service& operator=(      Service&&) = delete;
    Service& operator=(const Service &) = delete;

    ~Service() = default;

    /// @brief Parse a JSON string containing manifest.
    /// The method queries the factories_ array and tries to obtain a parser
    /// and schema validator for the version of the passed manifest. The
    /// manifest is first checked against the schema validator and then parsed.
    /// @param[in] buff A string object containing the manifest.
    /// @returns Result(Manifest) on success, see ucm/lib/pkg/mnf/types.h
    /// @returns Result(Error) on failure, see ucm/lib/pkg/mnf/types.h
    Result parse_buff(const std::string& buff) noexcept;

    /// @brief Parse a file containing JSON manifest.
    /// The method queries the factories_ array and tries to obtain a parser
    /// and schema validator for the version of the passed manifest. The
    /// manifest is first checked against the schema validator and then parsed.
    /// @param[in] file A file containing the manifest.
    /// @returns Result(Manifest) on success, see ucm/lib/pkg/mnf/types.h
    /// @returns Result(Error) on failure, see ucm/lib/pkg/mnf/types.h
    Result parse_file(const std::string& file) noexcept;

    /// @brief Register a manifest processing Factory.
    /// The method should be called only during the modules <b>setup</b> phase
    /// as there is no concurrent access protection in place.
    /// @param[in] factory A unique pointer to the base class of the Factory.
    void register_factory(std::unique_ptr<Factory>&& factory);

protected:
    bool setup_nolock()    noexcept override;
    bool startoff_nolock() noexcept override;
    bool shutdown_nolock() noexcept override;

private:
    /// @brief An array to hold the manifest processing factories.
    /// The array is limited to UCMS_MODULES_NUMBER as it is only logical
    /// one module to register only one Factory and deal internally how and
    /// what parsers and validators should be created.
    std::array<std::unique_ptr<Factory>, UCMS_MODULES_NUMBER> factories_{};

    /// @brief A helper method to select the appropriate Factory.
    /// Since different factories can create schema validators and JSON parsers,
    /// the method selects the factory that should return the schema validator.
    /// @param[in] maxv Manifest's major version
    /// @param[in] minv Manifest's minor version
    /// @return A reference to a factory in the factories_ array
    /// @throws std::runtime_error if no factory can be selected.
    Factory& select_schema_factory(unsigned long maxv, unsigned long minv);

    /// @brief A helper method to select the appropriate Factory.
    /// Since different factories can create schema validators and JSON parsers,
    /// the method selects the factory that should return the parser.
    /// @param[in] maxv Manifest's major version
    /// @param[in] minv Manifest's minor version
    /// @return A reference to a factory in the factories_ array
    /// @throws std::runtime_error if no factory can be selected.
    Factory& select_parser_factory(unsigned long maxv, unsigned long minv);
};

}    // namespace mnf
}    // namespace pkg
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif // UCM_AAP_LIBRARY__UCM_LIB_PKG_MNF__SERVICE_H_
