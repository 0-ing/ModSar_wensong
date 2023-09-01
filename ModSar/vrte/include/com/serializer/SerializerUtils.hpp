//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2022 by DENSO CORPORATION and Robert Bosch GmbH.
// All rights reserved.
//
// This file is property of DENSO CORPORATION and Robert Bosch GmbH. Any
// unauthorized copy, use or distribution is an offensive act against
// international law and may be prosecuted under federal law. Its content is
// company confidential.
//=============================================================================
#ifndef COM_SERIALIZER_SERIALIZERUTILS_HPP
#define COM_SERIALIZER_SERIALIZERUTILS_HPP

#include "stdint.h"

namespace com
{
namespace serializer
{
static constexpr const uint32_t bigEndianConfig = 0;
static constexpr const uint32_t littleEndianConfig = 1;
static constexpr const uint32_t opaqueConfig = 2;

//Check if you need to change the byte order
inline bool judgeByteOrder(uint32_t config_endian)
{
    bool ret = false;

    if(config_endian == opaqueConfig)
    {
        // opaque
        ret = false;
    }
    else
    {
        uint32_t x = 1;
        // If machine is little endian, machine_endian is 0x1 and if machine is big endian, machine_endian is 0x0.
        uint32_t machine_endian = static_cast<uint32_t>(*(static_cast<char*>(static_cast<void*>(&x))));

        if(machine_endian == config_endian)
        {
            // If endian is same, false
            ret = false;
        }
        else
        {
            // If endian is different, true
            ret = true;
        }
    }

    return ret;
}

//Swap 2-byte data for the byte order conversion
inline uint16_t swap16(uint16_t val)
{
    uint16_t ret = 0;
    ret  = static_cast<uint16_t>(val << 8);
    ret |= static_cast<uint16_t>(val >> 8);
    return ret;
}

//Swap 4-byte data for the byte order conversion
inline uint32_t swap32(uint32_t val)
{
    uint32_t ret = 0;
    ret  = val << 24;
    ret |= (val & 0x0000FF00) << 8;
    ret |= (val & 0x00FF0000) >> 8;
    ret |= val >> 24;
    return ret;
}

//Swap 8-byte data for the byte order conversion
inline uint64_t swap64(uint64_t val)
{
    uint64_t ret = 0;
    ret  = val << 56;
    ret |= (val & 0x000000000000FF00) << 40;
    ret |= (val & 0x0000000000FF0000) << 24;
    ret |= (val & 0x00000000FF000000) << 8;
    ret |= (val & 0x000000FF00000000) >> 8;
    ret |= (val & 0x0000FF0000000000) >> 24;
    ret |= (val & 0x00FF000000000000) >> 40;
    ret |= val >> 56;
    return ret;
}

} // namespace serializer
} // namespace com
#endif // COM_SERIALIZER_SERIALIZERUTILS_HPP
