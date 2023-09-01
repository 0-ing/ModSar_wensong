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

#ifndef SOMEIP_IF_MSG_H
#define SOMEIP_IF_MSG_H

#include "enumeration_types.h"
#include "primitive_types.h"

namespace ara
{
namespace com
{
namespace someip
{
class message
{
public:
    virtual void set_service_id(service_id_t svc_id)                      = 0;
    virtual void set_instance_id(instance_id_t inst_id)                = 0;
    virtual void set_method_id(method_id_t method_id)                     = 0;
    virtual void set_event_id(event_id_t event_id)                     = 0;
    virtual void set_length(length_t len)                              = 0;
    virtual void set_client_id(client_id_t client_id)                     = 0;
    virtual void set_session_id(session_id_t session_id)               = 0;
    virtual void set_request_id(request_id_t request_id)               = 0;
    virtual void set_protocol_version(protocol_ver_t protocol_version) = 0;
    virtual void set_interface_version(interface_ver_t if_version)     = 0;
    virtual void set_return_code(e_return_code return_code)            = 0;
    virtual void set_payload(ara::core::Vector<uint8_t> payload)       = 0;
    virtual void set_message_type(e_message_type message_type)         = 0;
    virtual service_id_t get_service_id()                                 = 0;
    virtual instance_id_t get_instance_id()                            = 0;
    virtual method_id_t get_method_id()                                   = 0;
    virtual event_id_t get_event_id()                                  = 0;
    virtual length_t get_length()                                      = 0;
    virtual client_id_t get_client_id()                                   = 0;
    virtual session_id_t get_session_id()                              = 0;
    virtual request_id_t get_request_id()                              = 0;
    virtual protocol_ver_t get_protocol_version()                      = 0;
    virtual interface_ver_t get_interface_version()                    = 0;
    virtual e_return_code get_return_code()                            = 0;
    virtual ara::core::Vector<uint8_t> get_payload()                   = 0;
    virtual e_message_type get_message_type()                          = 0;
};
} // namespace someip
} // namespace com
} // namespace ara

#endif
