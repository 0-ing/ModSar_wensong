//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/utl/offset.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY__UCM_LIB_UTL__OFFSET_H_
#define UCM_AAP_LIBRARY__UCM_LIB_UTL__OFFSET_H_

#include <type_traits>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace utl   {

template<typename T,
    std::enable_if_t<std::is_integral<T>::value, bool> = true>
class Offset
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test__ucm_lib_utl__Offset, CTor);
#endif

public:
    constexpr Offset(T value) noexcept
        : address_{value}
    {}

    Offset(Offset     &&) = default;
    Offset(Offset const&) = default;

    Offset& operator=(Offset     &&) = default;
    Offset& operator=(Offset const&) = default;

    ~Offset() = default;

    Offset& operator++() noexcept
    { ++address_; return *this; }

    Offset& operator--() noexcept
    { ++address_; return *this; }

    Offset operator++(int) noexcept
    { auto val = address_; operator++(); return val; }

    Offset operator--(int) noexcept
    { auto val = address_; operator--(); return val; }

    Offset<T>& operator+=(const Offset<T>& rhs) noexcept
    { address_ += rhs(); return *this; }

    Offset<T>& operator-=(const Offset<T>& rhs) noexcept
    { address_ -= rhs(); return *this; }

    Offset<T>& operator+=(const T& rhs) noexcept
    { address_ += rhs; return *this; }

    Offset<T>& operator-=(const T& rhs) noexcept
    { address_ -= rhs; return *this; }

    T operator()()                const { return address_;           }
    T operator()(T value)         const { return address_ + value;   }
    T operator()(Offset<T> value) const { return address_ + value(); }

private:
    T address_;
};

template<typename T,
    std::enable_if_t<std::is_integral<T>::value, bool> = true>
inline bool operator<(const Offset<T>& lhs, const Offset<T>& rhs)
{
    return lhs() < rhs();
}

template<typename T, typename U,
    std::enable_if_t<
        (std::is_integral<T>::value &&
         std::is_integral<U>::value), bool> = true>
inline bool operator<(const Offset<T>& lhs, const U& rhs)
{
    return lhs() < static_cast<T>(rhs);
}

template<typename T, typename U,
    std::enable_if_t<
        (std::is_integral<T>::value &&
         std::is_integral<U>::value), bool> = true>
inline bool operator<(const U& lhs, const Offset<T>& rhs)
{
    return static_cast<T>(lhs) < rhs();
}

template<typename T,
    std::enable_if_t<std::is_integral<T>::value, bool> = true>
inline bool operator>(const Offset<T>& lhs, const Offset<T>& rhs)
{
    return lhs() > rhs();
}

template<typename T, typename U,
    std::enable_if_t<
        (std::is_integral<T>::value &&
         std::is_integral<U>::value), bool> = true>
inline bool operator>(const Offset<T>& lhs, const U& rhs)
{
    return lhs() > static_cast<T>(rhs);
}

template<typename T, typename U,
    std::enable_if_t<
        (std::is_integral<T>::value &&
         std::is_integral<U>::value), bool> = true>
inline bool operator>(const U& lhs, const Offset<T>& rhs)
{
    return static_cast<T>(lhs) > rhs();
}

template<typename T,
    std::enable_if_t<std::is_integral<T>::value, bool> = true>
inline bool operator<=(const Offset<T>& lhs, const Offset<T>& rhs)
{
    return !(lhs > rhs);
}

template<typename T, typename U,
    std::enable_if_t<
        (std::is_integral<T>::value &&
         std::is_integral<U>::value), bool> = true>
inline bool operator<=(const Offset<T>& lhs, const U& rhs)
{
    return !(lhs > rhs);
}

template<typename T, typename U,
    std::enable_if_t<
        (std::is_integral<T>::value &&
         std::is_integral<U>::value), bool> = true>
inline bool operator<=(const U& lhs, const Offset<T>& rhs)
{
    return !(lhs > rhs);
}

template<typename T,
    std::enable_if_t<std::is_integral<T>::value, bool> = true>
inline bool operator>=(const Offset<T>& lhs, const Offset<T>& rhs)
{
    return !(lhs < rhs);
}

template<typename T, typename U,
    std::enable_if_t<
        (std::is_integral<T>::value &&
         std::is_integral<U>::value), bool> = true>
inline bool operator>=(const Offset<T>& lhs, const U& rhs)
{
    return !(lhs < rhs);
}

template<typename T, typename U,
    std::enable_if_t<
        (std::is_integral<T>::value &&
         std::is_integral<U>::value), bool> = true>
inline bool operator>=(const U& lhs, const Offset<T>& rhs)
{
    return !(lhs < rhs);
}

template<typename T,
    std::enable_if_t<std::is_integral<T>::value, bool> = true>
inline bool operator==(const Offset<T>& lhs, const Offset<T>& rhs)
{
    return lhs() == rhs();
}

template<typename T, typename U,
    std::enable_if_t<
        (std::is_integral<T>::value &&
         std::is_integral<U>::value), bool> = true>
inline bool operator==(const Offset<T>& lhs, const U& rhs)
{
    return lhs() == static_cast<T>(rhs);
}

template<typename T, typename U,
    std::enable_if_t<
        (std::is_integral<T>::value &&
         std::is_integral<U>::value), bool> = true>
inline bool operator==(const U& lhs, const Offset<T>& rhs)
{
    return static_cast<T>(lhs) == rhs();
}

template<typename T,
    std::enable_if_t<std::is_integral<T>::value, bool> = true>
inline bool operator!=(const Offset<T>& lhs, const Offset<T>& rhs)
{
    return !(lhs == rhs);
}

template<typename T, typename U,
    std::enable_if_t<
        (std::is_integral<T>::value &&
         std::is_integral<U>::value), bool> = true>
inline bool operator!=(const Offset<T>& lhs, const U& rhs)
{
    return !(lhs == rhs);
}

template<typename T, typename U,
    std::enable_if_t<
        (std::is_integral<T>::value &&
         std::is_integral<U>::value), bool> = true>
inline bool operator!=(const U& lhs, const Offset<T>& rhs)
{
    return !(lhs == rhs);
}

template<typename T, typename U,
    std::enable_if_t<
        (std::is_integral<T>::value &&
         std::is_integral<U>::value), bool> = true>
inline U operator+(Offset<T> lhs, U rhs)
{
    return lhs() + rhs;
}

template<typename T, typename U,
    std::enable_if_t<
        (std::is_integral<T>::value &&
         std::is_integral<U>::value), bool> = true>
inline U operator+(U lhs, const Offset<T>& rhs)
{
    return lhs + rhs();
}

template<typename T, typename U,
    std::enable_if_t<
        (std::is_integral<T>::value &&
         std::is_integral<U>::value), bool> = true>
inline U operator-(Offset<T> lhs, U rhs)
{
    return lhs() - rhs;
}

template<typename T, typename U,
    std::enable_if_t<
        (std::is_integral<T>::value &&
         std::is_integral<U>::value), bool> = true>
inline U operator-(U lhs, const Offset<T>& rhs)
{
    return lhs - rhs();
}

template<typename T, typename U,
    std::enable_if_t<
        (std::is_integral<T>::value &&
         std::is_integral<U>::value), bool> = true>
inline U& operator-=(U& lhs, const Offset<T>& rhs)
{
    lhs -= rhs();
    return lhs;
}

template<typename T, typename U,
    std::enable_if_t<
        (std::is_integral<T>::value &&
         std::is_integral<U>::value), bool> = true>
inline U& operator+=(U& lhs, const Offset<T>& rhs)
{
    lhs += rhs();
    return lhs;
}


}    // namespace utl
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY__UCM_LIB_UTL__OFFSET_H_
