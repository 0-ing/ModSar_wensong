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
/// @file      libs/eh/include/bosch/vrte/stm/eh/iexternalinterfacefactory.hpp
/// @brief     Interface to create stm external interfaces factory
/// @copyright Robert Bosch GmbH 2018-2021
/// @author    VRTE StM Team
//
//=============================================================================

#ifndef BOSCH_VRTE_STM_EH_IEXTERNALINTERFACEFACTORY_HPP_INCLUDED
#define BOSCH_VRTE_STM_EH_IEXTERNALINTERFACEFACTORY_HPP_INCLUDED

namespace bosch
{
namespace vrte
{
namespace stm
{
namespace eh
{

/// @brief This abstract class provides interfaces to interact with Factory.
class CIExternalInterfacesFactory
{
public:
    ///@brief  Destructor
    virtual ~CIExternalInterfacesFactory() = default;

    ///@brief: Create objects of the factory components
    virtual void create() = 0;

    ///@brief: Start the event loop processing
    virtual void start() = 0;
};  // class CIExternalInterfacesFactory

}  // namespace eh
}  // namespace stm
}  // namespace vrte
}  // namespace bosch

#endif  // BOSCH_VRTE_STM_EH_IEXTERNALINTERFACEFACTORY_HPP_INCLUDED
