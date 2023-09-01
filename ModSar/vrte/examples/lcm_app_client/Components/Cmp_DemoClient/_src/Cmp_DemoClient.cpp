/**
 **********************************************************************************************************************
 *
 * COPYRIGHT RESERVED, Robert Bosch GmbH, 2019. All rights reserved.
 * The reproduction, distribution and utilization of this document as well as the communication of its contents to
 * others without explicit authorization is prohibited. Offenders will be held liable for the payment of damages.
 * All rights reserved in the event of the grant of a patent, utility model or design.
 *
 **********************************************************************************************************************
 */

#include "Cmp_DemoClient.hpp"
#include "Cmp_DemoClientLogger.hpp"
#include <iostream>

namespace bosch
{
namespace vrte
{
namespace stm
{
namespace democlient
{

/* SysMode: Type definition and mode mapping  begin */
enum class eSysMode:uint8_t {
        kSysModeNormal      = 0U,
        kSysModeHOL         = 1U,
        kSysModeHIL         = 2U,
        kSysModeSWUpdate    = 3U,
        kSysModeDV          = 4U,
        kSysModeCF          = 5U,
        kSysModeEOL         = 6U,
        kSysModeInvalid     = 0xFEU,
        kSysModeReserved    = 0xFFU
};

const std::map<uint8_t, std::string> Cmp_DemoClient::map_sysmode2string = {
    {static_cast<uint8_t> (eSysMode::kSysModeNormal), "On"},
    {static_cast<uint8_t> (eSysMode::kSysModeHOL), "HOL"},
    {static_cast<uint8_t> (eSysMode::kSysModeHIL), "HIL"},
    {static_cast<uint8_t> (eSysMode::kSysModeSWUpdate), "SWUpdate"},
    {static_cast<uint8_t> (eSysMode::kSysModeDV), "DV"},
    {static_cast<uint8_t> (eSysMode::kSysModeCF), "CF"},
    {static_cast<uint8_t> (eSysMode::kSysModeEOL), "EOL"},
    {static_cast<uint8_t> (eSysMode::kSysModeInvalid), "Invalid"},
    {static_cast<uint8_t> (eSysMode::kSysModeReserved),  "Reserved"},
};

const std::map<std::string, uint8_t> Cmp_DemoClient::map_string2sysmode = {
    {"On", static_cast<uint8_t> (eSysMode::kSysModeNormal)},
    {"HOL", static_cast<uint8_t> (eSysMode::kSysModeHOL) },
    {"HIL", static_cast<uint8_t> (eSysMode::kSysModeHIL)},
    {"SWUpdate", static_cast<uint8_t> (eSysMode::kSysModeSWUpdate)},
    {"DV", static_cast<uint8_t> (eSysMode::kSysModeDV)},
    {"CF",  static_cast<uint8_t> (eSysMode::kSysModeCF)},
    {"EOL", static_cast<uint8_t> (eSysMode::kSysModeEOL)},
    {"Invalid", static_cast<uint8_t> (eSysMode::kSysModeInvalid)},
    {"Reserved", static_cast<uint8_t> (eSysMode::kSysModeReserved)},
};
/* SysMode: Type definition and mode mapping  begin */

/* TestMode: Type definition and mode mapping  begin */
enum class eTestMode:uint8_t {
        kTestModeNormal        = 0U,
        kTestModeStopBeatHeart = 1U,
        kSysModeReserved       = 0xFFU
};

const std::map<uint8_t, std::string> Cmp_DemoClient::map_testmode2string = {
    {static_cast<uint8_t> (eTestMode::kTestModeNormal), "On" },
    {static_cast<uint8_t> (eTestMode::kTestModeStopBeatHeart), "StopBeatHeart"},
};

const std::map<std::string, uint8_t> Cmp_DemoClient::map_string2testmode = {
    {"On", static_cast<uint8_t> (eTestMode::kTestModeNormal)},
    {"StopBeatHeart", static_cast<uint8_t> (eTestMode::kTestModeStopBeatHeart)},
};
/* TestMode: Type definition and mode mapping  end */

// Constructor
Cmp_DemoClient::Cmp_DemoClient(const ara::com::InstanceIdentifier &f_instance)
    : m_logger(ara::log::CreateLogger("DEMC", "DemoClient SoftwareComponent", ara::log::LogLevel::kVerbose))
    , m_promise()
    , m_thread()
    , m_DefaultFG_Proxy(nullptr)
    , m_SysModeFG_Proxy(nullptr)
    , setDefaultFG_Off(true)        // At startup DiagFG is Off
    , setDefaultFG_Verify(false)
    , m_proxy_Generic(nullptr)
    , m_proxy_SysModeRequest(nullptr)
    , m_proxy_TC_SysModeRequest(nullptr)
    , m_proxy_TestModeRequest(nullptr)
{
    static_cast<void>(f_instance);
    //m_logger.LogInfo() << "[Demo Client] Default constructor called";
    
    ara::com::InstanceIdentifier insIden_TriggerIn(TRIGGERIN_GENERIC_INSTANCE_ID);
    auto serviceHandlesResult_TriggerIn = bosch::vrte::sm::proxy::TriggerIn_GenericProxy::FindService(insIden_TriggerIn);
    if (serviceHandlesResult_TriggerIn.HasValue())
    {
        auto serviceHandles_TriggerIn = serviceHandlesResult_TriggerIn.Value();
        if (0 != serviceHandles_TriggerIn.size())
        {
            m_proxy_Generic = std::make_shared<bosch::vrte::sm::proxy::TriggerIn_GenericProxy>(
                serviceHandles_TriggerIn[0U]);
        }
    }

    ara::com::InstanceIdentifier insIden_TriggerInOut(TRIGGERINOUT_SYSMODE_REQUEST_INSTANCE_ID);
    auto serviceHandlesResult_TriggerInOut = ara::sm::sysmode_request::proxy::TriggerInOut_SysModeRequestProxy::FindService(insIden_TriggerInOut);
    if (serviceHandlesResult_TriggerInOut.HasValue())
    {
        auto serviceHandles_TriggerInOut = serviceHandlesResult_TriggerInOut.Value();
        if (0 != serviceHandles_TriggerInOut.size())
        {
            m_proxy_SysModeRequest = std::make_shared<ara::sm::sysmode_request::proxy::TriggerInOut_SysModeRequestProxy>(
                serviceHandles_TriggerInOut[0U]);
        }
    }

    ara::com::InstanceIdentifier insIden_TC_TriggerInOut(TRIGGERINOUT_TESTCLIENT_REQUEST_INSTANCE_ID);
    auto serviceHandlesResult_TC_TriggerInOut = ara::sm::testclient_request::proxy::TriggerInOut_TestClientRequestProxy::FindService(insIden_TC_TriggerInOut);
    if (serviceHandlesResult_TC_TriggerInOut.HasValue())
    {
        auto serviceHandles_TC_TriggerInOut = serviceHandlesResult_TC_TriggerInOut.Value();
        if (0 != serviceHandles_TC_TriggerInOut.size())
        {
            m_proxy_TC_SysModeRequest = std::make_shared<ara::sm::testclient_request::proxy::TriggerInOut_TestClientRequestProxy>(
                serviceHandles_TC_TriggerInOut[0U]);
        }
    }

    ara::com::InstanceIdentifier insIden_TestMode_TriggerInOut(TRIGGERINOUT_TESTMODE_REQUEST_INSTANCE_ID);
    auto serviceHandlesResult_TestMode_TriggerInOut = ara::sm::testmode_request::proxy::TriggerInOut_TestModeRequestProxy::FindService(
        insIden_TestMode_TriggerInOut);

    if (serviceHandlesResult_TestMode_TriggerInOut.HasValue())
    {
        auto serviceHandles_TestMode_TriggerInOut = serviceHandlesResult_TestMode_TriggerInOut.Value();
        if (0 != serviceHandles_TestMode_TriggerInOut.size())
        {
            m_proxy_TestModeRequest = std::make_shared<ara::sm::testmode_request::proxy::TriggerInOut_TestModeRequestProxy>(
                serviceHandles_TestMode_TriggerInOut[0U]);
        }
    }
}

// Deconstructor
Cmp_DemoClient::~Cmp_DemoClient()
{
    m_logger.LogInfo() << "[Demo Client] Deconstructor called";

    // if (m_thread.joinable())
    // {
    //     m_thread.join();
    // }
}

int32_t Cmp_DemoClient::Init()
{
    m_logger.LogInfo() << "Cmp_DemoClient::Init()";

    findAndSubscribeDefaultFG();
    findAndSubscribeSysModeFG();

    /* set log*/
    std::string appId = "DEMC";
    bosch::vrte::stm::democlient::CDemoClientAppLogger::setAppId(appId);

    //set component client
    m_DemoClientComponentClient= std::shared_ptr<CDemoClientComponentClientImpl> (new CDemoClientComponentClientImpl("ExampleApp", "ExampleComponent", "2"));
    if (nullptr != m_DemoClientComponentClient)
    {
        m_DemoClientComponentClient->vInit();
        m_DemoClientComponentClient->vStart();
    }
    else
    {

    }

    return 0;
}

// overrides the function of IComponent-Interface
int32_t Cmp_DemoClient::Run()
{
    m_logger.LogInfo() << "[Demo Client] Run(): Method called";

    // Start thread
    if (m_thread.joinable() == false)
    {
        m_thread = std::thread(&Cmp_DemoClient::Task, this, std::move(m_promise.get_future()));
        m_thread.detach();
        m_logger.LogInfo() << "[Demo Client] Run(): Thread created";
    }
    else
    {
        // in this case the thread is already running. Nothing to do here.
        m_logger.LogInfo() << "[Demo Client] Run(): Thread already running!";
    }

    return 0;
}

// overrides the function of IComponent-Interface
int32_t Cmp_DemoClient::Shutdown()
{
    m_logger.LogInfo() << "[Demo Client] Shutdown(): Method called";

    /* 	Other applications should call StopOfferService() on their skeletons here.
        Check in other examples to see
    */
    m_logger.LogInfo() << "[Demo Client] Joining threads";

    if (m_thread.joinable())
    {
        m_promise.set_value(1U);    // will cause MISRA errors
        m_thread.join();
        m_logger.LogInfo() << "[Demo Client] Threads successfully joined";
    }
    else
    {
        // Thread is not joinable. Probably join() was called before? Print an error.
        m_logger.LogError() << "[Demo Client] Threads could not be joined";
        return -1;
    }

    return 0;
}

void Cmp_DemoClient::Task(std::future<int32_t> &&future)    //  MISRA A8-4-8
{
    int64_t input = 0;
    m_logger.LogInfo() << "[Demo Client] Task()";

    auto start{std::chrono::high_resolution_clock::now()};

    //while ((true) && (setDefaultFG_Verify == false))
    bool exitProgram_Flag = false;
    while (!exitProgram_Flag)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(3000));
        int64_t input;
        std::cout<<std::endl;
        std::cout << "Please select the test mode by input Integer value: "<< std::endl;
        std::cout << " Default FG: Verify = 1, Calibrate = 2, On = 3"<< std::endl;
        std::cout << " SysMode FG: On = 4, HOL = 5, HIL = 6, SWUpdate = 7" << std::endl;
        std::cout << "             DV = 8, CF = 9, EOL = 10" << std::endl;

        std::cout << " GetSysModeState: 20" << std::endl;
        std::cout << " Set SysMode to Invalid state: 21" << std::endl;
        std::cout << " Get SysMode for Invalid state: 22" << std::endl;
        std::cout << " Set Soc to stop send beatheart to mcu: 23" << std::endl;

        std::cout << " SetCmState: On = 30 " << std::endl;
        std::cout << " GetCmState: 31" << std::endl;
        std::cout << " SetOsmState: Diagnostic = 32, Calibrate = 33, Update = 34, Run = 35, Shutdown = 36" <<std::endl;
        std::cout << " Input Ctrl+C to exit" <<std::endl;
        std::cout<<std::endl;
        std::cin >> input;

        // Check if the future object holds a valid shared state (only valid if it has been set by promise
        // before) Also wait for 500ms (compared to timestamp at loop beginning)
        std::cout << "input:  " << input << &std::endl;

        switch (input)
        {
            case 0:
                std::cout<< "Exit test program ......" <<std::endl;
                exitProgram_Flag = true;
                break;
            case 1:
                if ((checkAndHandleDefaultFG() == SERVICE_OKAY))
                {
                    std::cout << "default function group Verify selected" << &std::endl;
                    this->vSetStateDefaultFg("Verify");
                    this->setDefaultFG_Off = false;
                    //setDefaultFG_Verify = true;
                    //test = 0;
                }
                else
                {
                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                }
                break;
            case 2:
                if ((checkAndHandleDefaultFG() == SERVICE_OKAY))
                {
                    std::cout << "default function group Calibrate selected" << &std::endl;
                    this->vSetStateDefaultFg("Calibrate");
                    this->setDefaultFG_Off = false;
                    //setDefaultFG_Verify = true;
                    //test = 0;
                }
                else
                {
                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                }
                break;
            case 3:
                if ((checkAndHandleDefaultFG() == SERVICE_OKAY))
                {
                    std::cout << "default function group On selected" << &std::endl;
                    this->vSetStateDefaultFg("On");
                    this->setDefaultFG_Off = false;
                    //setDefaultFG_Verify = true;
                    //test = 0;
                }
                else
                {
                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                }
                break;
            case 4:
                if ((checkAndHandleSysModeFG() == SERVICE_OKAY))
                {
                    std::cout << "SysMode function group On selected" << &std::endl;
                    this->vSetSysMode("On");
                    this->setDefaultFG_Off = false;
                    //setDefaultFG_Verify = true;
                }
                else
                {
                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                }
                break;
            case 5:
                if ((checkAndHandleSysModeFG() == SERVICE_OKAY))
                {
                    std::cout << "SysMode function group HOL selected" << &std::endl;
                    this->vSetSysMode("HOL");
                    this->setDefaultFG_Off = false;
                    //setDefaultFG_Verify = true;
                }
                else
                {
                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                }
                break;
            case 6:
                if ((checkAndHandleSysModeFG() == SERVICE_OKAY))
                {
                    std::cout << "SysMode function group HIL selected" << &std::endl;
                    this->vSetSysMode("HIL");
                    this->setDefaultFG_Off = false;
                    //setDefaultFG_Verify = true;
                }
                else
                {
                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                }
                break;
            case 7:
                if ((checkAndHandleSysModeFG() == SERVICE_OKAY))
                {
                    std::cout << "SysMode function group SWUpdate selected" << &std::endl;
                    this->vSetSysMode("SWUpdate");
                    this->setDefaultFG_Off = false;
                    //setDefaultFG_Verify = true;
                }
                else
                {
                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                }
                break;
            case 8:
                if ((checkAndHandleSysModeFG() == SERVICE_OKAY))
                {
                    std::cout << "SysMode function group DV selected" << &std::endl;
                    this->vSetSysMode("DV");
                    this->setDefaultFG_Off = false;
                    //setDefaultFG_Verify = true;
                }
                else
                {
                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                }
                break;
            case 9:
                if ((checkAndHandleSysModeFG() == SERVICE_OKAY))
                {
                    std::cout << "SysMode function group CF selected" << &std::endl;
                    this->vSetSysMode("CF");
                    this->setDefaultFG_Off = false;
                    //setDefaultFG_Verify = true;
                }
                else
                {
                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                }
                break;
            case 10:
                if ((checkAndHandleSysModeFG() == SERVICE_OKAY))
                {
                    std::cout << "SysMode function group EOL selected" << &std::endl;
                    this->vSetSysMode("EOL");
                    this->setDefaultFG_Off = false;
                    //setDefaultFG_Verify = true;
                }
                else
                {
                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                }
                break;

            case 20:
                {
                    std::cout << "GetSysModeState " << &std::endl;
                    vGetSysModeState();
                }
                break;
            case 21:
                {
                    std::cout << "Set sysmode state to Invalid" << &std::endl;
                    std::string setState{"Invalid"};
                    vTCSetSysMode(setState);
                }
                break;
            case 22:
                {
                    std::cout << "vTCGetSysModeState get sysmode for Invalid state" << &std::endl;
                    vTCGetSysModeState();
                }
                break;
            case 23:
                {
                    std::cout << "Set TestMode state to StopBeatHeart" << &std::endl;
                    std::string setState{"StopBeatHeart"};
                    vSetTestMode(setState);
                }
                break;

           case 30:
                //if ((checkAndHandleDefaultFG() == SERVICE_OKAY))
                {
                    std::cout << "SetCmState ExampleComponent On " << &std::endl;
                    this->vSetCmState("ExampleComponent","On");
                    //setDefaultFG_Verify = true;
                }
                {
                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                }
                break;
           case 31:
                {
                    std::cout << "GetCmState " << &std::endl;
                    //this->vSetOsmState("Shutdown");
                    //setDefaultFG_Verify = true;
                }
                {
                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                }
                break;
           case 32:
                //if ((checkAndHandleDefaultFG() == SERVICE_OKAY))
                {
                    std::cout << "SetOsmState Diagnostic " << &std::endl;
                    this->vSetOsmState("Diagnostic");
                    //setDefaultFG_Verify = true;
                }
                {
                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                }
                break;
           case 33:
                //if ((checkAndHandleDefaultFG() == SERVICE_OKAY))
                {
                    std::cout << "SetOsmState Calibrate " << &std::endl;
                    this->vSetOsmState("Calibrate");
                    //setDefaultFG_Verify = true;
                }
                {
                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                }
                break;
           case 34:
                //if ((checkAndHandleDefaultFG() == SERVICE_OKAY))
                {
                    std::cout << "SetOsmState Update " << &std::endl;
                    this->vSetOsmState("Update");
                    //setDefaultFG_Verify = true;
                }
                {
                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                }
                break;
           case 35:
                //if ((checkAndHandleDefaultFG() == SERVICE_OKAY))
                {
                    std::cout << "SetOsmState Run " << &std::endl;
                    this->vSetOsmState("Run");
                    //setDefaultFG_Verify = true;
                }
                {
                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                }
                break;
           case 36:
                //if ((checkAndHandleDefaultFG() == SERVICE_OKAY))
                {
                    std::cout << "SetOsmState Shutdown " << &std::endl;
                    this->vSetOsmState("Shutdown");
                    //setDefaultFG_Verify = true;
                }
                {
                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                }
                break;
            default:
                std::cout<< "Invalid select, please reselect!!!" << &std::endl;
                break;
        }
    }
}

void Cmp_DemoClient::vSetStateDefaultFg(std::string f_state)
{
    m_logger.LogInfo() << "[TriggerInOut_StateDefaultFG_Proxy] vSetStateDefaultFg(): Start method";
    ara::sm::FunctionGroupStateType fg_state_data{f_state};
    m_DefaultFG_Proxy->Trigger.Set(fg_state_data);
    m_logger.LogInfo() << "[TriggerInOut_StateDefaultFG_Proxy] vSetStateDefaultFg(): End method";
}

void Cmp_DemoClient::vSetStateSysModeFg(std::string f_state)
{
    m_logger.LogInfo() << "[TriggerInOut_StateSysModeFG_Proxy] vSetStateSysModeFg(): Start method";
    ara::sm::FunctionGroupStateType fg_state_data{f_state};
    m_SysModeFG_Proxy->Trigger.Set(fg_state_data);
    m_logger.LogInfo() << "[TriggerInOut_StateSysModeFG_Proxy] vSetStateSysModeFg(): End method";
}

bool Cmp_DemoClient::checkAndHandleSysModeFG(void)
{
    bool returnval{false};

    if (nullptr == m_SysModeFG_Proxy)
    {
        returnval = findAndSubscribeSysModeFG();
    }
    else
    {
        returnval = checkSubscriptionSysModeFG();
    }

    return returnval;

}

bool Cmp_DemoClient::findAndSubscribeSysModeFG(void)
{
    bool returnval{false};
    m_logger.LogInfo() << "[m_SysModeFG_Proxy SysModeFG] findAndSubscribeSysModeFG(): Method start";

    // initialize m_DefaultFG_Proxy, if it hasn't been done before
    if (nullptr == m_SysModeFG_Proxy)
    {
        m_logger.LogInfo() << "[m_SysModeFG_Proxy SysModeFG] findAndSubscribeSysModeFG(): Create instance";
        ara::com::InstanceIdentifier l_SysModeinstance("1");

        // Do a onetime shot to find service
        auto serviceHandlesResult =
            ara::sm::sysmode_fg::proxy::TriggerInOut_StateSysModeFGProxy::FindService(l_SysModeinstance);
        if (serviceHandlesResult.HasValue())
        {
            // Take the service that was found first
            auto serviceHandles = serviceHandlesResult.Value();
            if (0 != serviceHandles.size())
            {
                m_logger.LogInfo() << "[m_SysModeFG_Proxy SysModeFG] findAndSubscribeSysModeFG(): Service found";

                m_SysModeFG_Proxy = std::shared_ptr<ara::sm::sysmode_fg::proxy::TriggerInOut_StateSysModeFGProxy>(
                    new ara::sm::sysmode_fg::proxy::TriggerInOut_StateSysModeFGProxy(serviceHandles[0]));
                m_SysModeFG_Proxy->Notifier.Subscribe(1U);
                m_SysModeFG_Proxy->Notifier.SetReceiveHandler(static_cast<ara::com::EventReceiveHandler>(
                    std::bind(&Cmp_DemoClient::receiveFieldEventCallbackSysModeFG, this)));

                returnval = checkSubscriptionSysModeFG();
            }
            else
            {
                 m_logger.LogError() << "serviceHandles.size() equals 0 , SubscribeSysModeFG Failed!";
            }
        }
        else
        {
            m_logger.LogDebug() << "[m_SysModeFG_Proxy SysModeFG] findAndSubscribeSysModeFG(): Service not found";
        }
    }
    m_logger.LogInfo() << "[m_SysModeFG_Proxy SysModeFG] findAndSubscribeSysModeFG(): Method end";

    return returnval;

}

bool Cmp_DemoClient::checkSubscriptionSysModeFG(void)
{
    bool returnval{false};

    if (ara::com::SubscriptionState::kSubscribed != m_SysModeFG_Proxy->Notifier.GetSubscriptionState())
    {
        m_logger.LogDebug() << "[TriggerInOut_StateSysModeFG_Proxy] checkSubscriptionSysModeFG(): Subscription lost";
    }
    else
    {
        m_logger.LogInfo() << "[TriggerInOut_StateSysModeFG_Proxy] checkSubscriptionSysModeFG(): Service okay";
        returnval = SERVICE_OKAY;
    }

    return returnval;

}

void Cmp_DemoClient::receiveFieldEventCallbackSysModeFG(void)
{
    if (checkAndHandleSysModeFG() == SERVICE_OKAY)
    {
        ara::sm::FunctionGroupStateResultType temp;
        auto result = m_SysModeFG_Proxy->Notifier.GetNewSamples(
            [&temp](const ara::com::SamplePtr<const ara::sm::FunctionGroupStateResultType> l_samples)
            {
                temp = *l_samples;    // alternative: temp.FGStateinResult = l_samples-> FGStateinResult; FGError
            });
        if (result.HasValue())
        {
            m_logger.LogInfo()
                << "[TriggerInOut_StateSysModeFG_Proxy] receiveFieldEventCallbackSysModeFG(): Values received from STM";
            switch (static_cast<uint8_t>(temp.FGError))
            {
                case 0U:
                    m_logger.LogInfo() << "[TriggerInOut_StateSysModeFG_Proxy] receiveFieldEventCallbackSysModeFG(): "
                                          "FunctionGroup State change request was executed successfully";
                    //setDefaultFG_Verify = true;
                    //std::cout << "FunctionGroup State change request was executed successfully" << &std::endl;
                    break;
                case 1U:
                    m_logger.LogInfo() << "[TriggerInOut_StateSysModeFG_Proxy] receiveFieldEventCallbackSysModeFG(): "
                                          "FunctionGroup State change request was invalid e,g, unknown state";
                    //std::cout << "FunctionGroup State change request was invalid e,g, unknown state" << &std::endl;
                    break;
                case 2U:
                    m_logger.LogInfo() << "[TriggerInOut_StateSysModeFG_Proxy] receiveFieldEventCallbackSysModeFG(): "
                                          "FunctionGroup State change request failed due to other reason";
                    //std::cout << "FunctionGroup State change request failed due to other reason" << &std::endl;
                    break;
                default:
                    m_logger.LogError()
                        << "[TriggerInOut_StateSysModeFG_Proxy] receiveFieldEventCallbackSysModeFG(): Unknown value";
                    //std::cout << "unknown value" << &std::endl;
                    break;
            }
        }
        else
        {
            m_logger.LogError()
                << "[TriggerInOut_StateSysModeFG_Proxy] receiveFieldEventCallbackSysModeFG(): No values received from STM";
            //std::cout << "no values received from STM" << &std::endl;
        }
    }
}

bool Cmp_DemoClient::checkAndHandleDefaultFG(void)
{
    bool returnval{false};

    if (nullptr == m_DefaultFG_Proxy)
    {
        // Returns SERRVICE_OKAY (true), when subscribed to service
        returnval = findAndSubscribeDefaultFG();
    }
    else
    {
        // Returns SERRVICE_OKAY (true), when subscribed to service
        returnval = checkSubscriptionDefaultFG();
    }

    return returnval;
}

bool Cmp_DemoClient::findAndSubscribeDefaultFG(void)
{
    bool returnval{false};
    m_logger.LogInfo() << "[m_DefaultFG_Proxy DefaultFG] findAndSubscribeDefaultFG(): Method start";

    // initialize m_DefaultFG_Proxy, if it hasn't been done before
    if (nullptr == m_DefaultFG_Proxy)
    {
        m_logger.LogInfo() << "[m_DefaultFG_Proxy DefaultFG] findAndSubscribeDefaultFG(): Create instance";
        ara::com::InstanceIdentifier l_instance("1");

        // Do a onetime shot to find service
        auto serviceHandlesResult =
            ara::sm::default_fg::proxy::TriggerInOut_StateDefaultFGProxy::FindService(l_instance);
        if (serviceHandlesResult.HasValue())
        {
            // Take the service that was found first
            auto serviceHandles = serviceHandlesResult.Value();
            if (0 != serviceHandles.size())
            {
                m_logger.LogInfo() << "[m_DefaultFG_Proxy DefaultFG] findAndSubscribeDefaultFG(): Service found";

                m_DefaultFG_Proxy = std::shared_ptr<ara::sm::default_fg::proxy::TriggerInOut_StateDefaultFGProxy>(
                    new ara::sm::default_fg::proxy::TriggerInOut_StateDefaultFGProxy(serviceHandles[0]));
                m_DefaultFG_Proxy->Notifier.Subscribe(1U);
                m_DefaultFG_Proxy->Notifier.SetReceiveHandler(static_cast<ara::com::EventReceiveHandler>(
                    std::bind(&Cmp_DemoClient::receiveFieldEventCallbackDefaultFG, this)));

                returnval = checkSubscriptionDefaultFG();    // Returns SERRVICE_OKAY (true), when subscribed to service
            }
        }
        else
        {
            m_logger.LogDebug() << "[m_DefaultFG_Proxy DefaultFG] findAndSubscribeDefaultFG(): Service not found";
        }
    }
    m_logger.LogInfo() << "[m_DefaultFG_Proxy DefaultFG] findAndSubscribeDefaultFG(): Method end";

    return returnval;

}

bool Cmp_DemoClient::checkSubscriptionDefaultFG(void)
{
    bool returnval{false};

    if (ara::com::SubscriptionState::kSubscribed != m_DefaultFG_Proxy->Notifier.GetSubscriptionState())
    {
        m_logger.LogDebug() << "[TriggerInOut_StateDefaultFG_Proxy] checkSubscriptionDefaultFG(): Subscription lost";
    }
    else
    {
        m_logger.LogInfo() << "[TriggerInOut_StateDefaultFG_Proxy] checkSubscriptionDefaultFG(): Service okay";
        returnval = SERVICE_OKAY;
    }

    return returnval;

}

void Cmp_DemoClient::receiveFieldEventCallbackDefaultFG(void)
{
    if (checkAndHandleDefaultFG() == SERVICE_OKAY)
    {
        ara::sm::FunctionGroupStateResultType temp;
        auto result = m_DefaultFG_Proxy->Notifier.GetNewSamples(
            [&temp](const ara::com::SamplePtr<const ara::sm::FunctionGroupStateResultType> l_samples)
            {
                temp = *l_samples;    // alternative: temp.FGStateinResult = l_samples-> FGStateinResult; FGError
            });
        if (result.HasValue())
        {
            m_logger.LogInfo()
                << "[TriggerInOut_StateDefaultFG_Proxy] receiveFieldEventCallbackDefaultFG(): Values received from STM";
            switch (static_cast<uint8_t>(temp.FGError))
            {
                case 0U:
                    m_logger.LogInfo() << "[TriggerInOut_StateDefaultFG_Proxy] receiveFieldEventCallbackDefaultFG(): "
                                          "FunctionGroup State change request was executed successfully";
                    setDefaultFG_Verify = true;
                    //std::cout << "FunctionGroup State change request was executed successfully" << &std::endl;
                    break;
                case 1U:
                    m_logger.LogInfo() << "[TriggerInOut_StateDefaultFG_Proxy] receiveFieldEventCallbackDefaultFG(): "
                                          "FunctionGroup State change request was invalid e,g, unknown state";
                    //std::cout << "FunctionGroup State change request was invalid e,g, unknown state" << &std::endl;
                    break;
                case 2U:
                    m_logger.LogInfo() << "[TriggerInOut_StateDefaultFG_Proxy] receiveFieldEventCallbackDefaultFG(): "
                                          "FunctionGroup State change request failed due to other reason";
                    //std::cout << "FunctionGroup State change request failed due to other reason" << &std::endl;
                    break;
                default:
                    m_logger.LogError()
                        << "[TriggerInOut_StateDefaultFG_Proxy] receiveFieldEventCallbackDefaultFG(): Unknown value";
                    //std::cout << "unknown value" << &std::endl;
                    break;
            }
        }
        else
        {
            m_logger.LogError()
                << "[TriggerInOut_StateDefaultFG_Proxy] receiveFieldEventCallbackDefaultFG(): No values received from STM";
            //std::cout << "no values received from STM" << &std::endl;
        }
    }
}


void Cmp_DemoClient::vSetOsmState(std::string f_state)
{
    m_logger.LogInfo() << " vSetOsmState " << f_state;
    bosch::vrte::sm::GenericStateRequestType state_data;
    state_data.requestType = bosch::vrte::sm::RequestedSubComponentType::kOsm;
    state_data.osmState    = RequestedOsmStateTypeMap[f_state];
    m_proxy_Generic->Trigger.Set(state_data);
}

void Cmp_DemoClient::vSetCmState(std::string f_name, std::string f_state)
{
    m_logger.LogInfo() << " vSetCmState with component " << f_name << " and State is " << f_state;
    bosch::vrte::sm::GenericStateRequestType state_data;
    state_data.requestType = bosch::vrte::sm::RequestedSubComponentType::kCm;
    state_data.cmState.componentName = f_name;
    state_data.cmState.requestedState = f_state;
    m_proxy_Generic->Trigger.Set(state_data);
}

void Cmp_DemoClient::vSetSysMode(std::string f_state)
{
    m_logger.LogInfo() << " vSetCmState enter: ";

    //0: On, 1: HOL, 2: HIL
    ara::sm::SysModeType set_SysMode;
    set_SysMode = static_cast<ara::sm::SysModeType>(eSysMode::kSysModeNormal);

    auto it = map_string2sysmode.find(f_state);
    if (it != map_string2sysmode.end())
    {
        set_SysMode = static_cast<ara::sm::SysModeType>(it->second);
    }

    m_proxy_SysModeRequest->SysModeRequest.Set(set_SysMode);
}

void Cmp_DemoClient::vGetSysModeState(void)
{
    m_logger.LogInfo() << " vGetSysModeState enter: ";

    //0: On, 1: HOL, 2: HIL
    auto req = m_proxy_SysModeRequest->SysModeRequestResult.Get();
    auto res = req.get();
    auto curSysMode = static_cast<uint8_t>(res.SysModeSetCurVal);
    auto perSysMode = static_cast<uint8_t>(res.SysModeSetPerVal);

    auto itCur = map_sysmode2string.find(curSysMode);
    if (itCur != map_sysmode2string.end())
    {
        std::cout << " Current SysModeState: " << (itCur->second);
    } else {
        std::cout << " Current SysModeState: Unknow SysMode State";
    }

    auto itPer = map_sysmode2string.find(perSysMode);
    if (itPer != map_sysmode2string.end())
    {
        std::cout << " , Current Persistency SysModeState: " << (itPer->second) << std::endl;
    } else {
        std::cout << " , Current Persistency SysModeState: Unknow SysMode State" << std::endl;
    }

    m_logger.LogInfo() << "  SysModeSetCurVal " << static_cast<uint8_t>(curSysMode) << " SysModeSetPerVal " << static_cast<uint8_t>(perSysMode);
}

void Cmp_DemoClient::vTCSetSysMode(std::string& f_state)
{
    m_logger.LogInfo() << " vGetSysModeState enter: ";

    //0: On, 1: HOL, 2: HIL
    ara::sm::TC_SysModeType set_SysMode;
    set_SysMode = static_cast<ara::sm::TC_SysModeType>(eSysMode::kSysModeNormal);

    auto it = map_string2sysmode.find(f_state);
    if (it != map_string2sysmode.end())
    {
        set_SysMode = static_cast<ara::sm::TC_SysModeType>(it->second);
    }

    m_proxy_TC_SysModeRequest->TestClientRequest.Set(set_SysMode);
}

// get m_proxy_TC_SysModeRequest sysmode state
void Cmp_DemoClient::vTCGetSysModeState(void)
{
    m_logger.LogInfo() << " vTCGetSysModeState enter: ";

    //0: On, 1: HOL, 2: HIL
    auto req = m_proxy_TC_SysModeRequest->TestClientRequestResult.Get();
    auto res = req.get();
    auto curSysMode = static_cast<uint8_t>(res.SysModeSetCurVal);
    auto perSysMode = static_cast<uint8_t>(res.SysModeSetPerVal);

    auto itCur = map_sysmode2string.find(curSysMode);
    if (itCur != map_sysmode2string.end())
    {
        std::cout << " Current SysModeState: " << (itCur->second);
    } else {
        std::cout << " Current SysModeState: Unknow SysMode State";
    }

    auto itPer = map_sysmode2string.find(perSysMode);
    if (itPer != map_sysmode2string.end())
    {
        std::cout << " , Current Persistency SysModeState: " << (itPer->second) << std::endl;
    } else {
        std::cout << " , Current Persistency SysModeState: Unknow SysMode State" << std::endl;
    }

    m_logger.LogInfo() << "  SysModeSetCurVal " << static_cast<uint8_t>(curSysMode) << " SysModeSetPerVal " << static_cast<uint8_t>(perSysMode);
}

void Cmp_DemoClient::vSetTestMode(std::string f_state)
{
    std::cout << "vSetTestMode enter";
    m_logger.LogInfo() << " vSetTestMode enter: ";

    //0: On, 1: StopBeatHeart
    ara::sm::TestModeType set_TestMode;
    set_TestMode = static_cast<ara::sm::TestModeType>(eTestMode::kTestModeNormal);

    auto it = map_string2testmode.find(f_state);
    if (it != map_string2testmode.end())
    {
        set_TestMode = static_cast<ara::sm::TestModeType>(it->second);
    }

    m_proxy_TestModeRequest->TestModeRequest.Set(set_TestMode);
}

}  // namespace demoserver
}  // namespace stm
}  // namespace vrte
}  // namespace bosch
