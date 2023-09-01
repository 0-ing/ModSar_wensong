
#include "ac3log/simplelogger.hpp"
#include "ara/com/types.h"
#include "ara/runtime.h" // TODO is this the correct include path ??
#include "com/bosch/vrte/com/it/ipc/iapp1notification_proxy.h"
#include "com/bosch/vrte/com/it/ipc/iapp2notification_skeleton.h"
#include "com/bosch/vrte/com/it/ipc/servicecontroller_skeleton.h"
#include "utils.h"

#include <chrono>
#include <memory>
#include <thread>

#define MQ_APP_NAME "/receiver" /* unique identifier */

namespace it_ipc = com::bosch::vrte::com::it::ipc;

// Anonymous namespace for instance testing
namespace
{
ara::com::InstanceIdentifier IApp1NotificationInstance("11");
ara::com::InstanceIdentifier IApp2NotificationInstance("22");
ara::com::InstanceIdentifier ServiceControllerInstance("1");

} // namespace

// Enum
enum class fieldNotify
{
    triggerFieldTestNotify = 0,
    triggerFieldTestNoSetNotify,
    triggerFieldTestNoGetNotify,
    DoNottriggerNotify = 255,
};

uint32_t g_rx_killswitch = 0;

ara::com::SampleContainer<ara::com::SamplePtr<DataMessage const>> samples_data_msg;

uint8_t triggernotify = static_cast<uint8_t>(fieldNotify::DoNottriggerNotify);

static void sigHandler(int f_sig)
{
    std::ignore = f_sig;
    // caught SIGINT or SIGTERM, now exit gracefully
    g_rx_killswitch = 1;
}

class ServiceControllerSkeletonImpl : public it_ipc::skeleton::ServiceControllerSkeleton
{
public:
    ~ServiceControllerSkeletonImpl()
    {
    }

    ServiceControllerSkeletonImpl(const ara::com::InstanceIdentifier& f_instance)
        : it_ipc::skeleton::ServiceControllerSkeleton(f_instance), state(ara::com::SubscriptionState::kNotSubscribed)
    {
    }

    /*deployed someip methods*/
    ara::core::Future<it_ipc::OutputGetSubscriptionState> GetSubscriptionState()
    {
        return GetClientSubscriptionState<it_ipc::OutputGetSubscriptionState>(state);
    }

    ara::com::SubscriptionState state;
};

class IApp2NotificationSkeletonImpl : public it_ipc::skeleton::IApp2NotificationSkeleton
{
public:
    ~IApp2NotificationSkeletonImpl()
    {
    }

    IApp2NotificationSkeletonImpl(const ara::com::InstanceIdentifier& f_instance)
        : it_ipc::skeleton::IApp2NotificationSkeleton(f_instance)
    {
    }
};

void Loop()
{
    bool lookingForIApp1NotificationInstance = true;
    bool wasOnceSubscribed                   = false;

    INFO_PRINTF("ServiceControllerSkeleton - OfferService");
    ServiceControllerSkeletonImpl ServiceControllerSkeleton(ServiceControllerInstance);
    ServiceControllerSkeleton.OfferService();

    INFO_PRINTF("app2: IApp2NotificationSkeleton - OfferService");
    IApp2NotificationSkeletonImpl IApp2NotificationSkeleton(IApp2NotificationInstance);
    IApp2NotificationSkeleton.OfferService();

    it_ipc::proxy::IApp1NotificationProxy* app1NotificationProxy = nullptr;

    while (0 == g_rx_killswitch)
    {
        if (true == lookingForIApp1NotificationInstance)
        {
            app1NotificationProxy = FindProxyInTime<it_ipc::proxy::IApp1NotificationProxy>(IApp1NotificationInstance, 1);
            if (nullptr != app1NotificationProxy)
            {
                lookingForIApp1NotificationInstance = false;
                app1NotificationProxy->DataApp1.Subscribe(1);
                INFO_PRINTF("app2: app1NotificationProxy - Proxy Subscribed");
            }
        }

        if (nullptr != app1NotificationProxy)
        {
            ServiceControllerSkeleton.state = app1NotificationProxy->DataApp1.GetSubscriptionState();
            if (ara::com::SubscriptionState::kSubscribed == ServiceControllerSkeleton.state)
            {
                wasOnceSubscribed = true;
                auto result       = app1NotificationProxy->DataApp1.GetNewSamples(
                          [&](ara::com::SamplePtr<DataMessage const> sample) {
                        samples_data_msg.push_back(std::move(sample));
                        INFO_PRINTF("app2: app1NotificationProxy - pushed sample");
                          });
                if (result.HasValue())
                {
                    size_t nSamples = result.Value();
                    if (nSamples > 0)
                    {
                        INFO_PRINTF("app2: app1NotificationProxy - Number of data received %d \n", nSamples);
                        for (auto& l_sample : samples_data_msg)
                        {
                            auto data = IApp2NotificationSkeleton.DataApp2.Allocate();
                            for (size_t i = 0, end = l_sample->Data.size(); i < end; i++)
                            {
                                data.Value()->Data[i] = static_cast<uint8_t>(~l_sample->Data[i]);
                            }
                            INFO_PRINTF("app2: IApp2NotificationSkeleton - Sending Data");
                            IApp2NotificationSkeleton.DataApp2.Send(std::move(data).Value());
                        }
                        samples_data_msg.clear();
                    }
                }
                else
                {
                    INFO_PRINTF("app2: app1NotificationProxy - No data received. Error code %d \n", result.Error());
                }
            }
            else if (true == wasOnceSubscribed)
            {
                // we assume the skeleton went off and we have to start again
                lookingForIApp1NotificationInstance = true;
                app1NotificationProxy               = nullptr;
                wasOnceSubscribed                   = false;
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
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
