//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2020 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/ara/client/command.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_PKGMANAGER_ARA_CLIENT_COMMAND_H_
#define UCM_AAP_PKGMANAGER_ARA_CLIENT_COMMAND_H_

#include <map>
#include <mutex>
#include <memory>

#include "ucm/lib/types.h"
#include "ucm/lib/log/logger.h"
#include "ucm/ara/client/tuple.h"
#include "ucm/ara/client/ara_proxy.h"
#include "ucm/ara/client/step_data.h"

namespace bosch {
namespace vrte {
namespace ucm {
namespace ara {
namespace client {

class Command
{
protected:
    explicit Command(Tuple& tuple, const std::string& name, StepData&& data);

public:

    Command(Command     &&) = delete;
    Command(Command const&) = delete;

    Command& operator=(Command     &&) = delete;
    Command& operator=(Command const&) = delete;

    virtual ~Command();

    const auto& name() const noexcept;
    const auto& data() const noexcept;

    void perform(StepData&);

protected:
    Tuple& tuple_;
    StepData data_;
    std::string name_;
    ucm::lib::log::Logger logger_{};

    virtual void impl_perform(StepData&) = 0;
};

inline const auto& Command::name() const noexcept
{
    return name_;
}

inline const auto& Command::data() const noexcept
{
    return data_;
}

}    // namespace client
}    // namespace ara
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_PKGMANAGER_ARA_CLIENT_COMMAND_H_
