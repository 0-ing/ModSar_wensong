//==============================================================================
// C O P Y R I G H T
//------------------------------------------------------------------------------
// Copyright (c) 2020 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//==============================================================================

/// @file         ucm/lib/swc/db/backend.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY_UCM_LIB_SWC_DB__BACKEND_H_
#define UCM_AAP_LIBRARY_UCM_LIB_SWC_DB__BACKEND_H_

#include <memory>
#include <vector>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/log/logger.h"
#include "ucm/lib/swc/db/query.h"
#include "ucm/lib/swc/db/handle.h"


namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace swc   {
namespace db    {


class Backend
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_ucm_lib_swc_db__Backend, CTor);
    FRIEND_TEST(Test_ucm_lib_swc_db_bdb__BDB_Backend, Shutdown);
    FRIEND_TEST(Test_ucm_lib_swc_db_bdb__BDB_Backend, Startoff);
#endif
public:

    Backend(Backend     &&) = delete;
    Backend(Backend const&) = delete;

    Backend& operator=(Backend     &&) = delete;
    Backend& operator=(Backend const&) = delete;

    virtual ~Backend() = default;

    const auto& name() const noexcept;
    const auto& specs() const noexcept;
    const auto& has_irecord() const noexcept;
    const auto& has_hrecord() const noexcept;
    const auto& has_frecord() const noexcept;
    const auto& has_srecord() const noexcept;

    virtual void startoff() = 0;
    virtual void shutdown() = 0;

    virtual std::unique_ptr<Handle> select_handle() = 0;
    virtual std::unique_ptr<Handle> update_handle() = 0;

protected:
    explicit Backend(std::string&& name, std::string&& specs,
                     bool irecord, bool hrecord, bool frecord, bool srecord)
        noexcept(std::is_nothrow_constructible<bool>::value     &&
                 std::is_nothrow_move_constructible<std::string>::value);

protected:
    bool started_{false};
    log::Logger logger_{};
    Handle::Tuple tuple_;
    mutable Mutex mutex_{};
};

inline const auto& Backend::name() const noexcept
{
    return tuple_.name_;
}

inline const auto& Backend::specs() const noexcept
{
    return tuple_.specs_;
}

inline const auto& Backend::has_irecord() const noexcept
{
    return tuple_.irecord_enable_;
}

inline const auto& Backend::has_hrecord() const noexcept
{
    return tuple_.hrecord_enable_;
}

inline const auto& Backend::has_frecord() const noexcept
{
    return tuple_.hrecord_enable_;
}

inline const auto& Backend::has_srecord() const noexcept
{
    return tuple_.srecord_enable_;
}


}    // namespace db
}    // namespace swc
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY_UCM_LIB_SWC_DB__BACKEND_H_
