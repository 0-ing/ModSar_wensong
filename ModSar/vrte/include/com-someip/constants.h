//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021-2022 by DENSO CORPORATION. All rights reserved.
//
// This file is property of DENSO CORPORATION. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/**
 * \file
 */

#ifndef SOMEIP_CONSTANTS_H
#define SOMEIP_CONSTANTS_H

#include "defines.h"
#include "primitive_types.h"

#include <cstdint>

namespace ara
{
namespace com
{
namespace someip
{
const event_id_t ANY_EVENT           = 0xFFFF;
const method_id_t ANY_METHOD         = 0x7FFF;
const service_id_t ANY_SERVICE       = 0xFFFF;
const instance_id_t ANY_INSTANCE     = 0xFFFF;
const eventgroup_id_t ANY_EVENTGROUP = 0xFFFF;
const major_version_t ANY_MAJOR      = 0xFF;
const minor_version_t ANY_MINOR      = 0xFFFFFFFF;
const uint8_t MSG_ID_HEADER_SIZE     = 4;
const uint8_t LEN_HEADER_SIZE        = 4;

} // namespace someip
} // namespace com
} // namespace ara

#endif