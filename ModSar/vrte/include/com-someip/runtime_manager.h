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

#ifndef SOMEIP_LIB_APL_MGR_IMPL_H
#define SOMEIP_LIB_APL_MGR_IMPL_H

#include "application.h"
#include "ara/core/map.h"
#include "ara/core/string.h"
#include "defines.h"
#include "message.h"

#include <iostream>
#include <memory>
#include <mutex>

namespace ara
{
namespace com
{
namespace someip
{
class runtime_manager
{
public:
    std::shared_ptr<application> create_application(ara::core::String apl_name = "");

    std::shared_ptr<message> create_message();

    void delete_application(ara::core::String apl_name);

private:
    bool m_cfg_loaded = false;
    std::map<ara::core::String, std::shared_ptr<application>> m_apl_map;

    mutable std::mutex m_apl_map_mutex;
};

} // namespace someip
} // namespace com
} // namespace ara

#endif // SOMEIP_LIB_APL_MGR_IMPL_H
