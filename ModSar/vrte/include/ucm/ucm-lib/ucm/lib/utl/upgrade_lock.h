//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/utl/upgrade_lock.h
/// @brief
/// @copyright    Robert Bosch GmbH 2022
/// @author       Hans Berghaell
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY_LIB_UTL_UPGRADE_LOCK_H_
#define UCM_AAP_LIBRARY_LIB_UTL_UPGRADE_LOCK_H_

#include <mutex>
#include <atomic>
#include <functional>
#include <shared_mutex>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif


/// @addtogroup bosch_vrte_ucm_lib_utl
/// @{
namespace bosch {
namespace vrte {
namespace ucm {
namespace lib {
namespace utl {

struct UpgradeLock;

struct UpgradeMutex final
{
    std::mutex                unique {};
    std::shared_timed_mutex   shared {};
    std::condition_variable   cv     {};
    bool                      set_next_upgrade(UpgradeLock&);
    void                      clr_next_upgrade(UpgradeLock&);

private:
    std::atomic<UpgradeLock*> next_  {nullptr};
};

/** @class UpgradeLock
    @ingroup bosch_vrte_ucm_lib_utl
    @brief Switch between shared and unique lock.

    See C++ proposal n3427 for switching between shared and unique locks.

    Note that the sequence of a failing call to try_upgrade() and a subsequent
    call to shared() is done without any lock. The next_upgrade methods can
    instead be used to do such a switch from a shared to a unique lock, with a
    guarantee not to be intervened.

    Informally, the shared lock can be used to serve multiple readers, and the
    upgrade lock a single writer, while allowing a single prioritised next
    writer (for say, cancel operations).
*/
struct UpgradeLock final
{
    enum class Mode
    {
        deferred,      ///< no lock
        shared,        ///< blocking wait for a shared lock
        upgrade,       ///< blocking wait for a upgradable shared lock
        unique,        ///< blocking wait for a downgradable unique lock
        try_shared,    ///< non-blocking version of shared()
        try_upgrade,   ///< non-blocking version of upgrade()
        try_unique     ///< non-blocking version of unique()
    };

    using UMtx = std::mutex;
    using SMtx = std::shared_timed_mutex;

    ~UpgradeLock();
    explicit UpgradeLock(UpgradeMutex&, Mode);

    UpgradeLock(UpgradeLock     &&) = delete;
    UpgradeLock(UpgradeLock const&) = delete;
    UpgradeLock& operator=(UpgradeLock     &&) = delete;
    UpgradeLock& operator=(UpgradeLock const&) = delete;

    void unlock();            ///< unlock all
    void shared();            ///< blocking wait for shared lock
    void upgrade();           ///< blocking wait for upgrade lock
    void unique();            ///< blocking wait for unique lock
    bool try_shared();        ///< non-blocking try for a shared lock
    bool try_upgrade();       ///< non-blocking try for a upgradable shared lock
    bool try_unique();        ///< non-blocking try for a unique lock
    bool next_upgrade();      ///< put as next upgrade lock
    bool next_upgrade_wait(); ///< put as next upgrade lock and wait for it


    /// retry upgrade when @var equals @arg
    /// @return false for shared lock, true for upgrade lock
    template<typename T, typename U>
    bool retry_upgrade_if(T const& var, U arg)
    {
        while(true) {
             if (try_upgrade())
                return true;
            shared();
            if (var != arg)
                break;
            unlock();
        }
        return false;
    }

    operator bool () const; ///< true if holding any lock

    /// set variable under a temporary unique lock
    template<typename T, typename U>
    void unique(T& var, U arg)
    {
        auto before = sstate_;
        if (sstate_ != SState::unique)
            unique();
        var = arg;
        if (before == SState::shared)
            shared();
    }

    /// call function under a temporary unique lock
    void unique(std::function<void()>&&);

private:
    enum class UState { none, upgrade };
    enum class SState { none, shared, unique };

    UpgradeMutex&  mtx_;
    UState ustate_ {UState::none};
    SState sstate_ {SState::none};
};


}    // namespace utl
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif /* UCM_AAP_LIBRARY_LIB_UTL_UPGRADE_LOCK_H_ */
