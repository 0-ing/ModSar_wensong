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
/// @file      stmdemoclientcompstaterequestproxycfginterface.hpp
/// @brief
/// @copyright Robert Bosch GmbH 2019
/// @author    VRTE StM Team
//=============================================================================

#ifndef DEMOCLIENTAPPCOMPSTATEREQUESTPROXYCFGINTERFACE_HPP_INCLUDED
#define DEMOCLIENTAPPCOMPSTATEREQUESTPROXYCFGINTERFACE_HPP_INCLUDED

#include <cstdint>
#include <functional>
#include <string>

using componentstaterequest_callback_t = std::function<void(std::string, std::string, uint8_t)>;

namespace bosch
{
namespace vrte
{
namespace stm
{
namespace democlient
{

class CDemoClientAppCompStateRequestProxyCfgInterface
{
public:
    CDemoClientAppCompStateRequestProxyCfgInterface()                                             = default;
    virtual ~CDemoClientAppCompStateRequestProxyCfgInterface()                                    = default;
    virtual bool vRegisterComponentStateRequestEvent(componentstaterequest_callback_t f_callback) = 0;
};

}  // namespace democlient
}  // namespace stm
}  // namespace vrte
}  // namespace bosch

#endif  // DEMOCLIENTAPPCOMPSTATEREQUESTPROXYCFGINTERFACE_HPP_INCLUDED
