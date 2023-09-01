//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2020 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/ara/client/commands/wf_barrier_Wait.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_PKGMANAGER_ARA_CLIENT_COMMANDS_WF_BARRIER_H_
#define UCM_AAP_PKGMANAGER_ARA_CLIENT_COMMANDS_WF_BARRIER_H_

#include "ucm/ara/client/command.h"

namespace bosch {
namespace vrte {
namespace ucm {
namespace ara {
namespace client {

class Wf_BarrierWait final : public Command
{
public:
    explicit Wf_BarrierWait(Tuple& tuple,
                            const std::string& name, StepData&& data);

    Wf_BarrierWait(Wf_BarrierWait     &&) = delete;
    Wf_BarrierWait(Wf_BarrierWait const&) = delete;

    Wf_BarrierWait& operator=(Wf_BarrierWait     &&) = delete;
    Wf_BarrierWait& operator=(Wf_BarrierWait const&) = delete;

    virtual ~Wf_BarrierWait() = default;

protected:
    virtual void impl_perform(StepData&) override;
};

}    // namespace client
}    // namespace ara
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_PKGMANAGER_ARA_CLIENT_COMMANDS_WF_BARRIER_H_
