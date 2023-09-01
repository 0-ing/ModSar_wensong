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
/// @file      IDeserializer.hpp
/// @brief     Interface Class for deserialization
/// @copyright Robert Bosch GmbH 2021
/// @author    mtk2abt
//=============================================================================
#ifndef COM_SERIALIZER_IDESERIALIZER_HPP
#define COM_SERIALIZER_IDESERIALIZER_HPP

#include "stdint.h"

namespace com
{
namespace serializer
{
template<typename SampleType_T>
class IDeserializer
{
public:
    /** \brief Virtual destructor required to allow deleting via the interface */
    virtual ~IDeserializer() = default;

    // In order to deserialize we have to know where to put the deserialized object and
    // how much data can be read from which buffer
    // the return value is the success of the deserialization (true = success, false = something went wrong)
    // additionally the number of read bytes is written into the uint32_t pointed to by readbytes
    virtual bool deserialize(const uint8_t* receivebuffer, uint32_t length, SampleType_T* objectp, uint32_t* readbytes)
        = 0;
};

} // namespace serializer
} // namespace com

#endif // COM_SERIALIZER_IDESERIALIZER_HPP