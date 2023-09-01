#include "ac3log/simplelogger.hpp"
#include "ara/com/types.h"
#include "ara/runtime.h" // TODO is this the correct include path ??
#include "com/bosch/vrte/com/example/isum_skeleton.h"
#include "com/bosch/vrte/com/example/iseed_skeleton.h"
#include "utils.h"

#include <chrono>
#include <memory>
#include <thread>

#define MQ_APP_NAME "/ipc_example_server"
namespace ipc_example = com::bosch::vrte::com::example;

// Anonymous namespace for instance testing
namespace
{
ara::com::InstanceIdentifier ISumInstance("11");
ara::com::InstanceIdentifier ISeedInstance("22");
} // namespace

uint32_t g_rx_killswitch = 0;

ara::com::SampleContainer<ara::com::SamplePtr<DataMessage const>> samples_data_msg;

static void sigHandler(int f_sig)
{
    std::ignore = f_sig;
    // caught SIGINT or SIGTERM, now exit gracefully
    g_rx_killswitch = 1;
}

class sumSkeletonImpl : public ipc_example::skeleton::ISumSkeleton
{
public:
    ~sumSkeletonImpl()
    {
    }

    sumSkeletonImpl(const ara::com::InstanceIdentifier& f_instance)
        : ipc_example::skeleton::ISumSkeleton(f_instance)
    {
    }

    /*deployed someip methods*/
    ara::core::Future<ipc_example::Outputsum> sum(const uint32_t input0, const uint32_t input1)
    {
        INFO_PRINTF("---------------------------------------\n");
        INFO_PRINTF("Method Sum()\n");
        INFO_PRINTF("---------------------------------------\n");
        ara::core::Promise<ipc_example::Outputsum> promise;
        struct ipc_example::Outputsum result;
        result.ret = input0+input1;
        //struct it_method::OutputInOut result = MyApp3InOut(input0);

        promise.set_value(result);

        INFO_PRINTF("---------------------------------------\n");

        return promise.get_future();
    }
};

class seedSkeletonImpl : public ipc_example::skeleton::ISeedSkeleton
{
public:
    ~seedSkeletonImpl()
    {
    }

    seedSkeletonImpl(const ara::com::InstanceIdentifier& f_instance)
        : ipc_example::skeleton::ISeedSkeleton(f_instance)
    {
    }
};

void Loop()
{
#if 1
	DataMessage seed;

	seed.Data = 0;
    INFO_PRINTF("seedSkeleton - OfferService");
    seedSkeletonImpl seedSkeleton(ISeedInstance);
    seedSkeleton.OfferService();

    INFO_PRINTF("sumSkeleton - OfferService");
    sumSkeletonImpl sumSkeleton(ISumInstance);
    sumSkeleton.OfferService();

    while (0 == g_rx_killswitch)
    {
#if 0
                            auto data = IApp2NotificationSkeleton.DataApp2.Allocate();
                            for (size_t i = 0, end = l_sample->Data.size(); i < end; i++)
                            {
                                data.Value()->Data[i] = static_cast<uint8_t>(~l_sample->Data[i]);
                            }
                            INFO_PRINTF("app2: IApp2NotificationSkeleton - Sending Data");
                            IApp2NotificationSkeleton.DataApp2.Send(std::move(data).Value());
#endif
                            seedSkeleton.data.Send(seed);
                            seed.Data++;

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

