#include "ac3log/simplelogger.hpp"
#include "ara/com/types.h"
#include "ara/runtime.h" // TODO is this the correct include path ??
#include "com/bosch/vrte/com/example/isum_proxy.h"
#include "com/bosch/vrte/com/example/iseed_proxy.h"
#include "utils.h"

#include <chrono>
#include <memory>
#include <thread>

#define MQ_APP_NAME "/ipc_example_client"
namespace ipc_example = com::bosch::vrte::com::example;

// Anonymous namespace for instance testing
namespace
{
ara::com::InstanceIdentifier ISumInstance("11");
ara::com::InstanceIdentifier ISeedInstance("22");
} // namespace

uint32_t g_rx_killswitch = 0;

ara::com::SampleContainer<ara::com::SamplePtr<DataMessage const>> samples_data_msg;
std::unique_ptr<ipc_example::proxy::ISeedProxy> seedCltProxy;

static void sigHandler(int f_sig)
{
    std::ignore = f_sig;
    // caught SIGINT or SIGTERM, now exit gracefully
    g_rx_killswitch = 1;
}

void seedProxy_EventHandler()
{
        INFO_PRINTF("seedProxy_EventHandler \n");
        // Wait for new event
        ara::com::SampleContainer<ara::com::SamplePtr<DataMessage const>> samples_data_msg;
        uint32_t noOfDataChecks = 0u;
        while (noOfDataChecks < 15)
        {
            noOfDataChecks++;
            auto result = seedCltProxy->data.GetNewSamples(
                [&](ara::com::SamplePtr<DataMessage const> sample) { samples_data_msg.push_back(std::move(sample)); });
            if (((int)result.HasValue() > 0) && ((int)result.Value() > 0))
            {
                INFO_PRINTF("aseedCltProxy - Number of data received %d \n", result.Value());
                break;
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(100u));
        }
        for (auto& l_sample : samples_data_msg)
        {
            INFO_PRINTF("seedCltProxy -- get the seed event, value is %d\n",l_sample->Data);
        }
        samples_data_msg.clear();
}

void Loop()
{
#if 1
	int i=0,j=0;
    INFO_PRINTF("seedSkeleton - findService");
    std::unique_ptr<ipc_example::proxy::ISumProxy> sumCltProxy;

    sumCltProxy.reset(FindProxyInTime<ipc_example::proxy::ISumProxy>(ISumInstance));
    seedCltProxy.reset(FindProxyInTime<ipc_example::proxy::ISeedProxy>(ISeedInstance));
    seedCltProxy->data.SetReceiveHandler(seedProxy_EventHandler);
    seedCltProxy->data.Subscribe(1);

    while (0 == g_rx_killswitch)
    {
        auto l_future = sumCltProxy->sum(i++,j++);
            INFO_PRINTF("Get the future using Get()");
            ipc_example::Outputsum l_output = l_future.get();
            INFO_PRINTF("Future returned, sum = %d\n", l_output.ret);
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
#endif
}

int main(int argc, char* argv[])
{
    static_cast<void>(argc);
    static_cast<void>(argv);
    // register sigHandler for SIGINT and SIGTERM
    struct sigaction act;
    sigemptyset(&act.sa_mask);
    act.sa_handler = sigHandler;
    act.sa_flags   = 0;
    if (-1 == sigaction(SIGINT, &act, NULL))
    {
        LOG_ERR("Calling sigaction() failed");
        exit(EXIT_FAILURE);
    }

    if (-1 == sigaction(SIGTERM, &act, NULL))
    {
        LOG_ERR("Calling sigaction() failed");
        exit(EXIT_FAILURE);
    }
    log_init();

    // initialize runtime and connect to RouDi
    ara::Runtime::GetInstance(MQ_APP_NAME);

    std::thread runner(Loop);
    runner.join();

    return (EXIT_SUCCESS);
}

