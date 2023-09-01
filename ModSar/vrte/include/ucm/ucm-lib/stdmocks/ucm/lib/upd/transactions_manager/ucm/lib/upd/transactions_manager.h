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

#include "ucm/mock/sequence.h"
#include "ucm/lib/upd/cache.h"
#include "ucm/lib/utl/unique_id.h"
#include "ucm/lib/upd/transaction.h"
#include "ucm/lib/app/core_context.h"
#include "ucm/lib/upd/transaction_group.h"

namespace bosch {
namespace vrte {
namespace ucm {
namespace lib {
namespace upd {

class TransactionsManager final
      : app::Service
      , virtual protected ucm::mock::Sequence
{
public:
    explicit TransactionsManager(app::CoreContext&) noexcept
        : app::Service("upd::TransactionsManager")
    {}

    // copy semantics
    TransactionsManager(const TransactionsManager&) = delete;
    TransactionsManager& operator=(const TransactionsManager&) = delete;

    // move semantic
    TransactionsManager(TransactionsManager&&) = delete;
    TransactionsManager& operator=(TransactionsManager&&) = delete;

    ~TransactionsManager() = default;

    void expire() noexcept {pop<void>();}

    void trans_destroy(const id_type&) {pop<void>();}

    void group_destroy(const id_type&) {pop<void>();}

    std::shared_ptr<Transaction> trans_create(const id_type&) {return pop<std::shared_ptr<Transaction>>();}

    std::shared_ptr<Transaction> trans_lookup(const id_type&) {return pop<std::shared_ptr<Transaction>>();}

    std::shared_ptr<Transaction> trans_remove(const id_type&) {return pop<std::shared_ptr<Transaction>>();}

    std::shared_ptr<TransactionGroup> group_create(const id_type&) {return pop<std::shared_ptr<TransactionGroup>>();}

    std::shared_ptr<TransactionGroup> group_lookup(const id_type&) {return pop<std::shared_ptr<TransactionGroup>>();}

    std::shared_ptr<TransactionGroup> group_remove(const id_type&) {return pop<std::shared_ptr<TransactionGroup>>();}

protected:
    bool setup_nolock()    noexcept override { return true; }
    bool startoff_nolock() noexcept override { return true; }
    bool shutdown_nolock() noexcept override { return true; }
};

}    // namespace upd
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY_LIB_UPD_TRANSACTIONS_MANAGER_H_
