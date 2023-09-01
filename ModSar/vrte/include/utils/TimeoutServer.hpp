//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file      TimeoutServer.hpp
/// @brief     Timeout Monitoring server
/// @copyright Robert Bosch GmbH  2018
/// @author    Arnaud Riess

#ifndef UTILS_TIMEOUTSERVER_HPP_INCLUDED
#define UTILS_TIMEOUTSERVER_HPP_INCLUDED

#include "log/Debug.hpp"
#include "utils/Expectations.hpp"
#include "utils/ITimeoutServer.hpp"
#include "utils/StdReturnType.hpp"
#include "utils/Thread.hpp"
#include "utils/Time.hpp"
#include "utils/Timeout.hpp"

#include <stdint.h>

namespace exm
{
namespace utils
{

/// @brief Time monitoring Sever
/// The template argument allows efficient deployment if few or many timeout elements are needed.
template <uint32_t MAX_TIMEOUTS>
class TimeoutServer : public ITimeoutServer,
                      public ITimeoutServices,
                      public ICondition,
                      public IThread
{
public:
    /// @brief Constructor
    /// @param  PollingTime_ polling time
    TimeoutServer(uint32_t PollingTime_)
        : ITimeoutServer()
        , ITimeoutServices()
        , ICondition()
        , IThread()
        , timeoutArray()
        , thread()
        , expectations()
        , next_free_timeout_object(0U)
        , PollingTime(PollingTime_)
        , isStarted(false)
        , cancelFlag(false)
    {
    }

    /// @brief Destructor
    virtual ~TimeoutServer()
    {
    } // Not covered: Only the deleting destructor is not covered. We don't use the heap.

    /// @brief copy constructor not needed
    TimeoutServer(const TimeoutServer&) = delete;

    /// @brief copy assignment not needed
    TimeoutServer& operator=(const TimeoutServer&) = delete;
 
    /// @brief Return a timeout object to monitor one timeout.
    /// @param[out] timeOut A timeout object.
    /// @return OK on success, INSUFFICIENT_RESOURCES if no more elements are available.
    virtual StdReturnType GetNew(ITimeout** timeOut)
    {
        StdReturnType ret = StdReturnType::OK;

        if (!isStarted) // Not covered: At least one monomorphisation is covering all branches.
        {
            log::Log(Severity::ERROR, "GetNew() - not started");
            ret = StdReturnType::GENERAL_ERROR;
        }
        else if (StdReturnType::OK != Lock()) // Not covered: At least one monomorphisation is
                                              // covering all branches.
        {
            log::Log(Severity::ERROR, "GetNew() - lock error");
            ret = StdReturnType::FATAL_ERROR;
        }
        else
        {
            if (next_free_timeout_object < MAX_TIMEOUTS)
            {
                ITimeoutController& ctrl = timeoutArray[next_free_timeout_object];
                ctrl.init(*this);

                *timeOut = &timeoutArray[next_free_timeout_object];
                next_free_timeout_object++;
            }
            else
            {
                log::Log(Severity::ERROR, "GetNew() - insufficient resources");
                ret = StdReturnType::INSUFFICIENT_RESOURCES;
            }

            if (StdReturnType::OK
                != Unlock()) // Not covered: This is pretty much impossible to cover in its current
                             // nature as failing to unlock marks the mutex as broken, but it is
                             // being used on the TimeoutServer thread, which deadlocks it, as the
                             // Mutex can never actually be unlocked again, but the condition
                             // variable there wants to acquire the lock again.
            {
                log::Log(Severity::ERROR, "GetNew() - lock error");
                ret = StdReturnType::FATAL_ERROR; // Not covered: This is pretty much impossible to
                                                  // cover in its current nature as failing to
                                                  // unlock marks the mutex as broken, but it is
                                                  // being used on the TimeoutServer thread, which
                                                  // deadlocks it, as the Mutex can never actually
                                                  // be unlocked again, but the condition variable
                                                  // there wants to acquire the lock again.
            }
        }

        return ret;
    }

    /// @brief Start the server.
    /// From here on, it can return new timeout objects and monitor timeouts.
    /// @return OK on success, GENERAL_ERROR if already started or thread creation failed.
    StdReturnType Start()
    {
        if (isStarted) // Not covered: At least one monomorphisation is covering all branches.
        {
            log::Log(Severity::ERROR, "Start() - already started");
            return StdReturnType::GENERAL_ERROR;
        }
        const char* thread_name = "EM_TimerOutServer";
        if (thread.create(*this, thread_name) != StdReturnType::OK)
        {
            log::Log(Severity::ERROR, "Start() - not possible to create threads");
            return StdReturnType::GENERAL_ERROR;
        }
        else
        {
            isStarted = true;
        }

        return StdReturnType::OK;
    }

    /// @brief Stop threads if running.
    /// @return OK on success, error if not started or something fails.
    StdReturnType Join()
    {
        StdReturnType ret = StdReturnType::OK;

        if (!isStarted)
        {
            log::Log(Severity::ERROR, "Join() - not started");
            ret = StdReturnType::GENERAL_ERROR;
        }
        else if (thread.join() != StdReturnType::OK) // Not covered: At least one monomorphisation
                                                     // is covering all branches.
        {
            ret = StdReturnType::GENERAL_ERROR;
        }
        else
        {
            isStarted = false;
        }

        return ret;
    }

    /// @brief Cancel operation.
    /// @return OK on success, error if not started or something fails.
    StdReturnType cancel()
    {
        StdReturnType ret = StdReturnType::OK;

        if (!isStarted)
        {
            log::Log(Severity::ERROR, "cancel() - not started");
            ret = StdReturnType::GENERAL_ERROR;
        }
        else
        {
            cancelFlag = true;
            ret = InterruptServer();
        }

        return ret;
    }

private:
    Timeout timeoutArray[MAX_TIMEOUTS]; ///< Array of timeout objects.
    Thread thread;                      ///< A thread to wait for timeouts.
    Expectations expectations;          ///< Mechanism to allow communication with the timeout thread.
    uint32_t next_free_timeout_object;  ///< Hold the current object count.
    const uint32_t PollingTime;         ///< A constant at which the timout thread wakes up the latest.
    bool isStarted;                     ///< Timeout Server is started
    bool cancelFlag;                    ///< Timeout Server is required to cancel

    /// @brief This method is executed in the timeout thread.
    virtual void routine()
    {
        while (!cancelFlag)
        {
            Time now;
            Time min_absolute_time(PollingTime);

            if (StdReturnType::OK != now.Now()) // Not covered: At least one monomorphisation is
                                                // covering all branches.
            {
                // TODO: Handle hard error.
                log::Log(Severity::ERROR, "Handle() - min_absolute_time.Now() failed");
                cancelFlag = true;
            }
            else
            {
                if (min_absolute_time.Accumulate(now) != StdReturnType::OK)
                {
                    // TODO: Handle hard error.
                    log::Log(Severity::ERROR, "Handle() - min_absolute_time.Accumulate() failed");
                    cancelFlag = true;
                }
                if (StdReturnType::OK
                    != CheckAllTimeouts(
                        now, min_absolute_time)) // Not covered: At least one monomorphisation is
                                                 // covering all branches.
                {
                    // TODO: Handle hard error.
                    log::Log(Severity::ERROR, "Handle() - while checking timeouts");
                    cancelFlag = true;
                }
                else
                {
                    WaitAndEval(min_absolute_time, cancelFlag);
                }
            }
        }

        cancelFlag = false;
    }

    /// @brief Waits/blocks for a given time and evaluates the unblocking causes
    /// @param[in] time Time to wait
    /// @param[in/out] cancel Flag for cancelation
    void WaitAndEval(Time& time, bool& cancel)
    {
        // A time in the past will unblock immediately.
        StdReturnType rv = expectations.StartWaiting(time, this);

        if (StdReturnType::OK == rv)
        {
            // We got interrupted.
            // All timeouts will be checked and re-evaluated when we re-enter the loop.
            if (StdReturnType::OK
                != expectations.IncrementExpectationsBy(
                    1)) // Not covered: At least one monomorphisation is covering
                            // all branches.
            {
                // TODO: Handle hard error.
                log::Log(Severity::ERROR, 
                    "Handle() - expectations.IncrementExpectationsBy(1) failed");
                cancel = true;
            }
        }
        else if (StdReturnType::TIMEOUT == rv) // Not covered: At least one
                                                // monomorphisation is covering all
                                                // branches.
        {
            // Nothing to do here.
            // All timeouts will be checked when we re-enter the loop.
        }
        else
        {
            // TODO: Handle hard error.
            log::Log(Severity::ERROR, "Handle() - expectations.StartWaiting() failed");
            cancel = true;
        }
    }

    /// @brief Iterate over all timeout element, and check if one needs to fire.
    /// In addition, find the new minimum absolute time on which to fire.
    /// @param[in]    now               The current time
    /// @param[inout] min_absolute_time The new minimum absolute time.
    /// @return OK on success, GENERAL_ERROR on failure.
    StdReturnType CheckAllTimeouts(const Time& now, Time& min_absolute_time)
    {
        StdReturnType ret = StdReturnType::OK;

        for (uint32_t i = 0U; i < next_free_timeout_object;
             i++) // Not covered: At least one monomorphisation is covering all branches.
        {
            ITimeoutController& ctrl = timeoutArray[i];

            // Check if this timeout needs to fire and return the next minimum time until target
            // time
            if (StdReturnType::OK
                != ctrl.Check(now, min_absolute_time)) // Not covered: At least one monomorphisation
                                                       // is covering all branches.
            {
                ret = StdReturnType::GENERAL_ERROR;
            }
        }

        return ret;
    }

    /// @brief Implementation of ITImeoutServices interface method.
    /// @return OK on success, or FATAL_ERROR in such a case.
    virtual StdReturnType InterruptServer() { return expectations.SignalOneCall(); }

    /// @brief Implementation of ITImeoutServices interface method.
    /// @return OK on success, or FATAL_ERROR in such a case.
    virtual StdReturnType Lock() { return expectations.Lock(); }

    /// @brief Implementation of ITImeoutServices interface method.
    /// @return OK on success, or FATAL_ERROR in such a case.
    virtual StdReturnType Unlock() { return expectations.Unlock(); }

    /// @brief Implementation of the ICondition method.
    /// See interface definition for details.
    /// @param[in] count Current expectation count.
    /// @return true if count<0, i.e. one or more interruption signals were sent.
    virtual bool Fullfilled(int32_t count) { return (count < 0); }
}; /* class TimeoutServer */
} /* namespace utils */
} /* namespace exm */
#endif
