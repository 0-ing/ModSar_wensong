//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2020 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/utl/thread.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY_LIB_UTL_THREAD_H_
#define UCM_AAP_LIBRARY_LIB_UTL_THREAD_H_

#include <string>
#include <thread>
#include <atomic>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif


#include "ucm/lib/utl/syserror.h"
#include "ucm/lib/utl/thread_attr.h"
#include "ucm/lib/utl/thread_handle.h"
#include "ucm/lib/utl/thread_factory.h"

namespace bosch {
namespace vrte {
namespace ucm {
namespace lib {
namespace utl {

/// @brief Base class for thread execution across UCM implementation.
///
/// The implementation defines a basic API for controlling a thread of execution
/// life cycle. All threads are started by default with PTHREAD_CANCEL_DISABLE
/// and PTHREAD_CANCEL_DEFERRED flags set.
///
/// The class itself does not keep its running state and is meant to be
/// controlled via the ucm::lib::utl::Runnable class and created by
/// ucm::lib::RunnableFactory, which could provide different ways of controling
/// threads of execution (i.e. POSIX or platform specific threads management).
///
class Thread
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_ucm_lib_utl_Thread, CTor);
    FRIEND_TEST(Test_ucm_lib_utl_Thread, SetName);
    FRIEND_TEST(Test_ucm_lib_utl_Thread, SetPrio);
    FRIEND_TEST(Test_ucm_lib_utl_Thread, Shutdown);
    FRIEND_TEST(Test_ucm_lib_utl_Thread, Startoff);
    FRIEND_TEST(Test_ucm_lib_utl_Thread, SysError);
    FRIEND_TEST(Test_ucm_lib_utl_Thread, BarrierInit);
    FRIEND_TEST(Test_ucm_lib_utl_Thread, BarrierWait);
#endif

    static void barrier_init(pthread_barrier_t*);

    static void barrier_wait(pthread_barrier_t*);

public:
    explicit Thread(ThreadAttr&&, ThreadFactory&);

    // copy semantics
    Thread(const Thread&) = delete;
    Thread& operator=(const Thread&) = delete;

    // move semantic
    Thread(Thread&&) = delete;
    Thread& operator=(Thread&&) = delete;

    virtual ~Thread();

    /// @brief Start a thread which is not running
    ///
    /// @return true if thread is successfully started
    /// @return false if thread failed to start
    bool startoff() noexcept;

    /// @brief Stop a running thread
    ///
    /// @return true if thread is successfully stopped
    /// @return false if thread failed to stop
    bool shutdown() noexcept;

    /// @brief Return the name of the thread.
    ///
    /// @return Constant reference to the thread name
    const auto& name() const noexcept;

    /// @brief Return the system error associated with the Thread object
    ///
    /// @return Constant reference to the syserr_ for the Thread object
    const auto& syserror() const noexcept;

    /// @brief Return the native handle for the thread
    const auto& native_handle() const noexcept;


protected:

    virtual void thread_cancel() noexcept = 0;
    virtual void thread_function() noexcept = 0;

private:
    SysError          syserr_   {};
    pthread_t         thread_id_{};
    pthread_barrier_t barrier_  {};
    std::atomic<bool> startoff_ {false};
    std::atomic<bool> shutdown_ {true};

    ThreadAttr                    attrib_;
    std::unique_ptr<ThreadHandle> handle_;


    /// @brief Set the thread's name
    ///
    /// @return true if name is set, false otherwise and save system error
    bool set_name() noexcept;

    /// @brief Set the thread's POSIX scheduling priority
    ///
    /// @return true if priority is set, false otherwise and save system error
    bool set_prio() noexcept;

    /// @brief Check if thread is started successfully
    ///
    /// @return true if thread is started successfully, false otherwise
    bool thread_startoff_ok() noexcept;

    /// @brief Check if thread is stopped successfully
    ///
    /// @return true if thread is started successfully, false otherwise
    bool thread_shutdown_ok() noexcept;

    /// @brief The main thread function executed in thread context
    void thread_execute() noexcept;
};

inline const auto& Thread::name() const noexcept
{
    return attrib_.name();
}

inline const auto& Thread::syserror() const noexcept
{
    return syserr_;
}

inline const auto& Thread::native_handle() const noexcept
{
    return thread_id_;
}

}    // namespace utl
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif    // UCM_AAP_LIBRARY_LIB_UTL_THREAD_H_
