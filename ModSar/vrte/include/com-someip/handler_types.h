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

#ifndef SOMEIP_HANDLER_TYPES_H
#define SOMEIP_HANDLER_TYPES_H

#include "enumeration_types.h"
#include "message.h"

#include <functional>
#include <memory>

namespace ara
{
namespace com
{
namespace someip
{
using message_handler_t = std::function<void(const std::shared_ptr<message>&)>;
using availability_handler_t
    = std::function<void(service_id_t, instance_id_t, major_version_t, minor_version_t, bool, bool)>;
using sub_state_handler_t
    = std::function<void(service_id_t, instance_id_t, eventgroup_id_t, major_version_t, minor_version_t, event_id_t, bool)>;

} // namespace someip
} // namespace com
} // namespace ara

#endif
