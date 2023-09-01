//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================
//
/// @file      subscriber.cpp
/// @brief     Method subscriber example application
/// @copyright Robert Bosch GmbH 2021
//=============================================================================
// Standard C++ Header files used for thread handling, delay and event
#include <chrono>
#include <csignal>
#include <thread>

//
#include <iostream>

//
using std::cout;
using std::endl;

// General Types Header-File used in ara::com
#include "ara/com/types.h"

// ara core and ara logging headers
#include "ara/core/error_code.h"
#include "ara/core/initialization.h"
#include "ara/core/result.h"

#include "ara/log/logger.h"

// Include Header-Files of the generated Service-Proxy
#include "com/bosch/vrte/method/method_proxy.h"

// Include implementation specific Header-Files for instance
#include <cstdlib>

// Application Specific Implementation

// Application unique identifier
const std::string MQ_APP_NAME = "/method_subscriber";

// signal handling
std::atomic<bool> g_rx_killswitch{false};

ara::log::Logger& logger()
{
    static ara::log::Logger loggerInstance = ara::log::CreateLogger("CLT", "Method client");
    return loggerInstance;
}

static void sigHandler(int f_sig)
{
    std::ignore = f_sig;
    // caught SIGINT or SIGTERM, now exit gracefully
    g_rx_killswitch = true;
}

namespace it_usrdoc = ::com::bosch::vrte::method;
namespace usrdoc
{
enum ESubscriberStates : uint8_t
{
    SM_WAIT_FOR_SERVICE = 0u,
    SM_METHOD_CALL,
    SM_METHOD_CALL_RESULT,
    SM_EXIT
};

// Implementation of Receive Function
// The Function identifier <Service-Name>Rx is only an example. Any valid C++ identifier can be use
void MethodRx()
{
    ESubscriberStates currentState = SM_WAIT_FOR_SERVICE;

    // Creation of a InstanceIdentifier of the Skeleton-Service
    ara::com::InstanceIdentifier l_instance("34343");

    // Declaration of Proxy object
    std::shared_ptr<it_usrdoc::proxy::MethodProxy> l_proxy{nullptr};
    ara::core::Future<it_usrdoc::OutputMethodIO> l_future;

    // Declaration of find service handler as lambda
    auto l_handler
        =
            [&](ara::com::ServiceHandleContainer<it_usrdoc::proxy::MethodProxy::HandleType> f_container,
                ara::com::FindServiceHandle f_handle) {
                // ignore not used f_handle parameter to avoid compiler warning
                std::ignore = f_handle;
                // iterate through the container, we only expect one "34343" instance
                for (auto item : f_container)
                {
                    logger().LogInfo() << "FS2: Found Service Instance Id: \"34343\"";
                    cout << "FS2: Found Service Instance Id: \"34343\"" << endl;
                    // we only expect take the first instance
                    std::shared_ptr<it_usrdoc::proxy::MethodProxy> proxy;
                    proxy = std::make_shared<it_usrdoc::proxy::MethodProxy>(item);

                    // publish proxy reference to eventRx thread but only l_proxy is nullptr
                    if (std::atomic_load(&l_proxy) == nullptr)
                    {
                        logger().LogInfo() << "FS2: Set proxy for Service Instance Id: \"34343\"";
                        cout << "FS2: Set proxy for Service Instance Id: \"34343\"" << endl;
                        std::atomic_store(&l_proxy, proxy);
                    }
                    else
                    {
                        logger().LogInfo()
                            << "FS2: Ignore setting proxy for Service Instance Id: \"34343\", it was already set";
                        cout << "FS2: Ignore setting proxy for Service Instance Id: \"34343\", it was already set"
                             << endl;
                    }
                    break;
                }
            };

    logger().LogInfo() << "FS2: Start find service for Instance Id: \"34343\"";
    cout << "FS2: Start find service for Instance Id: \"34343\"" << endl;
    it_usrdoc::proxy::MethodProxy::StartFindService(l_handler, l_instance);

    // Loop while the proxy is not terminated
    while (false == g_rx_killswitch)
    {
        // Sleep for a while, e.g. <TimeValue> = 2000
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));

        switch (currentState)
        {
        case SM_WAIT_FOR_SERVICE:
        {
            logger().LogInfo() << "FS2: WAIT_FOR_SERVICE";
            cout << "FS2: WAIT_FOR_SERVICE" << endl;
            if (std::atomic_load<it_usrdoc::proxy::MethodProxy>(&l_proxy) != nullptr)
            {
                // continue after lambda of handler has been called
                currentState = SM_METHOD_CALL;
            }
            else
            {
                logger().LogInfo() << "FS2: No service found. Waiting ...";
                cout << "FS2: No service found. Waiting ..." << endl;
                currentState = SM_WAIT_FOR_SERVICE;
            }
            break;
        }
        case SM_METHOD_CALL:
        {
            // Method-Specific Implementation
            // Initialize the input argument of the method
            //<in-argument> = <init-value>

            MsgRequest l_input;
            l_input.value_one[0] = 30000;
            l_input.value_one[1] = 2;
            l_input.value_one[2] = 100;
            l_input.value_two    = true;
            l_input.value_three  = 0xCAFEAFFE;

            try
            {
                logger().LogInfo() << "FS2: METHOD_CALL to Publisher";
                cout << "FS2: METHOD_CALL to Publisher" << endl;

                // execute method call
                l_future     = l_proxy->MethodIO(l_input);
                currentState = SM_METHOD_CALL_RESULT;
            }
            catch (const std::exception& exception)
            {
                // handle exception
                logger().LogInfo() << "FS2: EXCEPTION ERROR: during Method call";
                cout << "FS2: EXCEPTION ERROR: during Method call" << endl;
                currentState = SM_EXIT;
            }
            break;
        }
        case SM_METHOD_CALL_RESULT:
        {
            logger().LogInfo() << "FS2: METHOD_CALL_RESULT";
            cout << "FS2: METHOD_CALL_RESULT" << endl;

            if (l_future.wait_for(std::chrono::milliseconds(100)) == ara::core::future_status::kReady)
            {
                // access the method call result
                it_usrdoc::OutputMethodIO l_output = l_future.get();

                logger().LogInfo() << "FS2: Received out arguments from Method Publisher: "
                                   << (int)l_output.m_value_out[0] << " " << (int)l_output.m_value_out[1] << " "
                                   << (int)l_output.m_value_out[2] << " " << (int)l_output.m_value_out[3] << " "
                                   << (int)l_output.m_value_out[4];
                cout << "FS2: Received out arguments from Method Publisher: " << (int)l_output.m_value_out[0] << " "
                     << (int)l_output.m_value_out[1] << " " << (int)l_output.m_value_out[2] << " "
                     << (int)l_output.m_value_out[3] << " " << (int)l_output.m_value_out[4] << endl;
            }
            else
            {
                // wait time expired without any received response
                logger().LogInfo() << "FS2: ERROR: No response from Method Publisher";
                cout << "FS2: ERROR: No response from Method Publisher" << endl;
            }

            // exit no mather what happend
            currentState = SM_EXIT;
            break;
        }
        case SM_EXIT:
        {
            logger().LogInfo() << "FS2: EXIT -> Shutting down ...";
            cout << "FS2: EXIT -> Shutting down ..." << endl;
            g_rx_killswitch = true;
            break;
        }
        default:
            break;
        } // end switch
    }     // end while
} // end MethodRx

} // namespace usrdoc

// Implementation of the Main-Function
int main(int argc, char* argv[])
{
    // both main parameters are not used
    std::ignore = argc;
    std::ignore = argv;

    // Initialization
    auto rt = ara::core::Initialize();
    if (!rt.HasValue())
    {
        ara::core::ErrorCode ec = rt.Error();
        std::cerr << "init error: " << ec.Message() << "[" << ec.SupportData() << std::endl;
        exit(EXIT_FAILURE);
    }

    // Signal handling
    struct sigaction act;
    sigemptyset(&act.sa_mask);
    act.sa_handler = sigHandler;
    act.sa_flags   = 0;

    // monitor signals to terminate
    if (-1 == sigaction(SIGINT, &act, NULL))
    {
        logger().LogInfo() << "FS2: Calling sigaction() failed";
        cout << "FS2: Calling sigaction() failed" << endl;
        exit(EXIT_FAILURE);
    }

    if (-1 == sigaction(SIGTERM, &act, NULL))
    {
        logger().LogInfo() << "FS2: Calling sigaction() failed";
        cout << "FS2: Calling sigaction() failed" << endl;
        exit(EXIT_FAILURE);
    }

    // Runtime Initialization and connection to RouDi
    ara::Runtime::GetInstance(MQ_APP_NAME);

    // Thread Creation for each Service Transmit-Function
    std::thread runner(usrdoc::MethodRx);

    // Joining the created Threads
    runner.join();

    rt = ara::core::Deinitialize();
    if (!rt.HasValue())
    {
        ara::core::ErrorCode ec = rt.Error();
        std::cerr << "deinit error: " << ec.Message() << "[" << ec.SupportData() << std::endl;
        exit(EXIT_FAILURE);
    }

    return (EXIT_SUCCESS);
}
