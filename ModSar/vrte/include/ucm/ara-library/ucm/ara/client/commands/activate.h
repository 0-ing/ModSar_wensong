//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/ara/client/commands/activate.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       dsh8cob
/// @version
/// @remarks

#ifndef UCM_AAP_PKGMANAGER_ARA_CLIENT_COMMANDS_ACTIVATE_H_
#define UCM_AAP_PKGMANAGER_ARA_CLIENT_COMMANDS_ACTIVATE_H_

#include "ucm/ara/client/command.h"

namespace bosch  {
namespace vrte   {
namespace ucm    {
namespace ara    {
namespace client {

class Activate final : public Command
{
public:
    explicit Activate(Tuple& tuple,
                      const std::string& name, StepData&& data);

    Activate(Activate     &&) = delete;
    Activate(Activate const&) = delete;

    Activate& operator=(Activate     &&) = delete;
    Activate& operator=(Activate const&) = delete;

    virtual ~Activate() = default;

protected:
    virtual void impl_perform(StepData&) override;
};

}    // namespace client
}    // namespace ara
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_PKGMANAGER_ARA_CLIENT_COMMANDS_ACTIVATE_H_
