//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2020 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/ara/api/server.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_PKGMANAGER_ARA_API_SERVER_H_
#define UCM_AAP_PKGMANAGER_ARA_API_SERVER_H_

#include <memory>
#include <functional>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif


#include "ucm/lib/app/core_context.h"
#include "ucm/lib/upd/transactions_manager.h"
#include "ucm/ara/api/package_manager_ara.h"
#include "ucm/ara/api/package_manager_1911.h"


/// @addtogroup bosch_vrte_ucm_ara_api
/// @{

namespace bosch {
namespace vrte {
namespace ucm {
namespace ara {
namespace api {

/// @class Server
/// @ingroup bosch_vrte_ucm_ara_api
/// @brief Package manager server.
///

class Server final
{


/// Friend class for unit tests
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_ucm_ara_api_Server, StartoffServices);
    FRIEND_TEST(Test_ucm_ara_api_Server, ShutdownServices);
#endif
public:
    /// Explicit parameterized constructor
    explicit Server(const ucm::lib::cfg::Table&,
                    ucm::lib::swc::db::Service&,
                    ucm::lib::stm::UCM_State&,
                    ucm::lib::stm::Service&,
                    ucm::lib::upd::TransactionsManager&) noexcept;

    /// Copy semantics
    Server(const Server&) = delete;

    /// Copy semantics
    Server& operator=(const Server&) = delete;

    /// Move semantics
    Server(Server&&) = delete;

    /// Move semantics
    Server& operator=(Server&&) = delete;

    /// Virtual destructor
    virtual ~Server() = default;

    /// \brief Start package manager services.
    void startoff_services();

    /// \brief Shutdown package manager services.
    void shutdown_services();

private:
    const ucm::lib::cfg::Table& config_; /// Reference for Configuration
    ucm::lib::swc::db::Service& swcdbs_; /// Reference to SW database
    ucm::lib::stm::UCM_State& ucm_state_; /// Reference to UCM state
    ucm::lib::stm::Service& stm_service_; /// Reference to STM Bridge
    ucm::lib::upd::TransactionsManager& tmanager_; /// Reference to Transacton manager
    std::unique_ptr<PackageManager1911> pkgmanager_ara_{}; /// Unique pointer to PackageManager1911 object
};

}    // namespace api
}    // namespace ara
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif    // UCM_AAP_PKGMANAGER_ARA_API_SERVER_H_
