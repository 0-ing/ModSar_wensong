//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/utl/cpputils.h
/// @brief
/// @copyright    Robert Bosch GmbH 2018
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY__UCM_LIB_UTL__CPPUTILS_H_
#define UCM_AAP_LIBRARY__UCM_LIB_UTL__CPPUTILS_H_

#include <arpa/inet.h>

#include <ios>
#include <limits>
#include <vector>
#include <bitset>
#include <cerrno>
#include <memory>
#include <string>
#include <sstream>
#include <cstring>
#include <exception>
#include <type_traits>

#include "ucm/mock/sequence.h"

#ifdef _MSC_VER
#define NOEXCEPT
#else
#define NOEXCEPT noexcept
#endif

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace utl   {

#if defined(__BIG_ENDIAN__)
#define htonll(x) (x)
#define ntohll(x) (x)
#else
template<typename T,
    std::enable_if_t<std::is_integral<T>::value, bool> = true>
uint64_t htonll(T value) noexcept
{
    return ucm::mock::Sequence::pop<uint64_t>();
}

template<typename T,
    std::enable_if_t<std::is_integral<T>::value, bool> = true>
uint64_t ntohll(T value) noexcept
{
    return ucm::mock::Sequence::pop<uint64_t>();
}
#endif

template<class T,
    std::enable_if_t<
        std::is_same<
            std::make_unsigned_t<T>, uint16_t>::value, bool> = true>
static T ntoh(const T& )
{
    return ucm::mock::Sequence::pop<uint16_t>();
}

template<class T,
    std::enable_if_t<
        std::is_same<
            std::make_unsigned_t<T>, uint32_t>::value, bool> = true>
static T ntoh(const T& )
{
    return ucm::mock::Sequence::pop<uint32_t>();
}

template<class T,
    std::enable_if_t<
        std::is_same<
            std::make_unsigned_t<T>, uint64_t>::value, bool> = true>
static T ntoh(const T& )
{
    return ucm::mock::Sequence::pop<uint64_t>();
}

template<class T,
    std::enable_if_t<
        std::is_same<
            std::make_unsigned_t<T>, uint16_t>::value, bool> = true>
static T hton(const T& )
{
    return ucm::mock::Sequence::pop<uint16_t>();
}

template<class T,
    std::enable_if_t<
        std::is_same<
            std::make_unsigned_t<T>, uint32_t>::value, bool> = true>
static T hton(const T& )
{
    return ucm::mock::Sequence::pop<uint32_t>();
}

template<class T,
    std::enable_if_t<
        std::is_same<
            std::make_unsigned_t<T>, uint64_t>::value, bool> = true>
static T hton(const T& )
{
    return ucm::mock::Sequence::pop<uint64_t>();
}

// Check for addition overflow
template<class T,
    std::enable_if_t<std::is_integral<T>::value, bool> = true>
inline static bool add_overflow(T a, T b, T* res) noexcept
{
    return ucm::mock::Sequence::pop<bool>();
}

// Check for substraction underflow
template<class T,
    std::enable_if_t<std::is_integral<T>::value, bool> = true>
inline static T sub_overflow(T a, T b)
{
    return ucm::mock::Sequence::pop<int>();
}

// Check for multiplication overflow
template<class T,
    std::enable_if_t<std::is_integral<T>::value, bool> = true>
inline static T mul_overflow(T a, T b)
{
    return ucm::mock::Sequence::pop<int>();
}


// MISRA conformant, but ugly!
template <typename R, typename F, typename... Args>
inline static auto
temp_failure_retry(const R& _failed, const F& _func, const Args&... _args)
    -> decltype(_func(_args...))
{
return ucm::mock::Sequence::pop<const F&>();
}

template<class T,
    std::enable_if_t<std::is_integral<T>::value, bool> = true>
constexpr inline static T align_up(const T&, const T&)
{
    return ucm::mock::Sequence::pop<int>();
}

template<class T,
    std::enable_if_t<std::is_integral<T>::value, bool> = true>
constexpr inline static T align_down(const T& address, const T& align)
{
    return ucm::mock::Sequence::pop<int>();
}

template <typename D, typename B>
std::unique_ptr<D> static_cast_ptr(std::unique_ptr<B>& base)
{
    return ucm::mock::Sequence::pop<std::unique_ptr<D>>();
}

template <typename D, typename B>
std::unique_ptr<D> static_cast_ptr(std::unique_ptr<B>&& base)
{
    return ucm::mock::Sequence::pop<std::unique_ptr<D>>();
}

#if !defined(array_size)
template <size_t SIZE, class T>
inline size_t array_size(T (&arr)[SIZE])
{
    return ucm::mock::Sequence::pop<size_t>();
}
#endif

template <typename T, typename... Args>
inline T check_range(const T& v, const T& min, const T& max, Args&&... args)
{
    return ucm::mock::Sequence::pop<T const&>();
}

template <typename T, typename... Args>
inline T check_round(const T& v, const T& s, Args&&... args)
{
    return ucm::mock::Sequence::pop<T const&>();
}

template <typename T>
std::string type_name() {return ucm::mock::Sequence::pop<std::string>();}

template <class T, size_t ROW, size_t COL>
using Matrix = std::array<std::array<T, COL>, ROW>;

struct convert
{
    template <typename T>
    static std::string to_hex(const T& num)
    {
        return ucm::mock::Sequence::pop<std::string>();
    }

    static std::string to_hex (std::vector<std::uint8_t> const& arg __attribute__((unused))) {return ucm::mock::Sequence::pop<std::string>();}
    static std::vector<std::uint8_t> from_hex(std::string const& arg __attribute__((unused))) {return ucm::mock::Sequence::pop<std::vector<std::uint8_t>>();}

    template <typename T>
    static std::string to_oct(const T& num)
    {
        return ucm::mock::Sequence::pop<std::string>();
    }

    template <typename T, std::size_t D>
    static std::string to_bin(const T& num)
    {
        return ucm::mock::Sequence::pop<std::string>();
    }
};

bool string_equal(const std::string& a __attribute__((unused)), const std::string& b __attribute__((unused))) {return ucm::mock::Sequence::pop<bool>();}

// helper to put non-copyable/movable types in a vector

template <typename T> struct EmplaceVector
{
private:
    using Raw = typename std::aligned_storage<sizeof(T),
          alignof(T)>::type;
    std::vector<Raw> v;

    static T* cast(Raw* ptr)
    {
        return ucm::mock::Sequence::pop<T*>();
    }

public:
    template<typename... U>
    EmplaceVector(size_t count, U&&... u)
        : v(count)
    {

    }

   ~EmplaceVector()
   {

   }

   T& at(size_t i)
   {
       return ucm::mock::Sequence::pop<T&>();
   }
};

std::string trim(const std::string& str __attribute__((unused))) {return ucm::mock::Sequence::pop<std::string>();}

//==============================================================================
//
// contiguous mutable memory streams

template<typename T> struct Membuf
    : std::basic_streambuf<T>
{
    Membuf(T* ptr, std::size_t len)
    {

    }

};

template<typename T, template<typename...> class S>
struct Memstream
    : S <T>
{
    Memstream(T* ptr, std::size_t len)
        : S<T>(&buf)
        , buf(ptr, len)
    {

    }

    template<typename C, typename = typename std::enable_if<
        std::is_same<
            std::random_access_iterator_tag,
            typename std::iterator_traits<
                decltype(std::begin(std::declval<C&>()))
            >::iterator_category
        >::value,
        decltype(std::end(std::declval<C&>()))
    >::type>
    Memstream(C& arg)
        : Memstream(&(*std::begin(arg)), std::end(arg) - std::begin(arg)) {}

private:
    Membuf<T> buf;
};

//==============================================================================
template<typename D, typename S>
char *ucm_strcpy(D dst, S src)
{
	return ucm::mock::Sequence::pop<char*>();
}



//==============================================================================

std::string str_tolower(const std::string& src __attribute__((unused))) {return ucm::mock::Sequence::pop<std::string>();}
std::string str_toupper(const std::string& src __attribute__((unused))) {return ucm::mock::Sequence::pop<std::string>();}

inline std::string yesno(const bool& flag __attribute__((unused)))
{
    return ucm::mock::Sequence::pop<std::string>();
}

}    // namespace utl
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif /* UCM_AAP_LIBRARY__UCM_LIB_UTL__CPPUTILS_H_ */
