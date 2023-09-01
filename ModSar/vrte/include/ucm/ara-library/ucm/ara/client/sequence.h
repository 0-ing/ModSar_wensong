//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2020 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/ara/client/sequence.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_PKGMANAGER_ARA_CLIENT_SEQUENCE_H_
#define UCM_AAP_PKGMANAGER_ARA_CLIENT_SEQUENCE_H_

#include <memory>
#include <vector>

#include "ucm/ara/client/gtuple.h"
#include "ucm/ara/client/thread.h"

namespace bosch {
namespace vrte {
namespace ucm {
namespace ara {
namespace client {

class Sequence final
{
public:
    explicit Sequence() = default;

    Sequence(Sequence     &&) = delete;
    Sequence(Sequence const&) = delete;

    Sequence& operator=(Sequence     &&) = delete;
    Sequence& operator=(Sequence const&) = delete;

    ~Sequence() = default;

    auto& tuple() noexcept;

    void execute(void);

    void add_thread(std::unique_ptr<Thread>&&);

private:
    GTuple gtuple_{};
    std::vector<std::unique_ptr<Thread>> threads_{};
};

inline auto& Sequence::tuple() noexcept
{
    return gtuple_;
}

}    // namespace client
}    // namespace ara
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_PKGMANAGER_ARA_CLIENT_SEQUENCE_H_
