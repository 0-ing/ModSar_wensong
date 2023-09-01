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
/// @file      stmdemoclientaracompstaterequestproxy.hpp
/// @brief
/// @copyright Robert Bosch GmbH 2019
/// @author    VRTE StM Team
//=============================================================================

#ifndef DEMOCLIENTAPPARACOMPSTATEREQUESTPROXY_HPP_INCLUDED
#define DEMOCLIENTAPPARACOMPSTATEREQUESTPROXY_HPP_INCLUDED

#include <memory>
#include <string>

#include "ara/sm/triggerout_componentstaterequest_proxy.h"
#include "Cmp_DemoClientAppCompStateRequestProxyCfg.hpp"

#define COMPONENTSTATEREQUEST_DUMMY_INSTANCE_ID "1"

namespace bosch
{
namespace vrte
{
namespace stm
{
namespace democlient
{

class CDemoClientAppCompStateRequestProxyCfg::CDemoClientAppCompStateRequestProxyImpl
{
public:
    CDemoClientAppCompStateRequestProxyImpl();
    void                        ComponentStateRequestHandler();
    void                        Subscribe();
    ara::com::SubscriptionState GetSubscriptionState();
    void                        SetReceiveHandler();

    std::string                                                            m_proxy_name;
    std::string                                                            m_instance_id;
    std::shared_ptr<ara::sm::proxy::TriggerOut_ComponentStateRequestProxy> m_proxy;
    componentstaterequest_callback_t                                       m_componentstaterequest_callback;
};

}  // namespace democlient
}  // namespace stm
}  // namespace vrte
}  // namespace bosch

#endif  // DEMOCLIENTAPPARACOMPSTATEREQUESTPROXY_HPP_INCLUDED
