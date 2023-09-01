//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2020 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/ara/client/commands/get_sw_process_progress.h
/// @brief
/// @copyright    Robert Bosch GmbH 2022
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_PKGMANAGER_ARA_CLIENT_COMMANDS_GET_SW_PROCESS_PROGRESS_H_
#define UCM_AAP_PKGMANAGER_ARA_CLIENT_COMMANDS_GET_SW_PROCESS_PROGRESS_H_

#include "ucm/ara/client/command.h"

namespace bosch  {
namespace vrte   {
namespace ucm    {
namespace ara    {
namespace client {

class GetSwProcessProgress final : public Command
{
public:
    explicit GetSwProcessProgress(Tuple& tuple,
                      const std::string& name, StepData&& data);

    GetSwProcessProgress(GetSwProcessProgress     &&) = delete;
    GetSwProcessProgress(GetSwProcessProgress const&) = delete;

    GetSwProcessProgress& operator=(GetSwProcessProgress     &&) = delete;
    GetSwProcessProgress& operator=(GetSwProcessProgress const&) = delete;

    virtual ~GetSwProcessProgress() = default;

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

#endif // UCM_AAP_PKGMANAGER_ARA_CLIENT_COMMANDS_GET_SW_PROCESS_PROGRESS_H_
