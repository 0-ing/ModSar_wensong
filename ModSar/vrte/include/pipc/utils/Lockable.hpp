#ifndef UTILS_THREADSAFE_HPP
#define UTILS_THREADSAFE_HPP

#include <mutex>

namespace pipc
{
namespace utils
{
/**
 * @brief List of supported lock implementations.
 */
enum class LockImpl
{
    /**
     * @brief Use a standard mutex for exclusive access.
     *
     * Limitations:
     * - no support for recursive locking
     */
    kMutex = 0,
    /**
     * @brief Use a fast recursive mutex for exclusive access.
     *
     * Limitations:
     * - no priority inheritance
     * - no guarantee which blocked thread is scheduled first
     *
     * @remark
     * If we need it, we can implement it by using a FastSemaphore and
     * pthread_self.
     */
    // kFastRecursiveMutex,
    /**
     * @brief Use a fast mutex for exclusive access.
     *
     * Limitations:
     * - no priority inheritance
     * - no guarantee which blocked thread is scheduled first
     * - no support for recursive locking
     *
     * @remark
     * If we need it, we can implement it by using a FastSemaphore.
     */
    // kFastMutex,
};

/**
 * @brief Class for thread-safe handling of type T.
 *
 * Lockable makes sure that a given value stays consistent over the time it is
 * read. It bundles T with a lock for more convenient handling.
 *
 * @remark
 * Best case this class won't be needed, using locks in realtime-critical can
 * always lead to unexpected side effects.
 */
template<typename T, LockImpl P = LockImpl::kMutex>
struct Lockable;

/** @brief Lockable with a mutex. */
template<typename T>
struct Lockable<T, LockImpl::kMutex>
{
    using LockType = std::mutex;
    T value;
    std::mutex lock;
};

} // namespace utils
} // namespace pipc

#endif // UTILS_THREADSAFE_HPP
