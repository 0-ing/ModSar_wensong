//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2020 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/ara/client/commands/get_log.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_PKGMANAGER_ARA_CLIENT_COMMANDS_GET_LOG_H_
#define UCM_AAP_PKGMANAGER_ARA_CLIENT_COMMANDS_GET_LOG_H_

#include "ucm/ara/client/command.h"

namespace bosch {
namespace vrte {
namespace ucm {
namespace ara {
namespace client {

class GetLog final : public Command
{
public:
    explicit GetLog(const std::string& name, StepData&& data);

    GetLog(GetLog     &&) = delete;
    GetLog(GetLog const&) = delete;

    GetLog& operator=(GetLog     &&) = delete;
    GetLog& operator=(GetLog const&) = delete;

    virtual ~GetLog() = default;

    virtual void perform(Tuple&) const noexcept override;
};

}    // namespace client
}    // namespace ara
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_PKGMANAGER_ARA_CLIENT_COMMANDS_GET_LOG_H_
