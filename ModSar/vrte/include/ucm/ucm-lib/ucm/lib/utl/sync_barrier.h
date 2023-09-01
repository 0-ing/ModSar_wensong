//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/utl/sync_barrier.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY__UCM_LIB_UTL__SYNC_BARRIER__H_
#define UCM_AAP_LIBRARY__UCM_LIB_UTL__SYNC_BARRIER__H_

#include <pthread.h>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace utl   {

class SyncBarrier final
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_SyncBarrier, Constructor);
#endif

public:
    SyncBarrier(unsigned count);

    // copy semantics
    SyncBarrier(const SyncBarrier&) = delete;
    SyncBarrier& operator=(const SyncBarrier&) = delete;

    // move semantic
    SyncBarrier(SyncBarrier&&) = delete;
    SyncBarrier& operator=(SyncBarrier&&) = delete;

    ~SyncBarrier();

    void wait() noexcept;

private:
    pthread_barrier_t barrier_{};
};


}    // namespace utl
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif    // UCM_AAP_LIBRARY__UCM_LIB_UTL__SYNC_BARRIER__H_
