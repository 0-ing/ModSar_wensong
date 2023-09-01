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

/// @file span.h
/// @brief A view over a contiguous sequence of objects, the storage of which is owned by another object.
//========================================================================================================

#ifndef ARA_CORE_SPAN_H_
#define ARA_CORE_SPAN_H_

#include <iostream>
#include <type_traits>
#include <cstddef>
#include <cassert>
#include <limits>
#include <algorithm>
#include <iterator>
#include <array>

#include "ara/core/array.h"
#include "ara/core/utility.h"

namespace ara {
namespace core {

/// @brief A constant for creating Spans with dynamic sizes
///
/// The constant is always set to std::numeric_limits<std::size_t>::max().
///
/// @traceid{SWS_CORE_01901}
constexpr std::size_t dynamic_extent = std::numeric_limits<std::size_t>::max();

template <typename T, std::size_t Extent>
class Span;

namespace internal {

// Re-implementation of std::remove_cvref from C++20.
template <typename T>
struct remove_cvref {
    using type = std::remove_cv_t<std::remove_reference_t<T>>;
};

// Re-implementation of std::remove_cvref_t from C++20.
template <typename T>
using remove_cvref_t = typename remove_cvref<T>::type;

// Re-implementation of std::void_t from C++20.
// We assume that the compiler implements CWG defect 1558.
template <typename...>
using void_t = void;

template <typename T>
struct is_ara_core_span_checker : public std::false_type {};

template <typename T, std::size_t Extent>
struct is_ara_core_span_checker<core::Span<T, Extent>> : public std::true_type {};

template <typename T>
struct is_ara_core_span : public is_ara_core_span_checker<remove_cvref_t<T>> {};

template <typename T>
struct is_ara_core_array_checker : public std::false_type {};

template <typename T, std::size_t N>
struct is_ara_core_array_checker<core::Array<T, N>> : public std::true_type {};

template <typename T>
struct is_ara_core_array : public is_ara_core_array_checker<remove_cvref_t<T>> {};

template <typename, typename = size_t>
struct is_complete : std::false_type {};

template <typename T>
struct is_complete<T, decltype(sizeof(T))> : std::true_type {};

template <typename T>
struct is_std_array_checker : public std::false_type {};

template <typename T, std::size_t N>
struct is_std_array_checker<std::array<T, N>> : public std::true_type {};

template <typename T>
struct is_std_array : public is_std_array_checker<remove_cvref_t<T>> {};

template <typename, typename, typename, typename = void>
struct is_suitable_container : public std::false_type {};

template <typename C, typename ArgT, typename ElementType>
struct is_suitable_container<C, ArgT, ElementType,
    void_t<                                                       //
        std::enable_if_t<!is_ara_core_span<C>::value>,  //
        std::enable_if_t<!is_ara_core_array<C>::value>, //
        std::enable_if_t<!is_std_array<C>::value>,      //
        std::enable_if_t<!std::is_array<C>::value>,               //
        decltype(core::data(std::declval<ArgT>())),               //
        decltype(core::size(std::declval<ArgT>())),               //
        std::enable_if_t<std::is_convertible<std::remove_pointer_t<decltype(core::data(std::declval<ArgT>()))> (*)[],
                                             ElementType (*)[]>::value> // NOLINT(whitespace/parens)
        > //
    > : public std::true_type {};

}  // namespace internal

/// @brief A view over a contiguous sequence of objects
/// @tparam T  the type of elements in the Span
/// @tparam Extent  the extent to use for this Span
///
/// @traceid{SWS_CORE_01900}
template <typename T, std::size_t Extent = dynamic_extent>
class Span {
    static_assert(std::is_object<T>::value, "Span cannot contain reference or void types");
    static_assert(!std::is_abstract<T>::value, "Span cannot contain abstract types");
    static_assert(internal::is_complete<T>::value, "Span cannot contain incomplete types");

    template <typename U>
    using type_of_data = decltype(ara::core::data(std::declval<U>()));

public:
    /// @brief Alias for the type of elements in this Span
    ///
    /// @traceid{SWS_CORE_01911}
    using element_type = T;
    /// @brief Alias for the type of values in this Span
    ///
    /// @traceid{SWS_CORE_01912}
    using value_type = typename std::remove_cv<element_type>::type;
    /// @brief Alias for the type of parameters that indicate a difference of indexes into the Span
    ///
    /// @traceid{SWS_CORE_01914}
    using difference_type = std::ptrdiff_t;
    /// @brief Alias type for a pointer to an element
    ///
    /// @traceid{SWS_CORE_01915}
    using pointer = element_type*;

    /// @brief Alias type for a reference to an element
    ///
    /// @traceid{SWS_CORE_01916}
    using reference = element_type&;

    /// @brief The type of an iterator to elements
    ///
    /// This iterator shall implement the concepts RandomAccessIterator,
    /// ContiguousIterator, and ConstexprIterator.
    ///
    /// @traceid{SWS_CORE_01917}
    using iterator = element_type*;

    /// @brief The type of a const_iterator to elements
    ///
    /// This iterator shall implement the concepts RandomAccessIterator,
    /// ContiguousIterator, and ConstexprIterator.
    ///
    /// @traceid{SWS_CORE_01918}
    using const_iterator = element_type const*;

    /// @brief The type of a reverse_iterator to elements
    ///
    /// @traceid{SWS_CORE_01919}
    using reverse_iterator = std::reverse_iterator<iterator>;

    /// @brief The type of a const_reverse_iterator to elements
    ///
    /// @traceid{SWS_CORE_01920}
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    // Not in C++ standard, but we need it for GMock's IsSize()

    /// @brief Alias for the type of parameters that indicate a size or a number of values
    ///
    /// @traceid{SWS_CORE_01921}
    using size_type = std::size_t;

    /// @brief A constant reflecting the configured Extent of this Span
    ///
    /// @traceid{SWS_CORE_01931}
    static constexpr size_type extent = Extent;

    // 21.7.3.2, constructors, copy, and assignment

    /// @brief Default constructor
    ///
    /// This constructor shall not participate in overload resolution unless Extent <= 0 is true.
    ///
    /// @traceid{SWS_CORE_01941}
    template <typename U = void, typename = typename std::enable_if<Extent == dynamic_extent || Extent == 0, U>::type>
    constexpr Span() noexcept : mData(nullptr), mExtent(0) {}

    /// @brief Construct a new Span from the given pointer and size
    ///
    /// [ptr, ptr + count) shall be a valid range.
    /// If @a Extent is not equal to @a dynamic_extent, then @a count shall be equal to @a Extent.
    ///
    /// @param ptr  the pointer
    /// @param count  the number of elements to take from @a ptr
    ///
    /// @traceid{SWS_CORE_01942}
    Span(pointer ptr, size_type count) : mData(ptr), mExtent(count) {
        if (Extent != dynamic_extent && count != Extent) {
            assert(!"inconsistent extent");
        }
    }

    /// @brief Construct a new Span from the open range between [firstElem, lastElem).
    ///
    /// [first, last) shall be a valid range.
    /// If @ extent is not equal to @a dynamic_extent, then (@a last - @a first) shall be equal to @a Extent.
    ///
    /// @param firstElem  pointer to the first element
    /// @param lastElem  pointer to past the last element
    ///
    /// @traceid{SWS_CORE_01943}
    Span(pointer firstElem, pointer lastElem) : Span(firstElem, lastElem - firstElem) {
        assert(std::distance(firstElem, lastElem) >= 0);
    }

    /// @brief Construct a new Span from the given raw array.
    ///
    /// This constructor shall not participate in overload resolution unless:
    ///     - Extent == dynamic_extent || N == Extent is true, and
    ///     - std::remove_pointer<decltype(ara::core::data(arr))>::type(*)[] is convertible to T(*)[].
    ///
    /// @tparam N  the size of the raw array
    /// @param arr  the raw array
    ///
    /// @traceid{SWS_CORE_01944}
    template <std::size_t N,
              typename = typename std::enable_if<
                  (Extent == dynamic_extent || Extent == N)
                  && std::is_convertible<typename std::remove_pointer<type_of_data<element_type (&)[N]>>::type(*)[],
                                         element_type(*)[]>::value>::type>
    constexpr Span(element_type (&arr)[N]) noexcept : Span(std::addressof(arr[0]), N) {} // NOLINT(runtime/explicit)

    /// @brief Construct a new Span from the given Array.
    ///
    /// This constructor shall not participate in overload resolution unless:
    ///     - Extent == dynamic_extent || N == Extent is true, and
    ///     - std::remove_pointer<decltype(ara::core::data(arr))>::type(*)[] is convertible to T(*)[].
    ///
    /// @tparam N  the size of the Array
    /// @param arr  the array
    ///
    /// @traceid{SWS_CORE_01945}
    template <typename U,
              std::size_t N,
              typename = typename std::enable_if<(extent == dynamic_extent || extent == N)
                                                 && std::is_convertible<
                                                 typename std::remove_pointer_t<decltype(std::declval<Array<U, N>>().data())> (*)[],
                                                     element_type (*)[]>::value>::type> // NOLINT(whitespace/parens)
    constexpr Span(Array<U, N> & arr) noexcept // NOLINT(runtime/explicit)
        : Span(arr.data(), N) {}

    /// @brief Construct a new Span from the given const Array.
    ///
    /// This constructor shall not participate in overload resolution unless:
    ///     - Extent == dynamic_extent || N == Extent is true, and
    ///     - std::remove_pointer<decltype(ara::core::data(arr))>::type(*)[] is convertible to T(*)[].
    ///
    /// @tparam N  the size of the Array
    /// @param arr  the array
    ///
    /// @traceid{SWS_CORE_01946}
    template <typename U,
              std::size_t N,
              typename = typename std::enable_if<(extent == dynamic_extent || extent == N)
                                                 && std::is_convertible<
                                                 typename std::remove_pointer_t<decltype(std::declval<Array<U, N> const>().data())> (*)[],
                                                     element_type (*)[]>::value>::type> // NOLINT(whitespace/parens)
    constexpr Span(Array<U, N> const& arr) noexcept // NOLINT(runtime/explicit)
        : Span(arr.data(), N) {}

    /// @brief Construct a new Span from the given container.
    ///
    /// [ara::core::data(cont), ara::core::data(cont) + ara::core::size(cont)) shall be a valid range.
    /// If @a Extent is not equal to @a dynamic_extent, then ara::core::size(cont) shall be equal to @a Extent.
    ///
    /// These constructors shall not participate in overload resolution unless:
    ///     - Container is not a specialization of Span,
    ///     - Container is not a specialization of Array,
    ///     - std::is_array<Container>::value is false,
    ///     - ara::core::data(cont) and ara::core::size(cont) are both well-formed, and
    ///     - std::remove_pointer<decltype(ara::core::data(cont))>::type(*)[] is convertible to T(*)[].
    ///
    /// @tparam Container  the type of container
    /// @param cont  the container
    ///
    /// @traceid{SWS_CORE_01947}
    template <typename Container,
              typename = typename std::enable_if<
              (extent == dynamic_extent)
              && internal::is_suitable_container<Container, Container&, element_type>::value>::type>
    constexpr Span(Container & cont) // NOLINT(runtime/explicit)
        : Span(core::data(cont), core::size(cont)) {}

    /// @brief Construct a new Span from the given const container.
    ///
    /// [ara::core::data(cont), ara::core::data(cont) + ara::core::size(cont)) shall be a valid range.
    /// If @a Extent is not equal to @a dynamic_extent, then ara::core::size(cont) shall be equal to @a Extent.
    ///
    /// These constructors shall not participate in overload resolution unless:
    ///     - Container is not a specialization of Span,
    ///     - Container is not a specialization of Array,
    ///     - std::is_array<Container>::value is false,
    ///     - ara::core::data(cont) and ara::core::size(cont) are both well-formed, and
    ///     - std::remove_pointer<decltype(ara::core::data(cont))>::type(*)[] is convertible to T(*)[].
    ///
    /// @tparam Container  the type of container
    /// @param cont  the container
    ///
    /// @traceid{SWS_CORE_01948}
    template <typename Container,
              typename = typename std::enable_if<
              (extent == dynamic_extent)
              && internal::is_suitable_container<Container, Container const&, element_type>::value>::type>
    constexpr Span(Container const& cont) // NOLINT(runtime/explicit)
        : Span(core::data(cont), core::size(cont)) {}

    /// @brief Copy construct a new Span from another instance
    /// @param other  the other instance
    ///
    /// @traceid{SWS_CORE_01949}
    constexpr Span(Span const& other) noexcept = default;

    /// @brief Converting constructor
    ///
    /// This ctor allows assignment of a cv-Span<> from a normal Span<>,
    /// and also of a dynamic_extent-Span<> from a static extent-one.
    ///
    /// @tparam U  the type of elements within the other Span
    /// @tparam N  the Extent of the other Span
    /// @param s  the other Span instance
    ///
    /// @traceid{SWS_CORE_01950}
    template <typename U,
              std::size_t N,
              typename = typename std::enable_if<(Extent == dynamic_extent || Extent == N)
                                                 && std::is_convertible<U(*)[], element_type(*)[]>::value>::type*>
    constexpr Span(Span<U, N> const& s) noexcept : Span(s.data(), s.size()) {}

    /// @brief Destructor
    ///
    /// @traceid{SWS_CORE_01951}
    ~Span() noexcept = default;

    // Not "constexpr" because that would make it also "const" on C++11 compilers.
    /// @brief Copy assignment operator
    /// @param other  the other instance
    /// @returns *this
    ///
    /// @traceid{SWS_CORE_01952}
    Span& operator=(Span const& other) noexcept = default;

    // 21.7.3.3, subviews

    /// @brief Return a subspan containing only the first elements of this Span.
    /// @tparam Count  the number of elements to take over
    /// @returns the subspan
    ///
    /// @traceid{SWS_CORE_01961}
    template <std::size_t Count>
    constexpr Span<element_type, Count> first() const {
        static_assert(0 <= Count, "subview size cannot be negative");
        static_assert(Count <= Extent, "Span::first out of bounds");
        assert(Count <= size());

        return { mData, Count };
    }

    /// @brief Return a subspan containing only the first elements of this Span.
    /// @param count  the number of elements to take over
    /// @returns the subspan
    ///
    /// @traceid{SWS_CORE_01962}
    constexpr Span<element_type, dynamic_extent> first(size_type count) const {
        assert(count <= size());
        return { mData, count };
    }

    /// @brief Return a subspan containing only the last elements of this Span.
    /// @tparam Count  the number of elements to take over
    /// @returns the subspan
    ///
    /// @traceid{SWS_CORE_01963}
    template <std::size_t Count>
    constexpr Span<element_type, Count> last() const {
        static_assert(0 <= Count, "subview size cannot be negative");
        static_assert(Count <= Extent, "Span::first out of bounds");
        assert(Count <= size());

        return { mData + (size() - Count), Count };
    }

    /// @brief Return a subspan containing only the last elements of this Span.
    /// @param count  the number of elements to take over
    /// @returns the subspan
    ///
    /// @traceid{SWS_CORE_01964}
    constexpr Span<element_type, dynamic_extent> last(size_type count) const {
        assert(count <= size());
        return { mData + (size() - count), count };
    }

    /// @brief Return a subspan of this Span.
    ///
    /// The second template argument of the returned Span type is:
    ///
    /// Count != dynamic_extent ? Count: (Extent != dynamic_extent ? Extent - Offset: dynamic_extent)
    ///
    /// @tparam Offset  offset into this Span from which to start
    /// @tparam Count  the number of elements to take over
    /// @returns the subspan
    ///
    /// @traceid{SWS_CORE_01965}
    template <std::size_t Offset, std::size_t Count = dynamic_extent>
    constexpr auto subspan() const
        -> Span<element_type,
                (Count != dynamic_extent) ? Count : (Extent != dynamic_extent ? Extent - Offset : dynamic_extent)
                > {
        static_assert(Offset <= Extent && (Count == dynamic_extent || Count <= Extent - Offset),
                      "Span::subspan out of bounds");
        assert(Offset <= size());
        assert(Count == dynamic_extent || (Count <= size() - Offset));

        constexpr size_type E
            = (Count != dynamic_extent) ? Count : (Extent != dynamic_extent ? Extent - Offset : dynamic_extent);

        return Span<element_type, E>(mData + Offset, Count != dynamic_extent ? Count : size() - Offset);
    }

    /// @brief Return a subspan of this Span.
    /// @param offset  offset into this Span from which to start
    /// @param count  the number of elements to take over
    /// @returns the subspan
    ///
    /// @traceid{SWS_CORE_01966}
    constexpr Span<element_type, dynamic_extent> subspan(size_type offset, size_type count = dynamic_extent) const {
        assert(offset <= size());
        assert(count == dynamic_extent || (count <= size() - offset));

        return { mData + offset, count == dynamic_extent ? size() - offset : count };
    }

    // 21.7.3.4, observers

    /// @brief Return the size of this Span.
    /// @returns the number of elements contained in this Span
    ///
    /// @traceid{SWS_CORE_01967}
    constexpr size_type size() const noexcept { return mExtent; }

    /// @brief Return the size of this Span in bytes.
    /// @returns the number of bytes covered by this Span
    ///
    /// @traceid{SWS_CORE_01968}
    constexpr size_type size_bytes() const noexcept { return mExtent * sizeof(T); }

    /// @brief Return whether this Span is empty.
    /// @returns true if this Span contains 0 elements, false otherwise
    ///
    /// @traceid{SWS_CORE_01969}
    constexpr bool empty() const noexcept { return mExtent == 0; }

    // 21.7.3.5, element access

    /// @brief Return a reference to the n-th element of this Span.
    /// @param idx  the index into this Span
    /// @returns the reference
    ///
    /// @traceid{SWS_CORE_01970}
    constexpr reference operator[](size_type idx) const { return mData[idx]; }

    /// @brief Return a pointer to the start of the memory block covered by this Span.
    /// @returns the pointer
    ///
    /// @traceid{SWS_CORE_01971}
    constexpr pointer data() const noexcept { return mData; }

    // 21.7.3.6, iterator support

    /// @brief Return an iterator pointing to the first element of this Span.
    /// @returns the iterator
    ///
    /// @traceid{SWS_CORE_01972}
    constexpr iterator begin() const noexcept { return &mData[0]; }

    /// @brief Return an iterator pointing past the last element of this Span.
    /// @returns the iterator
    ///
    /// @traceid{SWS_CORE_01973}
    constexpr iterator end() const noexcept { return &mData[mExtent]; }

    /// @brief Return a const_iterator pointing to the first element of this Span.
    /// @returns the const_iterator
    ///
    /// @traceid{SWS_CORE_01974}
    constexpr const_iterator cbegin() const noexcept { return &mData[0]; }

    /// @brief Return a const_iterator pointing past the last element of this Span.
    /// @returns the const_iterator
    ///
    /// @traceid{SWS_CORE_01975}
    constexpr const_iterator cend() const noexcept { return &mData[mExtent]; }

    /// @brief Return a reverse_iterator pointing to the last element of this Span.
    /// @returns the reverse_iterator
    ///
    /// @traceid{SWS_CORE_01976}
    constexpr reverse_iterator rbegin() const noexcept { return reverse_iterator(end()); }

    /// @brief Return a reverse_iterator pointing past the first element of this Span.
    /// @returns the reverse_iterator
    ///
    /// @traceid{SWS_CORE_01977}
    constexpr reverse_iterator rend() const noexcept { return reverse_iterator(begin()); }

    /// @brief Return a const_reverse_iterator pointing to the last element of this Span.
    /// @returns the const_reverse_iterator
    ///
    /// @traceid{SWS_CORE_01978}
    constexpr const_reverse_iterator crbegin() const noexcept { return const_reverse_iterator(end()); }

    /// @brief Return a const_reverse_iterator pointing past the first element of this Span.
    /// @returns the reverse_iterator
    ///
    /// @traceid{SWS_CORE_01979}
    constexpr const_reverse_iterator crend() const noexcept { return const_reverse_iterator(begin()); }

private:
    pointer mData;
    size_type mExtent;
};

// C++17 deduction guides
#if defined(__cpp_deduction_guides) && (__cpp_deduction_guides - 0) >= 201703L
template <typename T, std::size_t N>
Span(T (&)[N]) -> Span<T, N>;

template <typename T, std::size_t N>
Span(Array<T, N>&) -> Span<T, N>;

template <typename T, std::size_t N>
Span(Array<T, N> const&) -> Span<T const, N>;

template <typename Container>
Span(Container&) -> Span<typename Container::value_type>;

template <typename Container>
Span(Container const&) -> Span<const typename Container::value_type>;
#endif // C++17 deduction guides

/// @brief Create a new Span from the given pointer and size
/// @tparam T  the type of elements
/// @param ptr  the pointer
/// @param count  the number of elements to take from @a ptr
/// @returns the new Span
///
/// @traceid{SWS_CORE_01990}
template <typename T>
constexpr Span<T> MakeSpan(T* ptr, typename Span<T>::size_type count) {
    return Span<T>(ptr, count);
}

/// @brief Create a new Span from the open range between [firstElem, lastElem).
/// @tparam T  the type of elements
/// @param firstElem  pointer to the first element
/// @param lastElem  pointer to past the last element
/// @returns the new Span
///
/// @traceid{SWS_CORE_01991}
template <typename T>
constexpr Span<T> MakeSpan(T* firstElem, T* lastElem) {
    return Span<T>(firstElem, lastElem);
}

/// @brief Create a new Span from the given raw array.
/// @tparam T  the type of elements
/// @tparam N  the size of the raw array
/// @param arr  the raw array
/// @returns the new Span
///
/// @traceid{SWS_CORE_01992}
template <typename T, std::size_t N>
constexpr Span<T, N> MakeSpan(T (&arr)[N]) noexcept {
    return Span<T, N>(arr);
}

/// @brief Create a new Span from the given container.
/// @tparam Container  the type of container
/// @param cont  the container
/// @returns the new Span
///
/// @traceid{SWS_CORE_01993}
template <typename Container>
constexpr Span<typename Container::value_type> MakeSpan(Container& cont) {
    return Span<typename Container::value_type>(cont);
}

/// @brief Create a new Span from the given const container.
/// @tparam Container  the type of container
/// @param cont  the container
/// @returns the new Span
///
/// @traceid{SWS_CORE_01994}
template <typename Container>
constexpr Span<typename Container::value_type const> MakeSpan(Container const& cont) {
    return Span<typename Container::value_type const>(cont);
}

/// @brief Return a read-only Span<Byte> over the object representation of the input Span<T>
/// @tparam T  the type of elements
/// @tparam Extent  the size of the raw array
/// @param s  the Span<T> instance
/// @returns a Span<const Byte>
///
/// @traceid{SWS_CORE_01980}
template <typename T, std::size_t Extent>
Span<const Byte, Extent == dynamic_extent ? dynamic_extent : sizeof(T) * Extent> as_bytes(Span<T, Extent> s) noexcept {
    return { reinterpret_cast<const Byte*>(s.data()), s.size_bytes() };
}

/// @brief Return a writable Span<Byte> over the object representation of the input Span<T>
/// @tparam T  the type of elements
/// @tparam Extent  the size of the raw array
/// @param s  the Span<T> instance
/// @returns a Span<Byte>
///
/// @traceid{SWS_CORE_01981}
template <typename T, std::size_t Extent>
Span<Byte, Extent == dynamic_extent ? dynamic_extent : sizeof(T) * Extent>
as_writable_bytes(Span<T, Extent> s) noexcept {
    return { reinterpret_cast<Byte*>(s.data()), s.size_bytes() };
}

}  // namespace core
}  // namespace ara

#endif  // ARA_CORE_SPAN_H_
