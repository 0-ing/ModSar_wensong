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

#include "ucm/mock/sequence.h"


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
    : protected virtual mock::Sequence
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test__ucm_lib_pkg_mnf__Model, TEST__CTor);
    FRIEND_TEST(Test__ucm_lib_pkg_mnf__Model, TEST__translate_action);
#endif

    static UpdateAction translate_action(const std::string&)
    {
        return pop<UpdateAction>();
    }

public:
    explicit SectionUpdate() = default;

    explicit SectionUpdate(std::string&&,
                           swc::DepUnit&&,
                           std::size_t&&,
                           std::string&&,
                           std::size_t&&,
                           std::uint64_t&&,
                           Configuration&&,
                           Configuration&&,
                           Configuration&&,
                           Configuration&&,
                           Configuration&&,
                           Configuration&&,
                           bool&&,
                           bool&&,
                           std::size_t&&,
                           std::vector<ArtifactObject>&&,
                           std::vector<DependencyObject>&&)
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
};

inline const auto& SectionUpdate::action() const noexcept
{
    return pop<UpdateAction const&>();
}

inline const auto& SectionUpdate::swcunit() const noexcept
{
    return pop<swc::DepUnit const&>();
}

inline const auto& SectionUpdate::artifacts() const noexcept
{
    return pop<std::vector<ArtifactObject> const&>();
}

inline const auto& SectionUpdate::timestamp() const noexcept
{
    return pop<std::uint64_t const&>();
}

inline const auto& SectionUpdate::packager_id() const noexcept
{
    return pop<std::size_t const&>();
}

inline const auto& SectionUpdate::dependencies() const noexcept
{
    return pop<std::vector<DependencyObject> const&>();
}

inline const auto& SectionUpdate::conf_failure() const noexcept
{
    return pop<Configuration const&>();
}

inline const auto& SectionUpdate::conf_rollback() const noexcept
{
    return pop<Configuration const&>();
}

inline const auto& SectionUpdate::artifacts_size() const noexcept
{
    return pop<std::size_t const&>();
}

inline const auto& SectionUpdate::conf_preinstall() const noexcept
{
    return pop<Configuration const&>();
}

inline const auto& SectionUpdate::conf_postinstall() const noexcept
{
    return pop<Configuration const&>();
}

inline const auto& SectionUpdate::conf_preactivate() const noexcept
{
    return pop<Configuration const&>();
}

inline const auto& SectionUpdate::conf_verification() const noexcept
{
    return pop<Configuration const&>();
}

inline const auto SectionUpdate::deprules() const noexcept
{
    return pop<std::vector<swc::DepRule>>();
}

inline const auto& SectionUpdate::artifacts_number() const noexcept
{
    return pop<std::size_t const&>();
}

}    // namespace mnf
}    // namespace pkg
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY__UCM_LIB_PKG_MNF__SECTION_UPDATE_H_
