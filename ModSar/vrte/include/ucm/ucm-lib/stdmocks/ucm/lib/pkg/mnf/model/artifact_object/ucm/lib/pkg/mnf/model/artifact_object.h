//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/pkg/mnf/artifact_object.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY__UCM_LIB_PKG_MNF__ARTIFACT_OBJECT_H_
#define UCM_AAP_LIBRARY__UCM_LIB_PKG_MNF__ARTIFACT_OBJECT_H_

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/swc/version.h"
#include "ucm/lib/pkg/mnf/model/artifact_security.h"
#include "ucm/lib/pkg/mnf/model/artifact_install_configuration.h"

#include "ucm/mock/sequence.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace pkg   {
namespace mnf   {

class ArtifactObject final
    : protected virtual mock::Sequence
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test__ucm_lib_pkg_mnf__Model, TEST__CTor);
#endif
public:
    explicit ArtifactObject(std::size_t&&,
                            std::string&&,
                            std::string&&,
                            std::string&&,
                            std::string&&,
                            std::string&&,
                            std::string&&,
                            std::size_t&&,
                            std::size_t&&,
                            ArtifactSecurity&&,
                            ArtifactInstallConfiguration)
    {}

    ArtifactObject(      ArtifactObject&&) = default;
    ArtifactObject(const ArtifactObject &) = default;

    ArtifactObject& operator=(      ArtifactObject&&) = default;
    ArtifactObject& operator=(const ArtifactObject &) = default;

    ~ArtifactObject() = default;

    const auto& id() const noexcept;
    const auto& type() const noexcept;
    const auto& format() const noexcept;
    const auto& source() const noexcept;
    const auto& target() const noexcept;
    const auto& address() const noexcept;
    const auto& security() const noexcept;
    const auto& compression() const noexcept;
    const auto& package_size() const noexcept;
    const auto& deployed_size() const noexcept;
    const auto& install_configuration() const noexcept;

    bool push_streaming() const noexcept;
};

inline const auto& ArtifactObject::id() const noexcept
{
    return pop<std::size_t const&>();
}

inline const auto& ArtifactObject::type() const noexcept
{
    return pop<std::string const&>();
}

inline const auto& ArtifactObject::format() const noexcept
{
    return pop<std::string const&>();
}

inline const auto& ArtifactObject::source() const noexcept
{
    return pop<std::string const&>();
}

inline const auto& ArtifactObject::target() const noexcept
{
    return pop<std::string const&>();
}

inline const auto& ArtifactObject::address() const noexcept

{
    return pop<std::string const&>();
}

inline const auto& ArtifactObject::security() const noexcept
{
    return pop<ArtifactSecurity const&>();
}

inline const auto& ArtifactObject::compression() const noexcept
{
    return pop<std::string const&>();
}

inline const auto& ArtifactObject::package_size() const noexcept
{
    return pop<std::size_t const&>();
}

inline const auto& ArtifactObject::deployed_size() const noexcept
{
    return pop<std::size_t const&>();
}

inline const auto& ArtifactObject::install_configuration() const noexcept
{
    return pop<ArtifactInstallConfiguration const&>();
}

inline bool ArtifactObject::push_streaming() const noexcept
{
    return pop<bool>();
}

}    // namespace mnf
}    // namespace pkg
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY__UCM_LIB_PKG_MNF__ARTIFACT_OBJECT_H_
