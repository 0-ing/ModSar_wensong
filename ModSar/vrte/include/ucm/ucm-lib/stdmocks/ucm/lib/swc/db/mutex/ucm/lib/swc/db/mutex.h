//==============================================================================
// C O P Y R I G H T
//------------------------------------------------------------------------------
// Copyright (c) 2020 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//==============================================================================

/// @file         ucm/lib/swc/db/mutex.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY_UCM_LIB_SWC_DB__MUTEX_H_
#define UCM_AAP_LIBRARY_UCM_LIB_SWC_DB__MUTEX_H_

#include <shared_mutex>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/mock/sequence.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace swc   {
namespace db    {


class Mutex
        : virtual protected ucm::mock::Sequence
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_ucm_lib_swc_DBMutex, CTor);
    FRIEND_TEST(Test_ucm_lib_swc_DBMutex, Lock);
    FRIEND_TEST(Test_ucm_lib_swc_DBMutex, TryLock);
    FRIEND_TEST(Test_ucm_lib_swc_DBMutex, TryLockFor);
    FRIEND_TEST(Test_ucm_lib_swc_DBMutex, LockShared);
    FRIEND_TEST(Test_ucm_lib_swc_DBMutex, TryLockShared);
    FRIEND_TEST(Test_ucm_lib_swc_DBMutex, TryLockSharedFor);
#endif
public:
    explicit Mutex() = default;

    Mutex(Mutex     &&) = delete;
    Mutex(Mutex const&) = delete;

    Mutex& operator=(Mutex     &&) = delete;
    Mutex& operator=(Mutex const&) = delete;

    virtual ~Mutex() = default;

    virtual void lock() {pop<void>();}
    virtual void unlock() {pop<void>();}
    virtual bool try_lock() {return pop<bool>();}
    virtual bool try_lock_for(unsigned long)  {return pop<bool>();}

    virtual void lock_shared() {pop<void>();}
    virtual void unlock_shared() {pop<void>();}
    virtual bool try_lock_shared() {return pop<bool>();}
    virtual bool try_lock_shared_for(unsigned long ) {return pop<bool>();}

private:
    mutable std::shared_timed_mutex mutex_{};
};


}    // namespace db
}    // namespace swc
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY_UCM_LIB_SWC_DB__MUTEX_H_
