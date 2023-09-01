//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/upd/upload_manager.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY__UCM_LIB_UPD__UPLOAD_MANAGER_H_
#define UCM_AAP_LIBRARY__UCM_LIB_UPD__UPLOAD_MANAGER_H_

#include <mutex>
#include <string>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/types.h"
#include "ucm/lib/app/core_context.h"

#include "ucm/lib/upd/phase.h"
#include "ucm/lib/upd/update_context.h"


namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace upd   {

class UploadManager final
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_ucm_lib_upd__UploadManager, start_kUpload);
    FRIEND_TEST(Test_ucm_lib_upd__UploadManager, start_kStream);
    FRIEND_TEST(Test_ucm_lib_upd__UploadManager, start_closed_False);
    friend class UploadManagerUT;
#endif

public:
    explicit UploadManager(UpdateContext&);

    UploadManager(UploadManager     &&) = delete;
    UploadManager(UploadManager const&) = delete;

    UploadManager& operator=(UploadManager     &&) = delete;
    UploadManager& operator=(UploadManager const&) = delete;

    ~UploadManager();

    void enable(bool) noexcept;
    bool enabled() const noexcept;

    void swpackage_set(SWPackage* swpackage) noexcept;

    ara_error_type close() noexcept;
    ara_error_type start(std::size_t) noexcept;
    ara_error_type write(const ara_data_type&, const usize_type&) noexcept;
    ara_error_type write(const uint8_t*,
                         const usize_type&,
                         const usize_type&) noexcept;

private:
    bool enable_{true};
    bool closed_{true};
    UpdateContext& ucontext_;
    app::CoreContext& ccontext_;
    SWPackage* swpackage_{nullptr};
    std::size_t aindex_{0}; // artifact index
    std::shared_ptr<Phase>         phase_{};

    auto& logger() noexcept;
    auto& objects() noexcept;
    auto& object_store() noexcept;
    auto& update_object() noexcept;

    ara_error_type close_dispatch(Object&) noexcept;
    ara_error_type start_dispatch(Object&) noexcept;
    ara_error_type write_dispatch(
            Object&, const uint8_t*, const usize_type&) noexcept;

    ara_error_type close_upload(Object&) noexcept;
    ara_error_type start_upload(Object&) noexcept;
    ara_error_type write_upload(
            const uint8_t*, const usize_type&) noexcept;

    ara_error_type close_stream(Object&) noexcept;
    ara_error_type start_stream(Object&) noexcept;
    ara_error_type write_stream(
            const uint8_t*, const usize_type&) noexcept;

    ara_error_type pipeline_release() noexcept;
};

inline void UploadManager::enable(bool value) noexcept
{
    enable_ = value;
}

inline bool UploadManager::enabled() const noexcept
{
    return enable_;
}

inline auto& UploadManager::objects() noexcept
{
    return ucontext_.object_store().objects();
}

inline auto& UploadManager::object_store() noexcept
{
    return ucontext_.object_store();
}

inline auto& UploadManager::update_object() noexcept
{
    return object_store().currobj();
}

}    // namespace upd
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY__UCM_LIB_UPD__UPLOAD_MANAGER_H_
