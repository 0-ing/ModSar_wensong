//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2020 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/upd/transaction_group.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY_LIB_UPD_TRANSACTION_GROUP_H_
#define UCM_AAP_LIBRARY_LIB_UPD_TRANSACTION_GROUP_H_

#include <mutex>
#include <chrono>

#include "ucm/lib/types.h"
#include "ucm/lib/upd/cache.h"
#include "ucm/lib/upd/transaction.h"
#include "ucm/lib/upd/update_context.h"

#include "ucm/mock/sequence.h"

// only present in mock, not in original file
#include <vector>
#include <algorithm>

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace upd   {

class TransactionGroup final
       : public utl::ObjectLocker
       , virtual protected ucm::mock::Sequence
{
public:
    std::vector<std::shared_ptr<Transaction>> __mock_vector {};

    explicit TransactionGroup(
            const id_type& , app::CoreContext& , Cache<Transaction>& )
    {
    }

    TransactionGroup(TransactionGroup&&) noexcept = delete;
    TransactionGroup& operator=(TransactionGroup&&) = delete;

    TransactionGroup(const TransactionGroup&) = delete;
    TransactionGroup& operator=(const TransactionGroup&) = delete;

    virtual ~TransactionGroup() {}

    void files_delete() {pop<void>();}

    const id_type& key() const noexcept { return pop<id_type const&>(); }

    void clear() noexcept {pop<void>();}

    void expire(const std::chrono::seconds&) noexcept {pop<void>();}

    void destroy(const id_type&) {pop<void>();}

    std::shared_ptr<Transaction> create() {return pop<std::shared_ptr<Transaction>>();}

    std::shared_ptr<Transaction> lookup(const id_type&) {return pop<std::shared_ptr<Transaction>>();}

    std::shared_ptr<Transaction> remove(const id_type&) {return pop<std::shared_ptr<Transaction>>();}

    __attribute__((warn_unused_result))
    ara_error_type revert() noexcept {return pop<ara_error_type>();}

    __attribute__((warn_unused_result))
    ara_error_type finish() noexcept {return pop<ara_error_type>();}

    __attribute__((warn_unused_result))
    ara_error_type activate() noexcept {return pop<ara_error_type>();}

    __attribute__((warn_unused_result))
    ara_error_type verify() noexcept {return pop<ara_error_type>();}

    __attribute__((warn_unused_result))
    ara_error_type rollback() noexcept {return pop<ara_error_type>();}

    std::vector<TransferInfo> transfer_info() const { return pop<std::vector<TransferInfo>>();}

    std::set<std::string> get_fgroups(
            const pkg::mnf::Configuration& (pkg::mnf::SectionUpdate::*)() const,
                    std::function<bool(const std::shared_ptr<Transaction>&)>
        ) const
    {
        return pop<std::set<std::string>>();
    }

    std::set<std::string> get_fgroups(
            const pkg::mnf::Configuration& (
                    pkg::mnf::SectionUpdate::*)() const
        ) const
    {
        return pop<std::set<std::string>>();
    }

    std::set<std::string> get_fgroups(
            const pkg::mnf::Configuration& (
                    pkg::mnf::SectionUpdate::*)() const,
            Transaction::State
        ) const
    {
        return pop<std::set<std::string>>();
    }

    bool any(std::function<bool(std::shared_ptr<Transaction>&)>&& cb) noexcept
    {
        if (not __mock_vector.empty())
            return std::any_of(__mock_vector.begin(), __mock_vector.end(), cb);
        return pop<bool>();
    }

    bool all(std::function<bool(std::shared_ptr<Transaction>&)>&& cb) noexcept
    {
        if (not __mock_vector.empty())
            return std::all_of(__mock_vector.begin(), __mock_vector.end(), cb);
        return pop<bool>();
    }

    bool all(std::function<bool(
            const std::shared_ptr<Transaction>&)>&& cb) const noexcept
    {
        if (not __mock_vector.empty())
            return std::all_of(__mock_vector.begin(), __mock_vector.end(), cb);
        return pop<bool>();
    }
};

}    // namespace upd
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY_LIB_UPD_TRANSACTION_GROUP_H_
