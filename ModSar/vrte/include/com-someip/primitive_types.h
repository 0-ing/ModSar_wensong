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

#ifndef SOMEIP_PRIMITIVE_TYPES_H
#define SOMEIP_PRIMITIVE_TYPES_H

#include "enumeration_types.h"

#include <ara/core/string.h>
#include <ara/core/vector.h>
#include <functional>
#include <memory>

namespace ara
{
namespace com
{
namespace someip
{
using IP_address_t = ara::core::Vector<uint8_t>;

using message_id_t    = uint32_t;
using instance_id_t   = uint16_t;
using length_t        = uint32_t;
using session_id_t    = uint16_t;
using request_id_t    = uint32_t;
using protocol_ver_t  = uint8_t;
using interface_ver_t = uint8_t;
using message_type_t  = uint8_t;
using return_code_t   = uint8_t;
using major_version_t = uint8_t;
using minor_version_t = uint32_t;
using ttl_t           = uint32_t;

using method_id_t       = uint16_t;
using client_id_t       = uint16_t;
using service_id_t      = uint16_t;
using svc_instance_id_t = uint16_t;
using event_id_t        = uint16_t;
using eventgroup_id_t   = uint16_t;
using counter_t         = uint32_t;

using method_t       = method_id_t;
using client_t       = client_id_t;
using service_t      = service_id_t;
using event_t        = event_id_t;
using eventgroup_t   = eventgroup_id_t;
using event_group_t  = eventgroup_id_t;

using port_t = uint16_t;
using byte_t = uint8_t;

using time_t    = uint32_t;
using ip_addr_t = uint32_t;

using threshold_t = uint8_t;
using endpoint_t  = std::pair<ip_addr_t, port_t>;

using delay_t = uint32_t;

using byte_vector_t     = ara::core::Vector<uint8_t>;
using byte_vector_ptr_t = std::shared_ptr<byte_vector_t>;

template<typename T>
struct config_param_s
{
    T value           = T(0);
    bool is_set       = false;
    bool is_misconfig = false;
};

struct response_delay_s
{
    config_param_s<delay_t> minimum_delay;
    config_param_s<delay_t> maximum_delay;
};

using ip_endpoint_t      = std::pair<ara::core::String, port_t>;
using service_instance_t = std::pair<service_id_t, instance_id_t>;

using udp_send_cbk_t
    = std::function<void(byte_vector_t, ip_endpoint_t, ip_endpoint_t, e_send_trigger, service_instance_t)>;

struct service_discovery_config_s
{
    uint16_t port                                = 0;
    ara::core::String src_ipv4_address           = "";
    ara::core::String dst_ipv4_multicast_address = "";
    ara::core::String network_mask               = "";
};

struct event_endpoint_s
{
    ip_endpoint_t tcp;       // IP address and port for TCP communication
    ip_endpoint_t udp;       // IP address and port for UDP communication
    ip_endpoint_t multicast; // Multicast IP address and port
    event_endpoint_s()
    {
    }
    inline bool operator==(const event_endpoint_s& value) const
    {
        return (tcp == value.tcp && udp == value.udp);
    }

    inline bool operator<(const event_endpoint_s& value) const
    {
        return (std::tie(tcp, udp) < std::tie(value.tcp, value.udp));
    }
};

struct source_endpoint_s
{
    ara::core::String ip_addr = "";
    port_t tcp_port           = 0;
    port_t udp_port           = 0;
    source_endpoint_s() : ip_addr(""), tcp_port(0), udp_port(0)
    {
    }
    inline bool operator==(const source_endpoint_s& value) const
    {
        return (ip_addr == value.ip_addr && tcp_port == value.tcp_port && udp_port == value.udp_port);
    }

    inline bool operator<(const source_endpoint_s& value) const
    {
        return (std::tie(ip_addr, tcp_port, udp_port) < std::tie(value.ip_addr, value.tcp_port, value.udp_port));
    }
};

/*! \struct so_addr_info
 *  \brief  Contains socket information
 *  This is used as key for socket related maps
 */
struct so_addr_info
{
    bool is_reliable          = false;
    int port                  = 0;
    ara::core::String addr    = "";
    e_socket_type socket_type = e_socket_type::UNKNOWN;

    inline bool operator==(const so_addr_info& obj) const
    {
        return ((is_reliable == obj.is_reliable) && (port == obj.port) && (addr == obj.addr));
    }

    inline bool operator<(const so_addr_info& obj) const
    {
        return (std::tie(is_reliable, port, addr) < std::tie(obj.is_reliable, obj.port, obj.addr));
    }
};

} // namespace someip
} // namespace com
} // namespace ara

#endif
