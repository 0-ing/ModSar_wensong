//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2020 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/ara/client/db_mutex.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_PKGMANAGER_ARA_CLIENT_DB_MUTEX_H_
#define UCM_AAP_PKGMANAGER_ARA_CLIENT_DB_MUTEX_H_

#include <pthread.h>

#include <mutex>
#include <memory>
#include <string>

namespace bosch {
namespace vrte {
namespace ucm {
namespace ara {
namespace client {

class DB_Mutex final
{
public:
    explicit DB_Mutex(const std::string&);

    DB_Mutex(DB_Mutex     &&) = default;
    DB_Mutex(DB_Mutex const&) = delete;

    DB_Mutex& operator=(DB_Mutex     &&) = default;
    DB_Mutex& operator=(DB_Mutex const&) = delete;

    ~DB_Mutex() = default;

    auto& operator()() noexcept;

    const auto& name() const noexcept;

private:
    std::string name_;
    std::unique_ptr<std::mutex> mutex_;
};

inline auto& DB_Mutex::operator()() noexcept
{
    return *mutex_;
}

inline const auto& DB_Mutex::name() const noexcept
{
    return name_;
}

}    // namespace client
}    // namespace ara
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_PKGMANAGER_ARA_CLIENT_DB_MUTEX_H_
