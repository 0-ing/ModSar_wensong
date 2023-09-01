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

#include "ucm/mock/sequence.h"
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
      : virtual protected ucm::mock::Sequence
{
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
                     bool iflag, bool hflag, bool fflag, bool sflag)
        noexcept(std::is_nothrow_constructible<bool>::value     &&
                 std::is_nothrow_move_constructible<std::string>::value)
    : tuple_(std::move(name), std::move(specs), iflag, hflag, fflag, sflag)
    {
    }

protected:
    bool started_{false};
    log::Logger logger_{};
    Handle::Tuple tuple_;
    mutable Mutex mutex_{};
};

inline const auto& Backend::name() const noexcept
{
    return pop<std::string const&>();
}

inline const auto& Backend::specs() const noexcept
{
    return pop<std::string const&>();
}

inline const auto& Backend::has_irecord() const noexcept
{
    return pop<bool const&>();
}

inline const auto& Backend::has_hrecord() const noexcept
{
    return pop<bool const&>();
}

inline const auto& Backend::has_frecord() const noexcept
{
    return pop<bool const&>();
}

inline const auto& Backend::has_srecord() const noexcept
{
    return pop<bool const&>();
}


}    // namespace db
}    // namespace swc
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY_UCM_LIB_SWC_DB__BACKEND_H_
