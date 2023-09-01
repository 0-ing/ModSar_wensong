//==============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// @copyright (c) 2021-2022 by Robert Bosch GmbH. All rights reserved.
//
// The reproduction, distribution and utilization of this file as
// well as the communication of its contents to others without express
// authorization is prohibited. Offenders will be held liable for the
// payment of damages. All rights reserved in the event of the grant
// of a patent, utility model or design.
//==============================================================================

/// @file utility.h
//==============================================================================

#ifndef ARA_CORE_UTILITY_H_
#define ARA_CORE_UTILITY_H_

#include <initializer_list>
#include <iterator>
#include <cstddef>
#include <climits>

namespace ara {
namespace core {

namespace internal {

#ifdef __GNUC__
#ifndef ATTR_PACKED
#define APD_PACKED __attribute__((packed))
#else
// Do here what is necessary for achieving SWS_CORE_10101 for this compiler!
#define APD_PACKED
#endif
#endif

/// @brief A non-integral binary type
///
/// This is a class-based implementation. It fulfils all the requirements
/// but also allows other, non-conforming uses, in particular initialization
/// with brackets, e.g. "Byte b(42)". This is not possible with a
/// std::byte-based implementation and thus should not be used.
///
/// It is implementation-defined whether this type can be used for type aliasing
/// without triggering Undefined Behavior.
/// If in doubt, instruct your compiler to exhibit non-strict aliasing behavior
/// with something like gcc's -fno-strict-aliasing
///
/// @traceid{SWS_CORE_10100}
/// @traceid{SWS_CORE_10101}
/// @traceid{SWS_CORE_10105}
class Byte final {
    /// @traceid{SWS_CORE_10102}
    unsigned char mValue;

public:
    /// @brief Default constructor
    ///
    /// This constructor deliberately does not initialize anything, so that
    /// default-initialization leaves the instance with indeterminate value.
    /// It also deliberately is "defaulted on first declaration", so that this
    /// class does NOT have a "user-provided" default constructor, which is
    /// necessary for achieving the desired equivalence to std::byte.
    ///
    /// @traceid{SWS_CORE_10104}
    Byte() noexcept = default;

    /// @brief Converting constructor from 'unsigned char'
    ///
    /// @traceid{SWS_CORE_10103}
    /// @traceid{SWS_CORE_10106}
    constexpr explicit Byte(unsigned char value) noexcept : mValue(value) {}

    // The compiler-generated special member functions are fine
    // and would be equivalent to these:
    //
    // constexpr byte(byte const& other) noexcept = default;
    // constexpr byte(byte&& other) noexcept = default;
    // constexpr byte& operator=(byte const& other) noexcept = default;
    // constexpr byte& operator=(byte&& other) noexcept = default;
    // ~byte() noexcept = default;

    /// @brief Conversion operator to 'unsigned char'
    ///
    /// @traceid{SWS_CORE_10107}
    /// @traceid{SWS_CORE_10108}
    constexpr explicit operator unsigned char() const noexcept { return mValue; }
} APD_PACKED;

/// @traceid{SWS_CORE_10109}
constexpr bool operator==(Byte b1, Byte b2) noexcept {
    return (static_cast<unsigned char>(b1) == static_cast<unsigned char>(b2));
}

/// @traceid{SWS_CORE_10110}
constexpr bool operator!=(Byte b1, Byte b2) noexcept {
    return (static_cast<unsigned char>(b1) != static_cast<unsigned char>(b2));
}

}  // namespace internal

#if __cplusplus < 201703L
/// @traceid{SWS_CORE_04200}
using Byte = internal::Byte;
#else
/// @traceid{SWS_CORE_04200}
using Byte = std::byte;
#endif

// -------------------------------------------------------------------------

#if defined(__cpp_lib_nonmember_container_access) && (__cpp_lib_nonmember_container_access - 0) >= 201411
using std::data;
using std::size;
using std::empty;
#else
// pre C++17
/// @brief Return a pointer to the block of memory that contains the elements of a container.
/// @tparam Container  a type with a data() method
/// @param c  an instance of Container
/// @returns a pointer to the first element of the container
///
/// @traceid{SWS_CORE_04110}
template <typename Container>
constexpr auto data(Container& c) -> decltype(c.data()) {
    return c.data();
}

/// @brief Return a const_pointer to the block of memory that contains the elements of a container.
/// @tparam Container  a type with a data() method
/// @param c  an instance of Container
/// @returns a pointer to the first element of the container
///
/// @traceid{SWS_CORE_04111}
template <typename Container>
constexpr auto data(Container const& c) -> decltype(c.data()) {
    return c.data();
}

/// @brief Return a pointer to the block of memory that contains the elements of a raw array.
/// @tparam T  the type of array elements
/// @tparam N  the number of elements in the array
/// @param array  reference to a raw array
/// @returns a pointer to the first element of the array
///
/// @traceid{SWS_CORE_04112}
template <typename T, std::size_t N>
constexpr T* data(T (&array)[N]) noexcept {
    return array;
}

/// @brief Return a pointer to the block of memory that contains the elements of a std::initializer_list.
/// @tparam E  the type of elements in the std::initializer_list
/// @param il  the std::initializer_list
/// @returns a pointer to the first element of the std::initializer_list
///
/// @traceid{SWS_CORE_04113}
template <typename E>
constexpr E const* data(std::initializer_list<E> il) noexcept {
    return il.begin();
}

/// @brief Return the size of a container.
/// @tparam Container  a type with a data() method
/// @param c  an instance of Container
/// @returns the size of the container
///
/// @traceid{SWS_CORE_04120}
template <typename Container>
constexpr auto size(Container const& c) -> decltype(c.size()) {
    return c.size();
}

/// @brief Return the size of a raw array.
/// @tparam T  the type of array elements
/// @tparam N  the number of elements in the array
/// @param array  reference to a raw array
/// @returns the size of the array, i.e. N
///
/// @traceid{SWS_CORE_04121}
template <typename T, std::size_t N>
constexpr std::size_t size(T const (&array)[N]) noexcept {
    return (void)array, N;  // The comma operator is used here to ignore unused variables inside a C++11 constexpr func
}

/// @brief Return whether the given container is empty.
/// @tparam Container  a type with a empty() method
/// @param c  an instance of Container
/// @returns true if the container is empty, false otherwise
///
/// @traceid{SWS_CORE_04130}
template <typename Container>
constexpr auto empty(Container const& c) -> decltype(c.empty()) {
    return c.empty();
}

/// @brief Return whether the given raw array is empty.
///
/// As raw arrays cannot have zero elements in C++, this function
/// always returns false.
///
/// @tparam T  the type of array elements
/// @tparam N  the number of elements in the array
/// @param array  the raw array
/// @returns false
///
/// @traceid{SWS_CORE_04131}
template <typename T, std::size_t N>
constexpr bool empty(T const (&array)[N]) noexcept {
    return (void)array,
           false;  // The comma operator is used here to ignore unused variables inside a C++11 constexpr func
}

/// @brief Return whether the given std::initializer_list is empty.
/// @tparam E  the type of elements in the std::initializer_list
/// @param il  the std::initializer_list
/// @returns true if the std::initializer_list is empty, false otherwise
///
/// @traceid{SWS_CORE_04132}
template <typename E>
constexpr bool empty(std::initializer_list<E> il) noexcept {
    return il.size() == 0;
}
#endif
// In-place construction
// @traceid{SWS_CORE_04011}
struct in_place_t {
    // @traceid{SWS_CORE_04012}
    explicit in_place_t() = default;  // NOLINT (runtime/explicit)
};
// @traceid{SWS_CORE_04013}
constexpr in_place_t in_place{ };

// @traceid{SWS_CORE_04021}
template <typename T>
struct in_place_type_t {
    using type = T;

    // @traceid{SWS_CORE_04022}
    explicit in_place_type_t() = default;  // NOLINT (runtime/explicit)
};

/// @traceid{SWS_CORE_04031}
template <std::size_t I>
struct in_place_index_t {
    static constexpr size_t value = I;

    // @traceid{SWS_CORE_04032}
    explicit in_place_index_t() = default;  // NOLINT (runtime/explicit)
};

template <std::size_t I>
constexpr in_place_index_t<I> in_place_index{ };

/**
 * variable templates are only available with -std=c++14
 *
template <typename T>
constexpr in_place_type_t<T> in_place_type;
template <typename T>
constexpr in_place_index_t<T> in_place_index;
*/


/** Downported and conforming C++11 implementation of the
 *  std::conjunction helper templates.
 */
template <typename...>
struct conjunction : std::true_type {};

template <typename B1>
struct conjunction<B1> : B1 {};

template <typename B1, typename B2>
struct conjunction<B1, B2> : std::conditional<B1::value, B2, B1>::type {};

template <typename B1, typename... Bs>
struct conjunction<B1, Bs...> : std::conditional<B1::value, conjunction<Bs...>, B1>::type {};

/** Downported and conforming C++11 implementation of the
 *  std::disjunction helper templates.
 */
template <typename...>
struct disjunction : std::false_type {};

template <typename B1>
struct disjunction<B1> : B1 {};

template <typename B1, typename B2>
struct disjunction<B1, B2> : std::conditional<B1::value, B1, B2>::type {};

template <typename B1, typename... Bs>
struct disjunction<B1, Bs...> : std::conditional<B1::value, B1, disjunction<Bs...>>::type {};

}  // namespace core
}  // namespace ara

#endif  // ARA_CORE_UTILITY_H_
