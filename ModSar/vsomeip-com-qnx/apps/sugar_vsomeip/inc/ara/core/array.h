//==============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
/// @copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// The reproduction, distribution and utilization of this file as
// well as the communication of its contents to others without express
// authorization is prohibited. Offenders will be held liable for the
// payment of damages. All rights reserved in the event of the grant
// of a patent, utility model or design.
//==============================================================================

/// @file array.h
/// @brief Interface to class ara::core::array
//==============================================================================

#ifndef ARA_CORE_ARRAY_H_
#define ARA_CORE_ARRAY_H_

#include <algorithm>
#include <iterator>
#include <utility>
#include <type_traits>
#include <tuple>
#include <cstddef>

namespace ara {
namespace core {

namespace internal {

template <typename T, std::size_t N>
struct ArrayHolder final {
    using Type = T[N];

    static constexpr T const* ptr(Type const& data, std::size_t i) noexcept { return &data[i]; }

    static constexpr T* ptr(Type& data, std::size_t i) noexcept { return &data[i]; }
};

template <typename T>
struct ArrayHolder<T, 0> final {
    struct Type final { };

    static constexpr T const* ptr(Type const&, std::size_t) noexcept { return nullptr; }

    static constexpr T* ptr(Type&, std::size_t) noexcept { return nullptr; }
};

// This helper namespace basically re-implements C++17's std::is_nothrow_swappable.
// The key to this is that ADL has to be used for the swap() call within noexcept.
namespace adl {

using std::swap;

template <typename T>
struct is_nothrow_swappable : std::integral_constant<bool, noexcept(swap(std::declval<T&>(), std::declval<T&>()))> { };

} // namespace adl
} // namespace internal

/// @traceid{SWS_CORE_01201}
/// @traceid{SWS_CORE_11200}

/// @defgroup araCoreArray
/// @{
template <typename T, std::size_t N>
class Array final {
public:
    /// @brief Alias type for a reference to an element.
    ///
    /// @traceid{SWS_CORE_01210}
    using reference = T&;
    /// @brief Alias type for a const_reference to an element.
    ///
    /// @traceid{SWS_CORE_01211}
    using const_reference = T const&;
    /// @brief The type of an iterator to elements.
    ///
    /// @traceid{SWS_CORE_01212}
    using iterator = T*;
    /// @brief The type of a const_iterator to elements.
    ///
    /// @traceid{SWS_CORE_01213}
    using const_iterator = T const*;
    /// @brief Alias for the type of parameters that indicate an index into the Array.
    ///
    /// @traceid{SWS_CORE_01214}
    using size_type = std::size_t;
    /// @brief Alias for the type of parameters that indicate a difference of indexes into the Array.
    ///
    /// @traceid{SWS_CORE_01215}
    using difference_type = std::ptrdiff_t;
    /// @brief Alias for the type of elements in this Array.
    ///
    /// @traceid{SWS_CORE_01216}
    using value_type = T;
    /// @brief Alias type for a pointer to an element.
    ///
    /// @traceid{SWS_CORE_01217}
    using pointer = T*;
    /// @brief Alias type for a pointer to a const element.
    ///
    /// @traceid{SWS_CORE_01218}
    using const_pointer = T const*;
    /// @brief The type of a reverse_iterator to elements.
    ///
    /// @traceid{SWS_CORE_01219}
    using reverse_iterator = std::reverse_iterator<iterator>;
    /// @brief The type of a const_reverse_iterator to elements.
    ///
    /// @traceid{SWS_CORE_01220}
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    // no explicit construct/copy/destroy for aggregate type

    // Need to support N==0, for which we have to introduce an indirection.
    using AH = internal::ArrayHolder<T, N>;
    typename AH::Type mData;

    /// @brief Assign the given value to all elements of this Array.
    ///
    /// @param u the value
    ///
    /// @traceid{SWS_CORE_01241}
    void fill(T const& u) { std::fill(begin(), end(), u); }

    /// @brief Exchange the contents of this Array with those of other.
    ///        The noexcept specification shall make use of ADL for the swap() call.
    ///
    /// @param other the other Array
    ///
    /// @traceid{SWS_CORE_01242}
    void swap(Array<T, N>& other) noexcept(internal::adl::is_nothrow_swappable<T>::value) {
        std::swap_ranges(begin(), end(), other.begin());
    }

    // iterators:

    /// @brief Return an iterator pointing to the first element of this Array.
    ///
    /// @returns the const_iterator
    ///
    /// @traceid{SWS_CORE_01250}
    iterator begin() noexcept { return AH::ptr(mData, 0); }

    /// @brief Return a const_iterator pointing to the first element of this Array.
    ///
    /// @returns the iterator
    ///
    /// @traceid{SWS_CORE_01251}
    const_iterator begin() const noexcept { return AH::ptr(mData, 0); }

    /// @brief Return an iterator pointing past the last element of this Array.
    ///
    /// @returns the iterator
    ///
    /// @traceid{SWS_CORE_01252}
    iterator end() noexcept { return AH::ptr(mData, N); }

    /// @brief Return a const_iterator pointing past the last element of this Array.
    ///
    /// @returns the const_iterator
    ///
    /// @traceid{SWS_CORE_01253}
    const_iterator end() const noexcept { return AH::ptr(mData, N); }

    /// @brief Return a reverse_iterator pointing to the last element of this Array
    ///
    /// @returns the reverse_iterator
    ///
    /// @traceid{SWS_CORE_01254}
    reverse_iterator rbegin() noexcept { return reverse_iterator(end()); }

    /// @brief Return a const_reverse_iterator pointing to the last element of this Array.
    ///
    /// @returns the const_reverse_iterator
    ///
    /// @traceid{SWS_CORE_01255}
    const_reverse_iterator rbegin() const noexcept { return const_reverse_iterator(end()); }

    /// @brief Return a reverse_iterator pointing past the first element of this Array.
    ///
    /// @returns the reverse_iterator
    ///
    /// @traceid{SWS_CORE_01256}
    reverse_iterator rend() noexcept { return reverse_iterator(begin()); }

    /// @brief Return a const_reverse_iterator pointing past the first element of this Array.
    ///
    /// @returns the const_reverse_iterator
    ///
    /// @traceid{SWS_CORE_01257}
    const_reverse_iterator rend() const noexcept { return const_reverse_iterator(begin()); }

    /// @brief Return a const_iterator pointing to the first element of this Array.
    ///
    /// @returns the const_iterator
    ///
    /// @traceid{SWS_CORE_01258}
    const_iterator cbegin() const noexcept { return begin(); }

    /// @brief Return a const_iterator pointing past the last element of this Array.
    ///
    /// @returns the const_iterator
    ///
    /// @traceid{SWS_CORE_01259}
    const_iterator cend() const noexcept { return end(); }

    /// @brief Return a const_reverse_iterator pointing to the last element of this Array.
    ///
    /// @returns the const_reverse_iterator
    ///
    /// @traceid{SWS_CORE_01260}
    const_reverse_iterator crbegin() const noexcept { return rbegin(); }

    /// @brief Return a const_reverse_iterator pointing past the first element of this Array.
    ///
    /// @returns the const_reverse_iterator
    ///
    /// @traceid{SWS_CORE_01261}
    const_reverse_iterator crend() const noexcept { return rend(); }

    // capacity:

    /// @brief Return the number of elements in this Array.
    ///
    /// @returns the number of elements in this Array.
    ///
    /// @traceid{SWS_CORE_01262}
    constexpr size_type size() const noexcept { return N; }

    /// @brief Return the maximum number of elements supported by this Array.
    ///
    /// @returns the maximum number of elements supported by this Array.
    ///
    /// @traceid{SWS_CORE_01263}
    constexpr size_type max_size() const noexcept { return N; }

    /// @brief Return whether this Array is empty.
    ///
    /// @returns true if this Array contains 0 elements, false otherwise
    ///
    /// @traceid{SWS_CORE_01264}
    constexpr bool empty() const noexcept { return N == 0; }

    // element access:

    /// @brief Return a reference to the n-th element of this Array.
    ///
    /// @param n the index into this Array
    ///
    /// @returns the reference
    ///
    /// @traceid{SWS_CORE_01265}
    reference operator[](size_type n) { return *AH::ptr(mData, n); }

    /// @brief Return a const_reference to the n-th element of this Array.
    ///
    /// @param n the index into this Array
    ///
    /// @returns the const_reference
    ///
    /// @traceid{SWS_CORE_01266}
    constexpr const_reference operator[](size_type n) const { return *AH::ptr(mData, n); }

    /// @brief Return a reference to the first element of this Array.
    ///        The behavior of this function is undefined if the Array is empty.
    ///
    /// @returns the reference
    ///
    /// @traceid{SWS_CORE_01267}
    reference front() { return *AH::ptr(mData, 0); }

    /// @brief Return a const_reference to the first element of this Array.
    ///        The behavior of this function is undefined if the Array is empty.
    ///
    /// @returns the reference
    ///
    /// @traceid{SWS_CORE_01268}
    constexpr const_reference front() const { return *AH::ptr(mData, 0); }

    /// @brief Return a reference to the last element of this Array.
    ///        The behavior of this function is undefined if the Array is empty.
    ///
    /// @returns the reference
    ///
    /// @traceid{SWS_CORE_01269}
    reference back() { return *AH::ptr(mData, N - 1); }

    /// @brief Return a const_reference to the last element of this Array.
    ///        The behavior of this function is undefined if the Array is empty.
    ///
    /// @returns the reference
    ///
    /// @traceid{SWS_CORE_01270}
    constexpr const_reference back() const { return *AH::ptr(mData, N - 1); }

    /// @brief Return a pointer to the first element of this Array.
    ///
    /// @returns the pointer
    ///
    /// @traceid{SWS_CORE_01271}
    T* data() noexcept { return AH::ptr(mData, 0); }

    /// @brief Return a const_pointer to the first element of this Array.
    ///
    /// @returns the const_pointer
    ///
    /// @traceid{SWS_CORE_01272}
    T const* data() const noexcept { return AH::ptr(mData, 0); }
};

// comparison operators:

/// @brief Return true if the two Arrays have equal content.
///
/// @tparam T   the type of element in the Array
/// @tparam N   the number of elements in the Array
///
/// @param lhs  the left-hand side of the comparison
/// @param rhs  the right-hand side of the comparison
///
/// @returns true if the Arrays are equal, false otherwise
///
/// @traceid{SWS_CORE_01290}
template <typename T, std::size_t N>
bool operator==(Array<T, N> const& lhs, Array<T, N> const& rhs) {
    return std::equal(lhs.begin(), lhs.end(), rhs.begin());
}

/// @brief Return true if the two Arrays have non-equal content.
///
/// @tparam T   the type of element in the Array
/// @tparam N   the number of elements in the Array
///
/// @param lhs  the left-hand side of the comparison
/// @param rhs  the right-hand side of the comparison
///
/// @returns true if the Arrays are non-equal, false otherwise
///
/// @traceid{SWS_CORE_01291}
template <typename T, std::size_t N>
bool operator!=(Array<T, N> const& lhs, Array<T, N> const& rhs) {
    return !operator==(lhs, rhs);
}

/// @brief Return true if the contents of lhs are lexicographically less than the
///        contents of rhs.
///
/// @tparam T   the type of element in the Array
/// @tparam N   the number of elements in the Array
///
/// @param lhs  the left-hand side of the comparison
/// @param rhs  the right-hand side of the comparison
///
/// @returns true if lhs is less than rhs, false otherwise
///
/// @traceid{SWS_CORE_01292}
template <typename T, std::size_t N>
bool operator<(Array<T, N> const& lhs, Array<T, N> const& rhs) {
    return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

/// @brief Return true if the contents of rhs are lexicographically less than the
///        contents of lhs.
///
/// @tparam T   the type of element in the Array
/// @tparam N   the number of elements in the Array
///
/// @param lhs  the left-hand side of the comparison
/// @param rhs  the right-hand side of the comparison
///
/// @returns true if rhs is less than lhs, false otherwise
///
/// @traceid{SWS_CORE_01293}
template <typename T, std::size_t N>
bool operator>(Array<T, N> const& lhs, Array<T, N> const& rhs) {
    return rhs < lhs;
}

/// @brief Return true if the contents of lhs are lexicographically less than
///         or equal to the contents of rhs.
///
/// @tparam T   the type of element in the Array
/// @tparam N   the number of elements in the Array
///
/// @param lhs  the left-hand side of the comparison
/// @param rhs  the right-hand side of the comparison
///
/// @returns true if lhs is less than or equal to rhs, false otherwise
///
/// @traceid{SWS_CORE_01294}
template <typename T, std::size_t N>
bool operator<=(Array<T, N> const& lhs, Array<T, N> const& rhs) {
    return !(rhs < lhs);
}

/// @brief Return true if the contents of rhs are lexicographically less than
///        or euqal to the contents of lhs.
///
/// @tparam T   the type of element in the Array
/// @tparam N   the number of elements in the Array
///
/// @param lhs  the left-hand side of the comparison
/// @param rhs  the right-hand side of the comparison
///
/// @returns true if rhs is less than or equal to lhs, false otherwise
///
/// @traceid{SWS_CORE_01295}
template <typename T, std::size_t N>
bool operator>=(Array<T, N> const& lhs, Array<T, N> const& rhs) {
    return !(lhs < rhs);
}

/// @brief Overload of std::swap for ara::core::Array.
///
/// @tparam T   the type of element in the Array
/// @tparam N   the number of elements in the Array
///
/// @param lhs  the left-hand side of the comparison
/// @param rhs  the right-hand side of the comparison
///
/// @traceid{SWS_CORE_01296}
template <typename T, std::size_t N>
void swap(Array<T, N>& lhs, Array<T, N>& rhs) noexcept(noexcept(lhs.swap(rhs))) {
    lhs.swap(rhs);
}

// tuple interface (1/2)
// The C++14 standard prohibits extension of the std namespace with new overloads,
// so we need to put them into our own namespace and rely on ADL to have them found.

/// @brief Overload of std::get for an lvalue mutable ara::core::Array.
///        The implementation shall flag the condition I >= N as a compile error.
///
/// @tparam I  the index into the Array whose element is desired
/// @tparam T  the type of element in the Array
/// @tparam N  the number of elements in the Array
///
/// @param a  the Array
///
/// @returns  a reference to the Ith element of the Array
///
/// @traceid{SWS_CORE_01282}
template <std::size_t I, typename T, std::size_t N>
constexpr T& get(Array<T, N>& a) noexcept {
    static_assert(I < N, "index out of bounds");
    return a[I];
}

/// @brief Overload of std::get for an rvalue ara::core::Array.
///        The implementation shall flag the condition I >= N as a compile error.
///
/// @tparam I  the index into the Array whose element is desired
/// @tparam T  the type of element in the Array
/// @tparam N  the number of elements in the Array
///
/// @param a  the Array
///
/// @returns  an rvalue reference to the Ith element of the Array
///
/// @traceid{SWS_CORE_01283}
template <std::size_t I, typename T, std::size_t N>
constexpr T&& get(Array<T, N>&& a) noexcept {
    return std::move(get<I>(a));
}

/// @brief Overload of std::get for an lvalue const ara::core::Array.
///        The implementation shall flag the condition I >= N as a compile error.
///
/// @tparam I  the index into the Array whose element is desired
/// @tparam T  the type of element in the Array
/// @tparam N  the number of elements in the Array
///
/// @param a  the Array
///
/// @returns  a const_reference to the Ith element of the Array
///
/// @traceid{SWS_CORE_01284}
template <std::size_t I, typename T, std::size_t N>
constexpr T const& get(Array<T, N> const& a) noexcept {
    static_assert(I < N, "index out of bounds");
    return a[I];
}

/// @}
} // namespace core
} // namespace ara

// tuple interface (2/2)
// Specialization of these symbols in the std namespace is permitted in C++14 by 17.6.4.2.1 [namespace.std],
// because they depend on a user-defined type (i.e. ara::core::Array).

namespace std {

/// @brief Specialization of std::tuple_size for ara::core::Array.
///        This specialization shall meet the C++14 UnaryTypeTrait requirements with a Base
///        Characteristic of std::integral_constant<std::size_t, N>.
///
/// @tparam T  the type of element in the Array
/// @tparam N  the number of elements in the Array
///
/// @traceid{SWS_CORE_01280}
template <typename T, size_t N>
struct tuple_size<ara::core::Array<T, N>> : integral_constant<size_t, N> { };

/// @brief Specialization of std::tuple_element for ara::core::Array.
///        The implementation shall flag the condition I >= N as a compile error.
///
/// @tparam I  the index into the Array whose element is desired
/// @tparam T  the type of element in the Array
/// @tparam N  the number of elements in the Array
///
/// @traceid{SWS_CORE_01281}
template <size_t I, typename T, size_t N>
struct tuple_element<I, ara::core::Array<T, N>> {
    /// @brief Alias for the type of the Array element with the given index.
    ///
    /// @traceid{SWS_CORE_01285}
    using type = T;
};

} // namespace std

#endif // ARA_CORE_ARRAY_H_
