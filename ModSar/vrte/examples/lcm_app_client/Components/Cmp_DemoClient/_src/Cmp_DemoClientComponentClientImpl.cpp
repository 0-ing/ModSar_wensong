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
/// @file      dummycomponentclientimpl.cpp
/// @brief
/// @copyright Robert Bosch GmbH 2019
/// @author    VRTE StM Team
//=============================================================================

#include "Cmp_DemoClientComponentClientImpl.hpp"
#include "Cmp_DemoClientCompStateRequestProxy.hpp"
#include "Cmp_DemoClientCompStateStatusService.hpp"
#include "Cmp_DemoClientLogger.hpp"

#include <cstdlib>

namespace bosch
{
namespace vrte
{
namespace stm
{
namespace democlient
{

CDemoClientComponentClientImpl::CDemoClientComponentClientImpl(std::string f_appname,
                                                     std::string f_componentname,
                                                     std::string f_instance_id)
    : m_appname(f_appname + f_instance_id + f_componentname)
    , m_instance_id(f_instance_id)
    , m_compname(f_componentname)
    , m_compstate("Off")
    , m_mode(INVALID_COMP_MODE)
    , m_componentstatestatus(COMP_STATE_STATUS_SUCCESS)
{
}

CDemoClientComponentClientImpl::~CDemoClientComponentClientImpl() {}

void CDemoClientComponentClientImpl::vInit()
{
    // Init
    DEMO_CLIENT_APP_DEBUG(m_appname, " vInit()");
    m_democlientcompstatusservice = std::make_shared<CDemoClientAppCompStateStatusService>(m_instance_id, m_compname);
    if (m_democlientcompstatusservice != nullptr)
    {
        std::shared_ptr<CDemoClientAppCompStateStatusServiceInterface> m_democlientcompstatus =
            std::dynamic_pointer_cast<CDemoClientAppCompStateStatusServiceInterface>(m_democlientcompstatusservice);
        if (m_democlientcompstatus != nullptr)
        {
            m_democlientcompstatus->vUpdateComponentClientReturn(m_componentstatestatus);
            m_democlientcompstatus->vUpdateComponentState(m_compstate);
        }
    }

    m_democlientcompstatusservice->vInitService();
    m_compstaterequestproxy = std::make_shared<CDemoClientAppCompStateRequestProxy>();
    if (m_compstaterequestproxy == nullptr)
    {
        DEMO_SERVER_APP_ERROR(m_appname, " Can not allocate the CDemoClientAppCompStateRequestProxy");
    }
}

void CDemoClientComponentClientImpl::vStart()
{
    DEMO_CLIENT_APP_DEBUG(m_appname, " vStart() ");

    m_compstaterequestproxy->vRegisterComponentStateRequestEvent(
        std::bind(&CDemoClientComponentClientImpl::vComponentStateRequestCallback, this, std::placeholders::_1,
                  std::placeholders::_2, std::placeholders::_3));
    m_democlientcompstatusservice->vStartService();
}

void CDemoClientComponentClientImpl::vStop()
{
    DEMO_CLIENT_APP_DEBUG(m_appname, " vStop()");
}

void CDemoClientComponentClientImpl::vComponentStateStatusFileWatcherCallback(std::string f_content)
{
    if (f_content.empty())
        return;
    uint8_t compretstatus = ComponentStateClientReturnTypeToUint8(f_content);
    if (m_componentstatestatus != compretstatus)
    {
        DEMO_CLIENT_APP_DEBUG(m_appname, " vComponentStateStatusFileWatcherCallback(", f_content.c_str(), ")");
        m_componentstatestatus = compretstatus;
        vComponentStateConfirm();
    }
}

void CDemoClientComponentClientImpl::vComponentStateRequestCallback(std::string f_component,
                                                               std::string f_state,
                                                               uint8_t     f_mode)
{
    DEMO_CLIENT_APP_DEBUG(m_appname, " vComponentStateRequestCallback() component: ", f_component);
    DEMO_CLIENT_APP_DEBUG(m_appname, " vComponentStateRequestCallback() state: ", f_state);
    DEMO_CLIENT_APP_DEBUG(m_appname, " vComponentStateRequestCallback() mode: ", static_cast<uint32_t>(f_mode));
    m_compname                 = f_component;
    m_compstate                = f_state;
    m_mode                     = f_mode;

    vComponentStateConfirm();
}

void CDemoClientComponentClientImpl::vComponentStateConfirm()
{
    DEMO_CLIENT_APP_DEBUG(m_appname, " vComponentStateConfirm()");
    std::shared_ptr<CDemoClientAppCompStateStatusServiceInterface> m_democlientcompstatus =
        std::dynamic_pointer_cast<CDemoClientAppCompStateStatusServiceInterface>(m_democlientcompstatusservice);
    if (m_democlientcompstatus != nullptr)
    {
        DEMO_CLIENT_APP_DEBUG(m_appname, " vComponentStateConfirm send state: ", m_compstate.c_str());
        DEMO_CLIENT_APP_DEBUG(m_appname,
                              " vComponentStateConfirm send status: ", static_cast<uint32_t>(m_componentstatestatus));
        m_democlientcompstatus->vUpdateComponentClientReturn(m_componentstatestatus);
        m_democlientcompstatus->vUpdateComponentState(m_compstate);
        m_democlientcompstatus->vComponentStateConfirm();
    }
}

}  // namespace democlient
}  // namespace stm
}  // namespace vrte
}  // namespace bosch
