//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2020 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/app/cfg/config_poco.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Vesselin Mladenov
/// @version
/// @remarks
/// @ingroup      bosch_vrte_ucm_app_cfg

#ifndef UCM_AAP_LIBRARY_APP_CFG_CONFIG_POCO_H_
#define UCM_AAP_LIBRARY_APP_CFG_CONFIG_POCO_H_

#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wsign-promo"
#pragma GCC diagnostic ignored "-Wconversion"
#pragma GCC diagnostic ignored "-Wfloat-equal"
#pragma GCC diagnostic ignored "-Wsign-compare"
#pragma GCC diagnostic ignored "-Wold-style-cast"
#pragma GCC diagnostic ignored "-Wstrict-overflow"
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wfloat-conversion"
#pragma GCC diagnostic ignored "-Woverloaded-virtual"
#include <Poco/JSON/Array.h>
#include <Poco/JSON/Object.h>
#pragma GCC diagnostic pop


#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/cfg/table.h"
#include "ucm/lib/cfg/parser.h"

/// @addtogroup bosch_vrte_ucm_app_cfg
/// @{

namespace bosch {
namespace vrte {
namespace ucm {
namespace app {
namespace cfg {
    
/// @struct Array array.h ucm/app/cfg/config_poco.h
/// @ingroup bosch_vrte_ucm_app_cfg
/// @brief Configuration parser.
///


struct ConfigPoco final : public lib::cfg::Parser
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_ucm_app_cfg_config_poco, parse_pipeline);
    FRIEND_TEST(Test_ucm_app_cfg_config_poco, parse_monitor);
    FRIEND_TEST(Test_ucm_app_cfg_config_poco, parse_memslot_type);
    FRIEND_TEST(Test_ucm_app_cfg_config_poco, parse_device_memslots);
    FRIEND_TEST(Test_ucm_app_cfg_config_poco, parse_memslots);
    FRIEND_TEST(Test_ucm_app_cfg_config_poco, parse_devices);
    FRIEND_TEST(Test_ucm_app_cfg_config_poco, parse_images);
    FRIEND_TEST(Test_ucm_app_cfg_config_poco, parse_exception);
    FRIEND_TEST(Test_ucm_app_cfg_config_poco, parse_success);
#endif

    ConfigPoco() = default;

    ConfigPoco(ConfigPoco&&) = delete;
    ConfigPoco& operator=(ConfigPoco&&) = delete;

    ConfigPoco(const ConfigPoco&) = delete;
    ConfigPoco& operator=(const ConfigPoco&) = delete;

    virtual ~ConfigPoco() = default;

    bool parse(lib::cfg::Table&, Poco::JSON::Object::Ptr) override;

private:
    void parse_monitor(lib::cfg::Table*, Poco::JSON::Object::Ptr);
    void parse_pipeline(lib::cfg::Table*, Poco::JSON::Object::Ptr);

    void parse_images(lib::cfg::Table*, Poco::JSON::Array::Ptr);
    void parse_devices(lib::cfg::Table*, Poco::JSON::Array::Ptr);
    void parse_memslots(lib::cfg::Table*, const lib::dev::Device::Specs&,
                        Poco::JSON::Object::Ptr);
    std::vector<lib::dev::MemSlot::Specs>
    parse_device_memslots(Poco::JSON::Array::Ptr);

    lib::dev::MemSlot::Type parse_memslot_type(Poco::JSON::Object::Ptr);

};

}    // namespace cfg
}    // namespace app
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif // UCM_AAP_LIBRARY_APP_CFG_CONFIG_POCO_H_
