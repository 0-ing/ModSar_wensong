//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/app/monitor.h
/// @brief
/// @copyright    Robert Bosch GmbH 2018
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY__LIB_APP__MONITOR_H_
#define UCM_AAP_LIBRARY__LIB_APP__MONITOR_H_

#include <queue>
#include <mutex>
#include <memory>
#include <atomic>
#include <exception>
#include <condition_variable>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/utl/pidfile.h"
#include "ucm/lib/app/monitor_event.h"
#include "ucm/lib/sys/thread_signals.h"
#include "ucm/lib/app/core_module.h"
#include "ucm/lib/app/supp_module.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace app   {

class Monitor final
{
#if defined(GOOGLE_TEST)
        FRIEND_TEST(Test_Monitor, Simple);
        FRIEND_TEST(Test_ucm_app_Monitor, CTor);
        FRIEND_TEST(Test_ucm_app_Monitor, other_private_func);
        FRIEND_TEST(Test_ucm_app_Monitor, run_signal_1);
        FRIEND_TEST(Test_ucm_app_Monitor, run_signal_2);
        FRIEND_TEST(Test_ucm_app_Monitor, queue_wait);
        FRIEND_TEST(Test_ucm_app_Monitor, module_config);
        FRIEND_TEST(Test_ucm_app_Monitor, module_setup);
        FRIEND_TEST(Test_ucm_app_Monitor, module_startoff);
#endif

public:
    Monitor(const char* buildid, int argc, char** argv);

    Monitor(Monitor&&) = delete;
    Monitor& operator=(Monitor&&) = delete;

    Monitor(const Monitor&) = delete;
    Monitor& operator=(const Monitor&) = delete;

    ~Monitor();

    void run();

private:
    std::string buildid_;
    std::shared_ptr<CoreModule> core_module_{};
    std::unique_ptr<lib::utl::PidFile> pidfile_{};
    std::unique_ptr<sys::ThreadSignals> thread_signals_{};

    mutable std::mutex queue_mutex_{};
    std::condition_variable queue_cond_{};
    std::atomic_bool queue_quit_{false};
    std::atomic_bool queue_abort_{false};
    std::queue<std::unique_ptr<MonitorEvent>> queue_{};

    void gc_callback(void);
    void queue_wait();
    void queue_wake();
    void queue_quit();
    void queue_abort();
    void queue_post(MonitorEvent::Type type);
    void queue_process(const std::unique_ptr<MonitorEvent>& evt);

    void posix_signal(siginfo_t* siginfo);

    void block_signals();
    void setup_logging();
    void setup_signals();
    void setup_pidfile();

    void modules_setup();
    void modules_config();
    void modules_startoff();
    void modules_shutdown();



    void error_and_exit(const char*);
    void error_and_exit(const std::exception&, const char*);
};



}    // namespace app
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif    // UCM_AAP_LIBRARY__LIB_APP__MONITOR_H_
