//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/upd/transaction.h
/// @brief
/// @copyright    Robert Bosch GmbH 2018
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY_LIB_UPD_TRANSACTION_H_
#define UCM_AAP_LIBRARY_LIB_UPD_TRANSACTION_H_

#include <chrono>
#include <future>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/types.h"
#include "ucm/lib/utl/restate.h"
#include "ucm/lib/utl/unique_id.h"
#include "ucm/lib/app/core_context.h"
#include "ucm/lib/utl/upgrade_lock.h"
#include "ucm/lib/utl/object_locker.h"


#include "ucm/lib/upd/swpackage.h"
#include "ucm/lib/upd/object_store.h"
#include "ucm/lib/upd/transfer_info.h"
#include "ucm/lib/upd/upload_manager.h"
#include "ucm/lib/upd/update_context.h"
#include "ucm/lib/upd/transaction_install.h"


namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace upd   {

struct Transaction final
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test__ucm_lib_upd__Transaction, CTor1);
    FRIEND_TEST(Test__ucm_lib_upd__Transaction, CTor2);
    FRIEND_TEST(Test__ucm_lib_upd__Transaction, path_create);
    FRIEND_TEST(Test__ucm_lib_upd__Transaction, path_exists);
    FRIEND_TEST(Test__ucm_lib_upd__Transaction, path_remove);
    FRIEND_TEST(Test__ucm_lib_upd__Transaction, exm_fg_verify);
    FRIEND_TEST(Test__ucm_lib_upd__Transaction, sec_fg_verify);
    FRIEND_TEST(Test__ucm_lib_upd__Transaction, rollback_nostm);
    FRIEND_TEST(Test__ucm_lib_upd__Transaction, activate_nostm);
    FRIEND_TEST(Test__ucm_lib_upd__Transaction, activate_state);
    FRIEND_TEST(Test__ucm_lib_upd__Transaction, rollback_state);
#endif

    static void path_create(const std::string&);
    static bool path_exists(const std::string&);
    static void path_remove(const std::string&);

public:
    enum class State : unsigned
    {
        kIdle,
        kUploadReady,
        kUploading,
        kUploadDone,
        kInstalling,
        kCancelling,
        kInstalled,
        kActivating,
        kActivated,
        kRollingBack,
        kRolledBack,
        kCleaning
    };

    struct Specs
    {
        id_type             key_{0};
        id_type             group_{0};
        std::string         fsroot_{};
        std::string         pkgdir_{};
        timestamp_type      created_on_{};
        timestamp_type      updated_on_{};
        utl::UniqueId::UUID uuid_{};
    };

    explicit Transaction(Specs&&);

    Transaction(Transaction     &&) = delete;
    Transaction(Transaction const&) = delete;

    Transaction& operator=(Transaction     &&) = delete;
    Transaction& operator=(Transaction const&) = delete;

    ~Transaction();

    const auto& key()        const noexcept;
    const auto& uuid()       const noexcept;
    const auto& group()      const noexcept;
    const auto& fsroot()     const noexcept;
    const auto& created_on() const noexcept;
    const auto  updated_on() const noexcept;

    const uint8_t& progress() const noexcept;

    void touch() noexcept;

    State state() const noexcept;

    ara_error_type
    upload_close() noexcept;

    ara_error_type
    upload_start(const usize_type&) noexcept;

    ara_error_type
    upload_block(const ara_data_type&, const usize_type&) noexcept;

    ara_error_type
    upload_block(const uint8_t*, const usize_type&, const usize_type&) noexcept;

    ara_error_type verify() noexcept;

    ara_error_type cancel() noexcept;

    ara_error_type finish();

    ara_error_type install() noexcept;

    ara_error_type activate() noexcept;

    ara_error_type rollback() noexcept;

    ara_error_type revert();

    ara_error_type swc_checkdeps() noexcept;

    TransferInfo transfer_info() const;

    const pkg::mnf::Manifest& manifest() const;

private:
    Specs specs_;
    Counters counters_{};
    std::uint8_t progress_{0xff};

    using Lock = utl::UpgradeLock;
    mutable utl::UpgradeMutex    mutex_      {};
    std::atomic<State>           state_      {State::kIdle};
    /// Only clear while holding a unique lock.
    std::atomic<bool>            cancel_req_ {false};
    /// Don't set or get while holding a unique lock.
    std::promise<ara_error_type> cancel_res_ {};

    // To avoid expensive initializations
    UpdateContext ucontext_;
    app::CoreContext& ccontext_;
    UploadManager upload_manager_;
    ara_error_type ara_error_{ara_error_type::Ok};
    std::unique_ptr<SWPackage> swpackage_{};
    std::unique_ptr<TransactionInstall> install_{};

private:
    auto& objects() noexcept;
    auto& object_store() noexcept;

    auto ara_error(const ara_error_type&) noexcept;

    ara_error_type rollback_nostm() noexcept;
    ara_error_type rollback_state() noexcept;

    ara_error_type activate_nostm() noexcept;
    ara_error_type activate_state() noexcept;

    ara_error_type exm_fg_verify() noexcept;

    ara_error_type sec_fg_verify() noexcept;

    ara_error_type process_tar() noexcept;
    ara_error_type swpackage_tar() noexcept;

    ara_error_type process_bin() noexcept;
    ara_error_type swpackage_bin() noexcept;

    ara_error_type img_install(const std::string&,
                               const pkg::mnf::ArtifactObject&) noexcept;

    ara_error_type install_action() noexcept; ///< select between update actions

    ara_error_type swc_install() noexcept;

    ara_error_type swc_update() noexcept;

    ara_error_type revert(Lock&);

    ara_error_type swc_remove() noexcept;

    ara_error_type swc_finish_install() noexcept;

    ara_error_type swc_finish_update() noexcept;

    ara_error_type swc_finish_remove() noexcept;

    ara_error_type manifest_process(const std::string&) noexcept;

    ara_error_type object_create(const usize_type&,
                                 const Object::Method&) noexcept;

    ara_error_type
    upload_start_nolock(const usize_type&) noexcept;

    ara_error_type
    upload_nolock(const uint8_t*, const usize_type&, const usize_type&) noexcept;

};

inline const auto& Transaction::key() const noexcept
{
    return specs_.key_;
}

inline const auto& Transaction::uuid() const noexcept
{
    return specs_.uuid_;
}

inline const auto& Transaction::group() const noexcept
{
    return specs_.group_;
}

inline const auto& Transaction::fsroot() const noexcept
{
    return specs_.fsroot_;
}

inline const auto& Transaction::created_on() const noexcept
{
    return specs_.created_on_;
}

inline const auto Transaction::updated_on() const noexcept
{
    return specs_.updated_on_;
}

inline auto& Transaction::objects() noexcept
{
    return ucontext_.object_store().objects();
}

inline auto& Transaction::object_store() noexcept
{
    return ucontext_.object_store();
}

inline auto Transaction::ara_error(const ara_error_type& value) noexcept
{
    ara_error_ = value;
    return ara_error_;
}

inline const uint8_t& Transaction::progress() const noexcept
{
    return progress_;
}

}    // namespace upd
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY_LIB_UPD_TRANSACTION_H_

