//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018-2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================
//
/// @file      libs/common/include/bosch/vrte/stm/timeoutthread.hpp
/// @brief     Timeout thread class header.
/// @copyright Robert Bosch GmbH 2018-2021
/// @author    VRTE StM Team
//
//=============================================================================

#ifndef BOSCH_VRTE_STM_TIMEOUTTHREAD_HPP_INCLUDED
#define BOSCH_VRTE_STM_TIMEOUTTHREAD_HPP_INCLUDED

#include "bosch/vrte/stm/thread.hpp"

#include <atomic>
#include <chrono>
#include <condition_variable>
#include <functional>
#include <mutex>

namespace bosch
{
namespace vrte
{
namespace stm
{

/// @brief Generic timeout thread handling.
///
/// Use this class in order to start an abortable timeout thread.
class CTimeoutThread
{
public:
    /// @brief Constructor
    ///
    /// @param f_ref    Reference for thread configuration.
    /// @param f_name   Thread name.
    CTimeoutThread(const std::string& f_ref, const std::string& f_name);

    /// @brief Destructor
    ~CTimeoutThread();

    /// @brief Start timeout.
    ///
    /// @param f_timeout    Timeout interval.
    /// @param f_callback   Callback to be called in case of a timeout.
    /// @return             false if the thread could not be started.
    bool start(std::chrono::milliseconds f_timeout, std::function<void()> f_callback);

    /// @brief Abort timeout.
    ///
    /// When a timeout thread is aborted the callback will not be called.
    void abort();

private:
    /// @brief Timeout thread.
    ///
    /// @param f_timeout    Timeout interval.
    /// @param f_callback   Callback to be called in case of a timeout.
    void thread(std::chrono::milliseconds f_timeout, std::function<void()> f_callback);

    std::string             m_name;
    CThread                 m_thread;
    std::condition_variable m_condition;
    std::mutex              m_mutex;

    // Flag indicating that the timeout thread shall be aborted.
    // Is used together with m_mutex and m_condition-
    bool m_aborted = false;

    // Flag indicating whether the thread is currently stopped or about to end.
    std::atomic<bool> m_stopped;
};

}  // namespace stm
}  // namespace vrte
}  // namespace bosch

#endif  // BOSCH_VRTE_STM_TIMEOUTTHREAD_HPP_INCLUDED
