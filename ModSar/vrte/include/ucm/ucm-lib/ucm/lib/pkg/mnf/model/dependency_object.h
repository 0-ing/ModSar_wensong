//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/pkg/mnf/dependency_object.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY__UCM_LIB_PKG_MNF__DEPENDENCY_OBJECT_H_
#define UCM_AAP_LIBRARY__UCM_LIB_PKG_MNF__DEPENDENCY_OBJECT_H_

#include <string>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/swc/deprule.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace pkg   {
namespace mnf   {

class DependencyObject final
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test__ucm_lib_pkg_mnf__ArtifactSecurity, CTor);
#endif
public:

    static std::vector<swc::DepRule> deprules(
            const std::vector<DependencyObject>&);

    explicit DependencyObject(std::string&&  type,
                              swc::DepRule&& deprule,
                              std::string&&  version_code)
        : type_(std::move(type))
        , deprule_(std::move(deprule))
        , version_code_(std::move(version_code))
    {}

    DependencyObject(      DependencyObject&&) = default;
    DependencyObject(const DependencyObject &) = default;

    DependencyObject& operator=(      DependencyObject&&) = default;
    DependencyObject& operator=(const DependencyObject &) = default;

    ~DependencyObject() = default;

    const auto& type() const noexcept;
    const auto& deprule() const noexcept;
    const auto& version_code() const noexcept;

private:
    std::string     type_;
    swc::DepRule    deprule_;
    std::string     version_code_;
};

inline const auto& DependencyObject::type() const noexcept
{
    return type_;
}

inline const auto& DependencyObject::deprule() const noexcept
{
    return deprule_;
}

inline const auto& DependencyObject::version_code() const noexcept
{
    return version_code_;
}

}    // namespace mnf
}    // namespace pkg
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY__UCM_LIB_PKG_MNF__DEPENDENCY_OBJECT_H_
