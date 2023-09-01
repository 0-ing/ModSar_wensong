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
/// @file      stmdemoclientcompstaterequestproxyinterface.hpp
/// @brief
/// @copyright Robert Bosch GmbH 2019
/// @author    VRTE StM Team
//=============================================================================

#ifndef DEMOCLIENTAPPCOMPSTATEREQUESTPROXYINTERFACE_HPP_INCLUDED
#define DEMOCLIENTAPPCOMPSTATEREQUESTPROXYINTERFACE_HPP_INCLUDED

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

class CDemoClientAppCompStateRequestProxyInterface
{
public:
    CDemoClientAppCompStateRequestProxyInterface()                                                = default;
    virtual ~CDemoClientAppCompStateRequestProxyInterface()                                       = default;
    virtual bool vRegisterComponentStateRequestEvent(componentstaterequest_callback_t f_callback) = 0;
};

}  // namespace democlient
}  // namespace stm
}  // namespace vrte
}  // namespace bosch

#endif  // DEMOCLIENTAPPCOMPSTATEREQUESTPROXYINTERFACE_HPP_INCLUDED
