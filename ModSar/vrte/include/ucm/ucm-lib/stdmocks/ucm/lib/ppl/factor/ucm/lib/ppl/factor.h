//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/ppl/factor.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Vesselin Mladenov
/// @version
/// @remarks
///

#ifndef UCM_AAP_LIBRARY_LIB_PPL_FACTOR_H_
#define UCM_AAP_LIBRARY_LIB_PPL_FACTOR_H_

#include <vector>
#include <cstddef>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/ppl/tag.h"
#include "ucm/mock/sequence.h"

namespace bosch {
namespace vrte {
namespace ucm {
namespace lib {
namespace ppl {

class Factor final
    : virtual protected ucm::mock::Sequence
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_ucm_lib_ppl_Factor, CTor);
    FRIEND_TEST(Test_ucm_lib_ppl_Factor, Reset);
    FRIEND_TEST(Test_ucm_lib_ppl_Factor, Verdict);
    FRIEND_TEST(Test_ucm_lib_ppl_Factor, Countpp);
    FRIEND_TEST(Test_ucm_lib_ppl_Factor, Countmm);
    FRIEND_TEST(Test_ucm_lib_ppl_Factor, Increase);
    FRIEND_TEST(Test_ucm_lib_ppl_Factor, Decrease);
#endif

    constexpr static Tag::taskid_type load_per_task = 4;

    constexpr static auto load_per_task_get() noexcept
    {
        return load_per_task;
    }

    static const Tag::taskid_type& check_maxvalue(const Tag&)
    {
        return pop<Tag::taskid_type const&>();
    }

public:
    explicit Factor(const Tag& tag)
        : maxvalue_{check_maxvalue(tag)}
    {
        pop<void>();
    }

    // copy semantics
    Factor(const Factor& other) = default;
    Factor& operator=(const Factor&) = default;

    // move semantic
    Factor(Factor&&) noexcept = default;
    Factor& operator=(Factor&&) = default;

    ~Factor() = default;

    void reset() noexcept { pop<void>(); }

    Tag increase() { return pop<Tag>(); }

    void decrease() { pop<void>(); }

    void countpp(const Tag&) noexcept { pop<void>(); }

    void countmm(const Tag&) noexcept { pop<void>(); }

    bool verdict(const Tag&) noexcept { return pop<bool>(); }

private:
    Tag::taskid_type curvalue_{0};
    Tag::taskid_type maxvalue_{0};
    std::vector<Tag::taskid_type> tracker_{};
};

}    // namespace ppl
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif    // UCM_AAP_LIBRARY_LIB_PPL_FACTOR_H_
