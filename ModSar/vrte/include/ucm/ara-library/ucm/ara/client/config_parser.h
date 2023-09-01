//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2020 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/ara/client/config_parser.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_PKGMANAGER_ARA_CLIENT_CONFIG_PARSER_H_
#define UCM_AAP_PKGMANAGER_ARA_CLIENT_CONFIG_PARSER_H_

#include "ucm/lib/log/logger.h"
#include "ucm/ara/client/sequence.h"

namespace bosch {
namespace vrte {
namespace ucm {
namespace ara {
namespace client {

class ConfigParser
{
public:
    virtual ~ConfigParser() = default;

    virtual bool parse(const std::string& file) = 0;

protected:
    Sequence& sequence_;
    ucm::lib::log::Logger logger_{};

    ConfigParser(Sequence& sequence)
        : sequence_{sequence} {}

    ConfigParser(ConfigParser     &&) = default;
    ConfigParser(ConfigParser const&) = delete;

    ConfigParser& operator=(ConfigParser     &&) = delete;
    ConfigParser& operator=(ConfigParser const&) = delete;
};

}    // namespace client
}    // namespace ara
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_PKGMANAGER_ARA_CLIENT_CONFIG_PARSER_H_
