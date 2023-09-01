#include "ac3log/simplelogger.hpp"
#include "ara/com/types.h"
#include "ara/runtime.h" // TODO is this the correct include path ??
#include "com/bosch/vrte/com/it/method/imethodapp1_skeleton.h"
#include "com/bosch/vrte/com/it/method/imethodapp3_proxy.h"
#include "utils.h"

#include "gtest/gtest.h"
#include <atomic>
#include <chrono>
#include <memory>
#include <thread>

#define MQ_APP_NAME "/sender" /* unique identifier */
namespace it_method = com::bosch::vrte::com::it::method;

namespace
{
ara::com::InstanceIdentifier IMethodApp1Instance("255");
ara::com::InstanceIdentifier IMethodApp3Instance("32500");
} // namespace

MethodResult MtdResult;

class IMethodApp1SkeletonImpl : public it_method::skeleton::IMethodApp1Skeleton
{
public:
    ~IMethodApp1SkeletonImpl()
    {
    }

    IMethodApp1SkeletonImpl(const ara::com::InstanceIdentifier& f_instance)
        : it_method::skeleton::IMethodApp1Skeleton(f_instance)
    {
    }

    /* deployed someip metod */
    void MethodApp1CalledFromAppX(const MethodResult input0) override
    {
        INFO_PRINTF("------------------Method-MethodCalled----------------- \n");
        INFO_PRINTF("Result: %d", input0.result);
        MtdResult.result = input0.result;
    }
};

///
/// @defgroup BT_METHODS_tests Methods tests
/// @verbatim embed:rst:leading-slashes
/// .. test_spec:: BT_METHODS
///     :id: TS_METHODS
///     :status: accepted
///     :tests: SWS_CM_00191, SWS_CM_00193, SWS_CM_00195, SWS_CM_00196, SWS_CM_10297, SWS_CM_10298, SWS_CM_10301,
///             SWS_CM_10303, SWS_CM_10309, SWS_CM_10312, SWS_CM_10318, SWS_CM_10414, SC_COM_BINDING,
///             SC_COM_DSOMEIP_LIB, SC_COM_DSOMEIP_SD_MANAGER, PUB_COM_PROXY_SKELETON, SB_LIB_ARA_COM, SB_LIB_BINDING
///
///         **Test Design**
///             Testing that method communication via UDP is working correctly.
///
///         **Test Steps**
///             Common Test Steps
///              1. App3 offer IMethodApp3 service and App1 subscribe it
///              2. App1 offer IMethodApp1 service and App3 subscribe it
///
///         .. doxygengroup:: BT_METHODS_Test_Cases
///             :project: VRTE
/// @endverbatim
class BT_METHODS : public testing::Test
{
protected:
    static void SetUpTestCase()
    {
        log_init();
        // Initialize runtime and connect to RouDi
        ara::Runtime::GetInstance(MQ_APP_NAME);
        INFO_PRINTF("IMethodApp1Skeleton - OfferService");
        static IMethodApp1SkeletonImpl IMethodApp1Skeleton(IMethodApp1Instance);
        IMethodApp1Skeleton.OfferService();

        // Give the other side some more moments to find our service
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    void SetUp() override
    {
        MtdResult.result = 255;
        INFO_PRINTF("IMethodApp3Proxy - FindProxyInTime");
        methodApp3Proxy.reset(FindProxyInTime<it_method::proxy::IMethodApp3Proxy>(IMethodApp3Instance));
        ASSERT_FALSE(methodApp3Proxy == nullptr);
    }

    void TearDown() override
    {
    }

    std::unique_ptr<it_method::proxy::IMethodApp3Proxy> methodApp3Proxy;
};

/// @addtogroup BT_METHODS_Test_Cases
/// @verbatim embed:rst:leading-slashes
/// **Test Case: Access the result of the method InOut which has an input and output using get()**
///
/// **Test Steps**
///     1. App1 calls the method InOut of App3 known data
///     2. App3 uses the method InOut to invert the input data and send it back
///     3. App1 verfies the sent data from App3
///     4. App3 calls a Method of App1
///     5. App1 verfies if the call of App3 happend
///
/// **Expected Result:**
///     1. The received data of App1 is correct
///     2. App3's method is called from App1
/// @endverbatim
//@ID{[SWS_CM_10311]}
//@ID{[SWS_CM_10414]}
//@ID{[SWS_CM_00192]}
//@ID{[SWS_CM_10303]}
TEST_F(BT_METHODS, MethodInOut_Get)
{
    INFO_PRINTF("-----------------Methods------------------\n");
    INFO_PRINTF("Call InOut()\n");

    // Zero will be casted to the scoped enum: TestObject_Method within app3's method
    DataMessage l_input;
    for (uint32_t i = 0, end = sizeof(l_input.Data); i < end; i++)
    {
        l_input.Data[i] = static_cast<uint8_t>(i % 255);
    }

    auto l_future = methodApp3Proxy->InOut(l_input);

    INFO_PRINTF("Get the future using Get()");
    it_method::OutputInOut l_output = l_future.get();
    INFO_PRINTF("Future returned");
    for (uint32_t i = 0, end = sizeof(l_output.odataMtd.Data); i < end; i++)
    {
        uint8_t tmp = static_cast<uint8_t>(~(i % 255));
	//INFO_PRINTF("The dataMtd[%d]=0x%x\n",i, l_output.odataMtd.Data[i]);
        ASSERT_EQ(tmp, l_output.odataMtd.Data[i]);
    }

    INFO_PRINTF("---------------------Methods--------------------- \n");
    INFO_PRINTF("Check result of app1's method call from app3\n");

    // Wait for a successful output
    INFO_PRINTF("Wait for a successful result");
    uint32_t noOfResultChecks = 0u;
    while ((MtdResult.result != 0u) && (noOfResultChecks != 30u))
    {
        noOfResultChecks++;
        ASSERT_LT(noOfResultChecks, 30u);
        std::this_thread::sleep_for(std::chrono::milliseconds(100u));
    }
    INFO_PRINTF("---------Methods End--------------------- \n");
}

/// @addtogroup BT_METHODS_Test_Cases
/// @verbatim embed:rst:leading-slashes
/// **Test Case: Use is_ready () to poll if the call to the method InOut with input and output has finished**
///
/// **Test Steps**
///     1. App1 calls the method InOut of App3 known data
///     2. App3 uses the method InOut to invert the input data and send it back
///     3. App1 verfies the sent data from App3
///     4. App3 calls a Method of App1
///     5. App1 verfies if the call of App3 happend
///
/// **Expected Result:**
///     1. The received data of App1 is correct
///     2. App3's method is called from App1
/// @endverbatim
//@ID{[SWS_CM_00193]}
TEST_F(BT_METHODS, MethodInOut_Is_Ready)
{
    INFO_PRINTF("-----------------Methods------------------\n");
    INFO_PRINTF("Call InOut()\n");

    // Zero will be casted to the scoped enum: TestObject_Method within app3's method
    DataMessage l_input;
    for (uint32_t i = 0, end = sizeof(l_input.Data); i < end; i++)
    {
        l_input.Data[i] = static_cast<uint8_t>(i % 255);
    }

    auto l_future = methodApp3Proxy->InOut(l_input);

    INFO_PRINTF("Get the future using polling (is_ready)");

    uint8_t noOfPoll = 0;
    while (noOfPoll < 30u)
    {
        if (l_future.is_ready() == true)
        {
            it_method::OutputInOut l_output = l_future.get();
            INFO_PRINTF("Future returned");
            for (uint32_t i = 0, end = sizeof(l_output.odataMtd.Data); i < end; i++)
            {
                uint8_t tmp = static_cast<uint8_t>(~(i % 255));
                ASSERT_EQ(tmp, l_output.odataMtd.Data[i]);
            }
            break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        noOfPoll++;
        EXPECT_LT(noOfPoll, 30u);
    }

    INFO_PRINTF("---------------------Methods--------------------- \n");
    INFO_PRINTF("Check result of app1's method call from app3\n");

    // Wait for a successful output
    INFO_PRINTF("Wait for a successful result");
    uint32_t noOfResultChecks = 0u;
    while ((MtdResult.result != 0u) && (noOfResultChecks != 30u))
    {
        noOfResultChecks++;
        ASSERT_LT(noOfResultChecks, 30u);
        std::this_thread::sleep_for(std::chrono::milliseconds(100u));
    }
    INFO_PRINTF("---------Methods End--------------------- \n");
}

/// @addtogroup BT_METHODS_Test_Cases
/// @verbatim embed:rst:leading-slashes
/// **Test Case: Exceptionless access the result of the method InOut which has an input and output using GetResult()**
///
/// **Test Steps**
///     1. App1 calls the method InOut of App3 known data
///     2. App3 uses the method InOut to invert the input data and send it back
///     3. App1 verfies the sent data from App3
///     4. App3 calls a Method of App1
///     5. App1 verfies if the call of App3 happend
///
/// **Expected Result:**
///     1. The received data of App1 is correct
///     2. App3's method is called from App1
/// @endverbatim
//@ID{[SWS_CM_00195]}
TEST_F(BT_METHODS, MethodInOut_GetResult)
{
    INFO_PRINTF("-----------------Methods------------------\n");
    INFO_PRINTF("Call InOut()\n");

    // Zero will be casted to the scoped enum: TestObject_Method within app3's method
    DataMessage l_input;
    for (uint32_t i = 0, end = sizeof(l_input.Data); i < end; i++)
    {
        l_input.Data[i] = static_cast<uint8_t>(i % 255);
    }

    auto l_future = methodApp3Proxy->InOut(l_input);
    auto l_result = l_future.GetResult();

    INFO_PRINTF("Get the future using GetResult()");
    // ara::core::Result<it_method::OutputInOut, ara::core::ErrorCode> res = l_future.GetResult();
    if (l_result.HasValue())
    {
        it_method::OutputInOut l_output = l_result.Value();
        INFO_PRINTF("Future returned");
        for (uint32_t i = 0, end = sizeof(l_output.odataMtd.Data); i < end; i++)
        {
            uint8_t tmp = static_cast<uint8_t>(~(i % 255));
            ASSERT_EQ(tmp, l_output.odataMtd.Data[i]);
        }
    }

    INFO_PRINTF("---------------------Methods--------------------- \n");
    INFO_PRINTF("Check result of app1's method call from app3\n");

    // Wait for a successful output
    INFO_PRINTF("Wait for a successful result");
    uint32_t noOfResultChecks = 0u;
    while ((MtdResult.result != 0u) && (noOfResultChecks != 30u))
    {
        noOfResultChecks++;
        ASSERT_LT(noOfResultChecks, 30u);
        std::this_thread::sleep_for(std::chrono::milliseconds(100u));
    }
    INFO_PRINTF("---------Methods End--------------------- \n");
}

/// @addtogroup BT_METHODS_Test_Cases
/// @verbatim embed:rst:leading-slashes
/// **Test Case: Get notification when the result of method InOut is available which has an input and output using then()**
///
/// **Test Steps**
///     1. App1 calls the method InOut of App3 known data
///     2. App3 uses the method InOut to invert the input data and send it back
///     3. App1 verfies the sent data from App3
///     4. App3 calls a Method of App1
///     5. App1 verfies if the call of App3 happend
///
/// **Expected Result:**
///     1. The received data of App1 is correct
///     2. App3's method is called from App1
/// @endverbatim
//@ID{[SWS_CM_00197]}
//@ID{[SWS_CM_10318]}
TEST_F(BT_METHODS, MethodInOut_Then)
{
    INFO_PRINTF("-----------------Methods------------------\n");
    INFO_PRINTF("Call InOut()\n");

    // Zero will be casted to the scoped enum: TestObject_Method within app3's method
    DataMessage l_input;
    for (uint32_t i = 0, end = sizeof(l_input.Data); i < end; i++)
    {
        l_input.Data[i] = static_cast<uint8_t>(i % 255);
    }

    auto l_future = methodApp3Proxy->InOut(l_input);

    // ToDo: Add a "try catch" block for future.get()
    l_future.then([](ara::core::Future<it_method::OutputInOut> l_result) {
        INFO_PRINTF("Get the future using Then()");
        it_method::OutputInOut l_output = l_result.get();
        INFO_PRINTF("Future returned");
        for (uint32_t i = 0, end = sizeof(l_output.odataMtd.Data); i < end; i++)
        {
            uint8_t tmp = static_cast<uint8_t>(~(i % 255));
            ASSERT_EQ(tmp, l_output.odataMtd.Data[i]);
        }
    });

    INFO_PRINTF("---------------------Methods--------------------- \n");
    INFO_PRINTF("Check result of app1's method call from app3\n");

    // Wait for a successful output
    INFO_PRINTF("Wait for a successful result");
    uint32_t noOfResultChecks = 0u;
    while ((MtdResult.result != 0u) && (noOfResultChecks != 30u))
    {
        noOfResultChecks++;
        ASSERT_LT(noOfResultChecks, 30u);
        std::this_thread::sleep_for(std::chrono::milliseconds(100u));
    }
    INFO_PRINTF("---------Methods End--------------------- \n");
}

/// @addtogroup BT_METHODS_Test_Cases
/// @verbatim embed:rst:leading-slashes
/// **Test Case: The Method has only an input**
///
/// **Test Steps**
///     1. App1 calls the method OnlyIn of App3 with known data as input
///     2. App3 verfies the input data
///     3. App3 calls a Method of App1 if the data transmisson was successfull
///
/// **Expected Result:**
///     1. App3's method is called from App1
/// @endverbatim
TEST_F(BT_METHODS, MethodOnlyInput)
{
    INFO_PRINTF("Call OnlyIn of AppX\n");

    // Zero will be casted to the scoped enum: TestObject_Method within app3's method
    DataMessage l_input;
    for (uint32_t i = 0, end = sizeof(l_input.Data); i < end; i++)
    {
        l_input.Data[i] = static_cast<uint8_t>(i % 255);
    }

    methodApp3Proxy->OnlyIn(l_input);

    // Give the other side some more moments to find our service
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    // Wait for a successful output
    INFO_PRINTF("FromApp1: - Wait for a successful result");
    uint32_t noOfResultChecks = 0u;
    while (MtdResult.result != 1u)
    {
        noOfResultChecks++;
        ASSERT_LT(noOfResultChecks, 40u);
        std::this_thread::sleep_for(std::chrono::milliseconds(100u));
    }
    INFO_PRINTF("---------Methods End--------------------- \n");
}

/// @addtogroup BT_METHODS_Test_Cases
/// @verbatim embed:rst:leading-slashes
/// **Test Case: The Method has only an output**
///
/// **Test Steps**
///     1. App1 calls the method OnlyOut of App3
///     2. App3 sends known data to App1
///
/// **Expected Result:**
///     1. The received data of App1 is correct
/// @endverbatim
TEST_F(BT_METHODS, MethodOnlyOutput)
{
    INFO_PRINTF("-----------------Methods------------------\n");

    auto l_future = methodApp3Proxy->OnlyOut();

    it_method::OutputOnlyOut l_output = l_future.get();
    for (uint32_t i = 0u, end = sizeof(l_output.odataMtd.Data); i < end; i++)
    {
        uint8_t tmp = static_cast<uint8_t>(~(i % 255));
        ASSERT_EQ(tmp, l_output.odataMtd.Data[i]);
    }
    INFO_PRINTF("---------Methods End--------------------- \n");
}
