//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/sys/thread_signals.h
/// @brief
/// @copyright    Robert Bosch GmbH 2018
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY__LIB_SYS__THREAD_SIGNALS_H_
#define UCM_AAP_LIBRARY__LIB_SYS__THREAD_SIGNALS_H_

#include <atomic>
#include <csignal>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/utl/thread.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace sys   {

class ThreadSignals final : public lib::utl::Thread
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_ThreadSignals, Simple);
    FRIEND_TEST(Test_ucm_app_ThreadSignals, thread_function);
#endif

public:
    explicit ThreadSignals(lib::utl::ThreadAttr&&, lib::utl::ThreadFactory&,
                           const std::function<void(siginfo_t*)>&& sigfnc);
    virtual ~ThreadSignals();

protected:
    void thread_cancel() noexcept override;
    void thread_function() noexcept override;

private:
    std::atomic_bool quit_{false};
    const std::function<void(siginfo_t*)> signal_dispatch_;
};

}    // namespace sys
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif    // UCM_AAP_LIBRARY__LIB_SYS__THREAD_SIGNALS_H_
