//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2020 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/ara/client/config_poco.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_PKGMANAGER_ARA_CLIENT_CONFIG_POCO_H_
#define UCM_AAP_PKGMANAGER_ARA_CLIENT_CONFIG_POCO_H_

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
#pragma GCC diagnostic ignored "-Woverloaded-virtual"
#include <Poco/JSON/Array.h>
#include <Poco/JSON/Object.h>
#pragma GCC diagnostic pop

#include "ucm/ara/client/step_data.h"
#include "ucm/ara/client/config_parser.h"

namespace bosch {
namespace vrte {
namespace ucm {
namespace ara {
namespace client {

struct ConfigPoco : public ConfigParser
{
    explicit ConfigPoco(Sequence& sequence)
        : ConfigParser(sequence) {}

    ConfigPoco(ConfigPoco     &&) = delete;
    ConfigPoco(ConfigPoco const&) = delete;

    ConfigPoco& operator=(ConfigPoco     &&) = delete;
    ConfigPoco& operator=(ConfigPoco const&) = delete;

    virtual ~ConfigPoco() = default;

    virtual bool parse(const std::string& file) override;

protected:
    void parse_common(Poco::JSON::Object::Ptr);
    void parse_common_files(Poco::JSON::Array::Ptr);
    void parse_common_mutexes(Poco::JSON::Array::Ptr);
    void parse_common_barriers(Poco::JSON::Array::Ptr);

    void parse_threads(Poco::JSON::Array::Ptr);
    void parse_thread_commands(std::unique_ptr<Thread>&,
                               Poco::JSON::Array::Ptr);
    StepData parse_thread_command_data(Poco::JSON::Object::Ptr);
};

}    // namespace client
}    // namespace ara
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_PKGMANAGER_ARA_CLIENT_CONFIG_POCO_H_
