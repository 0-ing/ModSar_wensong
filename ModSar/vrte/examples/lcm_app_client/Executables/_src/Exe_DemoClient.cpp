// define the unique application identifier
#include <iostream>
#include <array>
#include <csignal>
#include <atomic>

#include <ara/log/logger.h>
#include <ara/exec/execution_client.h>
#include <ara/core/initialization.h>

#include "Cmp_DemoClient.hpp"

namespace Executable
{
static std::atomic<bool> stopMain{false};
static void signalHandler(std::int32_t signal)
{
    static_cast<void>(signal);
    Executable::stopMain = true;
}
}    // namespace Executable

int main()
{
    const std::string APP_NAME{"/Exe_DemoClient"};    // unique identifier

    ara::log::Logger &cmplogstream_{ara::log::CreateLogger("DEMC", "Exe_DemoClient main function logging", ara::log::LogLevel::kVerbose)};

    /* Initalize adaptive AUTOSAR middleware components */

    ara::core::Result<void> rt = ara::core::Initialize();
    if (rt.HasValue() == false)
    {
        ara::core::ErrorCode ec = rt.Error();
        cmplogstream_.LogError() << "ara::core could not be initialized. Error: " << ec.Message() << "["
                                 << ec.SupportData() << "]\n";
        return EXIT_FAILURE;
    }

    static_cast<void>(ara::Runtime::GetInstance(APP_NAME));

    cmplogstream_.LogInfo() << "Demo Client executable's main: Create instance";
    std::array<std::unique_ptr<rb::pt::interfaces::IComponentSwc>, 1> components;

    ara::exec::ExecutionClient exec_client;
    // Create the components and store them in the array
    ara::com::InstanceIdentifier l_instance("1");
    components.at(0U) = std::unique_ptr<rb::pt::interfaces::IComponentSwc>(
        new bosch::vrte::stm::democlient::Cmp_DemoClient(l_instance));

    std::signal(SIGINT, &Executable::signalHandler);

    // Initialize the components
    cmplogstream_.LogInfo() << "Main: Startup";
    for (auto &component : components)
    {
        if (component->Init() != 0)
        {
            cmplogstream_.LogError() << "Components could not be initialized";
            return -1;
        }
    }

    // Execute the components
    cmplogstream_.LogInfo() << "Main: Run";
    for (auto &component : components)
    {
        if (component->Run() != 0)
        {
            cmplogstream_.LogError() << "Components are not running";
            return -1;
        }
    }

    // Execute the components

     //Report running state of the executable as running
     if (exec_client.ReportExecutionState(ara::exec::ExecutionState::kRunning))
     {
         //cmplogstream_.LogInfo() << "[EXM] Successfully reported execution state RUNNING";
     }
     else
     {
         //cmplogstream_.LogError() << "[EXM] Could not report execution state RUNNING";
     }

    // Report running state of the executable as running
    // For apps which are not started by the ExM (EcuCfg) it is not possible to report the state to ExM
    // as this is not a real use case to start apps manually
    // exec_client.ReportExecutionState(ara::exec::ExecutionState::kRunning);

    // Wait for someone to stop the executable via a SIGINT (ctrl+C)
    while (Executable::stopMain == false)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    cmplogstream_.LogInfo() << "Main: Stopped!";

    // Shutdown the components
    // For apps which are not started by the ExM (EcuCfg) it is not possible to report the state to ExM
    //exec_client.ReportExecutionState(ara::exec::ExecutionState::kTerminating);
    for (auto &component : components)
    {
        if (component->Shutdown() != 0)
        {
            cmplogstream_.LogError() << "Components could not be shutdown";
            return -1;
        }
    }

    cmplogstream_.LogInfo() << "Main: Return";
    ara::core::Deinitialize();
    return 0;
}
