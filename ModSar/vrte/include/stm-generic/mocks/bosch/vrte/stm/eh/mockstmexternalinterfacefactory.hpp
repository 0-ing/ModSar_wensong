//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018-2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================
//
/// @file      tests/VRTE_UT/mocks/include/bosch/vrte/stm/eh/mockstmexternalinterfacefactory.hpp
/// @brief     Factory Class Mock for external interfaces in STM (EH)
/// @copyright Robert Bosch GmbH 2018-2021
/// @author    VRTE StM Team
//
//=============================================================================

#ifndef BOSCH_VRTE_STM_EH_MOCKSTMEXTERNALINTERFACEFACTORY_HPP_INCLUDED
#define BOSCH_VRTE_STM_EH_MOCKSTMEXTERNALINTERFACEFACTORY_HPP_INCLUDED

#include "gmock/gmock.h"
#include <new>

#include "bosch/vrte/stm/eh/ieventhandler.hpp"
#include "bosch/vrte/stm/eh/iexternalinterface.hpp"

#include "bosch/vrte/stm/eh/mockeventhandlerclient.hpp"

namespace bosch
{
namespace vrte
{
namespace stm
{

namespace eh
{
class CIExternalInterface;
}

namespace testing
{

class CMockStmExternalInterfaceFactory
{

public:
    CMockStmExternalInterfaceFactory(eh::CIEventHandler* f_eh_p);
    virtual ~CMockStmExternalInterfaceFactory();

    // Create a client based on the request from EH
    eh::CIExternalInterface* getClient(const std::string& f_strName) const;

    // Delete EH clients in destructor
    void vDeleteClients();

private:
    eh::CIEventHandler*      m_eventhandler_p;
    CMockEventHandlerClient* m_ehClient1_p;
    CMockEventHandlerClient* m_ehClient2_p;
};

CMockStmExternalInterfaceFactory::CMockStmExternalInterfaceFactory(eh::CIEventHandler* f_eh_p)
    : m_eventhandler_p(f_eh_p)
    , m_ehClient1_p(nullptr)
    , m_ehClient2_p(nullptr)
{
    m_ehClient1_p = new (std::nothrow) CMockEventHandlerClient();
    m_ehClient2_p = new (std::nothrow) CMockEventHandlerClient();
}

CMockStmExternalInterfaceFactory::~CMockStmExternalInterfaceFactory() {}

eh::CIExternalInterface* CMockStmExternalInterfaceFactory::getClient(const std::string& f_strName) const
{
    CMockEventHandlerClient* ehClient = nullptr;

    if ("ehExternalClient1" == f_strName)
    {
        if (nullptr != m_ehClient1_p)
        {
            ehClient = m_ehClient1_p;
        }
    }
    else if ("ehExternalClient2" == f_strName)
    {
        if (nullptr != m_ehClient2_p)
        {
            ehClient = m_ehClient2_p;
        }
    }
    else
    {
        // Do nothing
    }

    return ehClient;
}

void CMockStmExternalInterfaceFactory::vDeleteClients()
{
    if (nullptr != m_ehClient1_p)
    {
        delete m_ehClient1_p;
        m_ehClient1_p = nullptr;
    }

    if (nullptr != m_ehClient2_p)
    {
        delete m_ehClient2_p;
        m_ehClient2_p = nullptr;
    }
}

}  // namespace testing
}  // namespace stm
}  // namespace vrte
}  // namespace bosch

#endif  // BOSCH_VRTE_STM_EH_MOCKSTMEXTERNALINTERFACEFACTORY_HPP_INCLUDED
