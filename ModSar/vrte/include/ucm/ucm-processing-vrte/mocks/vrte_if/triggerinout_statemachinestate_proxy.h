/*
**********************************************************************************************************************
*
* COPYRIGHT RESERVED, Robert Bosch GmbH, 2020. All rights reserved.
* The reproduction, distribution and utilization of this document as well as the communication of its contents to
* others without explicit authorization is prohibited. Offenders will be held liable for the payment of damages.
* All rights reserved in the event of the grant of a patent, utility model or design.
*
**********************************************************************************************************************
*/
/**
 * \\file  triggerinout_statemachinestate_proxy.h
 *
 * \\authors  This file was generated with VRTE Flexible Safety - Manifest to Adaptive Runtime API Generator
 *
 * \\brief  Function block model for TriggerInOut_StateMachineState
 *
 * The proxy is the representative of the (eventually remote) service instance.
 * It is used on the client application side to communicate with the service instance.
 *
 */

#ifndef SERVICE_TRIGGERINOUT_STATEMACHINESTATE_PROXY_H_INCLUDED
#define SERVICE_TRIGGERINOUT_STATEMACHINESTATE_PROXY_H_INCLUDED

#include <string>
#include <functional>

#include "types.hpp"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

namespace ara  {
namespace sm {

struct FunctionGroupStateType
{
    FunctionGroupStateType() = default;

    template<class T>
    FunctionGroupStateType(T&&) {}
};


struct FunctionGroupStateResultType
{

};

namespace machine_state {
namespace proxy {

namespace fields {

     using Notifier = ara::com::Decorator<ara::sm::FunctionGroupStateResultType>;
     using Trigger = ara::com::Decorator<ara::sm::FunctionGroupStateType>;

} // namespace fields

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
struct TriggerInOut_StateMachineStateProxy
{
    class HandleType
    {
    public:
        HandleType(const ara::com::InstanceIdentifier&) {}
        ~HandleType() = default;
    };

    explicit TriggerInOut_StateMachineStateProxy(const HandleType& f_handle) {}
    ~TriggerInOut_StateMachineStateProxy() = default;

    /*fields*/
    fields::Notifier Notifier;
    fields::Trigger Trigger;
};
#pragma GCC diagnostic pop

} // namespace proxy
} // namespace machine_state
} // namespace sm
} // namespace ara

#pragma GCC diagnostic pop

#endif



