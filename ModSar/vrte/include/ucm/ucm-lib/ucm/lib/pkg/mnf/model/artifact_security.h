//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/pkg/mnf/artifact_security.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY__UCM_LIB_PKG_MNF__ARTIFACT_SECURITY_H_
#define UCM_AAP_LIBRARY__UCM_LIB_PKG_MNF__ARTIFACT_SECURITY_H_

#include <string>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif


namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace pkg   {
namespace mnf   {

class ArtifactSecurity final
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test__ucm_lib_pkg_mnf__ArtifactSecurity, CTor);
#endif
public:
    explicit ArtifactSecurity(std::size_t certificate_size,
                              std::string checksum_type,
                              std::size_t cmac_id,
                              std::string secure_configuration,
                              std::string security_value)
        : certificate_size_(std::move(certificate_size))
        , checksum_type_(std::move(checksum_type))
        , cmac_id_(std::move(cmac_id))
        , secure_configuration_(std::move(secure_configuration))
        , security_value_(std::move(security_value))
    {}

    ArtifactSecurity(      ArtifactSecurity&&) = default;
    ArtifactSecurity(const ArtifactSecurity &) = default;

    ArtifactSecurity& operator=(      ArtifactSecurity&&) = default;
    ArtifactSecurity& operator=(const ArtifactSecurity &) = default;

    ~ArtifactSecurity() = default;

    const auto& cmac_id() const noexcept;
    const auto& checksum_type() const noexcept;
    const auto& security_value() const noexcept;
    const auto& certificate_size() const noexcept;
    const auto& secure_configuration() const noexcept;

private:
    std::size_t certificate_size_;
    std::string checksum_type_;
    std::size_t cmac_id_;
    std::string secure_configuration_;
    std::string security_value_;
};

inline const auto& ArtifactSecurity::cmac_id() const noexcept
{
    return cmac_id_;
}

inline const auto& ArtifactSecurity::checksum_type() const noexcept
{
    return checksum_type_;
}

inline const auto& ArtifactSecurity::security_value() const noexcept
{
    return security_value_;
}

inline const auto& ArtifactSecurity::certificate_size() const noexcept
{
    return certificate_size_;
}

inline const auto& ArtifactSecurity::secure_configuration() const noexcept
{
    return secure_configuration_;
}


}    // namespace mnf
}    // namespace pkg
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY__UCM_LIB_PKG_MNF__ARTIFACT_SECURITY_H_
