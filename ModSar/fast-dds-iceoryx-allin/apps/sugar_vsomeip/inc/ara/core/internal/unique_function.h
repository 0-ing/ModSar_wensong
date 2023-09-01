//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================
//
/// @file     unique_function.h
/// @brief    unique_function class supports move only version of std::function
//=============================================================================

#ifndef ARA_CORE_INTERNAL_UNIQUE_FUNCTION_H_
#define ARA_CORE_INTERNAL_UNIQUE_FUNCTION_H_

#include <functional>
#include <utility>
#include <type_traits>

namespace ara {
namespace core {
namespace internal {

// Re-implementation of C++14's std::enable_if_t
template <bool Condition, typename U = void>
using enable_if_t = typename std::enable_if<Condition, U>::type;

template <typename T>
class unique_function : public std::function<T> {
    template <typename Fn, typename En = void>
    struct wrapper;

    // specialization for MoveConstructible-only Fn
    template <typename Fn>
    struct wrapper<Fn, enable_if_t<!std::is_copy_constructible<Fn>::value && std::is_move_constructible<Fn>::value>> {
        Fn fn;

        explicit wrapper(Fn&& fn) : fn(std::forward<Fn>(fn)) {}

        wrapper(wrapper&&) = default;
        wrapper& operator=(wrapper&&) = default;

        // these two functions are instantiated by std::function
        // and are never called
        wrapper(const wrapper& rhs) : fn(const_cast<Fn&&>(rhs.fn)) {
            throw 0;
        }  // hack to initialize fn for non-DefaultContructible types
        wrapper& operator=(wrapper&) { throw 0; }

        template <typename... Args>
        auto operator()(Args&&... args) -> decltype(fn(std::forward<Args>(args)...)) {
            return fn(std::forward<Args>(args)...);
        }
    };

    using base = std::function<T>;

public:
    unique_function() noexcept = default;

    template <typename Fn>
    unique_function& operator=(Fn&& f) {
        base::operator=(wrapper<Fn>{ std::forward<Fn>(f) });
        return *this;
    }

    using base::operator();
};

}  // namespace internal
}  // namespace core
}  // namespace ara

#endif  // ARA_CORE_INTERNAL_UNIQUE_FUNCTION_H_
