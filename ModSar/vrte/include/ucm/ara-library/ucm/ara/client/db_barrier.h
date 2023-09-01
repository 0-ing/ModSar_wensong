//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2020 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/ara/client/db_barrier.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_PKGMANAGER_ARA_CLIENT_DB_BARRIER_H_
#define UCM_AAP_PKGMANAGER_ARA_CLIENT_DB_BARRIER_H_

#include <pthread.h>

#include <mutex>
#include <memory>
#include <string>

namespace bosch {
namespace vrte {
namespace ucm {
namespace ara {
namespace client {

class DB_Barrier final
{
public:
    explicit DB_Barrier(const std::string&, unsigned);

    DB_Barrier(DB_Barrier     &&) = default;
    DB_Barrier(DB_Barrier const&) = delete;

    DB_Barrier& operator=(DB_Barrier     &&) = default;
    DB_Barrier& operator=(DB_Barrier const&) = delete;

    ~DB_Barrier();

    void operator()() noexcept;

    const auto& name() const noexcept;

private:
    std::string name_;
    std::unique_ptr<pthread_barrier_t> barrier_;
};

inline const auto& DB_Barrier::name() const noexcept
{
    return name_;
}

}    // namespace client
}    // namespace ara
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_PKGMANAGER_ARA_CLIENT_DB_BARRIER_H_
