//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2020 by Robert Bosch GmbH. All rights reserved.
//
// This ClockPair is property of Robert Bosch GmbH. Any unauthorized copy, use
// or distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @ClockPair    ucm/lib/utl/object_locker.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY__UCM_LIB_UTL__OBJECT_LOCKER_H_
#define UCM_AAP_LIBRARY__UCM_LIB_UTL__OBJECT_LOCKER_H_

#include <atomic>
#include <functional>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif


namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace utl   {

struct ObjectLocker
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_ucm_lib_utl_ObjectLocker, CTor);
#endif

public:
    explicit ObjectLocker() noexcept = default;

    ObjectLocker(ObjectLocker     &&) = delete;
    ObjectLocker(ObjectLocker const&) = delete;

    ObjectLocker& operator=(ObjectLocker     &&) = delete;
    ObjectLocker& operator=(ObjectLocker const&) = delete;

    virtual ~ObjectLocker() = default;

    bool lock() noexcept;
    bool unlock() noexcept;
    bool is_locked() const noexcept;

    virtual void touch() noexcept;

    void on_acquire(std::function<void()>&&) noexcept;
    void on_release(std::function<void()>&&) noexcept;

protected:
    std::function<void()> on_release_{};
    std::function<void()> on_acquire_{};

private:
    std::atomic<bool> locked_{false};
};

}    // namespace utl
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif    // UCM_AAP_LIBRARY__UCM_LIB_UTL__OBJECT_LOCKER_H_
