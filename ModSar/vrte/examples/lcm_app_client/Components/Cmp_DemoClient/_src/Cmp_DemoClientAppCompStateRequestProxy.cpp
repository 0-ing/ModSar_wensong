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

#include "Cmp_DemoClientCompStateRequestProxy.hpp"


namespace bosch
{
namespace vrte
{
namespace stm
{
namespace democlient
{

CDemoClientAppCompStateRequestProxy::CDemoClientAppCompStateRequestProxy()
    : m_proxy_name("DummyCompStateRequestProxy")
{
    m_CompStatusRequestProxyCfg = std::make_shared<CDemoClientAppCompStateRequestProxyCfg>();
}

bool CDemoClientAppCompStateRequestProxy::vRegisterComponentStateRequestEvent(
    componentstaterequest_callback_t f_callback)
{
    bool ret = false;
    ret      = m_CompStatusRequestProxyCfg->vRegisterComponentStateRequestEvent(f_callback);
    return ret;
}

}  // namespace democlient
}  // namespace stm
}  // namespace vrte
}  // namespace bosch