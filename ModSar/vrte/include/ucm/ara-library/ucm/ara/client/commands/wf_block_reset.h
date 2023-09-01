//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2020 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/ara/client/commands/wf_block_reset.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_PKGMANAGER_ARA_CLIENT_COMMANDS_WF_BLOCK_RESET_H_
#define UCM_AAP_PKGMANAGER_ARA_CLIENT_COMMANDS_WF_BLOCK_RESET_H_

#include "ucm/ara/client/command.h"

namespace bosch {
namespace vrte {
namespace ucm {
namespace ara {
namespace client {

class Wf_BlockReset final : public Command
{
public:
    explicit Wf_BlockReset(Tuple& tuple,
                         const std::string& name, StepData&& data);

    Wf_BlockReset(Wf_BlockReset     &&) = delete;
    Wf_BlockReset(Wf_BlockReset const&) = delete;

    Wf_BlockReset& operator=(Wf_BlockReset     &&) = delete;
    Wf_BlockReset& operator=(Wf_BlockReset const&) = delete;

    virtual ~Wf_BlockReset() = default;

protected:
    virtual void impl_perform(StepData&) override;

private:
    StepData::datasize_type block_size(StepData&);
};

}    // namespace client
}    // namespace ara
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_PKGMANAGER_ARA_CLIENT_COMMANDS_WF_BLOCK_RESET_H_
