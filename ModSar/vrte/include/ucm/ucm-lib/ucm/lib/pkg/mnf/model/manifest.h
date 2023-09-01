//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/pkg/mnf/manifest.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY__UCM_LIB_PKG_MNF__MANIFEST_H_
#define UCM_AAP_LIBRARY__UCM_LIB_PKG_MNF__MANIFEST_H_

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/pkg/mnf/model/section_update.h"
#include "ucm/lib/pkg/mnf/model/section_general.h"
#include "ucm/lib/pkg/mnf/model/section_security.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace pkg   {
namespace mnf   {

class Manifest final
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test__ucm_lib_pkg_mnf__Manifest, CTor);
#endif
public:
    explicit Manifest() = default;

    explicit Manifest(SectionUpdate&& update,
                      SectionGeneral&& general,
                      SectionSecurity&& security)
            : valid_{true}
            , update_(std::move(update))
            , general_(std::move(general))
            , security_(std::move(security))
    {}

    Manifest(      Manifest&&) = default;
    Manifest(const Manifest &) = default;

    Manifest& operator=(      Manifest&&) = default;
    Manifest& operator=(const Manifest &) = default;

    ~Manifest() = default;

    // accessors
    const auto& valid() const noexcept;
    const auto& update() const noexcept;
    const auto& general() const noexcept;
    const auto& security() const noexcept;

    // shortcut accessors
    const auto& action() const noexcept;
    const auto& swcunit() const noexcept;
    const auto& artifacts_number() const noexcept;

private:
    bool            valid_{false};
    SectionUpdate   update_{};
    SectionGeneral  general_{};
    SectionSecurity security_{};
};

inline const auto& Manifest::valid() const noexcept
{
    return valid_;
}

inline const auto& Manifest::update() const noexcept
{
    return update_;
}

inline const auto& Manifest::general() const noexcept
{
    return general_;
}

inline const auto& Manifest::security() const noexcept
{
    return security_;
}

inline const auto& Manifest::action() const noexcept
{
    return update().action();
}

inline const auto& Manifest::swcunit() const noexcept
{
    return update().swcunit();
}

inline const auto& Manifest::artifacts_number() const noexcept
{
    return update().artifacts_number();
}

}    // namespace mnf
}    // namespace pkg
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY__UCM_LIB_PKG_MNF__MANIFEST_H_
