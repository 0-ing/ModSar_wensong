//==============================================================================
// C O P Y R I G H T
//------------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//==============================================================================

/// @file         ucm/lib/swc/deprule.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY_LIB_UCM_LIB_SWC__DEPRULE_H_
#define UCM_AAP_LIBRARY_LIB_UCM_LIB_SWC__DEPRULE_H_

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/swc/types.h"
#include "ucm/lib/swc/depunit.h"


namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace swc   {

class DepRule
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_ucm_lib_swc__DepRule, CTor1);
    FRIEND_TEST(Test_ucm_lib_swc__DepRule, CTor2);
    FRIEND_TEST(Test_ucm_lib_swc__DepRule, Compare_false);
    FRIEND_TEST(Test_ucm_lib_swc__DepRule, Compare_true);
    FRIEND_TEST(Test_ucm_lib_swc__DepRule, Relation);
    FRIEND_TEST(Test_ucm_lib_swc__DepRule, OperatorEQ);
    FRIEND_TEST(Test_ucm_lib_swc__DepRule, OperatorGT);
    FRIEND_TEST(Test_ucm_lib_swc__DepRule, OperatorLT);
    FRIEND_TEST(Test_ucm_lib_swc__DepRule, OperatorGE);
    FRIEND_TEST(Test_ucm_lib_swc__DepRule, OperatorLE);
    FRIEND_TEST(Test_ucm_lib_swc__DepRule, OperatorNE);
#endif
public:

    static const char *relation_cstr(const Relation& rel);

    explicit DepRule(const Relation&, DepUnit&&)
        noexcept(std::is_nothrow_move_constructible<DepUnit>::value);

    DepRule(DepRule     &&) = default;
    DepRule(DepRule const&) = default;

    DepRule& operator=(DepRule     &&) = default;
    DepRule& operator=(DepRule const&) = default;

    ~DepRule() = default;

    bool compare(const DepUnit&) const noexcept;

    const auto& rule() const noexcept;
    const auto& unit() const noexcept;
    const auto& swname() const noexcept;
    const auto& version() const noexcept;

private:
    Relation rule_;
    DepUnit  unit_;

    bool vcompare(const DepUnit&) const;
};

std::ostream& operator<<(std::ostream&, const DepRule&);

bool operator<(const DepRule& lhs, const DepRule& rhs);
bool operator>(const DepRule& lhs, const DepRule& rhs);
bool operator<=(const DepRule& lhs, const DepRule& rhs);
bool operator>=(const DepRule& lhs, const DepRule& rhs);
bool operator==(const DepRule& lhs, const DepRule& rhs);
bool operator!=(const DepRule& lhs, const DepRule& rhs);

inline const auto& DepRule::rule() const noexcept
{
    return rule_;
}

inline const auto& DepRule::unit() const noexcept
{
    return unit_;
}

inline const auto& DepRule::swname() const noexcept
{
    return unit_.swname();
}

inline const auto& DepRule::version() const noexcept
{
    return unit_.version();
}

}    // namespace swc
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY_LIB_UCM_LIB_SWC__DEPRULE_H_

