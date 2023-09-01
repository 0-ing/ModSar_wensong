//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2020 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/ara/client/commands/wf_file_open.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_PKGMANAGER_ARA_CLIENT_COMMANDS_WF_FILE_OPEN_H_
#define UCM_AAP_PKGMANAGER_ARA_CLIENT_COMMANDS_WF_FILE_OPEN_H_

#include "ucm/ara/client/command.h"

namespace bosch {
namespace vrte {
namespace ucm {
namespace ara {
namespace client {

class Wf_FileOpen final : public Command
{
public:
    explicit Wf_FileOpen(Tuple& tuple,
                         const std::string& name, StepData&& data);

    Wf_FileOpen(Wf_FileOpen     &&) = delete;
    Wf_FileOpen(Wf_FileOpen const&) = delete;

    Wf_FileOpen& operator=(Wf_FileOpen     &&) = delete;
    Wf_FileOpen& operator=(Wf_FileOpen const&) = delete;

    virtual ~Wf_FileOpen() = default;

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

#endif // UCM_AAP_PKGMANAGER_ARA_CLIENT_COMMANDS_WF_FILE_OPEN_H_
