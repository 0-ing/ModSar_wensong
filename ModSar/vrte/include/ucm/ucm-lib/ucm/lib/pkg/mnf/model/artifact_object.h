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

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace pkg   {
namespace mnf   {

class ArtifactObject final
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test__ucm_lib_pkg_mnf__Model, TEST__CTor);
#endif
public:
    explicit ArtifactObject(std::size_t&& id,
                            std::string&& type,
                            std::string&& format,
                            std::string&& source,
                            std::string&& target,
                            std::string&& address,
                            std::string&& compression,
                            std::size_t&& package_size,
                            std::size_t&& deployed_size,
                            ArtifactSecurity&& security,
                            ArtifactInstallConfiguration install_configuration)
            : id_(std::move(id))
            , type_(std::move(type))
            , format_(std::move(format))
            , source_(std::move(source))
            , target_(std::move(target))
            , address_(std::move(address))
            , compression_(std::move(compression))
            , package_size_(std::move(package_size))
            , deployed_size_(std::move(deployed_size))
            , security_(std::move(security))
            , install_configuration_(std::move(install_configuration))
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

private:
    std::size_t id_;
    std::string type_;
    std::string format_;
    std::string source_;
    std::string target_;
    std::string address_;
    std::string compression_;
    std::size_t package_size_;
    std::size_t deployed_size_;
    ArtifactSecurity security_;
    ArtifactInstallConfiguration install_configuration_;
};

inline const auto& ArtifactObject::id() const noexcept
{
    return id_;
}

inline const auto& ArtifactObject::type() const noexcept
{
    return type_;
}

inline const auto& ArtifactObject::format() const noexcept
{
    return format_;
}

inline const auto& ArtifactObject::source() const noexcept
{
    return source_;
}

inline const auto& ArtifactObject::target() const noexcept
{
    return target_;
}

inline const auto& ArtifactObject::address() const noexcept

{
    return address_;
}

inline const auto& ArtifactObject::security() const noexcept
{
    return security_;
}

inline const auto& ArtifactObject::compression() const noexcept
{
    return compression_;
}

inline const auto& ArtifactObject::package_size() const noexcept
{
    return package_size_;
}

inline const auto& ArtifactObject::deployed_size() const noexcept
{
    return deployed_size_;
}

inline const auto& ArtifactObject::install_configuration() const noexcept
{
    return install_configuration_;
}

inline bool ArtifactObject::push_streaming() const noexcept
{
    return source_ == "kStreaming";
}

}    // namespace mnf
}    // namespace pkg
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY__UCM_LIB_PKG_MNF__ARTIFACT_OBJECT_H_
