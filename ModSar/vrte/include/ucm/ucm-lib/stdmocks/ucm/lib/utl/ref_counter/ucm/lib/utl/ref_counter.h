//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/utl/ref_counter.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY_LIB_UTL_REF_COUNTER_H_
#define UCM_AAP_LIBRARY_LIB_UTL_REF_COUNTER_H_

#include <atomic>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/mock/sequence.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace utl   {

class RefCounter final
      : virtual protected ucm::mock::Sequence
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_ucm_lib_utl_RefCounter, CTor);
    FRIEND_TEST(Test_ucm_lib_utl_RefCounter, Acquire);
#endif

public:

    struct Ref final
    {
#if defined(GOOGLE_TEST)
        FRIEND_TEST(Test_ucm_lib_utl_Ref, CTor);
        FRIEND_TEST(Test_ucm_lib_utl_RefCounter, CTor);
        FRIEND_TEST(Test_ucm_lib_utl_RefCounter, Acquire);
#endif
        explicit Ref(std::atomic_uint&) noexcept
        : refcnt_(counter)
        {
            pop<void>();
        }

        Ref(Ref     &&) = default;
        Ref(Ref const&) = delete;

        Ref& operator=(Ref     &&) = delete;
        Ref& operator=(Ref const&) = delete;

        ~Ref();

    private:
        std::atomic_uint& refcnt_;
    };

    explicit RefCounter() = default;

    RefCounter(RefCounter     &&) = delete;
    RefCounter(RefCounter const&) = delete;

    RefCounter& operator=(RefCounter     &&) = delete;
    RefCounter& operator=(RefCounter const&) = delete;

    ~RefCounter() = default;

    Ref acquire() noexcept {return pop<Ref>();}

private:
    std::atomic_uint counter_{0};
};


}    // namespace utl
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY_LIB_UTL_REF_COUNTER_H_
