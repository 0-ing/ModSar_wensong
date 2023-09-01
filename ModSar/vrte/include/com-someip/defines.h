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

#ifndef SRC_INTERFACE_DEFINES_H_
#define SRC_INTERFACE_DEFINES_H_

#include "primitive_types.h"

#include <iostream>

namespace ara
{
namespace com
{
namespace someip
{
#define SOMEIP_MSG_TYPE_IDX (14)
#define SOMEIP_MSG_HEADER_BYTES (16)
#define SOMEIP_PAYLOAD_LIMIT (1392)
#define SOMEIP_PV_HEADER (0x1)
#define SOMEIP_SID_MAGIC_COOKIE (0xFFFF)
#define SOMEIP_CID_MAGIC_COOKIE (0xDEAD)
#define SOMEIP_LEN_MAGIC_COOKIE (0x00000008)
#define SOMEIP_PVER_MAGIC_COOKIE (0x01)
#define SOMEIP_IVER_MAGIC_COOKIE (0x01)
#define SOMEIP_SES_ID_MAGIC_COOKIE (0xBEEF)
#define SOMEIP_MID_MAGIC_COOKIE_SERVER (0x8000)
#define SOMEIP_MID_MAGIC_COOKIE_CLIENT (0x0000)
#define SOMEIP_MSG_HEADER_BYTES (16)

#define SD_ENTRY_SIZE (16)
#define SD_METHOD_ID (0x8100)
#define SD_SERVICE_ID (0xFFFF)
#define SD_CLIENT_ID (0x0000)
#define SD_RESERVED_SIZE (1)
#define SD_PROTOCOL_VERSION (0x01)
#define SD_INTERFACE_VERSION (0x01)
#define SD_MESSAGE_TYPE (0x02)
#define SD_RETURN_CODE (0x00)
#define SD_MESSAGE_HEADER_SIZE (12)
#define SD_ENTRIES_HEADER_SIZE (4)
#define SD_OPTIONS_HEADER_SIZE (4)
#define SD_IPv4_ENDPOINT_MULTICAST_OPT_LENGTH (0x0009)
#define SD_IPv4_ENDPOINT_OPTION_LENGTH (0x0009)
#define SD_LENGTH_OF_ENTRIES_IDX (20)
#define SD_ENTRIES_ARRAY_IDX (24)
#define SD_OPTION_LENGTH_SIZE (2)
#define SD_OPTION_TYPE_SIZE (1)

#define TP_FLAG (0x20)
#define TP_OFFSET_BASE (16)
#define TP_REORDER_MAX_DISTANCE (3)
#define TP_MORE_SEGMENTS_FLAG (0x1)
#define TP_LAST_SEGMENT_FLAG (0x0)

#define TIME_UNIT (100)
#define TIME_ONE_SECOND_IN_MS_VAL (1000)
#define TIME_TIMEOUT_SECONDS (5)
#define TIME_TIMEOUT_USECONDS (0)
#define TIME_TIMEWAIT_ONE_SECOND (1)

#define UNDEFINED_PORT (0)
#define MAX_BUFFER_LEN (65507)
#define UDP_MTU (1500)
#define MAX_RETRY_COUNT (65535)
#define TCP_MAX_PEER_CONNECTION (20)
#define COM_PROTOCOL_VERSION (0x1)
#define NO_FLAG (0)
#define EMPTY (0)
#define FAIL_VALUE (-1)
#define UNINITIALIZED_SOCKET (-1)

#define SIZEOF_KB_IN_BYTES (1024)
#define SIZEOF_MB_IN_BYTES (1024 * SIZEOF_KB_IN_BYTES)

#define TP_HDR_LEN (4)
#define SD_HDR_LEN (12)
#define SOMEIP_HDR_LEN (8)
#define SOMEIP_HDR_FULL_LEN (16)
#define SOMEIP_AND_TP_HDR_LEN (SOMEIP_HDR_LEN + TP_HDR_LEN)
#define SOMEIP_AND_TP_HDR_FULL_LEN (SOMEIP_HDR_FULL_LEN + TP_HDR_LEN)
#define SOMEIP_SD_HDR_LEN (SOMEIP_HDR_LEN + SD_HDR_LEN)
#define SOMEIP_SD_HDR_FULL_LEN (SOMEIP_HDR_FULL_LEN + SD_HDR_LEN)

#define IDX_MESSAGE_ID (0)
#define IDX_SERVICE_ID (0)
#define IDX_METHOD_ID (2)
#define IDX_LENGTH (4)
#define IDX_SIGNAL_BASED_PAYLOAD (8)
#define IDX_REQUEST_ID (8)
#define IDX_CLIENT_ID (8)
#define IDX_SESSION_ID (10)
#define IDX_PROTOCOL_VER (12)
#define IDX_INTERFACE_VER (13)
#define IDX_MESSAGE_TYPE (14)
#define IDX_RETURN_CODE (15)
#define IDX_PAYLOAD (16)
#define IDX_TP_OFFSET (16)
#define IDX_TP_MORE_FLAG (19)
#define IDX_TP_PAYLOAD (20)

#define IDX_SD_ENTRIES_LENGTH (20)
#define IDX_SD_ENTRIES_ARRAY (24)

#define SIGNALBASED_HDR_FULL_LEN (8)

#define MAX_RETRY_SUBSCRIBE (255)

const uint16_t MIN_SESSION_ID  = 0x1;
const uint16_t MAX_SESSION_ID  = 0xFFFF;
const uint16_t ZERO_SESSION_ID = 0x0;
const size_t ERROR_MSG_SIZE    = 1024;

} // namespace someip
} // namespace com
} // namespace ara

#endif /* SRC_INTERFACE_DEFINES_HPP_ */
