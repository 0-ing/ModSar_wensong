//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2022 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         tests/VRTE_UT/stdmocs/ucm/lib/upd/phase/ucm/lib/upd/phase.h
/// @brief
/// @copyright    Robert Bosch GmbH 2022
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY__UCM_LIB_UPD__PHASE_H_
#define UCM_AAP_LIBRARY__UCM_LIB_UPD__PHASE_H_

#include <mutex>
#include <memory>
#include <utility>

#include "ucm/lib/types.h"
#include "ucm/lib/utl/clock_pair.h"
#include "ucm/lib/utl/object_locker.h"

#include "ucm/lib/upd/swpackage.h"
#include "ucm/lib/upd/update_context.h"
#include "ucm/mock/sequence.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace upd   {

class Phase
        : public utl::ObjectLocker
          , virtual protected ucm::mock::Sequence
{
public:

    enum class Type : unsigned
    {
        kAny,
        kErase,
        kUpload,
        kStream,
        kVerify,
        kCleanup,
        kInstall,
        kActivate,
        kRollback,
    };

    static const char* type_cstr(const Type&) { return ""; }

    enum class Target : unsigned
    {
        kAny,
        kImage,
        kDevice,
        kApplication
    };

    static const char* target_cstr(const Target&) { return ""; }

    using Device = std::string;

    virtual ~Phase() = default;

    const std::string& name() const noexcept;

    const std::string& logname() const noexcept;

    virtual void reset() noexcept {}

    virtual ara_error_type setup() noexcept
    {
        return pop<ara_error_type>();
    }

    virtual ara_error_type verify() noexcept
    {
        return pop<ara_error_type>();
    }

    virtual ara_error_type perform() noexcept
    {
        return pop<ara_error_type>();
    }

    virtual ara_error_type after_failure() noexcept
    {
        return pop<ara_error_type>();
    }

    /// @brief Executed after the worker method succeeds.
    ///
    virtual ara_error_type after_success() noexcept
    {
        return pop<ara_error_type>();
    }

private:
    std::string name_;
    std::string logname_;

protected:
    UpdateContext& ucontext_;
    utl::ClockPair<timestamp_clock> clock_{};

    explicit Phase(std::string&& name, UpdateContext& uctx)
        : name_{std::move(name)}
        , logname_{name_}
        , ucontext_{uctx}
    {}

    Phase(Phase     &&) = delete;
    Phase(Phase const&) = delete;

    Phase& operator=(Phase     &&) = delete;
    Phase& operator=(Phase const&) = delete;
};

inline std::ostream& operator<<(std::ostream& s, const Phase::Type&) noexcept
{ return s; }

inline std::ostream& operator<<(std::ostream& s, const Phase::Target&) noexcept
{ return s; }

inline const std::string& Phase::name() const noexcept
{
    return name_;
}

inline const std::string& Phase::logname() const noexcept
{
    return logname_;
}

}    // namespace upd
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif    // UCM_AAP_LIBRARY__UCM_LIB_UPD__PHASE_H_
