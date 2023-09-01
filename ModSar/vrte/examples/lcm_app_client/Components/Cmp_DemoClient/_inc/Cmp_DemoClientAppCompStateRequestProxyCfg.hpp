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
/// @file      stmdemoclientcompstaterequestproxycfg.hpp
/// @brief
/// @copyright Robert Bosch GmbH 2019
/// @author    VRTE StM Team
//=============================================================================

#ifndef DEMOCLIENTAPPASFCOMPSTATEREQUESTPROXYCFG_HPP_INCLUDED
#define DEMOCLIENTAPPASFCOMPSTATEREQUESTPROXYCFG_HPP_INCLUDED

#include "interface/Cmp_DemoClientAppCompStateRequestProxyCfgInterface.hpp"
#include <condition_variable>
#include <memory>
#include <mutex>

namespace bosch
{
namespace vrte
{
namespace stm
{
namespace democlient
{

class CDemoClientAppCompStateRequestProxyCfg : public CDemoClientAppCompStateRequestProxyCfgInterface
{
public:
    CDemoClientAppCompStateRequestProxyCfg();
    virtual bool vRegisterComponentStateRequestEvent(componentstaterequest_callback_t f_callback);

private:
    class CDemoClientAppCompStateRequestProxyImpl;
    std::shared_ptr<CDemoClientAppCompStateRequestProxyImpl> m_CompStatusRequestProxyImpl;
};

}  // namespace democlient
}  // namespace stm
}  // namespace vrte
}  // namespace bosch

#endif  // DEMOCLIENTAPPASFCOMPSTATEREQUESTPROXYCFG_HPP_INCLUDED
