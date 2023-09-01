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
/// @file      stmdemoclientasfcompstatestatusservicecfg.hpp
/// @brief     StM Dummy component state status serivce
/// @copyright Robert Bosch GmbH 2019
/// @author    VRTE StM Team
//=============================================================================

#ifndef DEMOCLIENTAPPASFCOMPSTATESTATUSSERVICECFG_HPP_INCLUDED
#define DEMOCLIENTAPPASFCOMPSTATESTATUSSERVICECFG_HPP_INCLUDED

#include "interface/Cmp_DemoClientAppCompStateStatusServiceCfgInterface.hpp"
#include <cstdint>
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

class CDemoClientAppCompStateStatusServiceCfg : public CDemoClientAppCompStateStatusServiceCfgInterface
{
public:
    CDemoClientAppCompStateStatusServiceCfg(std::string f_instanceid, std::string f_compname);
    virtual void vInitService();
    virtual void vStartService();
    virtual void vStopService();
    virtual void vUpdateComponentState(std::string f_state);
    virtual void vUpdateComponentClientReturn(uint8_t f_ret);
    virtual void vComponentStateConfirm();

private:
    class CDemoClientAppCompStateStatusServiceImpl;
    std::shared_ptr<CDemoClientAppCompStateStatusServiceImpl> m_CompStateStatusServiceImpl;
};

}  // namespace democlient
}  // namespace stm
}  // namespace vrte
}  // namespace bosch

#endif  // DEMOCLIENTAPPASFCOMPSTATESTATUSSERVICECFG_HPP_INCLUDED
