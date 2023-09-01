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
/// @file      democlientaracompstatestatusservice.cpp
/// @brief
/// @copyright Robert Bosch GmbH 2019
/// @author    VRTE StM Team
//=============================================================================

#include "Cmp_DemoClientAppAraCompStateStatusService.hpp"
#include "componentclientenum.hpp"
#include "Cmp_DemoClientLogger.hpp"

#define CONFIG CDemoClientAppCompStateStatusServiceCfg

namespace bosch
{
namespace vrte
{
namespace stm
{
namespace democlient
{

using namespace ara::sm;
// CDemoClientAppCompStateStatusServiceImpl Implementation
CONFIG::CDemoClientAppCompStateStatusServiceImpl::CDemoClientAppCompStateStatusServiceImpl(std::string f_instance_id,
                                                                                           std::string f_compname)
    : m_service_name("CompStateStatusService" + f_instance_id)
    , m_instance_id(f_instance_id)
    , m_eventskeleton(nullptr)
    , m_compname(f_compname)
    , m_compstate("kInit")
    , m_status(INVALID_COMP_STATE_STATUS)
{
}

ara::core::Future<ara::sm::ComponentStateStatusType>
CONFIG::CDemoClientAppCompStateStatusServiceImpl::getterComponentStateStatus(void)
{
    // /*create promise*/
    ara::core::Promise<ara::sm::ComponentStateStatusType> promise;
    ara::sm::ComponentStateStatusType                     currentstate;

    // /*set value of promise*/
    currentstate.Component = m_compname;
    currentstate.State     = m_compstate;
    currentstate.Status = static_cast<ara::sm::ComponentStateClientReturnType>(m_status);
    promise.set_value(currentstate);

    // /*return future of already set promise*/
    return promise.get_future();
}

void CONFIG::CDemoClientAppCompStateStatusServiceImpl::updateComponentStateStatus(
    ara::sm::ComponentStateStatusType newstate)
{
    m_eventskeleton->ComponentStateStatus.Update(newstate);
}

void CONFIG::CDemoClientAppCompStateStatusServiceImpl::registerGetHandler()
{
    m_eventskeleton->ComponentStateStatus.RegisterGetHandler(
        std::bind(&CDemoClientAppCompStateStatusServiceImpl::getterComponentStateStatus, this));
}

// CDemoClientAppCompStateStatusServiceCfg Implementation
CDemoClientAppCompStateStatusServiceCfg::CDemoClientAppCompStateStatusServiceCfg(std::string f_instance_id,
                                                                                 std::string f_compname)
{
    m_CompStateStatusServiceImpl =
        std::make_shared<CDemoClientAppCompStateStatusServiceImpl>(f_instance_id, f_compname);
    DEMO_CLIENT_APP_DEBUG(m_CompStateStatusServiceImpl->m_service_name, " with instance id ", f_instance_id);
}

void CDemoClientAppCompStateStatusServiceCfg::vInitService()
{
    DEMO_CLIENT_APP_DEBUG(m_CompStateStatusServiceImpl->m_service_name, " vInitService");
    ara::com::InstanceIdentifier l_instance((m_CompStateStatusServiceImpl->m_instance_id).c_str());
    m_CompStateStatusServiceImpl->m_eventskeleton =
        std::make_shared<ara::sm::skeleton::TriggerOut_ComponentStateStatusSkeleton>(l_instance);
    if (nullptr == m_CompStateStatusServiceImpl->m_eventskeleton)
    {
        DEMO_SERVER_APP_ERROR(m_CompStateStatusServiceImpl->m_service_name, " can not allocate the skeleton ");
    }
    m_CompStateStatusServiceImpl->registerGetHandler();
}

void CDemoClientAppCompStateStatusServiceCfg::vStartService()
{
    ara::sm::ComponentStateStatusType initstate;  // m_compname m_compstate
    initstate.Component = m_CompStateStatusServiceImpl->m_compname;
    initstate.State     = m_CompStateStatusServiceImpl->m_compstate;

    initstate.Status = static_cast<ara::sm::ComponentStateClientReturnType>(m_CompStateStatusServiceImpl->m_status);
    DEMO_CLIENT_APP_DEBUG(m_CompStateStatusServiceImpl->m_service_name, " Init the ComponentStateClientReturnType: ",
                          static_cast<uint32_t>(m_CompStateStatusServiceImpl->m_status));
    m_CompStateStatusServiceImpl->updateComponentStateStatus(initstate);
    DEMO_CLIENT_APP_DEBUG(m_CompStateStatusServiceImpl->m_service_name, " offer service");
    m_CompStateStatusServiceImpl->m_eventskeleton->OfferService();
}
#if 0
void CDemoClientAppCompStateStatusServiceCfg::updateComponentStateStatus(ara::sm::ComponentStateStatusType initstate)
{
    ara::sm::ComponentStateStatusType initstate;  // m_compname m_compstate
    initstate.Component = m_CompStateStatusServiceImpl->m_compname;
    initstate.State     = m_CompStateStatusServiceImpl->m_compstate;
    initstate.Status    = static_cast<ara::sm::ComponentStateClientReturnType>(m_CompStateStatusServiceImpl->m_status);
    m_CompStateStatusServiceImpl->updateComponentStateStatus(initstate);
    m_CompStateStatusServiceImpl->m_eventskeleton->OfferService();
}
#endif
void CDemoClientAppCompStateStatusServiceCfg::vStopService()
{
    DEMO_CLIENT_APP_DEBUG(m_CompStateStatusServiceImpl->m_service_name, " stop service");
    m_CompStateStatusServiceImpl->m_eventskeleton->StopOfferService();
}

void CDemoClientAppCompStateStatusServiceCfg::vUpdateComponentClientReturn(uint8_t f_ret)
{
    if (f_ret != m_CompStateStatusServiceImpl->m_status)
    {
        m_CompStateStatusServiceImpl->m_status = f_ret;
        DEMO_CLIENT_APP_DEBUG(m_CompStateStatusServiceImpl->m_service_name,
                              " Update the ComponentStateClientReturnType: ",
                              static_cast<uint32_t>(m_CompStateStatusServiceImpl->m_status));
    }
}

void CDemoClientAppCompStateStatusServiceCfg::vUpdateComponentState(std::string f_state)
{
    if (f_state != m_CompStateStatusServiceImpl->m_compstate)
    {
        m_CompStateStatusServiceImpl->m_compstate = f_state;
        DEMO_CLIENT_APP_DEBUG(m_CompStateStatusServiceImpl->m_service_name,
                              " Update the Component state: ", m_CompStateStatusServiceImpl->m_compstate);
    }
}

void CDemoClientAppCompStateStatusServiceCfg::vComponentStateConfirm()
{
    ara::sm::ComponentStateStatusType newstate;
    // for loop copying data, ugly code ...
    newstate.Component = m_CompStateStatusServiceImpl->m_compname;
    newstate.State     = m_CompStateStatusServiceImpl->m_compstate;
    newstate.Status = static_cast<ara::sm::ComponentStateClientReturnType>(m_CompStateStatusServiceImpl->m_status);
    m_CompStateStatusServiceImpl->updateComponentStateStatus(newstate);
}

}  // namespace democlient
}  // namespace stm
}  // namespace vrte
}  // namespace bosch
