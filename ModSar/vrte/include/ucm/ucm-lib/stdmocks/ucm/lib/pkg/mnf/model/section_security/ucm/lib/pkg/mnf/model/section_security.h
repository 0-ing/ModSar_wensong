//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/pkg/mnf/section_security.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY__UCM_LIB_PKG_MNF__SECTION_SECURITY_H_
#define UCM_AAP_LIBRARY__UCM_LIB_PKG_MNF__SECTION_SECURITY_H_

#include <string>

#include "ucm/mock/sequence.h"

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

class SectionSecurity final
    : protected virtual mock::Sequence
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test__ucm_lib_pkg_mnf__SectionSecurity, CTor);
#endif
public:
    explicit SectionSecurity() = default;

    explicit SectionSecurity(std::string&&,
                             std::string&&,
                             std::size_t&&,
                             std::string&&,
                             std::string&&,
                             std::size_t&&,
                             std::string&&,
                             std::string&&,
                             std::string&&)
    {}

    SectionSecurity(      SectionSecurity&&) = default;
    SectionSecurity(const SectionSecurity &) = default;

    SectionSecurity& operator=(      SectionSecurity&&) = default;
    SectionSecurity& operator=(const SectionSecurity &) = default;

    ~SectionSecurity() = default;

    const auto& signature_size() const noexcept;
    const auto& hash_algorithm() const noexcept;
    const auto& security_config() const noexcept;
    const auto& signature_value() const noexcept;
    const auto& sec_operation_type() const noexcept;
    const auto& crypto_object_size() const noexcept;
    const auto& crypto_object_type() const noexcept;
    const auto& signature_algorithm() const noexcept;
    const auto& crypto_object_reference() const noexcept;

private:
    std::string hash_algorithm_{};
    std::string crypto_object_reference_{};
    std::size_t crypto_object_size_{};
    std::string crypto_object_type_{};
    std::string sec_operation_type_{};
    std::size_t security_config_{};
    std::string signature_algorithm_{};
    std::string signature_size_{};
    std::string signature_value_{};
};

inline const auto& SectionSecurity::signature_size() const noexcept
{
    return pop<std::string const&>();
}

inline const auto& SectionSecurity::hash_algorithm() const noexcept
{
    return pop<std::string const&>();
}

inline const auto& SectionSecurity::security_config() const noexcept
{
    return pop<std::size_t const&>();
}

inline const auto& SectionSecurity::signature_value() const noexcept
{
    return pop<std::string const&>();
}

inline const auto& SectionSecurity::sec_operation_type() const noexcept
{
    return pop<std::string const&>();
}

inline const auto& SectionSecurity::crypto_object_size() const noexcept
{
    return pop<std::size_t const&>();
}

inline const auto& SectionSecurity::crypto_object_type() const noexcept
{
    return pop<std::string const&>();
}

inline const auto& SectionSecurity::signature_algorithm() const noexcept
{
    return pop<std::string const&>();
}

inline const auto& SectionSecurity::crypto_object_reference() const noexcept
{
    return pop<std::string const&>();
}

}    // namespace mnf
}    // namespace pkg
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY__UCM_LIB_PKG_MNF__SECTION_SECURITY_H_
