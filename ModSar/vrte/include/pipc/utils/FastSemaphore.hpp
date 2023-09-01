#ifndef PIPC_UTILS_FAST_SEMAPHORE_HPP
#define PIPC_UTILS_FAST_SEMAPHORE_HPP

#include "Semaphore.hpp"

#include <atomic>

namespace pipc
{
namespace utils
{
/** @brief Fast Semaphore.
 *
 * Optimized version of a semaphore with atomic fetch_x operations.
 * Only enters the posix call in case the semaphore is contested.
 *
 * @todo
 * Very high potential for faster semaphore handling, but if we want to use it
 * in shared space we also need a protection of cnt_.
 */
class FastSemaphore
{
public:
    FastSemaphore(unsigned int value, bool shared) : semaphore_(0, shared), count_(value)
    {
    }

    void wait()
    {
        int count = count_.fetch_sub(1, std::memory_order_relaxed);
        // Check if we have to go sleep
        if (count < 1)
        {
            semaphore_.wait();
        }
        std::atomic_thread_fence(std::memory_order_acquire);
    }

    void post()
    {
        std::atomic_thread_fence(std::memory_order_release);
        int count = count_.fetch_add(1, std::memory_order_relaxed);
        // Check if someone is sleeping
        if (count < 0)
            semaphore_.post();
    }

private:
    Semaphore semaphore_;
    std::atomic<int> count_;
};

} // namespace utils
} // namespace pipc

#endif // PIPC_UTILS_FAST_SEMAPHORE_HPP
