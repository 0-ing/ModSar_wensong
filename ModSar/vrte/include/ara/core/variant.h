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

/// @file variant.h
/// @brief A type-safe union.
//==============================================================================

#ifndef ARA_CORE_VARIANT_H_
#define ARA_CORE_VARIANT_H_

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <utility>

#include "ara/core/utility.h"
#include "ara/core/internal/variant_internal.hpp"

namespace ara {
namespace core {
namespace internal {

/**
 * std::max is not constexpr in c++11, c++14 could be used instead
 **/
template <typename T>
constexpr T max(const T& a) {
    return a;
}
template <typename T>
constexpr T max(const T& a, const T& b) {
    return (b < a) ? a : b;
}
template <typename T, typename... Targs>
constexpr T max(const T& a, const T& b, const Targs&... args) {
    return max(max(a, b), args...);
}

}  // namespace internal

/// @brief value which an invalid variant index occupies
/// @code
///     ara::core::Variant<int, float> someVariant;
///
///     // every unset variant has an invalid variant in the beginning
///     if ( someVariant.index() == INVALID_VARIANT_INDEX ) ...
///
///     ara::core::Variant<int, float> someVariant2(ara::core::in_place_type<int>, 12);
///
///     // variant with setted value therefore the index is not invalid
///     if ( someVariant.index() != INVALID_VARIANT_INDEX ) ...
/// @endcode
static constexpr std::size_t INVALID_VARIANT_INDEX = std::size_t(-1);

/// @brief Variant implementation from the C++17 standard with C++11. The
///         interface is inspired by the C++17 standard but it has changes in
///         get and emplace since we are not allowed to throw exceptions.
/// @param Types... variadic list of types which the variant should be able to store
///
/// @code
///     #include "ara/core/variant.h"
///     #include <iostream>
///
///     ara::core::Variant<int, float, double> someVariant;
///
///     // ... do stuff
///
///     if ( someVariant.index() == INVALID_VARIANT_INDEX )
///     {
///         someVariant.emplace<float>(123.456f);
///     }
///     else if ( someVariant.index() == 1)
///     {
///         auto blubb = someVariant.template get_at_index<1>();
///         std::cout << *blubb << std::endl;
///
///         auto sameAsBlubb = someVariant.get<float>();
///         std::cout << *sameAsBlubb << std::endl;
///     }
///
///     // .. do stuff
///
///     int defaultValue = 123;
///     int * fuu = someVariant.get_if<int>(&defaultValue);
///     std::cout << *fuu << std::endl;
///
/// @endcode

/// @traceid{SWS_CORE_01601}
template <typename... Types>
class Variant {
private:
    /// @brief contains the size of the largest element
    static constexpr std::size_t TYPE_SIZE = internal::max(sizeof(Types)...);

public:
    /// @brief the default constructor constructs a variant which does not contain
    ///     an element and returns INVALID_VARIANT_INDEX when .index() is called
    Variant() = default;

    /// @brief creates a variant and performs an in place construction of the type
    ///         stored at index N. If the index N is out of bounds you get a compiler
    ///         error.
    /// @param[in] index index of the type which should be constructed
    /// @param[in] args variadic list of arguments which will be forwarded to the constructor to
    ///                 the type at index
    template <std::size_t N, typename... CTorArguments>
    Variant(const in_place_index_t<N>& index, CTorArguments&&... args) noexcept;  // NOLINT (runtime/explicit)

    /// @brief creates a variant and performs an in place construction of the class
    ///         stored at index ClassIndex with initializer_list f_inir. If the index N is out of bounds
    ///         you get a compiler error.
    /// @param[in] index index of the type which should be constructed
    /// @param[in] f_inir initialization list to construct the class at index
    /// @param[in] f_args variadic list of arguments which will be forwarded to the constructor to
    ///                 the class
    template <std::size_t ClassIndex, class U, class... CTorArguments>
    explicit Variant(in_place_index_t<ClassIndex> index, std::initializer_list<U> f_inir, CTorArguments&&... f_args);

    /// @brief creates a variant and performs an in place construction of the type T.
    ///         If T is not part of the variant you get a compiler error.
    /// @param[in] type type which should be created inside the variant
    /// @param[in] args variadic list of arguments which will be forwarded to the constructor to
    ///                 the type
    template <typename T, typename... CTorArguments>
    Variant(const in_place_type_t<T>& type, CTorArguments&&... args) noexcept;  // NOLINT (runtime/explicit)

    /// @brief creates a variant and performs an in place construction of the class
    ///        T with initializer_list f_inir. If T is not part of the variant you get
    ///        a compiler error.
    /// @param[in] T class which should be constructed
    /// @param[in] f_inir initialization list to construct the class T
    /// @param[in] f_args variadic list of arguments which will be forwarded to the constructor to
    ///                 the class
    template <class T, class U, class... CTorArguments>
    explicit Variant(in_place_type_t<T>, std::initializer_list<U> f_inir, CTorArguments&&... f_args);

    /// @brief if the variant contains an element the elements copy constructor is called
    ///     otherwise an empty variant is copied
    /// @param[in] rhs source of the copy
    Variant(const Variant& rhs) noexcept;

    /// @brief if the variant contains an element the elements copy assignment operator is called
    ///     otherwise an empty variant is copied
    /// @param[in] rhs source of the copy assignment
    /// @return reference to the variant itself
    Variant& operator=(const Variant& rhs) noexcept;

    /// @brief if the variant contains an element the elements move constructor is called
    ///     otherwise an empty variant is moved
    /// @param[in] rhs source of the move
    Variant(Variant&& rhs) noexcept;

    /// @brief if the variant contains an element the elements move assignment operator is called
    ///     otherwise an empty variant is moved
    /// @param[in] rhs source of the move assignment
    /// @return reference to the variant itself
    Variant& operator=(Variant&& rhs) noexcept;

    /// @brief if the variant contains an element the elements destructor is called otherwise
    ///         nothing happens
    ~Variant() noexcept;

    /// @brief The converting constructor uses the universal reference templated  type T&&,
    ///        which is then resolved to find a direct match inside <Types...>, or possible
    ///        overloads for each T_j are constructed using an iterative functor and then
    ///        resolved to find the best match for T in <Types...>. Failure to resolve will
    ///        throw a compile time error, nothrow guarantee at runtime.
    /// @param[in] rhs source object of type T
    template <typename T,
              typename U = internal::T_detail<T, Types...>,
              typename Enable
              = typename std::enable_if<U::T_valid && !std::is_same<Variant<Types...>, typename U::T_val>::value>::type>
    Variant(T&& rhs) noexcept(std::is_nothrow_constructible<typename U::T_varType, T&&>::value);  // NOLINT (runtime/explicit)

    /// @brief if the variant contains an element the elements assignment operator is called otherwise
    ///         we have undefined behavior. It is important that you make sure that the variant really
    ///         contains that type T.
    /// @param[in] rhs source object for the underlying move assignment
    /// @return reference to the variant itself
    template <typename T>
    typename std::enable_if<!std::is_same<T, Variant<Types...>&>::value, Variant<Types...>>::type&
    operator=(T&& rhs) noexcept;

    /// @brief forward parameters to emplace_at_index()
    /// @param TypeIndex index of the type which will be created
    /// @param[in] args arguments which will be forwarded to the constructor to the type at TypeIndex
    template <std::size_t TypeIndex, typename... CTorArguments>
    void emplace(CTorArguments&&... args) noexcept;

    /// @brief calls the constructor of the type at index TypeIndex and perfectly forwards the arguments
    ///         to this constructor. (not stl compliant)
    /// @param TypeIndex index of the type which will be created
    /// @param[in] args arguments which will be forwarded to the constructor to the type at TypeIndex
    template <std::size_t TypeIndex, typename... CTorArguments>
    void emplace_at_index(CTorArguments&&... args) noexcept;

    /// @brief calls the constructor of the type T and perfectly forwards the arguments
    ///         to the constructor of T.
    template <typename T, typename... CTorArguments>
    void emplace(CTorArguments&&... args) noexcept;

    /// @brief calls the constructor of the class at ClassIndex and perfectly forwards the initializer list
    ///         of class U and arguments to the constructor.
    template <std::size_t ClassIndex, class U, class... CTorArguments>
    void emplace(std::initializer_list<U> f_inir, CTorArguments&&... f_args);

    /// @brief calls the constructor of the class T and perfectly forwards the initializer list
    ///         of class U and arguments to the constructor.
    template <class T, class U, class... CTorArguments>
    void emplace(std::initializer_list<U> f_inir, CTorArguments&&... f_args);

    /// @brief returns a pointer to the type stored at index TypeIndex. (not stl compliant)
    /// @return if the variant does contain the type at index TypeIndex it returns a valid
    ///             pointer, if it does contain no type at all or a different type it returns
    ///             nullptr.
    /// @code
    ///     cxx::variant<int, float> someVariant(cxx::in_place_type<int>(), 12);
    ///     int * someNumber = someVariant.template get_at_index<0>();
    /// @endcode
    template <std::size_t TypeIndex>
    typename internal::get_type_at_index<0, TypeIndex, Types...>::type* get_at_index() noexcept;

    /// @brief returns a pointer to the type stored at index TypeIndex. (not stl compliant)
    /// @return if the variant does contain the type at index TypeIndex it returns a valid
    ///             pointer, if it does contain no type at all or a different type it returns
    ///             nullptr.
    /// @code
    ///     cxx::variant<int, float> someVariant(cxx::in_place_type<int>(), 12);
    ///     int * someNumber = someVariant.template get_at_index<0>();
    /// @endcode
    template <std::size_t TypeIndex>
    const typename internal::get_type_at_index<0, TypeIndex, Types...>::type* get_at_index() const noexcept;

    /// @brief returns a pointer to the type T stored in the variant. (not stl compliant)
    /// @return if the variant does contain the type T it returns a valid pointer otherwise
    ///         if the variant does contain no type at all or a different type it returns
    ///         nullptr
    template <typename T>
    const T* get() const noexcept;

    /// @brief returns a pointer to the type T stored in the variant. (not stl compliant)
    /// @return if the variant does contain the type T it returns a valid pointer otherwise
    ///         if the variant does contain no type at all or a different type it returns
    ///         nullptr
    template <typename T>
    T* get() noexcept;

    /// @brief returns a pointer to the type T if its stored in the variant otherwise
    ///         it returns the provided defaultValue
    /// @return pointer to the stored value if it is of type T, otherwise defaultValue
    template <typename T>
    T* get_if(T* defaultValue) noexcept;

    /// @brief returns a pointer to the type T if its stored in the variant otherwise
    ///         it returns the provided defaultValue
    /// @return pointer to the stored value if it is of type T, otherwise defaultValue
    template <typename T>
    const T* get_if(const T* defaultValue) const noexcept;

    /// @brief check whether variant holds value or not
    /// @return returns false if and only if the variant holds a value
    constexpr bool valueless_by_exception() const noexcept;

    /// @brief returns the index of the stored type in the variant. if the variant does
    ///         not contain any type it returns INVALID_VARIANT_INDEX
    /// @return index of the stored type
    constexpr size_t index() const noexcept;

    /// @brief swap value of Lvalue and rhs
    void swap(Variant& rhs) noexcept;

private:
    alignas(internal::max(alignof(Types)...)) internal::byte_t m_storage[TYPE_SIZE]{ 0u };
    std::size_t m_type_index = INVALID_VARIANT_INDEX;

private:
    template <typename T>
    bool has_bad_variant_element_access() const noexcept;
    static void error_message(const char* f_source, const char* f_msg) noexcept;

    void call_element_destructor() noexcept;
};

/// @brief returns true if the variant holds a given type T, otherwise false
template <typename T, typename... Types>
constexpr bool holds_alternative(const Variant<Types...>& f_variant) noexcept;

template <class T, class... Types>
constexpr T* get_if(Variant<Types...>* f_variant_ptr) noexcept;

template <class T, class... Types>
constexpr const T* get_if(const Variant<Types...>* f_variant_ptr) noexcept;

}  // namespace core
}  // namespace ara

#include "internal/variant.inl"

#endif  // ARA_CORE_VARIANT_H_
