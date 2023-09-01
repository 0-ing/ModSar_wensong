//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2020 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/ara/client/gtuple.h
/// @brief
/// @copyright    Robert Bosch GmbH 2022
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_PKGMANAGER_ARA_CLIENT_GTUPLE_H_
#define UCM_AAP_PKGMANAGER_ARA_CLIENT_GTUPLE_H_

#include <pthread.h>

#include <map>
#include <mutex>
#include <memory>

#include "ucm/lib/log/logger.h"
#include "ucm/lib/utl/file_io.h"
#include "ucm/ara/client/db_mutex.h"
#include "ucm/ara/client/ara_proxy.h"
#include "ucm/ara/client/db_barrier.h"


namespace bosch  {
namespace vrte   {
namespace ucm    {
namespace ara    {
namespace client {

class GTuple final
{
public:
    explicit GTuple();

    GTuple(GTuple     &&) = delete;
    GTuple(GTuple const&) = delete;

    GTuple& operator=(GTuple     &&) = delete;
    GTuple& operator=(GTuple const&) = delete;

    ~GTuple() = default;

    auto& mutex(const std::string& name);

    auto& barrier(const std::string& name);

    const auto& filepath(const std::string& name);

    const ARATypes::TransferIdType&
    transfer_id(const ARATypes::TransferIdType& key) const;

    void add_mutex(const std::string& name);

    void add_barrier(const std::string& name, unsigned count);

    void add_filepath(const std::string& name, const std::string& path);

    void add_transfer_id(const ARATypes::TransferIdType& key,
                         const ARATypes::TransferIdType& id);

private:
    ucm::lib::log::Logger logger_{};
    std::map<std::string, DB_Mutex> mutexes_{};
    std::map<std::string, std::string> files_{};
    std::map<std::string, DB_Barrier> barriers_{};
    std::map<ARATypes::TransferIdType, ARATypes::TransferIdType> id_{};
};


inline auto& GTuple::mutex(const std::string& name)
{
    return mutexes_.at(name);
}

inline auto& GTuple::barrier(const std::string& name)
{
    return barriers_.at(name);
}

inline const auto& GTuple::filepath(const std::string& name)
{
    return files_.at(name);
}

}    // namespace client
}    // namespace ara
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_PKGMANAGER_ARA_CLIENT_GTUPLE_H_
