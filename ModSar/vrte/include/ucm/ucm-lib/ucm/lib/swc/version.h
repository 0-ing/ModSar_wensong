//==============================================================================
// C O P Y R I G H T
//------------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//==============================================================================

/// @file         ucm/lib/swc/version.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY_LIB_UCM_LIB_SWC__VERSION_H_
#define UCM_AAP_LIBRARY_LIB_UCM_LIB_SWC__VERSION_H_

#include <string>
#include <iostream>
#include <functional>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace swc   {

class Version final
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_ucm_lib_swc__Version, CTor1);
    FRIEND_TEST(Test_ucm_lib_swc__Version, CTor2);
    FRIEND_TEST(Test_ucm_lib_swc__Version, CTor3);
    FRIEND_TEST(Test_ucm_lib_swc__Version, CTor4);
    FRIEND_TEST(Test_ucm_lib_swc__Version, CTor5);
    FRIEND_TEST(Test_ucm_lib_swc__Version, CTor6);
    FRIEND_TEST(Test_ucm_lib_swc__Version, Validate);
    FRIEND_TEST(Test_ucm_lib_swc__Version, ToNumber);
    FRIEND_TEST(Test_ucm_lib_swc__Version, ToString);
    FRIEND_TEST(Test_ucm_lib_swc__Version, CompareEq);
    FRIEND_TEST(Test_ucm_lib_swc__Version, CompareGt);
    FRIEND_TEST(Test_ucm_lib_swc__Version, CompareLt);
    FRIEND_TEST(Test_ucm_lib_swc__Version, CompareGe);
    FRIEND_TEST(Test_ucm_lib_swc__Version, CompareLe);
    FRIEND_TEST(Test_ucm_lib_swc__Version, CompareNe);
    FRIEND_TEST(Test_ucm_lib_swc__Version, SetupTuple);
    FRIEND_TEST(Test_ucm_lib_swc__Version, OperatorEq);
    FRIEND_TEST(Test_ucm_lib_swc__Version, OperatorGt);
    FRIEND_TEST(Test_ucm_lib_swc__Version, OperatorLt);
    FRIEND_TEST(Test_ucm_lib_swc__Version, OperatorGe);
    FRIEND_TEST(Test_ucm_lib_swc__Version, OperatorLe);
    FRIEND_TEST(Test_ucm_lib_swc__Version, OperatorNe);
#endif
public:
    using numconv_fn_type =
            std::function<void(
                    const std::string&,
                    unsigned long& major, unsigned long& minor,
                    unsigned long& patch, unsigned long& tweak)>;

    using tokconv_fn_type =
            std::function<std::string(
                    unsigned long major, unsigned long minor,
                    unsigned long patch, unsigned long tweak)>;

    using compare_fn_type =
            std::function<bool(
                    unsigned long major1, unsigned long minor1,
                    unsigned long patch1, unsigned long tweak1,
                    unsigned long major2, unsigned long minor2,
                    unsigned long patch2, unsigned long tweak2)>;

    struct Tuple
    {
        compare_fn_type eq{};
        compare_fn_type gt{};
        compare_fn_type lt{};
        compare_fn_type ge{};
        compare_fn_type le{};
        compare_fn_type ne{};
        tokconv_fn_type to_string{};
        numconv_fn_type to_number{};
    };

    explicit Version();

    explicit Version(std::string&&);

    explicit Version(const std::string&);

    Version(Version     &&) = default;
    Version(Version const&) = default;

    Version& operator=(Version     &&) = default;
    Version& operator=(Version const&) = default;

    virtual ~Version() = default;

    const auto& get_tuple() const noexcept;
    const auto& get_token() const noexcept;
    const auto& get_major() const noexcept;
    const auto& get_minor() const noexcept;
    const auto& get_patch() const noexcept;
    const auto& get_tweak() const noexcept;

private:
    Tuple           tuple_{};
    std::string     token_{};
    unsigned long   major_{0};
    unsigned long   minor_{0};
    unsigned long   patch_{0};
    unsigned long   tweak_{0};

    static void setup_tuple(Tuple&) noexcept;

    static bool compare_eq(
            unsigned long major1, unsigned long minor1,
            unsigned long patch1, unsigned long tweak1,
            unsigned long major2, unsigned long minor2,
            unsigned long patch2, unsigned long tweak2) noexcept;

    static bool compare_gt(
            unsigned long major1, unsigned long minor1,
            unsigned long patch1, unsigned long tweak1,
            unsigned long major2, unsigned long minor2,
            unsigned long patch2, unsigned long tweak2) noexcept;

    static bool compare_lt(
            unsigned long major1, unsigned long minor1,
            unsigned long patch1, unsigned long tweak1,
            unsigned long major2, unsigned long minor2,
            unsigned long patch2, unsigned long tweak2) noexcept;

    static bool compare_ge(
            unsigned long major1, unsigned long minor1,
            unsigned long patch1, unsigned long tweak1,
            unsigned long major2, unsigned long minor2,
            unsigned long patch2, unsigned long tweak2) noexcept;

    static bool compare_le(
            unsigned long major1, unsigned long minor1,
            unsigned long patch1, unsigned long tweak1,
            unsigned long major2, unsigned long minor2,
            unsigned long patch2, unsigned long tweak2) noexcept;

    static bool compare_ne(
            unsigned long major1, unsigned long minor1,
            unsigned long patch1, unsigned long tweak1,
            unsigned long major2, unsigned long minor2,
            unsigned long patch2, unsigned long tweak2) noexcept;

    static void to_number(const std::string&,
                          unsigned long& major, unsigned long& minor,
                          unsigned long& patch, unsigned long& tweak);

    static std::string to_string(
            unsigned long major, unsigned long minor,
            unsigned long patch, unsigned long tweak);

    static void validate(const std::string&);
};

std::ostream& operator<<(std::ostream&, const Version&);

bool operator<(const Version& lhs, const Version& rhs);
bool operator>(const Version& lhs, const Version& rhs);
bool operator<=(const Version& lhs, const Version& rhs);
bool operator>=(const Version& lhs, const Version& rhs);
bool operator==(const Version& lhs, const Version& rhs);
bool operator!=(const Version& lhs, const Version& rhs);

inline const auto& Version::get_tuple() const noexcept
{
    return tuple_;
}

inline const auto& Version::get_token() const noexcept
{
    return token_;
}

inline const auto& Version::get_major() const noexcept
{
    return major_;
}

inline const auto& Version::get_minor() const noexcept
{
    return minor_;
}

inline const auto& Version::get_patch() const noexcept
{
    return patch_;
}

inline const auto& Version::get_tweak() const noexcept
{
    return tweak_;
}

}    // namespace swc
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY_LIB_UCM_LIB_SWC__VERSION_H_

