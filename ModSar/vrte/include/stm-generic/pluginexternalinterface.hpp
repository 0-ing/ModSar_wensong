//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018-2022 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================
//
/// @file      libs/common/include/bosch/vrte/stm/pluginmanager/pluginexternalinterface.hpp
/// @brief     Plugin external interface for Event Handler
/// @copyright Robert Bosch GmbH 2018-2022
/// @author    VRTE StM Team
//
//=============================================================================

#ifndef BOSCH_VRTE_STM_PLUGINMANAGER_PLUGINEXTERNALINTERFACE_HPP_INCLUDED
#define BOSCH_VRTE_STM_PLUGINMANAGER_PLUGINEXTERNALINTERFACE_HPP_INCLUDED

#include "bosch/vrte/stm/pluginmanager/plugin.hpp"

namespace bosch
{
namespace vrte
{
namespace stm
{

namespace eh
{
class CIEventHandler;
}  // namespace eh

namespace ecucfg
{
class CIConfigManager;
}  // namespace ecucfg

namespace persistency
{
class CIPersistencyHandler;
}  // namespace persistency

namespace pluginmanager
{

///
/// \brief Interface for plugins containing ara::com interfaces
///
/// Plugins derived from this interface can register themselves with the Event Handler
/// to communicate with the other components
///
class CIPluginExternalInterfaceBase : public virtual CIPlugin
{
public:
    /// @brief Destructor
    virtual ~CIPluginExternalInterfaceBase() = default;

    /// @brief     Create instances of classes implementing the ara::com interfaces
    /// @param[in] f_eh : Reference to Event Handler
    /// @param[in] f_ecucfg : Reference to CIConfigManager
    /// @param[in] f_persistency : Reference to CIPersistencyHandler
    virtual void createExternalInterfaces(eh::CIEventHandler&                f_eh,
                                          ecucfg::CIConfigManager&           f_ecucfg,
                                          persistency::CIPersistencyHandler& f_persistency) = 0;

    /// @brief   Stop the ara::com communication and release the instances
    virtual void destroyExternalInterfaces() = 0;
};

}  // namespace pluginmanager
}  // namespace stm
}  // namespace vrte
}  // namespace bosch

#endif  // BOSCH_VRTE_STM_PLUGINMANAGER_PLUGINEXTERNALINTERFACE_HPP_INCLUDED
