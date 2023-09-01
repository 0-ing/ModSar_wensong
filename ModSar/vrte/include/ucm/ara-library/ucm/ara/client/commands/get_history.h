//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2020 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/ara/client/commands/get_history.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_PKGMANAGER_ARA_CLIENT_COMMANDS_GET_HISTORY_H_
#define UCM_AAP_PKGMANAGER_ARA_CLIENT_COMMANDS_GET_HISTORY_H_

#include "ucm/ara/client/command.h"

namespace bosch {
namespace vrte {
namespace ucm {
namespace ara {
namespace client {

class GetHistory final : public Command
{
public:
    explicit GetHistory(const std::string& name, StepData&& data);

    GetHistory(GetHistory     &&) = delete;
    GetHistory(GetHistory const&) = delete;

    GetHistory& operator=(GetHistory     &&) = delete;
    GetHistory& operator=(GetHistory const&) = delete;

    virtual ~GetHistory() = default;

    virtual void perform(Tuple&) const noexcept override;
};

}    // namespace client
}    // namespace ara
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_PKGMANAGER_ARA_CLIENT_COMMANDS_GET_HISTORY_H_
