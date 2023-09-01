//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2019 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================
//
/// @file      stmdemoclientaracompstatestatusservice.hpp
/// @brief     StM Dummy component state status serivce
/// @copyright Robert Bosch GmbH 2019
/// @author    VRTE StM Team
//=============================================================================

#ifndef DEMOCLIENTAPPARACOMPSTATUSSERVICE_HPP_INCLUDED
#define DEMOCLIENTAPPARACOMPSTATUSSERVICE_HPP_INCLUDED

#include <memory>
#include <string>

#include "ara/sm/impl_type_componentstateclientreturntype.h"
#include "ara/sm/triggerout_componentstatestatus_skeleton.h"
#include "Cmp_DemoClientAppCompStateStatusServiceCfg.hpp"

namespace bosch
{
namespace vrte
{
namespace stm
{
namespace democlient
{

class CDemoClientAppCompStateStatusServiceCfg::CDemoClientAppCompStateStatusServiceImpl
{
public:
    CDemoClientAppCompStateStatusServiceImpl(std::string f_instanceid, std::string f_compname);
    ara::core::Future<ara::sm::ComponentStateStatusType> getterComponentStateStatus(void);
    void updateComponentStateStatus(ara::sm::ComponentStateStatusType newstate);
    void registerGetHandler();

    std::string                                                                 m_compname;
    std::string                                                                 m_compstate;
    uint8_t                                                                     m_status;
    std::string                                                                 m_service_name;
    std::string                                                                 m_instance_id;
    std::shared_ptr<ara::sm::skeleton::TriggerOut_ComponentStateStatusSkeleton> m_eventskeleton;
};

}  // namespace democlient
}  // namespace stm
}  // namespace vrte
}  // namespace bosch

#endif  // DEMOCLIENTAPPARACOMPSTATUSSERVICE_HPP_INCLUDED
