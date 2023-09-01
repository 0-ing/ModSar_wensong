//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/pkg/mnf/section_general.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY__UCM_LIB_PKG_MNF__SECTION_GENERAL_H_
#define UCM_AAP_LIBRARY__UCM_LIB_PKG_MNF__SECTION_GENERAL_H_

#include <string>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/swc/version.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace pkg   {
namespace mnf   {

class SectionGeneral final
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test__ucm_lib_pkg_mnf__SectionGeneral, CTor);
#endif
public:
    explicit SectionGeneral() = default;

    explicit SectionGeneral(std::string&& format,
                            swc::Version&& version,
                            swc::Version&& ucm_version_min,
                            swc::Version&& ucm_version_max)
            : mnf_format_(std::move(format))
            , mnf_version_(std::move(version))
            , ucm_version_min_(std::move(ucm_version_min))
            , ucm_version_max_(std::move(ucm_version_max))
    {}

    SectionGeneral(      SectionGeneral&&) = default;
    SectionGeneral(const SectionGeneral &) = default;

    SectionGeneral& operator=(      SectionGeneral&&) = default;
    SectionGeneral& operator=(const SectionGeneral &) = default;

    ~SectionGeneral() = default;

    const auto& format() const noexcept;
    const auto& version() const noexcept;
    const auto& ucm_version_min() const noexcept;
    const auto& ucm_version_max() const noexcept;

private:
    std::string  mnf_format_{};       // general.manifest_format
    swc::Version mnf_version_{};      // general.manifest_version
    swc::Version ucm_version_min_{};  // general.minimum_supported_ucm_version
    swc::Version ucm_version_max_{};  // general.maximum_supported_ucm_version
};

inline const auto& SectionGeneral::format() const noexcept
{
    return mnf_format_;
}

inline const auto& SectionGeneral::version() const noexcept
{
    return mnf_version_;
}

inline const auto& SectionGeneral::ucm_version_min() const noexcept
{
    return ucm_version_min_;
}

inline const auto& SectionGeneral::ucm_version_max() const noexcept
{
    return ucm_version_max_;
}

}    // namespace mnf
}    // namespace pkg
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY__UCM_LIB_PKG_MNF__SECTION_GENERAL_H_
