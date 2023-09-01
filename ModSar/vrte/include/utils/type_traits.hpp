//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file      type_traits.hpp
/// @brief     Metaprogramming support struct to remove cv qualifiers
/// @copyright Robert Bosch GmbH  2018
/// @author    baetz

#ifndef QNX_EXM_DELIVERABLES_SRC_UTILS_INC_UTILS_TYPE_TRAITS_HPP_
#define QNX_EXM_DELIVERABLES_SRC_UTILS_INC_UTILS_TYPE_TRAITS_HPP_

#include <stdint.h>
#include <stddef.h>

#include <type_traits>

namespace exm
{

namespace utils
{

/// @brief Metaprogramming support struct to remove cv qualifiers.
/// Base template does not change type.
template<typename T>
struct RemoveQualifiers
{
    typedef T type;///< type of data
};

/// @brief Specialization to remove const.
template<typename T>
struct RemoveQualifiers<T const>
{
    typedef T type;///< type of data
};

/// @brief Specialization to remove volatile.
template<typename T>
struct RemoveQualifiers<T volatile>
{
    typedef T type;///< type of data
};

/// @brief Specialization to remove const volatile.
template<typename T>
struct RemoveQualifiers<T const volatile>
{
    typedef T type;///< type of data
};

/// @brief Metaprogramming helper struct to remove pointer type
template<typename T>
using RemovePointer_t = typename std::remove_pointer<T>::type;


/// @brief Metaprogramming helper struct to identify integral numbers and assign a true / false value.
/// Base template sets value to false.
template<typename T>
struct IsIntegralNumber_
{
    typedef IsIntegralNumber_<T> type;///< type of integral number
    static constexpr bool value = false;///< if number is integral or not
};

/// @brief Specialization to identify integer type.
template<>
struct IsIntegralNumber_<bool>
{
    typedef IsIntegralNumber_<bool> type;///< bool type of integral number
    static constexpr bool value = true;///< whether the number is integral bool 
};

/// @brief Specialization to identify integer type.
template<>
struct IsIntegralNumber_<char>
{
    typedef IsIntegralNumber_<char> type;///< char type of integral number
    static constexpr bool value = true;///< whether the number is integral char
};

/// @brief Specialization to identify integer type.
template<>
struct IsIntegralNumber_<uint8_t>
{
    typedef IsIntegralNumber_<uint8_t> type;///< uint8 type of integral number
    static constexpr bool value = true;///< whether the number is integral uint8
};

/// @brief Specialization to identify integer type.
template<>
struct IsIntegralNumber_<int8_t>
{
    typedef IsIntegralNumber_<int8_t> type;///< int8 type of integral number
    static constexpr bool value = true;///< whether the number is integral int8
};

/// @brief Specialization to identify integer type.
template<>
struct IsIntegralNumber_<uint16_t>
{
    typedef IsIntegralNumber_<uint16_t> type;///< uint16 type of integral number
    static constexpr bool value = true;///< whether the number is integral uint16
};

/// @brief Specialization to identify integer type.
template<>
struct IsIntegralNumber_<int16_t>
{
    typedef IsIntegralNumber_<int16_t> type;///< int16 type of integral number
    static constexpr bool value = true;///< whether the number is integral int16
};

/// @brief Specialization to identify integer type.
template<>
struct IsIntegralNumber_<uint32_t>
{
    typedef IsIntegralNumber_<uint32_t> type;///< uint32 type of integral number
    static constexpr bool value = true;///< whether the number is integral uint32
};

/// @brief Specialization to identify integer type.
template<>
struct IsIntegralNumber_<int32_t>
{
    typedef IsIntegralNumber_<int32_t> type;///< int32 type of integral number
    static constexpr bool value = true;///< whether the number is integral int32
};

/// @brief Specialization to identify integer type.

template<>
struct IsIntegralNumber_<uint64_t>
{
    typedef IsIntegralNumber_<uint64_t> type;///< uint64 type of integral number
    static constexpr bool value = true;///< whether the number is integral uint64
};

/// @brief Specialization to identify integer type.

template<>
struct IsIntegralNumber_<int64_t>
{
    typedef IsIntegralNumber_<int64_t> type;///< int64 type of integral number
    static constexpr bool value = true;///< whether the number is integral int64
};

/// @brief User side metaprogramming struct to identify integral numbers.
/// Makes use of IsIntegralNumber_ helper.

template<typename T>
struct IsIntegralNumber: public IsIntegralNumber_<
        typename RemoveQualifiers<T>::type>::type
{

};

/// @brief Metaprogramming class to identify derived classes.
/// Makes use of function overloading resolution and different type sizes to
/// test if sub is derived from base.
/// The enum value Is is true if sub is derived from base, and false else.

template<typename sub, typename base>
class IsDerivedFrom
{
private:
    class No
    {
    };
    ///@brief To check if sub is derived from base
    class Yes
    {
        No no[3];///< array of object of empty class
    };

    static Yes Test(base*); ///<member function to test is sub is derived
    static No Test(...); ///< member function for non derived sub           // PRQA S 2012 # This is only done at a type-level and it does not matter if a short is cast to an int because it would still choose the same overload (which is the only thing that matters in this specific case)
public:
    /// @brief Is true if sub is derived from base, and false else.
    enum
    {
        Is = sizeof(Test(static_cast<sub*>(0))) == sizeof(Yes)
    };

};

/// @brief Metaprogramming class to enable a certain template specialization if the first template parameter is true.
/// Default template is for false and will not be used as it does not define type.


template<bool, typename T = void>
struct EnableIf
{
};

/// @brief Partial specialization for true.

template<typename T>
struct EnableIf<true, T>
{
    typedef T type;///< data of given type
};

/// @brief Metaprogramming element to get the underlying integer type of an enum.
/// WARNING: The struct makes use of the built-in call
/// __underlying_type. If something else than an enum is
/// taken as T, a compile-time error is produced.
/// @return The underlying integer type of an enum

template<typename T>
struct UnderlyingType
{
    typedef __underlying_type(T) type;///< type of enum
};

/// @brief Metaprogramming element to determine if a type T is an enum type.
/// WARNING: Makes use of the built-in call __is_enum() to do the actual work.

template<typename T>
struct IsEnum
{
    static constexpr bool value = __is_enum(T);///< Is enum check result
};


/// @brief Aligned storage helper struct for <Len> no. of Bytes and <Align> alignment
/// If no alignment is specified, derive the system's default from size_t
template<size_t Len, size_t Align = alignof(size_t)>
struct AlignedStorage
{
    struct type
    {
        alignas(Align) uint8_t data[Len];
    };
};

/// @brief Aligned storage helper struct for <Len> no. of Bytes and <Align> alignment
/// Typedef wrapper
template<size_t Len, size_t Align = alignof(size_t)>
using AlignedStorage_t = typename AlignedStorage<Len, Align>::type;


}  // namespace utils

}  // namespace exm









#endif // QNX_EXM_DELIVERABLES_SRC_UTILS_INC_UTILS_TYPE_TRAITS_HPP_
