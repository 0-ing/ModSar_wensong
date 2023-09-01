//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
/// @copyright (c) 2019 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================
/// @file         MutexGuard.hpp
/// @brief        MutexGuard utility provides simplified interfaces for locking mechanisms.
/// @author       Yohan Pistor

#ifndef MUTEXGUARD_HPP_INCLUDED
#define MUTEXGUARD_HPP_INCLUDED

#include "utils/IMutex.hpp"
#include "utils/StdReturnType.hpp"

/// @brief LOCK macro provides a simplified way to use MutexGuard utility.
/// It tries to lock the provided mutex. In case of a failing lock it prints out a debug message
/// and returns the function with the given return value.
/// @param mutex Reference to Mutex variable.
/// @param msg Debug message to be printed out in case of a failing lock.
/// @param ret Return value of the calling function in case of a failing lock.
#define LOCK(mutex, msg, ret)                             /* PRQA S 1020 # This atomically */      \
    const utils::MutexGuard mguard(mutex);                /* creates the guard and checks for an */\
    if (mguard.GetMutexReturnType() != StdReturnType::OK) /* error. This is useful enough to */    \
    {                                                     /* keep. */                              \
        log::Log(Severity::ERROR ,msg);                                                            \
        return ret;                                                                                \
    }

/// @brief LOCK_REPORT macro provides a simplified way to use MutexGuard utility.
/// It tries to lock the provided mutex. In case of a failing lock it reports a criticalerror,
/// prints out a debug message and returns the function with the given return value.
/// @param mutex Reference to Mutex variable.
/// @param criticalerror Reference to the critical error interface.
/// @param ret Return value of the calling function in case of a failing lock.
/// @param msg Debug message to be printed out in case of a failing lock.
#define LOCK_REPORT(mutex, criticalerror, ret, msg, ...)  /* PRQA S 1020 # This atomically */      \
    const utils::MutexGuard mguard(mutex);                /* creates the guard and checks for an */\
    if (mguard.GetMutexReturnType() != StdReturnType::OK) /* error. This is useful enough to */    \
    {                                                     /* keep. */                              \
        log::Log(Severity::ERROR ,msg, ##__VA_ARGS__);                                             \
        (criticalerror).report(rep::ICriticalError::CriticalError::MUTEX_ERROR);                   \
        return ret;                                                                                \
    }

namespace exm
{
    namespace utils
    {
        /// @brief  MutexGuard utility class
        /// A MutexGuard can be used to automatically lock a Mutex on instantiation of a MutexGuard.
        /// Once the MutexGuard goes out of scope the Mutex gets automatically unlocked.
        class MutexGuard
        {
            public:
                /// @brief Default constructor not provided to avoid mistaken usage of MutexGuard
                MutexGuard() = delete;

                /// @brief Constructor
                /// Constructor automatically locks the Mutex and stores the result of it.
                /// @param mutex_ Interface to Mutex
                explicit MutexGuard(IMutex& mutex_)
                : mutex(mutex_)
                , m_returntype(mutex.Lock()) // Try to lock the mutex
                { }

                /// @brief Destructor
                ///
                /// Mutex is unlocked automatically inside the destructor.
                ~MutexGuard()
                {
                    /// If Mutex is currently locked
                    if(m_returntype == StdReturnType::OK)
                    {
                        /// Try to unlock the Mutex
                        m_returntype = mutex.Unlock();
                    }
                }

                /// @brief Prevent copy construction
                /// @private
                MutexGuard(const MutexGuard &other) = delete;
                /// @brief Prevent copy assignment
                /// @private
                MutexGuard& operator=(const MutexGuard& other) = delete;

                /// @brief  Get the Mutex return type
                /// @return StdReturnType Mutex return type

                StdReturnType GetMutexReturnType() const
                {
                    /// Return mutex return type
                    return m_returntype;
                }

            private:
                IMutex& mutex;                      /// Interface to Mutex
                StdReturnType m_returntype;         /// Return type of Mutex
        };
    }
}

#endif // MUTEXGUARD_HPP_INCLUDED
