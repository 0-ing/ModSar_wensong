#include "ac3log/simplelogger.hpp"
#include "ara/com/types.h"
#include "ara/runtime.h" // TODO is this the correct include path ??
#include "com/bosch/vrte/com/it/ipc/iapp1notification_skeleton.h"
#include "com/bosch/vrte/com/it/ipc/iapp2notification_proxy.h"
#include "com/bosch/vrte/com/it/ipc/servicecontroller_proxy.h"
#include "utils.h"

#include "gtest/gtest.h"
#include <atomic>
#include <chrono>
#include <exception>
#include <memory>
#include <thread>

#define MQ_APP_NAME "/sender" /* unique identifier */
namespace it_ipc = com::bosch::vrte::com::it::ipc;

// Anonymous namespace for instance testing
namespace
{
ara::com::InstanceIdentifier IApp1NotificationInstance("11");
ara::com::InstanceIdentifier IApp2NotificationInstance("22");
ara::com::InstanceIdentifier ServiceControllerInstance("1");
} // namespace

///
/// @defgroup BT_IPC_event_tests BT IPC_event tests
/// @verbatim embed:rst:leading-slashes
/// .. test_spec:: BT_IPC_event
///     :id: TS_IPC_event
///     :status: new/changed
///     :tests:
///
///         **Test Design**
///             Testing that event communication via IPC is working correctly.
///
///         .. doxygengroup:: BT_IPC_event_Test_Cases
///             :project: VRTE
///
/// @endverbatim

class BT_IPC_event : public testing::Test
{
protected:
    static void SetUpTestSuite()
    {
        log_init();
    }

    void SetUp() override
    {
        app2NotificationProxy                           = nullptr;
        expectCallTo_app2NotificationProxy_EventHandler = false;
        ara::Runtime::GetInstance(MQ_APP_NAME);
        INFO_PRINTF("ServiceControllerProxy - FindProxyInTime");
        serviceControllerProxy = FindProxyInTime<it_ipc::proxy::ServiceControllerProxy>(ServiceControllerInstance);
        ASSERT_FALSE(serviceControllerProxy == nullptr);
    }

    void TearDown() override
    {
    }

    it_ipc::proxy::IApp2NotificationProxy* app2NotificationProxy;
    it_ipc::proxy::ServiceControllerProxy* serviceControllerProxy;
    bool expectCallTo_app2NotificationProxy_EventHandler;

public:
    void app2NotificationProxy_EventHandler()
    {
        INFO_PRINTF("app1: app2SendDataToApp1Proxy - app2NotificationProxy_EventHandler \n");
        ASSERT_TRUE(expectCallTo_app2NotificationProxy_EventHandler);
        expectCallTo_app2NotificationProxy_EventHandler = false;
        // Wait for new event
        ara::com::SampleContainer<ara::com::SamplePtr<DataMessage const>> samples_data_msg;
        uint32_t noOfDataChecks = 0u;
        while (noOfDataChecks < 15)
        {
            noOfDataChecks++;
            auto result = app2NotificationProxy->DataApp2.GetNewSamples(
                [&](ara::com::SamplePtr<DataMessage const> sample) { samples_data_msg.push_back(std::move(sample)); });
            if (((int)result.HasValue() > 0) && ((int)result.Value() > 0))
            {
                INFO_PRINTF("app1: IApp2NotificationProxy - Number of data received %d \n", result.Value());
                break;
            }
            ASSERT_LT(noOfDataChecks, 15U);
            std::this_thread::sleep_for(std::chrono::milliseconds(100u));
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1000u));
        // Event received, check payload is the inverse of the send data
        {
            INFO_PRINTF("app1: IApp1NotificationSkeleton - Data received \n");
            checkEventPayload(samples_data_msg, true);
            samples_data_msg.clear();
        }
    }
};

class IApp1NotificationSkeletonImpl : public it_ipc::skeleton::IApp1NotificationSkeleton
{
public:
    ~IApp1NotificationSkeletonImpl()
    {
    }

    IApp1NotificationSkeletonImpl(const ara::com::InstanceIdentifier& f_instance)
        : it_ipc::skeleton::IApp1NotificationSkeleton(f_instance)
    {
    }
};

/// @addtogroup BT_IPC_event_Test_Cases
/// @verbatim embed:rst:leading-slashes
/// **Test Case: Event Communication over IPC (Bidirectional, Polling)**
///
/// **Test Steps**
///     1. App1 and App2 offer IApp2SendDataToApp1 service and subscribe to each other
///     2. App1 sends an event to App2
///     3. App2 automatically inverts the content and sends it back to App1
///     4. App1 verifies the received data
///     5. App1 unsubscribes and checks if no further data is received
///
/// **Expected Result:**
///     1. No received data is available before App1 send data.
///     2. When App1 receive event from App2, the payload is the inverse of the data which is sent from App1.
///     3. No further data is received after App1 unsubscribe to the event.
/// @endverbatim
TEST_F(BT_IPC_event, EventPolling)
{
    // Initialize runtime and connect to RouDi
    ara::com::SampleContainer<ara::com::SamplePtr<DataMessage const>> samples_data_msg;

    INFO_PRINTF("app1: IApp1NotificationSkeleton - OfferService");
    IApp1NotificationSkeletonImpl* app1NotificationSkeleton = new IApp1NotificationSkeletonImpl(
        IApp1NotificationInstance);
    app1NotificationSkeleton->OfferService();

    INFO_PRINTF("app1: IApp2NotificationProxy - FindProxyInTime");
    it_ipc::proxy::IApp2NotificationProxy* app2NotificationProxy
        = FindProxyInTime<it_ipc::proxy::IApp2NotificationProxy>(IApp2NotificationInstance, 10U);
    ASSERT_FALSE(app2NotificationProxy == nullptr);

    std::this_thread::sleep_for(std::chrono::milliseconds(1000u));
    // Check that no data is available before we have subscribed and subscribe
    {
        auto result = app2NotificationProxy->DataApp2.GetNewSamples(
            [&](ara::com::SamplePtr<DataMessage const> sample) { samples_data_msg.push_back(std::move(sample)); });

        ASSERT_FALSE(result.HasValue());
        samples_data_msg.clear();
    }
    app2NotificationProxy->DataApp2.Subscribe(1);

    // Wait for successful subscription
    INFO_PRINTF("app1: IApp2NotificationProxy - Wait for successful subscription");
    waitForEventSubscription(app2NotificationProxy->DataApp2);

    // Give the other side some more moments to find our service
    waitForClientSubscription(serviceControllerProxy, "IBigDataNotificationProxy");

    // There should still no data so far
    {
        auto result = app2NotificationProxy->DataApp2.GetNewSamples(
            [&](ara::com::SamplePtr<DataMessage const> sample) { samples_data_msg.push_back(std::move(sample)); });
        ASSERT_TRUE(result.HasValue());
        ASSERT_EQ(result.Value(), 0U);
        samples_data_msg.clear();
    }

    // Send event to app 2, on reception of the event, app2 will send the inverted event back
    {
        INFO_PRINTF("app1: IApp1NotificationSkeleton - Sending event");
        auto data = app1NotificationSkeleton->DataApp1.Allocate();
        fillEventData(data.Value());
        app1NotificationSkeleton->DataApp1.Send(std::move(data).Value());
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(3000u));
    // Wait for new event
    uint32_t noOfDataChecks = 0u;
    while (noOfDataChecks < 20)
    {
        noOfDataChecks++;
        auto result = app2NotificationProxy->DataApp2.GetNewSamples(
            [&](ara::com::SamplePtr<DataMessage const> sample) { samples_data_msg.push_back(std::move(sample)); });
        if (((int)result.HasValue() > 0) && ((int)result.Value() > 0))
        {
            INFO_PRINTF("app1: IApp2NotificationProxy - Number of data received %d \n", result.Value());
            break;
        }
        EXPECT_LT(noOfDataChecks, 20);
        std::this_thread::sleep_for(std::chrono::milliseconds(200u));
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(3000u));
    // Event received, check payload is the inverse of the send data
    {
        INFO_PRINTF("app1: IApp1NotificationSkeleton - Data received \n");
        for (auto& l_sample : samples_data_msg)
        {
            for (uint32_t i = 0, end = sizeof(l_sample->Data); i < end; i++)
            {
                uint8_t tmp = static_cast<uint8_t>(~(i % 255));
                EXPECT_EQ(tmp, l_sample->Data[i]);
            }
        }
        samples_data_msg.clear();
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(3000u));

    // Unsubscribe and check that no further data is received
    app2NotificationProxy->DataApp2.Unsubscribe();
    // Send event to app 3, on reception of the event, app2 will NOT send any data back
    INFO_PRINTF("IApp2NotificationProxy - Wait for not subscription");
    uint32_t noOfSubscriptionChecks = 0u;
    while (ara::com::SubscriptionState::kNotSubscribed != app2NotificationProxy->DataApp2.GetSubscriptionState())
    {
        noOfSubscriptionChecks++;
        ASSERT_LT(noOfSubscriptionChecks, 30u);
        std::this_thread::sleep_for(std::chrono::milliseconds(100u));
    }

    {
        INFO_PRINTF("app1: IApp1NotificationSkeleton - Sending event");
        auto data = app1NotificationSkeleton->DataApp1.Allocate();
        fillEventData(data.Value());
        app1NotificationSkeleton->DataApp1.Send(std::move(data).Value());
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(3000u));
    // Wait for new events
    noOfDataChecks = 0u;
    while (noOfDataChecks < 30)
    {
        noOfDataChecks++;
        auto result = app2NotificationProxy->DataApp2.GetNewSamples(
            [&](ara::com::SamplePtr<DataMessage const> sample) { samples_data_msg.push_back(std::move(sample)); });
        ASSERT_FALSE(result.HasValue());
        std::this_thread::sleep_for(std::chrono::milliseconds(100u));
    }
    EXPECT_EQ(noOfDataChecks, 30u);

    // Cleanup
    samples_data_msg.clear();
    app1NotificationSkeleton->StopOfferService();
    delete app1NotificationSkeleton;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000u));
}

/// @addtogroup BT_IPC_event_Test_Cases
/// @verbatim embed:rst:leading-slashes
/// **Test Case: Event Communication over IPC (Bidirectional, EventHandler)**
///
/// **Test Steps**
///     1. App1 and App2 offer IApp2SendDataToApp1 service and subscribe to each other
///     2. App1 sends an event to App2
///     3. App2 automatically inverts the content and sends it back to App1
///     4. App1 verifies the received data
///     5. App1 unsets the EventHandler and checks if no further data is received
///
/// **Expected Result:**
///     1. No received data is available before App1 send data.
///     2. When App1 receive event from App2, the payload is the inverse of the data which is sent from App1.
///     3. No further data is received after App1 unsubscribe to the event.
/// @endverbatim
TEST_F(BT_IPC_event, EventAsync)
{
    // Initialize runtime and connect to RouDi
    ara::com::SampleContainer<ara::com::SamplePtr<DataMessage const>> samples_data_msg;
    INFO_PRINTF("app1: IApp1NotificationSkeleton - OfferService");
    IApp1NotificationSkeletonImpl* app1NotificationSkeleton = new IApp1NotificationSkeletonImpl(
        IApp1NotificationInstance);
    app1NotificationSkeleton->OfferService();

    INFO_PRINTF("app1: IApp2NotificationProxy - FindProxyInTime");
    app2NotificationProxy = FindProxyInTime<it_ipc::proxy::IApp2NotificationProxy>(IApp2NotificationInstance);
    EXPECT_FALSE(app2NotificationProxy == nullptr);

    // Check that no data is available before we have subscribed and subscribe
    {
        auto result = app2NotificationProxy->DataApp2.GetNewSamples(
            [&](ara::com::SamplePtr<DataMessage const> sample) { samples_data_msg.push_back(std::move(sample)); });
        EXPECT_EQ(0u, (int)result.HasValue());
        samples_data_msg.clear();
    }
    expectCallTo_app2NotificationProxy_EventHandler = false;
    app2NotificationProxy->DataApp2.SetReceiveHandler(
        std::bind(&BT_IPC_event::app2NotificationProxy_EventHandler, this));
    app2NotificationProxy->DataApp2.Subscribe(1);

    // Wait for successful subscription
    INFO_PRINTF("app1: IApp2NotificationProxy - Wait for successful subscription");
    waitForEventSubscription(app2NotificationProxy->DataApp2);

    // Wait for successful client subscription
    waitForClientSubscription(serviceControllerProxy, "IBigDataNotificationProxy");

    // Send event to app 3, on reception of the event, app2 will send the inverted event back
    {
        INFO_PRINTF("app1: IApp1NotificationSkeleton - Sending event");
        expectCallTo_app2NotificationProxy_EventHandler = true;
        auto data                                       = app1NotificationSkeleton->DataApp1.Allocate();
        fillEventData(data.Value());
        app1NotificationSkeleton->DataApp1.Send(std::move(data).Value());
    }

    // Wait that the EventHandler checks were executed
    uint32_t noOfDataChecks = 0u;
    while (true == expectCallTo_app2NotificationProxy_EventHandler)
    {
        noOfDataChecks++;
        ASSERT_LT(noOfDataChecks, 20u);
        std::this_thread::sleep_for(std::chrono::milliseconds(100u));
    }

    // unsubscribe, check no further calls happen
    expectCallTo_app2NotificationProxy_EventHandler = false;
    app2NotificationProxy->DataApp2.Unsubscribe();

    INFO_PRINTF("IApp2NotificationProxy - Wait for not subscription");
    uint32_t noOfSubscriptionChecks = 0u;
    while (ara::com::SubscriptionState::kNotSubscribed != app2NotificationProxy->DataApp2.GetSubscriptionState())
    {
        noOfSubscriptionChecks++;
        ASSERT_LT(noOfSubscriptionChecks, 30u);
        std::this_thread::sleep_for(std::chrono::milliseconds(100u));
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(3000u));
    // Send event to app 3, on reception of the event, app2 will send the inverted event back
    {
        INFO_PRINTF("app1: IApp1NotificationSkeleton - Sending event");
        auto data = app1NotificationSkeleton->DataApp1.Allocate();
        fillEventData(data.Value());
        app1NotificationSkeleton->DataApp1.Send(std::move(data).Value());
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(3000u));

    // Subscribe and Unset the receive handler and check that no further calls happen
    expectCallTo_app2NotificationProxy_EventHandler = false;
    app2NotificationProxy->DataApp2.Subscribe(1);
    // Wait for successful subscription
    INFO_PRINTF("app1: IApp2NotificationProxy - Wait for successful subscription");
    waitForEventSubscription(app2NotificationProxy->DataApp2);
    app2NotificationProxy->DataApp2.UnsetReceiveHandler();
    std::this_thread::sleep_for(std::chrono::milliseconds(500u));
    // Send event to app 3, on reception of the event, app2 will send the inverted event back
    {
        INFO_PRINTF("app1: IApp1NotificationSkeleton - Sending event");
        auto data = app1NotificationSkeleton->DataApp1.Allocate();
        fillEventData(data.Value());
        app1NotificationSkeleton->DataApp1.Send(std::move(data).Value());
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(3000u));

    // Clean up
    samples_data_msg.clear();
    app1NotificationSkeleton->StopOfferService();
    delete app1NotificationSkeleton;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000u));
}
