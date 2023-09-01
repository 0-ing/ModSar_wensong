#ifndef PIPC_UTILS_TIME_SPEC_HPP
#define PIPC_UTILS_TIME_SPEC_HPP

#include <chrono>
#include <stdint.h>
#include <time.h>

namespace pipc
{
namespace utils
{
/**
 * @brief Wrapper for a posix timespec.
 *
 * This class provides a user-friendly interface
 * for using timespec structs and setting some time with them.
 *
 * @todo
 * Properly support all std::chrono types.
 */
class TimeSpec
{
public:
    /** @brief Constructor with optional initialization to the currrent time. */
    inline TimeSpec(bool initCurrentTime = true)
    {
        if (initCurrentTime)
        {
            setCurrentTime();
        }
    }

    /** @brief Set the timespec to the current time. */
    inline void setCurrentTime()
    {
        clock_gettime(CLOCK_REALTIME, &time_);
    }

    /** @brief Get the posix timespec struct. */
    inline const timespec& get() const
    {
        return time_;
    }

    /** @brief Increment the time by x seconds. */
    void incr(std::chrono::seconds seconds)
    {
        time_.tv_sec += seconds.count();
    }

    /** @brief Increment the time by x milliseconds. */
    void incr(std::chrono::milliseconds milliseconds)
    {
        time_.tv_nsec += milliseconds.count() * 1000000;
        // Go over a loop in case we have set more than 1 second
        while (time_.tv_nsec >= 1000000000)
        {
            time_.tv_sec += 1;
            time_.tv_nsec -= 1000000000;
        }
    }

private:
    struct timespec time_;
};

} // namespace utils
} // namespace pipc

#endif // PIPC_UTILS_TIME_SPEC_HPP
