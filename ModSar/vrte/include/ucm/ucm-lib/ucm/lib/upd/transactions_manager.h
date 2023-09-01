//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/upd/transactions_manager.h
/// @brief
/// @copyright    Robert Bosch GmbH 2018
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY_LIB_UPD_TRANSACTIONS_MANAGER_H_
#define UCM_AAP_LIBRARY_LIB_UPD_TRANSACTIONS_MANAGER_H_

#include <mutex>
#include <chrono>
#include <string>
#include <cstddef>
#include <cstdint>
#include <unordered_map>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/upd/cache.h"
#include "ucm/lib/app/service.h"
#include "ucm/lib/utl/unique_id.h"
#include "ucm/lib/upd/transaction.h"
#include "ucm/lib/app/core_context.h"
#include "ucm/lib/upd/transaction_group.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace upd   {

class TransactionsManager final : public app::Service
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_ucm_lib_upd_transactions_manager, setup_nolock);
    FRIEND_TEST(Test_ucm_lib_upd_transactions_manager, startoff_nolock);
    FRIEND_TEST(Test_ucm_lib_upd_transactions_manager, shutdown_nolock);
#endif
public:
    explicit TransactionsManager(app::CoreContext&) noexcept;

    // copy semantics
    TransactionsManager(const TransactionsManager&) = delete;
    TransactionsManager& operator=(const TransactionsManager&) = delete;

    // move semantic
    TransactionsManager(TransactionsManager&&) = delete;
    TransactionsManager& operator=(TransactionsManager&&) = delete;

    ~TransactionsManager() = default;

    void expire() noexcept;

    void trans_destroy(const id_type&);

    void group_destroy(const id_type&);

    std::shared_ptr<Transaction> trans_create(const id_type&);

    std::shared_ptr<Transaction> trans_lookup(const id_type&);

    std::shared_ptr<Transaction> trans_remove(const id_type&);

    std::shared_ptr<TransactionGroup> group_create(const id_type&);

    std::shared_ptr<TransactionGroup> group_lookup(const id_type&);

    std::shared_ptr<TransactionGroup> group_remove(const id_type&);

protected:
    bool setup_nolock()    noexcept override;
    bool startoff_nolock() noexcept override;
    bool shutdown_nolock() noexcept override;

private:
    app::CoreContext& context_;
    Cache<Transaction> t_cache_{};
    Cache<TransactionGroup> g_cache_{};

    mutable std::mutex mutex_{};
    std::chrono::seconds expinterval_{86400}; // 1 day

    /// @brief Create a Transaction in the given group
    std::shared_ptr<Transaction> make(const id_type&);

    /// @brief Lock a Transaction
    std::shared_ptr<Transaction> lockit(std::shared_ptr<Transaction>&);

    std::pair<id_type, utl::UniqueId::UUID> keypair_generate();
};

}    // namespace upd
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY_LIB_UPD_TRANSACTIONS_MANAGER_H_
