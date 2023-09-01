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

#include <memory>
#include <ara/core/variant.h>

namespace ara {
namespace core {
template <typename... Types>
inline Variant<Types...>::Variant(const Variant& f_rhs) noexcept : m_type_index(f_rhs.m_type_index) {
    if (m_type_index != INVALID_VARIANT_INDEX) {
        internal::call_at_index<0, Types...>::copyConstructor(
            m_type_index, const_cast<internal::byte_t*>(f_rhs.m_storage), m_storage);
    }
}

template <typename... Types>
template <std::size_t N, typename... CTorArguments>
inline Variant<Types...>::Variant(const in_place_index_t<N>&, CTorArguments&&... f_args) noexcept {
    emplace_at_index<N>(std::forward<CTorArguments>(f_args)...);
}

template <typename... Types>
template <std::size_t ClassIndex, class U, class... CTorArguments>
Variant<Types...>::Variant(in_place_index_t<ClassIndex>, std::initializer_list<U> f_inir, CTorArguments&&... f_args) {
    emplace<ClassIndex>(f_inir, std::forward<CTorArguments>(f_args)...);
}

template <typename... Types>
template <typename T, typename... CTorArguments>
inline Variant<Types...>::Variant(const in_place_type_t<T>&, CTorArguments&&... f_args) noexcept {
    emplace<T>(std::forward<CTorArguments>(f_args)...);
}

template <typename... Types>
template <class T, class U, class... CTorArguments>
Variant<Types...>::Variant(in_place_type_t<T>, std::initializer_list<U> f_inir, CTorArguments&&... f_args) {
    emplace<T>(f_inir, std::forward<CTorArguments>(f_args)...);
}

template <typename... Types>
Variant<Types...>& Variant<Types...>::operator=(const Variant& f_rhs) noexcept {
    if (this != &f_rhs) {
        if (m_type_index != f_rhs.m_type_index) {
            call_element_destructor();
            m_type_index = f_rhs.m_type_index;

            if (m_type_index != INVALID_VARIANT_INDEX) {
                internal::call_at_index<0, Types...>::copyConstructor(
                    m_type_index, const_cast<internal::byte_t*>(f_rhs.m_storage), m_storage);
            }
        } else {
            if (m_type_index != INVALID_VARIANT_INDEX) {
                internal::call_at_index<0, Types...>::copy(
                    m_type_index, const_cast<internal::byte_t*>(f_rhs.m_storage), m_storage);
            }
        }
    }
    return *this;
}

template <typename... Types>
Variant<Types...>::Variant(Variant&& f_rhs) noexcept : m_type_index{ std::move(f_rhs.m_type_index) } {
    if (m_type_index != INVALID_VARIANT_INDEX) {
        internal::call_at_index<0, Types...>::moveConstructor(m_type_index, f_rhs.m_storage, m_storage);
    }
    f_rhs.m_type_index = INVALID_VARIANT_INDEX;
}

template <typename... Types>
Variant<Types...>& Variant<Types...>::operator=(Variant&& f_rhs) noexcept {
    if (this != &f_rhs) {
        if (m_type_index != f_rhs.m_type_index) {
            call_element_destructor();
            m_type_index = std::move(f_rhs.m_type_index);
            if (m_type_index != INVALID_VARIANT_INDEX) {
                internal::call_at_index<0, Types...>::moveConstructor(m_type_index, f_rhs.m_storage, m_storage);
            }
            f_rhs.m_type_index = INVALID_VARIANT_INDEX;
        } else {
            if (m_type_index != INVALID_VARIANT_INDEX) {
                internal::call_at_index<0, Types...>::move(m_type_index, f_rhs.m_storage, m_storage);
            }
        }

        f_rhs.m_type_index = INVALID_VARIANT_INDEX;
    }
    return *this;
}

template <typename... Types>
inline Variant<Types...>::~Variant() noexcept {
    call_element_destructor();
}

template <typename... Types>
void Variant<Types...>::call_element_destructor() noexcept {
    if (m_type_index != INVALID_VARIANT_INDEX) {
        internal::call_at_index<0, Types...>::destructor(m_type_index, m_storage);
    }
}

template <typename... Types>
template <typename T, typename U, typename Enable>
Variant<Types...>::Variant(T&& f_rhs) noexcept(std::is_nothrow_constructible<typename U::T_varType, T&&>::value)
    : m_type_index(U::T_varIndex) {
    new (m_storage) typename U::T_varType(std::forward<T>(f_rhs));
}

template <typename... Types>
template <typename T>
inline typename std::enable_if<!std::is_same<T, Variant<Types...>&>::value, Variant<Types...>>::type&
Variant<Types...>::operator=(T&& f_rhs) noexcept {
    Variant<Types...> temp{ std::forward<T>(f_rhs) };

    if (m_type_index != INVALID_VARIANT_INDEX) {
        call_element_destructor();
    }

    internal::call_at_index<0, Types...>::moveConstructor(temp.m_type_index, temp.m_storage, m_storage);
    m_type_index = std::move(temp.m_type_index);

    return *this;
}

template <typename... Types>
template <std::size_t TypeIndex, typename... CTorArguments>
inline void Variant<Types...>::emplace(CTorArguments&&... f_args) noexcept {
    Variant<Types...>::emplace_at_index<TypeIndex, CTorArguments...>(std::forward<CTorArguments>(f_args)...);
}

template <typename... Types>
template <std::size_t TypeIndex, typename... CTorArguments>
inline void Variant<Types...>::emplace_at_index(CTorArguments&&... f_args) noexcept {
    static_assert(TypeIndex <= sizeof...(Types), "TypeIndex is out of bounds");
    using T = typename internal::get_type_at_index<0, TypeIndex, Types...>::type;
    call_element_destructor();
    new (m_storage) T(std::forward<CTorArguments>(f_args)...);
    m_type_index = TypeIndex;
}

template <typename... Types>
template <typename T, typename... CTorArguments>
inline void Variant<Types...>::emplace(CTorArguments&&... f_args) noexcept {
    static_assert(internal::does_contain_type<T, Types...>::value, "variant does not contain given type");
    if (m_type_index != INVALID_VARIANT_INDEX) {
        call_element_destructor();
    }
    new (m_storage) T(std::forward<CTorArguments>(f_args)...);
    m_type_index = internal::get_index_of_type<0, T, Types...>::index;
}

template <typename... Types>
template <std::size_t ClassIndex, class U, class... CTorArguments>
void Variant<Types...>::emplace(std::initializer_list<U> f_inir, CTorArguments&&... f_args) {

    static_assert(ClassIndex <= sizeof...(Types), "ClassIndex is out of bounds");
    using T = typename internal::get_type_at_index<0, ClassIndex, Types...>::type;
    call_element_destructor();
    new (m_storage) T(f_inir, std::forward<CTorArguments>(f_args)...);
    m_type_index = ClassIndex;
}

template <typename... Types>
template <class T, class U, class... CTorArguments>
void Variant<Types...>::emplace(std::initializer_list<U> f_inir, CTorArguments&&... f_args) {

    static_assert(internal::does_contain_type<T, Types...>::value, "variant does not contain given type");
    call_element_destructor();
    new (m_storage) T(f_inir, std::forward<CTorArguments>(f_args)...);
    m_type_index = internal::get_index_of_type<0, T, Types...>::index;
}

template <typename... Types>
template <std::size_t TypeIndex>
inline typename internal::get_type_at_index<0, TypeIndex, Types...>::type* Variant<Types...>::get_at_index() noexcept {
    if (TypeIndex != m_type_index) {
        return nullptr;
    }

    using T = typename internal::get_type_at_index<0, TypeIndex, Types...>::type;

    return static_cast<T*>(static_cast<void*>(m_storage));
}

template <typename... Types>
template <std::size_t TypeIndex>
inline const typename internal::get_type_at_index<0, TypeIndex, Types...>::type* Variant<Types...>::get_at_index() const
    noexcept {
    using T = typename internal::get_type_at_index<0, TypeIndex, Types...>::type;
    return const_cast<const T*>(const_cast<Variant*>(this)->get_at_index<TypeIndex>());
}

template <typename... Types>
template <typename T>
inline const T* Variant<Types...>::get() const noexcept {
    if (has_bad_variant_element_access<T>()) {
        return nullptr;
    } else {
        return static_cast<const T*>(static_cast<const void*>(m_storage));
    }
}

template <typename... Types>
template <typename T>
inline T* Variant<Types...>::get() noexcept {
    return const_cast<T*>(const_cast<const Variant*>(this)->get<T>());
}

template <typename... Types>
template <typename T>
inline T* Variant<Types...>::get_if(T* f_default_value) noexcept {
    return const_cast<T*>(const_cast<const Variant*>(this)->get_if<T>(const_cast<const T*>(f_default_value)));
}

template <typename... Types>
template <typename T>
inline const T* Variant<Types...>::get_if(const T* f_default_value) const noexcept {
    if (has_bad_variant_element_access<T>()) {
        return f_default_value;
    }
    return this->get<T>();
}

template <typename... Types>
constexpr bool Variant<Types...>::valueless_by_exception() const noexcept {
    return (m_type_index == INVALID_VARIANT_INDEX);
}

template <typename... Types>
constexpr size_t Variant<Types...>::index() const noexcept {
    return m_type_index;
}

template <typename... Types>
void Variant<Types...>::swap(Variant& rhs) noexcept {
    static_assert(internal::are_move_constructible<Types...>::value, "Not all types is move constructible");
    if (valueless_by_exception() && rhs.valueless_by_exception())
        return;
    std::swap(*this, rhs);
}

template <typename... Types>
template <typename T>
inline bool Variant<Types...>::has_bad_variant_element_access() const noexcept {
    static_assert(internal::does_contain_type<T, Types...>::value, "variant does not contain given type");
    return (m_type_index != internal::get_index_of_type<0, T, Types...>::index);
}

template <typename T, typename... Types>
inline constexpr bool holds_alternative(const Variant<Types...>& f_variant) noexcept {
    return f_variant.template get<T>() != nullptr;
}

template <class T, class... Types>
constexpr T* get_if(Variant<Types...>* f_variant_ptr) noexcept {
    return f_variant_ptr->template get<T>();
}

template <class T, class... Types>
constexpr const T* get_if(const Variant<Types...>* f_variant_ptr) noexcept {
    return f_variant_ptr->template get<T>();
}

}  // namespace core
}  // namespace ara
