//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2020 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/utl/restate.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY__UCM_LIB_UTL__RESTATE_H_
#define UCM_AAP_LIBRARY__UCM_LIB_UTL__RESTATE_H_

#include <atomic>
#include <stdexcept>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace utl   {

/// @brief Reentrant state wrapper for enums
/// The class provides a mechanism for entering and leaving a state in a
/// RAII fashion.
template<class _Value,
    std::enable_if_t<std::is_enum<_Value>::value, bool> = true>
class REState final
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test__ucm_lib_utl__REState, CTor);
#endif

public:
    explicit REState(const _Value& on_leave) noexcept
        : on_leave_{on_leave}
        , state_{on_leave}
    {}

    REState(REState     &&) = delete;
    REState(REState const&) = delete;

    REState& operator=(REState     &&) = delete;
    REState& operator=(REState const&) = delete;

    ~REState() = default;

    void enter(const _Value& value)
    {
        if (state_ != on_leave_)
            throw std::runtime_error("REState entered");
        state_ = value;
    }

    void leave() noexcept
    {
        state_ = on_leave_;
    }

    const _Value& value() const noexcept
    {
        return state_;
    }

private:
    const _Value on_leave_;
    std::atomic<_Value> state_;
};

/// @brief Reentrant state wrapper for enums
/// The class provides a mechanism for entering and leaving a state in a
/// RAII fashion.
template<class _REState, class _Value>
class REStateLock final
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test__ucm_lib_utl__REState, CTor);
#endif

public:
    explicit REStateLock(_REState& restate, const _Value& value)
        : restate_{restate}
    {
        restate_.enter(value);
    }

    REStateLock(REStateLock     &&) = delete;
    REStateLock(REStateLock const&) = delete;

    REStateLock& operator=(REStateLock     &&) = delete;
    REStateLock& operator=(REStateLock const&) = delete;

    ~REStateLock()
    {
        restate_.leave();
    }

private:
    _REState& restate_;
};

}    // namespace utl
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif    // UCM_AAP_LIBRARY__UCM_LIB_UTL__RESTATE_H_
