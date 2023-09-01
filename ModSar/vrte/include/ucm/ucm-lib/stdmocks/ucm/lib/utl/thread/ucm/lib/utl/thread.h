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

#include "ucm/mock/sequence.h"

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
        : virtual protected ucm::mock::Sequence
{

    static void barrier_init(pthread_barrier_t*) { pop<void>();}

    static void barrier_wait(pthread_barrier_t*) { pop<void>();}

public:
    explicit Thread(ThreadAttr&&, ThreadFactory&) {}

    // copy semantics
    Thread(const Thread&) = delete;
    Thread& operator=(const Thread&) = delete;

    // move semantic
    Thread(Thread&&) = delete;
    Thread& operator=(Thread&&) = delete;

    virtual ~Thread() {}

    /// @brief Start a thread which is not running
    ///
    /// @return true if thread is successfully started
    /// @return false if thread failed to start
    bool startoff() noexcept {return pop<bool>();}

    /// @brief Stop a running thread
    ///
    /// @return true if thread is successfully stopped
    /// @return false if thread failed to stop
    bool shutdown() noexcept {return pop<bool>();}

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

};

inline const auto& Thread::name() const noexcept
{
    return pop<std::string const&>();
}

inline const auto& Thread::syserror() const noexcept
{
    return pop<SysError const&>();
}

inline const auto& Thread::native_handle() const noexcept
{
    return pop<pthread_t const&>();
}

}    // namespace utl
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif    // UCM_AAP_LIBRARY_LIB_UTL_THREAD_H_
