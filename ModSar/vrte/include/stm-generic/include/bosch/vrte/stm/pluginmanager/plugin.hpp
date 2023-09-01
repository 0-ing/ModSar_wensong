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
/// @file      libs/common/include/bosch/vrte/stm/pluginmanager/plugin.hpp
/// @brief     Base implementation class of IPlugin
/// @copyright Robert Bosch GmbH 2018-2022
/// @author    VRTE StM Team
//
//=============================================================================

#ifndef BOSCH_VRTE_STM_PLUGINMANAGER_PLUGIN_HPP_INCLUDED
#define BOSCH_VRTE_STM_PLUGINMANAGER_PLUGIN_HPP_INCLUDED

#include "bosch/vrte/stm/pluginmanager/iplugin.hpp"

namespace bosch
{
namespace vrte
{
namespace stm
{
namespace pluginmanager
{

/// @brief Base class for all plugins.
class CPlugin : public virtual CIPlugin
{
public:
    /// @brief Constructor
    explicit CPlugin(uint32_t f_version, const std::string& f_name, EPluginType f_type, EServerPlugin f_server);

    /// @brief Destructor
    virtual ~CPlugin() = default;

    /// See documentation at IPlugin
    uint32_t           getVersion() const override;
    const std::string& getName() const override;
    EPluginType        getType() const override;
    EServerPlugin      getServer() const override;

protected:
    uint32_t          m_version;
    const std::string m_name;
    EPluginType       m_type;
    EServerPlugin     m_server;
};

}  // namespace pluginmanager
}  // namespace stm
}  // namespace vrte
}  // namespace bosch

#endif  // BOSCH_VRTE_STM_PLUGINMANAGER_PLUGIN_HPP_INCLUDED
