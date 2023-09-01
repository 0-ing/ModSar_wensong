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

#include "ucm/mock/sequence.h"

#include "ucm/lib/types.h"
#include "ucm/lib/log/logger.h"
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
    : virtual protected ucm::mock::Sequence
{

    static void path_create(const std::string&) {pop<void>();}
    static bool path_exists(const std::string&) {return pop<bool>();}
    static void path_remove(const std::string&) {pop<void>();}

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

    explicit Transaction(Specs&&){}

    Transaction(Transaction     &&) = delete;
    Transaction(Transaction const&) = delete;

    Transaction& operator=(Transaction     &&) = delete;
    Transaction& operator=(Transaction const&) = delete;

    ~Transaction() {};

    const auto& key()        const noexcept;
    const auto& uuid()       const noexcept;
    const auto& group()      const noexcept;
    const auto& fsroot()     const noexcept;
    const auto& created_on() const noexcept;
    const auto  updated_on() const noexcept;

    const uint8_t& progress() const noexcept { return pop<uint8_t const&>(); }

    void touch() noexcept {}

    State state() const noexcept { return pop<State>(); }

    ara_error_type
    upload_close() noexcept { return pop<ara_error_type>(); }

    ara_error_type
    upload_start(const usize_type&) noexcept { return pop<ara_error_type>(); }

    ara_error_type
    upload_block(const ara_data_type&, const usize_type&) noexcept { return pop<ara_error_type>(); }

    ara_error_type
    upload_block(const uint8_t*, const usize_type&, const usize_type&) noexcept { return pop<ara_error_type>(); }

    ara_error_type verify() noexcept { return pop<ara_error_type>(); }

    ara_error_type cancel() noexcept { return pop<ara_error_type>(); }

    ara_error_type finish() { return pop<ara_error_type>(); }

    ara_error_type install() noexcept { return pop<ara_error_type>(); }

    ara_error_type activate() noexcept { return pop<ara_error_type>(); }

    ara_error_type rollback() noexcept { return pop<ara_error_type>(); }

    ara_error_type revert() { return pop<ara_error_type>(); }

    ara_error_type swc_checkdeps() noexcept { return pop<ara_error_type>(); }

    TransferInfo transfer_info() const { return pop<TransferInfo>(); }

    const pkg::mnf::Manifest& manifest() const { return pop<pkg::mnf::Manifest const&>(); }

private:
    ara_error_type rollback_nostm() noexcept { return pop<ara_error_type>(); }
    ara_error_type rollback_state() noexcept { return pop<ara_error_type>(); }

    ara_error_type activate_nostm() noexcept { return pop<ara_error_type>(); }
    ara_error_type activate_state() noexcept { return pop<ara_error_type>(); }
};

inline const auto& Transaction::key() const noexcept
{
    return pop<id_type const&>();
}

inline const auto& Transaction::uuid() const noexcept
{
    return pop<utl::UniqueId::UUID const&>();
}

inline const auto& Transaction::group() const noexcept
{
    return pop<id_type const&>();
}

inline const auto& Transaction::fsroot() const noexcept
{
    return pop<std::string const&>();
}

inline const auto& Transaction::created_on() const noexcept
{
    return pop<timestamp_type const&>();
}

inline const auto Transaction::updated_on() const noexcept
{
    return pop<timestamp_type const&>();
}

}    // namespace upd
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY_LIB_UPD_TRANSACTION_H_
