//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2020 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/utl/value_pair.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY_UCM_LIB_UTL_VALUE_PAIR_H_
#define UCM_AAP_LIBRARY_UCM_LIB_UTL_VALUE_PAIR_H_

#include <limits>
#include <utility>
#include <type_traits>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif


namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace utl   {

template<class _C, class _T>
struct ValuePair final
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_ucm_lib_utl_ValuePair, CTor);
    FRIEND_TEST(Test_ucm_lib_utl_ValuePair, Assign);
#endif

    typedef _C class_type;
    typedef _T value_type;


    constexpr ValuePair() = default;

    constexpr ValuePair(bool valid, const _T& value)
        : pair_(valid, value)
    {}

    template<class _U,
        typename std::enable_if<
            std::is_convertible<_U, _T>::value>::type = true>
    constexpr ValuePair(bool valid, _U&& value)
        : pair_(valid, std::forward<_U>(value))
    {}

    ValuePair(ValuePair     &&) = default;
    ValuePair(ValuePair const&) = default;

    ValuePair& operator=(ValuePair     &&) = default;
    ValuePair& operator=(ValuePair const&) = default;

    ~ValuePair() = default;

    ValuePair& operator=(const _T& value)
    {
        pair_.second = value;
        return *this;
    }

    ValuePair& operator=(_T&& value)
    {
        pair_.second = std::move(value);
        return *this;
    }

    void operator()(bool valid) noexcept
    {
        pair_.first = valid;
    }

    operator bool() const noexcept
    {
        return std::get<0>(pair_);
    }

    void set_valid(bool flag) noexcept
    {
        pair_.first = flag;
    }

    const auto& get_value() const noexcept
    {
        return std::get<1>(pair_);
    }

    auto& get_value() noexcept
    {
        return std::get<1>(pair_);
    }

protected:
    std::pair<bool, _T> pair_{};
};

template <class _T1, class _T2>
inline constexpr bool
operator==(const ValuePair<_T1, _T2>& x, const _T2& y)
{
    return x.get_value() == y;
}

template <class _T1, class _T2>
inline constexpr bool
operator==(const _T2& x, const ValuePair<_T1, _T2>& y)
{
    return x == y.get_value();
}

template <class _T1, class _T2>
inline constexpr bool
operator==(const ValuePair<_T1, _T2>& x, const ValuePair<_T1, _T2>& y)
{
    return x.get_value() == y.get_value();
}

template <class _T1, class _T2>
inline constexpr bool
operator!=(const ValuePair<_T1, _T2>& x, const ValuePair<_T1, _T2>& y)
{
    return !(x == y);
}

template <class _T1, class _T2>
inline constexpr bool
operator<(const ValuePair<_T1, _T2>& x, const ValuePair<_T1, _T2>& y)
{
    return x.get_value() < y.get_value();
}

template <class _T1, class _T2>
inline constexpr bool
operator>(const ValuePair<_T1, _T2>& x, const ValuePair<_T1, _T2>& y)
{
    return y < x;
}

template <class _T1, class _T2>
inline constexpr bool
operator>=(const ValuePair<_T1, _T2>& x, const ValuePair<_T1, _T2>& y)
{
    return !(x < y);
}

template <class _T1, class _T2>
inline constexpr bool
operator<=(const ValuePair<_T1, _T2>& x, const ValuePair<_T1, _T2>& y)
{
    return !(y < x);
}


}    // namespace client
}    // namespace ara
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY_UCM_LIB_UTL_VALUE_PAIR_H_
