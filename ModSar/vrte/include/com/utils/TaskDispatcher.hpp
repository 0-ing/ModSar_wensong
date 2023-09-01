/// @copyright : 2022 Robert Bosch GmbH. All rights reserved.
#ifndef COM_UTILS_TASKDISPATCHER_HPP
#define COM_UTILS_TASKDISPATCHER_HPP

#include "pipc/utils/Semaphore.hpp"

#include <functional>
#include <memory>
#include <thread>

namespace com
{
namespace utils
{
/**
 * @brief A TaskDispatcher to asynchronously process receiveHandler callbacks.
 *
 * The TaskDispatcher thread is triggered by semaphore to call the registered handler.
 *
 */
class TaskDispatcher
{
    using Semaphore = pipc::utils::Semaphore;

public:
    /** @brief Constructor to initialize the class members. */
    TaskDispatcher() : thread_(), semaphore_(0, 0), stop_(true), func_()
    {
    }

    /** @brief destructor to stop the thread (if not already stopped). */
    ~TaskDispatcher()
    {
        stop();
    }

    /** @brief Create the thread. */
    void start()
    {
        if (stop_)
        {
            stop_   = false;
            thread_ = std::make_unique<std::thread>(&TaskDispatcher::loop, this);
        }
    }

    /** @brief Signalize stop (if not already done) and posts the semaphore to break and join the thread loop. */
    void stop()
    {
        if (!stop_)
        {
            stop_ = true;
            semaphore_.post();
            thread_->join();
        }
    }

    /** @brief Post the semaphore to call the registered handler. */
    void notify()
    {
        semaphore_.post();
    }

    /** @brief Register the Receive Handler function. */
    void setReceiveHandler(std::function<void()> handler)
    {
        func_ = handler;
    }

    /** @brief Thread loop. */
    void loop()
    {
        while (true)
        { // wait on semaphore post (notify or stop)
            semaphore_.wait();
            if (stop_)
            {
                break;
            }
            func_();
        }
    }

private:
    /** @brief worker thread. */
    std::unique_ptr<std::thread> thread_;
    /** @brief a semaphore to wait on (notify or stop call). */
    Semaphore semaphore_;
    /** @brief flag to end break the loop and join. */
    bool stop_;
    /** @brief registered receive handler func. */
    std::function<void()> func_;
};

} // namespace utils
} // namespace com
#endif // COM_UTILS_TASKDISPATCHER_HPP
