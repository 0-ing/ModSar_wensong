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

#include <set>
#include <mutex>
#include <chrono>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/types.h"
#include "ara/core/result.h"
#include "ucm/lib/upd/cache.h"
#include "ucm/lib/upd/transaction.h"
#include "ucm/lib/upd/update_context.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace upd   {

class TransactionGroup final : public utl::ObjectLocker
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test__ucm_lib_upd__TransactionGroup, Constructor_Correct);
    FRIEND_TEST(Test__ucm_lib_upd__TransactionGroup, Constructor_NoFolder);
    FRIEND_TEST(Test__ucm_lib_upd__TransactionGroup, path_exists);
    FRIEND_TEST(Test__ucm_lib_upd__TransactionGroup, path_create);
    FRIEND_TEST(Test__ucm_lib_upd__TransactionGroup, t_path_make);
    FRIEND_TEST(Test__ucm_lib_upd__TransactionGroup, expire);
    FRIEND_TEST(Test__ucm_lib_upd__TransactionGroup, clear);
    FRIEND_TEST(Test__ucm_lib_upd__TransactionGroup, create);
    FRIEND_TEST(Test__ucm_lib_upd__TransactionGroup, remove);
    FRIEND_TEST(Test__ucm_lib_upd__TransactionGroup, lookup);
    FRIEND_TEST(Test__ucm_lib_upd__TransactionGroup, revert);
    FRIEND_TEST(Test__ucm_lib_upd__TransactionGroup, transfer_info);
    FRIEND_TEST(Test__ucm_lib_upd__TransactionGroup, files_delete_positive);
    FRIEND_TEST(Test__ucm_lib_upd__TransactionGroup,
                files_delete_positive_path_exists);
    FRIEND_TEST(Test__ucm_lib_upd__TransactionGroup, key);
    FRIEND_TEST(Test__ucm_lib_upd__TransactionGroup, stm_update_enter);
    FRIEND_TEST(Test__ucm_lib_upd__TransactionGroup, stm_update_leave);
#endif

    static void path_create(const std::string&);
    static bool path_exists(const std::string&);
    static void path_remove(const std::string&);

    static std::string g_path_make(const id_type&, const std::string&);
    static std::string t_path_make(const id_type&, const std::string&);

    static const std::string& scratch_path(app::CoreContext&);

public:
    explicit TransactionGroup(
            const id_type&, app::CoreContext&, Cache<Transaction>&);

    TransactionGroup(TransactionGroup&&) noexcept = delete;
    TransactionGroup& operator=(TransactionGroup&&) = delete;

    TransactionGroup(const TransactionGroup&) = delete;
    TransactionGroup& operator=(const TransactionGroup&) = delete;

    virtual ~TransactionGroup();

    void files_delete();

    const auto& key() const noexcept;

    void clear() noexcept;

    void expire(const std::chrono::seconds&) noexcept;

    void destroy(const id_type&);

    std::shared_ptr<Transaction> create();

    std::shared_ptr<Transaction> lookup(const id_type&);

    std::shared_ptr<Transaction> remove(const id_type&);

    __attribute__((warn_unused_result))
    ara_error_type revert() noexcept;

    __attribute__((warn_unused_result))
    ara_error_type finish() noexcept;

    __attribute__((warn_unused_result))
    ara_error_type activate() noexcept;

    __attribute__((warn_unused_result))
    ara_error_type verify() noexcept;

    __attribute__((warn_unused_result))
    ara_error_type rollback() noexcept;

    std::vector<TransferInfo> transfer_info() const;

    /// @brief A generic method to create a set, quering all Transactions.
    ///
    /// @param conf The method from pkg::mnf::SectionUpdate to return the
    /// required configuration.
    /// @param pred Predicate that allows/denies inclusion of the transaction's
    /// values in the set.
    /// @return Unique collection of the selected configuration elements.
    /// @throws Underlying methods may throw, so proper handling should be done
    /// by the caller.
    std::set<std::string> get_fgroups(
            const pkg::mnf::Configuration& (
                    pkg::mnf::SectionUpdate::* conf)() const,
                    std::function<bool(
                            const std::shared_ptr<Transaction>&)> pred
    ) const;

    /// @brief Create a std::set from configurations of all transactions.
    ///
    /// @param conf The method from pkg::mnf::SectionUpdate to return the
    /// required configuration.
    /// @return Unique collection of the selected configuration elements.
    /// @throws Underlying methods may throw, so proper handling should be done
    /// by the caller.
    std::set<std::string> get_fgroups(
            const pkg::mnf::Configuration&
                (pkg::mnf::SectionUpdate::* conf)() const
    ) const;


    /// @brief Create a std::set from configurations of transactions for a state
    ///
    /// @param state The required state for each Transaction.
    /// @param conf The method from pkg::mnf::SectionUpdate to return the
    /// required configuration.
    /// @return Unique collection of the selected configuration elements.
    /// @throws Underlying methods may throw, so proper handling should be done
    /// by the caller.
    std::set<std::string> get_fgroups(
            const pkg::mnf::Configuration&
                (pkg::mnf::SectionUpdate::* conf)() const,
            Transaction::State state
    ) const;

    bool any(std::function<bool(std::shared_ptr<Transaction>&)>&&) noexcept;
    bool all(std::function<bool(std::shared_ptr<Transaction>&)>&&) noexcept;

    bool all(std::function<bool(
            const std::shared_ptr<Transaction>&)>&&) const noexcept;

private:
    id_type id_;
    std::string fsroot_;
    app::CoreContext& context_;
    Cache<Transaction>& cache_;

    template<typename T> using Result = ::ara::core::Result<T, ara_error_type>;

    ara_error_type stm_update_enter() noexcept;

    ara_error_type stm_update_leave() noexcept;
};

inline const auto& TransactionGroup::key() const noexcept
{
    return id_;
}

}    // namespace upd
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY_LIB_UPD_TRANSACTION_GROUP_H_
