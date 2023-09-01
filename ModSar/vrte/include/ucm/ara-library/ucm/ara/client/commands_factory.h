//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2020 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/ara/client/CommandFactory_factory.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_PKGMANAGER_ARA_CLIENT_COMMANDS_FACTORY_H_
#define UCM_AAP_PKGMANAGER_ARA_CLIENT_COMMANDS_FACTORY_H_

#include <pthread.h>

#include <map>
#include <mutex>
#include <memory>

#include "ucm/ara/client/command.h"

namespace bosch {
namespace vrte {
namespace ucm {
namespace ara {
namespace client {

class CommandsFactory final
{
public:
    explicit CommandsFactory() = default;

    CommandsFactory(CommandsFactory     &&) = default;
    CommandsFactory(CommandsFactory const&) = default;

    CommandsFactory& operator=(CommandsFactory     &&) = default;
    CommandsFactory& operator=(CommandsFactory const&) = default;

    ~CommandsFactory() = default;

    static std::unique_ptr<Command>
    make(Tuple& tuple, const std::string& name, StepData&&);
};

}    // namespace client
}    // namespace ara
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_PKGMANAGER_ARA_CLIENT_COMMANDS_FACTORY_H_
