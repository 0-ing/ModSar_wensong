//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
/// @copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================
/// @file      Expectations.hpp
/// @brief     Declaration/Definition of Expectations
/// @author    baetz
//=============================================================================
#ifndef EXPECTATIONS_HPP_INCLUDED
#define EXPECTATIONS_HPP_INCLUDED

#include "log/Debug.hpp"
#include "utils/Mutex.hpp"
#include "utils/StdReturnType.hpp"
#include "utils/Time.hpp"

#include "utils/c/errno.hpp" //wrapper to prevent direct inclusion of libc headers

#include <pthread.h>
#include <stdint.h>

namespace exm
{
namespace utils
{
/// @brief Condition instance for condition to wait on
class ICondition
{
public:
    /// @brief Default destructor
    virtual ~ICondition() {} // Not covered: Deleting destructors of pure virtual base classes can not be called.
    /// @brief Default constructor
    ICondition() {}
    /// @brief Helper to check condition.
    /// @param count number of expectations remaining unfulfilled.
    /// @return true if the expactation is fulfilled
    virtual bool Fullfilled(int32_t count) = 0;
};

/// @brief Class to support thread synchronization.
/// The class allows setting a number of expectations with #IncrementExpectationsBy
/// and asynchronously fulfilling them with #SignalOneCall.
/// By calling StartWaiting, the calling thread blocks until the expectation is met.
/// Note: the timing mechanism are implemented using the CLOCK_MONOTONIC.
class Expectations : public Mutex, public ICondition
{
public:
    /// @brief Default constructor
    Expectations();

    /// @brief Destructor
    virtual ~Expectations();

    /// @brief copy constructor not needed
    Expectations(const Expectations& ) = delete;

    /// @brief copy assignment operator not needed
    Expectations& operator=(const Expectations& ) = delete;

    /// @brief Call to set expectations.
    /// @param amount Number of expected calls.
    /// @return OK if success
    virtual StdReturnType IncrementExpectationsBy(const int16_t amount);

    /// @brief Signal a single fulfilled expectation.
    /// @return OK if success
    virtual StdReturnType SignalOneCall();

    /// @brief Broadcast a single fulfilled expectation.
    /// @return OK if success
    virtual StdReturnType BroadcastOneCall();

    /// @brief Starts synchronizing for expectations.
    /// The calling thread blocks until as many #SignalOneCall or #BroadcastOneCall calls were
    /// made as expectations were set with #IncrementExpectationsBy.
    /// @param ms_relative_timeout Relative timeout value for waiting for the expectation.
    /// @param condition Condition to wait on. This is an optional parameter. If set to nullptr, then the default condition (counter==0) will be used.
    /// @return OK if success, TIMEOUT if the timeout value overruns. Any other value is a fatal error.
    virtual StdReturnType StartWaiting(const uint32_t ms_relative_timeout, ICondition* const condition);

    /// @brief Starts synchronizing for expectations.
    /// The calling thread blocks until as many #SignalOneCall or #BroadcastOneCall calls were
    /// made as expectations were set with #IncrementExpectationsBy.
    /// @param AbsTimeout Absolute timeout value for waiting for the expectation.
    /// @param condition Condition to wait on. This is an optional parameter. If set to nullptr, then the default condition (counter==0) will be used.
    /// @return OK if success, TIMEOUT if the timeout value overruns. Any other value is a fatal error.
    virtual StdReturnType StartWaiting(const Time& AbsTimeout, ICondition* const condition);

private:
    /// @brief Helper to check condition.
    /// @param count number of expectations remaining unfulfilled.
    /// @return true if the expactation is fulfilled
    virtual bool Fullfilled(const int32_t count);

    pthread_cond_t cond;      ///< Condition variable for synchronization.
    int32_t nrOfExpectations; ///< Current amount of expectations.
    bool wasCreated;          ///< Set to true, if the Expectations object was created correctly.

    /// @brief Starts synchronizing for expectations internal function.
    StdReturnType StartWaitingInternal(const Time& AbsTimeout, ICondition* condition);

    int32_t set_condattr(pthread_condattr_t& condattr);
};

}
}
#endif
