//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2020 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/ara/client/commands/transfer_exit.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_PKGMANAGER_ARA_CLIENT_COMMANDS_TRANSFER_EXIT_H_
#define UCM_AAP_PKGMANAGER_ARA_CLIENT_COMMANDS_TRANSFER_EXIT_H_

#include "ucm/ara/client/command.h"

namespace bosch {
namespace vrte {
namespace ucm {
namespace ara {
namespace client {

class TransferExit final : public Command
{
public:
    explicit TransferExit(Tuple& tuple,
                          const std::string& name, StepData&& data);

    TransferExit(TransferExit     &&) = delete;
    TransferExit(TransferExit const&) = delete;

    TransferExit& operator=(TransferExit     &&) = delete;
    TransferExit& operator=(TransferExit const&) = delete;

    virtual ~TransferExit() = default;

protected:
    virtual void impl_perform(StepData&) override;

private:
    StepData::transferid_type transfer_id(StepData&);
};

}    // namespace client
}    // namespace ara
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_PKGMANAGER_ARA_CLIENT_COMMANDS_TRANSFER_EXIT_H_
