//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/utl/async_barrier.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY_LIB_UTL_AYSNC_BARRIER_H_
#define UCM_AAP_LIBRARY_LIB_UTL_AYSNC_BARRIER_H_

#include <mutex>
#include <condition_variable>
#include "ucm/mock/sequence.h"

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

namespace bosch {
namespace vrte {
namespace ucm {
namespace lib {
namespace utl {

class AsyncBarrier final
         : virtual protected ucm::mock::Sequence
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_AsyncBarrier, Constructor);
#endif

public:
    AsyncBarrier() = default;

    AsyncBarrier(bool) {}

    // copy semantics
    AsyncBarrier(const AsyncBarrier&) = delete;
    AsyncBarrier& operator=(const AsyncBarrier&) = delete;

    // move semantic
    AsyncBarrier(AsyncBarrier&&) = delete;
    AsyncBarrier& operator=(AsyncBarrier&&) = delete;

    ~AsyncBarrier() = default;

    auto& mutex() noexcept;

    auto& condvar() noexcept;

    void reset(bool lkflag = true) noexcept
    { (void)lkflag; pop<void>(); }

    void notify(bool lkflag = true) noexcept
    { (void)lkflag; pop<void>(); }

    bool wait() noexcept { return pop<bool>(); }

    bool wait(std::unique_lock<std::mutex>&) noexcept { return pop<bool>(); }

    bool peak(bool lkflag = true) const noexcept
    { (void)lkflag; return pop<bool>(); }

    bool read(bool lkflag = true) const noexcept
    { (void)lkflag; return pop<bool>(); }

    bool wait_for(unsigned long) noexcept { return pop<bool>(); }

    bool wait_for(unsigned long, std::unique_lock<std::mutex>&) noexcept
    { return pop<bool>(); }

private:
    bool notified_{false};
    mutable std::mutex mutex_{};
    std::condition_variable cond_{};
};

inline auto& AsyncBarrier::mutex() noexcept
{
    return mutex_;
}

inline auto& AsyncBarrier::condvar() noexcept
{
    return cond_;
}

}    // namespace utl
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif    // UCM_AAP_LIBRARY_LIB_UTL_AYSNC_BARRIER_H_
