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
/// @file      Cmp_DemoClientCompStateRequestProxy.hpp
/// @brief
/// @copyright Robert Bosch GmbH 2019
/// @author    VRTE StM Team
//=============================================================================

#ifndef DEMOCLIENTAPPCOMPSTATEREQUESTPROXY_HPP_INCLUDED
#define DEMOCLIENTAPPCOMPSTATEREQUESTPROXY_HPP_INCLUDED

#include "Cmp_DemoClientAppCompStateRequestProxyCfg.hpp"
#include "interface/Cmp_DemoClientAppCompStateRequestProxyCfgInterface.hpp"
#include "interface/Cmp_DemoClientAppCompStateRequestProxyInterface.hpp"
#include <memory>
#include <string>

namespace bosch
{
namespace vrte
{
namespace stm
{
namespace democlient
{

class CDemoClientAppCompStateRequestProxy : public CDemoClientAppCompStateRequestProxyInterface
{
public:
    CDemoClientAppCompStateRequestProxy();
    virtual ~CDemoClientAppCompStateRequestProxy()                                        = default;
    CDemoClientAppCompStateRequestProxy(const CDemoClientAppCompStateRequestProxy& other) = delete;
    CDemoClientAppCompStateRequestProxy& operator=(const CDemoClientAppCompStateRequestProxy& other) = delete;
    CDemoClientAppCompStateRequestProxy(CDemoClientAppCompStateRequestProxy&& other)                 = delete;
    CDemoClientAppCompStateRequestProxy& operator=(CDemoClientAppCompStateRequestProxy&& other) = delete;

    virtual bool vRegisterComponentStateRequestEvent(componentstaterequest_callback_t f_callback);

private:
    std::shared_ptr<CDemoClientAppCompStateRequestProxyCfg> m_CompStatusRequestProxyCfg;
    std::string                                             m_proxy_name;
};

}  // namespace democlient
}  // namespace stm
}  // namespace vrte
}  // namespace bosch

#endif  // DEMOCLIENTAPPCOMPSTATEREQUESTPROXY_HPP_INCLUDED
