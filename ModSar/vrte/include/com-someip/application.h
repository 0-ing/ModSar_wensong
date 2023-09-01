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

#ifndef SOMEIP_IF_APL_H
#define SOMEIP_IF_APL_H

#include "constants.h"
#include "handler_types.h"
#include "message.h"
#include "primitive_types.h"

#include <ara/core/map.h>
#include <memory>
#include <tuple>

namespace ara
{
namespace com
{
namespace someip
{
class application
{
public:
    virtual ~application()
    {
    }

    virtual bool init()                                         = 0;
    virtual void start()                                        = 0;
    virtual void stop()                                         = 0;
    virtual void send_message(std::shared_ptr<message> message) = 0;

    virtual void offer_service(service_id_t service_id,
                               instance_id_t instance_id,
                               major_version_t major_version,
                               minor_version_t minor_version)
        = 0;
    virtual void stop_offer_service(service_id_t service_id,
                                    instance_id_t instance_id,
                                    major_version_t major_version,
                                    minor_version_t minor_version)
        = 0;
    virtual bool is_available(service_id_t service_id,
                              instance_id_t instance_id,
                              major_version_t major_version,
                              minor_version_t minor_version)
        = 0;
    virtual void get_available_instances(
        std::shared_ptr<ara::core::Map<std::tuple<service_id_t, instance_id_t, major_version_t, minor_version_t>, bool>>
            service_instances)
        = 0;

    virtual void register_availability_handler(service_id_t service_id,
                                               instance_id_t instance_id,
                                               availability_handler_t handler,
                                               major_version_t major,
                                               minor_version_t minor)
        = 0;
    virtual void unregister_availability_handler(service_id_t service_id,
                                                 instance_id_t instance_id,
                                                 major_version_t major,
                                                 minor_version_t minor)
        = 0;

    virtual void subscribe(service_id_t service_id,
                           instance_id_t instance_id,
                           eventgroup_id_t eventgroup_id,
                           major_version_t major,
                           minor_version_t minor,
                           event_id_t event_id = ANY_EVENT)
        = 0;
    virtual void unsubscribe(service_id_t service_id,
                             instance_id_t instance_id,
                             eventgroup_id_t eventgroup_id,
                             event_id_t event_id,
                             major_version_t major = ANY_MAJOR,
                             minor_version_t minor = ANY_MINOR)
        = 0;

    virtual void register_subscriptionstate_handler(service_id_t service_id,
                                                    instance_id_t instance_id,
                                                    eventgroup_id_t eventgroup_id,
                                                    major_version_t major,
                                                    minor_version_t minor,
                                                    event_id_t event_id,
                                                    sub_state_handler_t handler)
        = 0;
    virtual void unregister_subscriptionstate_handler(service_id_t service_id,
                                                      instance_id_t instance_id,
                                                      eventgroup_id_t eventgroup_id,
                                                      major_version_t major,
                                                      minor_version_t minor,
                                                      event_id_t event_id)
        = 0;

    virtual void register_message_handler(service_id_t service_id,
                                          instance_id_t instance_id,
                                          major_version_t major,
                                          minor_version_t minor,
                                          method_id_t method_id,
                                          message_handler_t message_handler)
        = 0;
    virtual void unregister_message_handler(service_id_t service_id,
                                            instance_id_t instance_id,
                                            major_version_t major,
                                            minor_version_t minor,
                                            method_id_t method_id)
        = 0;
};

} // namespace someip
} // namespace com
} // namespace ara

#endif // SOMEIP_IF_APL_H
