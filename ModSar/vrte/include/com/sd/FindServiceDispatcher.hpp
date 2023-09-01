#ifndef COM_SD_FIND_SERVICE_DISPATCHER_HPP
#define COM_SD_FIND_SERVICE_DISPATCHER_HPP

#include "ara/core/map.h"
#include "com/Types.hpp"
#include "pipc/utils/FastSemaphore.hpp"
#include "sd/IRuntime.hpp"

#include <thread>

namespace com
{
namespace sd
{
/**
 * @brief A FindServiceDispatcher to asynchronously process FindServiceHandler callbacks.
 *
 * The FindServiceDispatcher consists of a queue with service availability updates and a thread consuming the data.
 * The thread is triggered by semaphore.
 */
class FindServiceDispatcher
{
public:
    /** @brief Constructor. */
    FindServiceDispatcher();

    /** @brief Destructor. */
    ~FindServiceDispatcher();

    /** @brief Start the dispatcher thread. */
    void start();

    /** @brief Stop the dispatcher thread. */
    void stop();

    /** @brief Add a FindServiceHandler to the dispatcher. */
    void addFindServiceHandler(FindServiceHandle findServiceHandle, const FindServiceHandler& findServiceHandler);

    /**
     * @brief Add a FindServiceNotification to the dispatcher.
     *
     * This function consumes the given availableInstanceIds and resets the container.
     */
    void addFindServiceInvocation(ServiceHandleContainer& availableServiceHandles,
                                  FindServiceHandle findServiceHandle);

    /** @brief Remove a FindServiceHandle from the dispatcher. */
    bool removeFindServiceHandler(FindServiceHandle findServiceHandle);

private:
    /** @brief Element for one handler invocation. */
    struct HandlerInvocation
    {
        /** @brief Default constructor. */
        HandlerInvocation() = default;

        /** @brief Constructor for emplace semantics. */
        HandlerInvocation(ServiceHandleContainer& availableServiceHandles, FindServiceHandle findServiceHandle)
            : availableServiceHandles(std::move(availableServiceHandles)), findServiceHandle(findServiceHandle)
        {
        }

        /** @brief The list of available serviceHandles. */
        ServiceHandleContainer availableServiceHandles;
        /**
         * @brief The associated findServiceHandle.
         */
        FindServiceHandle findServiceHandle;
    };

    /** @brief Main function of the dispatcher thread. */
    void main();

    /** @brief Map of all active findServiceHandlers. */
    ara::core::Map<FindServiceHandle, FindServiceHandler> findServiceHandlers_;
    /** @brief Mutex for accessing findServiceHandlers_. */
    std::recursive_mutex handlersMutex_;
    /** @brief The queue of handler invocations. */
    std::deque<HandlerInvocation> queue_;
    /** @brief The mutex for accessing the data queue. */
    std::mutex queueMutex_;
    /** @brief Thread consuming the commands. */
    std::unique_ptr<std::thread> thread_;
    /** @brief Semaphore to signal the thread. */
    pipc::utils::FastSemaphore signal_;
    /** @brief Stop flag for joining the thread. */
    bool stop_;
};

} // namespace sd
} // namespace com

#endif // COM_SD_FIND_SERVICE_DISPATCHER_HPP
