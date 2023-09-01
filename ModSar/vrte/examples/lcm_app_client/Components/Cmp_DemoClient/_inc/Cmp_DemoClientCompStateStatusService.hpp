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
/// @file      stmdemoclientcompstatusservice.hpp
/// @brief     StM Dummy component state status serivce
/// @copyright Robert Bosch GmbH 2019
/// @author    VRTE StM Team
//=============================================================================

#ifndef DEMOCLIENTAPPCOMPSTATESTATUSSERVICE_HPP_INCLUDED
#define DEMOCLIENTAPPCOMPSTATESTATUSSERVICE_HPP_INCLUDED

#include "Cmp_DemoClientAppCompStateStatusServiceCfg.hpp"
#include "interface/Cmp_DemoClientAppCompStateStatusServiceCfgInterface.hpp"
#include "interface/Cmp_DemoClientAppCompStateStatusServiceInterface.hpp"
#include "interface/Cmp_DemoClientAppServiceInterface.hpp"
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

class CDemoClientAppCompStateStatusService : public CDemoClientAppCompStateStatusServiceInterface,
                                             public CDemoClientAppServiceInterface
{
public:
    CDemoClientAppCompStateStatusService(std::string f_instanceid, std::string f_compname);
    CDemoClientAppCompStateStatusService()          = delete;
    virtual ~CDemoClientAppCompStateStatusService() = default;
    virtual void vInitService();
    virtual void vStartService();
    virtual void vStopService();
    virtual void vUpdateEventStatus(uint8_t f_status)
    {
        (void)f_status;
    };
    virtual void vUpdateComponentState(std::string f_state);
    virtual void vUpdateComponentClientReturn(uint8_t f_ret);
    virtual void vTriggerEvent(){};
    virtual void vComponentStateConfirm();

private:
    std::shared_ptr<CDemoClientAppCompStateStatusServiceCfg> m_CompStateStatusServiceCfg;
    std::string                                              m_service_name;
    std::string                                              m_comp;
    std::string                                              m_compstate;
    uint8_t                                                  m_status;
};

}  // namespace democlient
}  // namespace stm
}  // namespace vrte
}  // namespace bosch

#endif  // DEMOCLIENTAPPCOMPSTATESTATUSSERVICE_HPP_INCLUDED
