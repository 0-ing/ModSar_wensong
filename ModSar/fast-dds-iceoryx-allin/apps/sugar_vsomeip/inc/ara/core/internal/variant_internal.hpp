/// @copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef ARA_CORE_INTERNAL_VARIANT_INTERNAL_HPP_
#define ARA_CORE_INTERNAL_VARIANT_INTERNAL_HPP_

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <type_traits>
#include <utility>
#include <tuple>

#include "ara/core/utility.h"

namespace ara {
namespace core {
namespace internal {
using byte_t = uint8_t;
template <typename TypeToCheck, typename T, typename... Targs>
struct does_contain_type {
    static constexpr bool value
        = std::is_same<TypeToCheck, T>::value || does_contain_type<TypeToCheck, Targs...>::value;
};

template <typename TypeToCheck, typename T>
struct does_contain_type<TypeToCheck, T> {
    static constexpr bool value = std::is_same<TypeToCheck, T>::value;
};

template <std::size_t N, typename Type, typename T, typename... Targs>
struct get_index_of_type {
    static constexpr std::size_t index = get_index_of_type<N + 1, Type, Targs...>::index;
};

template <std::size_t N, typename Type, typename... Targs>
struct get_index_of_type<N, Type, Type, Targs...> {
    static constexpr std::size_t index = N;
};

template <std::size_t N, std::size_t Index, typename T, typename... Targs>
struct get_type_at_index {
    using type = typename get_type_at_index<N + 1, Index, Targs...>::type;
};

template <std::size_t N, typename T, typename... Targs>
struct get_type_at_index<N, N, T, Targs...> {
    using type = T;
};

template <std::size_t N, typename T, typename... Targs>
struct call_at_index {
    static void destructor(const std::size_t index, byte_t* ptr) {
        if (N == index) {
            reinterpret_cast<T*>(ptr)->~T();
        } else {
            call_at_index<N + 1, Targs...>::destructor(index, ptr);
        }
    }

    static void move(const std::size_t index, byte_t* source, byte_t* destination) {
        if (N == index) {
            *reinterpret_cast<T*>(destination) = std::move(*reinterpret_cast<T*>(source));
        } else {
            call_at_index<N + 1, Targs...>::move(index, source, destination);
        }
    }

    static void moveConstructor(const std::size_t index, byte_t* source, byte_t* destination) {
        if (N == index) {
            new (destination) T(std::move(*reinterpret_cast<T*>(source)));
        } else {
            call_at_index<N + 1, Targs...>::moveConstructor(index, source, destination);
        }
    }

    static void copy(const std::size_t index, byte_t* source, byte_t* destination) {
        if (N == index) {
            *reinterpret_cast<T*>(destination) = *reinterpret_cast<T*>(source);
        } else {
            call_at_index<N + 1, Targs...>::copy(index, source, destination);
        }
    }

    static void copyConstructor(const std::size_t index, byte_t* source, byte_t* destination) {
        if (N == index) {
            new (destination) T(*reinterpret_cast<T*>(source));
        } else {
            call_at_index<N + 1, Targs...>::copyConstructor(index, source, destination);
        }
    }
};

template <std::size_t N, typename T>
struct call_at_index<N, T> {
    static void destructor(const std::size_t index, byte_t* ptr) {
        if (N == index) {
            reinterpret_cast<T*>(ptr)->~T();
        } else {
            assert(false && "Could not call destructor for variant element");
        }
    }

    static void move(const std::size_t index, byte_t* source, byte_t* destination) {
        if (N == index) {
            *reinterpret_cast<T*>(destination) = std::move(*reinterpret_cast<T*>(source));
        } else {
            assert(false && "Could not call move assignment for variant element");
        }
    }

    static void moveConstructor(const std::size_t index, byte_t* source, byte_t* destination) {
        if (N == index) {
            new (destination) T(std::move(*reinterpret_cast<T*>(source)));
        } else {
            assert(false && "Could not call move constructor for variant element");
        }
    }

    static void copy(const std::size_t index, byte_t* source, byte_t* destination) {
        if (N == index) {
            *reinterpret_cast<T*>(destination) = *reinterpret_cast<T*>(source);
        } else {
            assert(false && "Could not call copy assignment for variant element");
        }
    }

    static void copyConstructor(const std::size_t index, byte_t* source, byte_t* destination) {
        if (N == index) {
            new (destination) T(*reinterpret_cast<T*>(source));
        } else {
            assert(false && "Could not call copy constructor for variant element");
        }
    }
};

template <typename TypeToCheck, typename... Targs>
struct are_move_constructible {
    static constexpr bool value
        = std::is_move_constructible<TypeToCheck>::value && are_move_constructible<Targs...>::value;
};

template <typename TypeToCheck>
struct are_move_constructible<TypeToCheck> {
    static constexpr bool value = std::is_move_constructible<TypeToCheck>::value;
};

/** The following helper structures and types are needed by the Variant
 ** Converting Constructor implementation.
 **/

using index_type = std::size_t;
static constexpr index_type invalid_index = index_type(-1);

/* Recursive template structs, to retrieve the potential index of the type T to be
 * copy/move assigned into the Variant.
 */
template <typename T, typename... Types>
struct get_direct_type_index;

template <typename T, typename N, typename... Types>
struct get_direct_type_index<T, N, Types...> {
    static constexpr index_type index
        = std::is_same<T, N>::value ? sizeof...(Types) : get_direct_type_index<T, Types...>::index;
};

template <typename T>
struct get_direct_type_index<T> {
    static constexpr index_type index = invalid_index;
};

/* Recursive template structs, to check the type convertibility of the the potential type T
 * to be copy or move assigned into the Variant against the types held in the Variant.
 */
template <typename T, typename... Types>
struct get_convertible_type_index;

template <typename T, typename N, typename... Types>
struct get_convertible_type_index<T, N, Types...> {
    static constexpr index_type index = std::is_convertible<T, N>::value
        ? disjunction<std::is_convertible<T, Types>...>::value ? invalid_index : sizeof...(Types)
        : get_convertible_type_index<T, Types...>::index;
};

template <typename T>
struct get_convertible_type_index<T> {
    static constexpr index_type index = invalid_index;
};

/* The following structure contains the relevant details regarding the type T passed to the Variant
 * converting constructor - potential index of T in the Variant retrieved either by directly checking
 * against the contained types, or looking up potential conversion of T into one of the Variant types
 * and retrieving the matched index. Finally, the type inside the Variant best fit for T is deduced
 * from a tuple constructed of void (if supported in future) and Types... from the Variant.
 */
template <typename T, typename... Types>
struct T_detail {
    using T_val = typename std::remove_const<typename std::remove_reference<T>::type>::type;
    static constexpr index_type T_direct = get_direct_type_index<T_val, Types...>::index;
    static constexpr bool T_present = T_direct != invalid_index;
    static constexpr index_type T_index = T_present ? T_direct : get_convertible_type_index<T_val, Types...>::index;
    static constexpr bool T_valid = T_index != invalid_index;
    static constexpr index_type T_final = T_valid ? sizeof...(Types) - T_index : 0;
    static constexpr index_type T_varIndex = T_final - 1;
    using T_varType = typename std::tuple_element<T_final, std::tuple<void, Types...>>::type;
};

}  // namespace internal
}  // namespace core
}  // namespace ara

#endif  // ARA_CORE_INTERNAL_VARIANT_INTERNAL_HPP_
