//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2020 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/vrte/cfg/parser.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Vesselin Mladenov
/// @version
/// @remarks
/// @ingroup      bosch_vrte_ucm_vrte_cfg

#ifndef UCM_AAP_PROCESSING_VRTE_UCM_VRTE_CFG_CONFIG_POCO_H_
#define UCM_AAP_PROCESSING_VRTE_UCM_VRTE_CFG_CONFIG_POCO_H_

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/cfg/table.h"
#include "ucm/lib/cfg/parser.h"
#include "ucm/vrte/cfg/table.h"

/// @addtogroup bosch_vrte_ucm_vrte_cfg
/// @{

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace vrte  {
namespace cfg   {

/// @brief Configuration handler for IPC mechanism.
///

struct ConfigPoco : public lib::cfg::Parser
{
    ConfigPoco() noexcept = default;

    ConfigPoco(Table*) noexcept;

    ConfigPoco(ConfigPoco&&) = delete;
    ConfigPoco& operator=(ConfigPoco&&) = delete;

    ConfigPoco(const ConfigPoco&) = delete;
    ConfigPoco& operator=(const ConfigPoco&) = delete;

    virtual ~ConfigPoco() = default;
    
    /// @brief Parsing configuration [processing_sw] section of UCM configuration.
    /// @param [IN] JSON object with UCM configuration of type Poco::JSON::Object::Ptr
    /// @return Parse status always returns TRUE
    virtual bool parse(lib::cfg::Table&, Poco::JSON::Object::Ptr) override;

private:
    Table* module_config_{nullptr};

    void parse_section(Poco::JSON::Object::Ptr);

    void dlt_loglevel(Poco::JSON::Object::Ptr);
    void fc_exm_enable(Poco::JSON::Object::Ptr);
    void fc_sec_enable(Poco::JSON::Object::Ptr);
    void fc_stm_enable(Poco::JSON::Object::Ptr);
    void fc_exm_ipc_enable(Poco::JSON::Object::Ptr);
    void fc_sec_ipc_enable(Poco::JSON::Object::Ptr);
    void fc_stm_ipc_enable(Poco::JSON::Object::Ptr);
};

}    // namespace cfg
}    // namespace vrte
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif // UCM_AAP_PROCESSING_VRTE_UCM_VRTE_CFG_CONFIG_POCO_H_
