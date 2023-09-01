//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
/// @copyright (c) 2020 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================
/// @file         Thread.hpp
/// @brief        Thread API provides a simplified interface to create threads.
/// @author       crg2fe


#ifndef VRTE_EXM_THREAD_HPP_INCLUDED
#define VRTE_EXM_THREAD_HPP_INCLUDED

#include <pthread.h>

#ifdef __QNX__
#include <sys/neutrino.h>
#include <sys/syspage.h>
#else // Linux
#include <unistd.h>
#endif // __QNX__

#include <new>

#include "bosch/vrte/exm/ThreadAttr.hpp"
#include "utils/type_traits.hpp"
#include "utils/memory.hpp"
#include "utils/StdReturnType.hpp"
#include "utils/Try.hpp"
#include "utils/Types.hpp"
#include "utils/c/errno.hpp"

/* Portability macros */
#ifdef __QNX__
#define VRTE_EXM_THREAD_NAME_MAX _NTO_THREAD_NAME_MAX
#define VRTE_EXM_NUM_CPU (_syspage_ptr->num_cpu)
#else // Linux
#define VRTE_EXM_THREAD_NAME_MAX 16 // equals TASK_COMM_LEN used in pthread_setname_np. It is defined in linux/sched.h, but not exported
#define VRTE_EXM_NUM_CPU (sysconf(_SC_NPROCESSORS_ONLN))
#endif // __QNX__


/*

IMPLEMENTATION NOTES:

The class Thread contains various constructors, which all create a lambda appropriate for the input
arguments, construct a wrapper around it and keep a reference to the wrapper via the ICallable interface.
The wrapper reference is then used to call the appropriate start function for the thread and deallocate
resources afterwards.

ICallable provides an interface for type erasure of the lambda, which is required for the following reasons:

Virtual operator():
Call interface for the function PThreadStartFunction, which is to be declared as extern "C"
to fully comply with the linkage reuqirement towards the Posix C API.

Virtual destructor:
Interface for the Thread class to deallocate the lambda properly. Since lambda types are anonymuous,
Thread cannot directly store a pointer to the appropriate type.


We could improve this situation a little by not using lambdas for the parameter binding, but this would
only remove the virtual destructor and not the other restriction due to the extern "C" constraint.

*/

namespace bosch
{
namespace vrte
{
namespace exm
{

using ThreadName = ::exm::utils::String<VRTE_EXM_THREAD_NAME_MAX>;

extern "C"
{
/// @brief Wrapper with correct function signature required for pthread_create
void* PThreadStartRoutine(void* dptr);
}


/// @brief Interface to make any object callable
class ICallable
{
    public:
        virtual ~ICallable() {} // Not covered: Deleting destructors of pure virtual base classes can not be called.
        virtual void operator()() = 0;
};


/// @brief Wrapper class to make a lambda callable without knowing its specific type
template<typename Lambda>
class LambdaWrapper : public ICallable
{
    public:
        /// @brief No default constructor (construction must happen with a specified lambda)
        LambdaWrapper() = delete;

        /// @brief Constructor for a given pointer to a lambda
        LambdaWrapper(Lambda* lam) : lambda(lam) { }

        /// @brief LambdaWrapper is neither copyable nor movable
        LambdaWrapper(const LambdaWrapper& t) = delete;
        LambdaWrapper(LambdaWrapper&& t) = delete;
        LambdaWrapper& operator=(const LambdaWrapper&) = delete;
        LambdaWrapper& operator=(LambdaWrapper&&) = delete;

        /// @brief Destroy the underlying lambda
        ~LambdaWrapper() override
// Example to instruct LCOV to ignore branch coverage
// LCOV_EXCL_BR_START
        {
            lambda->~Lambda(); // Not covered: Deleting destructors of pure virtual base classes can not be called
        }
// LCOV_EXCL_BR_STOP

        /// @brief Invoke the lambda
        void operator()() override
        {
            (*lambda)();
        }

    private:
        Lambda* lambda; ///< Pointer to managed lambda object
};


/// @brief ThreadCallable class creates objects which call functions with captured parameters 
class ThreadCallable
{
    public:
        /// @brief No default constructor
        ThreadCallable() = delete;

        /// @brief Constructor for creating a ThreadCallable from a lambda or function pointer
        template<typename Function, typename ...Args>
        ThreadCallable(ThreadName* thrName, Function&& fnc, Args&&... args) : callable(), lambdaStorage(), threadName(thrName) 
        {
            auto lambda = new (&lambdaStorage) auto([fnc, args...]() mutable { (void)fnc(args...); }); // Not covered: GCC inserts unreachable code for placement new nullptr check
            using Lambda = ::exm::utils::RemovePointer_t<decltype(lambda)>;
            static_assert(sizeof(Lambda) <= LAMBDA_STORAGE_SIZE, "Memory reserved to capture thread function parameters must be sufficient.");

            callable.reset<LambdaWrapper<Lambda>>(lambda);
        }

        /// @brief Constructor for creating a ThreadCallable from a member function pointer
        template<typename Return, typename Class, typename ...Args, typename ...Any>
        ThreadCallable(ThreadName* thrName, Return (Class::*method)(Any...), Class* obj, Args&&... args) : callable(), lambdaStorage(), threadName(thrName)
        {
            auto lambda = new (&lambdaStorage) auto([method, obj, args...]() mutable { (void)(obj->*method)(args...); }); // Not covered: GCC inserts unreachable code for placement new nullptr check
            using Lambda = ::exm::utils::RemovePointer_t<decltype(lambda)>;
            static_assert(sizeof(Lambda) <= LAMBDA_STORAGE_SIZE, "Memory reserved to capture thread function parameters must be sufficient.");

            callable.reset<LambdaWrapper<Lambda>>(lambda);
        }

        /// @brief ThreadCallable is neither copyable nor movable
        ThreadCallable(const ThreadCallable& t) = delete;
        ThreadCallable(ThreadCallable&& t) = delete;
        ThreadCallable& operator=(const ThreadCallable&) = delete;
        ThreadCallable& operator=(ThreadCallable&&) = delete;

        /// @brief ThreadCallable can use the default destructor
        ~ThreadCallable() = default;

        /// @brief Execution of the thread function
        void operator()()
        {
            pthread_t id = pthread_self();

            // No check of retval needed, as thread name string length is programmed to always be within bounds
            (void)pthread_setname_np(id, threadName->AsStr());

            // Call the thread function
            (*callable)();
        }

    private:
        ::exm::utils::placed_ptr<ICallable, sizeof(LambdaWrapper<void()>), alignof(LambdaWrapper<void()>)> callable; ///< LambdaWrapper object
        static constexpr size_t LAMBDA_STORAGE_SIZE = 128U;  ///< No. of storage bytes reserved for the lambda object
        ::exm::utils::AlignedStorage_t<LAMBDA_STORAGE_SIZE> lambdaStorage;  ///< Storage for the lambda object
        ThreadName* threadName; ///< Pointer to thread name string, required to set the thread name upon start of the thread
};


/// @brief Thread class for thread creation via posix pthreads
/// HINT: Functions with variable references as inputs cannot be used as threads. 
/// Reference input arguments could be wrapped with a function like std::ref, though.
class Thread
{
    public:
        /// @brief No default constructor (construction shall lead to immediate thread creation)
        Thread() = delete;

        /// @brief Constructor for creating a thread with thread attribute reference & name suffix
        template<typename Function, typename ...Args>
        Thread(const char* threadAttrRef, const char* threadNameSuffix, Function&& fnc, Args&&... args) : 
            Thread(static_cast<uint32_t>(VRTE_EXM_NUM_CPU),
            threadAttrRef,
            threadNameSuffix,
            static_cast<Function&&>(fnc),
            static_cast<Args&&>(args)...)
        {
        }

        /// @brief Thread is neither copyable nor movable
        Thread(const Thread& t) = delete;
        Thread(Thread&& t) = delete;
        Thread& operator=(const Thread&) = delete;
        Thread& operator=(Thread&&) = delete;

        /// @brief Check the error state
        ::exm::StdReturnType assertion()
        {
            return errorState;
        }

        /// @brief Blocking wait until the thread is finished
        ::exm::StdReturnType join()
        {
            TRY(errorState);
            if(pthread_join(id, nullptr) == 0)
            {
                errorState = ::exm::StdReturnType::INVALID_STATE;
                return ::exm::StdReturnType::OK;
            }
            else
            {
                errorState = ::exm::StdReturnType::GENERAL_ERROR;
                return errorState;
            }
        }
        /// @brief Get a pointer to the ThreadAttr object associated with the Thread
        const ThreadAttr* getThreadAttr() const
        {
            return (threadAttr.get());
        }

        /// @brief Get a pointer to the ThreadName object associated with the Thread
        const ThreadName* getThreadName() const
        {
            return (&threadName);
        }

        /// @brief Join the thread on destruction
        ~Thread()
        {
            (void)join();
        }

    private:
        /// @brief Internal constructor for creating the thread with check for number of CPUs
        template<typename Function, typename ...Args>
        Thread(uint32_t numCpu, const char* threadAttrRef, const char* threadNameSuffix, Function&& fnc, Args&&... args) : 
            id(-1),
            errorState(::exm::StdReturnType::GENERAL_ERROR),
            threadCallable(),
            threadAttr(),
            threadName()
        {
#ifdef __QNX__
            if (RMSK_SIZE(numCpu) == 1)
#else
            if ( true ) // The runmask is currently not set for linux.
#endif // __QNX__
            {
                threadAttr.reset(threadAttrRef);
                errorState = threadAttr->assertion();
                
                // If the attributes are defined properly, then use them
                if (errorState == ::exm::StdReturnType::OK || errorState == ::exm::StdReturnType::NOT_APPLICABLE)
                {
                    // Assemble the name string for the thread
                    errorState = setThreadName(threadNameSuffix);
                    if (errorState == ::exm::StdReturnType::OK)
                    {
                        int err = 0;
#ifdef __QNX__
                        // Prepare the inherit runmask for the new thread, it is used by QNX during pthread_create to set the runmask of the created thread.
                        // Hint: Below code only works for up to 32 CPUs, but that should be sufficient for our use case.
                        // For more information check: http://www.qnx.com/developers/docs/7.0.0/#com.qnx.doc.neutrino.lib_ref/topic/t/threadctl.html#threadctl___NTO_TCTL_RUNMASK_GET_AND_SET_INHERIT
                        ThreadRunmask runmask = {1, 0U, 0U};
                        if (threadAttr->getThreadRunmask() != nullptr)
                        {
                            runmask.inherit_mask[0U] = *threadAttr->getThreadRunmask();
                        }
                        
                        err = ThreadCtl_r(_NTO_TCTL_RUNMASK_GET_AND_SET_INHERIT, reinterpret_cast<void*>(&runmask));
#endif // __QNX__
                        // Only create the thread, if the inherit runmask was set properly
                        if (err == 0)
                        {
                            threadCallable.reset(&threadName, static_cast<Function&&>(fnc), static_cast<Args&&>(args)...);
                            (void)processPThreadRetVal(pthread_create(&id, threadAttr->getPthreadAttr(), PThreadStartRoutine, threadCallable.getRaw()));
#ifdef __QNX__
                            // Reset the inherit runmask
                            err = ThreadCtl_r(_NTO_TCTL_RUNMASK_GET_AND_SET_INHERIT, reinterpret_cast<void*>(&runmask));
#else
                            err = ENOTSUP;
#endif // __QNX__
                        }
                        // If the first runmask manipulation already failed, save an error state to prevent joining the not created thread later
                        else
                        {
                            errorState = ::exm::StdReturnType::GENERAL_ERROR;
                        }
                        
                        // Report any runmask manipulation errors, this should never happen
                        if (err != 0)
                        {
#ifdef __QNX__
                            ::exm::log::Log(::exm::Severity::ERROR, "Thread runmask could not be set, CPU affinity is inconsistent");
#else
                            ::exm::log::Log(::exm::Severity::WARN, "Thread runmask could not be set, CPU affinity is inconsistent");
#endif
                        }
                    }
                    else
                    {
                        ::exm::log::Log(::exm::Severity::ERROR, "Thread name too long or no suffix given, thread is not created");
                    }
                }
                // For other cases don't create the thread
                else
                {
                    ::exm::log::Log(::exm::Severity::ERROR, "Invalid ThreadAttr, thread is not created");
                }
            }
            else
            {
                ::exm::log::Log(::exm::Severity::ERROR, "Can only create threads on systems with up to 'size of int' cores");
            }
        }

        /// @brief Setting of the thread name consisting of prefix and suffix
        ::exm::StdReturnType setThreadName(const char* threadNameSuffix)
        {
            if (threadAttr->getThreadNamePrefix() != nullptr)
            {
                TRY(threadName.TrySetStr(*threadAttr->getThreadNamePrefix()));
            }
            TRY(threadName.TryAppendChar('/'));
            TRY(threadName.TryAppendStr(threadNameSuffix));
            return ::exm::StdReturnType::OK;
        }

        /// @brief Return value processing of the pthread calls within Thread class
        ::exm::StdReturnType processPThreadRetVal(::exm::Integer err)
        {
            ::exm::StdReturnType rv = ::exm::StdReturnType::GENERAL_ERROR;
            if (err == 0)
            {
                rv = ::exm::StdReturnType::OK;
            }
            errorState = rv;
            return errorState;
        }

        pthread_t id;   ///< Id assigned by the pthread api
        ::exm::StdReturnType errorState;   ///< Current error state, reflecting possible errors from pthread API
        ::exm::utils::placed_ptr<ThreadCallable> threadCallable;   ///< pointer with placement storage for ThreadCallable
        ::exm::utils::placed_ptr<ThreadAttr> threadAttr; ///< ThreadAttr object associated with the Thread
        ThreadName threadName; ///< Thread name, constructed as '<prefix>/<suffix>'

        using ThreadRunmask = struct ///< Internal type used for manipulating the QNX inherit mask
        {
            ::exm::Integer size;
            ::exm::UnsignedInt runmask[1U];
            ::exm::UnsignedInt inherit_mask[1U];
        };
};


} // namespace bosch
} // namespace vrte
} // namespace exm


#endif // VRTE_EXM_THREAD_HPP_INCLUDED
