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
/// @file      stmdemoclientcompstatestatusserviceinterface.hpp
/// @brief     StM Example App serivce Interface
/// @copyright Robert Bosch GmbH 2019
/// @author    VRTE StM Team
//=============================================================================

#ifndef DEMOCLIENTAPPCOMPSTATESTATUSSERVICEINTERFACE_HPP_INCLUDED
#define DEMOCLIENTAPPCOMPSTATESTATUSSERVICEINTERFACE_HPP_INCLUDED

namespace bosch
{
namespace vrte
{
namespace stm
{
namespace democlient
{

class CDemoClientAppCompStateStatusServiceInterface
{
public:
    CDemoClientAppCompStateStatusServiceInterface()          = default;
    virtual ~CDemoClientAppCompStateStatusServiceInterface() = default;
    virtual void vUpdateComponentState(std::string f_state)  = 0;
    virtual void vUpdateComponentClientReturn(uint8_t f_ret) = 0;
    virtual void vComponentStateConfirm()                    = 0;
};

}  // namespace democlient
}  // namespace stm
}  // namespace vrte
}  // namespace bosch

#endif  // DEMOCLIENTAPPCOMPSTATESTATUSSERVICEINTERFACE_HPP_INCLUDED
