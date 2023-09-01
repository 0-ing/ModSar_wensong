//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/pkg/mnf/section_update.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY__UCM_LIB_PKG_MNF__SECTION_UPDATE_H_
#define UCM_AAP_LIBRARY__UCM_LIB_PKG_MNF__SECTION_UPDATE_H_

#include <vector>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/swc/version.h"
#include "ucm/lib/swc/depunit.h"
#include "ucm/lib/pkg/mnf/model/configuration.h"
#include "ucm/lib/pkg/mnf/model/artifact_object.h"
#include "ucm/lib/pkg/mnf/model/dependency_object.h"


namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace pkg   {
namespace mnf   {

enum class UpdateAction : unsigned
{
    kUpdate,
    kRemove,
    kInstall,
    kInvalidValue
};

class SectionUpdate final
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test__ucm_lib_pkg_mnf__Model, TEST__CTor);
    FRIEND_TEST(Test__ucm_lib_pkg_mnf__Model, TEST__translate_action);
#endif

    static UpdateAction translate_action(const std::string& str);

public:
    explicit SectionUpdate() = default;

    explicit SectionUpdate(std::string&&    action,
                           swc::DepUnit&&   swcunit,
                           std::size_t&&    packager_id,
                           std::string&&    version_code,
                           std::size_t&&    artifact_number,
                           std::uint64_t&&  timestamp,
                           Configuration&&  conf_failure,
                           Configuration&&  conf_rollback,
                           Configuration&&  conf_preinstall,
                           Configuration&&  conf_postinstall,
                           Configuration&&  conf_preactivate,
                           Configuration&&  conf_verification,
                           bool&&           pre_activate_reboot,
                           bool&&           post_verification_reboot,
                           std::size_t&&    total_received_artifacts_size,
                           std::vector<ArtifactObject>&& artifacts,
                           std::vector<DependencyObject>&& dependencies)
            : action_(translate_action(action))
            , swcunit_(std::move(swcunit))
            , packager_id_(std::move(packager_id))
            , version_code_(std::move(version_code))
            , artifacts_number_(std::move(artifact_number))
            , timestamp_(std::move(timestamp))
            , conf_failure_(std::move(conf_failure))
            , conf_rollback_(std::move(conf_rollback))
            , conf_preinstall_(std::move(conf_preinstall))
            , conf_postinstall_(std::move(conf_postinstall))
            , conf_preactivate_(std::move(conf_preactivate))
            , conf_verification_(std::move(conf_verification))
            , pre_activate_reboot_(std::move(pre_activate_reboot))
            , post_verification_reboot_(std::move(post_verification_reboot))
            , total_received_artifacts_size_(
                    std::move(total_received_artifacts_size))
            , artifacts_(std::move(artifacts))
            , dependencies_(std::move(dependencies))
    {}

    SectionUpdate(      SectionUpdate&&) = default;
    SectionUpdate(const SectionUpdate &) = default;

    SectionUpdate& operator=(      SectionUpdate&&) = default;
    SectionUpdate& operator=(const SectionUpdate &) = default;

    ~SectionUpdate() = default;

    const auto& action() const noexcept;
    const auto& swcunit() const noexcept;
    const auto& artifacts() const noexcept;
    const auto& timestamp() const noexcept;
    const auto& packager_id() const noexcept;
    const auto& dependencies() const noexcept;
    const auto& conf_failure() const noexcept;
    const auto& conf_rollback() const noexcept;
    const auto& artifacts_size() const noexcept;
    const auto& conf_preinstall() const noexcept;
    const auto& conf_postinstall() const noexcept;
    const auto& conf_preactivate() const noexcept;
    const auto& conf_verification() const noexcept;
    const auto& artifacts_number() const noexcept;

    const auto deprules() const noexcept;

private:
    UpdateAction    action_{UpdateAction::kInvalidValue};
    swc::DepUnit    swcunit_{};
    std::size_t     packager_id_{};
    std::string     version_code_{};
    std::size_t     artifacts_number_{};
    std::uint64_t   timestamp_{};
    Configuration   conf_failure_{};
    Configuration   conf_rollback_{};
    Configuration   conf_preinstall_{};
    Configuration   conf_postinstall_{};
    Configuration   conf_preactivate_{};
    Configuration   conf_verification_{};
    bool            pre_activate_reboot_{};
    bool            post_verification_reboot_{};
    std::size_t     total_received_artifacts_size_{};
    std::vector<ArtifactObject>   artifacts_{};
    std::vector<DependencyObject> dependencies_{};
};

inline const auto& SectionUpdate::action() const noexcept
{
    return action_;
}

inline const auto& SectionUpdate::swcunit() const noexcept
{
    return swcunit_;
}

inline const auto& SectionUpdate::artifacts() const noexcept
{
    return artifacts_;
}

inline const auto& SectionUpdate::timestamp() const noexcept
{
    return timestamp_;
}

inline const auto& SectionUpdate::packager_id() const noexcept
{
    return packager_id_;
}

inline const auto& SectionUpdate::dependencies() const noexcept
{
    return dependencies_;
}

inline const auto& SectionUpdate::conf_failure() const noexcept
{
    return conf_failure_;
}

inline const auto& SectionUpdate::conf_rollback() const noexcept
{
    return conf_rollback_;
}

inline const auto& SectionUpdate::artifacts_size() const noexcept
{
    return total_received_artifacts_size_;
}

inline const auto& SectionUpdate::conf_preinstall() const noexcept
{
    return conf_preinstall_;
}

inline const auto& SectionUpdate::conf_postinstall() const noexcept
{
    return conf_postinstall_;
}

inline const auto& SectionUpdate::conf_preactivate() const noexcept
{
    return conf_preactivate_;
}

inline const auto& SectionUpdate::conf_verification() const noexcept
{
    return conf_verification_;
}

inline const auto SectionUpdate::deprules() const noexcept
{
    return DependencyObject::deprules(dependencies_);
}

inline const auto& SectionUpdate::artifacts_number() const noexcept
{
    return artifacts_number_;
}

}    // namespace mnf
}    // namespace pkg
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY__UCM_LIB_PKG_MNF__SECTION_UPDATE_H_
