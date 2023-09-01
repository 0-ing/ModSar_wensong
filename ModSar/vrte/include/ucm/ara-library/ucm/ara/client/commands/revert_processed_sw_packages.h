//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/ara/client/commands/revert_processed_sw_packages.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       dsh8cob
/// @version
/// @remarks

#ifndef UCM_AAP_PKGMANAGER_ARA_CLIENT_COMMANDS_REVERT_PROCESSED_SW_PACKAGES_H_
#define UCM_AAP_PKGMANAGER_ARA_CLIENT_COMMANDS_REVERT_PROCESSED_SW_PACKAGES_H_

#include "ucm/ara/client/command.h"

namespace bosch  {
namespace vrte   {
namespace ucm    {
namespace ara    {
namespace client {

class RevertProcessedSwPackages final : public Command
{
public:
    explicit RevertProcessedSwPackages(Tuple& tuple,
                                       const std::string& name,
                                       StepData&& data);

    RevertProcessedSwPackages(RevertProcessedSwPackages     &&) = delete;
    RevertProcessedSwPackages(RevertProcessedSwPackages const&) = delete;

    RevertProcessedSwPackages& operator=(
            RevertProcessedSwPackages     &&) = delete;
    RevertProcessedSwPackages& operator=(
            RevertProcessedSwPackages const&) = delete;

    virtual ~RevertProcessedSwPackages() = default;

protected:
    virtual void impl_perform(StepData&) override;
};

}    // namespace client
}    // namespace ara
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_PKGMANAGER_ARA_CLIENT_COMMANDS_REVERT_PROCESSED_SW_PACKAGES_H_
