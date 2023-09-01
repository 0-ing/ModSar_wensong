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
/// @file      ISerializer.hpp
/// @brief     Interface Class for serialization
/// @copyright Robert Bosch GmbH 2021
/// @author    mtk2abt
//=============================================================================
#ifndef COM_SERIALIZER_ISERIALIZER_HPP
#define COM_SERIALIZER_ISERIALIZER_HPP

#include "stdint.h"

namespace com
{
namespace serializer
{
template<typename SampleType_T>
class ISerializer
{
public:
    /** \brief Virtual destructor required to allow deleting via the interface */
    virtual ~ISerializer() = default;

    // In order to know how much shared memory we have to allocate we have to know how big the serialized object becomes
    virtual uint32_t computeSerializedSize(const SampleType_T* objectp) = 0;

    // In order to serialize we have to know where to put the serialized data, how much data can be written there
    // and what to serialize; the return value is the success of the serialization (true = success, false = something
    // went wrong)
    virtual bool serialize(uint8_t* targetbuffer, uint32_t maxsize, const SampleType_T* objectp) = 0;
};

} /* namespace serializer */
} /* namespace com */

#endif // COM_SERIALIZER_ISERIALIZER_HPP