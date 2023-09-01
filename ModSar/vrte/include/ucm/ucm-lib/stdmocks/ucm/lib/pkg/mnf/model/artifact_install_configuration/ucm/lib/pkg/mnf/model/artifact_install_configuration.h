//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/pkg/mnf/artifact_install_configuration.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY__UCM_LIB_PKG_MNF__ARTIFACT_INSTALL_CONFIGURATION_H_
#define UCM_AAP_LIBRARY__UCM_LIB_PKG_MNF__ARTIFACT_INSTALL_CONFIGURATION_H_

#include <string>

#include "ucm/mock/sequence.h"

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif


namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace pkg   {
namespace mnf   {

class ArtifactInstallConfiguration final
    : protected virtual mock::Sequence
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test__ucm_lib_pkg_mnf__ArtifactSecurity, CTor);
#endif
public:
    explicit ArtifactInstallConfiguration(std::string&&)
    {}

    ArtifactInstallConfiguration(
            ArtifactInstallConfiguration&&) = default;
    ArtifactInstallConfiguration(
            const ArtifactInstallConfiguration &) = default;

    ArtifactInstallConfiguration& operator=(
            ArtifactInstallConfiguration&&) = default;
    ArtifactInstallConfiguration& operator=(
            const ArtifactInstallConfiguration &) = default;

    ~ArtifactInstallConfiguration() = default;

    const auto& installer_input_value() const noexcept;
};

inline const auto&
ArtifactInstallConfiguration::installer_input_value() const noexcept
{
    return pop<std::string const&>();
}


}    // namespace mnf
}    // namespace pkg
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY__UCM_LIB_PKG_MNF__ARTIFACT_INSTALL_CONFIGURATION_H_
