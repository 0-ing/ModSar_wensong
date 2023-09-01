//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2020 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================
//
/// @file         src/ucm/mock/any.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Hans Berghaell
/// @version
/// @remarks

#ifndef UCM_AAP_BUILD_UCM_MOCK_ANY_H_
#define UCM_AAP_BUILD_UCM_MOCK_ANY_H_

#include "ucm/mock/bit_flags.h"

#include <stdexcept>
#include <type_traits>
#include <utility>
#include <iostream>

namespace bosch    {
namespace vrte     {
namespace ucm      {
namespace mock     {

struct Any final
{
private:
    enum  Property { Void, Ref, RRef, Const };
    using Properties = BitFlags<Property>;
    using Deleter    = void (*)(void*);
    using Thrower    = void (*)(Any&);

    // specific helpers for the GetRhs default predicate
    template<bool P, typename T> using AddConst =
        typename std::conditional<P, T const, T>::type;
    template<bool P, typename T> using AddRef =
        typename std::conditional<P, T &&, T&>::type;
    template<typename T, bool C, bool R> using Constructible =
        std::is_constructible<T, AddRef<R, AddConst<C, T>>>;   

    template<typename T, bool = std::is_reference<T>::value> struct Make;
    template<typename T, bool = std::is_reference<T>::value> struct Get;
    template<typename T, bool C, bool R,
        bool = Constructible<T, C, R>::value> struct GetRhs;

    template<typename, bool            > friend class Make;
    template<typename, bool            > friend class Get;
    template<typename, bool, bool, bool> friend class GetRhs;


    Deleter    deleter    {nullptr};
    Thrower    thrower    {nullptr};
    void*      storage    {nullptr};
    Properties properties {};

    template<typename U> static void delete_(void* ptr)
    {
        delete static_cast<U*>(ptr);
    }

    template<typename U> static void throw_(Any& arg)
    {
        throw arg.get_<U>();
    }

    template<typename T>
    T get_()
    {
        Any lhs = Make<T>::init();
        if (not storage and not properties.is<Void>()) {
            std::cout << "Any::get empty from object!\n";
            std::exit(1);
        }
        if (lhs.deleter != deleter) {
            std::cout << "Any::get type error\n";
            std::exit(1);
        }
        return Get<T>::value(lhs, *this);
    }

public:
    template<typename T, typename... U>
    static Any make(U&&... u)
    {
        Any res = Make<T>::init();
        res.storage = Make<T>::storage(static_cast<U&&>(u)...);
        return res;
    }

    template<typename T, typename... U>
    static Any make_exception(U&&... u)
    {
        Any res = make<T>(static_cast<U&&>(u)...);
        res.thrower = throw_<T>;
        return res;
    }

    Any() = default;

    ~Any()
    {
        if (not properties.is<Ref>() and deleter and storage)
            deleter(storage);
    }

    Any(Any&& arg) noexcept
        : deleter   (arg.deleter)
        , thrower   (arg.thrower)
        , storage   (arg.storage)
        , properties(arg.properties)
    {
        if (not properties.is<Ref>())
            arg.storage = nullptr;
    }

    Any(Any const&) = delete;
    Any& operator = (Any &&) = delete;
    Any& operator = (Any const&) = delete;

    template<typename T>
    T get()
    {
        if (thrower)
            thrower(*this);
        return get_<T>();
    }
};

template<typename T> struct Any::Make<T, false>
{
    static Any init()
    {
        using V = typename std::remove_cv<T>::type;
        Any res;
        res.deleter = delete_<V>;
        res.properties.is<Const>(std::is_const<T>::value); 
        static_assert(not std::is_volatile<T>::value, "volatile not supported");
        return res;
    }

    template<typename... U> static void* storage (U&&... u)
    {
        using V = typename std::remove_cv<T>::type;
        return new V (static_cast<U&&>(u)...);
    }
};

template<> struct Any::Make<void, false>
{
    static Any init()
    {
        Any res;
        res.deleter = nullptr;
        res.properties.is<Void>(true); 
        return res;
    }

    template<typename... U> static void* storage (U&&... u)
    {
        return nullptr;
    }
};

template<typename T> struct Any::Make<T, true>
{
    static Any init()
    {
        using U = typename std::remove_reference<T>::type;
        using V = typename std::remove_cv<U>::type;
        Any res;
        res.deleter = delete_<V>;
        res.properties.is<Const>(std::is_const<U>::value); 
        res.properties.is<Ref  >(true); 
        res.properties.is<RRef >(std::is_rvalue_reference<U>::value); 
        return res;
    }

    static void* storage (T&& t)
    {
        using U = typename std::remove_reference<T>::type;
        return const_cast<typename std::remove_cv<U>::type*>(&t);
    }
};

// lhs reference
template<typename T> struct Any::Get<T, true>
{
    static T value (Any& lhs, Any& rhs)
    {
        using U = typename std::remove_reference<T>::type;
        if(rhs.properties.is<Const>() and not lhs.properties.is<Const>()) {
            std::cout << "Any::get const error\n";
            std::exit(1);
        }
        if(not rhs.properties.is<Ref>()) {
            std::cout << "Any::get dangling reference\n";
            std::exit(1);
        }
        return static_cast<T>(*static_cast<U*>(rhs.storage));
    }
};

// lhs void
template<> struct Any::Get<void, false>
{
    static void value (Any const&, Any&) {}
};

// lhs value
template<typename T> struct Any::Get<T, false>
{
    static T value (Any const&, Any& rhs)
    {
        if (rhs.properties.is<Const>()) {
            if (not rhs.properties.is<Ref>() or rhs.properties.is<RRef>())
                return GetRhs<T, true, true>::value(rhs);
            return GetRhs<T, true, false>::value(rhs);
        }
        if (not rhs.properties.is<Ref>() or rhs.properties.is<RRef>())
            return GetRhs<T, false, true>::value(rhs);
        return GetRhs<T, false, false>::value(rhs);
    }
};

// lhs not constructible from rhs
template<typename T, bool C, bool R> struct Any::GetRhs<T, C, R, false>
{
    static T value (Any& rhs)
    {
        std::cout << __PRETTY_FUNCTION__ << " not constructible\n";
        std::exit(1);
    }
};

// T (T&)
template<typename T> struct Any::GetRhs<T, false, false, true>
{
    static T value (Any& rhs)
    {
        return T (*static_cast<T*>(rhs.storage));
    }
};

// T (T &&)
template<typename T> struct Any::GetRhs<T, false, true, true>
{
    static T value (Any& rhs)
    {
        return T (std::move(*static_cast<T*>(rhs.storage)));
    }
};

// T (T const &)
template<typename T> struct Any::GetRhs<T, true, false, true>
{
    static T value (Any& rhs)
    {
        return T (*static_cast<T const*>(rhs.storage));
    }
};

// T (T const &&)
template<typename T> struct Any::GetRhs<T, true, true, true>
{
    static T value (Any& rhs)
    {
        return T (std::move(*static_cast<T const*>(rhs.storage)));
    }
};

} // namespace mock
} // namespace ucm
} // namespace vrte
} // namespace bosch

#endif // UCM_AAP_BUILD_UCM_MOCK_ANY_H_
