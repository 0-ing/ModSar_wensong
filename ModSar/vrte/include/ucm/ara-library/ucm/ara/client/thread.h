//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2020 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/ara/client/thread.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_PKGMANAGER_ARA_CLIENT_THREAD_H_
#define UCM_AAP_PKGMANAGER_ARA_CLIENT_THREAD_H_

#include <memory>
#include <vector>

#include "ucm/lib/log/logger.h"
#include "ucm/ara/client/tuple.h"
#include "ucm/ara/client/command.h"

namespace bosch  {
namespace vrte   {
namespace ucm    {
namespace ara    {
namespace client {

class Thread final
{
public:
    explicit Thread(Tuple&& tuple);

    Thread(Thread     &&) = default;
    Thread(Thread const&) = delete;

    Thread& operator=(Thread     &&) = delete;
    Thread& operator=(Thread const&) = delete;

    ~Thread();

    auto& tuple() noexcept;

    void execute() noexcept;

    void add_command(std::unique_ptr<Command>&&);

private:
    Tuple tuple_;
    StepData data_{};
    ucm::lib::log::Logger logger_{};
    std::vector<std::unique_ptr<Command>> commands_{};

    bool command_execute(std::unique_ptr<Command>&) noexcept;
};

inline auto& Thread::tuple() noexcept
{
    return tuple_;
}

}    // namespace client
}    // namespace ara
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_PKGMANAGER_ARA_CLIENT_THREAD_H_
