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

#ifndef Cmp_DemoClient_H_
#define Cmp_DemoClient_H_

/* Include std libraries */
#include <thread>
#include <csignal>
#include <cstdlib>
#include <future>
#include <cstdint>
#include <functional>

/* Include generated proxy-skeletons and impl_types*/
#include "ara/sm/sysmode_request/triggerinout_sysmoderequest_proxy.h"
#include "ara/sm/default_fg/triggerinout_statedefaultfg_proxy.h"
#include "ara/sm/sysmode_fg/triggerinout_statesysmodefg_proxy.h"
#include "ara/sm/triggerout_componentstatestatus_proxy.h"
#include "ara/sm/testclient_request/triggerinout_testclientrequest_proxy.h"
#include "ara/sm/testmode_request/triggerinout_testmoderequest_proxy.h"
#include "bosch/vrte/sm/triggerin_generic_proxy.h"
#include "Cmp_DemoClientComponentClientImpl.hpp"
/* Include ara-libs */
#include <ara/log/logger.h>

/* Include the common Interface IComponentSwc */
#include "IComponentSwc.hpp"

using defaultfgresultnotifier_callback_t = std::function<void(std::string, uint8_t)>;

namespace bosch
{
namespace vrte
{
namespace stm
{
namespace democlient
{

static const bool SERVICE_OKAY{true};

static std::map<std::string, bosch::vrte::sm::RequestedOsmStateType> RequestedOsmStateTypeMap = {
    {"Init", bosch::vrte::sm::RequestedOsmStateType::kInit},
    {"Run", bosch::vrte::sm::RequestedOsmStateType::kRun},
    {"Update", bosch::vrte::sm::RequestedOsmStateType::kUpdate},
    {"Calibrate", bosch::vrte::sm::RequestedOsmStateType::kCalibrate},
    {"Diagnostic", bosch::vrte::sm::RequestedOsmStateType::kDiagnostic},
    {"PrepareShutdown", bosch::vrte::sm::RequestedOsmStateType::kPrepareShutdown},
    {"Shutdown", bosch::vrte::sm::RequestedOsmStateType::kShutdown},
//    {"Sentry", bosch::vrte::sm::RequestedOsmStateType::kSentry},
  };

// Instance Id of the offered interface
const ara::core::StringView TRIGGERIN_GENERIC_INSTANCE_ID = "1";
const ara::core::StringView TRIGGERINOUT_SYSMODE_REQUEST_INSTANCE_ID = "1";
const ara::core::StringView TRIGGERINOUT_CM_STATE_STATUS_INSTANCE_ID = "2";
const ara::core::StringView TRIGGERINOUT_TESTCLIENT_REQUEST_INSTANCE_ID = "1";
const ara::core::StringView TRIGGERINOUT_TESTMODE_REQUEST_INSTANCE_ID = "1";

class Cmp_DemoClient : public rb::pt::interfaces::IComponentSwc
{
  private:

    ara::log::Logger &m_logger;
    bool setDefaultFG_Off;
    bool setDefaultFG_Verify;

    // Pointer to proxy instance
    std::shared_ptr<bosch::vrte::sm::proxy::TriggerIn_GenericProxy> m_proxy_Generic;
    std::shared_ptr<ara::sm::sysmode_request::proxy::TriggerInOut_SysModeRequestProxy> m_proxy_SysModeRequest;
    std::shared_ptr<ara::sm::proxy::TriggerOut_ComponentStateStatusProxy> m_proxy_OutCmStateStatus;
    std::shared_ptr<ara::sm::testclient_request::proxy::TriggerInOut_TestClientRequestProxy> m_proxy_TC_SysModeRequest;
    std::shared_ptr<ara::sm::testmode_request::proxy::TriggerInOut_TestModeRequestProxy> m_proxy_TestModeRequest;

    // Proxy to subscribe STM and to change states of DiagFG (DiagFunctionGroup), take effect just now.
    std::shared_ptr<ara::sm::default_fg::proxy::TriggerInOut_StateDefaultFGProxy> m_DefaultFG_Proxy;
    std::shared_ptr<ara::sm::sysmode_fg::proxy::TriggerInOut_StateSysModeFGProxy> m_SysModeFG_Proxy;
    float m_Kick;
    std::thread m_thread;
    std::promise<int32_t> m_promise;
    static constexpr auto waitingPeriodDefaultFGOFF = std::chrono::milliseconds(9000);
    //class COsmEINCProject
    std::shared_ptr<CDemoClientComponentClientImpl>   m_DemoClientComponentClient;

    // map for sysmode ara::sm::SysModeType
    static const std::map<uint8_t, std::string> map_sysmode2string;
    static const std::map<std::string,uint8_t> map_string2sysmode;

    // map for testmode ara::sm::TestModeType
    static const std::map<uint8_t, std::string> map_testmode2string;
    static const std::map<std::string,uint8_t> map_string2testmode;

    /* Methods */
    void Task(std::future<int32_t> &&future);

    void vSetStateDefaultFg(std::string f_state);
    void vSetStateSysModeFg(std::string f_state);
    /* Default FG*/
    bool findAndSubscribeDefaultFG(void);
    bool checkSubscriptionDefaultFG(void);
    void receiveFieldEventCallbackDefaultFG(void);
    bool checkAndHandleDefaultFG(void);

    /* SysMode FG*/
    bool findAndSubscribeSysModeFG(void);
    bool checkSubscriptionSysModeFG(void);
    void receiveFieldEventCallbackSysModeFG(void);
    bool checkAndHandleSysModeFG(void);

    /* OSM */
    bool findAndSubscribeCmStatus(void);
    void vSetOsmState(std::string f_state);  // calling the ara::com set osm state
    void vSetCmState(std::string f_name, std::string f_state);               // calling the ara::com trigger cm state
    void vGetCmState(void);
    void vSetSysMode(std::string f_state);
    void vGetSysModeState(void);

    /* TestClient FG, Write invalid state to Persistency */
    void vTCSetSysMode(std::string& f_state);
    void vTCGetSysModeState(void);

    /* TestMode FG */
    void vSetTestMode(std::string f_state);

  public:
    Cmp_DemoClient(const ara::com::InstanceIdentifier &f_instance);

    // these three functions are required by inheritance of the virtual class IComponent
    int32_t Init() override;
    int32_t Run() override;
    int32_t Shutdown() override;

    /* rule of five */
    /// @brief Destructor
    ~Cmp_DemoClient();
    /// @brief Copy constructor
    Cmp_DemoClient(Cmp_DemoClient const &) = delete;
    /// @brief Copy Assignment operator
    Cmp_DemoClient &operator=(Cmp_DemoClient const &) & = delete;
    /// @brief  Move Constructor
    Cmp_DemoClient(Cmp_DemoClient &&) = delete;
    /// @brief Move Assignment Operator
    Cmp_DemoClient &operator=(Cmp_DemoClient &&) & = delete;
};

}  // namespace demoserver
}  // namespace stm
}  // namespace vrte
}  // namespace bosch

#endif
