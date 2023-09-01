//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2020 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         tests/VRTE_UT/depmocks/ucm/lib/utl/restate/ucm/lib/utl/restate.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY__UCM_LIB_UTL__RESTATE_H_
#define UCM_AAP_LIBRARY__UCM_LIB_UTL__RESTATE_H_

#include <atomic>
#include <stdexcept>

#include "ucm/mock/sequence.h"


namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace utl   {

template<class _Value,
    std::enable_if_t<std::is_enum<_Value>::value, bool> = true>
class REState final
            : virtual protected ucm::mock::Sequence
{
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

    void use_pop(bool flag) noexcept
    {
        usepop_ = flag;
    }

    void enter(const _Value& value)
    {
        if (usepop_) {
            bool tflag = pop<bool>();
            if (tflag)
                throw std::runtime_error("REState entered");
        }
        else {
            if (state_ != on_leave_)
                throw std::runtime_error("REState entered");
            state_ = value;
        }
    }

    void leave() noexcept
    {
        state_ = on_leave_;
    }

private:
    bool usepop_{false};
    const _Value on_leave_;
    std::atomic<_Value> state_;
};

template<class _REState, class _Value>
class REStateLock final
{
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
