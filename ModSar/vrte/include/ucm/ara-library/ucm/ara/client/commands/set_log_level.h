//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2020 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/ara/client/commands/set_log_level.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_PKGMANAGER_ARA_CLIENT_COMMANDS_SET_LOG_LEVEL_H_
#define UCM_AAP_PKGMANAGER_ARA_CLIENT_COMMANDS_SET_LOG_LEVEL_H_

#include "ucm/ara/client/command.h"

namespace bosch {
namespace vrte {
namespace ucm {
namespace ara {
namespace client {

class SetLogLevel final : public Command
{
public:
    explicit SetLogLevel(const std::string& name, StepData&& data);

    SetLogLevel(SetLogLevel     &&) = delete;
    SetLogLevel(SetLogLevel const&) = delete;

    SetLogLevel& operator=(SetLogLevel     &&) = delete;
    SetLogLevel& operator=(SetLogLevel const&) = delete;

    virtual ~SetLogLevel() = default;

    virtual void perform(Tuple&) const noexcept override;
};

}    // namespace client
}    // namespace ara
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_PKGMANAGER_ARA_CLIENT_COMMANDS_SET_LOG_LEVEL_H_
