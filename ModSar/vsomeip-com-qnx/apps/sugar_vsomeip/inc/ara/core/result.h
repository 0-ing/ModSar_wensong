//==============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
/// @copyright (c) 2021-2022 by Robert Bosch GmbH. All rights reserved.
//
// The reproduction, distribution and utilization of this file as
// well as the communication of its contents to others without express
// authorization is prohibited. Offenders will be held liable for the
// payment of damages. All rights reserved in the event of the grant
// of a patent, utility model or design.
//==============================================================================

/// @file result.h
/// @brief A type that contains either a value or an error.
//==============================================================================

#ifndef ARA_CORE_RESULT_H_
#define ARA_CORE_RESULT_H_

#include <system_error>
#include <type_traits>
#include <memory>
#include <utility>
#include <iostream>

#include "ara/core/variant.h"
#include "ara/core/utility.h"

#include "ara/core/error_code.h"

namespace ara {
namespace core {
/// @brief This class is a type that contains either a value or an error.
///
/// @tparam T  the type of value
/// @tparam E  the type of error
///
/// @traceid{SWS_CORE_00701}
template <typename T, typename E = ErrorCode>
class Result final {
    Variant<T, E> mData;

    template <typename U, typename... Args>
    struct has_as_first_checker;

    template <typename U>
    struct has_as_first_checker<U> : std::false_type { };

    template <typename U, typename... Args>
    struct has_as_first_checker<U, U, Args...> : std::true_type { };

    template <typename U, typename A, typename... Args>
    struct has_as_first_checker<U, A, Args...> : std::false_type { };

    template <typename U, typename... Args>
    struct has_as_first : public has_as_first_checker<typename std::remove_reference<U>::type,
                                                      typename std::remove_reference<Args>::type...> { };

public:
    /// @brief Type alias for the type T of values
    /// @traceid{SWS_CORE_00711}
    using value_type = T;

    /// @brief Type alias for the type E of errors
    /// @traceid{SWS_CORE_00712}
    using error_type = E;

    /// @brief Build a new Result from the specified value (given as lvalue).
    ///
    /// @param t  the value to put into the Result
    /// @returns a Result that contains the value @a t
    ///
    /// @traceid{SWS_CORE_00731}
    static Result FromValue(T const& t) { return Result(t); }
    /// @brief Build a new Result from the specified value (given as rvalue).
    ///
    /// @param t  the value to put into the Result
    /// @returns a Result that contains the value @a t
    ///
    /// @traceid{SWS_CORE_00732}
    static Result FromValue(T&& t) { return Result(std::move(t)); }

    /// @brief Build a new Result from a value that is constructed in-place from the given arguments.
    ///
    /// This function shall not participate in overload resolution unless:
    /// std::is_constructible<T, Args&&...>::value is true, and
    ///     - the first type of the expanded parameter pack is not T, and
    ///     - the first type of the expanded parameter pack is not a specialization of Result
    ///
    /// @tparam Args...  the types of arguments given to this function
    /// @param args  the arguments used for constructing the value
    /// @returns a Result that contains a value
    ///
    /// @traceid{SWS_CORE_00733}
    template <typename... Args,
              typename = typename std::enable_if<true                                          //
                                                 && std::is_constructible<T, Args&&...>::value //
                                                 && !has_as_first<T, Args...>::value           //
                                                 && !has_as_first<Result, Args...>::value      //
                                                 >::type                                       //
              >
    static Result FromValue(Args&&... args) {
        return Result(T { std::forward<Args>(args)... });
    }

    /// @brief Build a new Result from the specified error (given as lvalue).
    ///
    /// @param e  the error to put into the Result
    /// @returns a Result that contains the error @a e
    ///
    /// @traceid{SWS_CORE_00734}
    static Result FromError(E const& e) { return Result(e); }

    /// @brief Build a new Result from the specified error (given as rvalue).
    ///
    /// @param e  the error to put into the Result
    /// @returns a Result that contains the error @a e
    ///
    /// @traceid{SWS_CORE_00735}
    static Result FromError(E&& e) { return Result(std::move(e)); }

    /// @brief Build a new Result from an error that is constructed in-place from the given arguments.
    ///
    /// This function shall not participate in overload resolution unless:
    /// std::is_constructible<E, Args&&...>::value is true, and
    ///     - the first type of the expanded parameter pack is not E, and
    ///     - the first type of the expanded parameter pack is not a specialization of Result
    ///
    /// @tparam Args...  the types of arguments given to this function
    /// @param args  the arguments used for constructing the error
    /// @returns a Result that contains an error
    ///
    /// @traceid{SWS_CORE_00736}
    template <typename... Args,
              typename = typename std::enable_if<true                                          //
                                                 && std::is_constructible<E, Args&&...>::value //
                                                 && !has_as_first<E, Args...>::value           //
                                                 && !has_as_first<Result, Args...>::value      //
                                                 >::type                                       //
              >
    static Result FromError(Args&&... args) {
        return Result(E { std::forward<Args>(args)... });
    }

    // ----------------------------------------
    Result() = delete;

    /// @brief Construct a new Result from the specified value (given as lvalue).
    /// @param t  the value to put into the Result
    ///
    /// @traceid{SWS_CORE_00721}
    Result(T const& t) : mData(in_place_type_t<T>(), t) { }

    /// @brief Construct a new Result from the specified value (given as rvalue).
    /// @param t  the value to put into the Result
    ///
    /// @traceid{SWS_CORE_00722}
    Result(T&& t) : mData(in_place_type_t<T>(), std::move(t)) { }

    /// @brief Construct a new Result from the specified error (given as lvalue).
    /// @param e  the error to put into the Result
    ///
    /// @traceid{SWS_CORE_00723}
    explicit Result(E const& e) : mData(in_place_type_t<E>(), e) { }

    /// @brief Construct a new Result from the specified error (given as rvalue).
    /// @param e  the error to put into the Result
    ///
    /// @traceid{SWS_CORE_00724}
    explicit Result(E&& e) : mData(in_place_type_t<E>(), std::move(e)) { }

    /// @brief Copy-construct a new Result from another instance.
    /// @param other  the other instance
    ///
    /// @traceid{SWS_CORE_00725}
    Result(Result const& other) = default;

    /// @brief Move-construct a new Result from another instance.
    /// @param other  the other instance
    ///
    /// @traceid{SWS_CORE_00726}
    Result(Result&& other) noexcept(
        std::is_nothrow_move_constructible<T>::value&& std::is_nothrow_move_constructible<E>::value)
        = default;

    /// @brief Destructor
    ///
    /// This destructor is trivial if std::is_trivially_destructible<T>::value
    /// && std::is_trivially_destructible<E>::value is true.
    ///
    /// @traceid{SWS_CORE_00727}
    ~Result() = default;

    /// @brief Copy-assign another Result to this instance.
    /// @param other  the other instance
    /// @returns *this, containing the contents of @a other
    ///
    /// @traceid{SWS_CORE_00741}
    Result& operator=(Result const& other) = default;

    /// @brief Move-assign another Result to this instance.
    /// @param other  the other instance
    /// @returns *this, containing the contents of @a other
    ///
    /// @traceid{SWS_CORE_00742}
    Result& operator=(Result&& other) noexcept(
        std::is_nothrow_move_constructible<T>::value&& std::is_nothrow_move_assignable<T>::value&&
            std::is_nothrow_move_constructible<E>::value&& std::is_nothrow_move_assignable<E>::value)
        = default;

    /// @brief Put a new value into this instance, constructed in-place from the given arguments.
    /// @tparam Args...  the types of arguments given to this function
    /// @param args  the arguments used for constructing the value
    ///
    /// @traceid{SWS_CORE_00743}
    template <typename... Args>
    void EmplaceValue(Args&&... args) {
        mData.template emplace<T>(std::forward<Args>(args)...);
    }

    /// @brief Put a new error into this instance, constructed in-place from the given arguments.
    /// @tparam Args...  the types of arguments given to this function
    /// @param args  the arguments used for constructing the error
    ///
    /// @traceid{SWS_CORE_00744}
    template <typename... Args>
    void EmplaceError(Args&&... args) {
        mData.template emplace<E>(std::forward<Args>(args)...);
    }

    /// @brief Exchange the contents of this instance with those of @a other.
    /// @param[in,out] other  the other instance
    ///
    /// @traceid{SWS_CORE_00745}
    void Swap(Result& other) noexcept(
        std::is_nothrow_move_constructible<T>::value&& std::is_nothrow_move_assignable<T>::value&&
            std::is_nothrow_move_constructible<E>::value&& std::is_nothrow_move_assignable<E>::value) {
        using std::swap;
        swap(mData, other.mData);
    }

    /// @brief Check whether *this contains a value.
    /// @returns true if *this contains a value, false otherwise
    ///
    /// @traceid{SWS_CORE_00752}
    explicit operator bool() const noexcept { return HasValue(); }

    /// @brief Check whether *this contains a value.
    /// @returns true if *this contains a value, false otherwise
    ///
    /// @traceid{SWS_CORE_00751}
    bool HasValue() const noexcept { return mData.index() == 0; }

    /// @brief Access the contained value.
    ///
    /// This function's behavior is undefined if *this does not contain a value.
    ///
    /// @returns a const_reference to the contained value
    ///
    /// @traceid{SWS_CORE_00753}
    T const& operator*() const& { return Value(); }

    /// @brief Access the contained value.
    ///
    /// This function's behavior is undefined if *this does not contain a value.
    ///
    /// @returns an rvalue reference to the contained value
    ///
    /// @traceid{SWS_CORE_00759}
    T&& operator*() && { return std::move(*this).Value(); }

    /// @brief Access the contained value.
    ///
    /// This function's behavior is undefined if *this does not contain a value.
    ///
    /// @returns a pointer to the contained value
    ///
    /// @traceid{SWS_CORE_00754}
    T const* operator->() const { return std::addressof(Value()); }

    /// @brief Access the contained value.
    ///
    /// The behavior of this function is undefined if *this does not contain a value.
    ///
    /// @returns a const reference to the contained value
    ///
    /// @traceid{SWS_CORE_00755}
    T const& Value() const& {
        T const* ptr = get_if<T>(&mData);
        if (ptr)
            return *ptr;
        std::cout << "__ value() called but NOT a value!\n";
        std::terminate();
    }

    /// @brief Access the contained value.
    ///
    /// The behavior of this function is undefined if *this does not contain a value.
    ///
    /// @returns an rvalue reference to the contained value
    ///
    /// @traceid{SWS_CORE_00756}
    T&& Value() && {
        T* ptr = get_if<T>(&mData);
        if (ptr)
            return std::move(*ptr);
        std::cout << "__ value() called but NOT a value!\n";
        std::terminate();
    }

    /// @brief Access the contained error.
    ///
    /// The behavior of this function is undefined if *this does not contain an error.
    ///
    /// @returns a const reference to the contained error
    ///
    /// @traceid{SWS_CORE_00757}
    E const& Error() const& {
        E const* ptr = get_if<E>(&mData);
        if (ptr)
            return *ptr;
        std::cout << "__ error() called but NOT an error!\n";
        std::terminate();
    }

    /// @brief Access the contained error.
    ///
    /// The behavior of this function is undefined if *this does not contain an error.
    ///
    /// @returns an rvalue reference to the contained error
    ///
    /// @traceid{SWS_CORE_00758}
    E&& Error() && {
        E* ptr = get_if<E>(&mData);
        if (ptr)
            return std::move(*ptr);
        std::cout << "__ error() called but NOT an error!\n";
        std::terminate();
    }

    /// @brief Return the contained value or the given default value.
    ///
    /// If *this contains a value, it is returned. Otherwise, the specified
    /// default value is returned, static_cast'd to T.
    ///
    /// @tparam U  the type of @a defaultValue
    /// @param defaultValue  the value to use if *this does not contain a value
    /// @returns the value
    ///
    /// @traceid{SWS_CORE_00761}
    template <typename U>
    T ValueOr(U&& defaultValue) const& {
        return HasValue() ? Value() : static_cast<T>(std::forward<U>(defaultValue));
    }

    /// @brief Return the contained value or the given default value.
    ///
    /// If *this contains a value, it is returned. Otherwise, the specified
    /// default value is returned, static_cast'd to T.
    ///
    /// @tparam U  the type of @a defaultValue
    /// @param defaultValue  the value to use if *this does not contain a value
    /// @returns the value
    ///
    /// @traceid{SWS_CORE_00762}
    template <typename U>
    T ValueOr(U&& defaultValue) && {
        return HasValue() ? std::move(Value()) : static_cast<T>(std::forward<U>(defaultValue));
    }

    /// @brief Return the contained error or the given default error.
    ///
    /// If *this contains an error, it is returned. Otherwise, the specified
    /// default error is returned, static_cast'd to E.
    ///
    /// @tparam G  the type of @a defaultError
    /// @param defaultError  the error to use if *this does not contain an error
    /// @returns the error
    ///
    /// @traceid{SWS_CORE_00763}
    template <typename G>
    E ErrorOr(G&& defaultError) const {
        return HasValue() ? static_cast<E>(std::forward<G>(defaultError)) : Error();
    }

    /// @brief Return whether this instance contains the given error.
    ///
    /// This call compares the argument @a error, static_cast'd to E, with
    /// the return value from Error().
    ///
    /// @tparam G  the type of the error argument @a error
    /// @param error  the error to check
    /// @returns true if *this contains an error that is equivalent to the given error, false otherwise
    ///
    /// @traceid{SWS_CORE_00765}
    template <typename G>
    bool CheckError(G&& e) const {
        return HasValue() ? false : (Error() == static_cast<E>(std::forward<G>(e)));
    }

#ifndef ARA_NO_EXCEPTIONS
    /// @brief Return the contained value or throw an exception.
    ///
    /// This function does not participate in overload resolution when the compiler toolchain
    /// does not support C++ exceptions.
    ///
    /// @returns a const reference to the contained value
    /// @throws <TYPE>  the exception type associated with the contained error
    ///
    /// @traceid{SWS_CORE_00766}
    T const& ValueOrThrow() const& noexcept(false) {
        T const* ptr = get_if<T>(&mData);
        if (ptr)
            return *ptr;

        // TODO: check if mData is uninitialized (-> monostate)
        E const* e = get_if<E>(&mData);

        e->ThrowAsException();
    }

    /// @brief Return the contained value or throw an exception.
    ///
    /// This function does not participate in overload resolution when the compiler toolchain
    /// does not support C++ exceptions.
    ///
    /// @returns an rvalue reference to the contained value
    /// @throws <TYPE>  the exception type associated with the contained error
    ///
    /// @traceid{SWS_CORE_00769}
    T&& ValueOrThrow() && noexcept(false) {
        T* ptr = get_if<T>(&mData);
        if (ptr)
            return std::move(*ptr);

        E* e = get_if<E>(&mData);
        e->ThrowAsException();
    }

#endif

    /// @brief Return the contained value or return the result of a function call.
    ///
    /// If *this contains a value, it is returned. Otherwise, the specified callable
    /// is invoked and its return value which is to be compatible to type T
    /// is returned from this function.
    ///
    /// The Callable is expected to be compatible to this interface:
    /// <code>
    /// T f(const E&);
    /// </code>
    ///
    /// @tparam F  the type of the Callable @a f
    /// @param f  the Callable
    /// @returns the value
    ///
    /// @traceid{SWS_CORE_00767}
    template <typename F>
    T Resolve(F&& f) const {
        return HasValue() ? Value() : std::forward<F>(f)(Error());
    }

private:
    // Re-implementation of C++14's std::enable_if_t
    template <bool Condition, typename U = void>
    using enable_if_t = typename std::enable_if<Condition, U>::type;

    // Re-implementation of C++14's std::result_of_t
    template <typename U>
    using result_of_t = typename std::result_of<U>::type;

    /// @brief Trait that detects whether a type is a Result<...>
    template <typename U>
    struct is_result : std::false_type { };

    template <typename U, typename G>
    struct is_result<Result<U, G>> : std::true_type { };

    template <typename F>
    using CallableReturnsResult = enable_if_t<is_result<result_of_t<F(T const&)>>::value>;

    template <typename F>
    using CallableReturnsNoResult = enable_if_t<!is_result<result_of_t<F(T const&)>>::value>;

public:
    /// @brief Apply the given Callable to the value of this instance, and return a new Result with the result of the
    /// call.
    ///
    /// The Callable is expected to be compatible to one of these two interfaces:
    /// - <code>Result<XXX, E> f(const T&);</code>
    /// - <code>XXX f(const T&);</code>
    /// meaning that the Callable either returns a Result<XXX> or a XXX directly,
    /// where XXX can be any type that is suitable for use by class Result.
    ///
    /// The return type of this function is <code>decltype(f(Value()))</code> for a template argument F
    /// that returns a Result type, and it is <code>Result<decltype(f(Value())), E></code> for a
    /// template argument F that does not return a Result type.
    ///
    /// If this instance does not contain a value, a new Result<XXX, E> is still
    /// created and returned, with the original error contents of this instance
    /// being copied into the new instance.
    ///
    /// @tparam F  the type of the Callable @a f
    /// @param f  the Callable
    /// @returns a new Result instance of the possibly transformed type
    ///
    /// @traceid{SWS_CORE_00768}
    template <typename F, typename = CallableReturnsResult<F>>
    auto Bind(F&& f) const -> decltype(f(Value())) {
        using U = decltype(f(Value()));
        return HasValue() ? std::forward<F>(f)(Value()) : U(Error());
    }

    /// @traceid{SWS_CORE_00768}
    template <typename F, typename = CallableReturnsNoResult<F>>
    auto Bind(F&& f) const -> Result<decltype(f(Value())), E> {
        using U = decltype(f(Value()));
        using R = Result<U, E>;
        return HasValue() ? std::forward<F>(f)(Value()) : R(Error());
    }

    template <typename, typename>
    friend class Result;
};

/// @brief Swap the contents of the two given arguments.
/// @param lhs  one instance
/// @param rhs  another instance
///
/// @traceid{SWS_CORE_00796}
template <typename T, typename E>
void swap(Result<T, E>& lhs, Result<T, E>& rhs) noexcept(noexcept(lhs.Swap(rhs))) {
    lhs.Swap(rhs);
}

/// @brief Compare two Result instances for equality.
///
/// A Result that contains a value is unequal to every Result containing an error.
/// A Result is equal to another Result only if both contain the same type,
/// and the value of that type compares equal.
///
/// @param lhs  the left hand side of the comparison
/// @param rhs  the right hand side of the comparison
/// @returns true if the two instances compare equal, false otherwise
///
/// @traceid{SWS_CORE_00780}
template <typename T, typename E>
bool operator==(Result<T, E> const& lhs, Result<T, E> const& rhs) {
    if (static_cast<bool>(lhs) != static_cast<bool>(rhs))
        return false;
    if (lhs)
        return lhs.Value() == rhs.Value();
    return lhs.Error() == rhs.Error();
}

/// @brief Compare two Result instances for inequality.
///
/// A Result that contains a value is unequal to every Result containing an error.
/// A Result is equal to another Result only if both contain the same type,
/// and the value of that type compares equal.
///
/// @param lhs  the left hand side of the comparison
/// @param rhs  the right hand side of the comparison
/// @returns true if the two instances compare unequal, false otherwise
/// @see operator==()
///
/// @traceid{SWS_CORE_00781}
template <typename T, typename E>
bool operator!=(Result<T, E> const& lhs, Result<T, E> const& rhs) {
    if (static_cast<bool>(lhs) != static_cast<bool>(rhs))
        return true;
    if (lhs)
        return lhs.Value() != rhs.Value();
    return lhs.Error() != rhs.Error();
}

/// @brief Compare a Result instance for equality to a value.
///
/// A Result that contains no value is unequal to every value.
/// A Result is equal to a value only if the Result contains a value of the
/// same type, and the values compare equal.
///
/// @param lhs  the Result instance
/// @param rhs  the value to compare with
/// @returns true if the Result's value compares equal to the rhs value, false otherwise
///
/// @traceid{SWS_CORE_00782}
template <typename T, typename E>
bool operator==(Result<T, E> const& lhs, T const& value) {
    return lhs ? *lhs == value : false;
}

/// @brief Compare a Result instance for equality to a value.
///
/// A Result that contains no value is unequal to every value.
/// A Result is equal to a value only if the Result contains a value of the
/// same type, and the values compare equal.
///
/// @param lhs  the value to compare with
/// @param rhs  the Result instance
/// @returns true if the Result's value compares equal to the lhs value, false otherwise
///
/// @traceid{SWS_CORE_00783}
template <typename T, typename E>
bool operator==(T const& value, Result<T, E> const& rhs) {
    return rhs ? value == *rhs : false;
}

/// @brief Compare a Result instance for inequality to a value.
///
/// A Result that contains no value is unequal to every value.
/// A Result is equal to a value only if the Result contains a value of the
/// same type, and the values compare equal.
///
/// @param lhs  the Result instance
/// @param rhs  the value to compare with
/// @returns true if the Result's value compares unequal to the rhs value, false otherwise
///
/// @traceid{SWS_CORE_00784}
template <typename T, typename E>
bool operator!=(Result<T, E> const& lhs, T const& value) {
    return lhs ? *lhs != value : true;
}

/// @brief Compare a Result instance for inequality to a value.
///
/// A Result that contains no value is unequal to every value.
/// A Result is equal to a value only if the Result contains a value of the
/// same type, and the values compare equal.
///
/// @param lhs  the value to compare with
/// @param rhs  the Result instance
/// @returns true if the Result's value compares unequal to the lhs value, false otherwise
///
/// @traceid{SWS_CORE_00785}
template <typename T, typename E>
bool operator!=(T const& value, Result<T, E> const& rhs) {
    return rhs ? value != *rhs : true;
}

/// @brief Compare a Result instance for equality to an error.
///
/// A Result that contains no error is unequal to every error.
/// A Result is equal to an error only if the Result contains an error of the
/// same type, and the errors compare equal.
///
/// @param lhs  the Result instance
/// @param rhs  the error to compare with
/// @returns true if the Result's error compares equal to the rhs error, false otherwise
///
/// @traceid{SWS_CORE_00786}
template <typename T, typename E>
bool operator==(Result<T, E> const& lhs, E const& error) {
    return lhs ? false : lhs.Error() == error;
}

/// @brief Compare a Result instance for equality to an error.
///
/// A Result that contains no error is unequal to every error.
/// A Result is equal to an error only if the Result contains an error of the
/// same type, and the errors compare equal.
///
/// @param lhs  the error to compare with
/// @param rhs  the Result instance
/// @returns true if the Result's error compares equal to the lhs error, false otherwise
///
/// @traceid{SWS_CORE_00787}
template <typename T, typename E>
bool operator==(E const& error, Result<T, E> const& rhs) {
    return rhs ? false : error == rhs.Error();
}

/// @brief Compare a Result instance for inequality to an error.
///
/// A Result that contains no error is unequal to every error.
/// A Result is equal to an error only if the Result contains an error of the
/// same type, and the errors compare equal.
///
/// @param lhs  the Result instance
/// @param rhs  the error to compare with
/// @returns true if the Result's error compares unequal to the rhs error, false otherwise
///
/// @traceid{SWS_CORE_00788}
template <typename T, typename E>
bool operator!=(Result<T, E> const& lhs, E const& error) {
    return lhs ? true : lhs.Error() != error;
}

/// @brief Compare a Result instance for inequality to an error.
///
/// A Result that contains no error is unequal to every error.
/// A Result is equal to an error only if the Result contains an error of the
/// same type, and the errors compare equal.
///
/// @param lhs  the error to compare with
/// @param rhs  the Result instance
/// @returns true if the Result's error compares unequal to the lhs error, false otherwise
///
/// @traceid{SWS_CORE_00789}
template <typename T, typename E>
bool operator!=(E const& error, Result<T, E> const& rhs) {
    return rhs ? true : error != rhs.Error();
}

/// @brief Specialization of class Result for "void" values
///
/// @tparam T  is void
/// @tparam E  the type of error
///
/// @traceid{SWS_CORE_00801}
template <typename E>
class Result<void, E> final {
    // Cannot use 'void' for variant, so define our own (default-constructible) dummy type instead.
    struct dummy { };
    using T = dummy;
    Variant<T, E> mData;

public:
    /// @brief Type alias for the type T of values, always "void" for this specialization
    /// @traceid{SWS_CORE_00811}
    using value_type = void;

    /// @brief Type alias for the type E of errors
    /// @traceid{SWS_CORE_00812}
    using error_type = E;

    /// @brief Build a new Result with "void" as value
    /// @returns a Result that contains a "void" value
    ///
    /// @traceid{SWS_CORE_00831}
    static Result FromValue() { return Result(); }

    /// @copydoc Result<T,E>::FromError(const E&)
    /// @traceid{SWS_CORE_00834}
    static Result FromError(E const& e) { return Result(e); }

    /// @copydoc Result<T,E>::FromError(E&&)
    /// @traceid{SWS_CORE_00835}
    static Result FromError(E&& e) { return Result(std::move(e)); }

    /// @brief Build a new Result from an error that is constructed in-place from the given arguments.
    ///
    /// This function shall not participate in overload resolution unless:
    /// std::is_constructible<E, Args&&...>::value is true, and
    ///     - the first type of the expanded parameter pack is not E, and
    ///     - the first type of the expanded parameter pack is not a specialization of Result
    ///
    /// @tparam Args...  the types of arguments given to this function
    /// @param args  the parameter pack used for constructing the error
    /// @returns a Result that contains an error
    ///
    /// @traceid{SWS_CORE_00836}
    template <typename... Args>
    static Result FromError(Args&&... args) {
        return Result(E { std::forward<Args>(args)... });
    }

    /// @brief Construct a new Result with a "void" value
    ///
    /// @traceid{SWS_CORE_00821}
    Result() noexcept : mData(in_place_type_t<T>(), T {}) { }

    /// @copydoc Result<T,E>::Result(const E&)
    /// @traceid{SWS_CORE_00823}
    explicit Result(E const& e) : mData(in_place_type_t<E>(), e) { }

    /// @copydoc Result<T,E>::Result(E&&)
    /// @traceid{SWS_CORE_00824}
    explicit Result(E&& e) : mData(in_place_type_t<E>(), std::move(e)) { }

    /// @copydoc Result<T,E>::Result(const Result&)
    /// @traceid{SWS_CORE_00825}
    Result(Result const& other) = default;

    /// @copydoc Result<T,E>::Result(Result&&)
    /// @traceid{SWS_CORE_00826}
    Result(Result&& other) noexcept(std::is_nothrow_move_constructible<E>::value) = default;

    /// @brief Destructor
    ///
    /// This destructor is trivial if std::is_trivially_destructible<E>::value is true.
    ///
    /// @traceid{SWS_CORE_00827}
    ~Result() { }

    /// @copydoc Result<T,E>::operator=(const Result&)
    /// @traceid{SWS_CORE_00841}
    Result& operator=(Result const& other) = default;

    /// @copydoc Result<T,E>::operator=(Result&&)
    /// @traceid{SWS_CORE_00842}
    Result& operator=(Result&& other) noexcept(
        std::is_nothrow_move_constructible<E>::value&& std::is_nothrow_move_assignable<E>::value)
        = default;

    /// @copydoc Result<T,E>::EmplaceValue()
    /// @traceid{SWS_CORE_00843}
    template <typename... Args>
    void EmplaceValue(Args&&... args) noexcept {
        mData.template emplace<T>(std::forward<Args>(args)...);
    }

    /// @copydoc Result<T,E>::EmplaceError()
    /// @traceid{SWS_CORE_00844}
    template <typename... Args>
    void EmplaceError(Args&&... args) {
        mData.template emplace<E>(std::forward<Args>(args)...);
    }

    /// @copydoc Result<T,E>::Swap()
    /// @traceid{SWS_CORE_00845}
    void Swap(Result& other) noexcept(
        std::is_nothrow_move_constructible<E>::value&& std::is_nothrow_move_assignable<E>::value) {
        using std::swap;
        swap(mData, other.mData);
    }

    /// @copydoc Result<T,E>::bool()
    /// @traceid{SWS_CORE_00852}
    explicit operator bool() const noexcept { return HasValue(); }

    /// @copydoc Result<T,E>::HasValue()
    /// @traceid{SWS_CORE_00851}
    bool HasValue() const noexcept { return mData.index() == 0; }

    /// @copydoc Result<void,E>::Value()
    /// @traceid{SWS_CORE_00853}
    void operator*() const { return Value(); }

    /// @brief Do nothing
    ///
    /// This function only exists for helping with generic programming.
    ///
    /// The behavior of this function is undefined if *this does not contain a value.
    ///
    /// @traceid{SWS_CORE_00855}
    void Value() const {
        T const* ptr = get_if<T>(&mData);
        if (ptr)
            return;
        std::cout << "__ value() called but NOT a (void) value!\n";
        std::terminate();
    }

    /// @copydoc Result<T,E>::Error()const&
    /// @traceid{SWS_CORE_00857}
    E const& Error() const& {
        E const* ptr = get_if<E>(&mData);
        if (ptr)
            return *ptr;
        std::cout << "__ error() called but NOT an error!\n";
        std::terminate();
    }

    /// @copydoc Result<T,E>::Error()&&
    /// @traceid{SWS_CORE_00858}
    E&& Error() && {
        E* ptr = get_if<E>(&mData);
        if (ptr)
            return std::move(*ptr);
        std::cout << "__ error() called but NOT an error!\n";
        std::terminate();
    }

    /// @brief Do nothing.
    ///
    /// @note This function only exists for helping with generic programming.
    ///
    /// @tparam U  the type of @a defaultValue
    /// @param defaultValue  the value to use if *this does not contain a value
    ///
    /// @traceid{SWS_CORE_00861}
    template <typename U>
    void ValueOr(U&& defaultValue) const {
        return HasValue() ? Value() : static_cast<void>(std::forward<U>(defaultValue));
    }

    /// @copydoc Result<T,E>::ErrorOr(G&&)const&
    /// @traceid{SWS_CORE_00863}
    template <typename G>
    E ErrorOr(G&& defaultError) const {
        return HasValue() ? static_cast<E>(std::forward<G>(defaultError)) : Error();
    }

    /// @copydoc Result<T,E>::CheckError()
    /// @traceid{SWS_CORE_00865}
    template <typename G>
    bool CheckError(G&& e) const {
        return HasValue() ? false : (Error() == static_cast<E>(std::forward<G>(e)));
    }

#ifndef ARA_NO_EXCEPTIONS
    /// @copydoc Result<T,E>::ValueOrThrow()
    /// @traceid{SWS_CORE_00866}
    void ValueOrThrow() const noexcept(false) {
        T const* ptr = get_if<T>(&mData);
        if (ptr)
            return;

        E const* e = get_if<E>(&mData);
        e->ThrowAsException();
    }
#endif
    /// @brief Do nothing or call a function.
    ///
    /// If *this contains a value, this function does nothing. Otherwise,
    /// the specified callable is invoked.
    ///
    /// The Callable is expected to be compatible to this interface:
    /// <code>
    /// void f(const E&);
    /// </code>
    ///
    /// This function only exists for helping with generic programming.
    ///
    /// @tparam F  the type of the Callable @a f
    /// @param f  the Callable
    ///
    /// @traceid{SWS_CORE_00867}
    template <typename F>
    void Resolve(F&& f) const {
        return HasValue() ? Value() : std::forward<F>(f)(Error());
    }

private:
    // Re-implementation of C++14's std::enable_if_t
    template <bool Condition, typename U = void>
    using enable_if_t = typename std::enable_if<Condition, U>::type;

    // Re-implementation of C++14's std::result_of_t
    template <typename U>
    using result_of_t = typename std::result_of<U>::type;

    /// @brief Trait that detects whether a type is a Result<...>
    template <typename U>
    struct is_result : std::false_type { };

    template <typename U, typename G>
    struct is_result<Result<U, G>> : std::true_type { };

    template <typename F>
    using CallableReturnsResult = enable_if_t<is_result<result_of_t<F()>>::value>;

    template <typename F>
    using CallableReturnsNoResult = enable_if_t<!is_result<result_of_t<F()>>::value>;

public:
    /// @brief Apply the given Callable to the value of this instance, and return a new Result with the result of the
    /// call.
    ///
    /// The Callable is expected to be compatible to one of these two interfaces:
    /// - <code>Result<XXX, E> f();</code>
    /// - <code>XXX f();</code>
    /// meaning that the Callable either returns a Result<XXX> or a XXX directly,
    /// where XXX can be any type that is suitable for use by class Result.
    ///
    /// The return type of this function is <code>decltype(f())</code> for a template argument F
    /// that returns a Result type, and it is <code>Result<decltype(f()), E></code> for a
    /// template argument F that does not return a Result type.
    ///
    /// If this instance does not contain a value, a new Result<XXX, E> is still
    /// created and returned, with the original error contents of this instance
    /// being copied into the new instance.
    ///
    /// @tparam F  the type of the Callable @a f
    /// @param f  the Callable
    /// @returns a new Result instance of the possibly transformed type
    ///
    /// @traceid{SWS_CORE_00870}
    template <typename F, typename = CallableReturnsResult<F>>
    auto Bind(F&& f) const -> decltype(f()) {
        using U = decltype(f());
        return HasValue() ? std::forward<F>(f)() : U(Error());
    }

    /// @traceid{SWS_CORE_00870}
    template <typename F, typename = CallableReturnsNoResult<F>>
    auto Bind(F&& f) const -> Result<decltype(f()), E> {
        using U = decltype(f());
        using R = Result<U, E>;
        return HasValue() ? std::forward<F>(f)() : R(Error());
    }

    template <typename, typename>
    friend class Result;
};

} // namespace core
} // namespace ara

#endif // ARA_CORE_RESULT_H_
