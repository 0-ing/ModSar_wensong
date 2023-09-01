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
/// @file      publisher.cpp
/// @brief     Method publisher example application
/// @copyright Robert Bosch GmbH 2021
//=============================================================================
// Standard C++/C Header files used for thread, time and signal handling
#include <chrono>
#include <csignal>
#include <thread>

//
#include <iostream>

//
using std::cout;
using std::endl;

// General Types Header-File
#include "ara/com/types.h"

// ara core and ara logging headers
#include "ara/core/error_code.h"
#include "ara/core/initialization.h"
#include "ara/core/result.h"
#include "ara/log/logger.h"

// Include Header-Files of the generated Skeleton-Service
#include "com/bosch/vrte/method/method_skeleton.h"

// Include implementation specific Header-Files, for instance
#include <fstream>

// Application Specific Implementation

// Application unique identifier
const std::string MQ_APP_NAME = "/method_publisher"; // unique identifier

// signal handling
std::atomic<bool> g_tx_killswitch{false};

ara::log::Logger& logger()
{
    static ara::log::Logger loggerInstance = ara::log::CreateLogger("SERV", "Method server");
    return loggerInstance;
}

static void sigHandler(int f_sig)
{
    std::ignore = f_sig;
    // caught SIGINT or SIGTERM, now exit gracefully
    g_tx_killswitch = true;
}

bool fs1_was_called = false;

// Method-Specific Implementation: Subclassing the generated Skeleton-Service class
// SubClassing the Skeleton-Service class

// The Class identifier Sample<ServiceInterface-Name>Skeleton is only an example. Any valid C++ identifier can be used
class SampleMethodSkeleton : public com::bosch::vrte::method::skeleton::MethodSkeleton
{
public:
    ~SampleMethodSkeleton()
    {
    }
    SampleMethodSkeleton(const ara::com::InstanceIdentifier& f_instance)
        : com::bosch::vrte::method::skeleton::MethodSkeleton(f_instance)
    {
    }

    // method with result (request/response)

    // This function will be called when method call is done in the subscriber side
    // all <in-parameter> and <out-argument> and their datatype are defined in the hadl and/or arxml files
    ara::core::Future<com::bosch::vrte::method::OutputMethodIO> MethodIO(const MsgRequest input)
    {
        // Implement what you want to do with the input value

        // Set the output data of the method (response)
        struct com::bosch::vrte::method::OutputMethodIO output = {};

        logger().LogInfo() << "FS1: ---------------------Methods--------------------- \n";
        cout << "FS1: ---------------------Methods--------------------- \n" << endl;

        for (uint16_t i = 0; i < 3; i++)
        {
            logger().LogInfo() << "FS1: Input: " << (int)input.value_one[i];
            cout << "FS1: Input: " << (int)input.value_one[i] << endl;
        }
        logger().LogInfo() << "FS1: Input: " << (int)input.value_two;
        cout << "FS1: Input: " << (int)input.value_two << endl;
        logger().LogInfo() << "FS1: Input: " << std::hex << input.value_three;
        cout << "FS1: Input: " << std::hex << input.value_three << endl;
        logger().LogInfo() << std::dec;
        cout << std::dec << endl;

        fs1_was_called = true;

        // This shall be done for all <out_argument>
        output.m_res_out   = true;
        output.m_value_out = {1, 2, 3, 4, 5};

        // create promise of type Output<Method-Name> - see <Service-Name>_common.h
        ara::core::Promise<com::bosch::vrte::method::OutputMethodIO> l_promise;

        // set value of promise
        l_promise.set_value(output);

        // return the method response
        return l_promise.get_future();
    }
};

// Transmit-Function Implementation for the Service-Skeleton
void MethodTx()
{
    // Creation of a InstanceIdentifier of the Skeleton-Service
    ara::com::InstanceIdentifier l_instance("34343");

    logger().LogInfo() << "FS1: MethodSkeleton - OfferService";
    cout << "FS1: MethodSkeleton - OfferService" << endl;

    // Instantiation of the Service with the created InstanceIdentifier
    SampleMethodSkeleton l_skeleton(l_instance);

    // Offer the instantiated service
    l_skeleton.OfferService();

    // Loop while the skeleton is not terminated
    while (false == g_tx_killswitch)
    {
        // sleep for a while, for instance <TimeValue> = 2000
        std::this_thread::sleep_for(std::chrono::milliseconds(10000u));

        // subscriber had 10s to find the publisher service and call the MethodIO remotely

        // only go thru this loop once
        g_tx_killswitch = true;
    }

    // Stop Offer the ServiceInstance
    l_skeleton.StopOfferService();
}

// Main-Function Implementation
int main()
{
    // Initialization
    auto rt = ara::core::Initialize();
    if (!rt.HasValue())
    {
        ara::core::ErrorCode ec = rt.Error();
        std::cerr << "init error: " << ec.Message() << "[" << ec.SupportData() << std::endl;
        exit(EXIT_FAILURE);
    }

    // Signal handling

    // register sigHandler for SIGINT and SIGTERM
    struct sigaction act;
    sigemptyset(&act.sa_mask);
    act.sa_handler = sigHandler;
    act.sa_flags   = 0;

    // monitor signals to terminate
    if (-1 == sigaction(SIGINT, &act, NULL))
    {
        logger().LogInfo() << "FS1: Calling sigaction() failed";
        cout << "FS1: Calling sigaction() failed" << endl;
        exit(EXIT_FAILURE);
    }

    if (-1 == sigaction(SIGTERM, &act, NULL))
    {
        logger().LogInfo() << "FS1: Calling sigaction() failed";
        cout << "FS1: Calling sigaction() failed" << endl;
        exit(EXIT_FAILURE);
    }

    // Runtime Initialization and connection to RouDi
    ara::Runtime::GetInstance(MQ_APP_NAME);

    // Thread Creation for each Service Transmit-Function
    std::thread mtx(MethodTx);

    // Joining the created Threads
    mtx.join();

    rt = ara::core::Deinitialize();
    if (!rt.HasValue())
    {
        ara::core::ErrorCode ec = rt.Error();
        std::cerr << "deinit error: " << ec.Message() << "[" << ec.SupportData() << std::endl;
        exit(EXIT_FAILURE);
    }

    return (EXIT_SUCCESS);
}
