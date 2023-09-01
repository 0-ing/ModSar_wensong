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
/// @file      democlientcomponentclientimpl.hpp
/// @brief     democlientcomponentclient implementation
/// @copyright Robert Bosch GmbH 2019
/// @author    VRTE StM Team
//=============================================================================

#ifndef DEMOCLIENTCOMPONENTCLIENTIMPL_HPP_INCLUDED
#define DEMOCLIENTCOMPONENTCLIENTIMPL_HPP_INCLUDED

#include "interface/Cmp_DemoClientAppCompStateRequestProxyInterface.hpp"
#include "interface/Cmp_DemoClientAppCompStateStatusServiceInterface.hpp"
#include "interface/Cmp_DemoClientAppServiceInterface.hpp"
#include "Cmp_DemoClientAppInterface.hpp"
#include "componentclientenum.hpp"

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

class CDemoClientComponentClientImpl : public CDemoClientAppInterface
{
public:
    CDemoClientComponentClientImpl(std::string f_appname, std::string f_componentname, std::string f_instance_id);

    // default constructors
    CDemoClientComponentClientImpl() = delete;
    virtual ~CDemoClientComponentClientImpl();
    CDemoClientComponentClientImpl(const CDemoClientComponentClientImpl& other) = delete;
    CDemoClientComponentClientImpl& operator=(const CDemoClientComponentClientImpl& other) = delete;
    CDemoClientComponentClientImpl(CDemoClientComponentClientImpl&& other)                 = delete;
    CDemoClientComponentClientImpl& operator=(CDemoClientComponentClientImpl&& other) = delete;

    void vInit();
    void vStart();
    void vStop();
    void vComponentStateConfirm();

    void vComponentStateStatusFileWatcherCallback(std::string f_content);
    void vComponentStateRequestCallback(std::string f_comp, std::string f_state, uint8_t f_mode);
private:
    std::shared_ptr<CDemoClientAppServiceInterface>               m_democlientcompstatusservice;
    std::shared_ptr<CDemoClientAppCompStateRequestProxyInterface> m_compstaterequestproxy;
    std::string                                                   m_appname;
    std::string                                                   m_instance_id;


    std::string m_compname;
    std::string m_compstate;
    uint8_t     m_mode;
    uint8_t     m_componentstatestatus;
};

}  // namespace democlient
}  // namespace stm
}  // namespace vrte
}  // namespace bosch

#endif  // 	DEMOCLIENTCOMPONENTCLIENTIMPL_HPP_INCLUDED
