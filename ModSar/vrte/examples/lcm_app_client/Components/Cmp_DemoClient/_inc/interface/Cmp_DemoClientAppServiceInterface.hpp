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
/// @file      stmdemoclientserviceinterface.hpp
/// @brief     StM Example App serivce Interface
/// @copyright Robert Bosch GmbH 2019
/// @author    VRTE StM Team
//=============================================================================

#ifndef DEMOCLIENTAPPSERVICEINTERFACE_HPP_INCLUDED
#define DEMOCLIENTAPPSERVICEINTERFACE_HPP_INCLUDED

#include <cstdint>

namespace bosch
{
namespace vrte
{
namespace stm
{
namespace democlient
{

class CDemoClientAppServiceInterface
{
public:
    CDemoClientAppServiceInterface()                  = default;
    virtual ~CDemoClientAppServiceInterface()         = default;
    virtual void vInitService()                       = 0;
    virtual void vStartService()                      = 0;
    virtual void vStopService()                       = 0;
    virtual void vUpdateEventStatus(uint8_t f_status) = 0;
    virtual void vTriggerEvent()                      = 0;
};

}  // namespace democlient
}  // namespace stm
}  // namespace vrte
}  // namespace bosch

#endif  // DEMOCLIENTAPPSERVICEINTERFACE_HPP_INCLUDED
