//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/utl/cast.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Hans Berghaell
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY_UCM_LIB_UTL_CAST_H_
#define UCM_AAP_LIBRARY_UCM_LIB_UTL_CAST_H_

#include <limits>
#include <cstdint>
#include <stdexcept>
#include <type_traits>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace utl   {


namespace cast_impl {

    // helpers
    template<typename T> using Lim =
        std::numeric_limits<typename std::decay<T>::type>;

    // custom decay, also of inner non-function pointers

    template<typename T, typename = typename std::decay<T>::type>
    struct Decay
        : std::decay<T> {};

    template<typename T, typename U>
    struct Decay <T, U*>
    {
        using type = typename std::decay<U>::type*;
    };

    template<typename T> using decay = typename Decay<T>::type;

    // alignment for pointers and uintptr_t
    template<
        typename T,
        typename U = decay<T>
    >
    struct Ali {};

    template<typename T, typename U>
    struct Ali <T, U*>
    {
        static constexpr std::size_t value = alignof(U);
    };

    template<typename T>
    struct Ali <T, void*>
    {
        static constexpr std::size_t value = 1;
    };

    template<typename T>
    struct Ali <T, std::uintptr_t>
    {
        static constexpr std::size_t value = 1;
    };

    //========================================================================
    //
    // has limits

    template<
        typename To, typename Fr,
        bool = (Lim<To>::min() > Lim<Fr>::min()),
        bool = (Lim<To>::max() < Lim<Fr>::max())
    >
    struct Has
    {
        using type = To;
        static constexpr type value(Fr&& fr) noexcept
        {
            return static_cast<To>(fr);
        }
    };

    // check lower bound
    template<typename To, typename Fr>
    struct Has <To, Fr, true, false>
    {
        using type = To;
        static constexpr type value(Fr&& fr)
        {
            using L = std::numeric_limits<typename std::decay<To>::type>;
            if (fr < L::min())
                throw std::out_of_range(__PRETTY_FUNCTION__);
            return static_cast<To>(fr);
        }
    };

    // check upper bound
    template<typename To, typename Fr>
    struct Has <To, Fr, false, true>
    {
        using type = To;
        static constexpr type value(Fr&& fr)
        {
            using L = std::numeric_limits<typename std::decay<To>::type>;
            if (fr > L::max())
                throw std::out_of_range(__PRETTY_FUNCTION__);
            return static_cast<To>(fr);
        }
    };

    // check lower and upper bound
    template<typename To, typename Fr>
    struct Has <To, Fr, true, true>
    {
        using type = To;
        static constexpr type value(Fr&& fr)
        {
            using L = std::numeric_limits<typename std::decay<To>::type>;
            if (fr < L::min() or fr > L::max())
                throw std::out_of_range(__PRETTY_FUNCTION__);
            return static_cast<To>(fr);
        }
    };

    //========================================================================
    //
    // no limits, i.e. conversion between pointer and void* or uintptr_t

    template<
        typename To, typename Fr,
        typename = decay<To>, 
        typename = decay<Fr>,
        bool     = (Ali<To>::value <= Ali<Fr>::value)
    >
    struct Not {};

    // pointer ==> uintptr_t
    template<typename To, typename Fr, typename F, bool A>
    struct Not <To, Fr, std::uintptr_t, F*, A>
    {
        using type = std::uintptr_t;
        static constexpr type value (Fr&& fr) noexcept
        {
            return reinterpret_cast<type>(fr);
        }
    };

    // uintptr_t ==> pointer with equal or smaller alignment
    template<typename To, typename Fr, typename T>
    struct Not <To, Fr, T*, std::uintptr_t, true>
    {
        using type = T*;
        static constexpr type value (Fr&& fr) noexcept
        {
            return reinterpret_cast<type>(fr);
        }
    };

    // uintptr_t ==> pointer with greater alignment
    template<typename To, typename Fr, typename T>
    struct Not <To, Fr, T*, std::uintptr_t, false>
    {
        using type = T*;
        static constexpr type value (Fr&& fr)
        {
            if(fr % Ali<To>::value)
                throw std::range_error(__PRETTY_FUNCTION__);
            return reinterpret_cast<type>(fr);
        }
    };

    // pointer ==> pointer - in general not allowed
    template<typename To, typename Fr, typename T, typename F, bool A>
    struct Not <To, Fr, T*, F*, A> {};

    // pointer ==> void*
    template<typename To, typename Fr, typename F, bool A>
    struct Not <To, Fr, void*, F*, A>
    {
        using type = void*;
        static constexpr type value (Fr&& fr) noexcept
        {
            return static_cast<type>(fr);
        }
    };

    // void* ==> pointer with equal or smaller alignment
    template<typename To, typename Fr, typename T>
    struct Not <To, Fr, T*, void*, true>
    {
        using type = T*;
        static constexpr type value (Fr&& fr) noexcept
        {
            return static_cast<type>(fr);
        }
    };

    // void* ==> pointer with greater alignment
    template<typename To, typename Fr, typename T>
    struct Not <To, Fr, T*, void*, false>
    {
        using type = T*;
        static constexpr type value (Fr&& fr)
        {
            if(reinterpret_cast<std::uintptr_t>(fr) % Ali<To>::value)
                throw std::range_error(__PRETTY_FUNCTION__);
            return static_cast<type>(fr);
        }
    };

    //=========================================================================
    //
    // entry point - select between types that has limits and those who do not

    template<
        typename T, typename F,
        bool = Lim<T>::is_specialized and
               Lim<F>::is_specialized
    >
    struct Entry
        : Has <T, F> {};

    template<typename T, typename F>
    struct Entry <T, F, false>
        : Not <T, F> {};

} // cast_impl

template<typename To, typename Fr>
constexpr auto cast(Fr&& fr)
    noexcept (noexcept(
             cast_impl::Entry<To, Fr>::value(std::declval<Fr&&>())
     ))
 -> typename cast_impl::Entry<To, Fr>::type
{
    return   cast_impl::Entry<To, Fr>::value(static_cast<Fr&&>(fr));
}


} // namespace utl
} // namespace lib
} // namespace ucm
} // namespace vrte
} // namespace bosch

#endif // UCM_AAP_LIBRARY_UCM_LIB_UTL_CAST_H_
