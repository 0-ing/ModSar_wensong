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

#ifndef SOMEIP_ENUMERATION_TYPES_H
#define SOMEIP_ENUMERATION_TYPES_H

#include <cstdint>

namespace ara
{
namespace com
{
namespace someip
{
enum class entry_type : uint8_t
{
    FIND_SERVICE       = 0x00,
    OFFER_SERVICE      = 0x01,
    SUBS_EVENT_GRP     = 0x06,
    SUBS_EVENT_GRP_ACK = 0x07
};

enum class option_type : uint8_t
{
    CONFIGURATION    = 0x1,
    LOAD_BALANCING   = 0x2,
    IPv4_ENDPOINT    = 0x4,
    IPv4_MULTICAST   = 0x14,
    UNKNOWN          = 0xFF
};

enum class allowed_option_type : uint8_t
{
    CONFIGURATION  = 0x00,
    LOAD_BALANCING = 0x01,
    ENDPOINT       = 0x03,
    MULTICAST      = 0x04,
    UNKNOWN        = 0xFF
};

enum class protocol_type : uint8_t
{
    INIT    = 0x00,
    TCP     = 0x06,
    UDP     = 0x11,
    UDP_TCP = (protocol_type::TCP | protocol_type::UDP),
    UNKNOWN = 0xFF
};

enum class IdType : uint8_t
{
    METHOD_ID = 0x1,
    EVENT_ID,
    GENERAL_ID = 0xFF
};

// Enum for Timer Type
typedef enum
{
    TIMER_INIT_TYPE,
    SINGLE_SHOT_TIMER,
    PERIODIC_TIMER
} e_timer_type;

typedef enum
{
    CLS_INIT,
    CLS_LINK_UP,
    CLS_LINK_DOWN
} e_link_status;

enum class e_subscriber_state : uint8_t
{
    PENDING,
    SUBSCRIBED,
    UNSUBSCRIBED
};

enum class e_event_state : uint8_t
{
    TCP_UNICAST_ONLY,
    UDP_UNICAST_ONLY,
    UDP_MULTICAST_ONLY,
    CANNOT_SEND
};

enum class e_message_type : uint8_t
{
    REQUEST              = 0x00, // A request expecting a response
    REQUEST_NO_RETURN    = 0x01, // A fire & forget request
    NOTIFICATION         = 0x02, // A request notification/event callback expecting no response
    RESPONSE             = 0x80, // The response message
    ERROR                = 0x81, // The response containing the error
    TP_REQUEST           = 0x20, // A TP request expecting a response
    TP_REQUEST_NO_RETURN = 0x21, // A TP fire & forget request
    TP_NOTIFICATION      = 0x22, // A TP request notification/event callback expecting no response
    TP_RESPONSE          = 0xa0, // The TP response message
    TP_ERROR             = 0xa1  // The TP response containing an error
};

enum class e_return_code : uint8_t
{
    E_OK                      = 0x00, // No error occurred
    E_NOT_OK                  = 0x01, // An unspecified error occurred
    E_UNKNOWN_SERVICE         = 0x02, // The requested Service ID is unknown
    E_UNKNOWN_METHOD          = 0x03, // The requested Method ID is unknown. Service ID is known
    E_NOT_READY               = 0x04, // Service ID and Method ID are known. Application not running
    E_NOT_REACHABLE           = 0x05, // System running the service is not reachable
    E_TIMEOUT                 = 0x06, // A timeout occurred
    E_WRONG_PROTOCOL_VERSION  = 0x07, // Version of SOME/IP protocol not supported
    E_WRONG_INTERFACE_VERSION = 0x08, // Interface version mismatch
    E_MALFORMED_MESSAGE       = 0x09, // Deserialization error, so that payload cannot be deserialized
    E_WRONG_MESSAGE_TYPE      = 0x0A, // An unexpected message type was received
    E_E2E_REPEATED            = 0x0B, // Repeated E2E calculation error
    E_E2E_WRONG_SEQUENCE      = 0x0C, // Wrong E2E sequence error
    E_E2E                     = 0x0D, // Not further specified E2E error
    E_E2E_NOT_AVAILABLE       = 0x0E, // E2E not available
    E_E2E_NO_NEW_DATA         = 0x0F, // No new data for E2E calculation present
    E_UNKNOWN_EVENT           = 0x10, // The requested Event ID is unknown. Service ID is known
};

/**
 * \brief Configuration type
 *
 */
enum class e_config_app : uint8_t
{
    AA = 0x00, /**< Configuration for AA */
    SD         /**< Configuration for SD */
};

/**
 * \brief Configuration error codes
 *
 */
enum class E_Error_Code : uint8_t
{
    E_OK = 0x00,      /**< No error occurred */
    E_NOT_DEFINED,    /**< Parameter is not defined */
    E_NOT_SET,        /**< Value is not set */
    E_IS_ZERO,        /**< Value is set to 0 */
    E_EMPTY,          /**< Array is empty (Size is 0) */
    E_INVALID_VALUE,  /**< Value is invalid */
    E_OUT_OF_RANGE,   /**< Value is out of range */
    E_CANNOT_OPEN,    /**< Config file cannot be opened */
    E_INVALID_FORMAT, /**< Config file format is invalid */
    E_INVALID_IPV4_TX /**< IPv4 transmission protocol invalid */
};

enum class e_config_id_type : uint8_t
{
    E_UNDEFINED = 0x00,
    E_INT       = 0x01,
    E_HEX
};

enum class e_config_num_type : uint8_t
{
    E_MAJOR = 0x00,
    E_REPETITION_MAX,
    E_MULTICAST_THRESHOLD,
    E_ACCU_TRIGGER,
    E_COLLECT_TRIGGER,
    E_PORT = 0x10,
    E_TP_SEGMENT_LEN,
    E_ACCU_BUFFER_THRESHOLD,
    E_TTL   = 0x20,
    E_MINOR = 0x30,
    E_UDP_MAX_RCV_BUFFER,
    E_UDP_TP_WAIT_TIME
};

enum class e_socket_type : uint8_t
{
    UDP           = 0x00,
    UDP_MULTICAST = 0x01,
    TCP_CLIENT    = 0x02,
    TCP_SERVER    = 0x03,
    UNKNOWN       = 0xFF,
};

enum class e_launch_flag : uint8_t
{
    NEW_PORT_LAUNCH    = 0x01, // case: new    ip port && new    service instance
    SHARED_PORT_LAUNCH = 0x02, // case: opened ip port && new    service instance
    PORT_LAUNCHED      = 0x03, // case: opened ip port && opened service instance
    DONT_LAUNCH        = 0xFF,
    DEFAULT            = 0x00
};

enum class e_session_flag : uint8_t
{
    E_FOUND     = 0x01, // id is found in the map
    E_NOT_FOUND = 0x02, // id is not found in the map
    E_MAX_SIZE  = 0x03, // maximum size of the map is reached
};

enum class e_send_trigger : uint8_t
{
    NORMAL                = 0x01,
    TP_CALLBACK           = 0x02,
    ACCUMULATION_CALLBACK = 0x03
};

typedef enum
{
    TCP_UNICAST_ONLY,
    UDP_UNICAST_ONLY,
    UDP_MULTICAST_ONLY,
    CANNOT_SEND
} e_transport_protocol;

enum class thread_state : uint8_t
{
    E_IN_USE     = 0x00,
    E_AVAILABLE  = 0x01,
    E_FOR_RETURN = 0x02
};

enum class e_serializer : uint8_t
{
    E_SOMEIP      = 0x0,
    E_SIGNALBASED = 0x1
};

enum class e_config_ipv4 : uint8_t
{
    E_UNICAST   = 0x0,
    E_MULTICAST = 0x1,
    E_NETMASK   = 0x3
};

enum class e_availability_status : uint8_t
{
    E_FIND_TTL_EXPIRED  = 0x0,
    E_OFFER_TTL_EXPIRED = 0x1,
    E_UPDATED           = 0x3
};

enum class e_link_state_type : uint8_t
{
    E_LINK_UP      = 0x00,
    E_LINK_DOWN    = 0x01,
    E_LINK_UNKNOWN = 0x02
};

} // namespace someip
} // namespace com
} // namespace ara

#endif
