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
/// @file      stmdemoclientcompstaterequestproxy.cpp
/// @brief
/// @copyright Robert Bosch GmbH 2019
/// @author    VRTE StM Team
//=============================================================================

#include "Cmp_DemoClientAppAraCompStateRequestProxy.hpp"
#include "Cmp_DemoClientLogger.hpp"

#define CONFIG CDemoClientAppCompStateRequestProxyCfg

namespace bosch
{
namespace vrte
{
namespace stm
{
namespace democlient
{

// CDemoClientAppCompStateRequestProxyImpl Implementation
CONFIG::CDemoClientAppCompStateRequestProxyImpl::CDemoClientAppCompStateRequestProxyImpl()
    : m_proxy_name("CompStateRequestProxy")
    , m_instance_id(std::string(COMPONENTSTATEREQUEST_DUMMY_INSTANCE_ID))
    , m_componentstaterequest_callback(nullptr)
{
    DEMO_CLIENT_APP_DEBUG(m_proxy_name, " CDemoClientAppCompStateRequestProxyImpl() ");

    ara::com::InstanceIdentifier insIden(COMPONENTSTATEREQUEST_DUMMY_INSTANCE_ID);
    auto serviceHandlesResult = ara::sm::proxy::TriggerOut_ComponentStateRequestProxy::FindService(insIden);
    if (serviceHandlesResult.HasValue())
    {
        auto serviceHandles = serviceHandlesResult.Value();
        if (0 != serviceHandles.size())
        {
            m_proxy = std::make_shared<ara::sm::proxy::TriggerOut_ComponentStateRequestProxy>(
                serviceHandles[0U]);
        }
    }
}

void CONFIG::CDemoClientAppCompStateRequestProxyImpl::ComponentStateRequestHandler()
{
    ara::sm::ComponentStateRequestType receivedComponentStateRequests;
    auto samples = m_proxy->ComponenStateRequest.GetNewSamples(
        [&receivedComponentStateRequests](ara::com::SamplePtr<ara::sm::ComponentStateRequestType const> sample) {
            receivedComponentStateRequests = *sample;
        });
    if (true == samples.HasValue())
    {
        if (nullptr != m_componentstaterequest_callback)
        {
            std::string comp  = receivedComponentStateRequests.Component.c_str();
            std::string state = receivedComponentStateRequests.State.c_str();
            DEMO_CLIENT_APP_DEBUG(m_proxy_name, " ComonentStateRequestHandler recive comp ", comp);
            DEMO_CLIENT_APP_DEBUG(m_proxy_name, " ComponentStateRequestHandler recive state ", state);
            uint8_t mode = static_cast<uint8_t>(receivedComponentStateRequests.Mode);
            m_componentstaterequest_callback(comp, state, mode);
        }
        else
        {
            DEMO_SERVER_APP_ERROR(m_proxy_name, " ComponentStateRequest callback is not valid");
        }
    }
    else
    {
        DEMO_SERVER_APP_INFO(m_proxy_name, "No ComponentStateRequest sample received.");
    }
}

void CONFIG::CDemoClientAppCompStateRequestProxyImpl::Subscribe()
{
    m_proxy->ComponenStateRequest.Subscribe(1);
}

ara::com::SubscriptionState CONFIG::CDemoClientAppCompStateRequestProxyImpl::GetSubscriptionState()
{
    return m_proxy->ComponenStateRequest.GetSubscriptionState();
}

void CONFIG::CDemoClientAppCompStateRequestProxyImpl::SetReceiveHandler()
{
    m_proxy->ComponenStateRequest.SetReceiveHandler(
        std::bind(&CDemoClientAppCompStateRequestProxyImpl::ComponentStateRequestHandler, this));
}

// CDemoClientAppCompStateRequestProxyCfg Implementation
CDemoClientAppCompStateRequestProxyCfg::CDemoClientAppCompStateRequestProxyCfg()
{
    m_CompStatusRequestProxyImpl = std::make_shared<CDemoClientAppCompStateRequestProxyImpl>();
}

bool CDemoClientAppCompStateRequestProxyCfg::vRegisterComponentStateRequestEvent(
    componentstaterequest_callback_t f_callback)
{
    bool is_proxy_subscribable = false;

    DEMO_CLIENT_APP_DEBUG(m_CompStatusRequestProxyImpl->m_proxy_name, " vRegisterComponentStateRequestEvent subscribe");
    if (nullptr != f_callback)
    {
        m_CompStatusRequestProxyImpl->m_componentstaterequest_callback = f_callback;
    }
    m_CompStatusRequestProxyImpl->Subscribe();
    while (true != is_proxy_subscribable)
    {
        if (ara::com::SubscriptionState::kSubscribed == m_CompStatusRequestProxyImpl->GetSubscriptionState())
        {
            is_proxy_subscribable = true;
            DEMO_CLIENT_APP_DEBUG(m_CompStatusRequestProxyImpl->m_proxy_name, " subscribed to CompStateRequest");
            m_CompStatusRequestProxyImpl->SetReceiveHandler();
            return true;
        }
        else
        {
            DEMO_CLIENT_APP_DEBUG(m_CompStatusRequestProxyImpl->m_proxy_name, " finding service");
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    }
    return false;
}

}  // namespace democlient
}  // namespace stm
}  // namespace vrte
}  // namespace bosch
