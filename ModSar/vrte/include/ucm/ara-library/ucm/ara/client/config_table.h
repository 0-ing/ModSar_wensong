//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2020 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/ara/client/config_ConfigTable.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_PKGMANAGER_ARA_CLIENT_CONFIG_ConfigTable_H_
#define UCM_AAP_PKGMANAGER_ARA_CLIENT_CONFIG_ConfigTable_H_

#include <string>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/dev/image.h"
#include "ucm/lib/dev/device.h"
#include "ucm/lib/dev/memslot.h"
#include "ucm/lib/ara/ara_types.h"
#include "ucm/ara/client/sequence.h"

namespace bosch {
namespace vrte {
namespace ucm {
namespace ara {
namespace client {

struct ConfigTable final
{
    explicit ConfigTable(int argc, char** argv, Sequence&);

    ConfigTable(ConfigTable     &&) = delete;
    ConfigTable(ConfigTable const&) = delete;

    ConfigTable& operator=(ConfigTable     &&) = delete;
    ConfigTable& operator=(ConfigTable const&) = delete;

    ~ConfigTable() = default;

private:
    Sequence& sequence_;
    std::string cfgfile_;


    void getopt(int argc, char** argv);

    bool getopt_bool(int argc, char** argv,
                     char key, bool defvalue) noexcept;

    std::string getopt_string(int argc, char** argv,
                              const char* key, const char* defvalue) noexcept;
};

}    // namespace client
}    // namespace ara
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_PKGMANAGER_ARA_CLIENT_CONFIG_ConfigTable_H_
