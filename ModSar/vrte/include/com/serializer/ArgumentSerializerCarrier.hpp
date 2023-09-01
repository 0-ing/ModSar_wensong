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
/// @file      ArgumentSerializerCarrier.hpp
/// @brief     Implementation for ArgumentSerializerCarrier
/// @copyright Robert Bosch GmbH 2021
/// @author    crg2fe
//=============================================================================
#ifndef COM_SERIALIZER_ARGUMENT_SERIALIZER_CARRIER
#define COM_SERIALIZER_ARGUMENT_SERIALIZER_CARRIER

#include "ISerializer.hpp"
#include "ara/com/types.h"

namespace com
{
namespace serializer
{
// Argument handling, can be directly used for fire and forget methods

template<size_t N, typename... Types>
class ArgumentSerializerCarrier;

template<>
class ArgumentSerializerCarrier<0>
{
public:
};

template<size_t N, typename T1, typename... Types>
class ArgumentSerializerCarrier<N, T1, Types...>
{
public:
    template<typename T>
    using UniquePtr = ara::com::UniquePtr<T>;

    ArgumentSerializerCarrier(UniquePtr<ISerializer<T1>> sip, UniquePtr<ArgumentSerializerCarrier<N - 1, Types...>> asc)
        : serp(std::move(sip)), next(std::move(asc))
    {
    }

    UniquePtr<ISerializer<T1>> serp;
    UniquePtr<ArgumentSerializerCarrier<N - 1, Types...>> next;
};

} // namespace serializer
} // namespace com

#endif
