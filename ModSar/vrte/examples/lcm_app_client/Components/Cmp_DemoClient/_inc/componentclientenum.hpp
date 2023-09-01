//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2019 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================
//
/// @file      componentclientenum.hpp
/// @brief     Enum for componentclient
/// @copyright Robert Bosch GmbH 2019
/// @author    VRTE StM Team
//=============================================================================

#ifndef COMPONENTCLIENTENUM_HPP_INCLUDED
#define COMPONENTCLIENTENUM_HPP_INCLUDED

#include <map>
#include <string>

constexpr uint8_t INVALID_COMP_MODE = 255;
constexpr uint8_t COMP_STATE_STATUS_SUCCESS = 0;
constexpr uint8_t INVALID_COMP_STATE_STATUS = 255;

namespace bosch
{
namespace vrte
{
namespace stm
{
namespace democlient
{

enum EComponentStateClientReturnType : uint8_t
    {
        kSuccess = 0,       ///< component state change successfully completed
        kGeneralError = 1,  ///< error on interface
        kPending = 2,       ///< state change accepted for processing, but not accepted for finally being carried out
        kInvalid = 3,       ///< unknown state
        kAborted = 4,       ///< confirm of aborted state change due to other state change incoming
        kRejected = 5,      ///< immediate (in handler function) or delayed (after kPending reporting) information that state was not accepted to be taken. State Management will have to ask again for this state (e.g. with kForced set)
        kUnchanged = 6      ///< state was not changed since last request to get new Component State. Only used for polling mode in conjunction with ComponentClient::GetComponentState()
    };

static std::map<EComponentStateClientReturnType, std::string> ComponentStateClientReturnTypeMap = {
    {EComponentStateClientReturnType::kSuccess, "Success"},
    {EComponentStateClientReturnType::kGeneralError, "GeneralError"},
    {EComponentStateClientReturnType::kPending, "Pending"},
    {EComponentStateClientReturnType::kInvalid, "Invalid"},
    {EComponentStateClientReturnType::kAborted, "Aborted"},
    {EComponentStateClientReturnType::kRejected, "Rejected"},
    {EComponentStateClientReturnType::kUnchanged, "Unchanged"}};

/*
for future using if need
static std::string ComponentStateClientReturnTypeToString(uint8_t f_status)
{
    return ComponentStateClientReturnTypeMap[static_cast<EComponentStateClientReturnType>(f_status)];
}*/

static uint8_t ComponentStateClientReturnTypeToUint8(std::string f_status)
{
    uint8_t ret = 255;
    for (auto it : ComponentStateClientReturnTypeMap)
    {
        if (it.second == f_status)
            ret = static_cast<EComponentStateClientReturnType>(it.first);
    }
    return ret;
}

}  // namespace democlient
}  // namespace stm
}  // namespace vrte
}  // namespace bosch
#endif  // COMPONENTCLIENTENUM_HPP_INCLUDED
