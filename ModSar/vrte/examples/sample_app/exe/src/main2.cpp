#include <iostream>
#include <array>
#include <csignal>
#include <atomic>
#include <thread>
#include <ara/core/initialization.h>
#include <ara/log/logger.h>
#include <ara/exec/execution_client.h>


namespace Executable
{
static std::atomic<bool> stopMain{false};
static void signalHandler(std::int32_t signal)
{
    static_cast<void>(signal);
    Executable::stopMain = true;
}
}    // namespace Executable

int main()    // MISRA M3-2-2 / M3-2-2 can be ignored
{
    const std::string APP_NAME{"/Sample_App"};    // unique identifier

    ara::log::Logger &cmplogstream_{
        ara::log::CreateLogger("SAPP", "Exe_Sample_App main function logging", ara::log::LogLevel::kVerbose)};

    /* Initalize adaptive AUTOSAR middleware components */
#if defined(_WAVE33_P_)
	#pragma message("========== variant wave3.3 primary ===========")
#elif defined(_WAVE33_S_)
	#pragma message("========== variant wave3.3 secondary ===========")
#elif defined(_WAVE32_)
	#pragma message("========== variant wave3.2 ===========")
#endif
	
#if defined(_DEBUG_)
	#pragma message("========== debug ===========")
#elif defined(_RELEASE_)
	#pragma message("========== release ===========")
#endif

    ara::core::Result<void> rt{ara::core::Initialize()};
    if (rt.HasValue() == false)
    {
        ara::core::ErrorCode ec{rt.Error()};
        cmplogstream_.LogError() << "ara::core could not be initialized. Error: " << ec.Message() << "["
                                 << ec.SupportData() << "]\n";
        return EXIT_FAILURE;
    }

//    static_cast<void>(ara::Runtime::GetInstance(APP_NAME));    // This function initializes COM-Runtime

    cmplogstream_.LogInfo() << "Drvr_Sample_App executable's main: Create instance";

    std::signal(SIGINT, &Executable::signalHandler);
    std::signal(SIGTERM, &Executable::signalHandler);

    // Report running state of the executable as running
    // For apps which are not started by the ExM (EcuCfg) it is not possible to report the state to ExM
    // as this is not a real use case to start apps manually
    // exec_client.ReportExecutionState(ara::exec::ExecutionState::kRunning);

    // Wait for someone to stop the executable via a SIGINT (ctrl+C)
    while (Executable::stopMain == false)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    	cmplogstream_.LogInfo() << "Sample App: alive!";
    }
    cmplogstream_.LogInfo() << "Main: Stopped!";

    cmplogstream_.LogInfo() << "Main: Return";
    ara::core::Deinitialize();
    return 0;
}
