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
/// @file      stmdemoclientinterface.hpp
/// @brief     StM Example App Interface
/// @copyright Robert Bosch GmbH 2019
/// @author    VRTE StM Team
//=============================================================================

#ifndef DEMOCLIENTAPPINTERFACE_HPP_INCLUDED
#define DEMOCLIENTAPPINTERFACE_HPP_INCLUDED

namespace bosch
{
namespace vrte
{
namespace stm
{
namespace democlient
{

class CDemoClientAppInterface
{
public:
    CDemoClientAppInterface()          = default;
    virtual ~CDemoClientAppInterface() = default;
    virtual void vInit()               = 0;
    virtual void vStart()              = 0;
    virtual void vStop()               = 0;
};

}  // namespace democlient
}  // namespace stm
}  // namespace vrte
}  // namespace bosch

#endif  // DEMOCLIENTAPPINTERFACE_HPP_INCLUDED
