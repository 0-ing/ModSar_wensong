//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2020 by Robert Bosch GmbH. All rights reserved.
//
// This ClockPair is property of Robert Bosch GmbH. Any unauthorized copy, use
// or distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         tests/VRTE_UT/ucm/lib/utl/object_locker/ucm/lib/utl/object_locker.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY__UCM_LIB_UTL__OBJECT_LOCKER_H_
#define UCM_AAP_LIBRARY__UCM_LIB_UTL__OBJECT_LOCKER_H_

#include <functional>

#include "ucm/mock/sequence.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace utl   {

struct ObjectLocker
       : virtual protected ucm::mock::Sequence
{
public:
    explicit ObjectLocker() noexcept = default;

    // copy semantics
    ObjectLocker(const ObjectLocker&) = delete;
    ObjectLocker& operator=(const ObjectLocker&) = delete;

    // move semantic
    ObjectLocker(ObjectLocker&&) noexcept = delete;
    ObjectLocker& operator=(ObjectLocker&&) = delete;

    virtual ~ObjectLocker() = default;

    bool lock() noexcept
    {
       return pop<bool>();
    }

    bool unlock() noexcept
    {
       return pop<bool>();
    }

    virtual void touch() noexcept {}

    bool is_locked() const noexcept
    {
       return pop<bool>();
    }

    void on_acquire(std::function<void()>&&) noexcept {}
    void on_release(std::function<void()>&&) noexcept {}

protected:
    std::function<void()> on_release_{};
    std::function<void()> on_acquire_{};
};

}    // namespace utl
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif    // UCM_AAP_LIBRARY__UCM_LIB_UTL__OBJECT_LOCKER_H_
