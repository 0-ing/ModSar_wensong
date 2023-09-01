//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This ClockPair is property of Robert Bosch GmbH. Any unauthorized copy, use
// or distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @ClockPair    ucm/lib/utl/clock_pair.h
/// @brief
/// @copyright    Robert Bosch GmbH 2018
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY_LIB_UTL_CLOCK_PAIR_H_
#define UCM_AAP_LIBRARY_LIB_UTL_CLOCK_PAIR_H_

#include <chrono>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/mock/sequence.h"

namespace bosch {
namespace vrte {
namespace ucm {
namespace lib {
namespace utl {

template <typename T = std::chrono::high_resolution_clock>
class ClockPair
      : virtual protected ucm::mock::Sequence
{
#if defined(GOOGLE_TEST)
    friend struct Test_ucm_lib_utl_ClockPair;
#endif

public:
    // copy semantics
    ClockPair(const ClockPair&) noexcept = default;
    ClockPair& operator=(const ClockPair&) noexcept = default;

    // move semantic
    ClockPair(ClockPair&&) noexcept = default;
    ClockPair& operator=(ClockPair&&) noexcept = default;


    ClockPair<T>() = default;
    ~ClockPair<T>() = default;

    void start()
    {
        pop<void>();
    }

    void stop()
    {
        pop<void>();
    }

    auto duration()
    {
        return pop<T::time_point>();
    }

    long duration_s()
    {
        return pop<long>();
    }

    long duration_us()
    {
        return pop<long>();
    }

    long duration_ms()
    {
        return pop<long>();
    }

private:
    typename T::time_point t1_{};
    typename T::time_point t2_{};
};


}    // namespace utl
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif    // UCM_AAP_LIBRARY_LIB_UTL_CLOCK_PAIR_H_
