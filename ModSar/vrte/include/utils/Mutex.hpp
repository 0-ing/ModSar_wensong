//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
/// @copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

///  @file      Mutex.hpp
///  @brief     Mutex Header
///  @author    Christopher Schwager

#ifndef MUTEX_HPP_INCLUDED
#define MUTEX_HPP_INCLUDED

#include "utils/IMutex.hpp"
#include <pthread.h>
#include <stdint.h>

namespace exm
{
namespace utils
{
/// @class    Mutex
/// @brief    Wrapper class for pthread mutexes
///
///           This class wraparound pthread mutex and ensures that it is initialized to PTHREAD_MUTEX_NORMAL type.
///           Explicit initialization of the mutex object ensures correct behaviour across different OSs.
///           Please note that the static PTHREAD_MUTEX_INITIALIZER will not be used as is not portable across OSs.
///           This is due to the fact that POSIX says:
///           1) PTHREAD_MUTEX_INITIALIZER is equivalent to pthread_mutex_init(&mutex_name, NULL)
///             - http://pubs.opengroup.org/onlinepubs/9699919799/functions/pthread_mutex_init.html
///           2) If pthread_mutex_init() gets NULL attr then the default mutex attributes are used
///             - http://pubs.opengroup.org/onlinepubs/9699919799/functions/pthread_mutex_init.html
///           3) The default value of the type attribute is PTHREAD_MUTEX_DEFAUL
///             - http://pubs.opengroup.org/onlinepubs/9699919799/functions/pthread_mutexattr_settype.html
///           4) An implementation may map PTHREAD_MUTEX_DEFAULT to one of the other mutex types --> i.e. it is not specified
///              what this is!
///             - http://pubs.opengroup.org/onlinepubs/9699919799/functions/pthread_mutexattr_settype.html
class Mutex : public IMutex
{
public:
    /// Default Constructor initializes mutex to PTHREAD_MUTEX_NORMAL type.
    Mutex();

    /// Destructor destroys mutex.
    virtual ~Mutex();

    /// @brief copy constructor not needed
    Mutex(const Mutex&) = delete;

    /// @brief copy assignment operator not needed
    Mutex& operator=(const Mutex&) = delete;

    /// Lock the Mutex
    ///
    /// @return StdReturnType
    /// @retval  OK = success
    /// @retval  GENERAL_ERROR = failed
    virtual StdReturnType Lock() override;

    /// Try to lock the Mutex
    /// Returns an error if mutex is already locked.
    ///
    /// @return StdReturnType
    /// @retval  OK = success
    /// @retval  GENERAL_ERROR = failed
    /// @retval  INVALID_STATE = mutex is already locked
    virtual StdReturnType TryLock() override;

    /// Unlock the Mutex
    ///
    /// @return StdReturnType
    /// @retval  OK = success
    /// @retval  GENERAL_ERROR = failed
    virtual StdReturnType Unlock() override;

protected:
    /// @brief   Pthread mutex
    pthread_mutex_t pmutex;

private:
    /// flag that marks if mutex is operational
    bool working_object;
};

} /* namespace fgm */
} /* namespace exm */

#endif
