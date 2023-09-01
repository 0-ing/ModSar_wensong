//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2022 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/upd/phase.h
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

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/types.h"
#include "ucm/lib/utl/clock_pair.h"
#include "ucm/lib/utl/object_locker.h"

#include "ucm/lib/upd/swpackage.h"
#include "ucm/lib/upd/update_context.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace upd   {

class Phase : public utl::ObjectLocker
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test__ucm_lib_upd__Phase, CTor);
#endif

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

    static const char* type_cstr(const Type&);

    enum class Target : unsigned
    {
        kAny,
        kImage,
        kDevice,
        kApplication
    };

    static const char* target_cstr(const Target&);

    using Device = std::string;

    virtual ~Phase();

    const std::string& name() const noexcept;

    const std::string& logname() const noexcept;

    /// @brief Verify the result of the execution.
    ///
    virtual void reset() noexcept;

    /// @brief Setup the the execution.
    ///
    virtual ara_error_type setup() noexcept = 0;

    /// @brief Verify the result of the execution.
    ///
    virtual ara_error_type verify() noexcept = 0;

    /// @brief Perform the associated action.
    ///
    virtual ara_error_type perform() noexcept = 0;

    /// @brief Executed after the worker method fails.
    ///
    virtual ara_error_type after_failure() noexcept = 0;

    /// @brief Executed after the worker method succeeds.
    ///
    virtual ara_error_type after_success() noexcept = 0;

private:
    std::string name_;
    std::string logname_;

protected:
    UpdateContext& ucontext_;
    utl::ClockPair<timestamp_clock> clock_{};

    explicit Phase(std::string&& name, UpdateContext& uctx);

    Phase(Phase     &&) = delete;
    Phase(Phase const&) = delete;

    Phase& operator=(Phase     &&) = delete;
    Phase& operator=(Phase const&) = delete;
};

std::ostream& operator<<(std::ostream&, const Phase::Type&) noexcept;
std::ostream& operator<<(std::ostream&, const Phase::Target&) noexcept;

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
