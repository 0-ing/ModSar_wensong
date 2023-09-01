/// @copyright : 2022 Robert Bosch GmbH. All rights reserved.

#ifndef COM_UTILS_THREADPOOL_HPP
#define COM_UTILS_THREADPOOL_HPP

#include <atomic>
#include <condition_variable>
#include <functional>
#include <mutex>
#include <thread>
#include <vector>

namespace com
{
namespace utils
{
/**
 * \brief A generic ThreadPool class.
 *
 * This class offers a ThreadPool which is able to provide threads for executing callbacks.
 */
class ThreadPool
{
public:
    /**
     * @brief Destructor.
     *
     * Cleanup of the used threads is performed in this function.
     */
    ~ThreadPool();

    /**
     * @brief Start the thread pool.
     *
     * @param threadCount The no. of threads to start.
     */
    void start(size_t threadCount);

    /**
     * @brief Stop the thread pool.
     */
    void stop();

    /**
     * @brief Function to notify the threadPool.
     *
     * For every notification the registered callback gets invoked once.
     */
    void notify();

    /**
     * @brief Function to register the methods callback.
     *
     * @param callback Callback to the function that process methods call.
     */
    void registerCallback(std::function<bool()> callback);

private:
    std::function<bool()> m_methodsCallback;

    std::vector<std::thread> m_threads;

    // worker function consisting in a set of instructions executed by each working thread
    void threadWorker();

    // flag to stop threads
    std::atomic<bool> m_stopThreads{true};

    std::atomic<int> m_callbacksCount{0};

    std::mutex m_poolMutex;
    std::condition_variable m_poolCv;
};

} // namespace utils
} // namespace com

#endif // COM_UTILS_THREADPOOL_HPP
