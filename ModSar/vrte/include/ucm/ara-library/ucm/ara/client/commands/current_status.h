//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/ara/client/commands/current_status.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       dsh8cob
/// @version
/// @remarks

#ifndef UCM_AAP_PKGMANAGER_ARA_CLIENT_COMMANDS_CURRENT_STATUS_H_
#define UCM_AAP_PKGMANAGER_ARA_CLIENT_COMMANDS_CURRENT_STATUS_H_

#include "ucm/ara/client/command.h"

namespace bosch {
namespace vrte {
namespace ucm {
namespace ara {
namespace client {

class CurrentStatus final : public Command
{
public:
    explicit CurrentStatus(Tuple& tuple, const std::string& name,
                           StepData&& data);

    CurrentStatus(CurrentStatus &&) = delete;
    CurrentStatus(CurrentStatus const&) = delete;

    CurrentStatus& operator=(CurrentStatus &&) = delete;
    CurrentStatus& operator=(CurrentStatus const&) = delete;

    virtual ~CurrentStatus() = default;

protected:
    virtual void impl_perform(StepData&) override;
};

}    // namespace client
}    // namespace ara
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_PKGMANAGER_ARA_CLIENT_COMMANDS_CURRENT_STATUS_H_
