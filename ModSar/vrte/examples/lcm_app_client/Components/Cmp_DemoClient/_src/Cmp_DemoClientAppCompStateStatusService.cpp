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
/// @file      stmdemoclientcompstatestatusservice.cpp
/// @brief
/// @copyright Robert Bosch GmbH 2019
/// @author    VRTE StM Team
//=============================================================================

#include "Cmp_DemoClientCompStateStatusService.hpp"
#include "componentclientenum.hpp"
#include "Cmp_DemoClientLogger.hpp"
namespace bosch
{
namespace vrte
{
namespace stm
{
namespace democlient
{

CDemoClientAppCompStateStatusService::CDemoClientAppCompStateStatusService(std::string f_instance_id,
                                                                           std::string f_compname)
    : m_service_name(f_compname + f_instance_id)
    , m_comp(f_compname)
    , m_compstate()
    , m_status(INVALID_COMP_STATE_STATUS)
{
    DEMO_CLIENT_APP_DEBUG(m_service_name, " with instance id ", f_instance_id);
    m_CompStateStatusServiceCfg =
        std::make_shared<CDemoClientAppCompStateStatusServiceCfg>(f_instance_id, f_compname);
}

void CDemoClientAppCompStateStatusService::vInitService()
{
    m_CompStateStatusServiceCfg->vInitService();
}

void CDemoClientAppCompStateStatusService::vStartService()
{
    m_CompStateStatusServiceCfg->vStartService();
}

void CDemoClientAppCompStateStatusService::vStopService()
{
    m_CompStateStatusServiceCfg->vStopService();
}

void CDemoClientAppCompStateStatusService::vUpdateComponentClientReturn(uint8_t f_ret)
{
    if (f_ret != m_status)
    {
        m_status = f_ret;
        m_CompStateStatusServiceCfg->vUpdateComponentClientReturn(m_status);
    }
}

void CDemoClientAppCompStateStatusService::vUpdateComponentState(std::string f_state)
{
    if (f_state != m_compstate)
    {
        m_compstate = f_state;
        m_CompStateStatusServiceCfg->vUpdateComponentState(f_state);
    }
}

void CDemoClientAppCompStateStatusService::vComponentStateConfirm()
{
    m_CompStateStatusServiceCfg->vComponentStateConfirm();
}

}  // namespace democlient
}  // namespace stm
}  // namespace vrte
}  // namespace bosch