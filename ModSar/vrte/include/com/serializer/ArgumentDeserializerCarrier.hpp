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
/// @file      ArgumentDeserializerCarrier.hpp
/// @brief     Implementation for ArgumentDeserializerCarrier
/// @copyright Robert Bosch GmbH 2021
/// @author    crg2fe
//=============================================================================
#ifndef COM_SERIALIZER_ARGUMENT_DESERIALIZER_CARRIER
#define COM_SERIALIZER_ARGUMENT_DESERIALIZER_CARRIER

#include "IDeserializer.hpp"
#include "com/Types.hpp"

namespace com
{
namespace serializer
{
// Argument handling, can be directly used for fire and forget methods

template<size_t N, typename... Types>
class ArgumentDeserializerCarrier;

template<>
class ArgumentDeserializerCarrier<0>
{
public:
};

template<size_t N, typename T1, typename... Types>
class ArgumentDeserializerCarrier<N, T1, Types...>
{
public:
    template<typename T>
    using UniquePtr = ara::com::UniquePtr<T>;

    ArgumentDeserializerCarrier(UniquePtr<IDeserializer<T1>> dip,
                                UniquePtr<ArgumentDeserializerCarrier<N - 1, Types...>> adc)
        : desp(std::move(dip)), next(std::move(adc))
    {
    }

    UniquePtr<IDeserializer<T1>> desp;
    UniquePtr<ArgumentDeserializerCarrier<N - 1, Types...>> next;
};

} // namespace serializer
} // namespace com

#endif
