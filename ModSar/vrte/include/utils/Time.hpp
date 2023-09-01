//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
/// @copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================
/// @file      Time.hpp
/// @brief     Declaration/Definition of Expectations
/// @author    Arnaud Riess
//=============================================================================
#ifndef TIME_HPP_INCLUDED
#define TIME_HPP_INCLUDED

#include <stdint.h>

#include "utils/c/time.hpp" //wrapper to prevent direct inclusion of libc headers

#include "utils/StdReturnType.hpp"

namespace exm
{

namespace utils
{

/// @brief Provides some abstraction to the Posix timespec structure
class Time
{
public:
    /// @brief Constructor
    Time();

    /// @brief Destructor
    ~Time();

    /// @brief  copy constructor not needed
    Time(const Time&) = delete;

    /// @brief Copy assignment operator 
    Time& operator=(const Time& other);

    /// @brief Constructor, note that it is only possible to initialze it with 32 bits, so that we
    /// never reach the max value.
    /// @param ms_time : Initialization value, in ms
    Time(const uint32_t ms_time);

    /// @brief Initializes this ibject with the current time, using the Posix CLOCK_MONOTONIC clock.
    /// @return OK for success
    StdReturnType Now();

    /// @brief Sleeps for a relative time
    /// @return OK for success
    StdReturnType RelativeSleep() const;

    /// @brief Accumulate some time to the current stored value
    /// @param other_ms_time : Time to be accumulated, in ms
    StdReturnType Accumulate(const uint64_t other_ms_time);

    /// @brief Set the current time
    /// @param new_ms_time : Time to be set, in ms
    StdReturnType Set(const uint64_t new_ms_time);

    /// @brief Accumulate some time to the current stored value
    /// @param other : time to be accumulated
    StdReturnType Accumulate(Time& other);

    /// @brief Checks if this time is greater or equal than another time
    /// @param other : Other time object to compare with
    /// @return bool True if this is greater or equal than the other time
    bool GreaterOrEqualThan(Time& other) const;

    /// @brief Get the Posix timespec structure
    /// @return Reference to a 'struct timespec'
    void getTimespec(struct timespec& spec) const;

    /// @brief Get current time in ms
    /// @return The current time in ms
    uint64_t getMs() const;

    /// @brief Get current time in us
    /// @return The current time in us
    uint64_t getUs() const;

    /// @brief Get the min between two Time objects
    /// @param[in,out] that first time to compare
    /// @param[in] other second time to compare
    static void Min(Time& that, const Time& other);

    // This over 500000 years
    static constexpr uint64_t MSEC_MAX = UINT64_MAX / 1000U;
    static constexpr uint64_t USEC_MAX = MSEC_MAX * 1000U;

private:
    StdReturnType AccumulateUs(const uint64_t other_us_time);
    uint64_t usec;
};
}
}
#endif
