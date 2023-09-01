//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2020 by Robert Bosch GmbH. All rights reserved.
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

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace utl   {

class AsyncBarrier final
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_AsyncBarrier, Constructor);
#endif

public:
    AsyncBarrier() = default;

    AsyncBarrier(bool autoreset);

    AsyncBarrier(      AsyncBarrier&&) = delete;
    AsyncBarrier(const AsyncBarrier& ) = delete;

    AsyncBarrier& operator=(      AsyncBarrier&&) = delete;
    AsyncBarrier& operator=(const AsyncBarrier& ) = delete;

    ~AsyncBarrier() = default;

    auto& mutex() noexcept;

    auto& condvar() noexcept;

    void reset(bool lkflag = true) noexcept;

    void notify(bool lkflag = true) noexcept;

    bool wait() noexcept;

    bool wait(std::unique_lock<std::mutex>&) noexcept;

    bool peak(bool lkflag = true) const noexcept;

    bool read(bool lkflag = true) noexcept;

    bool wait_for(unsigned long ms) noexcept;

    bool wait_for(unsigned long ms, std::unique_lock<std::mutex>&) noexcept;

private:
    bool notified_{false};
    bool autoreset_{false};
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
