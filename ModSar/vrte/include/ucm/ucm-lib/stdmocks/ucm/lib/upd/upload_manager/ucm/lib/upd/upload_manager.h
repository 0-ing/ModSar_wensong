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

#include "ucm/lib/types.h"
#include "ucm/lib/app/core_context.h"

#include "ucm/lib/upd/phase.h"
#include "ucm/lib/upd/object.h"
#include "ucm/lib/upd/counters.h"
#include "ucm/lib/upd/update_context.h"


namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace upd   {

class UploadManager final
      : virtual protected ucm::mock::Sequence
{

public:
    explicit UploadManager(UpdateContext& context)
    : ucontext_{context}
    {
    }

    UploadManager(UploadManager     &&) = delete;
    UploadManager(UploadManager const&) = delete;

    UploadManager& operator=(UploadManager     &&) = delete;
    UploadManager& operator=(UploadManager const&) = delete;

    ~UploadManager() {};

    void enable(bool) noexcept;
    bool enabled() const noexcept;

    ara_error_type close() noexcept {return pop<ara_error_type>();}
    ara_error_type start(std::size_t) noexcept  {return pop<ara_error_type>();}
    ara_error_type write(const ara_data_type&, const usize_type&) noexcept  {return pop<ara_error_type>();}
    ara_error_type write(const uint8_t*,
                         const usize_type&,
                         const usize_type&) noexcept  {return pop<ara_error_type>();}

private:
    bool enable_{true};
    bool closed_{true};
    UpdateContext& ucontext_;
    std::shared_ptr<Phase> phase_{};
    std::shared_ptr<ppl::Instance> pipeline_{};

    auto& logger() noexcept;
    auto& objects() noexcept;
    auto& object_store() noexcept;
    auto& update_object() noexcept;

    ara_error_type close_dispatch(Object&) noexcept {return pop<ara_error_type>();}
    ara_error_type start_dispatch(Object&) noexcept {return pop<ara_error_type>();}
    ara_error_type write_dispatch(
            Object&, const uint8_t*, const usize_type&) noexcept {return pop<ara_error_type>();}

    ara_error_type close_upload(Object&) noexcept {return pop<ara_error_type>();}
    ara_error_type start_upload(Object&) noexcept {return pop<ara_error_type>();}
    ara_error_type write_upload(
            const uint8_t*, const usize_type&) noexcept {return pop<ara_error_type>();}

    ara_error_type close_stream(Object&) noexcept {return pop<ara_error_type>();}
    ara_error_type start_stream(Object&) noexcept {return pop<ara_error_type>();}
    ara_error_type write_stream(
            const uint8_t*, const usize_type&) noexcept {return pop<ara_error_type>();}

    ara_error_type pipeline_acquire() noexcept {return pop<ara_error_type>();}
    ara_error_type pipeline_release() noexcept {return pop<ara_error_type>();}
};

inline void UploadManager::enable(bool value) noexcept
{
    enable_ = value;
}

inline bool UploadManager::enabled() const noexcept
{
    return pop<bool>();
}

inline auto& UploadManager::logger() noexcept
{
    return pop<log::Logger&>();
}

inline auto& UploadManager::objects() noexcept
{
    return pop<std::vector<Object>&>();
}

inline auto& UploadManager::object_store() noexcept
{
    return pop<ObjectStore&>();
}

inline auto& UploadManager::update_object() noexcept
{
    return pop<ObjectStore&>();
}

}    // namespace upd
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY__UCM_LIB_UPD__UPLOAD_MANAGER_H_
