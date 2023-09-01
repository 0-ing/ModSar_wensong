#include "ac3log/simplelogger.hpp"
#include "ara/com/types.h"
#include "ara/runtime.h" // TODO is this the correct include path ??
#include "com/bosch/vrte/com/it/method/imethodapp1_proxy.h"
#include "com/bosch/vrte/com/it/method/imethodapp3_skeleton.h"
#include "utils.h"

#include <chrono>
#include <memory>
#include <thread>

#define MQ_APP_NAME "/receiver" /* unique identifier */

namespace it_method = com::bosch::vrte::com::it::method;

namespace
{
ara::com::InstanceIdentifier IMethodApp3Instance("32500");
ara::com::InstanceIdentifier IMethodApp1Instance("255");
} // namespace

uint32_t g_rx_killswitch = 0;

enum MethodFlag
{
    InOut = 0,
    In,
    Out,
    Default = 255
};
uint8_t methodFlag = Default;

static MethodResult MtdResult;

static void sigHandler(int f_sig)
{
    std::ignore = f_sig;
    // caught SIGINT or SIGTERM, now exit gracefully
    g_rx_killswitch = 1;
}

// Method's definition
it_method::OutputInOut MyApp3InOut(const DataMessage input0)
{
    INFO_PRINTF(" Method Call InOut \n");

    // The method is called first from App2
    struct it_method::OutputInOut Output;
    uint32_t i   = 0;
    uint32_t end = sizeof(input0.Data);
    for (i = 0; i < end; i++)
    {
        Output.odataMtd.Data[i] = static_cast<uint8_t>(~input0.Data[i]);
    }
    methodFlag = InOut;
    return (Output);
}

class IMethodApp3SkeletonImpl : public it_method::skeleton::IMethodApp3Skeleton
{
public:
    ~IMethodApp3SkeletonImpl()
    {
    }

    IMethodApp3SkeletonImpl(const ara::com::InstanceIdentifier& f_instance)
        : it_method::skeleton::IMethodApp3Skeleton(f_instance)
    {
    }

    // deployed someip method
    ara::core::Future<it_method::OutputInOut> InOut(const DataMessage input0) override
    {
        INFO_PRINTF("---------------------------------------\n");
        INFO_PRINTF("Method InOut()\n");
        INFO_PRINTF("---------------------------------------\n");
        ara::core::Promise<it_method::OutputInOut> promise;

        struct it_method::OutputInOut result = MyApp3InOut(input0);

        promise.set_value(result);

        INFO_PRINTF("---------------------------------------\n");

        return promise.get_future();
    }

    ara::core::Future<it_method::OutputOnlyOut> OnlyOut(void) override
    {
        INFO_PRINTF("---------------------------------------\n");
        INFO_PRINTF("Method OnlyOut()\n");
        INFO_PRINTF("---------------------------------------\n");
        ara::core::Promise<it_method::OutputOnlyOut> promise;

        struct it_method::OutputOnlyOut result;
        uint32_t i   = 0;
        uint32_t end = sizeof(result.odataMtd.Data);
        for (i = 0; i < end; i++)
        {
            result.odataMtd.Data[i] = static_cast<uint8_t>(~(i % 255));
        }
        promise.set_value(result);

        INFO_PRINTF("---------------------------------------\n");

        return promise.get_future();
    }

    void OnlyIn(const DataMessage input0)
    {
        INFO_PRINTF("Function OnlyIn called\n");
        // check if the received input is valid
        bool failed  = false;
        uint32_t i   = 0;
        uint32_t end = sizeof(input0.Data);
        for (i = 0; i < end; i++)
        {
            if (input0.Data[i] != static_cast<uint8_t>(i % 255))
                failed = true;
        }

        if (failed)
            MtdResult.result = 255u;
        else
            MtdResult.result = 1u;
        INFO_PRINTF("Result: %d\n", MtdResult.result);
        methodFlag = In;
    }
};

void Loop()
{
    bool lookingForIMethodApp1Instance = true;

    INFO_PRINTF(" IMethodApp3Skeleton - OfferService");
    IMethodApp3SkeletonImpl IMethodApp3Skeleton(IMethodApp3Instance);
    IMethodApp3Skeleton.OfferService();

    it_method::proxy::IMethodApp1Proxy* methodApp1Proxy = nullptr;

    while (0 == g_rx_killswitch)
    {
        if (true == lookingForIMethodApp1Instance)
        {
            methodApp1Proxy = FindProxyInTime<it_method::proxy::IMethodApp1Proxy>(IMethodApp1Instance, 1);
            if (nullptr != methodApp1Proxy)
            {
                lookingForIMethodApp1Instance = false;
                INFO_PRINTF("IMethodApp1Proxy - Proxy Found");
            }
        }

        if (nullptr != methodApp1Proxy && methodFlag != Default)
        {
            INFO_PRINTF("-----------------Methods------------------\n");
            if (methodFlag == InOut)
            {
                MtdResult.result = 0u;
                INFO_PRINTF("InOut result %d\n", MtdResult.result);
                methodApp1Proxy->MethodApp1CalledFromAppX(MtdResult);
                methodFlag = Default;
            }
            if (methodFlag == In)
            {
                INFO_PRINTF("In result %d\n", MtdResult.result);
                methodApp1Proxy->MethodApp1CalledFromAppX(MtdResult);
                methodFlag = Default;
            }
            INFO_PRINTF("-------------------Methods End--------------\n");
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

int main(int argc, char* argv[])
{
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
