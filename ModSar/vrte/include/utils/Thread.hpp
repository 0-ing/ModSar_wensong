//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
/// @copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================
/// @file         Thread.hpp
/// @brief        Thread utility provides simplified interfaces to create threads.
/// @author

#ifndef UTILS_THREAD_HPP_INCLUDED
#define UTILS_THREAD_HPP_INCLUDED

#include <pthread.h>

#include "utils/StdReturnType.hpp"

namespace exm
{
namespace utils
{

/// @brief Interface class for the thread routine
class IThread
{
public:
    /// @brief Interface method for the thread main routine. This needs to be provided by the user of the Thread class.
    virtual void routine() = 0;
    virtual ~IThread() {}
};

/// @brief    Thread Utility class
///
/// Supports thread creation.
/// Methods are not thread safe, so please don't try to e.g. call create()
/// on a single Thread object from multiple concurrent threads.
/// It is recommended to join the thread before destruction by using the join() method.
/// If the thread runs in a loop, e.g. a shared cancelLoop boolean can be used to finish
/// the thread before joining.
class Thread
{
public:
    /// @brief Constructor
    Thread();

    /// @brief Destructor
    ///
    /// Will cancel the thread, but only if it was created and is still running.
    virtual ~Thread();

    /// @brief  copy construction not needed
    /// @private
    Thread(const Thread&) = delete;

    /// @brief  copy assignment not needed
    /// @private
    Thread& operator=(const Thread&) = delete;

    /// @brief Creates a thread
    ///
    /// @param      start_routine Reference to object implementing IThread
    /// @param      name name of thread
    /// @return     OK on success, GENERAL_ERROR on failure.
    StdReturnType create(IThread& start_routine, const char* name);

    /// @brief join thread
    ///
    /// @return OK on success, GENERAL_ERROR on failure.
    StdReturnType join();

    /// @brief cancel thread
    ///
    /// @return OK on success, GENERAL_ERROR on failure.
    StdReturnType cancel();

private:
    pthread_t pthread;  ///< Thread ID
    bool threadRunning; ///< flag set on thread creation, reset on termination
};
}
}

#endif // UTILS_THREAD_HPP_INCLUDED
