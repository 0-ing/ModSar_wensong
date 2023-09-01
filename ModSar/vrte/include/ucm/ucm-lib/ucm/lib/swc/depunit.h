//==============================================================================
// C O P Y R I G H T
//------------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//==============================================================================

/// @file         ucm/lib/swc/depunit.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY_LIB_UCM_LIB_SWC__DEPUNIT_H_
#define UCM_AAP_LIBRARY_LIB_UCM_LIB_SWC__DEPUNIT_H_

#include <iostream>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/swc/version.h"


namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace swc   {

class DepUnit
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_ucm_lib_swc__DepUnit, CTor1);
    FRIEND_TEST(Test_ucm_lib_swc__DepUnit, CTor2);
    FRIEND_TEST(Test_ucm_lib_swc__DepUnit, CTor3);
    FRIEND_TEST(Test_ucm_lib_swc__DepUnit, CTor4);
    FRIEND_TEST(Test_ucm_lib_swc__DepUnit, CTor5);
#endif
public:

    explicit DepUnit() = default;

    explicit DepUnit(std::string&& name, Version&& version)
        noexcept(std::is_nothrow_move_constructible<std::string>::value &&
                 std::is_nothrow_move_constructible<Version>::value);

    explicit DepUnit(const std::string& name, const Version& version)
        noexcept(std::is_nothrow_copy_constructible<std::string>::value &&
                 std::is_nothrow_copy_constructible<Version>::value);

    explicit DepUnit(const std::string& name, const std::string& version)
        noexcept(std::is_nothrow_copy_constructible<std::string>::value &&
                 std::is_nothrow_constructible<
                         Version(const std::string&)>::value);

    explicit DepUnit(std::string&& name, std::string&& version)
        noexcept(std::is_nothrow_move_constructible<std::string>::value &&
                 std::is_nothrow_constructible<Version(std::string&&)>::value);

    DepUnit(DepUnit     &&) = default;
    DepUnit(DepUnit const&) = default;

    DepUnit& operator=(DepUnit     &&) = default;
    DepUnit& operator=(DepUnit const&) = default;

    ~DepUnit() = default;

    const auto& swname() const noexcept;
    const auto& version() const noexcept;
    const auto& version_str() const noexcept;

private:
    std::string swname_{};
    Version     version_{};
};

std::ostream& operator<<(std::ostream&, const DepUnit&);

inline const auto& DepUnit::swname() const noexcept
{
    return swname_;
}

inline const auto& DepUnit::version() const noexcept
{
    return version_;
}

inline const auto& DepUnit::version_str() const noexcept
{
    return version_.get_token();
}

}    // namespace swc
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY_LIB_UCM_LIB_SWC__DEPUNIT_H_

