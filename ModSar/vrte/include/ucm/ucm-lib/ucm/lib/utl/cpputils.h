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


template<typename T,
    std::enable_if_t<std::is_integral<T>::value, bool> = true>
inline constexpr T& conseval_min(T& a, T& b)
{
    return a > b ? b : a;
}

#if defined(__BIG_ENDIAN__)
#define htonll(x) (x)
#define ntohll(x) (x)
#else
template<typename T,
    std::enable_if_t<std::is_integral<T>::value, bool> = true>
uint64_t htonll(T value) noexcept
{
    constexpr uint64_t mask = 0xFFFFFFFF;
    uint32_t hi = static_cast<uint32_t>(static_cast<uint64_t>(value) >> 32);
    uint32_t lo = static_cast<uint32_t>(static_cast<uint64_t>(value) & mask);

    return (static_cast<uint64_t>(htonl(lo)) << 32)
            | static_cast<uint64_t>(htonl(hi));
}

template<typename T,
    std::enable_if_t<std::is_integral<T>::value, bool> = true>
uint64_t ntohll(T value) noexcept
{
    constexpr uint64_t mask = 0xFFFFFFFF;
    uint32_t hi = static_cast<uint32_t>(static_cast<uint64_t>(value) >> 32);
    uint32_t lo = static_cast<uint32_t>(static_cast<uint64_t>(value) & mask);

    return (static_cast<uint64_t>(ntohl(lo)) << 32)
            | static_cast<uint64_t>(ntohl(hi));
}
#endif

template<class T,
    std::enable_if_t<
        std::is_same<
            std::make_unsigned_t<T>, uint16_t>::value, bool> = true>
static T ntoh(const T& val)
{
    return ntohs(val);
}

template<class T,
    std::enable_if_t<
        std::is_same<
            std::make_unsigned_t<T>, uint32_t>::value, bool> = true>
static T ntoh(const T& val)
{
    return ntohl(val);
}

template<class T,
    std::enable_if_t<
        std::is_same<
            std::make_unsigned_t<T>, uint64_t>::value, bool> = true>
static T ntoh(const T& val)
{
    return utl::ntohll(val);
}

template<class T,
    std::enable_if_t<
        std::is_same<
            std::make_unsigned_t<T>, uint16_t>::value, bool> = true>
static T hton(const T& val)
{
    return htons(val);
}

template<class T,
    std::enable_if_t<
        std::is_same<
            std::make_unsigned_t<T>, uint32_t>::value, bool> = true>
static T hton(const T& val)
{
    return htonl(val);
}

template<class T,
    std::enable_if_t<
        std::is_same<
            std::make_unsigned_t<T>, uint64_t>::value, bool> = true>
static T hton(const T& val)
{
    return utl::htonll(val);
}

// Check for addition overflow
template<class T,
    std::enable_if_t<std::is_integral<T>::value, bool> = true>
inline static bool add_overflow(T a, T b, T* res) noexcept
{
    return __builtin_add_overflow(a, b, res);
}

// Check for substraction underflow
template<class T,
    std::enable_if_t<std::is_integral<T>::value, bool> = true>
inline static T sub_overflow(T a, T b)
{
    T res;
    if (__builtin_sub_overflow(a, b, &res))
        throw std::out_of_range("sub_overflow");
    return a - b;
}

// Check for multiplication overflow
template<class T,
    std::enable_if_t<std::is_integral<T>::value, bool> = true>
inline static T mul_overflow(T a, T b)
{
    T res;
    if (__builtin_mul_overflow(a, b, &res))
        throw std::out_of_range("mul_overflow");
    return a * b;
}


// MISRA conformant, but ugly!
template <typename R, typename F, typename... Args>
inline static auto
temp_failure_retry(const R& _failed, const F& _func, const Args&... _args)
    -> decltype(_func(_args...))
{
    decltype(_func(_args...)) rv;
    errno = 0;
    do {
        rv = _func(_args...);
    } while (rv == _failed && errno == EINTR);

    return rv;
}

template<class T,
    std::enable_if_t<std::is_integral<T>::value, bool> = true>
constexpr inline static T align_up(const T& address, const T& align)
{
    return (align > 0 && (align & (align - 1)) == 0)
            ? ((address + (align - 1)) & (~(align - 1)))
            : throw std::logic_error("Unaligned address!");
}

template<class T,
    std::enable_if_t<std::is_integral<T>::value, bool> = true>
constexpr inline static T align_down(const T& address, const T& align)
{
    return (align > 0 && (align & (align - 1)) == 0)
            ? (address & (~(align - 1)))
            : throw std::logic_error("Unaligned address!");
}

template <typename D, typename B>
std::unique_ptr<D> static_cast_ptr(std::unique_ptr<B>& base)
{
    return std::unique_ptr<D>(static_cast<D*>(base.release()));
}

template <typename D, typename B>
std::unique_ptr<D> static_cast_ptr(std::unique_ptr<B>&& base)
{
    return std::unique_ptr<D>(static_cast<D*>(base.release()));
}

#if !defined(array_size)
template <size_t SIZE, class T>
inline size_t array_size(T (&arr)[SIZE])
{
    (void)arr;
    return SIZE;
}
#endif

template <typename T, typename... Args>
inline T check_range(const T& v, const T& min, const T& max, Args&&... args)
{
    if (v < min || v > max)
        throw std::out_of_range(static_cast<Args&&>(args)...);
    return v;
}

template <typename T, typename... Args>
inline T check_round(const T& v, const T& s, Args&&... args)
{
    if (s % v != 0)
        throw std::invalid_argument(static_cast<Args&&>(args)...);
    return v;
}

template <typename T>
std::string type_name();

template <class T, size_t ROW, size_t COL>
using Matrix = std::array<std::array<T, COL>, ROW>;

struct convert
{
    template <typename T>
    static std::string to_hex(const T& num)
    {
        std::stringstream ss;
        ss << std::hex << num;
        return std::string(ss.str());
    }

    static std::string to_hex (std::vector<std::uint8_t> const& arg);
    static std::vector<std::uint8_t> from_hex(std::string const& arg);

    template <typename T>
    static std::string to_oct(const T& num)
    {
        std::stringstream ss;
        ss << std::oct << num;
        return std::string(ss.str());
    }

    template <typename T, std::size_t D>
    static std::string to_bin(const T& num)
    {
        return std::bitset<D>(num).to_string();
    }
};

bool string_equal(const std::string& a, const std::string& b);

// helper to put non-copyable/movable types in a vector

template <typename T> struct EmplaceVector
{
private:
    using Raw = typename std::aligned_storage<sizeof(T),
          alignof(T)>::type;
    std::vector<Raw> v;

    static T* cast(Raw* ptr)
    {
        return reinterpret_cast<T*>(ptr);
    }

public:
    template<typename... U>
    EmplaceVector(size_t count, U&&... u)
        : v(count)
    {
        for (auto&& i : v)
            new (cast(&i)) T(static_cast<U&&>(u)...);
    }

   ~EmplaceVector()
   {
        for (auto&& i : v)
            (cast(&i))->~T();
   }

   T& at(size_t i)
   {
       return *cast(&v.at(i));
   }
};

std::string trim(const std::string& str);

//==============================================================================
//
// contiguous mutable memory streams

template<typename T> struct Membuf
    : std::basic_streambuf<T>
{
    Membuf(T* ptr, std::size_t len)
    {
        this->setp(ptr, ptr + len);
        this->setg(ptr, ptr, ptr + len);
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
        this->rdbuf(&buf);
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
	return ::strcpy(
			static_cast<char*>(static_cast<void*>(dst)),
			static_cast<const char*>(static_cast<const void*>(src)));
}



//==============================================================================

std::string str_tolower(const std::string& src);
std::string str_toupper(const std::string& src);

inline std::string yesno(const bool& flag)
{
    return flag ? std::string("yes") : std::string("no");
}

}    // namespace utl
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif /* UCM_AAP_LIBRARY__UCM_LIB_UTL__CPPUTILS_H_ */
