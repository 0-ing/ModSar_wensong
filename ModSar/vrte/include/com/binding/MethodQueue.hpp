/// @copyright : 2022 Robert Bosch GmbH. All rights reserved.

#ifndef COM_BINDING_METHODQUEUE_HPP
#define COM_BINDING_METHODQUEUE_HPP

#include "ara/com/e2e/types.h"
#include "com/Types.hpp"
#include "pipc/utils/Command.hpp"
#include "utils/ThreadPool.hpp"

namespace com
{
namespace binding
{
/**
 * \brief Method Queue class.
 *
 * This class is used in each Service Instance to handle requests (service method or field getter/setter calls) based on
 * the processing mode. The processing mode will be provided in the constructor of the MethodQueue
 */
class MethodQueue
{
public:
    using E2EErrorHandler
        = std::function<void(ara::com::e2e::E2EErrorCode, ara::com::e2e::DataID, ara::com::e2e::MessageCounter)>;
    using Command = pipc::utils::Command_1<void*, void>;
    using Mode    = ara::com::MethodCallProcessingMode;

    MethodQueue() = default;

    MethodQueue(const MethodQueue&) = delete;
    MethodQueue& operator=(const MethodQueue&) = delete;

    ~MethodQueue();

    /**
     * @brief Start the method queue.
     *
     * @remark
     * This function is called once during initialization by
     * the generated code. Calling it twice is undefined behavior.
     *
     * @param mode The method call processing mode.
     */
    void start(ara::com::MethodCallProcessingMode mode);

    /**
     * @brief Function to add a method call in the method queue
     *
     */
    void addMethodInvocation(Command cmd);

    /**
     * @brief Function used to execute the next method call from the method queue.
     *
     * @return true , if at least one pending method call (method queue not empty) , false otherwise
     */
    Future<bool> ProcessNextMethodCall();

    /**
     * @brief Function used to execute the next method call from the method queue.
     *
     * ProcessNextMethodCall method described above with an additional input parameter.
     *
     * @param executor This parameter shall provide an executioner object in which ProcessNextMethodCall shall be invoked.
     */
    template<typename ExecutorT>
    ara::core::Future<bool> ProcessNextMethodCall(ExecutorT&& executor)
    {
        ara::core::Promise<bool> promise;

        if (methodMode_ == ara::com::MethodCallProcessingMode::kPoll)
        {
            std::function<bool()> methodQueueProcessCall = std::bind(&MethodQueue::processNextMethodCall, this);
            auto result                                  = executor(methodQueueProcessCall);
            if (result.HasValue())
            {
                promise.set_value(result.Value());
            }
            else
            {
                // ProcessNextMethodCall() cannot be executed with the provided executor
                // (e.g. because of resource problem)
                promise.SetError(ara::com::ComErrc::kCouldNotExecute);
            }
        }
        else
        {
            promise.SetError(ara::com::ComErrc::kWrongMethodCallProcessingMode);
        }

        return promise.get_future();
    }

    /**
     * @brief Function to register e2e error handler
     */
    void setE2EErrorHandler(E2EErrorHandler handler);

    /**
     * @brief Function to invoke e2e error handler
     */
    void invokeE2EErrorHandler(ara::com::e2e::E2EErrorCode errorCode,
                               ara::com::e2e::DataID dataID,
                               ara::com::e2e::MessageCounter messageCounter);

private:
    /**
     * @brief Internal function to process the next method call.
     *
     * @return true , if at least one pending method call (method queue not empty) , false otherwise
     */
    bool processNextMethodCall();

    // internal thread-pool used to get threads for executing methods callbacks
    utils::ThreadPool threadPool_;

    // queue used to store the incoming method calls
    std::queue<Command> methodQueue_;

    std::mutex queueMutex_;
    ara::com::MethodCallProcessingMode methodMode_;
    E2EErrorHandler e2eErrorHandler_;
};

} // namespace binding
} // namespace com

#endif // COM_BINDING_METHODQUEUE_HPP
